package com.kingstargroup.fdykt.cancellock;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;

public class CancelLockAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CancelLockAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("error");
		try {
			DB2AccountDAO accdao = new DB2AccountDAO();
			ActionErrors errors = new ActionErrors();
			String reqip = request.getRemoteAddr();
//			InetAddress addr = InetAddress.getLocalHost();
//			String reqip = addr.getHostAddress();// 获得本机IP
			int deviceid = -2;
			try {
				deviceid = accdao.getdevidFromip(reqip);			
				if(deviceid<0){
					errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("deviceid.notregister"));
					saveErrors(request, errors);
					return mapping.findForward("failure");
				}
			} catch (Exception e1) {
				e1.printStackTrace();
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
			
			
			if (doUnlock(mapping, request, session,deviceid)) {
				forward = mapping.findForward("success");
				KSDaoSessionFactory.commit();
			} else {
				forward = mapping.findForward("failure");
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
			logger.error("事务失败:解挂卡失败");
		}
		return forward;
	}

	private boolean doUnlock(ActionMapping mapping, HttpServletRequest request,
			HttpSession session,int deviceid) {
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();
		String cardphyid = request.getParameter("cardphyid");
		String bala = request.getParameter("bala");
		String cxCnt = request.getParameter("cxCnt");
		String termid = request.getParameter("termid");
		String transdate = request.getParameter("transdate");
		String transtime =  request.getParameter("transtime");
		String lockcardcnt = request.getParameter("lockcardcnt");

		
		ActionErrors errors = new ActionErrors();
		// 取得系统日期时间
		try {
			String sysdate = new DB2SysParaDAO().getDBDateTime();
//			String systime = sysdate.substring(8);
			sysdate = sysdate.substring(0, 8);
			card = carddao.getCardInfoByPhyid(cardphyid);
			if(card==null){
				ArrayList cardlist = carddao.getCardInfoListByPhyid(cardphyid);
				if(cardlist!=null&&cardlist.size()>0){
					errors.add("login", new ActionError(
							"back.error", "卡片状态为注销，已不能使用本系统。"));
					saveErrors(request, errors);
				}else{
					errors.add("login", new ActionError(
							"back.error", "卡片信息未找到，卡片未发行！"));
					saveErrors(request, errors);
				}
				return false;
			}
			String state = card.getCardstatus();
			if (state == null || state.length() != 10)
				return false;
			char[] stateAry = state.toCharArray();
			if (KSConstant.BOOLEAN_TRUE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {
				errors.add("100561", new ActionError("errors.100561"));
				saveErrors(request, errors);
				return false;
			}
			if(KSConstant.BOOLEAN_TRUE == stateAry[KSConstant.CARDSTAT_TYPE_LOST]) {
				request.setAttribute("CARDSTAT", "3");//挂失卡
			}else{
				request.setAttribute("CARDSTAT", "0");
			}

				long xpackhandle = 0;
				int drtpno = 0;
				int errcode[] = { 1 };
				byte errmsg[] = new byte[300];
				int branchno = 0;// 后台drtp功能号
				int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
						"mainfunction1", 9000);
				int func = KSConfiguration.getInstance().getPropertyAsInt(
						"logicfunc_card_lock_cancel", 850011);// 后台业务功能号
				int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
						3);// 默认重试次数
				int[] RetCode = new int[1];
				int[] RecordCount = new int[1];
				bccclt bcc = null;
				try {
					bcc = BccctlInit.getBccctlInstance();				
					xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
							.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
					if (0 != xpackhandle) {
						bcc.SetRequestType(xpackhandle, func);
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
								Integer.parseInt(String.valueOf(card.getCardno())));// 卡号
						bcc.SetStringFieldByName(xpackhandle, 0,
								"sstation0".getBytes(), cardphyid.getBytes());// 物理卡号
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
								Integer.parseInt(bala));// 卡交易前余额(分)
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
								Integer.parseInt(cxCnt));// 交易次数
						bcc.SetStringFieldByName(xpackhandle, 0, "sphone".getBytes(), termid.getBytes());// 终端号
						bcc.SetStringFieldByName(xpackhandle, 0, "sdate0"
								.getBytes(), transdate.getBytes());// 终端号
						bcc.SetStringFieldByName(xpackhandle, 0, "stime0"
								.getBytes(), transtime.getBytes());// 终端号
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
								Integer.parseInt(lockcardcnt));// 交易次数
						bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
								.getBytes(), String.valueOf(deviceid).getBytes());//终端号

						boolean bccret = false;
						bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
									mainfunction, 10000, errcode, errmsg);

						if (bccret) {
							bcc.GetRetCode(xpackhandle, RetCode);
							bcc.GetRecordCount(xpackhandle, RecordCount);
							if (0 == RetCode[0]) {
								if (0 < RecordCount[0]) {
									
									byte[] inStr = new byte[300];
									int[] intRec = new int[1];
									Arrays.fill(inStr, (byte) 0);
									bcc.GetStringFieldByName(xpackhandle, 0, "sdate0"
											.getBytes(), inStr, 300);
									String sdate0 = BccUtil.getStringFromByte(inStr);
									
									Arrays.fill(inStr, (byte) 0);
									bcc.GetStringFieldByName(xpackhandle, 0, "stime0"
											.getBytes(), inStr, 300);
									String stime0 = BccUtil.getStringFromByte(inStr);
									
									Arrays.fill(intRec, 0);
									bcc.GetIntFieldByName(xpackhandle, 0, "lvol4"
											.getBytes(), intRec);// 出卡值（分）
									String amount = String.valueOf(intRec[0]);
									
									Arrays.fill(intRec, 0);
									bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
											.getBytes(), intRec);// 出卡值（分）
									String out_card_amount = String.valueOf(intRec[0]);
									
									String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
									"172.0.0.1");
									String drtpPort = KSConfiguration.getInstance().getProperty(
											"drtpport1", "4000");
									String svrFunc = KSConfiguration.getInstance().getProperty(
											"mainfunction1", "6000");
									request.setAttribute("ipServer", ipServer);
									request.setAttribute("drtpPort", drtpPort);
									request.setAttribute("svrFunc", svrFunc);
									
									request.setAttribute("cardphyid",cardphyid);
									request.setAttribute("cxCnt",cxCnt);
									request.setAttribute("sdate0", sdate0);
									request.setAttribute("stime0", stime0);
									request.setAttribute("amount",amount);
									request.setAttribute("outCardAmount",out_card_amount);
									
									return true;
								} else {
									errors.add("lost", new ActionError(
											"back.error", "后台处理失败"));
									saveErrors(request, errors);
									return false;
								}
							} else {
								// 失败
								if (0 < RecordCount[0]) {
									byte[] vsmess = new byte[300];
									bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
									String vs_mess = BccUtil.getStringFromByte(vsmess);
									errors.add("lost", new ActionError(
											"back.error",vs_mess));
									saveErrors(request, errors);	
									return false;
								} else {
									
									errors.add("lost", new ActionError(
											"back.error", "后台处理失败"));
									saveErrors(request, errors);
									return false;
								}

							}

						} else {
							// 请求失败
							errors.add("lost", new ActionError("errors.request"));
							saveErrors(request, errors);
							return false;
						
						}
					}
					errors.add("lost", new ActionError(
							"back.error", "系统出现异常，请稍后重试！"));
					saveErrors(request, errors);
					return false;

				} catch (Exception e) {
					// TODO: handle exception
					logger.error(e.getMessage());
					errors.add("lost", new ActionError(
							"back.error", "系统出现异常，请稍后重试！"));
					saveErrors(request, errors);
					return false;
				} catch (UnsatisfiedLinkError e) {
					logger.error(e.getMessage());
					errors.add("lost", new ActionError(
							"back.error", "系统出现异常，请稍后重试！"));
					saveErrors(request, errors);
					return false;
				} finally {
					if (xpackhandle != 0) {
						bcc.DeleteXpackHandle(xpackhandle);
					}
				}
		} catch (Exception e) {
			logger.error("解挂卡失败:" + e.getMessage());
			return false;
		}
	}

}

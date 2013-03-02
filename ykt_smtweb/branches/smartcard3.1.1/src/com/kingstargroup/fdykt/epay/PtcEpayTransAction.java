package com.kingstargroup.fdykt.epay;

import java.sql.SQLException;
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
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;

public class PtcEpayTransAction extends Action {
	/**
	 * Logger for this class
	 */
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(PtcEpayTransAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		String password = session.getAttribute("password").toString();
		String cardphyid = request.getParameter("cardphyid");//物理卡号
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		String dptCnt = request.getParameter("dptCnt");
		String transflag = request.getParameter("transflag");
		String epaypwd = request.getParameter("epaypwd");
		ActionErrors errors = new ActionErrors();
		
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1", "172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty("drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty("mainfunction1", "6000");
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("dptCnt", dptCnt);
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		request.setAttribute("transflag", transflag);
		
		
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		CardDTO card = new CardDTO();
		String cardpwd = null;
		String secepaypwd = null;
		try {
			cardpwd = Util.DESEnc(password);
		    secepaypwd = Util.toMD5(epaypwd);
		    
			card = carddao.getCardInfoById(cardphyid);
			if(card==null){
				logger.error("操作失败,请先检查卡片状态是否为正常卡！");
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("操作失败,请先检查卡片状态是否为正常卡！"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
			
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败"+e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("cardinfo.geterror"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");
		}
		
		String reqip = request.getRemoteAddr();
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				logger.error("设备未注册，不能使用此功能！");
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
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("epay_trans", 846336);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "lcert_code".getBytes(), String.valueOf(deviceid).getBytes());// 站点号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),Integer.parseInt(String.valueOf(card.getCardno())));// 交易卡号
				bcc.SetStringFieldByName(xpackhandle, 0, "sstation0".getBytes(),cardphyid.getBytes());//物理卡号
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit".getBytes(), cardpwd.getBytes());//卡密码
				bcc.SetStringFieldByName(xpackhandle, 0, "lvol3".getBytes(), transflag.getBytes());//转账方向
				bcc.SetIntFieldByName(xpackhandle, 0, "damt0".getBytes(),Integer.parseInt(money));//转账金额
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),Integer.parseInt(cardBala));// 交易前卡余额
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),Integer.parseInt(txCnt));//消费交易次数
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),Integer.parseInt(dptCnt));//充值交易次数
				if(transflag.equals("1")){
					bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(), secepaypwd.getBytes());//帐户密码
				}
				
				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							byte[] byteStr = new byte[300];
							int[] intRec = new int[1];
							
							Arrays.fill(byteStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3".getBytes(), byteStr, 81);
							String sdate3=BccUtil.getStringFromByte(byteStr);
							
							Arrays.fill(byteStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "stime3".getBytes(), byteStr, 81);
							String stime3 =  BccUtil.getStringFromByte(byteStr);
							
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8".getBytes(), intRec);// 余额（分）
							String out_card_amount = String.valueOf(intRec[0]);
							
							Arrays.fill(byteStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(), byteStr, 81);
							String sphone3=BccUtil.getStringFromByte(byteStr);
							
							Arrays.fill(byteStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "saddr".getBytes(), byteStr, 81);
							String saddr =  BccUtil.getStringFromByte(byteStr);
							
							request.setAttribute("sdate3", sdate3);
							request.setAttribute("stime3", stime3);
							request.setAttribute("outCardAmount", out_card_amount);
							request.setAttribute("sphone3", sphone3);
							request.setAttribute("saddr", saddr);
							logger.info("sdate3:"+sdate3);
							
							return mapping.findForward("success");
						} else {
							logger.error("后台处理失败");
							errors.add(ActionMessages.GLOBAL_MESSAGE,new ActionError("back.error","后台处理失败"));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							logger.error(vs_mess);
							errors.add(ActionMessages.GLOBAL_MESSAGE,new ActionError("back.error",vs_mess));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						} else {
							logger.error("后台处理失败");
							errors.add(ActionMessages.GLOBAL_MESSAGE,new ActionError("back.error","后台处理失败"));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败
					String s = BccUtil.getStringFromByte(errmsg);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("errors.connet"));
					saveErrors(request, errors);
					return mapping.findForward("failure");
				}
			}

			logger.error("系统出现异常，请稍后重试！");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("system.error"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("system.error"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("system.error"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}

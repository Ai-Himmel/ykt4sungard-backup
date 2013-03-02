package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

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
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;

public class ConsumerLimitResetAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ConsumerLimitResetAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String CardPhyId = request.getParameter("CardPhyId");// 物理卡号long
		String cardbal = request.getParameter("cardbal");
		String payCardCnt = request.getParameter("payCardCnt");
		String dptCardCnt = request.getParameter("dptCardCnt");
		String maxpercount = request.getParameter("maxpercount");
		String maxperday = request.getParameter("maxperday");
		ActionErrors errors = new ActionErrors();

		int deviceid = -2;
		try {
			String reqip = request.getRemoteAddr();
//			System.out.print("ip请求"+reqip);
//			InetAddress addr = InetAddress.getLocalHost();
//			String reqip = addr.getHostAddress();// 获得本机IP
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"deviceid.notregister"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(CardPhyId);
		} catch (Exception e) {
			System.out.println("卡信息读取失败");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"cardinfo.geterror"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		try {
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_consumerlimit_reset", 846320);// 后台业务功能号
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

					bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
							.getBytes(), String.valueOf(deviceid).getBytes());// 终端号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt(String.valueOf(card.getCardno())));// 卡号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
							Integer.parseInt(dptCardCnt));// 充值次数
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
							Integer.parseInt(payCardCnt));// 交易次数
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
							Integer.parseInt(cardbal));// 卡余额
					bcc.SetStringFieldByName(xpackhandle, 0, "sstation1"
							.getBytes(), CardPhyId.getBytes());// 物理卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1"
							.getBytes(), "1".getBytes());
					double d_maxpercount = Double.parseDouble(maxpercount);
					int n_maxpercount = (int)d_maxpercount * 100;
					double d_maxperday = Double.parseDouble(maxperday);
					int n_maxperday = (int)d_maxperday * 100;
					bcc.SetDoubleFieldByName(xpackhandle, 0, "damt11"
							.getBytes(), d_maxpercount);// 单次消费限额(元)
					bcc.SetDoubleFieldByName(xpackhandle, 0, "damt12"
							.getBytes(), d_maxperday);// 日累计消费限额(元)

					boolean bccret = false;
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 5000, errcode, errmsg);
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							request.setAttribute("CardPhyId", CardPhyId);
							String str_maxpercount = String.valueOf(n_maxpercount);
							if(str_maxpercount.indexOf(".")!=-1){
							str_maxpercount = str_maxpercount.substring(0,str_maxpercount.indexOf("."));
							}
							String str_maxperday = String.valueOf(n_maxperday);
							if(str_maxperday.indexOf(".")!=-1){
								str_maxperday = str_maxperday.substring(0,str_maxperday.indexOf("."));
							}
							request.setAttribute("maxpercount",str_maxpercount);
							request.setAttribute("maxperday",str_maxperday);							
							return mapping.findForward("success");
						} else {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);;
								errors.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionError("back.error",vs_mess));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							} else {
								errors.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionError("back.error","后台处理失败"));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							}

						}

					} else {
						// 请求失败

						errors.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionError("errors.request"));
						saveErrors(request, errors);
						return mapping.findForward("failure");

					}
				}
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"system.error"));
				saveErrors(request, errors);
				return mapping.findForward("failure");

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"system.error"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"system.error"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"cardinfo.fresherror"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
	}
}

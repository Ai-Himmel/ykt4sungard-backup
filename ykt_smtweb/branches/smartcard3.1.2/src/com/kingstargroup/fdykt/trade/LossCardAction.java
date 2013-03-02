package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

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
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.BccUtil;

public class LossCardAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LossCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.getInputForward();
		HttpSession session = request.getSession();
		if (null == session.getAttribute("card_id")|| null == session.getAttribute("stuempno"))
			return mapping.findForward("userlogon");
		KSDaoSessionFactory.createSession();
		try {
			forward = doLossCard(mapping, request, session);
			if (forward.getName().equals("success")) {
				KSDaoSessionFactory.commit();
			} else {
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doLossCard(ActionMapping mapping,
			HttpServletRequest request, HttpSession session) {
		DB2AccountDAO accdao = new DB2AccountDAO();
		String stuempno = (String) session.getAttribute("stuempno");
		String password = (String) session.getAttribute("password");
		String card_id = (String) session.getAttribute("card_id");
		String reqip = request.getRemoteAddr();

		ActionErrors errors = new ActionErrors();
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
		
		try {					
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_card_loss", 846801);// 后台业务功能号
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
							Integer.parseInt(card_id));// 卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), password.getBytes());// 密码
					bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
							.getBytes(), String.valueOf(deviceid).getBytes());//终端号
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1"
							.getBytes(), "1".getBytes());//挂失解挂标识

					boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 10000, errcode, errmsg);

					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							return mapping.findForward("success");
						} else {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								
								errors.add("lost", new ActionError(vs_mess));
								if (!errors.isEmpty()) {
									saveErrors(request, errors);
								}
								return mapping.findForward("failure");
							} else {
								errors.add("lost", new ActionError("后台处理失败"));
								if (!errors.isEmpty()) {
									saveErrors(request, errors);
								}
								return mapping.findForward("failure");
							}

						}

					} else {
						// 请求失败
					
						errors.add("lost", new ActionError("errors.request"));
						if (!errors.isEmpty()) {
							saveErrors(request, errors);
						}
						return mapping.findForward("failure");
					
					}
				}
				errors.add("lost", new ActionError("系统出现异常，请稍后重试！"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				errors.add("lost", new ActionError("系统出现异常，请稍后重试！"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				errors.add("lost", new ActionError("系统出现异常，请稍后重试！"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			logger.error("挂失卡失败 : " + e.getMessage() + ", stuempno[" + stuempno
					+ "]");
			errors.add("lost", new ActionError("挂失卡失败!请稍后重试！"));
			if (!errors.isEmpty()) {
				saveErrors(request, errors);
			}
			return mapping.findForward("failure");
		}
	}
}

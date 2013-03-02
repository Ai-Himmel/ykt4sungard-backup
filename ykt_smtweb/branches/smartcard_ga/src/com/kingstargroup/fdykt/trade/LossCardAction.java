package com.kingstargroup.fdykt.trade;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionError;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;

import java.sql.SQLException;
import java.util.*;

public class LossCardAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LossCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.getInputForward();
		HttpSession session = request.getSession();
		if (null == session.getAttribute("cutid")
				|| null == session.getAttribute("manId"))
			return forward;
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
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();

		String cutid = ((Integer) session.getAttribute("cutid")).toString();
		String manId = (String) session.getAttribute("manId");
		String password = (String) session.getAttribute("password");
		ActionErrors errors = new ActionErrors();
		try {
			DB2AccountDAO accountdao = new DB2AccountDAO();
			ArrayList accounts = accountdao.getAccountInfo(manId);
			if (accounts.size() == 0) {
				return (mapping.findForward("isnull"));
			}
			AccountDTO account = (AccountDTO) accounts.get(0);
			String cardid = String.valueOf(account.getCard_id());

			card = carddao.getCardInfo(cardid);
			String state = card.getStateId();
			// 检查客户信息，判断是否可以挂失
			if (state.substring(0, 4).equals(KSConstant.CARDSTAT_LOGOUT)) {
				errors.add("unable", new ActionError("errors.unable"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}
			if (state.substring(1, 2).equals("1")) {
				errors.add("lost", new ActionError("errors.lost"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}
			
			
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_card_loss", 847318);// 后台业务功能号
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
							Integer.parseInt(cutid));// 客户号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							Integer.parseInt("0"));// 交易卡号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
							Integer.parseInt("0"));// 交易卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd"
							.getBytes(), password.getBytes());//密码
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
							.getBytes(), "1".getBytes());//校验密码
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), "web".getBytes());//密码

					boolean bccret = false;
					while (--tries >= 0) {
						bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 2000, errcode, errmsg);
						if (bccret) {
							break;
						}
					}
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
								int i;
								for (i = 0; i < vsmess.length; i++) {
									if (vsmess[i] == 0) {
										break;
									}
								}
								String vs_mess = new String(vsmess, 0, i);
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
			logger.error("挂失卡失败 : " + e.getMessage() + ", manId[" + manId
					+ "]");
			errors.add("lost", new ActionError("挂失卡失败!请稍后重试！"));
			if (!errors.isEmpty()) {
				saveErrors(request, errors);
			}
			return mapping.findForward("failure");
		}
	}
}

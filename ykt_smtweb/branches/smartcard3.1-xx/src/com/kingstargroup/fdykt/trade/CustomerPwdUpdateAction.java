// Created by Xslt generator for Eclipse.
// XSL :  not found (java.io.FileNotFoundException:  (Bad file descriptor))
// Default XSL used : easystruts.jar$org.easystruts.xslgen.JavaClass.xsl

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
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;

/**
 * AccountSearchAction.java created by EasyStruts - XsltGen.
 * http://easystruts.sf.net created on 01-18-2005
 * 
 * XDoclet definition:
 * 
 * @struts:action path="/accountSearch" name="accountsearchForm"
 *                attribute="accountSearchForm" input="/accountSearch.jsp"
 *                validate="true"
 * @struts:action-forward name="/accountResult.jsp" path="/accountResult.jsp"
 */
public class CustomerPwdUpdateAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CustomerPwdUpdateAction.class);

	// --------------------------------------------------------- Instance
	// Variables

	// --------------------------------------------------------- Methods

	/**
	 * Method execute
	 * 
	 * @param ActionMapping
	 *            mapping
	 * @param ActionForm
	 *            form
	 * @param HttpServletRequest
	 *            request
	 * @param HttpServletResponse
	 *            response
	 * @return ActionForward
	 * @throws Exception
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String cardno = (String) session.getAttribute("cardno");
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("logon");
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("failure");
		try {
			DB2AccountDAO accdao = new DB2AccountDAO();
			ActionErrors errors = new ActionErrors();
			String reqip = request.getRemoteAddr();
			int deviceid = -2;
			try {
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

			if (doUpdatePswd(mapping, form, request, deviceid)) {
				forward = mapping.findForward("success");
				KSDaoSessionFactory.commit();
			} else {				
				KSDaoSessionFactory.rollback();
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
				"errors.pwdReset"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (SQLException e) {
			logger.error("更新卡密码失败", e);
			e.printStackTrace();
		}
		return forward;
	}

	private boolean doUpdatePswd(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, int deviceid) {

		HttpSession session = request.getSession();
		CustomerPwdUpdateForm customerPwdUpdateform = (CustomerPwdUpdateForm) form;
		DB2CardDAO carddao = new DB2CardDAO();
		ActionErrors errors = new ActionErrors();

		String cardno = (String) session.getAttribute("cardno");

		String pwd = customerPwdUpdateform.getPwd();
		String newpwd = customerPwdUpdateform.getNewPwd();
		try {
			CardDTO carddto = carddao.getCardInfo(cardno);
			String oldpwd = carddto.getCardpwd();
			String ciphered = Util.DESEnc(pwd);

			if (!ciphered.equals(oldpwd)) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"changepwd.oldpwderror"));
				saveErrors(request, errors);
				return false;
			}

			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_card_change_passwd", 847111);// 后台业务功能号
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
							Integer.parseInt(cardno));// 卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), pwd.getBytes());// 老密码
					bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
							.getBytes(), String.valueOf(deviceid).getBytes());// 终端号
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_no"
							.getBytes(), newpwd.getBytes());// 新密码

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
							request.setAttribute("newpwd", newpwd);
							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("changepwd.success"));
							saveErrors(request, errors);
							return true;
						} else {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);

								String vs_mess = BccUtil
										.getStringFromByte(vsmess);
								errors.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionError(vs_mess));
								saveErrors(request, errors);
								return false;
							} else {
								errors.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionError("后台处理失败"));
								saveErrors(request, errors);
								return false;
							}

						}

					} else {
						// 请求失败

						errors.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionError("errors.request"));
						saveErrors(request, errors);
						return false;

					}
				}
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"系统出现异常，请稍后重试！"));
				saveErrors(request, errors);
				return false;

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"系统出现异常，请稍后重试！"));
				saveErrors(request, errors);
				return false;
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"系统出现异常，请稍后重试！"));
				saveErrors(request, errors);
				return false;
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			return false;
		}
	}
}

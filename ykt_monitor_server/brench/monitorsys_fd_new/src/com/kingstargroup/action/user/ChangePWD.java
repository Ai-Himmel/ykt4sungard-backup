package com.kingstargroup.action.user;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:ChangePWD.java
 * Description: 用户修改密码 
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-10-09   何林青    添加用户修改密码功能
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class ChangePWD extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(ChangePWD.class);

	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		// filter
		HttpSession httpSession = request.getSession();
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
		.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		if (httpSession.getAttribute("userLogin") != null) {			
			Session session = HibernateSessionFactory.currentSession();			
			// get user info
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");

			Transaction tx = null;
			request.setCharacterEncoding("GBK");
			String oldPassword = request.getParameter("OldPassword");
			String newPasswordFirst = request.getParameter("NewPassword1");
			String newPasswordSecond = request.getParameter("NewPassword2");

			try {
				if ((oldPassword.equals(mapUserTable.getPassword()))
						&& (newPasswordFirst.equals(newPasswordSecond))) {
					// update password
					tx = session.beginTransaction();
					mapUserTable.setPassword(newPasswordFirst);
					session.update(mapUserTable);
					tx.commit();
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.SUCCESS,
									msgResources
											.getMessage("user.ChangePWD.CHANGE_PWD_SUCCESS"),
									null);
				} else if (!oldPassword.equals(mapUserTable.getPassword()
						.toString())) {
					// oldPassword error
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.OLD_PASSWORD_ERROR,
									msgResources
											.getMessage("user.ChangePWD.OLD_PASSWORD_ERROR"),
									null);
				} else if (!newPasswordFirst.equals(newPasswordSecond)) {
					// new password error
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.NEW_PASSWORD_ERROR,
									msgResources
											.getMessage("user.ChangePWD.NEW_PASSWORD_ERROR"),
									null);
				}

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (Exception e) {
				logger
						.error(
								"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				if (tx != null) {
					tx.rollback();
				}

			} finally {
				HibernateSessionFactory.closeSession();
			}

		} else {
			// user not login in
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.LOGIN_AGAIN_NEED,
					msgResources
							.getMessage("user.loginServlet.LOGIN_AGAIN_NEED"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

}

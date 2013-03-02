package com.kingstargroup.fdykt.logon;

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

import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AdminDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class AdminLoginAction extends Action {

	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(AdminLoginAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doLogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doLogin(ActionMapping mapping,
			HttpServletRequest request) {
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		DB2AdminDAO admindao = new DB2AdminDAO();

		try {
			if (null == password || "".equals(password)) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.emptypwd"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.getInputForward();
			}

			String ciphered = Util.DESEnc(password);
			if (admindao.checkLogin(username, ciphered)) {
				return (mapping.findForward("success"));
			}
			return (mapping.findForward("failure"));

		} catch (Exception e) {
			logger.error(e.getMessage());
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}
	}
}

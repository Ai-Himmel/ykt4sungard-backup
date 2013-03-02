package com.kingstargroup.fdykt.cancellock;

import java.sql.SQLException;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;


public class AccountAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(AccountAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionForward forward = mapping.findForward("logon");
		if (session.getAttribute("cardno") == null){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return forward;
		}
		KSDaoSessionFactory.createSession();
		
		forward = doAccountInfo(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doAccountInfo(ActionMapping mapping, HttpServletRequest request) {
		try {
			HttpSession session = request.getSession();
			String cardno = (String) session.getAttribute("cardno");
			DB2AccountDAO accountdao = new DB2AccountDAO();
			AccountDTO account = accountdao.getAccountInfoByCardno(cardno);
			if (account == null) {
				return (mapping.findForward("isnull"));
			}
			session.setAttribute("card_id", String.valueOf(account.getCardno()));
			session.setAttribute("account", account);
			return (mapping.findForward("success"));

		} catch (Exception e) {
			logger.error("查询客户信息失败");
			return (mapping.findForward("isnull"));
		}
	}
}

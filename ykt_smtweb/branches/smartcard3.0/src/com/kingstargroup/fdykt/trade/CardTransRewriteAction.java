package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class CardTransRewriteAction extends Action {
	/**
	 * Logger for this class
	 */

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
		
		HttpSession session = request.getSession(false);
		if(null==session.getAttribute("name")){
			return mapping.findForward("logon");
		}		
		String reqcardno = request.getParameter("reqcardno");
		String reqcardBalance = request.getParameter("reqcardbalance");
		String reqcardcnt = request.getParameter("reqcardbalance");
		String oldCardNo = request.getParameter("oldCardNo");
		String oldCardBalance = request.getParameter("oldCardBalance");
		String oldCardPwd = request.getParameter("oldCardPwd");
		String serialNo = request.getParameter("serialNo");
		String sdate3 = request.getParameter("sdate3");
		

		request.setAttribute("reqcardno", reqcardno);
		request.setAttribute("reqcardBalance", reqcardBalance);
		request.setAttribute("reqcardcnt", reqcardcnt);

		request.setAttribute("oldCardNo", oldCardNo);
		request.setAttribute("oldCardBalance", oldCardBalance);
		request.setAttribute("oldCardPwd", oldCardPwd);
		request.setAttribute("newCardName", session.getAttribute("name").toString());
		request.setAttribute("serialNo", serialNo);
		request.setAttribute("sdate3", sdate3);
		return (mapping.findForward("success"));
	}
}

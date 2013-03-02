package com.kingstargroup.fdykt.cardcard;

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
		
		String money = request.getParameter("money");
		String outcardphyno = request.getParameter("outcardphyno");
		String outcardbalance = request.getParameter("outcardbalance");
		String outcardcnt = request.getParameter("outcardcnt");
		String out_card_amount = request.getParameter("outCardAmount");

		request.setAttribute("money", money);
		request.setAttribute("outcardphyno", outcardphyno);
		request.setAttribute("outcardbalance", outcardbalance);
		request.setAttribute("outcardcnt", outcardcnt);
		request.setAttribute("outCardAmount",out_card_amount);
		
		return (mapping.findForward("success"));
	}
}

package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class CardTransReCardwriteAction extends Action {
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
		
		String reqcardno = request.getParameter("reqcardno");
		String outCardAmount = request.getParameter("outCardAmount");
		String reqcardcnt = request.getParameter("reqcardcnt");

		request.setAttribute("reqcardno", reqcardno);
		request.setAttribute("outCardAmount", outCardAmount);
		request.setAttribute("reqcardcnt", reqcardcnt);

		return (mapping.findForward("success"));
	}
}

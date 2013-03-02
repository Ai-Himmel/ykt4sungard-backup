package com.kingstargroup.fdykt.trade;

import java.io.UnsupportedEncodingException;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class CardPutinAction extends Action {
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
		try {
			request.setCharacterEncoding("GBK");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		String reqcardno = request.getParameter("reqcardno");
		String reqcardBalance = request.getParameter("reqcardBalance");
		String reqcardcnt = request.getParameter("reqcardcnt");
		String oldCardNo = request.getParameter("oldCardNo");
		String oldCardBalance = request.getParameter("oldCardBalance");
		String oldCardName = request.getParameter("oldCardName");
		String oldCardPwd = request.getParameter("oldCardPwd");

		request.setAttribute("reqcardno", reqcardno);
		request.setAttribute("reqcardBalance", reqcardBalance);
		request.setAttribute("reqcardcnt", reqcardcnt);

		request.setAttribute("oldCardNo", oldCardNo);
		request.setAttribute("oldCardBalance", oldCardBalance);
		request.setAttribute("oldCardName", oldCardName);
		request.setAttribute("oldCardPwd", oldCardPwd);
		return (mapping.findForward("success"));
	}
}

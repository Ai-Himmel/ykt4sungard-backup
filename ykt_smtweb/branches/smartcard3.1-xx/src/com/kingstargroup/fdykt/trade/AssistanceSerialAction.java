package com.kingstargroup.fdykt.trade;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.*;

import java.sql.SQLException;
import java.util.*;

public class AssistanceSerialAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(AssistanceSerialAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doAssistanceSerial(mapping, form, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doAssistanceSerial(ActionMapping mapping, ActionForm form, HttpServletRequest request) {
		DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
		HttpSession session = request.getSession();
		String cardno = (String) session.getAttribute("cardno");
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("logon");
		
		ArrayList ttifsidys = new ArrayList();
		TradeSerialForm tradeSerialForm = (TradeSerialForm) form;
		Integer page = new Integer(1);
		String begin = tradeSerialForm.getBegin();
		String end = tradeSerialForm.getEnd();
		try {
			// tradeserials = tradeserialdao.getTradeSerialByCollDate(stuempno,
			// begin,
			// end, page.intValue(), device, trademsg);
			ttifsidys = tradeserialdao.getAssistanceSerial(Long.parseLong(cardno),"0",page.intValue());
			// Integer all = new Integer(tradeserialdao.getCount(stuempno,
			// begin, end));
			Integer all = new Integer(tradeserialdao.getSidyCountByCardno(cardno,
					begin, end));
			session.setAttribute("ttifsidys", ttifsidys);
			session.setAttribute("begin", begin);
			session.setAttribute("end", end);
			session.setAttribute("page", page);
			session.setAttribute("all", all);
			return (mapping.findForward("success"));
		} catch (Exception e) {
			logger.error(e.getMessage());
			return (mapping.findForward("failure"));
		}
	}
}

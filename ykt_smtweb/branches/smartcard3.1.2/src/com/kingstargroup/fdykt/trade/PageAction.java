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

public class PageAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(PageAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPageAction(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("查询流水失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPageAction(ActionMapping mapping,
			HttpServletRequest request) {
		DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
		HttpSession session = request.getSession();
		String cardno = (String) session.getAttribute("cardno");
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("index");

		ArrayList tradeserials = new ArrayList();
		Integer page = new Integer(request.getParameter("page"));
		String begin = (String) session.getAttribute("begin");
		String end = (String) session.getAttribute("end");
		try {
			tradeserials = tradeserialdao.getTSByCardno(cardno, begin, end,
					(page.intValue() - 1) * 10 + 1 );
			session.setAttribute("tradeserials", tradeserials);
			session.setAttribute("begin", begin);
			session.setAttribute("end", end);
			session.setAttribute("page", page);
			return (mapping.findForward("success"));
		} catch (Exception e) {
			logger.error("分页查询流水失败");
			return (mapping.findForward("failure"));
		}
	}
}

package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.ArrayList;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.DateUtil;

public class TradeSerialAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(TradeSerialAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doTradeSerial(mapping, form, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doTradeSerial(ActionMapping mapping, ActionForm form, HttpServletRequest request) {
		DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
		HttpSession session = request.getSession();
		String cardId = (String) session.getAttribute("cardid");
		if (cardId == null || "".equals(cardId))
			return mapping.findForward("logon");
		
		ArrayList tradeserials = new ArrayList();
		TradeSerialForm tradeSerialForm = (TradeSerialForm) form;
		Integer page = new Integer(1);
		String begin = DateUtil.getBeforeMonth(); 
		String end =  DateUtil.getNowDate2();
		try {
			// tradeserials = tradeserialdao.getTradeSerialByCollDate(stuempno,
			// begin,
			// end, page.intValue(), device, trademsg);
			tradeserials = tradeserialdao.getTSByCardId(cardId, begin, end,
					page.intValue());
			// Integer all = new Integer(tradeserialdao.getCount(stuempno,
			// begin, end));
			Integer all = new Integer(tradeserialdao.getCountByCardId(cardId,
					begin, end));
			session.setAttribute("tradeserials", tradeserials);
			session.setAttribute("begin", begin);
			session.setAttribute("end", end);
			session.setAttribute("page", page);
			session.setAttribute("all", all);
			session.setAttribute("cardId",cardId);
			return (mapping.findForward("success"));
		} catch (Exception e) {
			logger.error(e.getMessage());
			return (mapping.findForward("failure"));
		}
	}
}

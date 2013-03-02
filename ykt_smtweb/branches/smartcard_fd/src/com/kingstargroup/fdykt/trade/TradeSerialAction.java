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

import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;

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
		DB2CardDAO  carddao = new  DB2CardDAO();
		HttpSession session = request.getSession(true);
		
	    try {
	    String week = request.getParameter("week");
		String 	cardno = request.getParameter("cardno");
	    CardDTO card = carddao.getCardInfoByCardNo(cardno);
		if (card == null){
			return mapping.findForward("msg");
		}
		String cardId = card.getCardId();
		ArrayList tradeserials = new ArrayList();
		TradeSerialForm tradeSerialForm = (TradeSerialForm) form;
		Integer page = new Integer(1);
		String begin = "";
		String end = "";
		
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
			return (mapping.findForward("success"));
		} catch (Exception e) {
			logger.error(e.getMessage());
			return (mapping.findForward("failure"));
		}
	}
}

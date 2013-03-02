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

public class SidyPageAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(SidyPageAction.class);
	
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
		DB2CardDAO carddao = new DB2CardDAO();
		HttpSession session = request.getSession();
		try {
		String cardno = request.getParameter("cardno");
		request.setAttribute("cardno",cardno);
		CardDTO card = carddao.getCardInfoByCardNo(cardno);
		if (card == null) {
			return mapping.findForward("msg");
		}
		String cardId = card.getCardId();

		ArrayList ttifsidys = new ArrayList();
		Integer page = new Integer(request.getParameter("page"));
		String begin = "";//(String) session.getAttribute("begin");
		String end = "";//(String) session.getAttribute("end");
		
			ttifsidys = tradeserialdao.getAssistanceSerial(cardId, begin, end,
					(page.intValue() - 1) * 10 + 1 );
			request.setAttribute("ttifsidys", ttifsidys);
		/*	session.setAttribute("begin", begin);
			session.setAttribute("end", end);*/
			session.setAttribute("page", page);
			return (mapping.findForward("success"));
		} catch (Exception e) {
			logger.error("分页查询流水失败");
			return (mapping.findForward("failure"));
		}
	}
}

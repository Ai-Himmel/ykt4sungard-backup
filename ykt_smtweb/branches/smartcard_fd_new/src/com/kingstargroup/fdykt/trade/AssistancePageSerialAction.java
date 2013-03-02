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

public class AssistancePageSerialAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(AssistancePageSerialAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doAssistanceSerial(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		} 
		return forward;
	}

	private ActionForward doAssistanceSerial(ActionMapping mapping,
			HttpServletRequest request) {
		DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
		HttpSession session = request.getSession();
		String cardId = (String) session.getAttribute("cardId");
		if (cardId == null || "".equals(cardId))
			return mapping.findForward("index");

		ArrayList ttifsidys = new ArrayList();
		Integer page = new Integer(request.getParameter("page"));
	/*	String begin = (String) session.getAttribute("begin");
		String end = (String) session.getAttribute("end");*/
		try {
			ttifsidys = tradeserialdao.getAssistanceSerial(cardId,
					(page.intValue() - 1) * 10 + 1 );
			session.setAttribute("ttifsidys", ttifsidys);
		/*	session.setAttribute("begin", begin);
			session.setAttribute("end", end);*/
			session.setAttribute("page", page);
			return (mapping.findForward("success"));
		} catch (Exception e) {
			logger.error("��ҳ��ѯ��ˮʧ��");
			return (mapping.findForward("failure"));
		}
	}
}

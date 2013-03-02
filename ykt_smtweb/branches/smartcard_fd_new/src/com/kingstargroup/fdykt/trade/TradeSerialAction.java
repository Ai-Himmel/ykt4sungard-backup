package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

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
		DB2CardDAO  carddao = new  DB2CardDAO();
		HttpSession session = request.getSession(true);
		
	    try {
	    int  week = Integer.parseInt(request.getParameter("week").toString());
		String 	cardno = request.getParameter("cardno");
	    CardDTO card = carddao.getCardInfoByCardNo(cardno);
		if (card == null){
			return mapping.findForward("msg");
		}
		String cardId = card.getCardId();
		ArrayList tradeserials = new ArrayList();
		Integer page = new Integer(1);
		String begin = "";
		String end = "";
 		Date[]  benEnd =	getBeginEndDate(week);
 		begin  = DateUtil.formatDateByFormat(benEnd[0],"yyyyMMdd");
 		end = DateUtil.formatDateByFormat(benEnd[1],"yyyyMMdd");
 		tradeserials = tradeserialdao.getTSByCardId(cardId, begin, end,
					page.intValue());
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
	
	private Date[]  getBeginEndDate(int week){
		String now =	DateUtil.getNow("yyyyMMdd");
		int weeks = DateUtil.getWeek(now);
		Date[] beginEnd = new Date[2];
		Calendar cal = Calendar.getInstance();
		beginEnd = DateUtil.getStartEnd(Integer.parseInt(now.substring(0,4)),weeks);
		 if(week!=0){
			cal.setTime(beginEnd[0]);
			cal.add(Calendar.DAY_OF_MONTH,-7*week);
			beginEnd[0]=cal.getTime();
			cal.setTime(beginEnd[1]);
			cal.add(Calendar.DAY_OF_MONTH,-7*week);
			beginEnd[1]=cal.getTime();
		 }
		return beginEnd;
	}
}

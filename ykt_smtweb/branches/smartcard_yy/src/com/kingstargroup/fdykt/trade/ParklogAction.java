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

public class ParklogAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ParklogAction.class);

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
		DB2ParklogDAO db2parklogdao = new DB2ParklogDAO();
		HttpSession session = request.getSession();
		String cardId = (String) session.getAttribute("cardid");
		if (cardId == null || "".equals(cardId))
			return mapping.findForward("logon");
		
		ArrayList parklogs = new ArrayList();
		ParklogForm parklogForm = (ParklogForm) form;
		Integer page = new Integer(1);
		String begin = parklogForm.getBegin();
		begin = begin.substring(0,4)+"-"+begin.substring(4,6)+"-"+begin.substring(6,8)+" "+"00:00:00";
		String end = parklogForm.getEnd();
		end= end.substring(0,4)+"-"+end.substring(4,6)+"-"+end.substring(6,8)+" "+"23:59:59";
		try {

			parklogs = db2parklogdao.getPLByCardId(cardId, begin, end,
					page.intValue());
			Integer all = new Integer(db2parklogdao.getCountByCardId(cardId,
					begin, end));
			session.setAttribute("parklogs", parklogs);
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

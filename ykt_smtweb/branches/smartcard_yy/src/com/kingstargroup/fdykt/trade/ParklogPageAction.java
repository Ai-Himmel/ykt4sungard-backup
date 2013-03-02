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

public class ParklogPageAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(ParklogPageAction.class);
	
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
		DB2ParklogDAO db2parklogdao = new DB2ParklogDAO();
		HttpSession session = request.getSession();
		String cardId = (String) session.getAttribute("cardid");
		if (cardId == null || "".equals(cardId))
			return mapping.findForward("logon");
		
		ArrayList parklogs = new ArrayList();
		Integer page = new Integer(request.getParameter("page"));
		String begin = (String) session.getAttribute("begin");
		String end = (String) session.getAttribute("end");
		try {
			parklogs = db2parklogdao.getPLByCardId(cardId, begin, end,
					(page.intValue() - 1) * 10 + 1 );
			session.setAttribute("parklogs", parklogs);
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

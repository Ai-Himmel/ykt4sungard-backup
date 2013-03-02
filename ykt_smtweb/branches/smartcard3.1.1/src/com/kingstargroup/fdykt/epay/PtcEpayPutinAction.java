package com.kingstargroup.fdykt.epay;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;


public class PtcEpayPutinAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(PtcEpayTransAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = checklogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward checklogin(ActionMapping mapping, HttpServletRequest request) {
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");	
		String netbalance = request.getParameter("netbalance");
		if (cardphyid == null || "".equals(cardphyid)){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return mapping.findForward("logon");	
		}			
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("netbalance", netbalance);
		
		return (mapping.findForward("success"));
	}
}



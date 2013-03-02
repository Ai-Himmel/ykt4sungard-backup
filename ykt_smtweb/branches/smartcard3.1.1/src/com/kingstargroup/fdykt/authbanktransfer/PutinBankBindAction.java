package com.kingstargroup.fdykt.authbanktransfer;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.DateUtil;

public class PutinBankBindAction extends Action {
	/**
	 * Logger for this class
	 */
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(PutinBankBindAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");	
		String stuempno = (String)session.getAttribute("stuempno");	
		if (cardphyid == null || "".equals(cardphyid)){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return mapping.findForward("logon");	
		}	
		
		request.setAttribute("stuempno", stuempno);
		
		return (mapping.findForward("success"));
	}
}


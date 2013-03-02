package com.kingstargroup.fdykt.water999;

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

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class WaterBusinessAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(WaterBusinessAction.class);

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
		String tradecode = request.getParameter("tradecode");
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");				
		if (cardphyid == null || "".equals(cardphyid)){
			session.setAttribute("REQ_URL", request.getRequestURL()+"?tradecode="+tradecode);
			return mapping.findForward("logon");	
		}			
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("tradecode", tradecode);
		return (mapping.findForward("success"));
	}
}

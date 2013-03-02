package com.kingstargroup.fdykt.trade;

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

public class ElecSearchAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(ElecSearchAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionForward logonForward = mapping.findForward("logon");
		if (session.getAttribute("cardid") == null){
			return logonForward;
		}
		
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
		String cardno = (String) session.getAttribute("cardno");				
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("logon");		
		request.setAttribute("cardno", cardno);
		return (mapping.findForward("success"));
	}
}

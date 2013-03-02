package com.kingstargroup.fdykt.transfer;

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

public class TransferPassWrodAction extends Action{
	
	private static final Logger logger = Logger.getLogger(TransferPassWrodAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = password(mapping, form, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	
	public ActionForward password(ActionMapping mapping, ActionForm form,
			HttpServletRequest request) {
		
		
		try {
			saveToken(request);
			HttpSession session = request.getSession(true);
			String money = request.getParameter("money").toString();
		
			session.setAttribute("money",money);
		
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("index");
		}
		return mapping.findForward("success");
	}

}

package com.kingstargroup.advquery.user.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.hibernate.util.UserUtil;

public class QueryUserAction extends Action {
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		
		HttpSession session = req.getSession();
		
		String  opeId = req.getParameter("opeId")==null?"":req.getParameter("opeId").trim();
		String  opename = req.getParameter("opename")==null?"":req.getParameter("opename").trim();
		List result = UserUtil.getUsers(opeId,opename);
		session.setAttribute("opeId", opeId);
		session.setAttribute("opename", opename);
		req.setAttribute("result", result);
		req.setAttribute("specStatTip", "²éÑ¯½á¹û");
		return  mapping.findForward("adminresult");
	}
}

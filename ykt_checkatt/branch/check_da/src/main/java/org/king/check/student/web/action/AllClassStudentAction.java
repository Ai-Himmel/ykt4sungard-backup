package org.king.check.student.web.action;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.service.CheckReportService;
import org.king.framework.web.action.BaseAction;

//取得应到学生名单
public class AllClassStudentAction extends BaseAction {
	
	private  CheckReportService  reportService;

	public void setReportService(CheckReportService reportService) {
		this.reportService = reportService;
	}
	
	public ActionForward getAllClassStudent(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)	
	throws Exception {   
		String planId = request.getParameter("planId");
        String classno = request.getParameter("classno");
		List  list  = new ArrayList();
		list = reportService.getAllStudentByPlan(planId,classno);
		request.setAttribute("list", list);
		return mapping.findForward("allClassStudent"); 
		
	}
}

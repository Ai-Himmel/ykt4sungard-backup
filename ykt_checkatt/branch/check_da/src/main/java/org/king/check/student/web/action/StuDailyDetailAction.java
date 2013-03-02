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

public class StuDailyDetailAction extends BaseAction {
	
	private  CheckReportService  reportService;
	
	public void setReportService(CheckReportService reportService) {
		this.reportService = reportService;
	}

	public ActionForward getStudentShoud(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception{
		String courseid = request.getParameter("courseid");
		String classid = request.getParameter("classid");
		String begindate = request.getParameter("begindate");
		String enddate =request.getParameter("enddate");
		String stuempno= request.getParameter("stuempno");
		List list = reportService.getDailyStudentShould(courseid, classid, begindate, enddate, stuempno);
		request.setAttribute("list", list);
		return mapping.findForward("studentshoud");
	}
	
	public ActionForward getStudentOther(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception{
		String courseid = request.getParameter("courseid");
		String classid = request.getParameter("classid");
		String begindate = request.getParameter("begindate");
		String enddate =request.getParameter("enddate");
		String stuempno= request.getParameter("stuempno");
		String type = request.getParameter("type");
		String typename ="";
		List list = new ArrayList();
		if("real".equals(type)){
			list = reportService.getDailyStudentOther(courseid, classid, begindate, enddate, stuempno, "0", "0");
			typename="学生实到课次";
		}
		if("late".equals(type)){
			list =  reportService.getDailyStudentOther(courseid, classid, begindate, enddate, stuempno, "1", "0");
			typename="学生迟到课次";
		}
		if("leave".equals(type)){
			list = reportService.getDailyStudentOther(courseid, classid, begindate, enddate, stuempno, "0", "1");
			typename="学生早退课次";
		}
		request.setAttribute("typename", typename);
		request.setAttribute("list", list);
		return mapping.findForward("studentdailydetail");
	}
}

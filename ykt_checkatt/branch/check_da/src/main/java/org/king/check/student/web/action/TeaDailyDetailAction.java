package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.service.CheckReportService;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.ArrayList;
import java.util.List;

public class TeaDailyDetailAction extends BaseAction {

    private CheckReportService reportService;

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public ActionForward getTeacherShoud(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String courseid = request.getParameter("courseid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String stuempno = request.getParameter("stuempno");
        List list = new ArrayList();
        list = reportService.getDailyTeacherShould(courseid, begindate, enddate, stuempno);
        request.setAttribute("list", list);
        return mapping.findForward("teachershoud");
    }

    public ActionForward getTeacherOther(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String stuempno = request.getParameter("stuempno");
        String type = request.getParameter("type");
        String typename = "";
        List list = new ArrayList();
        if ("real".equals(type)) {
            list = reportService.getDailyTeacherOther(courseid, begindate, enddate, stuempno, "0", "0");
            typename = "教师实到课次";
        }
        if ("late".equals(type)) {
            list = reportService.getDailyTeacherOther(courseid, begindate, enddate, stuempno, "1", "0");
            typename = "教师迟到课次";
        }
        if ("leave".equals(type)) {
            list = reportService.getDailyTeacherOther(courseid, begindate, enddate, stuempno, "0", "1");
            typename = "教师早退课次";
        }
        request.setAttribute("typename", typename);
        request.setAttribute("list", list);
        return mapping.findForward("teacherdailydetail");
    }
}

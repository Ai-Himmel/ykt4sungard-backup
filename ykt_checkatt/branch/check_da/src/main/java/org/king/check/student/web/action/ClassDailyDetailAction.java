package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.service.CheckReportService;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

public class ClassDailyDetailAction extends BaseAction {

    private CheckReportService reportService;

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public ActionForward getClassShoud(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {

        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");

        List list = new ArrayList();
        list = reportService.getClassShoudStudent(courseid, classid, begindate, enddate);
        request.setAttribute("list", list);
        return mapping.findForward("classshoud");
    }

    public ActionForward getClassOther(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }

        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String type = request.getParameter("type");

        session.setAttribute("courseid", courseid);
        session.setAttribute("classid", classid);
        session.setAttribute("begindate", begindate);
        session.setAttribute("enddate", enddate);
        session.setAttribute("type", type);

        String typename = "";
        String activename = "";
        String noactivename = "";
        List list = new ArrayList();
        List activeList = new ArrayList();
        List noactiveList = new ArrayList();
        if ("real".equals(type)) {
            list = reportService.getClassStudentOther(courseid, classid, begindate, enddate, "0", "0");
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "0", "0",null);
            noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "0", "0",null);
            typename = "学生实到课次";
            activename = "非本班学生确认";
            noactivename = "非本班学生未确认";
        } else if ("late".equals(type)) {
            list = reportService.getClassStudentOther(courseid, classid, begindate, enddate, "1", "0");
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "1", "0",null);
            noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "1", "0",null);
            typename = "学生迟到课次";
            activename = "非本班学生确认";
            noactivename = "非本班学生未确认";

        } else if ("leave".equals(type)) {
            list = reportService.getClassStudentOther(courseid, classid, begindate, enddate, "0", "1");
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "0", "1",null);
            noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "0", "1",null);
        } else if ("nocome".equals(type)) {
            list = reportService.getClassStudentNocome(courseid, classid, begindate, enddate);
            request.setAttribute("list", list);
            return mapping.findForward("nocome");
        }

        request.setAttribute("typename", typename);
        request.setAttribute("activename", activename);
        request.setAttribute("noactivename", noactivename);
        request.setAttribute("list", list);
        request.setAttribute("activeList", activeList);
        request.setAttribute("noactiveList", noactiveList);
        return mapping.findForward("classdailydetail");
    }

    public ActionForward updateUnplanStudent(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String type = request.getParameter("type");

        String student = request.getParameter("student");
        String cmd = request.getParameter("cmd");
        reportService.updateUnplanStudent(student, cmd);

        List activeList = new ArrayList();
        List noactiveList = new ArrayList();
        String result = null;
        String typename = "";
        if("real".equals(type) && "confirm".equals(cmd)){
			noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "0", "0",null);
            result = "invalid";
            typename = "实到";
        } else if ("real".equals(type) && "cancel".equals(cmd)){
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "0", "0",null);
            result = "valid";
            typename = "实到";
        } else if ("late".equals(type) && "confirm".equals(cmd)){
			noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "1", "0",null);
            result = "invalid";
            typename = "迟到";
        } else if ("late".equals(type) && "cancel".equals(cmd)){
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "1", "0",null);
            result = "valid";
            typename = "迟到";
        } else if ("leave".equals(type) && "confirm".equals(cmd)){
			noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "0", "1",null);
            result = "invalid";
            typename = "早退";
        } else if ("leave".equals(type) && "cancel".equals(cmd)){
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "0", "1",null);
            result = "valid";
            typename = "早退";
        }
        request.setAttribute("noactiveList", noactiveList);
        request.setAttribute("activeList", activeList);

        request.setAttribute("courseid", courseid);
        request.setAttribute("classid", classid);
        request.setAttribute("begindate", begindate);
        request.setAttribute("enddate", enddate);
        request.setAttribute("type", type);
        request.setAttribute("typename", typename);

        return mapping.findForward(result);
    }

    public ActionForward getPlannedCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String type = request.getParameter("type");

        String typename = "";
        List list = new ArrayList();
        if ("real".equals(type)) {
            list = reportService.getClassStudentOther(courseid, classid, begindate, enddate, "0", "0");
            typename = "实到";
        } else if ("late".equals(type)) {
            list = reportService.getClassStudentOther(courseid, classid, begindate, enddate, "1", "0");
            typename = "迟到";
        } else if ("leave".equals(type)) {
            list = reportService.getClassStudentOther(courseid, classid, begindate, enddate, "0", "1");
            typename = "早退";
        }

        request.setAttribute("courseid", courseid);
        request.setAttribute("classid", classid);
        request.setAttribute("begindate", begindate);
        request.setAttribute("enddate", enddate);
        request.setAttribute("type", type);
        request.setAttribute("typename", typename);
        request.setAttribute("list", list);
        return mapping.findForward("planned");
    }

    public ActionForward getValidCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String type = request.getParameter("type");

        String typename = "";
        List activeList = new ArrayList();
        if ("real".equals(type)) {
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "0", "0",null);
            typename = "实到";
        } else if ("late".equals(type)) {
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "1", "0",null);
            typename = "迟到";
        } else if ("leave".equals(type)) {
            activeList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "1", "0", "1",null);
            typename = "早退";
        }

        request.setAttribute("courseid", courseid);
        request.setAttribute("classid", classid);
        request.setAttribute("begindate", begindate);
        request.setAttribute("enddate", enddate);
        request.setAttribute("type", type);
        request.setAttribute("typename", typename);
        request.setAttribute("activeList", activeList);
        return mapping.findForward("valid");
    }

    public ActionForward getInvalidCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String courseid = request.getParameter("courseid");
        String classid = request.getParameter("classid");
        String begindate = request.getParameter("begindate");
        String enddate = request.getParameter("enddate");
        String type = request.getParameter("type");

        String typename = "";
        List noactiveList = new ArrayList();
        if ("real".equals(type)) {
            noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "0", "0",null);
            typename = "实到";
        } else if ("late".equals(type)) {
            noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "1", "0",null);
            typename = "迟到";

        } else if ("leave".equals(type)) {
            noactiveList = reportService.getUnplanStudent(courseid, classid, begindate, enddate, "0", "0", "1",null);
            typename = "早退";
        }

        request.setAttribute("courseid", courseid);
        request.setAttribute("classid", classid);
        request.setAttribute("begindate", begindate);
        request.setAttribute("enddate", enddate);
        request.setAttribute("type", type);
        request.setAttribute("typename", typename);

        request.setAttribute("noactiveList", noactiveList);
        return mapping.findForward("invalid");
    }
}

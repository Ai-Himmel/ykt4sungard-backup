package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.*;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.security.service.AccountService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

public class TeacherTermCheckReportAction extends BaseAction {
    private DepartmentService departmentService;

    private CourseService courseService;

    private CheckReportService reportService;

    private TermService termService;

    private AreaService areaService;

    private AccountService accountService;

    public void setAreaService(AreaService areaService) {
        this.areaService = areaService;
    }

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public void setCourseService(CourseService courseService) {
        this.courseService = courseService;
    }

    public void setTermService(TermService termService) {
        this.termService = termService;
    }

    public void setAccountService(AccountService accountService) {
        this.accountService = accountService;
    }

    public ActionForward teacherTermReportInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        List courseList = departmentService.findCourse("", "", "", account);
        List term = termService.findAllTerm();

        request.setAttribute("course", courseList);
        request.setAttribute("term", term);
        return mapping.findForward("list");
    }

    public ActionForward teacherTermReport(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        String personCode = request.getSession().getAttribute("personCode").toString();
        DynaActionForm dform = (DynaActionForm) form;
        if (accountService.isTeacher(account)) {
            dform.set("stuempNo", personCode);
        }

        List teacherTermCheckList = reportService.getTeacherTermCheckRpt(dform);

        List courseList = departmentService.findCourse("", "", "", account);
        List term = termService.findAllTerm();

        request.setAttribute("course", courseList);
        request.setAttribute("term", term);

        request.setAttribute("teacherTermCheckList", teacherTermCheckList);
        request.setAttribute("termId", dform.get("termId"));

        return mapping.findForward("list");
    }

    public ActionForward getTeacherShould(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String termId = request.getParameter("termId");
        String courseId = request.getParameter("courseId");
        String stuempNo = request.getParameter("stuempNo");
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = request.getParameter("type");
        String typename = "";
        if ("should".equals(type)) {
            typename = "教师应到课次";
        } else if ("nocome".equals(type)) {
            checkNum = Integer.valueOf(0);
            typename = "教师缺勤课次";
        }
        List result = reportService.getTeacherCheckDetail(termId, courseId, stuempNo, courseNum, checkNum, comeLateNum, leaveEarlyNum);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);

        return mapping.findForward("should");
    }

    public ActionForward getTeacherOther(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String termId = request.getParameter("termId");
        String courseId = request.getParameter("courseId");
        String stuempNo = request.getParameter("stuempNo");
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = request.getParameter("type");
        String typename = "";
        if ("real".equals(type)) {
            checkNum = Integer.valueOf(1);
            typename = "教师实到课次";
        } else if ("late".equals(type)) {
            comeLateNum = Integer.valueOf(1);
            typename = "教师迟到课次";
        } else if ("leave".equals(type)) {
            leaveEarlyNum = Integer.valueOf(1);
            typename = "教师早退课次";
        }
        List result = reportService.getTeacherCheckDetail(termId, courseId, stuempNo, courseNum, checkNum, comeLateNum, leaveEarlyNum);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);
        return mapping.findForward("other");
    }
}

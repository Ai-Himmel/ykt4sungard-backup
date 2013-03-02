package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.CheckReportService;
import org.king.check.service.DepartmentService;
import org.king.check.service.TermService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

public class ClassTermCheckReportAction extends BaseAction {
    private DepartmentService departmentService;

    private CheckReportService reportService;

    private TermService termService;

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public void setTermService(TermService termService) {
        this.termService = termService;
    }

    public ActionForward classTermReportInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");

        List term = termService.findAllTerm();
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse("", "", "",account);

        request.setAttribute("term", term);
        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        return mapping.findForward("list");
    }

    public ActionForward classTermReport(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        DynaActionForm dform = (DynaActionForm) form;
        dform.set("custid", account.getCustId());
        String areaCode = dform.getString("schoolarea");
        String pid = dform.getString("pid");
        String classno = dform.getString("classno");

        List classTermCheckList = reportService.getClassTermCheckRpt(dform);

        List term = termService.findAllTerm();
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse(areaCode, pid, classno, account);
        if (StringUtils.isNotBlank(pid)) {
            areaList = departmentService.findAreaFromDepartment(pid);
        }
        if (StringUtils.isNotBlank(areaCode)) {
            deptList = departmentService.findDepartment(areaCode, pid, account);
        }

        request.setAttribute("term", term);
        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        request.setAttribute("classTermCheckList", classTermCheckList);
        request.setAttribute("termId", dform.get("termId"));

        return mapping.findForward("list");
    }

    public ActionForward getClassShould(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String termId = dform.get("termId").toString();
        String classId = dform.get("classno").toString();
        String courseId = dform.get("courseId").toString();
        String stuempNo = dform.get("stuempNo").toString();
        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = dform.get("type").toString();
        String typename = "";
        if ("should".equals(type)) {
            typename = "学生应到课次";
        } else if ("nocome".equals(type)) {
            checkNum = Integer.valueOf(0);
            typename = "学生缺勤课次";
        }
        List result = reportService.getClassCheckDetail(termId, classId, courseId, stuempNo, courseNum, checkNum, comeLateNum, leaveEarlyNum, beginDate, endDate);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);

        return mapping.findForward("should");
    }

    public ActionForward getClassOther(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String termId = dform.get("termId").toString();
        String classId = dform.get("classno").toString();
        String courseId = dform.get("courseId").toString();
        String stuempNo = dform.get("stuempNo").toString();
        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = dform.get("type").toString();
        String typename = "";
        if ("real".equals(type)) {
            checkNum = Integer.valueOf(1);
            typename = "学生实到课次";
        } else if ("late".equals(type)) {
            comeLateNum = Integer.valueOf(1);
            typename = "学生迟到课次";
        } else if ("leave".equals(type)) {
            leaveEarlyNum = Integer.valueOf(1);
            typename = "学生早退课次";
        }
        List result = reportService.getClassCheckDetail(termId, classId, courseId, stuempNo, courseNum, checkNum, comeLateNum, leaveEarlyNum, beginDate, endDate);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);
        return mapping.findForward("other");
    }

    public ActionForward getPlannedCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String termId = dform.get("termId").toString();
        String classId = dform.get("classno").toString();
        String courseId = dform.get("courseId").toString();
        String stuempNo = dform.get("stuempNo").toString();
        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = dform.get("type").toString();
        String typename = "";
        if ("real".equals(type)) {
            checkNum = Integer.valueOf(1);
            typename = "实到";
        } else if ("late".equals(type)) {
            comeLateNum = Integer.valueOf(1);
            typename = "迟到";
        } else if ("leave".equals(type)) {
            leaveEarlyNum = Integer.valueOf(1);
            typename = "早退";
        }
        List result = reportService.getClassCheckDetail(termId, classId, courseId, stuempNo, courseNum, checkNum, comeLateNum, leaveEarlyNum, beginDate, endDate);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);
        return mapping.findForward("planned");
    }

    public ActionForward getValidCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String classId = dform.get("classno").toString();
        String courseId = dform.get("courseId").toString();
        String stuempNo = dform.get("stuempNo").toString();
        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();
        String type = dform.get("type").toString();

        String typename = "";
        List activeList = new ArrayList();
        if ("real".equals(type)) {
            activeList = reportService.getUnplanStudent(courseId, classId, beginDate, endDate, "1", "0", "0", stuempNo);
            typename = "实到";
        } else if ("late".equals(type)) {
            activeList = reportService.getUnplanStudent(courseId, classId, beginDate, endDate, "1", "1", "0", stuempNo);
            typename = "迟到";
        } else if ("leave".equals(type)) {
            activeList = reportService.getUnplanStudent(courseId, classId, beginDate, endDate, "1", "0", "1", stuempNo);
            typename = "早退";
        }

        request.setAttribute("typename", typename);
        request.setAttribute("activeList", activeList);
        return mapping.findForward("valid");
    }

    public ActionForward getInvalidCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String classId = dform.get("classno").toString();
        String courseId = dform.get("courseId").toString();
        String stuempNo = dform.get("stuempNo").toString();
        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();
        String type = dform.get("type").toString();

        String typename = "";
        List noactiveList = new ArrayList();
        if ("real".equals(type)) {
            noactiveList = reportService.getUnplanStudent(courseId, classId, beginDate, endDate, "0", "0", "0", stuempNo);
            typename = "实到";
        } else if ("late".equals(type)) {
            noactiveList = reportService.getUnplanStudent(courseId, classId, beginDate, endDate, "0", "1", "0", stuempNo);
            typename = "迟到";

        } else if ("leave".equals(type)) {
            noactiveList = reportService.getUnplanStudent(courseId, classId, beginDate, endDate, "0", "0", "1", stuempNo);
            typename = "早退";
        }

        request.setAttribute("typename", typename);
        request.setAttribute("noactiveList", noactiveList);
        return mapping.findForward("invalid");
    }
}

package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.service.CheckReportService;
import org.king.check.service.DepartmentService;
import org.king.check.service.TermService;
import org.king.check.util.PageLimitUtil;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

public class StudentTermCheckReportAction extends BaseAction {
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

    public ActionForward studentTermReportInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");

        List term = termService.findAllTerm();
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse("", "", "", account);

        request.setAttribute("term", term);
        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);
        request.setAttribute("totalRows", 0);

        return mapping.findForward("list");
    }

    public ActionForward studentTermReport(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        DynaActionForm dform = (DynaActionForm) form;
        dform.set("custid", account.getCustId());
        String areaCode = dform.getString("schoolarea");
        String pid = dform.getString("pid");
        String classno = dform.getString("classno");

        DBPageLimit page = new DBPageLimit();
        PageLimitUtil.pageInfoPopulate("ec", request, page);

        reportService.getStudentTermCheckRpt(dform, page);
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

        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);
        request.setAttribute("term", term);
        request.setAttribute("studentTermCheckList", page.getResult());
        request.setAttribute("termId", dform.get("termId"));
        request.setAttribute("totalRows", page.getTotalRows());
        return mapping.findForward("list");
    }

    public ActionForward getStudentShould(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String termId = request.getParameter("termId");
        String classId = request.getParameter("classId");
        String courseId = request.getParameter("courseId");
        String stuempNo = request.getParameter("stuempNo");
        Integer custType = Integer.valueOf(0);
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = request.getParameter("type");
        String typename = "";
        if ("should".equals(type)) {
            typename = "学生应到课次";
        } else if ("nocome".equals(type)) {
            checkNum = Integer.valueOf(0);
            typename = "学生缺勤课次";
        }
        List result = reportService.getCheckDetail(termId, classId, courseId, stuempNo, custType, courseNum, checkNum, comeLateNum, leaveEarlyNum);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);

        return mapping.findForward("should");
    }

    public ActionForward getStudentOther(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String termId = request.getParameter("termId");
        String classId = request.getParameter("classId");
        String courseId = request.getParameter("courseId");
        String stuempNo = request.getParameter("stuempNo");
        Integer custType = Integer.valueOf(0);
        Integer courseNum = Integer.valueOf(1);
        Integer checkNum = null;
        Integer comeLateNum = null;
        Integer leaveEarlyNum = null;
        String type = request.getParameter("type");
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
        List result = reportService.getCheckDetail(termId, classId, courseId, stuempNo, custType, courseNum, checkNum, comeLateNum, leaveEarlyNum);
        request.setAttribute("typename", typename);
        request.setAttribute("list", result);
        return mapping.findForward("other");
    }
}

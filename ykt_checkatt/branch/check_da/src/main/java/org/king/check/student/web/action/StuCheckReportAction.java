package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.CheckReportService;
import org.king.check.service.DepartmentService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

public class StuCheckReportAction extends BaseAction {

    private DepartmentService departmentService;

    private CheckReportService reportService;

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward dailyreport_init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");

        String endDate = DateUtilExtend.getYesterday();//昨天
        String beginDate = DateUtilExtend.getYesterday();//昨天

        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse("", "", "",account);

        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        request.getSession().setAttribute("endDate", endDate);
        request.getSession().setAttribute("beginDate", beginDate);
        return mapping.findForward("list");
    }

    public ActionForward dailyreport(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");

        DynaActionForm dform = (DynaActionForm) form;
        dform.set("custid", account.getCustId());

        String areaCode = dform.getString("schoolarea");
        String pid = dform.getString("pid");
        String classno = dform.getString("classno");

        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse(areaCode, pid, classno,account);
        if (StringUtils.isNotBlank(pid)) {
            areaList = departmentService.findAreaFromDepartment(pid);
        }
        if (StringUtils.isNotBlank(areaCode)) {
            deptList = departmentService.findDepartment(areaCode, pid,account);
        }

        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();

        long diffdate = DateUtilExtend.diffDate(beginDate, endDate);

        if (diffdate > 70) {
            request.setAttribute("msg", "查询范围不能超过10周");
            return mapping.findForward("list");
        }

        List stucheckList = reportService.getStuCheckRpt(dform);

        request.setAttribute("stucheckList", stucheckList);
        request.setAttribute("endDate", endDate);
        request.setAttribute("beginDate", beginDate);

        return mapping.findForward("list");
    }
}

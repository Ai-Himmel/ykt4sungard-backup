package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.*;
import org.king.check.service.CheckReportService;
import org.king.check.service.CourseService;
import org.king.check.service.DepartmentService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

public class StuTodayCheckSearchAction extends BaseAction {

    private static final Log log = LogFactory.getLog(StuTodayCheckSearchAction.class);

    private DepartmentService departmentService;

    private CheckReportService reportService;

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public ActionForward init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse("", "", "", account);

        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        return mapping.findForward("list");
    }


    public ActionForward list(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        DynaActionForm dform = (DynaActionForm) form;
        String areaCode = dform.getString("schoolarea");
        String pid = dform.getString("pid");
        String classno = dform.getString("classno");

        ActionMessages messages = new ActionMessages();

        List list = new ArrayList();
        List areaList = new ArrayList();
        List facultyList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = new ArrayList();

        dform.set("custid", account.getCustId());

        try {
            facultyList = departmentService.findFaculty();
            courseList = departmentService.findCourse(areaCode, pid, classno, account);

            if (StringUtils.isNotBlank(pid)) {
                areaList = departmentService.findAreaFromDepartment(pid);
            }
            if (StringUtils.isNotBlank(areaCode)) {
                deptList = departmentService.findDepartment(areaCode, pid, account);
            }
            list = reportService.getTodayStuCheckList(dform);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("查询出现异常"));
        }
        saveMessages(request, messages);
        request.setAttribute("todayStuCheckList", list);
        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        return mapping.findForward("list");
    }

    public ActionForward allClassStudent(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        ActionMessages messages = new ActionMessages();
        String planId = request.getParameter("planId");
        String classno = request.getParameter("classno");

        List list = new ArrayList();
        try {
            list = reportService.getAllStudentByPlan(planId, classno);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("获取明细信息失败"));
        }
        saveMessages(request, messages);
        request.setAttribute("list", list);
        return mapping.findForward("allClassStudent");
    }

    public ActionForward realStudent(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        ActionMessages messages = new ActionMessages();
        String planId = request.getParameter("planId");
        String classno = request.getParameter("classno");

        List list = new ArrayList();
        try {
            list = reportService.getRealStudentByPlan(planId, classno);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("获取明细信息失败"));
        }
        saveMessages(request, messages);
        request.setAttribute("list", list);
        return mapping.findForward("realStudent");
    }

    public ActionForward nocomeStudent(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        ActionMessages messages = new ActionMessages();
        String planId = request.getParameter("planId");
        String classno = request.getParameter("classno");

        List list = new ArrayList();
        try {
            list = reportService.getNotComeStudentByPlan(planId, classno);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("获取明细信息失败"));
        }
        saveMessages(request, messages);
        request.setAttribute("list", list);
        return mapping.findForward("nocomestudent");
    }
}

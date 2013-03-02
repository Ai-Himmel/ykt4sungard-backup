package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.AreaService;
import org.king.check.service.CheckReportService;
import org.king.check.service.DepartmentService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.security.service.AccountService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.List;

public class TeaCheckReportAction extends BaseAction {

    private AreaService areaService;

    private CheckReportService reportService;

    private AccountService accountService;

    private DepartmentService departmentService;

    public void setAccountService(AccountService accountService) {
        this.accountService = accountService;
    }

    public void setAreaService(AreaService areaService) {
        this.areaService = areaService;
    }

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward dailyreport_init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        List areaList = areaService.findArea();
        List courseList = departmentService.findCourse("", "", "", account);

        String endDate = DateUtilExtend.getYesterday();//昨天
        String beginDate = DateUtilExtend.getYesterday();//昨天

        request.getSession().setAttribute("endDate", endDate);
        request.getSession().setAttribute("beginDate", beginDate);
        request.getSession().setAttribute("areaList", areaList);
        request.setAttribute("course", courseList);
        return mapping.findForward("list");
    }

    public ActionForward dailyreport(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession();
        Account account = (Account) session.getAttribute("accountPerson");
        String personCode = request.getSession().getAttribute("personCode").toString();
        DynaActionForm dform = (DynaActionForm) form;
        if (accountService.isTeacher(account)) {
            dform.set("stuempNo", personCode);
        }

        List courseList = departmentService.findCourse("", "", "", account);
        request.setAttribute("course", courseList);

        String beginDate = dform.get("beginDate").toString();
        String endDate = dform.get("endDate").toString();

        request.setAttribute("endDate", endDate);
        request.setAttribute("beginDate", beginDate);

        long diffdate = DateUtilExtend.diffDate(beginDate, endDate);

        if (diffdate > 70) {
            request.setAttribute("msg", "查询范围不能超过10周");
            return mapping.findForward("list");
        }

        List teacheckList = reportService.getTeaCheckRpt(dform);
        request.setAttribute("teacheckList", teacheckList);

        return mapping.findForward("list");
    }
}

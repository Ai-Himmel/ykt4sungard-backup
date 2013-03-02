package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.CheckReportService;
import org.king.check.service.DepartmentService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.List;

public class RoomTransAction extends BaseAction {

    private CheckReportService reportService;

    private DepartmentService departmentService;


    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward roomTrans_init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List areaList = departmentService.findAreaFromDepartment();
        request.getSession().setAttribute("areaList", areaList);
        return mapping.findForward("list");
    }


    public ActionForward roomTransList(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        List areaList = departmentService.findAreaFromDepartment();

        request.getSession().setAttribute("areaList", areaList);

        List roomTransList = reportService.getTRoomTRans(dform);

        request.setAttribute("roomTransList", roomTransList);

        return mapping.findForward("list");
    }


    public ActionForward roomTrans(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String item = request.getParameter("para");
        String[] serialno = item.split(",");
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        String personName = session.getAttribute("personName").toString();
        String personCode = session.getAttribute("personCode").toString();

        reportService.roomTrans(serialno, personName, personCode);

        List roomTransList = reportService.getTRoomTRans(dform);

        request.setAttribute("roomTransList", roomTransList);

        return mapping.findForward("list");
    }

    public ActionForward transPerson_init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List areaList = departmentService.findAreaFromDepartment();
        String endDate = DateUtilExtend.getNowDate2();//当前时间
        String beginDate = DateUtilExtend.getNowDate2();//当前时间
        request.getSession().setAttribute("areaList", areaList);
        request.getSession().setAttribute("endDate", endDate);
        request.getSession().setAttribute("beginDate", beginDate);

        return mapping.findForward("transperson");
    }

    public ActionForward transPersonList(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        List list = reportService.getTransPerson(dform);

        request.setAttribute("transpersonList", list);
        return mapping.findForward("transperson");
    }
}

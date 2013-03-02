package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.CheckReportService;
import org.king.check.service.DepartmentService;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

public class RoomElecAction extends BaseAction {

    private CheckReportService reportService;

    private DepartmentService departmentService;

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List areaList = departmentService.findAreaFromDepartment();
        request.getSession().setAttribute("areaList", areaList);
        return mapping.findForward("roomElec");
    }

    public ActionForward getRoomElec(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        List list = reportService.getRoomState(dform);
        request.setAttribute("roomElecList", list);
        return mapping.findForward("roomElec");
    }
}

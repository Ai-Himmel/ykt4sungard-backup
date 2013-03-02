package org.king.check.student.web.action;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.*;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.service.*;
import org.king.check.util.PageLimitUtil;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-26
 */
public class DeviceCheckAction extends BaseAction {

    private static final Log log = LogFactory.getLog(StuTodayCheckSearchAction.class);

    private RoomService roomService;

    private DepartmentService departmentService;

    private CourseService courseService;

    private CheckReportService reportService;

    private AreaService areaService;


    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public void setCourseService(CourseService courseService) {
        this.courseService = courseService;
    }

    public void setReportService(CheckReportService reportService) {
        this.reportService = reportService;
    }

    public void setAreaService(AreaService areaService) {
        this.areaService = areaService;
    }

    public void setRoomService(RoomService roomService) {
        this.roomService = roomService;
    }

    public ActionForward list(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        ActionMessages messages = new ActionMessages();

        List deviceList = new ArrayList();
        List deviceCheckList = new ArrayList();
        try {
            deviceList = reportService.findDeviceUnplanned();
            deviceCheckList = reportService.findDeviceCheckList(dform);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("查询出现异常"));
        }
        saveMessages(request, messages);

        request.setAttribute("deviceList", deviceList);
        request.setAttribute("deviceCheckList", deviceCheckList);
        return mapping.findForward("list");
    }

    public ActionForward viewCheckDetail(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        ActionMessages messages = new ActionMessages();
        DBPageLimit page = new DBPageLimit();

        try {
            PageLimitUtil.pageInfoPopulate("ec", request, page);
            reportService.findCheckDetail(dform, page);
        } catch (Exception e) {
            e.printStackTrace();
            messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("查询出现异常"));
        }
        saveMessages(request, messages);

        request.setAttribute("checkDetailList", page.getResult());
        request.setAttribute("totalRows", page.getTotalRows());

        return mapping.findForward("detail");
    }

}


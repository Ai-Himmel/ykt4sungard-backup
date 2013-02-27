package org.king.template.web.action;

import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.king.template.domain.MonitorTimePeriods;
import org.king.template.exception.TemplateAlreadyExistException;
import org.king.template.service.TemplateService;
import org.king.template.util.TimePeriodsUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-7
 */
public class TimePeriodsAction extends BaseAction {
    private TemplateService templateService;

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public ActionForward inputMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTimePeriods monitorTimePeriods = new MonitorTimePeriods();
        List timerangers = TimePeriodsUtil.initTimerangerVO(monitorTimePeriods);

        ((DynaActionForm) form).set("monitorTimePeriods", monitorTimePeriods);
        ((DynaActionForm) form).set("timerangers", timerangers);

        ((DynaActionForm) form).set("type", "add");
        return mapping.findForward("input");
    }

    /**
     * 增加时间域模板
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorTimePeriods monitorTimePeriods = (MonitorTimePeriods) ((DynaActionForm) form).get("monitorTimePeriods");
            List timerangers = (List) ((DynaActionForm) form).get("timerangers");
            //关联timeranger对象
            monitorTimePeriods.setTimerangers(TimePeriodsUtil.convertTimeranger(timerangers, monitorTimePeriods, true));

            templateService.saveMonitorTimePeriods(monitorTimePeriods);
        } catch (TemplateAlreadyExistException e) {
            errors.add("addMonitorTimePeriods", new ActionMessage("errors.TemplateExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorTimePeriods monitorTimePeriods = (MonitorTimePeriods) ((DynaActionForm) form).get("monitorTimePeriods");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        templateService.findMonitorTimePeriodsByPage(page, monitorTimePeriods);

        request.setAttribute("timePeriodsList", page);
        ((DynaActionForm) form).set("monitorTimePeriods", monitorTimePeriods);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String periodId = request.getParameter("periodId");
        MonitorTimePeriods monitorTimePeriods = templateService.findMonitorTimePeriodsById(Integer.valueOf(periodId));
        List timerangers = TimePeriodsUtil.convertTimerangerVO(monitorTimePeriods.getTimerangers());

        ((DynaActionForm) form).set("monitorTimePeriods", monitorTimePeriods);
        ((DynaActionForm) form).set("timerangers", timerangers);
        ((DynaActionForm) form).set("type", "edit");

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String periodId = request.getParameter("periodId");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            templateService.deleteMonitorTimePeriods(Integer.valueOf(periodId));
            writer.write("删除时间域成功！");
        } catch (BusinessException e) {
            writer.write("error:删除失败，该时间域可能被主机模板、服务模板、设备模板、主机或者服务关联，请检查！");
        }
        return null;
    }

    public ActionForward updateMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTimePeriods monitorTimePeriods = (MonitorTimePeriods) ((DynaActionForm) form).get("monitorTimePeriods");
        List timerangers = (List) ((DynaActionForm) form).get("timerangers");
        //关联timeranger对象
        monitorTimePeriods.setTimerangers(TimePeriodsUtil.convertTimeranger(timerangers, monitorTimePeriods, false));
        templateService.updateMonitorTimePeriods(monitorTimePeriods);

        return mapping.findForward("success");
    }

    public ActionForward viewMonitorTimePeriods(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String periodId = request.getParameter("periodId");
        MonitorTimePeriods monitorTimePeriods = templateService.findMonitorTimePeriodsById(Integer.valueOf(periodId));
        List timerangers = TimePeriodsUtil.convertTimerangerVO(monitorTimePeriods.getTimerangers());

        ((DynaActionForm) form).set("monitorTimePeriods", monitorTimePeriods);
        ((DynaActionForm) form).set("timerangers", timerangers);
        return mapping.findForward("view");
    }
}

package org.king.termdev.web.action;

import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.support.service.MonitorSupportService;
import org.king.template.service.TemplateService;
import org.king.termdev.domain.MonitorTermdevService;
import org.king.termdev.exception.TermdevServiceAlreadyExistException;
import org.king.termdev.service.TermdevService;
import org.king.utils.DependencyUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public class TermdevServiceAction extends BaseAction {
    private TermdevService termdevService;

    private TemplateService templateService;

    private MonitorSupportService monitorSupportService;

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public ActionForward inputMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTermdevService monitorTermdevService = new MonitorTermdevService();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List termdevServiceCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(4));
        ((DynaActionForm) form).set("monitorTermdevService", monitorTermdevService);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("termdevServiceCommands", termdevServiceCommands);

        return mapping.findForward("input");
    }

    /**
     * 增加设备服务
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorTermdevService monitorTermdevService = (MonitorTermdevService) ((DynaActionForm) form).get("monitorTermdevService");
            DependencyUtil.clearDependencyProperty(monitorTermdevService);
            termdevService.saveMonitorTermdevService(monitorTermdevService);
        } catch (TermdevServiceAlreadyExistException e) {
            errors.add("addMonitorTermdevService", new ActionMessage("errors.TermdevServiceExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorTermdevService monitorTermdevService = (MonitorTermdevService) ((DynaActionForm) form).get("monitorTermdevService");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        termdevService.findMonitorTermdevServiceByPage(page, monitorTermdevService);

        request.setAttribute("termdevServiceList", page);
        ((DynaActionForm) form).set("monitorTermdevService", monitorTermdevService);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorTermdevService monitorTermdevService = termdevService.findMonitorTermdevServiceById(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorTermdevService);
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List termdevServiceCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(4));
        ((DynaActionForm) form).set("monitorTermdevService", monitorTermdevService);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("termdevServiceCommands", termdevServiceCommands);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        termdevService.deleteMonitorTermdevService(Integer.valueOf(id));
        return mapping.findForward("success");
    }

    public ActionForward updateMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTermdevService monitorTermdevService = (MonitorTermdevService) ((DynaActionForm) form).get("monitorTermdevService");
        DependencyUtil.clearDependencyProperty(monitorTermdevService);
        termdevService.updateMonitorTermdevService(monitorTermdevService);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorTermdevService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorTermdevService monitorTermdevService = termdevService.findMonitorTermdevServiceById(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorTermdevService);
        ((DynaActionForm) form).set("monitorTermdevService", monitorTermdevService);
        return mapping.findForward("view");
    }
}

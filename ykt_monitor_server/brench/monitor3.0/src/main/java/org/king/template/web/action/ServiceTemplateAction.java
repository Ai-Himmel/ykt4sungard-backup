package org.king.template.web.action;

import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorServiceTemplate;
import org.king.template.exception.TemplateAlreadyExistException;
import org.king.template.service.TemplateService;
import org.king.utils.DependencyUtil;
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
public class ServiceTemplateAction extends BaseAction {
    private TemplateService templateService;

    private MonitorSupportService monitorSupportService;

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public ActionForward inputMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorServiceTemplate monitorServiceTemplate = new MonitorServiceTemplate();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List serviceCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(2));
        ((DynaActionForm) form).set("monitorServiceTemplate", monitorServiceTemplate);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("serviceCommands",serviceCommands);

        return mapping.findForward("input");
    }

    /**
     * 增加服务模板
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorServiceTemplate monitorServiceTemplate = (MonitorServiceTemplate) ((DynaActionForm) form).get("monitorServiceTemplate");
            DependencyUtil.clearDependencyProperty(monitorServiceTemplate);
            templateService.saveMonitorServiceTemplate(monitorServiceTemplate);
        } catch (TemplateAlreadyExistException e) {
            errors.add("addMonitorServiceTemplate", new ActionMessage("errors.TemplateExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorServiceTemplate monitorServiceTemplate = (MonitorServiceTemplate) ((DynaActionForm) form).get("monitorServiceTemplate");
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        templateService.findMonitorServiceTemplateByPage(page, monitorServiceTemplate);

        request.setAttribute("serviceTemplates", page);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        ((DynaActionForm) form).set("monitorServiceTemplate", monitorServiceTemplate);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorServiceTemplate monitorServiceTemplate = templateService.findMonitorServiceTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorServiceTemplate);
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List serviceCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(2));
        ((DynaActionForm) form).set("monitorServiceTemplate", monitorServiceTemplate);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("serviceCommands",serviceCommands);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        templateService.deleteMonitorServiceTemplate(Integer.valueOf(templateId));
        writer.write("删除服务模板成功！");

        return null;
    }

    public ActionForward updateMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorServiceTemplate monitorServiceTemplate = (MonitorServiceTemplate) ((DynaActionForm) form).get("monitorServiceTemplate");
        DependencyUtil.clearDependencyProperty(monitorServiceTemplate);
        templateService.updateMonitorServiceTemplate(monitorServiceTemplate);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorServiceTemplate monitorServiceTemplate = templateService.findMonitorServiceTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorServiceTemplate);
        ((DynaActionForm) form).set("monitorServiceTemplate", monitorServiceTemplate);
        return mapping.findForward("view");
    }
}

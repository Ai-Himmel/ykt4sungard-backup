package org.king.template.web.action;

import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.host.service.MonitorHostService;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorHostTemplate;
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
 * Date: 2010-7-1
 */
public class HostTemplateAction extends BaseAction {
    private TemplateService templateService;

    private MonitorHostService monitorHostService;

    private MonitorSupportService monitorSupportService;

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public ActionForward inputMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorHostTemplate monitorHostTemplate = new MonitorHostTemplate();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();
        List hostCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(1));
        ((DynaActionForm) form).set("monitorHostTemplate", monitorHostTemplate);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);
        request.getSession().setAttribute("hostCommands", hostCommands);

        return mapping.findForward("input");
    }

    /**
     * 增加主机模板
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorHostTemplate monitorHostTemplate = (MonitorHostTemplate) ((DynaActionForm) form).get("monitorHostTemplate");
            DependencyUtil.clearDependencyProperty(monitorHostTemplate);
            templateService.saveMonitorHostTemplate(monitorHostTemplate);
        } catch (TemplateAlreadyExistException e) {
            errors.add("addMonitorHostTemplate", new ActionMessage("errors.TemplateExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorHostTemplate monitorHostTemplate = (MonitorHostTemplate) ((DynaActionForm) form).get("monitorHostTemplate");
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        templateService.findMonitorHostTemplateByPage(page, monitorHostTemplate);

        request.setAttribute("hostTemplates", page);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        ((DynaActionForm) form).set("monitorHostTemplate", monitorHostTemplate);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorHostTemplate monitorHostTemplate = templateService.findMonitorHostTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorHostTemplate);
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();
        List hostCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(1));

        ((DynaActionForm) form).set("monitorHostTemplate", monitorHostTemplate);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);
        request.getSession().setAttribute("hostCommands", hostCommands);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();

        templateService.deleteMonitorHostTemplate(Integer.valueOf(templateId));
        writer.write("删除主机模板成功！");

        return null;
    }

    public ActionForward updateMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorHostTemplate monitorHostTemplate = (MonitorHostTemplate) ((DynaActionForm) form).get("monitorHostTemplate");
        DependencyUtil.clearDependencyProperty(monitorHostTemplate);
        templateService.updateMonitorHostTemplate(monitorHostTemplate);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorHostTemplate monitorHostTemplate = templateService.findMonitorHostTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorHostTemplate);
        ((DynaActionForm) form).set("monitorHostTemplate", monitorHostTemplate);
        ((DynaActionForm) form).set("type", "view");
        return mapping.findForward("view");
    }
}

package org.king.template.web.action;

import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.template.domain.MonitorContactTemplate;
import org.king.template.exception.TemplateAlreadyExistException;
import org.king.template.service.TemplateService;
import org.king.utils.DependencyUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-7
 */
public class ContactTemplateAction extends BaseAction {
    private TemplateService templateService;

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public ActionForward inputMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorContactTemplate monitorContactTemplate = new MonitorContactTemplate();
        String[] hostCommands = templateService.getNotifyHostCommands();
        String[] serviceCommands = templateService.getNotifyServiceCommands();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        ((DynaActionForm) form).set("monitorContactTemplate", monitorContactTemplate);
        ((DynaActionForm) form).set("type", "add");
        request.setAttribute("hostCommands", hostCommands);
        request.setAttribute("serviceCommands", serviceCommands);
        request.setAttribute("monitorTimePeriods", monitorTimePeriods);
        return mapping.findForward("input");
    }

    /**
     * 增加联系人模板
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorContactTemplate monitorContactTemplate = (MonitorContactTemplate) ((DynaActionForm) form).get("monitorContactTemplate");
            DependencyUtil.clearDependencyProperty(monitorContactTemplate);
            templateService.saveMonitorContactTemplate(monitorContactTemplate);
        } catch (TemplateAlreadyExistException e) {
            errors.add("addMonitorContactTemplate", new ActionMessage("errors.TemplateExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorContactTemplate monitorContactTemplate = (MonitorContactTemplate) ((DynaActionForm) form).get("monitorContactTemplate");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        templateService.findMonitorContactTemplateByPage(page, monitorContactTemplate);

        request.setAttribute("contactTemplates", page);
        ((DynaActionForm) form).set("monitorContactTemplate", monitorContactTemplate);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorContactTemplate monitorContactTemplate = templateService.findMonitorContactTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorContactTemplate);
        String[] hostCommands = templateService.getNotifyHostCommands();
        String[] serviceCommands = templateService.getNotifyServiceCommands();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        ((DynaActionForm) form).set("monitorContactTemplate", monitorContactTemplate);
        ((DynaActionForm) form).set("type", "edit");
        request.setAttribute("hostCommands", hostCommands);
        request.setAttribute("serviceCommands", serviceCommands);
        request.setAttribute("monitorTimePeriods",monitorTimePeriods);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        templateService.deleteMonitorContactTemplate(Integer.valueOf(templateId));
        return mapping.findForward("success");
    }

    public ActionForward updateMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorContactTemplate monitorContactTemplate = (MonitorContactTemplate) ((DynaActionForm) form).get("monitorContactTemplate");
        DependencyUtil.clearDependencyProperty(monitorContactTemplate);
        templateService.updateMonitorContactTemplate(monitorContactTemplate);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorContactTemplate monitorContactTemplate = templateService.findMonitorContactTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorContactTemplate);
        ((DynaActionForm) form).set("monitorContactTemplate", monitorContactTemplate);

        return mapping.findForward("view");
    }
}

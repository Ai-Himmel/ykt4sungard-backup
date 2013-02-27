package org.king.hostservice.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.host.service.MonitorHostService;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorServiceTemplate;
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
 * Date: 2010-7-10
 */
public class HostserviceAction extends BaseAction {
    private MonitorHostserviceService monitorHostserviceService;

    private TemplateService templateService;

    private MonitorSupportService monitorSupportService;

    private MonitorHostService monitorHostService;

    public void setMonitorHostserviceService(MonitorHostserviceService monitorHostserviceService) {
        this.monitorHostserviceService = monitorHostserviceService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public ActionForward inputMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorService monitorService = new MonitorService();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List serviceCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(2));
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List monitorHosts = monitorHostService.findAllMonitorHost();
        ((DynaActionForm) form).set("monitorService", monitorService);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("serviceCommands", serviceCommands);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("monitorHosts", monitorHosts);

        return mapping.findForward("input");
    }

    /**
     * 增加主机服务
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        MonitorService monitorService = (MonitorService) ((DynaActionForm) form).get("monitorService");
        String type = (String) ((DynaActionForm) form).get("type");
        DependencyUtil.clearDependencyProperty(monitorService);
        monitorHostserviceService.saveMonitorService(monitorService);

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorService monitorService = (MonitorService) ((DynaActionForm) form).get("monitorService");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostserviceService.findMonitorServiceByPage(page, monitorService);

        request.setAttribute("hostserviceList", page);
        ((DynaActionForm) form).set("monitorService", monitorService);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorService monitorService = monitorHostserviceService.getMonitorService(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorService);
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List serviceCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(2));
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List monitorHosts = monitorHostService.findAllMonitorHost();
        ((DynaActionForm) form).set("monitorService", monitorService);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("serviceCommands", serviceCommands);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("monitorHosts", monitorHosts);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        monitorHostserviceService.deleteMonitorService(Integer.valueOf(id));
        writer.write("删除主机服务成功！");

        return null;
    }

    public ActionForward updateMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorService monitorService = (MonitorService) ((DynaActionForm) form).get("monitorService");
        DependencyUtil.clearDependencyProperty(monitorService);
        monitorHostserviceService.updateMonitorService(monitorService);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorService(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorService monitorService = monitorHostserviceService.getMonitorService(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorService);
        ((DynaActionForm) form).set("monitorService", monitorService);
        return mapping.findForward("view");
    }

    public ActionForward selectMonitorServiceTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        if (StringUtils.isNotBlank(templateId)) {
            MonitorServiceTemplate monitorServiceTemplate = templateService.findMonitorServiceTemplateById(Integer.valueOf(templateId));
            request.setAttribute("monitorServiceTemplate", monitorServiceTemplate);
        }
        List list = templateService.findAllMonitorServiceTemplate();
        request.setAttribute("list", list);
        request.setAttribute("templateId", templateId);
        return mapping.findForward("selectServiceTemplate");
    }
}

package org.king.host.web.action;

import org.apache.commons.beanutils.BeanComparator;
import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.util.LabelValueBean;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.king.host.domain.MonitorHost;
import org.king.host.exception.HostAlreadyExistException;
import org.king.host.service.MonitorHostService;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorHostTemplate;
import org.king.template.service.TemplateService;
import org.king.utils.Contants;
import org.king.utils.DependencyUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public class HostAction extends BaseAction {
    private MonitorHostService monitorHostService;

    private TemplateService templateService;

    private MonitorSupportService monitorSupportService;

    private List<LabelValueBean> hostTypes;

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public ActionForward inputMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorHost monitorHost = new MonitorHost();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();
        List hostCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(1));
        ((DynaActionForm) form).set("monitorHost", monitorHost);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("hostCommands", hostCommands);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);
        request.getSession().setAttribute("hostTypes", getHostTypes());

        return mapping.findForward("input");
    }

    /**
     * 获得主机状态集合
     *
     * @return .
     */
    private List getHostTypes() {
        if (hostTypes == null) {
            hostTypes = new ArrayList();
            Map<String, String> map = Contants.HOST_TYPE;
            for (String key : map.keySet()) {
                String value = map.get(key);
                hostTypes.add(new LabelValueBean(value, key));
            }
            Collections.sort(hostTypes, new BeanComparator("value"));
        }
        return hostTypes;
    }

    /**
     * 增加主机
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorHost monitorHost = (MonitorHost) ((DynaActionForm) form).get("monitorHost");
            DependencyUtil.clearDependencyProperty(monitorHost);
            monitorHostService.saveMonitorHost(monitorHost);
        } catch (HostAlreadyExistException e) {
            errors.add("addMonitorHost", new ActionMessage("errors.HostExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorHost monitorHost = (MonitorHost) ((DynaActionForm) form).get("monitorHost");
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostService.findMonitorHostByPage(page, monitorHost);
        StateDecorator hostTypeDecorator = DecoratorFactory.getHostTypeDecorator();
        request.setAttribute("hostList", page);
        request.setAttribute("hostTypeDecorator", hostTypeDecorator);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);
        ((DynaActionForm) form).set("monitorHost", monitorHost);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorHost monitorHost = monitorHostService.getMonitorHost(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorHost);
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List hostCommands = monitorSupportService.findMonitorCommands(Integer.valueOf(1));
        ((DynaActionForm) form).set("monitorHost", monitorHost);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("hostCommands", hostCommands);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);
        request.getSession().setAttribute("hostTypes", getHostTypes());

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            monitorHostService.deleteMonitorHost(Integer.valueOf(id));
            writer.write("删除主机成功！");
        } catch (BusinessException e) {
            writer.write("error:删除失败，该主机已被服务关联，请检查！");
        }
        return null;
    }

    public ActionForward updateMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorHost monitorHost = (MonitorHost) ((DynaActionForm) form).get("monitorHost");
        DependencyUtil.clearDependencyProperty(monitorHost);
        monitorHostService.updateMonitorHost(monitorHost);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorHost(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorHost monitorHost = monitorHostService.getMonitorHost(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorHost);
        ((DynaActionForm) form).set("monitorHost", monitorHost);
        return mapping.findForward("view");
    }

    public ActionForward selectMonitorHostTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        if (StringUtils.isNotBlank(templateId)) {
            MonitorHostTemplate monitorHostTemplate = templateService.findMonitorHostTemplateById(Integer.valueOf(templateId));
            request.setAttribute("monitorHostTemplate", monitorHostTemplate);
        }
        List list = templateService.findAllMonitorHostTemplate();
        request.setAttribute("list", list);
        request.setAttribute("templateId", templateId);
        return mapping.findForward("selectHostTemplate");
    }
}

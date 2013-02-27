package org.king.template.web.action;

import net.sf.json.JSONArray;
import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorTermdevTemplate;
import org.king.template.exception.TemplateAlreadyExistException;
import org.king.template.service.TemplateService;
import org.king.termdev.service.TermdevService;
import org.king.utils.DependencyUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-7
 */
public class TermdevTemplateAction extends BaseAction {
    private TemplateService templateService;

    private MonitorSupportService monitorSupportService;

    private TermdevService termdevService;

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public ActionForward inputMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTermdevTemplate monitorTermdevTemplate = new MonitorTermdevTemplate();
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        ((DynaActionForm) form).set("monitorTermdevTemplate", monitorTermdevTemplate);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);

        return mapping.findForward("input");
    }

    /**
     * 增加监控配置模板
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward addMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorTermdevTemplate monitorTermdevTemplate = (MonitorTermdevTemplate) ((DynaActionForm) form).get("monitorTermdevTemplate");
            DependencyUtil.clearDependencyProperty(monitorTermdevTemplate);
            templateService.saveMonitorTermdevTemplate(monitorTermdevTemplate);
        } catch (TemplateAlreadyExistException e) {
            errors.add("addMonitorTermdevTemplate", new ActionMessage("errors.TemplateExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorTermdevTemplate monitorTermdevTemplate = (MonitorTermdevTemplate) ((DynaActionForm) form).get("monitorTermdevTemplate");
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        templateService.findMonitorTermdevTemplateByPage(page, monitorTermdevTemplate);
        StateDecorator yesNoStatusDecorator = DecoratorFactory.getYesNoStatusDecorator();

        request.setAttribute("termdevTemplates", page);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
        ((DynaActionForm) form).set("monitorTermdevTemplate", monitorTermdevTemplate);
        request.setAttribute("yesNoStatusDecorator", yesNoStatusDecorator);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorTermdevTemplate monitorTermdevTemplate = templateService.findMonitorTermdevTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorTermdevTemplate);
        List monitorTimePeriods = templateService.findAllMonitorTimePeriods();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        ((DynaActionForm) form).set("monitorTermdevTemplate", monitorTermdevTemplate);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorTimePeriods", monitorTimePeriods);
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            templateService.deleteMonitorTermdevTemplate(Integer.valueOf(templateId));
            writer.write("删除设备模板成功！");
        } catch (BusinessException e) {
            writer.write("error:删除失败，该设备模板已和设备绑定，请检查！");
        }
        return null;
    }

    public ActionForward updateMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTermdevTemplate monitorTermdevTemplate = (MonitorTermdevTemplate) ((DynaActionForm) form).get("monitorTermdevTemplate");
        DependencyUtil.clearDependencyProperty(monitorTermdevTemplate);
        templateService.updateMonitorTermdevTemplate(monitorTermdevTemplate);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorTermdevTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        MonitorTermdevTemplate monitorTermdevTemplate = templateService.findMonitorTermdevTemplateById(Integer.valueOf(templateId));
        DependencyUtil.initDependencyProperty(monitorTermdevTemplate);
        ((DynaActionForm) form).set("monitorTermdevTemplate", monitorTermdevTemplate);
        return mapping.findForward("view");
    }

    public ActionForward editMonitorDevtem(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        JSONArray jsonArray = JSONArray.fromObject(termdevService.findBindingDevice(Integer.valueOf(templateId)));

        request.setAttribute("bindingDevice", jsonArray.toString());
        request.setAttribute("templateId", templateId);
        return mapping.findForward("devtem");
    }

    public ActionForward listEnableDevice(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        request.setAttribute("templateId", templateId);
        return mapping.findForward("deviceTree");
    }

    public ActionForward getDeviceXmlTree(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        String deviceXml = termdevService.getDeviceXmlTree(Integer.valueOf(templateId));
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        writer.write(deviceXml);
        return null;
    }


    public ActionForward bindingDevice(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        String deviceids = request.getParameter("deviceids");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();

        try {
            JSONArray jsonArray = JSONArray.fromObject(deviceids);
            Set devices = new HashSet();
            devices.addAll(Arrays.asList(jsonArray.toArray()));
            termdevService.updateBindingDevice(Integer.valueOf(templateId), devices);
            writer.write("分配模板成功！");
        } catch (Exception e) {
            writer.write("error:分配模板失败！");
            log.error(e.getMessage());
        }
        return null;
    }
}

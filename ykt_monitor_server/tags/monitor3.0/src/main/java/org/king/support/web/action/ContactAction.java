package org.king.support.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.support.domain.MonitorContact;
import org.king.support.exception.ContactAlreadyExistException;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorContactTemplate;
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
 * Date: 2010-7-9
 */
public class ContactAction extends BaseAction {
    private MonitorSupportService monitorSupportService;

    private TemplateService templateService;

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public ActionForward inputMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorContact monitorContact = new MonitorContact();
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        ((DynaActionForm) form).set("monitorContact", monitorContact);
        ((DynaActionForm) form).set("type", "add");
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);
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
    public ActionForward addMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorContact monitorContact = (MonitorContact) ((DynaActionForm) form).get("monitorContact");
            DependencyUtil.clearDependencyProperty(monitorContact);
            monitorSupportService.saveMonitorContact(monitorContact);
        } catch (ContactAlreadyExistException e) {
            errors.add("addMonitorContact", new ActionMessage("errors.ContactExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorContact monitorContact = (MonitorContact) ((DynaActionForm) form).get("monitorContact");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorSupportService.findMonitorContactByPage(page, monitorContact);

        request.setAttribute("contactList", page);
        ((DynaActionForm) form).set("monitorContact", monitorContact);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorContact monitorContact = monitorSupportService.findMonitorContactById(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorContact);
        List monitorContactgroups = monitorSupportService.findAllMonitorContactgroups();
        ((DynaActionForm) form).set("monitorContact", monitorContact);
        ((DynaActionForm) form).set("type", "edit");
        request.getSession().setAttribute("monitorContactgroups", monitorContactgroups);

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        monitorSupportService.deleteMonitorContact(Integer.valueOf(id));
        writer.write("删除联系人成功！");

        return null;
    }

    public ActionForward updateMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorContact monitorContact = (MonitorContact) ((DynaActionForm) form).get("monitorContact");
        DependencyUtil.clearDependencyProperty(monitorContact);
        monitorSupportService.updateMonitorContact(monitorContact);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorContact(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorContact monitorContact = monitorSupportService.findMonitorContactById(Integer.valueOf(id));
        DependencyUtil.initDependencyProperty(monitorContact);
        ((DynaActionForm) form).set("monitorContact", monitorContact);
        return mapping.findForward("view");
    }

    public ActionForward selectMonitorContactTemplate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String templateId = request.getParameter("templateId");
        if (StringUtils.isNotBlank(templateId)) {
            MonitorContactTemplate monitorContactTemplate = templateService.findMonitorContactTemplateById(Integer.valueOf(templateId));
            request.setAttribute("monitorContactTemplate", monitorContactTemplate);
        }
        List list = templateService.findAllMonitorContactTemplate();
        request.setAttribute("list", list);
        request.setAttribute("templateId", templateId);
        return mapping.findForward("selectContactTemplate");
    }
}

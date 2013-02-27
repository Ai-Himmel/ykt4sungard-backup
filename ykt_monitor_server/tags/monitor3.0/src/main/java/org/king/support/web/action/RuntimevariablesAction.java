package org.king.support.web.action;

import org.apache.struts.action.*;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.support.domain.MonitorRuntimevariables;
import org.king.support.exception.RuntimevariablesAlreadyExistException;
import org.king.support.service.MonitorSupportService;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-9
 */
public class RuntimevariablesAction extends BaseAction {
    private MonitorSupportService monitorSupportService;

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public ActionForward inputMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorRuntimevariables monitorRuntimevariables = new MonitorRuntimevariables();
        ((DynaActionForm) form).set("monitorRuntimevariables", monitorRuntimevariables);
        ((DynaActionForm) form).set("type", "add");
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
    public ActionForward addMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ActionMessages errors = new ActionMessages();
        try {
            MonitorRuntimevariables monitorRuntimevariables = (MonitorRuntimevariables) ((DynaActionForm) form).get("monitorRuntimevariables");
            monitorSupportService.saveMonitorRuntimevariables(monitorRuntimevariables);
        } catch (RuntimevariablesAlreadyExistException e) {
            errors.add("addMonitorRuntimevariables", new ActionMessage("errors.RuntimevariablesExist"));
        }

        if (!errors.isEmpty()) {
            saveErrors(request, errors);
            return mapping.findForward("input");
        } else {
            return mapping.findForward("success");
        }
    }

    public ActionForward listMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorRuntimevariables monitorRuntimevariables = (MonitorRuntimevariables) ((DynaActionForm) form).get("monitorRuntimevariables");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorSupportService.findMonitorRuntimevariablesByPage(page, monitorRuntimevariables);

        request.setAttribute("runtimevariablesList", page);
        ((DynaActionForm) form).set("monitorRuntimevariables", monitorRuntimevariables);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorRuntimevariables monitorRuntimevariables = monitorSupportService.findMonitorRuntimevariablesById(Integer.valueOf(id));
        ((DynaActionForm) form).set("monitorRuntimevariables", monitorRuntimevariables);
        ((DynaActionForm) form).set("type", "edit");

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        monitorSupportService.deleteMonitorRuntimevariables(Integer.valueOf(id));
        return mapping.findForward("success");
    }

    public ActionForward updateMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorRuntimevariables monitorRuntimevariables = (MonitorRuntimevariables) ((DynaActionForm) form).get("monitorRuntimevariables");
        monitorSupportService.updateMonitorRuntimevariables(monitorRuntimevariables);
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorRuntimevariables(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        MonitorRuntimevariables monitorRuntimevariables = monitorSupportService.findMonitorRuntimevariablesById(Integer.valueOf(id));
        ((DynaActionForm) form).set("monitorRuntimevariables", monitorRuntimevariables);
        ((DynaActionForm) form).set("type", "view");
        return mapping.findForward("view");
    }
}

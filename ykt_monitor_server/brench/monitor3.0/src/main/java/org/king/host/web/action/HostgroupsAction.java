package org.king.host.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.king.host.domain.MonitorHostgroups;
import org.king.host.exception.HostgroupsAlreadyExistException;
import org.king.host.service.MonitorHostService;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-28
 */
public class HostgroupsAction extends BaseAction {

    private MonitorHostService monitorHostService;

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public ActionForward inputMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorHostgroups monitorHostgroups = new MonitorHostgroups();

        ((DynaActionForm) form).set("monitorHostgroups", monitorHostgroups);
        ((DynaActionForm) form).set("type", "add");
        return mapping.findForward("input");
    }

    public ActionForward addMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            MonitorHostgroups monitorHostgroups = (MonitorHostgroups) ((DynaActionForm) form).get("monitorHostgroups");
            monitorHostService.saveMonitorHostgroups(monitorHostgroups);
            writer.write("添加主机组成功！");
        } catch (HostgroupsAlreadyExistException e) {
            writer.write("error:"+e.getMessage());
        }
        return null;
    }

    public ActionForward listMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorHostgroups monitorHostgroups = (MonitorHostgroups) ((DynaActionForm) form).get("monitorHostgroups");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostService.findMonitorHostgroupsByPage(page, monitorHostgroups);

        request.setAttribute("groupList", page);
        ((DynaActionForm) form).set("monitorHostgroups", monitorHostgroups);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String groupId = request.getParameter("groupId");
        MonitorHostgroups monitorHostgroups = monitorHostService.getMonitorHostgroups(Integer.valueOf(groupId));
        ((DynaActionForm) form).set("monitorHostgroups", monitorHostgroups);
        ((DynaActionForm) form).set("type", "edit");

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String groupId = request.getParameter("groupId");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            monitorHostService.deleteMonitorHostgroups(Integer.valueOf(groupId));
            writer.write("删除主机组成功！");
        } catch (BusinessException e) {
            writer.write("error:删除失败，该主机组可能被主机模板或者主机关联，请检查！");
        }
        return null;
    }

    public ActionForward updateMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            MonitorHostgroups monitorHostgroups = (MonitorHostgroups) ((DynaActionForm) form).get("monitorHostgroups");
            monitorHostService.updateMonitorHostgroups(monitorHostgroups);
            writer.write("修改主机组成功！");
        } catch (HostgroupsAlreadyExistException e) {
            writer.write("error:"+e.getMessage());
        }
        return null;
    }

    public ActionForward viewMonitorHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String groupId = request.getParameter("groupId");
        MonitorHostgroups monitorHostgroups = monitorHostService.getMonitorHostgroups(Integer.valueOf(groupId));
        ((DynaActionForm) form).set("monitorHostgroups", monitorHostgroups);

        return mapping.findForward("view");
    }
}

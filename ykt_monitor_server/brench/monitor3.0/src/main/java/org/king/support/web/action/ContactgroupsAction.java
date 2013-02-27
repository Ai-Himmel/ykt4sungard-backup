package org.king.support.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.king.support.domain.MonitorContactgroups;
import org.king.support.exception.ContactgroupsAlreadyExistException;
import org.king.support.service.MonitorSupportService;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-28
 */
public class ContactgroupsAction extends BaseAction {

    private MonitorSupportService monitorSupportService;

    public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
        this.monitorSupportService = monitorSupportService;
    }

    public ActionForward inputMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorContactgroups monitorContactgroups = new MonitorContactgroups();

        ((DynaActionForm) form).set("monitorContactgroups", monitorContactgroups);
        ((DynaActionForm) form).set("type", "add");
        return mapping.findForward("input");
    }

    public ActionForward addMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            MonitorContactgroups monitorContactgroups = (MonitorContactgroups) ((DynaActionForm) form).get("monitorContactgroups");
            monitorSupportService.saveMonitorContactgroups(monitorContactgroups);
            writer.write("�����ϵ����ɹ���");
        } catch (ContactgroupsAlreadyExistException e) {
            writer.write("error:" + e.getMessage());
        }

        return null;
    }

    public ActionForward listMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorContactgroups monitorContactgroups = (MonitorContactgroups) ((DynaActionForm) form).get("monitorContactgroups");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorSupportService.findMonitorContactgroupsByPage(page, monitorContactgroups);

        request.setAttribute("groupList", page);
        ((DynaActionForm) form).set("monitorContactgroups", monitorContactgroups);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String groupId = request.getParameter("groupId");
        MonitorContactgroups monitorContactgroups = monitorSupportService.getMonitorContactgroups(Integer.valueOf(groupId));
        ((DynaActionForm) form).set("monitorContactgroups", monitorContactgroups);
        ((DynaActionForm) form).set("type", "edit");

        return mapping.findForward("input");
    }

    public ActionForward deleteMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String groupId = request.getParameter("groupId");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            monitorSupportService.deleteMonitorContactgroups(Integer.valueOf(groupId));
            writer.write("ɾ����ϵ����ɹ���");
        } catch (BusinessException e) {
            writer.write("error:ɾ��ʧ�ܣ�����ϵ������ܱ�����ģ�塢����ģ�塢�豸ģ�塢���������������ϵ�˹��������飡");
        }
        return null;
    }

    public ActionForward updateMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            MonitorContactgroups monitorContactgroups = (MonitorContactgroups) ((DynaActionForm) form).get("monitorContactgroups");
            monitorSupportService.updateMonitorContactgroups(monitorContactgroups);
            writer.write("�޸���ϵ����ɹ���");
        } catch (ContactgroupsAlreadyExistException e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }

    public ActionForward viewMonitorContactgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String groupId = request.getParameter("groupId");
        MonitorContactgroups monitorContactgroups = monitorSupportService.getMonitorContactgroups(Integer.valueOf(groupId));
        ((DynaActionForm) form).set("monitorContactgroups", monitorContactgroups);

        return mapping.findForward("view");
    }
}

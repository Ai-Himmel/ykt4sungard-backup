package org.king.topo.web.action;

import net.sf.json.JSONArray;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.framework.web.action.BaseAction;
import org.king.topo.domain.MonitorTopoGroup;
import org.king.topo.service.MonitorTopoService;
import org.king.utils.DependencyUtil;

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
 * Date: 2011-3-21
 */
public class TopoGroupAction extends BaseAction {

    private MonitorTopoService monitorTopoService;

    public void setMonitorTopoService(MonitorTopoService monitorTopoService) {
        this.monitorTopoService = monitorTopoService;
    }

    public ActionForward listMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorTopoGroup monitorTopoGroup = (MonitorTopoGroup) ((DynaActionForm) form).get("monitorTopoGroup");
        List groupList = monitorTopoService.findMonitorTopoGroup(monitorTopoGroup);
        List locations = monitorTopoService.findAllMonitorTopoLocation();

        request.setAttribute("groupList", groupList);
        request.setAttribute("locations",locations);

        return mapping.findForward("list");
    }

    public ActionForward inputMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTopoGroup monitorTopoGroup = new MonitorTopoGroup();

        List locationList = monitorTopoService.findAllMonitorTopoLocation();
        request.setAttribute("locationList", locationList);
        ((DynaActionForm) form).set("monitorTopoGroup", monitorTopoGroup);
        ((DynaActionForm) form).set("type", "add");

        return mapping.findForward("input");
    }

    public ActionForward addMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTopoGroup monitorTopoGroup = (MonitorTopoGroup) ((DynaActionForm) form).get("monitorTopoGroup");
        DependencyUtil.clearDependencyProperty(monitorTopoGroup);
        monitorTopoService.saveMonitorTopoGroup(monitorTopoGroup);
        return mapping.findForward("success");
    }

    public ActionForward editMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        MonitorTopoGroup monitorTopoGroup = monitorTopoService.getMonitorTopoGroup(Integer.valueOf(deviceGroupId));
        DependencyUtil.initDependencyProperty(monitorTopoGroup);
        List locationList = monitorTopoService.findAllMonitorTopoLocation();
        request.setAttribute("locationList", locationList);
        ((DynaActionForm) form).set("monitorTopoGroup", monitorTopoGroup);
        ((DynaActionForm) form).set("type", "edit");

        return mapping.findForward("input");
    }

    public ActionForward updateMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTopoGroup monitorTopoGroup = (MonitorTopoGroup) ((DynaActionForm) form).get("monitorTopoGroup");
        DependencyUtil.clearDependencyProperty(monitorTopoGroup);
        monitorTopoService.updateMonitorTopoGroup(monitorTopoGroup);
        return mapping.findForward("success");
    }

    public ActionForward deleteMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        monitorTopoService.deleteMonitorTopoGroup(Integer.valueOf(deviceGroupId));
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorTopoGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        MonitorTopoGroup monitorTopoGroup = monitorTopoService.getMonitorTopoGroup(Integer.valueOf(deviceGroupId));
        DependencyUtil.initDependencyProperty(monitorTopoGroup);
        ((DynaActionForm) form).set("monitorTopoGroup", monitorTopoGroup);

        return mapping.findForward("view");
    }

    /**
     * 显示设备树形结构，用于添加到组别中
     *
     * @param mapping  .
     * @param form     .
     * @param request  .
     * @param response .
     * @return .
     * @throws Exception .
     */
    public ActionForward editMonitorDeviceGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        JSONArray jsonArray = JSONArray.fromObject(monitorTopoService.findBindingDevice(Integer.valueOf(deviceGroupId)));

        request.setAttribute("bindingDevice", jsonArray.toString());
        request.setAttribute("deviceGroupId", deviceGroupId);
        return mapping.findForward("deviceGroup");
    }

    public ActionForward listEnableDevice(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        request.setAttribute("deviceGroupId", deviceGroupId);
        return mapping.findForward("deviceTree");
    }

    public ActionForward getDeviceXmlTree(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        String deviceXml = monitorTopoService.getDeviceXmlTree(Integer.valueOf(deviceGroupId));
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        writer.write(deviceXml);
        return null;
    }

    public ActionForward bindingDevice(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceGroupId = request.getParameter("deviceGroupId");
        String deviceids = request.getParameter("deviceids");
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();

        try {
            JSONArray jsonArray = JSONArray.fromObject(deviceids);
            Set devices = new HashSet();
            devices.addAll(Arrays.asList(jsonArray.toArray()));
            monitorTopoService.updateBindingDevice(Integer.valueOf(deviceGroupId), devices);
            writer.write("分配设备成功！");
        } catch (Exception e) {
            writer.write("error:分配设备失败！");
            log.error(e.getMessage());
        }
        return null;
    }
}

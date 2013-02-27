package org.king.status.web.action;

import net.sf.json.JSONArray;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.framework.web.action.BaseAction;
import org.king.host.domain.MonitorHost;
import org.king.host.domain.MonitorHostgroups;
import org.king.host.service.MonitorHostService;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.service.MonitorHostserviceService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

/**
 * .该Action用于生成下拉框中数据
 * User: Yiming.You
 * Date: 2010-8-12
 */
public class SelectAction extends BaseAction {

    private MonitorHostService monitorHostService;

    private MonitorHostserviceService monitorHostserviceService;

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public void setMonitorHostserviceService(MonitorHostserviceService monitorHostserviceService) {
        this.monitorHostserviceService = monitorHostserviceService;
    }

    public ActionForward getHostgroups(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List hostgroups = monitorHostService.findAllMonitorHostgroups();
        List result = new ArrayList();
        if (hostgroups != null && hostgroups.size() > 0) {
            for (int i = 0; i < hostgroups.size(); i++) {
                MonitorHostgroups monitorHostgroups = (MonitorHostgroups) hostgroups.get(i);
                Object[] row = new Object[2];
                row[0] = monitorHostgroups.getHostgroupId();
                row[1] = monitorHostgroups.getGroupName();
                result.add(row);
            }
        }

        JSONArray jsonArray = JSONArray.fromObject(result);
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        writer.write(jsonArray.toString());
        return null;
    }

    public ActionForward getHosts(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String hostgroupId = request.getParameter("hostgroupId");
        List hosts = monitorHostService.findMonitorHost(Integer.valueOf(hostgroupId));
        List result = new ArrayList();
        if (hosts != null && hosts.size() > 0) {
            for (int i = 0; i < hosts.size(); i++) {
                MonitorHost monitorHost = (MonitorHost) hosts.get(i);
                Object[] row = new Object[2];
                row[0] = monitorHost.getHostId();
                row[1] = monitorHost.getDisplayName();
                result.add(row);
            }
        }

        JSONArray jsonArray = JSONArray.fromObject(result);
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        writer.write(jsonArray.toString());
        return null;
    }

    public ActionForward getServices(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String hostId = request.getParameter("hostId");
        List services = monitorHostserviceService.findMonitorService(Integer.valueOf(hostId));
        List result = new ArrayList();
        if (services != null && services.size() > 0) {
            for (int i = 0; i < services.size(); i++) {
                MonitorService monitorService = (MonitorService) services.get(i);
                Object[] row = new Object[2];
                row[0] = monitorService.getServiceId();
                row[1] = monitorService.getServiceName();
                result.add(row);
            }
        }

        JSONArray jsonArray = JSONArray.fromObject(result);
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        writer.write(jsonArray.toString());
        return null;
    }
}

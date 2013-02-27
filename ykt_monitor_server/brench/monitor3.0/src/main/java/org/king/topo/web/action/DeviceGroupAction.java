package org.king.topo.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.framework.web.action.BaseAction;
import org.king.topo.service.MonitorTopoService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-22
 */
public class DeviceGroupAction extends BaseAction {

    private MonitorTopoService monitorTopoService;

    public void setMonitorTopoService(MonitorTopoService monitorTopoService) {
        this.monitorTopoService = monitorTopoService;
    }

    public ActionForward listMonitorTopoDeviceGroup(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String devicename = (String) ((DynaActionForm) form).get("devicename");
        String devicegroupname = (String) ((DynaActionForm) form).get("devicegroupname");
        String locationname = (String) ((DynaActionForm) form).get("locationname");
        String[] args = new String[]{devicename, devicegroupname, locationname};

        List deviceGroupList = monitorTopoService.findDeviceGroup(args);

        request.setAttribute("deviceGroupList", deviceGroupList);

        return mapping.findForward("list");
    }
}

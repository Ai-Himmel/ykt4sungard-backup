package org.king.topo.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.framework.web.action.BaseAction;
import org.king.topo.domain.MonitorTopoLocation;
import org.king.topo.service.MonitorTopoService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-21
 */
public class TopoLocationAction extends BaseAction {

    private MonitorTopoService monitorTopoService;

    public void setMonitorTopoService(MonitorTopoService monitorTopoService) {
        this.monitorTopoService = monitorTopoService;
    }

    public ActionForward listMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition

        List locationList = monitorTopoService.findAllMonitorTopoLocation();

        request.setAttribute("locationList", locationList);

        return mapping.findForward("list");
    }

    public ActionForward inputMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTopoLocation monitorTopoLocation = new MonitorTopoLocation();

        ((DynaActionForm) form).set("monitorTopoLocation", monitorTopoLocation);
        ((DynaActionForm) form).set("type", "add");

        return mapping.findForward("input");
    }

    public ActionForward addMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTopoLocation monitorTopoLocation = (MonitorTopoLocation) ((DynaActionForm) form).get("monitorTopoLocation");
        monitorTopoService.saveMonitorTopoLocation(monitorTopoLocation);
        return mapping.findForward("success");
    }

    public ActionForward editMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String locationId = request.getParameter("locationId");
        MonitorTopoLocation monitorTopoLocation = monitorTopoService.getMonitorTopoLocation(Integer.valueOf(locationId));

        ((DynaActionForm) form).set("monitorTopoLocation", monitorTopoLocation);
        ((DynaActionForm) form).set("type", "edit");

        return mapping.findForward("input");
    }

    public ActionForward updateMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        MonitorTopoLocation monitorTopoLocation = (MonitorTopoLocation) ((DynaActionForm) form).get("monitorTopoLocation");
        monitorTopoService.updateMonitorTopoLocation(monitorTopoLocation);
        return mapping.findForward("success");
    }

    public ActionForward deleteMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String locationId = request.getParameter("locationId");
        monitorTopoService.deleteMonitorTopoLocation(Integer.valueOf(locationId));
        return mapping.findForward("success");
    }

    public ActionForward viewMonitorTopoLocation(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String locationId = request.getParameter("locationId");
        MonitorTopoLocation monitorTopoLocation = monitorTopoService.getMonitorTopoLocation(Integer.valueOf(locationId));
        ((DynaActionForm) form).set("monitorTopoLocation", monitorTopoLocation);

        return mapping.findForward("view");
    }
}

package org.king.status.web.action;

import net.sf.json.JSONArray;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.framework.web.action.BaseAction;
import org.king.host.service.MonitorHostService;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.status.util.ResultUtil;
import org.king.termdev.service.TermdevService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-15
 */
public class GlobalStatusAction extends BaseAction {
    private MonitorHostService monitorHostService;

    private MonitorHostserviceService monitorHostserviceService;

    private TermdevService termdevService;

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public void setMonitorHostserviceService(MonitorHostserviceService monitorHostserviceService) {
        this.monitorHostserviceService = monitorHostserviceService;
    }

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public ActionForward listGlobalStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String[][] hostStatusResult = monitorHostService.calculateHostStatus();
        String[][] serviceStatusResult = monitorHostserviceService.calculateServiceStatus();
        String[][] termdeviceStatusResult = termdevService.calculateTermdeviceStatus();
        String[][] termdevserviceStatusResult = termdevService.calculateTermdevserviceStatus();
        String[][] totalStatusResult = ResultUtil.caculateUnusual(hostStatusResult, serviceStatusResult, termdeviceStatusResult, termdevserviceStatusResult);

        request.setAttribute("hostStatusResult", hostStatusResult);
        request.setAttribute("serviceStatusResult", serviceStatusResult);
        request.setAttribute("termdeviceStatusResult", termdeviceStatusResult);
        request.setAttribute("termdevserviceStatusResult", termdevserviceStatusResult);
        request.setAttribute("totalStatusResult", totalStatusResult);

        return mapping.findForward("listGlobalStatus");
    }
}

package org.king.status.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.*;
import org.king.framework.web.action.BaseAction;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceStatus;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.utils.DateUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class ServiceStatusAction extends BaseAction {
    private MonitorHostserviceService monitorHostserviceService;

    public void setMonitorHostserviceService(MonitorHostserviceService monitorHostserviceService) {
        this.monitorHostserviceService = monitorHostserviceService;
    }

    public ActionForward listMonitorServiceStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String displayName = (String) ((DynaActionForm) form).get("displayName");
        String serviceName = (String) ((DynaActionForm) form).get("serviceName");
        String currentState = (String) ((DynaActionForm) form).get("currentState");
        String[] conditions = new String[]{displayName, serviceName, currentState};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostserviceService.findMonitorServiceStatusByPage(page, conditions);
        String[][] result = monitorHostserviceService.calculateServiceStatus();
        StateDecorator serviceStatusDecorator = DecoratorFactory.getServiceStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();
        DateIntervalDecorator dateIntervalDecorator = DecoratorFactory.getDateIntervalDecorator();

        request.setAttribute("serviceStatusDecorator", serviceStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);
        request.setAttribute("dateIntervalDecorator", dateIntervalDecorator);
        request.setAttribute("serviceStatusList", page);
        request.setAttribute("result", result);

        return mapping.findForward("listServiceStatus");
    }

    public ActionForward viewMonitorServiceStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String serviceId = request.getParameter("serviceId");
        MonitorServiceStatus monitorServiceStatus = monitorHostserviceService.getMonitorServiceStatus(Integer.valueOf(serviceId));
        MonitorService monitorService = monitorHostserviceService.getMonitorService(monitorServiceStatus.getServiceId());

        String statusDuration = DateUtil.convertTime(monitorServiceStatus.getLastStateChange());
        String updateDuration = DateUtil.convertTime(monitorServiceStatus.getStatusUpdateTime());
        if (StringUtils.isNotBlank(statusDuration)) {
            statusDuration = "(for " + statusDuration + ")";
        }
        if (StringUtils.isNotBlank(updateDuration)) {
            updateDuration = "(" + updateDuration + " ago)";
        }

        ((DynaActionForm) form).set("monitorServiceStatus", monitorServiceStatus);
        request.setAttribute("monitorService", monitorService);
        request.setAttribute("statusDuration", statusDuration);
        request.setAttribute("updateDuration", updateDuration);

        return mapping.findForward("viewServiceStatus");
    }
}

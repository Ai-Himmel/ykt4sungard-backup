package org.king.status.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DateDecorator;
import org.king.common.displaytag.decorator.DateIntervalDecorator;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.web.action.BaseAction;
import org.king.host.domain.MonitorHost;
import org.king.host.domain.MonitorHostStatus;
import org.king.host.service.MonitorHostService;
import org.king.utils.DateUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class HostStatusAction extends BaseAction {
    private MonitorHostService monitorHostService;

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public ActionForward listMonitorHostStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String displayName = (String) ((DynaActionForm) form).get("displayName");
        String hostAddress = (String) ((DynaActionForm) form).get("hostAddress");
        String currentState = (String) ((DynaActionForm) form).get("currentState");
        String hostgroupId = (String) ((DynaActionForm) form).get("hostgroupId");
        String[] conditions = new String[]{displayName, hostAddress, currentState, hostgroupId};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostService.findMonitorHostStatusByPage(page, conditions);
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();
        String[][] result = monitorHostService.calculateHostStatus();
        StateDecorator hostStatusDecorator = DecoratorFactory.getHostStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();
        DateIntervalDecorator dateIntervalDecorator = DecoratorFactory.getDateIntervalDecorator();

        request.setAttribute("hostStatusDecorator", hostStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);
        request.setAttribute("dateIntervalDecorator", dateIntervalDecorator);
        request.setAttribute("hostStatusList", page);
        request.setAttribute("result", result);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);

        return mapping.findForward("listHostStatus");
    }

    public ActionForward viewMonitorHostStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String hostId = request.getParameter("hostId");
        MonitorHostStatus monitorHostStatus = monitorHostService.getMonitorHostStatus(Integer.valueOf(hostId));
        MonitorHost monitorHost = monitorHostService.getMonitorHost(monitorHostStatus.getHostId());

        String statusDuration = DateUtil.convertTime(monitorHostStatus.getLastStateChange());
        String updateDuration = DateUtil.convertTime(monitorHostStatus.getStatusUpdateTime());
        if (StringUtils.isNotBlank(statusDuration)) {
            statusDuration = "(for " + statusDuration + ")";
        }
        if (StringUtils.isNotBlank(updateDuration)) {
            updateDuration = "(" + updateDuration + " ago)";
        }

        ((DynaActionForm) form).set("monitorHostStatus", monitorHostStatus);
        request.setAttribute("monitorHost", monitorHost);
        request.setAttribute("statusDuration", statusDuration);
        request.setAttribute("updateDuration", updateDuration);

        return mapping.findForward("viewHostStatus");
    }
}

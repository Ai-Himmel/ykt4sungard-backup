package org.king.status.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.jfree.chart.ChartRenderingInfo;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.servlet.ServletUtilities;
import org.king.common.chart.Chart;
import org.king.common.chart.ImageMapUtil;
import org.king.common.chart.StateChartFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DateDecorator;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.web.action.BaseAction;
import org.king.host.domain.MonitorHost;
import org.king.host.service.MonitorHostService;
import org.king.status.util.ResultUtil;
import org.king.status.util.TimePeriod;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-13
 */
public class HostHistoryStatusAction extends BaseAction {
    private MonitorHostService monitorHostService;

    public void setMonitorHostService(MonitorHostService monitorHostService) {
        this.monitorHostService = monitorHostService;
    }

    public ActionForward listHostHistoryStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String displayName = (String) ((DynaActionForm) form).get("displayName");
        String hostAddress = (String) ((DynaActionForm) form).get("hostAddress");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        String hostgroupId = (String) ((DynaActionForm) form).get("hostgroupId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        Object[] conditions = new Object[]{displayName, hostAddress, timePeriod.getStartTime(), timePeriod.getEndTime(), hostgroupId};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostService.findHostHistoryStatusByPage(page, conditions);
        List monitorHostgroups = monitorHostService.findAllMonitorHostgroups();

        request.setAttribute("hostHistoryStatus", page);
        request.getSession().setAttribute("monitorHostgroups", monitorHostgroups);

        return mapping.findForward("success");
    }

    public ActionForward viewHostHistoryStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String hostId = (String) ((DynaActionForm) form).get("hostId");
        String state = (String) ((DynaActionForm) form).get("state");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        Object[] conditions = new Object[]{Integer.valueOf(hostId), state, timePeriod.getStartTime(), timePeriod.getEndTime()};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostService.findMonitorHostchecksByPage(page, conditions);

        StateDecorator hostStatusDecorator = DecoratorFactory.getHostStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();
        request.setAttribute("monitorHostchecks", page);
        request.setAttribute("hostStatusDecorator", hostStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);

        return mapping.findForward("view");
    }

    public ActionForward viewHostHistoryChart(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        String hostId = (String) ((DynaActionForm) form).get("hostId");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        MonitorHost monitorHost = monitorHostService.getMonitorHost(Integer.valueOf(hostId));
        List list = monitorHostService.findMonitorHostchecks(Integer.valueOf(hostId), timePeriod.getStartTime(), timePeriod.getEndTime());
        Object[][] data = ResultUtil.transformMonitorHostchecks(list, timePeriod.getStartTime(), timePeriod.getEndTime());
        Chart chart = StateChartFactory.getStateBarChart(monitorHost.getDisplayName(), data, 800, 320, StateChartFactory.HOST_TYPE, timePeriod.getType());
        ChartRenderingInfo info = new ChartRenderingInfo();

        JFreeChart freeChart = chart.getChart();
        String filename = ServletUtilities.saveChartAsPNG(freeChart, 800, 320, info, request.getSession());
        ImageMapUtil.writeImageMap(response.getWriter(), filename, info, false);
        request.setAttribute("filename", filename);

        return mapping.findForward("chart");
    }
}

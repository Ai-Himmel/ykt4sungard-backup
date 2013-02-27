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
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.status.util.ResultUtil;
import org.king.status.util.TimePeriod;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-27
 */
public class ServiceHistoryStatusAction extends BaseAction {

    private MonitorHostserviceService monitorHostserviceService;

    public void setMonitorHostserviceService(MonitorHostserviceService monitorHostserviceService) {
        this.monitorHostserviceService = monitorHostserviceService;
    }

    public ActionForward listServiceHistoryStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String displayName = (String) ((DynaActionForm) form).get("displayName");
        String serviceName = (String) ((DynaActionForm) form).get("serviceName");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        Object[] conditions = new Object[]{displayName, serviceName, timePeriod.getStartTime(), timePeriod.getEndTime()};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostserviceService.findServiceHistoryStatusByPage(page, conditions);

        request.setAttribute("serviceHistoryStatus", page);

        return mapping.findForward("success");
    }

    public ActionForward viewServiceHistoryStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String serviceId = (String) ((DynaActionForm) form).get("serviceId");
        String state = (String) ((DynaActionForm) form).get("state");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        Object[] conditions = new Object[]{Integer.valueOf(serviceId), state, timePeriod.getStartTime(), timePeriod.getEndTime()};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        monitorHostserviceService.findMonitorServiceCheckByPage(page, conditions);

        StateDecorator serviceStatusDecorator = DecoratorFactory.getServiceStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();
        request.setAttribute("monitorServiceCheck", page);
        request.setAttribute("serviceStatusDecorator", serviceStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);

        return mapping.findForward("view");
    }

    public ActionForward viewServiceHistoryChart(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        String serviceId = (String) ((DynaActionForm) form).get("serviceId");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        MonitorService monitorService = monitorHostserviceService.getMonitorService(Integer.valueOf(serviceId));
        List list = monitorHostserviceService.findMonitorServiceCheck(Integer.valueOf(serviceId), timePeriod.getStartTime(), timePeriod.getEndTime());
        Object[][] data = ResultUtil.transformMonitorServiceCheck(list, timePeriod.getStartTime(), timePeriod.getEndTime());
        Chart chart = StateChartFactory.getStateBarChart(monitorService.getServiceName(), data, 800, 320, StateChartFactory.SERVICE_TYPE, timePeriod.getType());
        ChartRenderingInfo info = new ChartRenderingInfo();

        JFreeChart freeChart = chart.getChart();
        String filename = ServletUtilities.saveChartAsPNG(freeChart, 800, 320, info, request.getSession());
        ImageMapUtil.writeImageMap(response.getWriter(), filename, info, false);
        request.setAttribute("filename", filename);

        return mapping.findForward("chart");
    }
}

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
import org.king.status.util.ResultUtil;
import org.king.status.util.TimePeriod;
import org.king.template.service.TemplateService;
import org.king.termdev.service.TermdevService;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-13
 */
public class TermdeviceHistoryStatusAction extends BaseAction {

    private TermdevService termdevService;

    private TemplateService templateService;

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public ActionForward listTermdeviceHistoryStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String fdevicename = (String) ((DynaActionForm) form).get("fdevicename");
        String devicename = (String) ((DynaActionForm) form).get("devicename");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        String templateId = (String) ((DynaActionForm) form).get("templateId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        Object[] conditions = new Object[]{fdevicename, devicename, timePeriod.getStartTime(), timePeriod.getEndTime(),templateId};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        termdevService.findTermdevHistoryStatusByPage(page, conditions);
        List templateList = templateService.findAllMonitorTermdevTemplate();

        request.setAttribute("termdevHistoryStatus", page);
        request.setAttribute("templateList", templateList);

        return mapping.findForward("success");
    }

    public ActionForward viewTermdeviceHistoryStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceId = (String) ((DynaActionForm) form).get("deviceId");
        String state = (String) ((DynaActionForm) form).get("state");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        Object[] conditions = new Object[]{Integer.valueOf(deviceId), state, timePeriod.getStartTime(), timePeriod.getEndTime()};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        termdevService.findMonitorTermdevchecksByPage(page, conditions);

        StateDecorator termdeviceStatusDecorator = DecoratorFactory.getTermdeviceStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();
        request.setAttribute("monitorTermdevchecks", page);
        request.setAttribute("termdeviceStatusDecorator", termdeviceStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);

        return mapping.findForward("view");
    }

    public ActionForward viewTermdeviceHistoryChart(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        String deviceId = (String) ((DynaActionForm) form).get("deviceId");
        String timePeriodId = (String) ((DynaActionForm) form).get("timePeriodId");
        if (StringUtils.isBlank(timePeriodId)) {
            //默认显示今天的状态历史
            timePeriodId = "0";
        }
        TimePeriod timePeriod = new TimePeriod(Integer.parseInt(timePeriodId));
        String devicename = termdevService.getTDeviceName(Integer.valueOf(deviceId));
        List list = termdevService.findMonitorTermdevchecks(Integer.valueOf(deviceId), timePeriod.getStartTime(), timePeriod.getEndTime());
        Object[][] data = ResultUtil.transformMonitorTermdevchecks(list, timePeriod.getStartTime(), timePeriod.getEndTime());
        Chart chart = StateChartFactory.getStateBarChart(devicename, data, 800, 320, StateChartFactory.TERMDEVICE_TYPE, timePeriod.getType());
        ChartRenderingInfo info = new ChartRenderingInfo();

        JFreeChart freeChart = chart.getChart();
        String filename = ServletUtilities.saveChartAsPNG(freeChart, 800, 320, info, request.getSession());
        ImageMapUtil.writeImageMap(response.getWriter(), filename, info, false);
        request.setAttribute("filename", filename);

        return mapping.findForward("chart");
    }
}

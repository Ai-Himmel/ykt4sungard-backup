package org.king.common.chart;

import java.awt.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Locale;

/**
 * .生成状态图
 * User: Yiming.You
 * Date: 2010-8-11
 */
public class StateChartFactory {
    //配置每个状态对应的名称，用于显示在y轴上
    public static String[] HOST_STATUS_ALIAS = new String[]{"", "up", "down", "unreachable", "pending"};
    public static String[] SERVICE_STATUS_ALIAS = new String[]{"", "ok", "warning", "critical", "unknow", "pending"};
    public static String[] TERMDEVICE_STATUS_ALIAS = new String[]{"", "up", "down", "unreachable"};
    public static String[] TERMDEVSERVICE_STATUS_ALIAS = new String[]{"", "ok", "warning", "critical"};

    //配置每种状态对应的颜色
    public static Paint[] HOST_STATUS_PAINTS = new Paint[]{Color.GRAY, Color.GREEN, getColor("#FE3E00"), getColor("#F9A810"), Color.CYAN};
    public static Paint[] SERVICE_STATUS_PAINTS = new Paint[]{Color.GRAY, Color.GREEN, getColor("#F9A810"), getColor("#FE3E00"), getColor("#B1C9D3"), Color.CYAN};
    public static Paint[] TERMDEVICE_STATUS_PAINTS = new Paint[]{Color.GRAY, Color.GREEN, getColor("#FE3E00"), getColor("#F9A810")};
    public static Paint[] TERMDEVSERVICE_STATUS_PAINTS = new Paint[]{Color.GRAY, Color.GREEN, getColor("#F9A810"), getColor("#FE3E00")};

    //状态图类型，包括主机状态图，服务状态图，设备状态图，设备服务状态图
    public static int HOST_TYPE = 0;
    public static int SERVICE_TYPE = 1;
    public static int TERMDEVICE_TYPE = 2;
    public static int TERMDEVSERVICE_TYPE = 3;

    public static final DateFormat HOUR_FORMAT = new SimpleDateFormat("HH:mm", Locale.ENGLISH);

    public static final DateFormat DAY_FORMAT = new SimpleDateFormat("yyyy-MM-dd", Locale.ENGLISH);

    public static final DateFormat MONTH_FORMAT = new SimpleDateFormat("yyyy-MM", Locale.ENGLISH);

    public static Color getColor(String str) {
        int i = Integer.parseInt(str.substring(1), 16);
        return new Color(i);
    }

    /**
     * 生成时间域状态柱形图
     *
     * @param chartName 图名称
     * @param data      图的数据源
     * @param width     图宽度
     * @param height    图高度
     * @param type      图类型
     * @return .
     */
    public static Chart getStateBarChart(String chartName, Object[][] data, int width, int height, int type, int timePeriodType) {
        StateBarChart stateBarChart = new StateBarChart(chartName, width, height);
        stateBarChart.setData(data);
        if (timePeriodType >= 0 && timePeriodType <= 2) {
            stateBarChart.setDateFormat(HOUR_FORMAT);
            stateBarChart.setHourTickUnit(3);
        } else if (timePeriodType >= 3 && timePeriodType <= 8) {
            stateBarChart.setDateFormat(DAY_FORMAT);
            stateBarChart.setDayTickUnit(2);
        } else if (timePeriodType >= 9) {
            stateBarChart.setDateFormat(MONTH_FORMAT);
            stateBarChart.setMonthTickUnit(1);
        }
        
        switch (type) {
            case 0:
                stateBarChart.setStates(HOST_STATUS_ALIAS);
                stateBarChart.setPaints(HOST_STATUS_PAINTS);
                break;
            case 1:
                stateBarChart.setStates(SERVICE_STATUS_ALIAS);
                stateBarChart.setPaints(SERVICE_STATUS_PAINTS);
                break;
            case 2:
                stateBarChart.setStates(TERMDEVICE_STATUS_ALIAS);
                stateBarChart.setPaints(TERMDEVICE_STATUS_PAINTS);
                break;
            case 3:
                stateBarChart.setStates(TERMDEVSERVICE_STATUS_ALIAS);
                stateBarChart.setPaints(TERMDEVSERVICE_STATUS_PAINTS);
                break;
        }
        stateBarChart.setUpperBound(stateBarChart.getStates().length);
        return stateBarChart;
    }

    /**
     * 生成时间域状态柱形图
     *
     * @param chartName 图名称
     * @param data      图的数据源
     * @param width     图宽度
     * @param height    图高度
     * @param type      图类型
     * @return .
     */
    public static Chart getStatePieChart(String chartName, Object[][] data, int width, int height, int type) {
        StatePieChart statePieChart = new StatePieChart(chartName, width, height);
        statePieChart.setData(data);
        switch (type) {
            case 0:
                statePieChart.setStates(HOST_STATUS_ALIAS);
                statePieChart.setPaints(HOST_STATUS_PAINTS);
                statePieChart.setExplodeKey(HOST_STATUS_ALIAS[2]);
                break;
            case 1:
                statePieChart.setStates(SERVICE_STATUS_ALIAS);
                statePieChart.setPaints(SERVICE_STATUS_PAINTS);
                statePieChart.setExplodeKey(SERVICE_STATUS_ALIAS[4]);
                break;
            case 2:
                statePieChart.setStates(TERMDEVICE_STATUS_ALIAS);
                statePieChart.setPaints(TERMDEVICE_STATUS_PAINTS);
                statePieChart.setExplodeKey(TERMDEVICE_STATUS_ALIAS[2]);
                break;
            case 3:
                statePieChart.setStates(TERMDEVSERVICE_STATUS_ALIAS);
                statePieChart.setPaints(TERMDEVSERVICE_STATUS_PAINTS);
                statePieChart.setExplodeKey(TERMDEVSERVICE_STATUS_ALIAS[3]);
                break;
        }
        return statePieChart;
    }
}

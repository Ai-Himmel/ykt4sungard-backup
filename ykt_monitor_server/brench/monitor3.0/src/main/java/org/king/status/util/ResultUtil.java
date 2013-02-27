package org.king.status.util;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.host.domain.MonitorHostchecks;
import org.king.hostservice.domain.MonitorServiceCheck;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.utils.DateUtil;

import java.text.ParseException;
import java.util.Date;
import java.util.List;


/**
 * .
 * User: Yiming.You
 * Date: 2010-8-11
 */
public class ResultUtil {

    private static final Logger logger = Logger.getLogger(ResultUtil.class);


    /**
     * transform query result of MonitorHostchecks into a two-dimensional array
     * the method will be used when we draw the host status chart,and the return value is the datasource for the chart
     *
     * @param list .
     * @return .
     */
    public static Object[][] transformMonitorHostchecks(List list, Date startTime, Date endTime) throws ParseException {
        Date now = new Date();
        if (list == null || list.size() == 0) {
            return new Object[0][];
        }
        Object[][] result = new Object[list.size()][3];
        for (int i = 0; i < list.size(); i++) {
            MonitorHostchecks monitorHostchecks = (MonitorHostchecks) list.get(i);
            Date rowStartTime = DateUtil.getDate(monitorHostchecks.getStartTime());
            Date rowEndTime;
            if (StringUtils.isEmpty(monitorHostchecks.getEndTime())) {
                rowEndTime = now;
            } else {
                rowEndTime = DateUtil.getDate(monitorHostchecks.getEndTime());
            }
            if (rowStartTime.getTime() < startTime.getTime()) {
                result[i][0] = startTime;
            } else {
                result[i][0] = rowStartTime;
            }
            if (rowEndTime.getTime() > endTime.getTime()) {
                result[i][1] = endTime;
            } else {
                result[i][1] = rowEndTime;
            }

            //here we increase the state,mainly because we want to show the bar when the state is 0
            result[i][2] = monitorHostchecks.getState() + 1;
        }
        return result;
    }

    public static Object[][] transformMonitorServiceCheck(List list, Date startTime, Date endTime) throws ParseException {
        Date now = new Date();
        if (list == null || list.size() == 0) {
            return new Object[0][];
        }
        Object[][] result = new Object[list.size()][3];
        for (int i = 0; i < list.size(); i++) {
            MonitorServiceCheck monitorServiceCheck = (MonitorServiceCheck) list.get(i);
            Date rowStartTime = DateUtil.getDate(monitorServiceCheck.getStartTime());
            Date rowEndTime;
            if (StringUtils.isEmpty(monitorServiceCheck.getEndTime())) {
                rowEndTime = now;
            } else {
                rowEndTime = DateUtil.getDate(monitorServiceCheck.getEndTime());
            }
            if (rowStartTime.getTime() < startTime.getTime()) {
                result[i][0] = startTime;
            } else {
                result[i][0] = rowStartTime;
            }
            if (rowEndTime.getTime() > endTime.getTime()) {
                result[i][1] = endTime;
            } else {
                result[i][1] = rowEndTime;
            }

            //here we increase the state,mainly because we want to show the bar when the state is 0
            result[i][2] = monitorServiceCheck.getState() + 1;
        }
        return result;
    }

    public static Object[][] transformMonitorTermdevchecks(List list, Date startTime, Date endTime) throws ParseException {
        Date now = new Date();
        if (list == null || list.size() == 0) {
            return new Object[0][];
        }
        Object[][] result = new Object[list.size()][3];
        for (int i = 0; i < list.size(); i++) {
            MonitorTermdevchecks monitorTermdevchecks = (MonitorTermdevchecks) list.get(i);
            Date rowStartTime = DateUtil.getDate(monitorTermdevchecks.getStartTime());
            Date rowEndTime;
            if (StringUtils.isEmpty(monitorTermdevchecks.getEndTime())) {
                rowEndTime = now;
            } else {
                rowEndTime = DateUtil.getDate(monitorTermdevchecks.getEndTime());
            }
            if (rowStartTime.getTime() < startTime.getTime()) {
                result[i][0] = startTime;
            } else {
                result[i][0] = rowStartTime;
            }
            if (rowEndTime.getTime() > endTime.getTime()) {
                result[i][1] = endTime;
            } else {
                result[i][1] = rowEndTime;
            }

            //here we increase the state,mainly because we want to show the bar when the state is 0
            result[i][2] = monitorTermdevchecks.getState() + 1;
        }
        return result;
    }

    /**
     * 对主机状态结果，服务状态结果，设备状态结果，设备服务状态结果进行统计，计算出总数量和异常数量
     *
     * @param hostStatusResult           .
     * @param serviceStatusResult        .
     * @param termdeviceStatusResult     .
     * @param termdevserviceStatusResult .
     * @return .
     */
    public static String[][] caculateUnusual(String[][] hostStatusResult, String[][] serviceStatusResult, String[][] termdeviceStatusResult, String[][] termdevserviceStatusResult) {
        String[][] result = new String[4][2];
        result[0] = caculateUnusual(hostStatusResult);
        result[1] = caculateUnusual(serviceStatusResult);
        result[2] = caculateUnusual(termdeviceStatusResult);
        result[3] = caculateUnusual(termdevserviceStatusResult);
        return result;
    }

    private static String[] caculateUnusual(String[][] statusResult) {
        int total = 0;
        int unusual = 0;
        int value = 0;
        for (int i = 0; i < statusResult.length; i++) {
            value = Integer.parseInt(statusResult[i][1]);
            total += value;
            if ("up".equalsIgnoreCase(statusResult[i][0]) || "ok".equalsIgnoreCase(statusResult[i][0]) || "pending".equalsIgnoreCase(statusResult[i][0])) {
                //normal,do nothing
            } else {
                //unusual
                unusual += value;
            }
        }
        return new String[]{String.valueOf(total), String.valueOf(unusual)};
    }
}

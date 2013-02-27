package org.king.template.util;

import org.king.template.domain.MonitorTimePeriods;
import org.king.template.domain.MonitorTimeranger;

import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-8
 */
public class TimePeriodsUtil {
    private static String[] DAY_OF_WEEK = new String[]{"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};

    /**
     * 为一个新的MonitorTimePeriods对象初始化Timerangers对象
     *
     * @return .
     */
    public static List initTimerangerVO(MonitorTimePeriods monitorTimePeriods) {
        List result = new TimerangerList();
        for (int i = 0; i < DAY_OF_WEEK.length; i++) {
            TimerangerVO timerangerVO = new TimerangerVO();
            timerangerVO.setDayAlias(DAY_OF_WEEK[i]);

            MonitorTimeranger monitorTimeranger = new MonitorTimeranger();
            monitorTimeranger.setTimeperiodDay(Integer.valueOf(i));
            monitorTimeranger.setStartTime("0000");
            monitorTimeranger.setEndTime("0000");
            monitorTimeranger.setMonitorTimePeriods(monitorTimePeriods);

            timerangerVO.setMonitorTimeranger(monitorTimeranger);

            result.add(timerangerVO);
        }
        return result;
    }

    /**
     * 将Timeranger对象的集合转换成vo对象
     *
     * @param set .
     * @return .
     */
    public static List convertTimerangerVO(Set set) {
        List result = new TimerangerList();
        if (set != null) {
            for (Iterator iterator = set.iterator(); iterator.hasNext();) {
                MonitorTimeranger monitorTimeranger = (MonitorTimeranger) iterator.next();
                TimerangerVO timerangerVO = new TimerangerVO();
                timerangerVO.setMonitorTimeranger(monitorTimeranger);
                timerangerVO.setDayAlias(DAY_OF_WEEK[monitorTimeranger.getTimeperiodDay().intValue()]);
                result.add(timerangerVO);
            }
        }
        return result;
    }

    /**
     * 将vo对象的集合转换成Timeranger对象
     *
     * @param list               .
     * @param monitorTimePeriods
     * @return .
     */
    public static Set convertTimeranger(List list, MonitorTimePeriods monitorTimePeriods, boolean isNew) {
        Set result = new HashSet();
        if (list != null) {
            for (Iterator iterator = list.iterator(); iterator.hasNext();) {
                TimerangerVO timerangerVO = (TimerangerVO) iterator.next();

                timerangerVO.getMonitorTimeranger().setMonitorTimePeriods(monitorTimePeriods);
                if (isNew) {
                    timerangerVO.getMonitorTimeranger().setTimerangerId(null);
                }
                result.add(timerangerVO.getMonitorTimeranger());
            }
        }
        return result;
    }

    public static void main(String[] args) {
        Set result = new HashSet();
        MonitorTimeranger timerangerVO = new MonitorTimeranger();
        MonitorTimeranger timerangerVO1 = new MonitorTimeranger();
        MonitorTimeranger timerangerVO2 = new MonitorTimeranger();
        MonitorTimeranger timerangerVO3 = new MonitorTimeranger();
        result.add(timerangerVO);
        result.add(timerangerVO1);
        result.add(timerangerVO2);
        result.add(timerangerVO3);
        System.out.println("result.size() = " + result.size());
    }
}

package org.king.template.util;

import org.king.template.domain.MonitorTimeranger;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-8
 */
public class TimerangerVO {
    /**
     * timeperiodDay的中文名
     */
    private String dayAlias;

    private MonitorTimeranger monitorTimeranger;

    public String getDayAlias() {
        return dayAlias;
    }

    public void setDayAlias(String dayAlias) {
        this.dayAlias = dayAlias;
    }

    public MonitorTimeranger getMonitorTimeranger() {
        return monitorTimeranger;
    }

    public void setMonitorTimeranger(MonitorTimeranger monitorTimeranger) {
        this.monitorTimeranger = monitorTimeranger;
    }
}

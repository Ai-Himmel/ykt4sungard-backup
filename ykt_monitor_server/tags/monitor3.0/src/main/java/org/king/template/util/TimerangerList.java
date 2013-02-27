package org.king.template.util;

import org.king.template.domain.MonitorTimeranger;

import java.util.ArrayList;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-8
 */
public class TimerangerList extends ArrayList {
    @Override
    public Object get(int index) {
        while (index >= this.size()) {
            TimerangerVO timerangerVO = new TimerangerVO();
            MonitorTimeranger monitorTimeranger = new MonitorTimeranger();
            timerangerVO.setMonitorTimeranger(monitorTimeranger);
            this.add(timerangerVO);
        }
        return super.get(index);
    }
}

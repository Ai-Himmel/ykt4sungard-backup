package org.king.status.util;

import org.apache.commons.lang.time.DateUtils;

import java.util.Calendar;
import java.util.Date;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-13
 */
public class TimePeriod {
    private static final int TODAY = 0;
    private static final int LAST_24_HOURS = 1;
    private static final int YESTERDAY = 2;
    private static final int THIS_WEEK = 3;
    private static final int LAST_7_DAYS = 4;
    private static final int LAST_WEEK = 5;
    private static final int THIS_MONTH = 6;
    private static final int LAST_31_DAYS = 7;
    private static final int LAST_MONTH = 8;
    private static final int THIS_YEAR = 9;
    private static final int LAST_YEAR = 10;

    private Date startTime;

    private Date endTime;

    private int type;

    public TimePeriod(int type) {
        this.type = type;
        init();
    }

    public void init() {
        Date now = new Date();
        switch (type) {
            case LAST_24_HOURS:
                setStartTime(DateUtils.addDays(now, -1));
                setEndTime(now);
                break;
            case YESTERDAY:
                //the start date is yesterday 00:00,and the end date is today 00:00
                setStartTime(DateUtils.addDays(DateUtils.truncate(now, Calendar.DAY_OF_MONTH), -1));
                setEndTime(DateUtils.truncate(now, Calendar.DAY_OF_MONTH));
                break;
            case THIS_WEEK:
                setStartTime(getFirstDayOfWeek());
                setEndTime(now);
                break;
            case LAST_7_DAYS:
                setStartTime(DateUtils.addDays(now, -7));
                setEndTime(now);
                break;
            case LAST_WEEK:
                setStartTime(DateUtils.addDays(getFirstDayOfWeek(), -7));
                setEndTime(getFirstDayOfWeek());
                break;
            case THIS_MONTH:
                setStartTime(DateUtils.truncate(now, Calendar.MONTH));
                setEndTime(now);
                break;
            case LAST_31_DAYS:
                setStartTime(DateUtils.addDays(now, -31));
                setEndTime(now);
                break;
            case LAST_MONTH:
                setStartTime(DateUtils.addMonths(DateUtils.truncate(now, Calendar.MONTH), -1));
                setEndTime(DateUtils.truncate(now, Calendar.MONTH));
                break;
            case THIS_YEAR:
                setStartTime(DateUtils.truncate(now, Calendar.YEAR));
                setEndTime(now);
                break;
            case LAST_YEAR:
                setStartTime(DateUtils.addYears(DateUtils.truncate(now, Calendar.YEAR), -1));
                setEndTime(DateUtils.truncate(now, Calendar.YEAR));
                break;
            default:
                setStartTime(DateUtils.truncate(now, Calendar.DAY_OF_MONTH));
                setEndTime(now);

        }
    }

    public Date getFirstDayOfWeek() {
        Calendar calendar = Calendar.getInstance();
        int dayOfWeek = calendar.get(Calendar.DAY_OF_WEEK);
        //we try to accord with chinese custom,so the first day of a week is monday,not sunday
        if (dayOfWeek == 1) {
            //on sunday
            calendar.add(Calendar.DAY_OF_MONTH, -6);
        } else {
            calendar.add(Calendar.DAY_OF_MONTH, 2 - dayOfWeek);
        }
        return DateUtils.truncate(calendar.getTime(), Calendar.DAY_OF_MONTH);
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public Date getStartTime() {
        return startTime;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }

    public Date getEndTime() {
        return endTime;
    }

    public void setEndTime(Date endTime) {
        this.endTime = endTime;
    }

    public static void main(String[] args) {
        TimePeriod timePeriod = new TimePeriod(5);
        System.out.println(timePeriod.getStartTime());
        System.out.println(timePeriod.getEndTime());
    }
}

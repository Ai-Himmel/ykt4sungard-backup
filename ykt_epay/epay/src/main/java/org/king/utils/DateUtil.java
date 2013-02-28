package org.king.utils;

import org.apache.log4j.Logger;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * 日期处理类
 */
public class DateUtil {

    private static final Logger logger = Logger.getLogger(DateUtil.class);

    /**
     * 返回一个当前时间
     *
     * @return 格式：yyyyMMddHHmmss
     */
    public static String getNow() {
        if (logger.isDebugEnabled()) {
            logger.debug("getNow() - start"); //$NON-NLS-1$
        }

        java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyyMMddHHmmss");
        String returnString = sdf.format(new Date());
        if (logger.isDebugEnabled()) {
            logger.debug("getNow() - end"); //$NON-NLS-1$
        }
        return returnString;
    }

    /**
     * 根据类型返回一个当前时间
     *
     * @param partten .
     * @return .
     */
    public static String getNow(String partten) {
        if (logger.isDebugEnabled()) {
            logger.debug("getNow() - start"); //$NON-NLS-1$
        }

        java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(partten);
        String returnString = sdf.format(new Date());
        if (logger.isDebugEnabled()) {
            logger.debug("getNow() - end"); //$NON-NLS-1$
        }
        return returnString;
    }

    /**
     * 得到一个特殊的时间
     *
     * @param startTime 格式：yyyyMMddHHmmss
     * @param interval  秒
     * @return 新时间
     */
    public static String getNewTime(String startTime, int interval) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyyMMddHHmmss");
            Date d = sdf.parse(startTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            calendar.add(Calendar.SECOND, interval);
            return sdf.format(calendar.getTime());
        } catch (ParseException e) {
            return startTime;
        }
    }

    /**
     * 根据时间形式，得到加上间隙时间后的第二个时间
     *
     * @param startTime .
     * @param interval  .
     * @param partten   .
     * @return .
     */
    public static String getNewTimes(String startTime, int interval, String partten) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(partten);
            Date d = sdf.parse(startTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            calendar.add(Calendar.SECOND, interval);
            return sdf.format(calendar.getTime());
        } catch (ParseException e) {
            return startTime;
        }
    }
    
    /**
     * 获取 endTime 前几天的时间
     * @param endTime
     * @param days
     * @param partten
     * @return
     */
    public static String getLastDays(String endTime, int days, String partten) {  
    	try {
    		java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(partten);
            Date d = sdf.parse(endTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            long rightnow = calendar.getTimeInMillis();   
           long daysbefore = days * 24 * 60 * 60 * 1000;   
           return sdf.format(rightnow - daysbefore);   
		} catch (Exception e) {
			 return endTime;
		}
    	 
    	   }   


    /**
     * 得到两个时间字符串之间的间隙时间
     *
     * @param firstTime  .
     * @param secondTime .
     * @return .
     */
    public static long getIntervalTime(String firstTime, String secondTime) {
        long time = 000000000;
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyyMMddHHmmss");
            Date f = sdf.parse(firstTime);
            Date s = sdf.parse(secondTime);
            time = f.getTime() - s.getTime();
            return time;
        } catch (ParseException e) {
            return time;
        }
    }

    /**
     * 比较两个时间字符串的时间差
     *
     * @param firstTime  格式：yyyyMMddHHmmss
     * @param secondTime 格式: yyyyMMddHHmmss
     * @param seconds    .
     * @return firstTime+seconds=secondTime int=0,firstTime+seconds>secondTime int>0,firstTime+seconds<secondTime int<0
     */
    public static int checkIntervalTime(String firstTime, String secondTime, int seconds) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyyMMddHHmmss");
            Date f = sdf.parse(firstTime);
            Date s = sdf.parse(secondTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(f.getTime());
            calendar.add(Calendar.SECOND, seconds);
            Date temp = calendar.getTime();
            return temp.compareTo(s);
        } catch (Exception e) {
            return 0;
        }
    }

    public static int getDayofWeek() {
        Calendar calendar = Calendar.getInstance();
        return calendar.get(Calendar.DAY_OF_WEEK);
    }

    public static String reFormatTime(String time) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyyMMddHHmmss");
            Date d = sdf.parse(time);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
            return sdf.format(calendar.getTime());
        } catch (Exception e) {
            e.printStackTrace();
            return time;
        }
    }
}

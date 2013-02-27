package org.king.utils;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: DateUtil.java
 * Description: TODO
 * Modify History（或Change Log）:
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-29     何林青
 * <p/>
 *
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class DateUtil {
    /**
     * Logger for this class
     */
    private static final Logger logger = Logger.getLogger(DateUtil.class);

    public static final String[] alias = new String[]{"d", "h", "m", "s", "ms"};

    public static final long[] duration = new long[]{86400000, 3600000, 60000, 1000, 1};

    private static final DateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmss");

    /*
      * Description: 返回一个当前时间 @return String 格式：yyyyMMddHHmmss @exception Modify
      * History:
      */

    public static String getNow() {
        if (logger.isDebugEnabled()) {
            logger.debug("getNow() - start"); //$NON-NLS-1$
        }

        java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                "yyyyMMddHHmmss");
        String returnString = sdf.format(new Date());
        if (logger.isDebugEnabled()) {
            logger.debug("getNow() - end"); //$NON-NLS-1$
        }
        return returnString;
    }

    /*
      * Description: 根据类型返回一个当前时间 @param partten String @return String 格式：partten
      * @exception Modify History:
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

    /*
      * Description: 得到一个特殊的时间 @param startTime String 格式：yyyyMMddHHmmss @param
      * interval int 秒 @return String 格式：partten @exception Modify History:
      */

    public static String getNewTime(String startTime, int interval) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    "yyyyMMddHHmmss");
            Date d = sdf.parse(startTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            calendar.add(Calendar.SECOND, interval);
            return sdf.format(calendar.getTime());
        } catch (ParseException e) {
            return startTime;
        }
    }

    /*
      * Description: 得到一个特殊的时间 @param startTime String 格式：yyMMddHHmmss @param
      * interval int 秒 @return String 格式：partten @exception Modify History:
      */

    public static String getSpecialNewTime(String startTime, int interval) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    "yyMMddHHmmss");
            Date d = sdf.parse(startTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            calendar.add(Calendar.SECOND, interval);
            return sdf.format(calendar.getTime());
        } catch (ParseException e) {
            return startTime;
        }
    }

    /*
      * Description: 根据时间形式，得到加上间隙时间后的第二个时间 @param startTime String 格式：partten
      * @param interval int 秒 @return String 格式：partten @exception Modify
      * History:
      */

    public static String getNewTimes(String startTime, int interval,
                                     String partten) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    partten);
            Date d = sdf.parse(startTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            calendar.add(Calendar.SECOND, interval);
            return sdf.format(calendar.getTime());
        } catch (ParseException e) {
            return startTime;
        }
    }

    /*
      * Description: 得到两个时间字符串之间的间隙时间 @param firstTime String 格式：yyyyMMddHHmmss
      * @param secondTime String 格式: yyyyMMddHHmmss @return long @exception
      * parseException Modify History:
      */

    public static long getIntervalTime(String firstTime, String secondTime) {
        long time = 000000000;
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    "yyyyMMddHHmmss");
            Date f = sdf.parse(firstTime);
            Date s = sdf.parse(secondTime);
            time = f.getTime() - s.getTime();
            return time;
        } catch (ParseException e) {
            // TODO: handle exception
            return time;
        }
    }

    /*
      * Description: 比较两个时间字符串的前后关系 @param firstTime String 格式：yyyyMMddHHmmss
      * @param secondTime String 格式: yyyyMMddHHmmss @return int |
      * firstTime=second int=0 | firstTime>secondTime int>0 | firstTime<secondTime
      * int<0 @exception Modify History:
      */

    public static int checkTimeSequence(String firstTime, String secondTime) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    "yyyyMMddHHmmss");
            Date f = sdf.parse(firstTime);
            Date s = sdf.parse(secondTime);
            return f.compareTo(s);
        } catch (ParseException e) {
            // TODO: handle exception
            return 0;
        }
    }
    /*
      * Description: 比较两个时间字符串的前后关系 @param firstTime String 格式：yyyyMMddHHmmss
      * @param secondTime String 格式: yyyyMMddHHmmss @return int |
      * firstTime=second int=0 | firstTime>secondTime int>0 | firstTime<secondTime
      * int<0 @exception Modify History:
      */

    public static int checkSpecialTimeSequence(String firstTime, String secondTime, String format) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(format);
            Date f = sdf.parse(firstTime);
            Date s = sdf.parse(secondTime);
            return f.compareTo(s);
        } catch (ParseException e) {
            // TODO: handle exception
            return 0;
        }
    }

    /*
      * Description: 比较两个时间字符串的时间差 @param firstTime String 格式：yyyyMMddHHmmss
      * @param secondTime String 格式: yyyyMMddHHmmss @param second int 格式 @return
      * int | firstTime+seconds=secondTime int=0 | firstTime+seconds>secondTime
      * int>0 | firstTime+seconds<secondTime int<0 @exception Modify History:
      */

    public static int checkIntervalTime(String firstTime, String secondTime,
                                        int seconds) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    "yyyyMMddHHmmss");
            Date f = sdf.parse(firstTime);
            Date s = sdf.parse(secondTime);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(f.getTime());
            calendar.add(Calendar.SECOND, seconds);
            Date temp = calendar.getTime();
            return temp.compareTo(s);
        } catch (Exception e) {
            // TODO: handle exception
            return 0;
        }
    }

    public static int getDayofWeek() {
        Calendar calendar = Calendar.getInstance();
        return calendar.get(Calendar.DAY_OF_WEEK);
    }

    public static String reFormatTime(String time) {
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
                    "yyyyMMddHHmmss");
            Date d = sdf.parse(time);
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(d.getTime());
            sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
            return sdf.format(calendar.getTime());
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            return time;
        }
    }

    /**
     * 将yyyyMMddHHmmss格式的字符串日期与当前时间比较,结果精确到秒
     *
     * @param startTime .
     * @return .
     * @throws ParseException .
     */
    public static String convertTime(String startTime) throws ParseException {
        return convertTime(startTime, "yyyyMMddHHmmss", 4);
    }

    /**
     * 将指定格式的字符串日期与当前时间比较
     *
     * @param startTime .
     * @param pattern   .
     * @param precision .
     * @return .
     * @throws ParseException .
     */
    public static String convertTime(String startTime, String pattern, int precision) throws ParseException {
        if (StringUtils.isBlank(startTime)) {
            return "";
        }
        SimpleDateFormat dateFormat = new java.text.SimpleDateFormat(pattern);
        Date startDate = dateFormat.parse(startTime);
        long interval = System.currentTimeMillis() - startDate.getTime();
        return convertTime(interval, duration, alias, precision);
    }

    /**
     * 将指定的毫秒数转换成对应的时间长度字符串
     *
     * @param interval  .
     * @param duration  .
     * @param alias     .
     * @param precision 精度，例如精确到天，该值为1，精确到毫秒，改值为5
     * @return
     */
    public static String convertTime(long interval, long[] duration, String[] alias, int precision) {
        StringBuffer result = new StringBuffer();
        for (int i = 0; i < precision; i++) {
            long div = interval / duration[i];
            interval = interval % duration[i];
            result.append(div).append(alias[i]).append(" ");
        }
        if (result.length() > 0) {
            result = result.deleteCharAt(result.length() - 1);
        }
        return result.toString();
    }

    /**
     * Description: string 格式的日期转换成java.util.Date格式的日期
     *
     * @param @param  datetime
     * @param @param  pattern
     * @param @return
     * @param @throws ParseException
     * @return Date
     *         Modify History: 2010-8-5 Linqing.He create
     */
    public static Date getDate(String datetime, String pattern) throws ParseException {
        SimpleDateFormat dateFormat = new java.text.SimpleDateFormat(pattern);
        Date startDate = dateFormat.parse(datetime);
        return startDate;
    }

    /**
     * 获得两个字符串日期之间的时间差(单位毫秒)
     *
     * @param startTime .
     * @param endTime   .
     * @return .
     */
    public static long getDuration(String startTime, String endTime) {
        long duration = 0;
        try {
            duration = dateFormat.parse(endTime).getTime() - dateFormat.parse(startTime).getTime();
        } catch (ParseException e) {
            logger.error("Hi guys,there is an error when you try to parse the date string");
        }
        return duration;
    }

    public static String formatDate(Date date) {
        return dateFormat.format(date);
    }

    public static Date getDate(String date) throws ParseException {
        return dateFormat.parse(date);
    }

    /**
     * 获取某一个时间段内的有效时间长度
     *
     * @param startTime .
     * @param endTime   .
     * @param minTime   .
     * @param maxTime   .
     * @return .
     */
    public static long getDuration(String startTime, String endTime, Date minTime, Date maxTime) {
        long duration = 0;
        try {
            long low = DateUtil.getDate(startTime).getTime();
            long high = DateUtil.getDate(endTime).getTime();
            if (low < minTime.getTime()) {
                low = minTime.getTime();
            }
            if (high > maxTime.getTime()) {
                high = maxTime.getTime();
            }
            duration = high - low;
        } catch (ParseException e) {
            logger.error("Hi guys,there is an error when you try to parse the date string");
        }
        return duration;
    }
    
	/**
	* Description: 
	* @param @param startTime
	* @param @param interval
	* @param @return
	* @return String
	* Modify History: 2010-9-10 Linqing.He create
	*/
	public static String getSpecialCardver(String startTime, int interval) {
		String time = startTime.substring(0, 6);
		String cardver = startTime.substring(6);

		int cardint = Integer.parseInt(cardver);
		cardint = cardint - interval;

		String cardnewver = "000000";

		if (cardint > 0) {
			cardnewver = "000000" + String.valueOf(cardint);
		}

		cardnewver = cardnewver.substring(cardnewver.length() - 6);

		return time + cardnewver;

	}
}

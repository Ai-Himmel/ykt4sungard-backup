package com.kingstargroup.utils;

import org.apache.log4j.Logger;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: DateUtil.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2005-10-16 何林青 返回一个日期格式yyyyMMddHHmmss的字符串（当前时间）
 * <p>
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

	/**
	* Description: 比较两个时间字符串的时间差
	* | firstTime+seconds=secondTime int=0 | firstTime+seconds>secondTimeint>0 | firstTime+seconds<secondTime int<0
	*@param firstTime String 格式：yyyyMMddHHmmss
	*@param secondTime String 格式: yyyyMMddHHmmss
	*@param seconds int
	*@return 
	* @return Modify History: 2006-7-17 jackey create
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

}

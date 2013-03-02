/**
 * 
 */
package com.kingstargroup.ecard.util;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import com.kingstargroup.ecard.exceptions.DateTimeFormatException;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: DateFormatUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-3  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DateFormatUtil {
	public static String format(String unformatStr) throws DateTimeFormatException {
		return format(unformatStr, "-", ":");
	}
	
	public static String format(String unformatStr, String dateSeparator) throws DateTimeFormatException {
		return format(unformatStr, dateSeparator, "");
	}
	
	public static String format(String unformatStr, String dateSeparator, String timeSeparator) throws DateTimeFormatException {
		if (unformatStr == null) {
			throw new DateTimeFormatException("can not format the given string");
		}
		int length = unformatStr.length();
		if (length != 8 && length != 14) {
			throw new DateTimeFormatException("can not format the given string");
		}
		if (length == 8) {
			return formatDate(unformatStr, dateSeparator);
		} else {
			return formatDateTime(unformatStr, dateSeparator, timeSeparator);
		}
	}
	
	public static String getDateOfFirstWeekDay() {
		Calendar calendar = Calendar.getInstance();
		calendar.set(calendar.DAY_OF_WEEK, calendar.getFirstDayOfWeek());
		SimpleDateFormat format = new SimpleDateFormat("yyyy/MM/dd");
		return format.format(calendar.getTime());	
		
	}
	
	public static String getDateOfLastWeekDay() {
		Calendar calendar = Calendar.getInstance();
		calendar.set(calendar.DAY_OF_WEEK, 7);
		SimpleDateFormat format = new SimpleDateFormat("yyyy/MM/dd");
		return format.format(calendar.getTime());		
	}
	
	public static String getNowDate(){
		SimpleDateFormat format = new SimpleDateFormat("yyyy/MM/dd");
		String nowDate = format.format(new Date());
		return nowDate;
	}
	
	public static String getDateLaterNow(){
		Date nowDate;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy/MM/dd");
		Calendar c = Calendar.getInstance();
		c.setTimeInMillis(getMillis(new Date()) - ((long) 7) * 24 * 3600 * 1000);
		nowDate = c.getTime();
		String nowTime = sdf.format(nowDate);
		return nowTime;
		
	}
	public static long getMillis(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.getTimeInMillis();
	}

	
	static String formatDate(String unformatDate, String dateSeparator) throws DateTimeFormatException {
		try {
			SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");
			Date d = format.parse(unformatDate);
			StringBuffer pattern = new StringBuffer();
			pattern.append("yyyy")
					.append(dateSeparator)
					.append("MM")
					.append(dateSeparator)
					.append("dd");
			format.applyPattern(pattern.toString());
			return format.format(d);

		} catch (Exception e) {
			throw new DateTimeFormatException("can not format the given string");
		}
	}
	
	static String formatDateTime(String unformatDateTime, String dateSeparator, String timeSeparator) throws DateTimeFormatException {
		try {
			SimpleDateFormat format = new SimpleDateFormat("yyyyMMddHHmmss");
			Date d = format.parse(unformatDateTime);
			StringBuffer pattern = new StringBuffer();
			pattern.append("yyyy")
					.append(dateSeparator)
					.append("MM")
					.append(dateSeparator)
					.append("dd")
					.append(" ")
					.append("HH")
					.append(timeSeparator)
					.append("mm")
					.append(timeSeparator)
					.append("ss");
			format.applyPattern(pattern.toString());
			return format.format(d);

		} catch (Exception e) {
			throw new DateTimeFormatException("can not format the given string");
		}
	}
	
	public static boolean isHotInfo(Date d) {
		Calendar calendar = Calendar.getInstance();
		calendar.set(Calendar.HOUR, -12 * EcardConstants.HOT_INFORMATION_INTERVAL);
		SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");		
		int aday = Integer.parseInt(format.format(calendar.getTime()));
		int bday =  Integer.parseInt(format.format(d));
		if (aday <= bday) {
			return true;
		}
		return false;
	}
}

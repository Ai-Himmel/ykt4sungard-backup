/**
 * 
 */
package com.kingstargroup.mobileMessage.util;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

/**
 * 和日期相关的扩展函数
 * 
 * @author Administrator
 * 
 */
public class DateUtilExtend {
	static private SimpleDateFormat simpleFormat = new SimpleDateFormat(
			"yyyyMMdd");

	static private SimpleDateFormat simpleFormat2 = new SimpleDateFormat("yyyyMMddHHmmss");
	/**
	 * 以指定的格式来格式化日期
	 * @param dateDate
	 * @param formatString
	 * @return String
	 */
	public String formatDateByFormat(Date date, String format) {
		String result = "";
		if (date != null) {
			try {
				SimpleDateFormat sdf = new SimpleDateFormat(format);
				result = sdf.format(date);
			} catch (Exception ex) {
				// Logger.info("date:" + date);
				ex.printStackTrace();
			}
		}
		return result;
	}

	/**
	 * 常用的格式化日期
	 * 
	 * @param date
	 *            Date
	 * @return String
	 */
	public String formatDate(Date date) {
		return formatDateByFormat(date, "yyyy-MM-dd");
	}
	
	/**
	 * 格式化日期，传入格式：yyyymmdd，输出格式yyyy年mm月dd日
	 * @param date
	 * @return
	 */
	public static String formatDateSelf(String indate){
		String year;
		String month;
		String day;
		if ((null==indate)||("".equals(indate))){
			return "";
		}else{
			year = indate.substring(0,4);
			month = indate.substring(4,6);
			day = indate.substring(6,8);
			return year+"年"+month+"月"+day+"日";
		}
	}
	/**
	 * 格式化时间，传入格式：hhmmss，输出格式hh点mm分
	 * @param date
	 * @return
	 */
	public static String formatTimeSelf(String intime){
		String hour;
		String min;
		if ((null==intime)||("".equals(intime))){
			return "";
		}else{
			hour = intime.substring(0,2);
			min = intime.substring(2,4);
			//String sec = time.substring(4,2);
			return hour+"点"+min+"分";
		}
		
	}

	/**
	 * 返回小时，输入格式hhmmss，输出格式hh
	 * @param time
	 * @return
	 */
	public static String getHour(String time){
		if ((null==time)||("".equals(time))){
			return "00";
		}else{
			return time.substring(0,2);
		}
	}
	/**
	 * 返回分钟，输入格式hhmmss，输出格式mm
	 * @param time
	 * @return
	 */
	public static String getMin(String time){
		if ((null==time)||("".equals(time))){
			return "00";
		}else{
			return time.substring(2,4);
		}
	}
	/**
	 * 格式化日期，输入格式yyyy-mm-dd,输出格式yyyymmdd
	 * @param date
	 * @return
	 */
	public static String formatDate2(String date) {
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					"yyyy-MM-dd");
			Date d = sdf.parse(date);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			sdf = new SimpleDateFormat("yyyyMMdd");
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			e.printStackTrace();
			return date;
		}
	}
	
	/**
	 * 格式化日期，输入格式yyyymmdd,输出格式yyyy-mm-dd
	 * @param date
	 * @return
	 */
	public static String formatDate3(String date) {
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					"yyyyMMdd");
			Date d = sdf.parse(date);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			sdf = new SimpleDateFormat("yyyy-MM-dd");
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			e.printStackTrace();
			return date;
		}
	}

	public String formatDate3(Date date) {
		return formatDateByFormat(date, "yyyyMMdd");
	}

	/**
	 * 返回年份
	 * @param date日期
	 * @return 返回年份
	 */
	public static int getYear(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.YEAR);
	}

	/**
	 * 返回月份
	 * @param date日期
	 * @return 返回月份
	 */
	public static int getMonth(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MONTH) + 1;
	}

	/**
	 * 返回日份
	 * @param date日期
	 * @return 返回日份
	 */
	public static int getDay(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.DAY_OF_MONTH);
	}

	/**
	 * 返回小时
	 * @param date日期
	 * @return 返回小时
	 */
	public static int getHour(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.HOUR_OF_DAY);
	}

	/**
	 * 根据输入的字符串格式化时间，返回格式hh:mm:ss
	 * 传入格式：hhmmss
	 * @param time
	 * @return
	 */
	public static String reFormatTime(String time) {
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					"HHmmss");
			Date d = sdf.parse(time);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			sdf = new SimpleDateFormat("HH:mm:ss");
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			e.printStackTrace();
			return time;
		}

	}

	/**
	 * 返回分钟
	 * @param date日期
	 * @return 返回分钟
	 */
	public static int getMinute(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MINUTE);
	}

	/**
	 * 返回秒钟
	 * @param date日期
	 * @return 返回秒钟
	 */
	public static int getSecond(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.SECOND);
	}

	/**
	 * 返回毫秒
	 * @param date日期
	 * @return 返回毫秒
	 */
	public static long getMillis(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.getTimeInMillis();
	}

	/**
	 * 日期相加
	 * @param date日期
	 * @param day天数
	 * @return 返回相加后的日期
	 */
	public static Date addDate(Date date, int day) {
		Calendar c = Calendar.getInstance();
		c.setTimeInMillis(getMillis(date) + ((long) day) * 24 * 3600 * 1000);
		return c.getTime();
	}

	public static String addDate2(String date, int day) {
		Calendar c = Calendar.getInstance();
		c.setTime(getStrToDate(date));
		c.add(Calendar.DATE, +day);
		return simpleFormat.format(c.getTime());
	}
	
	/*
	 * 分钟相加，输入格式hhmmss,输出格式hhmmss
	 */
	public static String addTime(String time,int min){
		SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		Date begin = null;
		String outTime = null;
		try {
			begin = sdf.parse(time);
			Calendar c = Calendar.getInstance();
			c.setTime(begin);
			c.add(Calendar.MINUTE,min);
			outTime = sdf.format(c.getTime());
		} catch (Exception e) {
			e.printStackTrace();
		}
		//SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		//String nowTime = sdf.format(new Date());
		return outTime;
	}

	/**
	 * 日期相减
	 * @param date日期
	 * @param date1日期
	 * @return 返回相减后的日期
	 */
	public static int diffDate(Date date, Date date1) {
		return (int) ((getMillis(date) - getMillis(date1)) / (24 * 3600 * 1000));
	}

	/**
	 * 返回当前日期，格式为2005-01-01
	 * @return
	 */
	public static String getNowDate() {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}

	/**
	 * 返回当前日期，格式为20050101
	 * @return
	 */
	public static String getNowDate2() {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}

	/**
	 * 返回当前时间，格式：hhmmss
	 * @return
	 */
	public static String getNowTime() {
		SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}

	/**
	 * 返回当前时间，格式：hhmm
	 * @return
	 */
	public static String getNowTime2() {
		SimpleDateFormat sdf = new SimpleDateFormat("HHmm");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}

	/**
	 * 得到两个日期的日期差
	 * 
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public static long diffDate(String beginDate, String endDate) {
		Date bDate = null;
		Date eDate = null;
		try {
			bDate = simpleFormat.parse(beginDate);
			eDate = simpleFormat.parse(endDate);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		Calendar t1 = Calendar.getInstance();
		Calendar t2 = Calendar.getInstance();
		t1.setTime(bDate);
		t2.setTime(eDate);
		long diff = (t2.getTimeInMillis() - t1.getTimeInMillis())
				/ (1000 * 60 * 60 * 24);

		return diff;
	}
	
	/**
	 * 得到时间差，时间传入格式：20060101101010（年月日时分秒）yyyymmddhhmmss
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public static long diffDate2(String beginDate, String endDate) {
		Date bDate = null;
		Date eDate = null;
		long time=000000000;
		try {
			bDate = simpleFormat2.parse(beginDate);
			eDate = simpleFormat2.parse(endDate);
			time = eDate.getTime()-bDate.getTime();
			return time;
		} catch (ParseException e) {
			e.printStackTrace();
			return time;
		}
	}
	
	/**
	 * 传入参数格式为：hhmmss
	 * 比较两个时间的差，返回值为分钟
	 * @param beginTime
	 * @param endTime
	 * @return
	 */
	public static long timeDiff1(String beginTime, String endTime) {
		SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		Date begin = null;
		Date end = null;
		try {
			begin = sdf.parse(beginTime);
			end = sdf.parse(endTime);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		long times = (end.getTime() - begin.getTime()) / (1000 * 60);
		return times;
	}

	/**
	 * 返回两个时间差，返回值为分钟
	 * 传入时间格式为hhmm
	 * @param beginTime
	 * @param endTime
	 * @return
	 */
	public static long timeDiff2(String beginTime, String endTime) {
		SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		Date begin = null;
		Date end = null;
		try {
			begin = sdf.parse(beginTime + "00");
			end = sdf.parse(endTime + "00");
		} catch (ParseException e) {
			e.printStackTrace();
		}
		long times = (end.getTime() - begin.getTime()) / (1000 * 60);
		return times;
	}

	public static Date getStrToDate(String strDate) {
		Date outDate = null;
		try {
			outDate = simpleFormat.parse(strDate);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return outDate;
	}

	/**
	 * 返回当前日期的后一个月的日期，格式：2005-01-01
	 * 
	 * @return
	 */
	public static String getDateLaterMonth() {
		Date nowDate;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		Calendar c = Calendar.getInstance();
		c.setTimeInMillis(getMillis(new Date()) - ((long) 30) * 24 * 3600
				* 1000);
		nowDate = c.getTime();
		String nowTime = sdf.format(nowDate);
		return nowTime;

	}

	/**
	 * 根据某一个日期得到该日期属于该年的第几周
	 * 传入参数格式：yyyymmdd
	 * @param date
	 * @return
	 */
	public static String getWeek(String date) {
		String week = "";
		Date myDate = null;
		try {
			myDate = simpleFormat.parse(date);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		Calendar c = Calendar.getInstance();
		c.setTime(myDate);
		if (Integer.toString(c.get(Calendar.WEEK_OF_YEAR)).length() == 1) {
			week = "0" + Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
		} else {
			week = Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
		}
		return Integer.toString(c.get(Calendar.YEAR)) + week;
	}
	
	/**   
     *   根据年月判断当前月的日期天数   
     *   @param   s   String   格式为   yyyy-MM的日期字符串   
     *   @return   int   当月天数   
     *   @throws   ParseException   
     */   
   public static int getDaysByMonth(String s) {
	   int dayNum = 0;
	   switch (Integer.parseInt(s.substring(5,7))){
	   case 2:
		   int year = Integer.parseInt(s.substring(0,4));
		   if((year%4==0&&year%100!=0)||(year%400==0)){
			   dayNum = 29;
		   }else{
			   dayNum = 28;
		   }
		   break;	   
	   case 4:
		   dayNum = 30;
		   break;	   
	   case 6:
		   dayNum = 30;
		   break;	   
	   case 9:
		   dayNum = 30;
		   break;	   
	   case 11:
		   dayNum = 30;
		   break;	   
		default:
			dayNum = 31;
			break;
	   }
	   return dayNum;
   }
   
	/**
	 * 根据日期字符串取得当前为星期几
	 * 传入日期格式为yyyymmdd
	 * @param strdate
	 * @return
	 */
	public static int getWeekByDate2(String strdate) {
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
		Date date = null;
		try {
			date = dateFormat.parse(strdate);
		} catch (ParseException e) {

		}
		Calendar cd = Calendar.getInstance();
		cd.setTime(date);
		int mydate = cd.get(Calendar.DAY_OF_WEEK);
		return mydate;
	}

	/**
	 * 根据日期字符串取得当前为星期几，1为星期一，...7为星期日
	 * 传入日期格式为yyyymmdd
	 * @param strdate
	 * @return
	 */
	public static String getWeekByDate(String strdate) {
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
		Date date = null;
		try {
			date = dateFormat.parse(strdate);
		} catch (ParseException e) {

		}
		Calendar cd = Calendar.getInstance();
		cd.setTime(date);
		int mydate = cd.get(Calendar.DAY_OF_WEEK);
		String showDate = "";
		switch (mydate) {
		case 1:
			showDate = "日";
			break;
		case 2:
			showDate = "一";
			break;
		case 3:
			showDate = "二";
			break;
		case 4:
			showDate = "三";
			break;
		case 5:
			showDate = "四";
			break;
		case 6:
			showDate = "五";
			break;
		default:
			showDate = "六";
			break;
		}

		return showDate;
	}
	
	public static String getCheckSign(int i){
		String sign = "";
		switch (i) {
		case 0:
			sign = "早";
			break;
		case 1:
			sign = "上";
			break;
		case 2:
			sign = "下";
			break;
		case 3:
			sign = "晚";
			break;
		default:
			break;
		}
		return sign;
	}

	public static String getCheckSign2(int i){
		String sign = "";
		switch (i) {
		case 0:
			sign = "mo-";
			break;
		case 1:
			sign = "am-";
			break;
		case 2:
			sign = "pm-";
			break;
		case 3:
			sign = "ni-";
			break;
		default:
			break;
		}
		return sign;
	}
	


	// 判断两个日期是否是同一周，根据一个给定的日期获得所属周的周一和周五的日期。
	public class ManageWeek {
		// 判断两个日期是否在同一周
		boolean isSameWeekDates(Date date1, Date date2) {
			Calendar cal1 = Calendar.getInstance();
			Calendar cal2 = Calendar.getInstance();
			cal1.setTime(date1);
			cal2.setTime(date2);
			int subYear = cal1.get(Calendar.YEAR) - cal2.get(Calendar.YEAR);
			if (0 == subYear) {
				if (cal1.get(Calendar.WEEK_OF_YEAR) == cal2
						.get(Calendar.WEEK_OF_YEAR))
					return true;
			} else if (1 == subYear && 11 == cal2.get(Calendar.MONTH)) {
				// 如果12月的最后一周横跨来年第一周的话则最后一周即算做来年的第一周
				if (cal1.get(Calendar.WEEK_OF_YEAR) == cal2
						.get(Calendar.WEEK_OF_YEAR))
					return true;
			} else if (-1 == subYear && 11 == cal1.get(Calendar.MONTH)) {
				if (cal1.get(Calendar.WEEK_OF_YEAR) == cal2
						.get(Calendar.WEEK_OF_YEAR))
					return true;
			}
			return false;
		}

		// 产生周序列
		public String getSeqWeek() {
			Calendar c = Calendar.getInstance(Locale.CHINA);
			String week = Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
			if (week.length() == 1)
				week = "0" + week;
			String year = Integer.toString(c.get(Calendar.YEAR));
			return year + week;

		}

		// 获得周一的日期
		public String getMonday(Date date) {
			Calendar c = Calendar.getInstance();
			c.setTime(date);
			c.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
			return new SimpleDateFormat("yyyy-MM-dd").format(c.getTime());
		}

		// 获得周五的日期
		public String getFriday(Date date) {
			Calendar c = Calendar.getInstance();
			c.setTime(date);
			c.set(Calendar.DAY_OF_WEEK, Calendar.FRIDAY);
			return new SimpleDateFormat("yyyy-MM-dd").format(c.getTime());

		}

	}

	// 根据周得到该周的开始日期和结束日期
	static public class WeekBeginEndDate {
		private static DateFormat formatter = new SimpleDateFormat("yyyyMMdd");

		public Date[] getStartEnd(int year, int weeknum) {
			/*
			 * 参数说明 int year 年分 例如 2005 int weeknum 第几周 例如33 返回一个Calendar数组，长度为2
			 * 分别是开始日期和结束日期
			 */
			Calendar calendar = Calendar.getInstance();
			calendar.set(Calendar.YEAR, year);
			calendar.set(Calendar.WEEK_OF_YEAR, weeknum);
			int nw = calendar.get(Calendar.DAY_OF_WEEK);
			calendar.add(Calendar.DATE, 1 - nw);
			Date start = calendar.getTime();
			// end.add(Calendar.DATE, 7 - nw);
			calendar.add(Calendar.DATE, 6);
			Date end = calendar.getTime();
			Date[] darr = new Date[] { start, end };
			return darr;
		}

		public String getFullTimeStr(Date d) {
			String ret = "";
			try {
				ret = formatter.format(d);
			} catch (Exception ex) {
				// 其他错误处理
			}
			return ret;
		}

		public String weekBeginEnd(int year, int weeknum, String beginDate,
				String endDate) {
			String result = "";
			Date[] darr = getStartEnd(year, weeknum);
			if ((getFullTimeStr(darr[0]).compareTo(beginDate) < 0)
					&& (getFullTimeStr(darr[1]).compareTo(endDate) > 0)) {
				result = beginDate + "-" + endDate;
			} else if ((getFullTimeStr(darr[0]).compareTo(beginDate) < 0)
					&& (getFullTimeStr(darr[1]).compareTo(endDate) < 0)) {
				result = beginDate + "-" + getFullTimeStr(darr[1]);
			} else if ((getFullTimeStr(darr[0]).compareTo(beginDate) > 0)
					&& (getFullTimeStr(darr[1]).compareTo(endDate) < 0)) {
				result = getFullTimeStr(darr[0]) + "-"
						+ getFullTimeStr(darr[1]);
			} else if ((getFullTimeStr(darr[0]).compareTo(beginDate) > 0)
					&& (getFullTimeStr(darr[1]).compareTo(endDate) > 0)) {
				result = getFullTimeStr(darr[0]) + "-" + endDate;
			}
			return result;
		}

		public void main(String[] args) {

		}
	}


}

/**
 * 
 */
package com.kingstargroup.conference.common;

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
	/**
	 * 以指定的格式来格式化日期
	 * 
	 * @param date
	 *            Date
	 * @param format
	 *            String
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
	 * 返回年份
	 * 
	 * @param date
	 *            日期
	 * @return 返回年份
	 */
	public static int getYear(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.YEAR);
	}

	/**
	 * 返回月份
	 * 
	 * @param date
	 *            日期
	 * @return 返回月份
	 */
	public static int getMonth(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MONTH) + 1;
	}

	/**
	 * 返回日份
	 * 
	 * @param date
	 *            日期
	 * @return 返回日份
	 */
	public static int getDay(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.DAY_OF_MONTH);
	}

	/**
	 * 返回小时
	 * 
	 * @param date
	 *            日期
	 * @return 返回小时
	 */
	public static int getHour(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.HOUR_OF_DAY);
	}

		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DateUtilExtend根据输入的字符串格式化时间<br>
		 * Return: String<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-19  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
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
	 * 
	 * @param date
	 *            日期
	 * @return 返回分钟
	 */
	public static int getMinute(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MINUTE);
	}

	/**
	 * 返回秒钟
	 * 
	 * @param date
	 *            日期
	 * @return 返回秒钟
	 */
	public static int getSecond(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.SECOND);
	}

	/**
	 * 返回毫秒
	 * 
	 * @param date
	 *            日期
	 * @return 返回毫秒
	 */
	public static long getMillis(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.getTimeInMillis();
	}

	/**
	 * 日期相加
	 * 
	 * @param date
	 *            日期
	 * @param day
	 *            天数
	 * @return 返回相加后的日期
	 */
	public static Date addDate(Date date, int day) {
		Calendar c = Calendar.getInstance();
		c.setTimeInMillis(getMillis(date) + ((long) day) * 24 * 3600 * 1000);
		return c.getTime();
	}

	/**
	 * 日期相减
	 * 
	 * @param date
	 *            日期
	 * @param date1
	 *            日期
	 * @return 返回相减后的日期
	 */
	public static int diffDate(Date date, Date date1) {
		return (int) ((getMillis(date) - getMillis(date1)) / (24 * 3600 * 1000));
	}
	
	/**
	 * 返回当前日期，格式为2005-01-01
	 * @return
	 */
	public static String getNowDate(){
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DateUtilExtend返回当前日期，格式为20050101<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-4  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static String getNowDate2(){
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DateUtilExtend返回当前时间<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static String getNowTime(){
		SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}
	
	public static String getNowTime2(){
		SimpleDateFormat sdf = new SimpleDateFormat("HHmm");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}
	/**
	 * 得到两个日期的日期差
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public static long diffDate(String beginDate,String endDate){
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
		long diff = (t2.getTimeInMillis()-t1.getTimeInMillis())/(1000*60*60*24); 
		
		return diff;
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DateUtilExtend比较两个时间差<br>
		 * Return: long<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-28  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public static long timeDiff1(String beginTime ,String endTime) {
	        SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
	        Date begin = null;
	        Date end = null;
	        try {
	        	begin = sdf.parse(beginTime);
		        end = sdf.parse(endTime);
			} catch (ParseException e) {
				e.printStackTrace();
			}
	        long times = (end.getTime() - begin.getTime())/(1000*60);  
	        return times;
	}
	public static long timeDiff2(String beginTime ,String endTime) {
        SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
        Date begin = null;
        Date end = null;
        try {
        	begin = sdf.parse(beginTime+"00");
	        end = sdf.parse(endTime+"00");
		} catch (ParseException e) {
			e.printStackTrace();
		}
        long times = (end.getTime() - begin.getTime())/(1000*60);  
        return times;
}


	
	public static Date getStrToDate(String strDate){
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
	 * @return
	 */
	public static String getDateLaterMonth(){
		Date nowDate;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		Calendar c = Calendar.getInstance();
		c.setTimeInMillis(getMillis(new Date()) - ((long) 30) * 24 * 3600 * 1000);
		nowDate = c.getTime();
		String nowTime = sdf.format(nowDate);
		return nowTime;

	}
	
	/**
	 * 根据某一个日期得到该日期属于该年的第几周
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
		if (Integer.toString(c.get(Calendar.WEEK_OF_YEAR)).length()==1){
			week = "0"+Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
		}else{
			week = Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
		}
		return Integer.toString(c.get(Calendar.YEAR)) + week ;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DateUtilExtend根据日期字符串取得当前为星期几，1为星期一，...7为星期日<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-9  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static String getWeekByDate(String strdate){
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
            showDate = "7";
            break;
        case 2:
            showDate = "1";
            break;
        case 3:
            showDate = "2";
            break;
        case 4:
            showDate = "3";
            break;
        case 5:
            showDate = "4";
            break;
        case 6:
            showDate = "5";
            break;
        default:
            showDate = "6";
            break;
        }

        return showDate;
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
			//end.add(Calendar.DATE, 7 - nw);
			calendar.add(Calendar.DATE,6);
			Date end = calendar.getTime();
			Date [] darr = new Date[]{ start, end };
			return darr;
		}

		public String getFullTimeStr(Date d){
	        String ret="";
	        try {
				ret = formatter.format(d);
	        } catch (Exception ex) {
	            //其他错误处理
	        }
			return ret;
		}
		
		public String weekBeginEnd(int year,int weeknum,String beginDate,String endDate){
			String result = "";
			Date[] darr = getStartEnd(year, weeknum);
			if ((getFullTimeStr(darr[0]).compareTo(beginDate)<0)&&(getFullTimeStr(darr[1]).compareTo(endDate)>0)) {
				result = beginDate+"-"+endDate;
			}else if ((getFullTimeStr(darr[0]).compareTo(beginDate)<0)&&(getFullTimeStr(darr[1]).compareTo(endDate)<0)){
				result = beginDate+"-"+getFullTimeStr(darr[1]);
			}else if ((getFullTimeStr(darr[0]).compareTo(beginDate)>0)&&(getFullTimeStr(darr[1]).compareTo(endDate)<0)){
				result = getFullTimeStr(darr[0])+"-"+getFullTimeStr(darr[1]);
			}else if ((getFullTimeStr(darr[0]).compareTo(beginDate)>0)&&(getFullTimeStr(darr[1]).compareTo(endDate)>0)){
				result = getFullTimeStr(darr[0])+"-"+endDate;
			}
			return result;
		}

		public void main(String[] args) {

		}
	}

}

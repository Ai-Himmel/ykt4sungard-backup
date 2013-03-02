/**
 * 
 */
package org.king.check.util;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
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
	 * @param date
	 * @param format
	 * @return String
	 */
	public static  String formatDateByFormat(Date date, String format) {
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
	
	public static String formatTime(String time){
		String result ="";
		if(time!=null){
			if(time.length()<5){
				result ="0"+time;
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
	 * @param indate
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
	 * @param intime
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
	/*
	格式化时间,输入格式hh:mm,输出格式hhmmss
	*
	*/
	public static String formattime(String time){
		if(time==null||("".equals(time))){
			return "";
		}
		time = time+":00";
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					"HH:mm:ss");
			Date d = sdf.parse(time);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			sdf = new SimpleDateFormat("HHmmss");
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			e.printStackTrace();
			return time;
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

	public static String formatDate3(Date date) {
		return formatDateByFormat(date, "yyyyMMdd");
	}

	/**
	 * 返回年份
	 * @param date 日期
	 * @return 返回年份
	 */
	public static int getYear(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.YEAR);
	}

	/**
	 * 返回月份
	 * @param date 日期
	 * @return 返回月份
	 */
	public static int getMonth(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MONTH) + 1;
	}

	/**
	 * 返回日份
	 * @param date 日期
	 * @return 返回日份
	 */
	public static int getDay(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.DAY_OF_MONTH);
	}

	/**
	 * 返回小时
	 * @param date 日期
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
	 * 根据输入的字符串格式化时间，返回格式hhmm
	 * 传入格式：hh:mm:ss
	 * @param time
	 * @return  
	 */
	public static String FormatTimeHm(String time) {
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					"HH:mm:ss");
			Date d = sdf.parse(time);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			sdf = new SimpleDateFormat("HHmm");
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			e.printStackTrace();
			return time;
		}
	}

	/**
	 * 返回分钟
	 * @param date 日期
	 * @return 返回分钟
	 */
	public static int getMinute(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MINUTE);
	}

	/**
	 * 返回秒钟
	 * @param date 日期
	 * @return 返回秒钟
	 */
	public static int getSecond(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.SECOND);
	}

	/**
	 * 返回毫秒
	 * @param date 日期
	 * @return 返回毫秒
	 */
	public static long getMillis(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.getTimeInMillis();
	}

	/**
	 * 日期相加
	 * @param date 日期
	 * @param day 天数
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
		c.add(Calendar.DATE, day);
		return simpleFormat.format(c.getTime());
	}

	/**
	 * 日期相减
	 * @param date 日期
	 * @param date1 日期
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
	 * 返回时间撮，格式为20050101 10:45:50
	 * @return
	 */
	
	public static String  getTimestamp(){
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd HH:mm:ss");
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

    public static String getYesterday(){
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
        Calendar now = Calendar.getInstance();
        now.add(Calendar.DAY_OF_MONTH,-1);
        return sdf.format(now.getTime());
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
	
	/*
	 * 取当前月的第一天，格式yyyymmdd
	 */
	public static String getNowMonthFirstDate(Date d){
		
		Calendar calendar = new GregorianCalendar();
		calendar.setTime(d);
		calendar.set(Calendar.DATE, calendar.getActualMinimum(Calendar.DATE));
		return formatDate3(calendar.getTime());
		
	}
	
	/**
	 * 取当前月的最后一天，格式yyyymmdd
	 * @return
	 */
	public static String getNowMonthLastDate(Date d){
		
		Calendar calendar = new GregorianCalendar();
		calendar.setTime(d);
		calendar.set(Calendar.DATE, calendar.getActualMaximum(Calendar.DATE));
		return formatDate3(calendar.getTime());
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

	}
	// 获得周五的日期
	public static String getFriday(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		c.set(Calendar.DAY_OF_WEEK, Calendar.FRIDAY);
		
		return new SimpleDateFormat("yyyy-MM-dd").format(c.getTime());

	}
	
	// 获得周一的日期
	public static String getMonday(Date date) {  
		Calendar c = Calendar.getInstance();   
		c.setTime(date);
		c.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
		return new SimpleDateFormat("yyyyMMdd").format(c.getTime());
	}

    /*****************************************
     * @功能     计算指定日期某年的第几周
     * @return  interger
     * @throws ParseException
     ****************************************/
    public static int getWeekNumOfYearDay(String strDate ){
     Calendar calendar = Calendar.getInstance();
     calendar.setFirstDayOfWeek(Calendar.MONDAY);
     SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");
     Date curDate = null;
     try{
     	curDate = format.parse(strDate);
     }catch (ParseException e){
    	 
     }
     calendar.setTime(curDate);
     if("1231".equals(strDate.substring(4,8))){
    	 int iWeekNum =calendar.getActualMaximum(Calendar.WEEK_OF_YEAR);
    	 return iWeekNum;
     }else{
         int iWeekNum = calendar.get(Calendar.WEEK_OF_YEAR);
         return iWeekNum;
     }
    }
    
	/*
	 * 指定某个时间开始后第第几周，的周几的具体日期。
	 * beginDate 学期开始时间
	 * weeknum 第几周
	 * week周几
	 */
	public static  String  getCourseDate(String beginDate ,int weekNum , int week,String format){
		   String ret="";
			try{ 
				java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(format);
				 Calendar c =  Calendar.getInstance(Locale.CHINESE);
				 c.setFirstDayOfWeek(Calendar.MONDAY);
				 //System.out.println(c.getFirstDayOfWeek());
				 Date d= sdf.parse(beginDate);
				// System.out.println(Calendar.MONDAY);
				 c.setTime(d);
				 c.add(Calendar.WEEK_OF_YEAR, weekNum-1);
				 //System.out.println(sdf.format(c.getTime()));
				 c.set(Calendar.DAY_OF_WEEK, week+1);
				 ret = sdf.format(c.getTime());           
			}
			catch(Exception e){
				    
			}
			return ret;
		}


	public static Date[] getStartEnd(int year, int weeknum) {
		/*
		 * 参数说明 int year 年分 例如 2005 int weeknum 第几周 例如33 返回一个Calendar数组，长度为2
		 * 分别是开始日期和结束日期
		 */
		Calendar calendar = Calendar.getInstance();
        calendar.set(2009,1,1);
		calendar.setFirstDayOfWeek(Calendar.MONDAY);
		calendar.set(Calendar.YEAR, year);  
        calendar.getTime();
		calendar.set(Calendar.WEEK_OF_YEAR, weeknum);
		int nw = calendar.get(Calendar.DAY_OF_WEEK);
		//System.out.println(calendar.getTime());
		calendar.add(Calendar.DATE, 1 - nw);
		Date start = calendar.getTime();
		// end.add(Calendar.DATE, 7 - nw);
		calendar.add(Calendar.DATE, 6);
		Date end = calendar.getTime();
		Date[] darr = new Date[] { start, end };
		return darr;
	}

    /**
     * 获得两个日期之间相差的周次
     *
     * @param termBeginDate
     * @param useDate
     * @return
     */
    public static long getUseWeek(String termBeginDate, Date useDate) {
        try {
            Calendar beginMonday = Calendar.getInstance(Locale.CHINESE);
            beginMonday.setFirstDayOfWeek(Calendar.MONDAY);
            beginMonday.setTime(simpleFormat.parse(termBeginDate));
            //将开始日期调整为所属周的周一，默认周一为一周的第一天
            beginMonday.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);

            long DAY = 24L * 60L * 60L * 1000L;
            long mills = useDate.getTime() - beginMonday.getTimeInMillis();
            if (mills < 0) {
                return -1;
            }
            long days = mills / DAY;
            return days / 7 + 1;
        } catch (ParseException e) {
            throw new RuntimeException("解析日期错误：" + e.getMessage());
        }
    }

    /**
     * 得到下周一对应的日期
     *
     * @return
     */
    public static Date getNextMonday() {
        Calendar now = Calendar.getInstance(Locale.CHINESE);
        now.setFirstDayOfWeek(Calendar.MONDAY);
        now.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
        now.add(Calendar.DAY_OF_YEAR, 7);
        return now.getTime();
    }

    public static String getNow() {
        Date date = new Date();
        return simpleFormat2.format(date);
    }

	// 根据周得到该周的开始日期和结束日期
	public static class WeekBeginEndDate {
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

		public static  void main(String[] args) {
			String begindate="8:30";
			System.out.println(begindate.indexOf(":"));
			String newb=begindate.replace(":", "");
			System.out.println(newb);
			System.out.println(timeDiff1("083000","084000"));
			System.out.println(timeDiff1("103000","093000"));
			System.out.println(FormatTimeHm("9:23:45"));
			System.out.println(formattime("8:30"));
        }

        
		
	}
}

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
 * ��������ص���չ����
 * 
 * @author Administrator
 * 
 */
public class DateUtilExtend {
	static private SimpleDateFormat simpleFormat = new SimpleDateFormat(
			"yyyyMMdd");

	static private SimpleDateFormat simpleFormat2 = new SimpleDateFormat("yyyyMMddHHmmss");
	/**
	 * ��ָ���ĸ�ʽ����ʽ������
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
	 * ���õĸ�ʽ������
	 * 
	 * @param date
	 *            Date
	 * @return String
	 */
	public String formatDate(Date date) {
		return formatDateByFormat(date, "yyyy-MM-dd");
	}
	
	/**
	 * ��ʽ�����ڣ������ʽ��yyyymmdd�������ʽyyyy��mm��dd��
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
			return year+"��"+month+"��"+day+"��";
		}
	}
	/**
	 * ��ʽ��ʱ�䣬�����ʽ��hhmmss�������ʽhh��mm��
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
			return hour+"��"+min+"��";
		}
		
	}
	/*
	��ʽ��ʱ��,�����ʽhh:mm,�����ʽhhmmss
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
	 * ����Сʱ�������ʽhhmmss�������ʽhh
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
	 * ���ط��ӣ������ʽhhmmss�������ʽmm
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
	 * ��ʽ�����ڣ������ʽyyyy-mm-dd,�����ʽyyyymmdd
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
	 * ��ʽ�����ڣ������ʽyyyymmdd,�����ʽyyyy-mm-dd
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
	 * �������
	 * @param date ����
	 * @return �������
	 */
	public static int getYear(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.YEAR);
	}

	/**
	 * �����·�
	 * @param date ����
	 * @return �����·�
	 */
	public static int getMonth(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MONTH) + 1;
	}

	/**
	 * �����շ�
	 * @param date ����
	 * @return �����շ�
	 */
	public static int getDay(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.DAY_OF_MONTH);
	}

	/**
	 * ����Сʱ
	 * @param date ����
	 * @return ����Сʱ
	 */
	public static int getHour(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.HOUR_OF_DAY);
	}

	/**
	 * ����������ַ�����ʽ��ʱ�䣬���ظ�ʽhh:mm:ss
	 * �����ʽ��hhmmss
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
	 * ����������ַ�����ʽ��ʱ�䣬���ظ�ʽhhmm
	 * �����ʽ��hh:mm:ss
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
	 * ���ط���
	 * @param date ����
	 * @return ���ط���
	 */
	public static int getMinute(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MINUTE);
	}

	/**
	 * ��������
	 * @param date ����
	 * @return ��������
	 */
	public static int getSecond(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.SECOND);
	}

	/**
	 * ���غ���
	 * @param date ����
	 * @return ���غ���
	 */
	public static long getMillis(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.getTimeInMillis();
	}

	/**
	 * �������
	 * @param date ����
	 * @param day ����
	 * @return ������Ӻ������
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
	 * �������
	 * @param date ����
	 * @param date1 ����
	 * @return ��������������
	 */
	public static int diffDate(Date date, Date date1) {
		return (int) ((getMillis(date) - getMillis(date1)) / (24 * 3600 * 1000));
	}

	/**
	 * ���ص�ǰ���ڣ���ʽΪ2005-01-01
	 * @return
	 */
	public static String getNowDate() {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}
	/**
	 * ����ʱ��飬��ʽΪ20050101 10:45:50
	 * @return
	 */
	
	public static String  getTimestamp(){
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd HH:mm:ss");
		String nowTime = sdf.format(new Date());
		return nowTime;
		
	}

	/**
	 * ���ص�ǰ���ڣ���ʽΪ20050101
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
	 * ���ص�ǰʱ�䣬��ʽ��hhmmss
	 * @return
	 */
	public static String getNowTime() {
		SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}

	/**
	 * ���ص�ǰʱ�䣬��ʽ��hhmm
	 * @return
	 */
	public static String getNowTime2() {
		SimpleDateFormat sdf = new SimpleDateFormat("HHmm");
		String nowTime = sdf.format(new Date());
		return nowTime;
	}

	/**
	 * �õ��������ڵ����ڲ�
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
	 * �õ�ʱ��ʱ�䴫���ʽ��20060101101010��������ʱ���룩yyyymmddhhmmss
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
	 * ���������ʽΪ��hhmmss
	 * �Ƚ�����ʱ��Ĳ����ֵΪ����
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
	 * ��������ʱ������ֵΪ����
	 * ����ʱ���ʽΪhhmm
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
	 * ���ص�ǰ���ڵĺ�һ���µ����ڣ���ʽ��2005-01-01
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
	 * ȡ��ǰ�µĵ�һ�죬��ʽyyyymmdd
	 */
	public static String getNowMonthFirstDate(Date d){
		
		Calendar calendar = new GregorianCalendar();
		calendar.setTime(d);
		calendar.set(Calendar.DATE, calendar.getActualMinimum(Calendar.DATE));
		return formatDate3(calendar.getTime());
		
	}
	
	/**
	 * ȡ��ǰ�µ����һ�죬��ʽyyyymmdd
	 * @return
	 */
	public static String getNowMonthLastDate(Date d){
		
		Calendar calendar = new GregorianCalendar();
		calendar.setTime(d);
		calendar.set(Calendar.DATE, calendar.getActualMaximum(Calendar.DATE));
		return formatDate3(calendar.getTime());
	}

	/**
	 * ����ĳһ�����ڵõ����������ڸ���ĵڼ���
	 * ���������ʽ��yyyymmdd
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
     *   ���������жϵ�ǰ�µ���������   
     *   @param   s   String   ��ʽΪ   yyyy-MM�������ַ���   
     *   @return   int   ��������   
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
	 * ���������ַ���ȡ�õ�ǰΪ���ڼ�
	 * �������ڸ�ʽΪyyyymmdd
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
	 * ���������ַ���ȡ�õ�ǰΪ���ڼ���1Ϊ����һ��...7Ϊ������
	 * �������ڸ�ʽΪyyyymmdd
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
			showDate = "��";
			break;
		case 2:
			showDate = "һ";
			break;
		case 3:
			showDate = "��";
			break;
		case 4:
			showDate = "��";
			break;
		case 5:
			showDate = "��";
			break;
		case 6:
			showDate = "��";
			break;
		default:
			showDate = "��";
			break;
		}

		return showDate;
	}

	// �ж����������Ƿ���ͬһ�ܣ�����һ�����������ڻ�������ܵ���һ����������ڡ�
	public class ManageWeek {
		// �ж����������Ƿ���ͬһ��
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
				// ���12�µ����һ�ܺ�������һ�ܵĻ������һ�ܼ���������ĵ�һ��
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

		// ����������
		public String getSeqWeek() {
			Calendar c = Calendar.getInstance(Locale.CHINA);
			String week = Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
			if (week.length() == 1)
				week = "0" + week;
			String year = Integer.toString(c.get(Calendar.YEAR));
			return year + week;

		}

	}
	// ������������
	public static String getFriday(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		c.set(Calendar.DAY_OF_WEEK, Calendar.FRIDAY);
		
		return new SimpleDateFormat("yyyy-MM-dd").format(c.getTime());

	}
	
	// �����һ������
	public static String getMonday(Date date) {  
		Calendar c = Calendar.getInstance();   
		c.setTime(date);
		c.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
		return new SimpleDateFormat("yyyyMMdd").format(c.getTime());
	}

    /*****************************************
     * @����     ����ָ������ĳ��ĵڼ���
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
	 * ָ��ĳ��ʱ�俪ʼ��ڵڼ��ܣ����ܼ��ľ������ڡ�
	 * beginDate ѧ�ڿ�ʼʱ��
	 * weeknum �ڼ���
	 * week�ܼ�
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
		 * ����˵�� int year ��� ���� 2005 int weeknum �ڼ��� ����33 ����һ��Calendar���飬����Ϊ2
		 * �ֱ��ǿ�ʼ���ںͽ�������
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
     * �����������֮�������ܴ�
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
            //����ʼ���ڵ���Ϊ�����ܵ���һ��Ĭ����һΪһ�ܵĵ�һ��
            beginMonday.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);

            long DAY = 24L * 60L * 60L * 1000L;
            long mills = useDate.getTime() - beginMonday.getTimeInMillis();
            if (mills < 0) {
                return -1;
            }
            long days = mills / DAY;
            return days / 7 + 1;
        } catch (ParseException e) {
            throw new RuntimeException("�������ڴ���" + e.getMessage());
        }
    }

    /**
     * �õ�����һ��Ӧ������
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

	// �����ܵõ����ܵĿ�ʼ���ںͽ�������
	public static class WeekBeginEndDate {
		private static DateFormat formatter = new SimpleDateFormat("yyyyMMdd");

		public Date[] getStartEnd(int year, int weeknum) {
			/*
			 * ����˵�� int year ��� ���� 2005 int weeknum �ڼ��� ����33 ����һ��Calendar���飬����Ϊ2
			 * �ֱ��ǿ�ʼ���ںͽ�������
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
				// ����������
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

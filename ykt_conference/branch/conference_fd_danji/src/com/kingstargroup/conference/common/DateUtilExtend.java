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
 * ��������ص���չ����
 * 
 * @author Administrator
 * 
 */
public class DateUtilExtend {
	static private SimpleDateFormat simpleFormat = new SimpleDateFormat(
			"yyyyMMdd");
	/**
	 * ��ָ���ĸ�ʽ����ʽ������
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
	 * �������
	 * 
	 * @param date
	 *            ����
	 * @return �������
	 */
	public static int getYear(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.YEAR);
	}

	/**
	 * �����·�
	 * 
	 * @param date
	 *            ����
	 * @return �����·�
	 */
	public static int getMonth(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MONTH) + 1;
	}

	/**
	 * �����շ�
	 * 
	 * @param date
	 *            ����
	 * @return �����շ�
	 */
	public static int getDay(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.DAY_OF_MONTH);
	}

	/**
	 * ����Сʱ
	 * 
	 * @param date
	 *            ����
	 * @return ����Сʱ
	 */
	public static int getHour(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.HOUR_OF_DAY);
	}

		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DateUtilExtend����������ַ�����ʽ��ʱ��<br>
		 * Return: String<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-19  <br>
		 * @author   ����ΰ
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
	 * ���ط���
	 * 
	 * @param date
	 *            ����
	 * @return ���ط���
	 */
	public static int getMinute(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.MINUTE);
	}

	/**
	 * ��������
	 * 
	 * @param date
	 *            ����
	 * @return ��������
	 */
	public static int getSecond(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.get(Calendar.SECOND);
	}

	/**
	 * ���غ���
	 * 
	 * @param date
	 *            ����
	 * @return ���غ���
	 */
	public static long getMillis(Date date) {
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		return c.getTimeInMillis();
	}

	/**
	 * �������
	 * 
	 * @param date
	 *            ����
	 * @param day
	 *            ����
	 * @return ������Ӻ������
	 */
	public static Date addDate(Date date, int day) {
		Calendar c = Calendar.getInstance();
		c.setTimeInMillis(getMillis(date) + ((long) day) * 24 * 3600 * 1000);
		return c.getTime();
	}

	/**
	 * �������
	 * 
	 * @param date
	 *            ����
	 * @param date1
	 *            ����
	 * @return ��������������
	 */
	public static int diffDate(Date date, Date date1) {
		return (int) ((getMillis(date) - getMillis(date1)) / (24 * 3600 * 1000));
	}
	
	/**
	 * ���ص�ǰ���ڣ���ʽΪ2005-01-01
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
	 * Description: DateUtilExtend���ص�ǰ���ڣ���ʽΪ20050101<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-4  <br>
	 * @author   ����ΰ
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
	 * Description: DateUtilExtend���ص�ǰʱ��<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
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
	 * �õ��������ڵ����ڲ�
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
		 * Description: DateUtilExtend�Ƚ�����ʱ���<br>
		 * Return: long<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-28  <br>
		 * @author   ����ΰ
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
	 * ���ص�ǰ���ڵĺ�һ���µ����ڣ���ʽ��2005-01-01
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
	 * ����ĳһ�����ڵõ����������ڸ���ĵڼ���
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
	 * Description: DateUtilExtend���������ַ���ȡ�õ�ǰΪ���ڼ���1Ϊ����һ��...7Ϊ������<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-5-9  <br>
	 * @author   ����ΰ
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

		// �����һ������
		public String getMonday(Date date) {
			Calendar c = Calendar.getInstance();
			c.setTime(date);
			c.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
			return new SimpleDateFormat("yyyy-MM-dd").format(c.getTime());
		}

		// ������������
		public String getFriday(Date date) {
			Calendar c = Calendar.getInstance();
			c.setTime(date);
			c.set(Calendar.DAY_OF_WEEK, Calendar.FRIDAY);
			return new SimpleDateFormat("yyyy-MM-dd").format(c.getTime());

		}

	}

	// �����ܵõ����ܵĿ�ʼ���ںͽ�������
	static public class WeekBeginEndDate {
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
	            //����������
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

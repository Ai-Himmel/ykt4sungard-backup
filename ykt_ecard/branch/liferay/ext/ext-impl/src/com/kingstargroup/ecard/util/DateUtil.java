package com.kingstargroup.ecard.util;

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
 * Modify History����Change Log��: <br>
 * �������ͣ��������޸ĵȣ� �������� ������ �������ݼ���<br>
 * ���� 2005-10-16 ������ ����һ�����ڸ�ʽyyyyMMddHHmmss���ַ�������ǰʱ�䣩
 * <p>
 * 
 * @author ������ 
 * @version 1.0
 * @since 1.0
 */
public class DateUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DateUtil.class);

	static private SimpleDateFormat simpleFormat = new SimpleDateFormat("yyyyMMdd");
	
	static private SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd"); 
	
	/*
	 * Description: ����һ����ǰʱ�� @return String ��ʽ��yyyyMMddHHmmss @exception Modify
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
	 * Description: �������ͷ���һ����ǰʱ�� @param partten String @return String ��ʽ��partten
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
	 * Description: �õ�һ�������ʱ�� @param startTime String ��ʽ��yyyyMMddHHmmss @param
	 * interval int �� @return String ��ʽ��partten @exception Modify History:
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
	
	
	/**
	 * @param startDate
	 * @param interval
	 * @return Date һ���µ�ʱ��
	 */
	public static Date getNewDate(Date startDate,int interval){
		Calendar calendar = Calendar.getInstance();
		calendar.setTimeInMillis(startDate.getTime());
		calendar.add(Calendar.SECOND, interval);
		return calendar.getTime();
	}
	
	public static String getOtherDate(String startDate,int interval){
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					"yyyyMMdd");
			Date d = sdf.parse(startDate);
			Calendar calendar = Calendar.getInstance();
			calendar.setTime(d);
			calendar.add(Calendar.DATE, interval);
			return sdf.format(calendar.getTime());
		} catch (ParseException e) {
			return startDate;
		}
	}
	
	public static String getOtherDate(String startDate,String parttn,int interval){
		try {
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
					parttn);
			Date d = sdf.parse(startDate);
			Calendar calendar = Calendar.getInstance();
			calendar.setTime(d);
			calendar.add(Calendar.DATE, interval);
			return sdf.format(calendar.getTime());
		} catch (ParseException e) {
			return startDate;
		}
	}

	/*
	 * Description: �õ�һ�������ʱ�� @param startTime String ��ʽ��yyMMddHHmmss @param
	 * interval int �� @return String ��ʽ��partten @exception Modify History:
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
	 * Description: ����ʱ����ʽ���õ����ϼ�϶ʱ���ĵڶ���ʱ�� @param startTime String ��ʽ��partten
	 * @param interval int �� @return String ��ʽ��partten @exception Modify
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
	 * Description: �õ�����ʱ���ַ���֮��ļ�϶ʱ�� @param firstTime String ��ʽ��yyyyMMddHHmmss
	 * @param secondTime String ��ʽ: yyyyMMddHHmmss @return long @exception
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
	
	public static long getIntervalTime(String firstTime, String secondTime,String partten) {
		long time = 000000000L;
		try {
			System.out.println(firstTime);
			System.out.println(secondTime);
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(partten);
			Date f = sdf.parse(firstTime);
			Date s = sdf.parse(secondTime);
			time = f.getTime() - s.getTime();
			return time;
		} catch (ParseException e) {
			// TODO: handle exception
			e.printStackTrace();
			return time;
		}
	}

	/*
	 * Description: �Ƚ�����ʱ���ַ�����ǰ���ϵ @param firstTime String ��ʽ��yyyyMMddHHmmss
	 * @param secondTime String ��ʽ: yyyyMMddHHmmss @return int |
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
	
	/**
	 * @param firstDate
	 * @param secondDate
	 * @return  firstDate=secondDate int=0 | firstDate>secondDate int>0 | firstDate<secondDate int<0
	 */
	public static int checkDateSequence(Date firstDate,Date secondDate){
		return firstDate.compareTo(secondDate);
	}
	/*
	 * Description: �Ƚ�����ʱ���ַ�����ǰ���ϵ @param firstTime String ��ʽ��yyyyMMddHHmmss
	 * @param secondTime String ��ʽ: yyyyMMddHHmmss @return int |
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
	 * Description: �Ƚ�����ʱ���ַ�����ʱ��� @param firstTime String ��ʽ��yyyyMMddHHmmss
	 * @param secondTime String ��ʽ: yyyyMMddHHmmss @param second int ��ʽ @return
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
					"yyyy-MM-dd");
			Date d = sdf.parse(time);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			sdf = new SimpleDateFormat("yyyyMMdd");
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return time;
		}

	}
	/**
	 * �Ѵ�������ڸ�ʽ�����·�
	 * @param time
	 * @return
	 */
	public static String getMonth(String time) {
		/**java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
		"yyyy-MM");
		Date d = null;
		try {
			d = sdf.parse(time);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return time;
		}
		Calendar calendar = Calendar.getInstance();
		calendar.setTimeInMillis(d.getTime());
		sdf = new SimpleDateFormat("yyyyMM");
		return sdf.format(calendar.getTime());**/
		return time.replaceAll("-","");
	}
	
	public static int getdiffMonth(String date1,String date2){
		if(date1.length()>6){
			date1=date1.substring(0, 6);
		}
		if(date2.length()>6){
			date2=date2.substring(0, 6);
		}
		try{
			java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyyMM");
			Date f = sdf.parse(date1);
			Date s = sdf.parse(date2);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(f.getTime());
			int year1 = calendar.get(Calendar.YEAR);
			int month1 = calendar.get(Calendar.MONTH);
			calendar.setTimeInMillis(s.getTime());
			int year2 = calendar.get(Calendar.YEAR);
			int month2 = calendar.get(Calendar.MONTH);
			return (year2-year1)*12+(month2-month1);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 100;
		}		
	}
	
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

	
	public static int formatStr2Date(String indate){
	//String s2 = "19960245"; // yyyyMMdd
	java.text.DateFormat df2 = new java.text.SimpleDateFormat("yyyyMMdd");
	try {
		Date date2 = df2.parse(indate);
		System.out.println(date2);
	} catch (ParseException e) {
		//e.printStackTrace();
		return -1;
	}
		return 0;
	}
	
	public static Date String2Date(String indate,String partten){
		//String s2 = "19960245"; // yyyyMMdd
		java.text.DateFormat df2 = new java.text.SimpleDateFormat(partten);
		try {
			Date date2 = df2.parse(indate);
			return date2;
		} catch (ParseException e) {
			//e.printStackTrace();
			return null;
		}
		}

	/**
	 * ��hhssmm��ʽתΪhh:ss:mm
	 * @param inpuString
	 * @return
	 */
	public static String formatStr2Str(String inpuString) {
		if(inpuString!=null && inpuString.length()==6){
			String result = inpuString.substring(0, 2) + ":"
			+ inpuString.substring(2, 4) + ":"
			+ inpuString.substring(4, inpuString.length());
			return result;
		}
		if(inpuString==null){
			return "";
		}
		return inpuString;
	}
	
	public static int dateCompare(String bDate,String eDate){
		if (("".equals(bDate))&&("".equals(eDate))){
			return 0;
		}
		try{
			int bD = Integer.parseInt(bDate);
			int eD = Integer.parseInt(eDate);
			if (bD>eD){
				return -2;
			}
		}catch(Exception e){
			//e.printStackTrace();
			return -1;
		}
		return 0;
	}
	
	/**
	 * pattern yyyy-MM-dd
	 * @param date
	 * @return
	 */
	public static String formatDate(Date date) {
		if (date == null) {
			return "";
		}
		return dateFormat.format(date);
	}
}

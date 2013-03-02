package com.kingstar.basetask.bean;

import java.util.Calendar;
import java.util.Date;
import java.util.StringTokenizer;

public class CalendarWrapper {

	Calendar caldate = Calendar.getInstance();

	public void setTime(Date d) {
		caldate.setTime(d);

	}

	public void add(int hours) {
		caldate.add(Calendar.HOUR, hours);

	}

	public Date getTime() {
		return caldate.getTime();

	}

	public void generateInterval(Calendar begin,Calendar end, int interval) {
	//while (true){
			
			
	//	Date d=null;
//		if(begin.compareTo(end)>=0){
//          d.setDate(begin.);
//
//		b.setMinutes(t);
//
//			System.out.println(b.getD());
//		}

	}

	public static void main(String[] args) {
		CalendarWrapper cw=new CalendarWrapper();
		System.out.println(cw.getTime());
		
//		d.generateInterval(7, 24, 3000);

	}

	public static void splitDate(String source) {
		StringTokenizer st = new StringTokenizer(source, ",");
		while (st.hasMoreTokens()) {
			System.out.println(st.nextToken());
		}
	}

}

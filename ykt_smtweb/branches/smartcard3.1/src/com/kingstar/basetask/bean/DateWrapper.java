package com.kingstar.basetask.bean;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;
import java.util.StringTokenizer;

public class DateWrapper {

	Date date = null;

	public DateWrapper() {

		date = new Date();

	}

	public void setHours(int time) {

		date.setHours(time);
	}

	public void setMinutes(int minutes) {

		date.setMinutes(minutes);

	}
	public void setSeconds(int seconds) {

		date.setSeconds(seconds);

	}

	public void printDate(DateWrapper d) {

		DateFormat df = DateFormat.getDateInstance(DateFormat.LONG, Locale.SIMPLIFIED_CHINESE);
		
	//	SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		//System.out.println(df.format(date.getDate()));
	}

	public int getMinutes() {

		return date.getMinutes();

	}

	public Date getDate() {
		return date;
	}

	public void setDate(Date date) {
		this.date = date;
	}

	//interval is 秒,  60分* 60秒=3600
	public static ArrayList generateInterval(Date begin, Date end, int interval) {
		// DateFormat df = DateFormat.getDateInstance();
		ArrayList l= new ArrayList();
		
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//		
//		System.out.println(" generateInterval start.............");
//		System.out.println("begine is " + format.format(begin));
//		System.out.println("end  is " + format.format(end));
//     	System.out.println("interval  is " + interval);
    	
//		Date d=new Date(begin.toString());
	//	System.out.println("begin :"+format.format(d));
		//while ((begin.getTime()) <(end.getTime())) {
     	long t = begin.getTime();
		while ((begin.compareTo(end)<0)) {
			
     	  t +=(interval*1000);
	//   System.out.println(t);
     	 begin.setTime(t);	
		
		//l.add(d.toString());
			Date temp=new Date(begin.getTime());
			l.add(temp);
		}
		
//	Iterator i=l.iterator();
//		while(i.hasNext()){
//			System.out.println("iterator start: "+format.format(i.next()));
//		
//	}
		return l;

	}

	
	public Date getDate(String date) {

		SimpleDateFormat formatter = new SimpleDateFormat();
		try {
			return formatter.parse(date);
		} catch (Exception e) {
			throw new RuntimeException("日期格式不正确");
		}
	}

	public static void main(String[] args) {
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		
		Date d1 = new Date();
		Date d2 = new Date();
		d1.setHours(4);
		
		System.out.println("d1 "+formatter.format(d1));

		//interval is 秒,  60分* 60秒=3600
		ArrayList a=DateWrapper.generateInterval(d1, d2, 3600);
	
	}

	public static ArrayList splitDate(String source,String s) {
		ArrayList l=new ArrayList();
		//System.out.println("source :"+source);
		StringTokenizer st = new StringTokenizer(source, s);
		while (st.hasMoreTokens()) {
			l.add(st.nextToken());
			
		}
		return l;
	}

//	// split second and million , example "70:00"
//	public static List splitTime(String source) {
//          List l=null;
//		StringTokenizer st = new StringTokenizer(source, ":");
//		while (st.hasMoreTokens()) {
//			l.add(st.nextToken());
////			System.out.println(st.nextToken());
//		}
//		return l;
//	}

}

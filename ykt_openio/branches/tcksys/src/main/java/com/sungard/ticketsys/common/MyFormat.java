package com.sungard.ticketsys.common;

import java.text.DecimalFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;

public class MyFormat {

	public static Boolean checkMoneySdf(String inpuString) {
		String regex = "^((([1-9]{1}\\d{0,9}))|([0]{1}))((\\.(\\d){2}))?$";
		boolean result = inpuString.matches(regex);
		return result;
	}

	/**
	 * 将hhssmm格式转为hh:ss:mm
	 * @param inpuString
	 * @return
	 */
	public static String timeSdf(String inpuString) {
		String result = inpuString.substring(0, 2) + ":"
				+ inpuString.substring(2, 4) + ":"
				+ inpuString.substring(4, inpuString.length());
		return result;
	}
	
	/**
	 * 将yyyyMMdd格式转为yyyy-MM-dd
	 * @param inpuString
	 * @return
	 */
	public static String dateSdf(String inpuString) {
		String result = inpuString.substring(0, 4) + "-"
				+ inpuString.substring(4, 6) + "-"
				+ inpuString.substring(6, inpuString.length());
		return result;
	}
	
	/**
	 * 将yyyy-MM-dd格式转为yyyyMMdd
	 * @param inpuString
	 * @return
	 */
	public static String dateTSdf(String inpuString) {
		String result = inpuString.substring(0, 4)
				+ inpuString.substring(5, 7)
				+ inpuString.substring(8, inpuString.length());
		return result;
	}
	
	/**
	 * 金钱格式
	 * @param input
	 * @return
	 */
	public static String moneySdf(Double input){
		DecimalFormat   df   =new DecimalFormat("0.00");  
		return df.format(input); 
	}
	
	public static long dateDiff(String startTime, String endTime, String format){

		//按照传入的格式生成一个simpledateformate对象

		SimpleDateFormat sd = new SimpleDateFormat(format);

		long nd = 1000*24*60*60;//一天的毫秒数

		long nh = 1000*60*60;//一小时的毫秒数

		long nm = 1000*60;//一分钟的毫秒数

		long ns = 1000;//一秒钟的毫秒数

		long diff = 0;


		//获得两个时间的毫秒时间差异

		try {
			diff = sd.parse(endTime).getTime() - sd.parse(startTime).getTime();
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		long day = diff/nd;//计算差多少天

		long hour = diff%nd/nh;//计算差多少小时

		long min = diff%nd%nh/nm;//计算差多少分钟

		long sec = diff%nd%nh%nm/ns;//计算差多少秒

		//输出结果
        return day;

		}


	
}

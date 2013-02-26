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
	 * ��hhssmm��ʽתΪhh:ss:mm
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
	 * ��yyyyMMdd��ʽתΪyyyy-MM-dd
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
	 * ��yyyy-MM-dd��ʽתΪyyyyMMdd
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
	 * ��Ǯ��ʽ
	 * @param input
	 * @return
	 */
	public static String moneySdf(Double input){
		DecimalFormat   df   =new DecimalFormat("0.00");  
		return df.format(input); 
	}
	
	public static long dateDiff(String startTime, String endTime, String format){

		//���մ���ĸ�ʽ����һ��simpledateformate����

		SimpleDateFormat sd = new SimpleDateFormat(format);

		long nd = 1000*24*60*60;//һ��ĺ�����

		long nh = 1000*60*60;//һСʱ�ĺ�����

		long nm = 1000*60;//һ���ӵĺ�����

		long ns = 1000;//һ���ӵĺ�����

		long diff = 0;


		//�������ʱ��ĺ���ʱ�����

		try {
			diff = sd.parse(endTime).getTime() - sd.parse(startTime).getTime();
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		long day = diff/nd;//����������

		long hour = diff%nd/nh;//��������Сʱ

		long min = diff%nd%nh/nm;//�������ٷ���

		long sec = diff%nd%nh%nm/ns;//����������

		//������
        return day;

		}


	
}

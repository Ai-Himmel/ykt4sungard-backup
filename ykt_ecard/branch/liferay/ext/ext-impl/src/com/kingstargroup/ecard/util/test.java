package com.kingstargroup.ecard.util;

import org.apache.derby.tools.sysinfo;

import com.liferay.portal.UserPasswordException;

public class test {

	/**
	 * Method name: main<br>
	 * Description: <br>
	 * Return: void<br>
	 * Args: @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		try {
			String encodedStr = SimpleEncoding.byte2hex(SimpleEncoding.md5("4321njuneusoftecard2009-12-16 13:00:00".getBytes()));
//			String a="adbb";
//			long b = (long)(Double.parseDouble(a)*100);
			System.out.println(DateUtil.getIntervalTime("2009-12-16 13:00:00", DateUtil.getNow("yyyy-MM-dd HH:mm:ss"),"yyyy-MM-dd HH:mm:ss"));
			System.out.println(encodedStr);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
//		System.out.println(DateUtil.getdiffMonth("2007-01", "2009-10"));
	}

}

package com.kingstargroup.fdykt.util;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: XMLGenerateUtil.java
 * Description: util�࣬��Ҫ����һЩ�й���xml��صĲ�����
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���
 * ����  				2005-9-28    ������    ���XML������
 * �޶�					2005-10-08   ������    ����XML����� XMLSendOut
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */

import org.apache.log4j.Logger;


public class SocketInfoGenerateUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SocketInfoGenerateUtil.class);

	public static String InfoGenerate(String cellphone,String money,String serialno,String ecardno) {
		money += "00";
		for(int i= 7-money.length();i>0;i--){
			money = "0"+money;
		}
		String secTime = DateUtil.getNow("MMddHHmmss");
		String dateTime = DateUtil.getNow("yyyyMMdd");

		
		String encycode = "";
		try {
			StringBuffer INFO = new StringBuffer(300);
			INFO.append("1");
			INFO.append("0067");
			INFO.append("0100");
			INFO.append("0000000000000000");
			INFO.append(cellphone).append("           ");		
			INFO.append(money);
			INFO.append(secTime);
			INFO.append(dateTime);
			INFO.append(serialno);
			INFO.append(cellphone);
			INFO.append("00");
			INFO.append(ecardno);
			INFO.append("000000000000000000000000000000000000");			
			String signcode = dateTime+serialno+cellphone+money;
			
			RSA t = new RSA();
			for(int i =0;i<signcode.length();i++){
				String temp = signcode.substring(i, i+1);
				long y = Long.parseLong(temp);
				y += 10;
				encycode += t.ency(y)+",";
			}
			
			for(int j=130-encycode.length(); j>0;j--){
				encycode +=" ";
			}
		} catch (Exception e) {
			System.err.println(e + "error");
		}

		return encycode;

	}
	
	public static String InfoDecode(String encycode){
		String [] encyStr = encycode.split(",");
		String decodeStr ="";
		RSA t = new RSA();
		for(int i=0;i<encyStr.length;i++){
			String temp = encyStr[i];
			long y = Long.parseLong(temp);
			if(!"".equals(temp.trim())){
				decodeStr+=t.decode(y);
			}
		}
		return decodeStr;
	}

}

package com.kingstargroup.fdykt;

import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Timer;

import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class Teest {

	/**
	 * File name: Teest.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ������    2007-4-28  <br>
	 * @author   ������
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
//		HashMap map = new HashMap();
//		map.put("lvol1", "10000");
//		System.out.println(XMLGenerateUtil.MapXMLGenerate("0000", "�ɹ�", map));
		String money = "25.453";
		int a = (int)(Double.parseDouble(money)*100);
		System.out.println(a);
	}

}

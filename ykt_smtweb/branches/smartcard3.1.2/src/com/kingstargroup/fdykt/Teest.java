package com.kingstargroup.fdykt;

import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Timer;

import com.kingstargroup.fdykt.util.ANSIX98FormatUtil;
import com.kingstargroup.fdykt.util.Crypt;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class Teest {

	/**
	 * File name: Teest.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    2007-4-28  <br>
	 * @author   何林青
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		String bankcardinfo =";4682030210343921=11101011874701462259?+994682030210343921=1561560500050000000015462259214000011101=0210343921=000000000=03000000021000000000000";
//		String bankcardinfo="";
		byte[] enc_pwd = ANSIX98FormatUtil.process("123456", "4682030210343921");
		
		try {
			String des_pwd = Util.ZHDesEnc(enc_pwd);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		String bankcardcd2="";
		if(bankcardinfo.indexOf(";")>-1 && bankcardinfo.indexOf("?")>0){
			bankcardcd2=bankcardinfo.substring(bankcardinfo.indexOf(";")+1, bankcardinfo.indexOf("?"));
		}
		
		String bankcardcd3="";
		if(bankcardinfo.indexOf("+")>-1 && bankcardinfo.lastIndexOf("?")>0){
			bankcardcd3=bankcardinfo.substring(bankcardinfo.indexOf("+")+1, bankcardinfo.lastIndexOf("?"));
		}

		System.out.println(bankcardcd2+bankcardcd2);
//		6013820500980871010
		
//		417515
		//494949494949
		//064170
		
		//6013820500980872020
		
//		byte[] enc_pwd = ANSIX98FormatUtil.process("417515", "6013820500980872020");
//		
//		String test  ="";
//		try {
//			test  = Util.ZHDesEnc(enc_pwd);
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		System.out.println(test);
		
//		2BEE7FD70E8641E8

	}

}

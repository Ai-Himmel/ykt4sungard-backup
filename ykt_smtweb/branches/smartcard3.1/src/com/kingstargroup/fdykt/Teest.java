package com.kingstargroup.fdykt;

import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Timer;

import com.kingstargroup.fdykt.util.DateUtil;

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
		
		String cardexpiredate="20170707";
		// TODO Auto-generated method stub
		if(cardexpiredate.length()>6){
			cardexpiredate = cardexpiredate.substring(2);
		}

		System.out.println(cardexpiredate);	
		if(cardexpiredate.length()<8){
			cardexpiredate=DateUtil.getNow("yyyyMMdd").substring(0, 2)+cardexpiredate;
		}
		
		System.out.println(cardexpiredate);
		
//		String tsamt = String.valueOf("1.0");
//		tsamt = tsamt.substring(0, tsamt.indexOf("."));
//		Timer timer = new Timer();
//		SimpleDateFormat format = new SimpleDateFormat("yyyyMMddHHmmss");
//		Date d;
//		try {
//			d = format.parse("20090331170300");
//			 timer.schedule(new TimerTaskTest(), d);
//			  System.out.println("over");
//		} catch (ParseException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		 
//		  try{
//		   Thread.sleep(1000);
//		  }catch(Exception ex){
//		   timer.cancel();
//		  }

//
//		byte ttt[] = new byte[100];
//		ttt[0]=Byte.parseByte("1");
//		ttt[1]=Byte.parseByte("0");
//		int bytelength =0;
//		String aaaa ="";
//		for(int i=0;i<ttt.length;i++){
//			if(ttt[i]!=Byte.parseByte("0")){
//				bytelength++;
//				aaaa += Byte.toString(ttt[i]);
//			}else{
//				break;
//			}			
//		}
//		String bbb = "";
//		for(int i=0;i<ttt.length;i++){
//			bbb += Byte.toString(ttt[i]);
//		}
//		String ccc= "";
//		ccc= new String(ttt,0,100);
//
//		System.out.println(aaaa);
//		System.out.println(bbb);
//		System.out.println(ccc.trim());
//		double a = 26253;
//		a = a/100;
//		System.out.println(a);
	}

}

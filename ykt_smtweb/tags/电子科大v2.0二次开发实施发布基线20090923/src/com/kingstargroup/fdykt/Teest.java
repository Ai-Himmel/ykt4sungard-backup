package com.kingstargroup.fdykt;

import java.io.UnsupportedEncodingException;

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
		// TODO Auto-generated method stub
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
		String a ="0000000000001209";
		String b = Float.toString(Float.parseFloat(a)/100);
		System.out.println(b);
	}

}

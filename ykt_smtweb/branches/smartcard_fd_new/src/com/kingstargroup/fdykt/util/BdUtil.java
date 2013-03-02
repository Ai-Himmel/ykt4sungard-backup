package com.kingstargroup.fdykt.util;

import java.math.BigDecimal;

public class BdUtil {
	
	
	
	public static String round(double a,double b,int scale,int direct) {
		BigDecimal atemp = new BigDecimal(Double.toString(a));
		BigDecimal btemp = new BigDecimal(Double.toString(b));
		BigDecimal one = new BigDecimal("1");
		BigDecimal f = atemp.divide(one, scale, direct);
		String out = String.valueOf(f.multiply(btemp).doubleValue());
		return out;
	}
	
	
    //把元转换成分
	public  static int YuantoFen(double yuan){
		BigDecimal Y = new BigDecimal(yuan);
		BigDecimal F = Y.divide(new BigDecimal("1"),2,BigDecimal.ROUND_HALF_UP);
		int out = F.multiply(new BigDecimal("100")).intValue();
		return out;
	}
	
   //把元转换成分
	public  static int  YuantoFen(String yuan){
		BigDecimal Y = new BigDecimal(yuan);
		BigDecimal F = Y.divide(new BigDecimal("1"),2,BigDecimal.ROUND_HALF_UP);
		int out =F.multiply(new BigDecimal("100")).intValue();
		return out;
	}
	
	public static String   FentoYuan(double  fen){
		BigDecimal F = new  BigDecimal(fen);
		BigDecimal Y = F.divide(new BigDecimal("100"),2,BigDecimal.ROUND_HALF_UP);
		return   String.valueOf(Y.doubleValue());
	}
	public static String   FentoYuan(String  fen){
		BigDecimal F = new  BigDecimal(fen);
		BigDecimal Y = F.divide(new BigDecimal("100"),2,BigDecimal.ROUND_HALF_UP);
		return   String.valueOf(Y.doubleValue());
	}
	
	
	
	/*//元字符串，转换成金额
	public  static String YuanString(String yuan){
		BigDecimal Y = new BigDecimal(yuan);
		BigDecimal F = Y.divide(new BigDecimal("1"),2,BigDecimal.ROUND_HALF_UP);
		String out =String.valueOf(F.doubleValue());
		return out;
	}
	
//	元字符串，转换成金额
	public  static double YuanDouble(String yuan){
		BigDecimal Y = new BigDecimal(yuan);
		BigDecimal F = Y.divide(new BigDecimal("1"),2,BigDecimal.ROUND_HALF_UP);
		double out =F.doubleValue();
		return out;
	}
	
	
	
	public  static double YuanDouble2(double yuan){
		BigDecimal Y = new BigDecimal(yuan);
		BigDecimal F = Y.divide(new BigDecimal("1"),2,BigDecimal.ROUND_HALF_UP);
		double out =F.doubleValue();
		return out;
	}*/
	
	
	public  static void main(String[] arg){
		
		
		System.out.println(FentoYuan("7500"));
		int w = (int)Double.parseDouble("32.7")*100;
		System.out.println(YuantoFen("75.0"));
	}
}

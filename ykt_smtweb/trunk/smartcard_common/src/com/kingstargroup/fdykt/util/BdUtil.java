package com.kingstargroup.fdykt.util;

import java.math.BigDecimal;

public class BdUtil {
	
	
	//a,原值；b，运算值；scale,精度，direct
	public static String round(double a,double b,int scale,int direct) {
		BigDecimal atemp = new BigDecimal(Double.toString(a));
		BigDecimal btemp = new BigDecimal(Double.toString(b));
		BigDecimal one = new BigDecimal("1");
		BigDecimal f = atemp.divide(one, scale, direct);
		String out = String.valueOf(f.multiply(btemp).doubleValue());
		return out;
	}
	public static String round2(int a,int b,int scale,int direct) {
		BigDecimal atemp = new BigDecimal(Integer.toString(a));
		BigDecimal btemp = new BigDecimal(Integer.toString(b));
		BigDecimal one = new BigDecimal("1");
		BigDecimal f = atemp.divide(btemp, scale, direct);
		String out = String.valueOf(f.doubleValue());
		return out;
	}

}

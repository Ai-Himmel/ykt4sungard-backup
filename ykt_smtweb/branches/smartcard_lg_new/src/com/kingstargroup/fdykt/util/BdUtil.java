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

}

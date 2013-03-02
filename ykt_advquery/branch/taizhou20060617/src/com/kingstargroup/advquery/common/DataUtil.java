package com.kingstargroup.advquery.common;

import java.text.DecimalFormat;
import java.text.NumberFormat;

public class DataUtil {
	public static String formatMoney(String money){
		NumberFormat formatter = new DecimalFormat("#.00");
		return formatter.format(new Float(money)).toString();
	}

}

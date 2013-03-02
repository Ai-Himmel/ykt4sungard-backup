package com.kingstargroup.conference.util;

import java.math.BigDecimal;

public class IntegerUtil {
	
	public static Integer getInteger(BigDecimal decimalValue) {
	    if (decimalValue == null) {
	      return null;
	    }
	    
	    String decimalStr = decimalValue.toString();
	    int place = decimalStr.indexOf(".");
	    if (place != -1) {
	      decimalStr = decimalStr.substring(0, place);
	    }
	    //If decimalValue have large integer part , BigInteger should be used
	    Integer result = new Integer(decimalStr);
	    return result;
	  } 

}

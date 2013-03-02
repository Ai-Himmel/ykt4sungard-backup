package com.kingstargroup.fdykt.util;

import java.math.BigDecimal;

import junit.framework.TestCase;

public class BdUtilTest extends TestCase {

	public void testRound() {
		System.out.println(BdUtil.round(15.2399, 100, 2, BigDecimal.ROUND_HALF_UP));
	}
	
	public static void main(String[] arg){
		byte[] vsmess = new byte[300];
		
		
	}

}

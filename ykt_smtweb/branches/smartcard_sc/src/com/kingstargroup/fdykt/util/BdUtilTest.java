package com.kingstargroup.fdykt.util;

import java.math.BigDecimal;

import junit.framework.TestCase;

public class BdUtilTest extends TestCase {

	public void testRound() {
		System.out.println(BdUtil.round(15.2399, 100, 2, BigDecimal.ROUND_HALF_UP));
	}

}

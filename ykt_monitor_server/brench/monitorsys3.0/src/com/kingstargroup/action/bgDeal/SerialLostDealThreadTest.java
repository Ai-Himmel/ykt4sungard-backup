package com.kingstargroup.action.bgDeal;

import junit.framework.TestCase;

public class SerialLostDealThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgDeal.SerialLostDealThread.anaylize()'
	 */
	public void testAnaylize() {
		SerialLostDealThread a = new SerialLostDealThread();
		a.initParam();
//		a.startTime = "20061130180019";
//		a.endTime = "20061130230019";
		a.run();

	}

}

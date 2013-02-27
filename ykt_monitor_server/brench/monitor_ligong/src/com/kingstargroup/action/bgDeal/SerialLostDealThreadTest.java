package com.kingstargroup.action.bgDeal;

import junit.framework.TestCase;

public class SerialLostDealThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgDeal.SerialLostDealThread.anaylize()'
	 */
	public void testAnaylize() {
		SerialLostDealThread a = new SerialLostDealThread();
		a.initParam();
		a.startTime = "20060801101000";
		a.endTime = "20060801103000";
		a.run();
	}

}

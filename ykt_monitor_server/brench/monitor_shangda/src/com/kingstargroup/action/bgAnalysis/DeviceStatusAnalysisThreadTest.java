package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class DeviceStatusAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.DeviceStatusAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		DeviceStatusAnalysisThread a = new DeviceStatusAnalysisThread();
		a.initParam();
		a.startTime = "20060713000000";
		a.endTime = "20060713235900";
		a.run();
	}

}



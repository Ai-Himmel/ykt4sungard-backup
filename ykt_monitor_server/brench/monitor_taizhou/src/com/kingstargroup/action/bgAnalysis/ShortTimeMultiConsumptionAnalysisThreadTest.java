package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class ShortTimeMultiConsumptionAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.ShortTimeMultiConsumptionAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		ShortTimeMultiConsumptionAnalysisThread a = new ShortTimeMultiConsumptionAnalysisThread();
		a.initParam();
//		a.startTime = "20060707090230";
//		a.endTime = "20060707100000";
		a.run();
	}

}



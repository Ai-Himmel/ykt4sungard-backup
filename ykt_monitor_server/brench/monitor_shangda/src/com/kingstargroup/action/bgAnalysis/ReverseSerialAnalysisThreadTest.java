package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class ReverseSerialAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.ReverseSerialAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		ReverseSerialAnalysisThread a = new ReverseSerialAnalysisThread();
		a.initParam();
		a.startTime = "20060713000000";
		a.endTime = "20060713125900";
		a.run();
	}

}



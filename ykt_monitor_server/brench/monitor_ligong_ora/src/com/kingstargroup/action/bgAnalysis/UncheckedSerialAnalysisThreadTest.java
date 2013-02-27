package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class UncheckedSerialAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.UncheckedSerialAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		UncheckedSerialAnalysisThread a = new UncheckedSerialAnalysisThread();
		a.initParam();
		a.startTime = "20060713000000";
		a.endTime = "20060713125900";
		a.run();
	}

}



package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class LargeExceptAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.LargeExceptAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		LargeExceptAnalysisThread a = new LargeExceptAnalysisThread();
		a.initParam();
		a.startTime = "20060713000000";
		a.endTime = "20060713125900";
		a.run();
	}

}



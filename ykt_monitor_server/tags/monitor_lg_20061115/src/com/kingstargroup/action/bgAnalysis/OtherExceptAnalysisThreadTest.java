package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class OtherExceptAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.OtherExceptAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		OtherExceptAnalysisThread a = new OtherExceptAnalysisThread();
		a.initParam();
		a.startTime = "20060713000000";
		a.endTime = "20060713125900";
		a.run();

	}

}



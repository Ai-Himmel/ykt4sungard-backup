package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class SupressExceptAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.SupressExceptAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		SupressExceptAnalysisThread a = new SupressExceptAnalysisThread();
		a.initParam();
//		a.startTime = "20060713000000";
//		a.endTime = "20060713125900";
		a.run();
	}

}



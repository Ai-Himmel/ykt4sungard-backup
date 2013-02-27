package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class SettimeErrorAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.SettimeErrorAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		SettimeErrorAnalysisThread a = new SettimeErrorAnalysisThread();
		a.initParam();
//		a.startTime = "20060713000000";
//		a.endTime = "20060713125900";
		a.run();
	}

}



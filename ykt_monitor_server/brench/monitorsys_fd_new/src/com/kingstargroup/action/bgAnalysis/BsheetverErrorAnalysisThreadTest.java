package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class BsheetverErrorAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.BsheetverErrorAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		BsheetverErrorAnalysisThread a = new BsheetverErrorAnalysisThread();
		a.initParam();
//		a.startTime = "20060907080000";
//		a.endTime = "20060907090000";
		a.run();
	}

}



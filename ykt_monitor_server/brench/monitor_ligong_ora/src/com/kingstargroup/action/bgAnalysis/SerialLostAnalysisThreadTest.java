package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class SerialLostAnalysisThreadTest extends TestCase {

	/*
	 * Test method for
	 * 'com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		SerialLostAnalysisThread a = new SerialLostAnalysisThread();
		a.initParam();
		a.startTime = "20060815140000";
		a.endTime = "20060815180000";
		a.run();
		
	}

}

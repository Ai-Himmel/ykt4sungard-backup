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
//		a.startTime = "20061208095121";
//		a.endTime = "200612081051211";
		a.run();
		

	}

}

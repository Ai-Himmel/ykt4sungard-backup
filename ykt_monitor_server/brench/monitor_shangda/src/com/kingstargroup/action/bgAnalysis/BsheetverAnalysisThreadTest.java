package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class BsheetverAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		BsheetverAnalysisThread a = new BsheetverAnalysisThread();
		a.initParam();
//		a.startTime = "20060713000000";
//		a.endTime = "20060713235900";
		Thread analyze = (Thread)a;
		analyze.run();
		if(a.isTerminate()){
			a.terminate();
		}
		analyze.run();
	}

}

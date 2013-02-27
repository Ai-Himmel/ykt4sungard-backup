package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class MidDragExcptAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.MidDragExcptAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		MidDragExcptAnalysisThread a = new MidDragExcptAnalysisThread();
		a.initParam();
//		a.startTime = "20060713000000";
//		a.endTime = "20060713235900";
		a.run();
	}

}



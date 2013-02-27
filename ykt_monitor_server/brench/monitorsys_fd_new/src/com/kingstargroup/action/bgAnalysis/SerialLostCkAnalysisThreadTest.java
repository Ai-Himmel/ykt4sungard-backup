package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class SerialLostCkAnalysisThreadTest extends TestCase {

	public void testAnaylize() {
		SerialLostCkAnalysisThread a = new SerialLostCkAnalysisThread();
		a.startTime = "20061015000000";
		a.endTime = "200611150000";
		a.run();
	}

}

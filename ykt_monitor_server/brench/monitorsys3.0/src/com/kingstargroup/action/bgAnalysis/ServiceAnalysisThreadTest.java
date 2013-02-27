package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class ServiceAnalysisThreadTest extends TestCase {

	public void testAnaylize() {
		ServiceAnalysisThread a = new ServiceAnalysisThread();
		a.initParam();
		a.run();
	}

}

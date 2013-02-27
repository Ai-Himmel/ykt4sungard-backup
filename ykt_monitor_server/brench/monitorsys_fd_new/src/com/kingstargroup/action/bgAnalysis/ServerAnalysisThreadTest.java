package com.kingstargroup.action.bgAnalysis;

import junit.framework.TestCase;

public class ServerAnalysisThreadTest extends TestCase {

	public void testAnaylize() {
		ServerAnalysisThread a = new ServerAnalysisThread();
		a.initParam();
		a.run();
	}

}

package com.kingstargroup.action.bgAnalysis;

import com.kingstargroup.SqlStatementDictionary;

import junit.framework.TestCase;

public class ServerAnalysisThreadTest extends TestCase {

	public void testAnaylize() {
		SqlStatementDictionary.getIntance().load("oracle");
		ServerAnalysisThread a = new ServerAnalysisThread();
		a.initParam();
		a.run();
	}

}

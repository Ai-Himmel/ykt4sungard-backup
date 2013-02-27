package com.kingstargroup.action.bgAnalysis;

import com.kingstargroup.SqlStatementDictionary;

import junit.framework.TestCase;

public class ExceptSerilAnalysisThreadTest extends TestCase {

	/*
	 * Test method for 'com.kingstargroup.action.bgAnalysis.ExceptSerilAnalysisThread.anaylize()'
	 */
	public void testAnaylize() {
		SqlStatementDictionary.getIntance().load("oracle");
		ExceptSerilAnalysisThread a = new ExceptSerilAnalysisThread();
		a.initParam();
		a.startTime = "20061101000000";
		a.endTime = "20061201235900";
		a.run();
	}

	
	
//	select a.card_no, a.total_cnt as tot1,b.total_cnt as tot2,a.out_bala as bala1,b.in_bala as bala2,(a.out_bala-b.in_bala)/double(100) as diff from YKT_CUR.T_TIF_RCVDTL a,
//	YKT_CUR.T_TIF_RCVDTL b 
//	where a.total_cnt=b.total_cnt-1 and a.card_no=b.card_no
//	and a.col_timestamp>'20060715000000' and a.col_timestamp<='20060720000000'
//	and b.col_timestamp>'20060715000000' and b.col_timestamp<='20060720000000' 
//	and (a.tx_code=930031 or a.tx_code=930034) 
//	and (b.tx_code=930031 or b.tx_code=930034) 
//	and a.out_bala<>b.in_bala 
//	order by a.card_no,a.total_cnt with u
}



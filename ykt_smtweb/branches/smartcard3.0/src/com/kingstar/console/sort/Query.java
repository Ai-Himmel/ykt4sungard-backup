package com.kingstar.console.sort;
//查找接口
public interface Query {
	
	//操作符号和条件
	SortVector QueryResult(String operation,String qcondition);
}

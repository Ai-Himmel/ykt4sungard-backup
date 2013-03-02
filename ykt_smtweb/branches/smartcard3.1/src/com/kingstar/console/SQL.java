package com.kingstar.console;

import com.kingstar.db.Pool;

public class SQL {

	public static String createtaskSQL = "create table TASKHISTORY(ID  LONG,NAME VARCHAR2(20),"
			+ "CLA VARCHAR2(100),PRIORITY INTEGER,TASKTYPE  VARCHAR2(10),"
			+ "RUNTIMETYPE VARCHAR2(10),RUNTIMEDATA VARCHAR2(20),DESCRIPTION VARCHAR2(100),"
			+ "STATUS INTEGER,BELONGDATE  VARCHAR2(10),BELONGTYPE  INTEGER)";

	public static void main(String[] args) throws Exception {
		iniTaskHistory();

	}

	private static void iniTaskHistory() throws Exception {
		Pool p = new Pool();
		p.getPool(3);
		p.Update(createtaskSQL);
		p.close(3);
	}

}

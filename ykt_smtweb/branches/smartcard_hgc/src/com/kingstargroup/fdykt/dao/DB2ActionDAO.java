package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.SQLException;

public class DB2ActionDAO {
	public Connection getConnection()throws SQLException{
		return KSDaoSessionFactory.createSession().getConnection();
	}
	public Connection getConnection(boolean autoCommit)throws SQLException{
		return KSDaoSessionFactory.createSession().getConnection(autoCommit);
	}
} 

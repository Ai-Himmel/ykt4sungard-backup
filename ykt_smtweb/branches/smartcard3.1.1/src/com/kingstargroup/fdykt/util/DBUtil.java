package com.kingstargroup.fdykt.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;

public class DBUtil {
//	private static final Logger logger = Logger.getLogger(DBUtil.class);

	public static Connection getConnection() {
		Connection conn = null;
		try {
			String driverClass = KSConfiguration.getInstance().getProperty(KSConstant.SHZH_DRIVER_CLASS);
			String jdbcUrl = KSConfiguration.getInstance().getProperty(KSConstant.SHZH_JDBC_URL);
			String user = KSConfiguration.getInstance().getProperty(KSConstant.SHZH_USERNAME);
			String password = KSConfiguration.getInstance().getProperty(KSConstant.SHZH_PASSWORD);
			Class.forName(driverClass);
			conn = DriverManager.getConnection(jdbcUrl, user, password);
		} catch (Exception e) {
//			logger.error("fail to open connection", e);
		}
		return conn;
	}

	public static void closeConnection(Connection conn) {
		if (conn != null) {
			try {
				conn.close();
			} catch (SQLException e) {
			}
		}
	}

	public static void closeStatement(Statement stmt) {
		if (stmt != null) {
			try {
				stmt.close();
			} catch (SQLException e) {
			}
		}
	}

	public static void closeResultSet(ResultSet rs) {
		if (rs != null) {
			try {
				rs.close();
			} catch (SQLException e) {
			}
		}
	}

	public static void rollback(Connection conn) {
		if (conn != null) {
			try {
				conn.rollback();
			} catch (SQLException e) {
			}
		}
	}
	
	public static void main(String[] args){
		Connection conn = null;
		try {
			String driverClass = "oracle.jdbc.driver.OracleDriver";
			String jdbcUrl = "jdbc:oracle:thin:@10.253.42.200:1521:v3test";
			String user = "ykt_cur";
			String password = "kingstar";
			Class.forName(driverClass);
			conn = DriverManager.getConnection(jdbcUrl, user, password);
			while (true) {
				System.out.println("conn:" + conn);
				System.out.println("conn is closed:" + conn.isClosed());
				Thread.sleep(3000);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}

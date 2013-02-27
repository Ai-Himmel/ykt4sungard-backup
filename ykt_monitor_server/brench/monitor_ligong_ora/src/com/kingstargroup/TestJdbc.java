package com.kingstargroup;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class TestJdbc {

	/**
	 * Description: TODO
	 *@param args
	 * @return Modify History: 2006-7-11 jackey create
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			Connection conn = DriverManager.getConnection("jdbc:db2://10.108.0.222:50002/ykt","db2inst4","db2inst4");
			Statement stat = conn.createStatement();
			ResultSet rs = stat.executeQuery("from sysibm.systables");
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}

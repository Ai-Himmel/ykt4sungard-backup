package com.kingstargroup.action.serverAnalysis;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.kingstargroup.form.TPifDevice;

public class TestJdbc {

	/**
	 * Description: TODO
	 *@param args
	 * @return Modify History: 2006-7-11 jackey create
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
//			Class.forName("com.ibm.db2.jcc.DB2Driver").newInstance();
//			Connection conn = DriverManager.getConnection("jdbc:db2://10.108.0.222:50002/ykt","db2inst4","db2inst4");
//			Statement stat = conn.createStatement();
//			ResultSet rs = stat.executeQuery("select * from ykt_cur.t_pif_device");
//			System.out.println("010324e");
			Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
			Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@10.49.188.243:1521:yktdb","system","kingstar");
			Statement stat = conn.createStatement();
			ResultSet rs = stat.executeQuery("select * from dba_users");
			System.out.println("010324e");
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch (Exception e) {
			// TODO: handle exception
		}

	}

}

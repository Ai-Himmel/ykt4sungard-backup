package com.kingstargroup.action.serverAnalysis;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.ArrayListHandler;
import org.apache.commons.dbutils.handlers.MapListHandler;

public class MonitorDBUtils {
	private  String dbtype = "";// type of database

	private  String ipAddr = "";// db host ip address

	private  String port = "";// db connection port

	private  String dbname = "";// db name

	private  String username = "";// db usrname

	private  String password = "";// db paswrd


	public MonitorDBUtils() {

	}

	private MonitorDBUtils(String dbtype, String ipAddr, String port,
			String dbname, String username, String password) {
		this.dbtype = dbtype;
		this.ipAddr = ipAddr;
		this.port = port;
		this.dbname = dbname;
		this.username = username;
		this.password = password;
	}

	private  boolean db2Check() {
		try {
			QueryRunner qr = new QueryRunner();
			ResultSetHandler rsh = new ArrayListHandler();
			String strsql = "select * from SYSIBM.SYSDUMMY1";
			qr.query(getConnection(), strsql,rsh);
			return true;
		} catch (Exception ex) {
			return false;
		}
	}

	private  boolean oracleCheck() {
		try {
			QueryRunner qr = new QueryRunner();
			ResultSetHandler rsh = new MapListHandler();
			String strsql = "select * from dba_users";
			qr.query(getConnection(), strsql,rsh);
			return true;
		} catch (Exception ex) {
			return false;
		}
	}

//	public void testUpdate() {
//		try {
//			QueryRunner qr = new QueryRunner();
//			ResultSetHandler rsh = new ArrayListHandler();
//			String strsql = "insert test1(page ,writable ,content)values('ttt','ttt','faskldfjklasdjklfjasdklj')";
//			qr.update(getConnection(), strsql);
//			// System.out.print("");
//		} catch (Exception ex) {
//			ex.printStackTrace(System.out);
//		}
//	}

	private  Connection getConnection() throws InstantiationException,
			IllegalAccessException, ClassNotFoundException, SQLException {
		String strDriver = "";
		String strUrl = "";
		String strUser = username;
		String strPass = password;
		if ("db2".equalsIgnoreCase(dbtype)) {
			strDriver = "com.ibm.db2.jcc.DB2Driver";
			strUrl = "jdbc:db2://" + ipAddr + ":" + port + "/" + dbname;
		}else if ("oracle".equalsIgnoreCase(dbtype)) {
			strDriver = "oracle.jdbc.driver.OracleDriver";
			strUrl = "jdbc:oracle:thin:@" + ipAddr + ":" + port + ":" + dbname;
		}else if ("MySQL".equalsIgnoreCase(dbtype)) {
			strDriver = "org.gjt.mm.mysql.Driver";
			strUrl = "jdbc:mysql://" + ipAddr + ":" + port + "/" + dbname;
		}else if ("SQLServer".equalsIgnoreCase(dbtype)) {
			strDriver = "com.microsoft.jdbc.sqlserver.SQLServerDriver";
			strUrl = "jdbc:microsoft:sqlserver://" + ipAddr + ":" + port
					+ ";databaseName=" + dbname;
		}else{
			//Ä¬ÈÏÊÇdb2
			strDriver = "com.ibm.db2.jcc.DB2Driver";
			strUrl = "jdbc:db2://" + ipAddr + ":" + port + "/" + dbname;
		}
		Class.forName(strDriver).newInstance();
		return DriverManager.getConnection(strUrl, strUser, strPass);
	}

	// 1. MySQL(http://www.mysql.com)mm.mysql-2.0.2-bin.jar
	// Class.forName( "org.gjt.mm.mysql.Driver" );
	// cn = DriverManager.getConnection(
	// "jdbc:mysql://MyDbComputerNameOrIP:3306/myDatabaseName", sUsr, sPwd );
	//
	// 2. PostgreSQL(http://www.de.postgresql.org)pgjdbc2.jar
	// Class.forName( "org.postgresql.Driver" );
	// cn = DriverManager.getConnection(
	// "jdbc:postgresql://MyDbComputerNameOrIP/myDatabaseName", sUsr, sPwd );
	//
	// 3.
	// Oracle(http://www.oracle.com/ip/deploy/database/oracle9i/)classes12.zip
	// Class.forName( "oracle.jdbc.driver.OracleDriver" );
	// cn = DriverManager.getConnection(
	// "jdbc:oracle:thin:@MyDbComputerNameOrIP:1521:ORCL", sUsr, sPwd );
	//
	// 4. Sybase(http://jtds.sourceforge.net)jconn2.jar
	// Class.forName( "com.sybase.jdbc2.jdbc.SybDriver" );
	// cn = DriverManager.getConnection(
	// "jdbc:sybase:Tds:MyDbComputerNameOrIP:2638", sUsr, sPwd );
	// // (Default-Username/Password: "dba"/"sql")
	//
	// 5. Microsoft SQLServer(http://jtds.sourceforge.net)
	// Class.forName( "net.sourceforge.jtds.jdbc.Driver" );
	// cn = DriverManager.getConnection(
	// "jdbc:jtds:sqlserver://MyDbComputerNameOrIP:1433/master", sUsr, sPwd );
	//
	// 6. Microsoft SQLServer(http://www.microsoft.com)
	// Class.forName( "com.microsoft.jdbc.sqlserver.SQLServerDriver" );
	// cn = DriverManager.getConnection(
	// "jdbc:microsoft:sqlserver://MyDbComputerNameOrIP:1433;databaseName=master",
	// sUsr, sPwd );
	//
	// 7. ODBC
	// Class.forName( "sun.jdbc.odbc.JdbcOdbcDriver" );
	// Connection cn = DriverManager.getConnection( "jdbc:odbc:" + sDsn, sUsr,
	// sPwd );
	//
	// 8.DB2
	// Class.forName("Com.ibm.db2.jdbc.net.DB2Driver");
	// String url="jdbc:db2://192.9.200.108:6789/SAMPLE"
	// cn = DriverManager.getConnection( url, sUsr, sPwd );
	
	
	
	public static boolean checkDBstatus(String db,String ip,String port,String dbname,String username,String password){
		boolean chkstt = false;
		MonitorDBUtils dbutil = new MonitorDBUtils(db,ip,port,dbname,username,password);
		if("db2".equals(db)){
			chkstt = dbutil.db2Check();
		}else if("oracle".equals(db)){
			chkstt = dbutil.oracleCheck();
		}
		return chkstt;
	}


}

package com.kingstar.db;

/**
 * 加入指针回滚
 */

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

public class Pool extends ConnectPool {

	public Pool() throws Exception {
		super();

	}

	private ConnectPool connMgr;
	private Statement stmt;
	private Connection con;
	private ResultSet rst;
	private CallableStatement proc;

	/**
	 * 对象连接初始化
	 */

	public Connection getPool(int id) throws Exception {
		try {
			connMgr = ConnectPool.getInstance();
			con = connMgr.getConnection(id);
		} catch (Exception e) {
			System.err.println("不能创建连接!请尝试重启应用服务器");

		}
		return con;
	}

	/**
	 * 同以上方法,加入连接空闲等待时间 待用方法
	 */

	public Connection getPool_t(int id, long time) throws Exception {
		try {
			connMgr = ConnectPool.getInstance();
			con = connMgr.getConnection(id, time);
		} catch (Exception e) {
			System.err.println("不能创建连接!");

		}
		return con;
	}

	/**
	 * 执行查询方法1
	 */
	public ResultSet executeQuery(String SqlStr) throws Exception {
		ResultSet result = null;
		try {
			stmt = con.createStatement();
			result = stmt.executeQuery(SqlStr);
			// here add one line by jnma 12.11
			con.commit();
		} catch (java.sql.SQLException e) {
			throw new Exception("执行查询语句出错");
		}
		return result;
	}

	/**
	 * 执行查询方法2
	 */
	public ResultSet getRst(String SqlStr) throws Exception {
		// ResultSet result = null;
		try {
			stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
					ResultSet.CONCUR_UPDATABLE);
			rst = stmt.executeQuery(SqlStr);
			// here add one line by jnma 12.11
			con.commit();
		} catch (java.sql.SQLException e) {
			throw new Exception("执行查询语句出错");
		}
		return rst;
	}

	/**
	 * 执行更新
	 */
	public int Update(String SqlStr) throws Exception {
		int result = -1;
		try {
			
			//可前后滚动，和更新的结果集
		stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_UPDATABLE);
			//stmt = con.createStatement();
			result = stmt.executeUpdate(SqlStr);
		
			con.commit();
			if (result == 0)
				System.out.println("执行delete,update,insert SQL出错");
		} catch (java.sql.SQLException e) {
			System.err.println("执行delete,update,insert SQL出错");
		}
		return result;
	}

	/**
	 * 执行事务处理
	 */
	public boolean handleTransaction(Vector SqlArray) throws Exception {
		boolean result = false;
		int ArraySize = SqlArray.size();
		try {
			stmt = con.createStatement();
			con.setAutoCommit(false);
			System.out.println("ArraySize is" + ArraySize);
			for (int i = 0; i < ArraySize; i++) {
				System.out.println(" 开始执行语句" + (String) SqlArray.elementAt(i));
				stmt.executeUpdate((String) SqlArray.elementAt(i));
				System.out.println(" 执行成功");
			}
			con.commit();
			con.setAutoCommit(true);// 必须
			System.out.println("事务执行成功");
			result = true;
		} catch (java.sql.SQLException e) {
			try {
				System.out.println(e.toString());
				System.out.println("数据库操作失败");
				con.rollback();
			} catch (java.sql.SQLException Te) {
				System.err.println("事务出错回滚异常");
			}
		}
		try {
			con.setAutoCommit(true);
		} catch (java.sql.SQLException e) {
			System.err.println("设置自动提交失败");
		}
		return result;
	}
	
	//存储过程调用

	public boolean prepareCallUpdate(String callstatement){
		
		
		boolean result=false;
		try {
			
			//可前后滚动，和更新的结果集
			   proc = con.prepareCall(callstatement); 
			 
		  	result= proc.execute();
			con.commit();
		}
		  catch(SQLException e){
			  
		  
		  
		  }
		return result;
	
			
	}
	
public ResultSet prepareCallQuery(String callstatement){
		
		
	 
		try {
			
			//可前后滚动，和更新的结果集
		   proc = con.prepareCall(callstatement); 	 
		   proc.execute();
		   rst = proc.getResultSet();
		   
		  // rst = (ResultSet)proc.getObject(1);
		   
		   while(rst.next())

		      {
		          System.out.println("<tr><td>" + rst.getInt(1) + "</td><td>"+rst.getString(2)+"</td></tr>");
		      }
		}
		  catch(SQLException e){
			  
		  
		  
		  }
		 return rst;
	
			
	}
	/**
	 * 释放连接
	 */
	public void close(int id) throws Exception {
		try {
			if (stmt != null)
				stmt.close();
			if (con != null) {
				connMgr.freeConnection(id, con);

				System.out.println(" [ 正在释放一个连接 ] ");

			}
		} catch (java.sql.SQLException e) {
			System.err.println(" 释放连接出错");
		}
	}
	public static void main(String args[]) throws Exception {
		
		Pool p=new Pool();
		p.getPool(3);
		p.prepareCallQuery("{ call testcall}");
     	p.close(3);

		//p.Update("delete test");
    	//p.close(3);
	}

}
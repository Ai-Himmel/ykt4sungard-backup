package com.kingstar.db;

/**
 * ����ָ��ع�
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
	 * �������ӳ�ʼ��
	 */

	public Connection getPool(int id) throws Exception {
		try {
			connMgr = ConnectPool.getInstance();
			con = connMgr.getConnection(id);
		} catch (Exception e) {
			System.err.println("���ܴ�������!�볢������Ӧ�÷�����");

		}
		return con;
	}

	/**
	 * ͬ���Ϸ���,�������ӿ��еȴ�ʱ�� ���÷���
	 */

	public Connection getPool_t(int id, long time) throws Exception {
		try {
			connMgr = ConnectPool.getInstance();
			con = connMgr.getConnection(id, time);
		} catch (Exception e) {
			System.err.println("���ܴ�������!");

		}
		return con;
	}

	/**
	 * ִ�в�ѯ����1
	 */
	public ResultSet executeQuery(String SqlStr) throws Exception {
		ResultSet result = null;
		try {
			stmt = con.createStatement();
			result = stmt.executeQuery(SqlStr);
			// here add one line by jnma 12.11
			con.commit();
		} catch (java.sql.SQLException e) {
			throw new Exception("ִ�в�ѯ������");
		}
		return result;
	}

	/**
	 * ִ�в�ѯ����2
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
			throw new Exception("ִ�в�ѯ������");
		}
		return rst;
	}

	/**
	 * ִ�и���
	 */
	public int Update(String SqlStr) throws Exception {
		int result = -1;
		try {
			
			//��ǰ��������͸��µĽ����
		stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_UPDATABLE);
			//stmt = con.createStatement();
			result = stmt.executeUpdate(SqlStr);
		
			con.commit();
			if (result == 0)
				System.out.println("ִ��delete,update,insert SQL����");
		} catch (java.sql.SQLException e) {
			System.err.println("ִ��delete,update,insert SQL����");
		}
		return result;
	}

	/**
	 * ִ��������
	 */
	public boolean handleTransaction(Vector SqlArray) throws Exception {
		boolean result = false;
		int ArraySize = SqlArray.size();
		try {
			stmt = con.createStatement();
			con.setAutoCommit(false);
			System.out.println("ArraySize is" + ArraySize);
			for (int i = 0; i < ArraySize; i++) {
				System.out.println(" ��ʼִ�����" + (String) SqlArray.elementAt(i));
				stmt.executeUpdate((String) SqlArray.elementAt(i));
				System.out.println(" ִ�гɹ�");
			}
			con.commit();
			con.setAutoCommit(true);// ����
			System.out.println("����ִ�гɹ�");
			result = true;
		} catch (java.sql.SQLException e) {
			try {
				System.out.println(e.toString());
				System.out.println("���ݿ����ʧ��");
				con.rollback();
			} catch (java.sql.SQLException Te) {
				System.err.println("�������ع��쳣");
			}
		}
		try {
			con.setAutoCommit(true);
		} catch (java.sql.SQLException e) {
			System.err.println("�����Զ��ύʧ��");
		}
		return result;
	}
	
	//�洢���̵���

	public boolean prepareCallUpdate(String callstatement){
		
		
		boolean result=false;
		try {
			
			//��ǰ��������͸��µĽ����
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
			
			//��ǰ��������͸��µĽ����
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
	 * �ͷ�����
	 */
	public void close(int id) throws Exception {
		try {
			if (stmt != null)
				stmt.close();
			if (con != null) {
				connMgr.freeConnection(id, con);

				System.out.println(" [ �����ͷ�һ������ ] ");

			}
		} catch (java.sql.SQLException e) {
			System.err.println(" �ͷ����ӳ���");
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
package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.SQLException;

public class KSDaoSessionFactory {
	/**
	 * Logger for this class      
	 */
	private static final Logger logger = Logger
			.getLogger(KSDaoSessionFactory.class);
	
	private static final ThreadLocal threadLocal = new ThreadLocal();
	
	public static DB2Session createSession(){
		DB2Session session = (DB2Session)threadLocal.get();
		if(null == session){
			session = new DB2Session();
			threadLocal.set(session);
		}
		return session;
	}
	
	public static void commit() throws SQLException {
		DB2Session session = (DB2Session) threadLocal.get();
		if (session != null) {
			session.commit();
			session.close();
		}
	}

	public static void rollback() throws SQLException {
		DB2Session session = (DB2Session) threadLocal.get();
		if (session != null) {
			try{
				session.rollback();
			}catch(SQLException ex){
				// do nothing
				throw (ex);
			}finally{
				session.close();
			}
		}
	}
	public static void closeSession(){
		DB2Session session = (DB2Session)threadLocal.get();
		threadLocal.set(null);
		if(null != session){
			try {
				session.commit();
			} catch (SQLException e) {
				logger.error("提交事务失败！" + e); 
				e.printStackTrace();
			}	
			try {
				session.close();
			} catch (SQLException e) {
				logger.error("关闭连接session失败 " + e);
				e.printStackTrace();
			}
		}
	}
}

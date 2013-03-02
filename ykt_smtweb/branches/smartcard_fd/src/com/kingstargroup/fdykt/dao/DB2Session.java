package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.SQLException;

public class DB2Session {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2Session.class);

	private Connection connection;

	public Connection getConnection() throws SQLException {
		return getConnection(false);
	}

	public Connection getConnection(boolean autoCommit) throws SQLException {
		synchronized (this) {
			try {
				if (null == connection) {
					connection = DB2DAOFactory.getConnection();
					connection.setAutoCommit(autoCommit);
					logger.info("���������ݿ�����");
				}
			} catch (SQLException e) {
				logger.error("�������ݿ�ʧ��", e);
				throw new SQLException("�������ݿ�ʧ��");
			} catch (Exception e) {
				logger.error("�������ݿ�ʧ��", e);
			}
			return connection;
		}
	}

	public void rollback() throws SQLException {
		if (logger.isDebugEnabled()) {
			logger.debug("rollback() - start ");
		}
		if (null == connection) {
			return;
		}
		try {
			connection.rollback();

			if (logger.isDebugEnabled()) {
				logger.debug("rollback() - end ");
			}
		} catch (SQLException e) {
			connection = null;
			logger.error("�ع�ʧ��", e);
			if (logger.isDebugEnabled()) {
				logger.debug("rollback() - end");
			}
			throw (e);
		}
	}

	public void commit() throws SQLException {
		if (null == connection) {
			return;
		}
		try {
			connection.commit();
			logger.info("�ر����ݿ�����");
		} catch (SQLException e) {
			connection = null;
			logger.error("�ύʧ��", e);
			throw (e);
		}
	}

	public synchronized void close() throws SQLException {
		if (null == connection)
			return;
		connection.close();
		connection = null;
		logger.debug("�ر����ݿ�����");
	}
}

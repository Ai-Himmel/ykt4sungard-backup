package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;

import java.sql.*;
import javax.sql.*;
import javax.naming.*;

public class DB2DAOFactory {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2DAOFactory.class);

	// 缓存 DataSource
	private static DataSource currentDataSource = null;

	private static Object mutex = new Object();

	private DB2DAOFactory() {
	}

	static public Connection getConnection() throws SQLException, Exception {
		Connection con;
		try {
			synchronized (mutex) {
				if (currentDataSource == null) {
					// Register the driver
					Context initCtx = new InitialContext();
					Context ctx = (Context) initCtx.lookup("java:comp/env");
					if (ctx == null) {
						throw new Exception("Boom - No Context");
					}
					String res = KSConfiguration.getInstance()
					.getProperty(KSConstant.JNDI_RES_NAME);
					currentDataSource = (DataSource) ctx
							.lookup(res);
				}
			}
			con = currentDataSource.getConnection();
			return con;
		} catch (SQLException ex) {
			logger.error("创建连接失败");
			throw (ex);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		}
	}
}

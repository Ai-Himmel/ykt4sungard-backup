package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dto.TSubsysLogDTO;

public class DB2SubsysLogDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DB2SubsysLogDAO.class);

	public void createLogInfo(TSubsysLogDTO syslog)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			int sequence = 0;
			
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "insert into YKT_CUR.T_SUBSYS_LOG(CUST_ID, LOGIN_NAME, LOG_DATE, LOG_TIME, FLAG, SUSSYS_ID, COMMENTS) values("
						+ syslog.getCustId()
						+ ",'"
						+ syslog.getLoginName()
						+ "','"
						+ syslog.getLogDate()
						+ "','"
						+ syslog.getLogTime()
						+ "',"
						+ syslog.getFlag()
						+ ","
						+ syslog.getSussysId()
						+ ",'"
						+ syslog.getComments()
						+ "')";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sequence = getSequence(conn, "YKT_CUR.S_T_SUBSYS_LOG");
				sql = "insert into YKT_CUR.T_SUBSYS_LOG(ID,CUST_ID, LOGIN_NAME, LOG_DATE, LOG_TIME, FLAG, SUSSYS_ID, COMMENTS) values("
						+ sequence
						+ ","
						+ syslog.getCustId()
						+ ",'"
						+ syslog.getLoginName()
						+ "','"
						+ syslog.getLogDate()
						+ "','"
						+ syslog.getLogTime()
						+ "',"
						+ syslog.getFlag()
						+ ","
						+ syslog.getSussysId()
						+ ",'"
						+ syslog.getComments() + "')";
			}
			stm = conn.prepareStatement(sql);
			stm.execute();
		} catch (SQLException e1) {
			logger.error("µÇÂ½ÐÅÏ¢Ð´Ê§°Ü[" + syslog.getCustId());
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
	}

	private int getSequence(Connection conn, String sequenceTable){
		Statement stm = null;
		ResultSet result = null;
		String sql = "select " + sequenceTable
				+ ".nextval mysequence from dual";
		int ret = 0;
		try{
		stm = conn.createStatement();
		result = stm.executeQuery(sql);
		
		if (result.next()) {
			ret = result.getInt("mysequence");
		}
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		return ret;
	}

}

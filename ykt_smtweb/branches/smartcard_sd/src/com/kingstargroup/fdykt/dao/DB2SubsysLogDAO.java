package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dto.TSubsysLogDTO;

public class DB2SubsysLogDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2SubsysLogDAO.class);	

	public void createLogInfo(TSubsysLogDTO syslog)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			sql = "insert into YKT_CUR.T_SUBSYS_LOG(CUST_ID, LOGIN_NAME, LOG_DATE, LOG_TIME, FLAG, SUSSYS_ID, COMMENTS) values("
					+ syslog.getCustId() + ",'"
					+ syslog.getLoginName() + "','" + syslog.getLogDate()
					+ "','" + syslog.getLogTime() + "',"
					+ syslog.getFlag() + "," + syslog.getSussysId()+",'"+syslog.getComments()
					+ "')";
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

	
}

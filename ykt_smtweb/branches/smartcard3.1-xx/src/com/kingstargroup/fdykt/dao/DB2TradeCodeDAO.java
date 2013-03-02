package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;

import org.apache.log4j.Logger;

public class DB2TradeCodeDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DB2TradeCodeDAO.class);

	public HashMap RetriveTradeMsgs() throws ClassNotFoundException,
			SQLException, Exception {
		if (logger.isDebugEnabled()) {
			logger.debug("RetriveTradeMsgs() - start"); //$NON-NLS-1$
		}

		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			try {
				sql = "select transcode,transname from YKT_CUR.t_transcode";
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				HashMap trademsgs = new HashMap();
				while (result.next()) {
					trademsgs.put(result.getString("transcode"), result
							.getString("transname"));
				}
				return trademsgs;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("RetriveTradeMsgs()", e1); //$NON-NLS-1$
			return null;
		} catch (Exception e) {
			logger.error("RetriveTradeMsgs()", e); //$NON-NLS-1$
			return null;
		}

	}
}

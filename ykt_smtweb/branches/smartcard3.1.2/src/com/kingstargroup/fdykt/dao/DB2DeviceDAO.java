package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.*;
import java.util.*;

public class DB2DeviceDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2DeviceDAO.class);

	public HashMap RetriveDevice() {
		if (logger.isDebugEnabled()) {
			logger.debug("RetriveDevice() - start"); //$NON-NLS-1$
		}

		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select deviceid,devicename from ykt_cur.t_device";
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				HashMap devices = new HashMap();
				while (result.next()) {
					devices.put(result.getString("deviceid"), result
							.getString("devicename"));
				}
				return devices;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}

		} catch (SQLException e1) {
			logger.error("RetriveDevice()", e1); //$NON-NLS-1$
			return null;
		} catch (Exception e) {
			logger.error("RetriveDevice()", e); //$NON-NLS-1$
			return null;
		}

		
	}
}

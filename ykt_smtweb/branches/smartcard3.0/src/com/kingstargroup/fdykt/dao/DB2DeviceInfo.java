package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConstant;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Map;

/**
 * @author cash
 * 
 * TODO To change the template for this generated type comment go to Window -
 * Preferences - Java - Code Style - Code Templates
 */
public class DB2DeviceInfo extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2DeviceInfo.class);

	/**
	 * get device info from database
	 */
	private boolean getDatebaseDeviceInfo(Map device) {
		Connection conn = null;
		Statement stm = null;
//		logger.debug("**************************refresh device info!");
		try {
			conn = getConnection();
			try {
				stm = conn.createStatement();
				String sql = "select * from ykt_cur.v_term ";
				ResultSet rs = stm.executeQuery(sql);
				while (rs.next()) {
					device.put(rs.getString("termid"), rs
							.getString("termname"));
				}
				return true;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取设备区域信息失败", e1);
			return false;
		} catch (Exception e) {
			logger.error("读取设备区域信息失败", e);
			return false;
		}
	}

	public String getKey() {
		return KSConstant.DICT_AREADEV;
	}

	public Object getValue(Object key) {
		if (_dict != null) {
			_dict.get(key);
		}
		return null;
	}

	public boolean loadDiction(Map dict) {
		_dict = dict;
		return getDatebaseDeviceInfo(dict);
	}

	public boolean releaseDiction() {
		return true;
	}

	private Map _dict;
}

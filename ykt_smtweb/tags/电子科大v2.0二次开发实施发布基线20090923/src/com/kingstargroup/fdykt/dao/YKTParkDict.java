package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Map;

import com.kingstargroup.fdykt.KSConstant;

public class YKTParkDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(YKTParkDict.class);

	public String getKey() {
		return KSConstant.DICT_PARK;
	}

	public boolean loadDiction(Map dict) {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		try {
			_serial = dict;
			conn = getConnection();
			String sql = "select park_code,park_name from ykt_cur.t_car_parkdic a ";
			try {
				stmt = conn.createStatement();
				rs = stmt.executeQuery(sql);
				while (rs.next()) {
					dict
							.put(rs.getString("park_code"), rs
									.getString("park_name"));
				}
				return true;
			} finally {
				if (stmt != null)
					stmt.close();
			}

		} catch (SQLException e) {
			logger.error("读取交易代码字典失败", e);
			return false;
		} catch (Exception e1) {
			logger.error("读取交易代码字典失败", e1);
			return false;
		}
		
	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if (_serial != null)
			return _serial.get(key);
		return null;
	}

	private Map _serial = null;
}

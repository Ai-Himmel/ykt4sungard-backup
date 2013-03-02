package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConstant;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Map;

public class ErrorCodeDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(ErrorCodeDict.class);

	public String getKey() {
		return KSConstant.DICT_ERR_CODE;
	}

	public boolean loadDiction(Map dict) {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			_errcode = dict;
			conn = getConnection();
			sql = "Select * from ykt_cur.t_errcode t";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			while (result.next()) {
				dict.put(result.getString("errcode"),result.getString("errmsg"));
			}
			if (stm != null) {
				stm.close();
			}
			return true;
		} catch (Exception e) {
			logger.error("≤È—Ø¥ÌŒÛ¬Î ß∞‹");
			return false;
		}
	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if(_errcode!=null)
			return _errcode.get(key);
		return null;
	}
	Map _errcode = null;

}

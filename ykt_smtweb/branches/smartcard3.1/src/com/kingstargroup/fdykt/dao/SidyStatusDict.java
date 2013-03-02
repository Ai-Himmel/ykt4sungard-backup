package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConstant;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Map;

public class SidyStatusDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(SidyStatusDict.class);

	public String getKey() {
		return KSConstant.DICT_SIDY_STATUS;
	}

	public boolean loadDiction(Map dict) {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			_sidystatus = dict;
			conn = getConnection();
			sql = "Select * from YKT_CUR.T_DICTIONARY where dicttype=76 ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			while (result.next()) {
				dict.put(result.getString("dictval"),result.getString("dictcaption"));
			}
			if (stm != null) {
				stm.close();
			}
			return true;
		} catch (Exception e) {
			logger.error("查询收费类别失败");
			return false;
		}
	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if(_sidystatus!=null)
			return _sidystatus.get(key);
		return null;
	}
	Map _sidystatus = null;

}

package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConstant;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Map;

public class FeeTypeDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(FeeTypeDict.class);

	public String getKey() {
		return KSConstant.DICT_FEETYPE;
	}

	public boolean loadDiction(Map dict) {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			_feetype = dict;
			conn = getConnection();
			sql = "Select * from YKT_CUR.T_PIF_DICTIONARY where dict_no=21 ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			while (result.next()) {
				dict.put(result.getString("DICT_VALUE"),result.getString("Dict_Caption"));
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
		if(_feetype!=null)
			return _feetype.get(key);
		return null;
	}
	Map _feetype = null;

}

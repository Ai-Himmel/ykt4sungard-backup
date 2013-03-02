package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConstant;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Map;

public class SidyTypeDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(SidyTypeDict.class);

	public String getKey() {
		return KSConstant.DICT_SIDY_TYPE;
	}

	public boolean loadDiction(Map dict) {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			_sidytype = dict;
			conn = getConnection();
			sql = "Select * from YKT_CUR.T_PIF_DICTIONARY where dict_no=77 ";
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
		if(_sidytype!=null)
			return _sidytype.get(key);
		return null;
	}
	Map _sidytype = null;

}

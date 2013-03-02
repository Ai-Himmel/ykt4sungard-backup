package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Map;

import com.kingstargroup.fdykt.KSConstant;

public class SerialTypeDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(SerialTypeDict.class);

	public String getKey() {
		return KSConstant.DICT_SERIALTYPE;
	}

	public boolean loadDiction(Map dict) {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		try{
			_serial = dict;
			conn = getConnection();
			stmt = conn.createStatement();
			rs = stmt.executeQuery("select TRADECODE, TRADEMSG from YKT_CUR.T_PIF_TRADECODE");
			while(rs.next()){
				dict.put(rs.getString("TRADECODE"),rs.getString("TRADEMSG"));
			}
			if(stmt!=null)
				stmt.close();
			return true;
		}catch(SQLException e){
			logger.error("读取交易代码字典失败",e);
		}
		return false;
	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if(_serial != null)
			return _serial.get(key);
		return null;
	}

	private Map _serial = null;
}

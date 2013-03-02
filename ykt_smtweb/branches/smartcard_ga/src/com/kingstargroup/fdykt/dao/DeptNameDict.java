package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Map;

import com.kingstargroup.fdykt.KSConstant;


public class DeptNameDict extends DB2ActionDAO implements YKTDictionEntry {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DeptNameDict.class);

	private Map _dict;
	
	public String getKey() {
		return KSConstant.DICT_DEPTNAME;
	}

	public boolean loadDiction(Map dict) {
		Statement stmt = null;
		ResultSet rs = null;
		_dict = null;
		try{
			Connection conn = getConnection();
			try {
				stmt = conn.createStatement();
				rs = stmt
						.executeQuery("select dept_code,dept_name from ykt_cur.t_cif_dept");
				while (rs.next()) {
					dict.put(rs.getString("dept_code"), rs
							.getString("dept_name"));
				}
				_dict = dict;
				return true;
			} finally {
				if (stmt != null) {
					stmt.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("∂¡»°≤ø√≈◊÷µ‰ ß∞‹");
			e1.printStackTrace();
			return false;
		} catch (Exception e) {
			logger.error("∂¡»°≤ø√≈◊÷µ‰ ß∞‹");
			e.printStackTrace();
			return false;
		}

	}

	public boolean releaseDiction() {
		return true;
	}

	public Object getValue(Object key) {
		if (_dict != null) {
			return _dict.get(key);
		}
		return null;
	}

}

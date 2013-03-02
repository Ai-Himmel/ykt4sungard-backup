package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

import com.kingstargroup.fdykt.util.DateUtil;

public class DB2AdminDAO extends DB2ActionDAO {

	public DB2AdminDAO() {
		super();
		// TODO Auto-generated constructor stub
	}

	public boolean checkLogin(String username, String password)
			throws ClassNotFoundException, SQLException, Exception {
		boolean ret = false;

		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			sql = "select a.* from ykt_media.user_table a "
					+ " where a.username='" + username + "' and a.password='"
					+ password + "' and a.userstatus=0";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();

			if (result.getFetchSize() > 0) {
				ret = true;
			}
		} catch (SQLException e1) {
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}

		return ret;
	}

	public boolean changepwd(String oldpassword, String newpassword)
			throws ClassNotFoundException, SQLException, Exception {
		boolean ret = false;

		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			sql = "update ykt_media.user_table set password='" + newpassword
					+ "'";
			stm = conn.prepareStatement(sql);
			stm.executeUpdate();
			ret=true;
		} catch (Exception e) {
			e.printStackTrace();
			throw(e);
		}finally {
			if (stm != null) {
				stm.close();
			}
		}
		
		return ret;
	}
	
	public Map worktime() throws SQLException, Exception {
		
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		Map temp = new HashMap();
		try{
			
			conn = getConnection();
			sql =" select key_value,max_value from ykt_cur.t_pif_syskey  "+
				 " where  key_code = 'BankWorkTime' ";
			
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			
			if (result.next()) {
			temp.put("keyValue",new Integer(result.getInt("key_value")));
			temp.put("maxValue",new Integer(result.getInt("max_value")));
			  return temp;
			}
		} catch (SQLException e1) {
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}

		return temp;
		}
		
}



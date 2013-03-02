package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dto.SysParaDTO;
import java.sql.*;

public class DB2SysParaDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2SysParaDAO.class);

	public SysParaDTO getSysPara(int id) throws Exception {
		SysParaDTO sysPara = null;
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		try {
			conn = getConnection();
			try {
				
				String sql = "select * from ykt_cur.T_PIF_Cur_SysPara where id=?";
				stmt = conn.prepareStatement(sql);
				stmt.setInt(1, id);
				rs = stmt.executeQuery();
				if (rs.next()) {
					sysPara = new SysParaDTO();
					sysPara.setId(rs.getInt("id"));
					sysPara.setValue(rs.getString("Value"));
					sysPara.setParaName(rs.getString("para_name"));
					sysPara.setUsetime(rs.getString("Usetime"));
					sysPara.setOptime(rs.getString("Optime"));
					sysPara.setUnit(rs.getString("Unit"));
					sysPara.setComments(rs.getString("Comments"));
				}
			} finally {
				if (stmt != null)
					stmt.close();
			}
		} catch (SQLException e1) {
			logger.error("读取系统参数失败,[" + id + "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取系统参数失败,[" + id + "]");
			e.printStackTrace();
		}
		return sysPara;
	}

	public String getDBDateTime() throws Exception {
		StringBuffer sql = new StringBuffer();
		String database = KSConfiguration.getInstance().getProperty("database",
				"db2");
		if ("db2".equalsIgnoreCase(database)) {
			sql
					.append(
							"select substr(d,1,4)||substr(d,6,2)||substr(d,9,2)")
					.append(
							"||substr(t,1,2)||substr(t,4,2)||substr(t,7,2) tdate  ")
					.append(
							"  from (SELECT char(CURRENT date,ISO) d ,char(current time,ISO) t ")
					.append(" FROM SYSIBM.SYSDUMMY1 ) aaa");
		} else if ("oracle".equalsIgnoreCase(database)) {
			sql
					.append("select to_char(sysdate,'yyyymmddhh24miss') tdate from dual ");
		}

		Connection conn = null;
		Statement stmt = null;
		String result = "";
		try {
			conn = getConnection();
			try {
				stmt = conn.createStatement();
				ResultSet rs = stmt.executeQuery(sql.toString());
				if (rs.next()) {
					result = rs.getString(1);
				}
			} finally {
				if (stmt != null) {
					stmt.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取数据库日期失败");
			e1.printStackTrace();
		} catch (Exception ex) {
			logger.error("读取数据库日期失败");
			ex.printStackTrace();
		}
		return result;
	}

}

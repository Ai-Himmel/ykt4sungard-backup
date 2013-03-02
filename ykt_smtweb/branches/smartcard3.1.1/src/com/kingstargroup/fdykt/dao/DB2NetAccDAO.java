package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dto.NetAccDTO;

public class DB2NetAccDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2NetAccDAO.class);

	public DB2NetAccDAO() {
	}

	public NetAccDTO getNetAccInfoByCustid(String custid) throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select a.* from ykt_cur.t_netacc a "
						+ " where a.custid="
						+ custid
						+ " fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select a.* from ykt_cur.t_netacc a "
						+ " where a.custid="
						+ custid
						+ " and rownum=1";
			}
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					NetAccDTO temp_DTO = new NetAccDTO();
					temp_DTO.setAccno(result.getString("accno"));
					temp_DTO.setAccname(result.getString("accname"));
					temp_DTO.setAccPwd(result.getString("accPwd"));
					temp_DTO.setStatus(result.getString("status"));
					temp_DTO.setCustid(result.getLong("custid"));
					temp_DTO.setAvailbal(result.getDouble("availbal"));
					temp_DTO.setFrozebal(result.getDouble("frozebal"));
					temp_DTO.setBalance(result.getDouble("balance"));
					temp_DTO.setLastTransDate(result.getString("lastTransDate"));
					temp_DTO.setLastaccdate(result.getString("lastaccdate"));
					temp_DTO.setOpendate(result.getString("opendate"));
					temp_DTO.setClosedate(result.getString("closedate"));
					
					return temp_DTO;
				}
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取电子帐户信息失败" + e1.getMessage() + ",custid[" + custid
					+ "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取电子帐户信息失败" + e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

}

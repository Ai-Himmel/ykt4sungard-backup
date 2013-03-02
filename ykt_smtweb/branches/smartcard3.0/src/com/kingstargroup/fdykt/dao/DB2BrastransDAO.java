package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dto.BrastransdtlDTO;
import com.kingstargroup.fdykt.util.DateUtil;

public class DB2BrastransDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DB2BrastransDAO.class);

	public String getMinUncheckBrasTransLogDate()
			throws Exception {
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		String minuncheckdate = "";
		try {
			conn = getConnection();
			stm = conn
					.prepareStatement("select min(refno) as uncheckdate from ykt_cur.t_brastransdtl where chkflag=0");
			result = stm.executeQuery();
			if (result.next()) {
				minuncheckdate = result.getString("uncheckdate");
			}
		} catch (SQLException e1) {
			logger.error("读取帐户信息失败" + e1.getMessage());
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取帐户信息失败" + e.getMessage());
			e.printStackTrace();
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
		
		if(minuncheckdate!=null&&minuncheckdate.length()>=8){
			minuncheckdate = minuncheckdate.substring(0, 8);
		}else{
			minuncheckdate=DateUtil.getNow("yyyyMMdd");
		}
		return minuncheckdate;

	}

	public ArrayList getBrasTransLog(String sql) throws ClassNotFoundException,
			SQLException, Exception {
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList brastranslog = new ArrayList();
			while (result.next()) {
				BrastransdtlDTO temp_DTO = new BrastransdtlDTO();

				temp_DTO.setCardno(result.getLong("cardno"));
				temp_DTO.setCustname(result.getString("custname"));
				temp_DTO.setStuempno(result.getString("stuempno"));
				temp_DTO.setOppaccname(result.getString("oppaccname"));
				temp_DTO.setOppaccno(result.getString("oppaccno"));
				temp_DTO.setRefno(result.getString("refno"));
				temp_DTO.setRemark(result.getString("remark"));
				temp_DTO.setStatus(result.getLong("status"));
				temp_DTO.setSummary(result.getString("summary"));
				temp_DTO.setTransamt(result.getDouble("transamt"));
				temp_DTO.setTransdate(result.getString("transdate"));
				temp_DTO.setTranstime(result.getString("transtime"));
				temp_DTO.setTranstype(result.getLong("transtype"));
				temp_DTO.setRevflag(result.getString("revflag"));
				temp_DTO.setChkflag(result.getLong("chkflag"));

				brastranslog.add(temp_DTO);
			}
			return brastranslog;
		} catch (SQLException e1) {
			logger.error("读取帐户信息失败" + e1.getMessage());
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取帐户信息失败" + e.getMessage());
			e.printStackTrace();
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
		return null;
	}

	public void createBrasTransLog(BrastransdtlDTO brastransdtl)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			sql = "insert into YKT_CUR.T_BRASTRANSDTL(REFNO, CARDNO, STUEMPNO, CUSTNAME, OPPACCNO, OPPACCNAME, TRANSDATE, TRANSTIME,TRANSTYPE,SUMMARY,TRANSAMT,STATUS,REMARK,CHKFLAG) values('"
					+ brastransdtl.getRefno()
					+ "',"
					+ brastransdtl.getCardno()
					+ ",'"
					+ brastransdtl.getStuempno()
					+ "','"
					+ brastransdtl.getCustname()
					+ "','"
					+ brastransdtl.getOppaccno()
					+ "','"
					+ brastransdtl.getOppaccname()
					+ "','"
					+ brastransdtl.getTransdate()
					+ "','"
					+ brastransdtl.getTranstime()
					+ "',"
					+ brastransdtl.getTranstype()
					+ ",'"
					+ brastransdtl.getSummary()
					+ "',"
					+ brastransdtl.getTransamt()
					+ ","
					+ brastransdtl.getStatus()
					+ ",'"
					+ brastransdtl.getSummary()
					+ "',"
					+ brastransdtl.getChkflag() + ")";

			stm = conn.prepareStatement(sql);
			stm.execute();
			conn.commit();
		} catch (SQLException e1) {
			logger.error("bras流水写失败[" + brastransdtl.getRefno() + ","
					+ brastransdtl.getCardno() + ","
					+ brastransdtl.getStuempno() + ","
					+ brastransdtl.getCustname() + ","
					+ brastransdtl.getOppaccno() + ","
					+ brastransdtl.getTransdate() + ","
					+ brastransdtl.getTranstime() + ","
					+ brastransdtl.getTranstype() + ","
					+ brastransdtl.getSummary() + ","
					+ brastransdtl.getTransamt() + ","
					+ brastransdtl.getStatus() + ","
					+ brastransdtl.getSummary());
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
	}

	public void updateBrasTransLog(BrastransdtlDTO brastransdtl)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			//			
			sql = "update YKT_CUR.T_BRASTRANSDTL set status="
					+ brastransdtl.getStatus() + ", REMARK='"
					+ brastransdtl.getRemark() + "' where refno='"
					+ brastransdtl.getRefno() + "'";

			stm = conn.prepareStatement(sql);
			stm.execute();
			conn.commit();
		} catch (SQLException e1) {
			logger.error("bras流水更新失败[" + brastransdtl.getRefno() + ","
					+ brastransdtl.getStatus() + ","
					+ brastransdtl.getSummary());
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
	}

	public void updateBrasTransLogCHKFLAG(String refno_date)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			//			
			sql = "update YKT_CUR.T_BRASTRANSDTL set chkflag=1 where refno like '"
					+ refno_date + "%'";

			stm = conn.prepareStatement(sql);
			stm.execute();
			conn.commit();
		} catch (SQLException e1) {
			logger.error("bras流水更新对账标志失败[" + refno_date + "]");
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
	}

}

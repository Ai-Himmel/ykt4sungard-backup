package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.*;
import java.util.*;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.UpdateInfoDTO;

public class DB2AccountDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2AccountDAO.class);

	public DB2AccountDAO() {
	}

	public AccountDTO getAccountInfoByCardno(String cardno)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select a.*,cus.custtype,cus.stuempno,cus.custname,c.cardtype,c.opendate,c.expiredate,('0'||c.lossflag||c.frozeflag||'0'||c.badflag||'00000') as cardstatus,cus.deptcode,ctf.custtypename from ykt_cur.t_account a "
						+ " left join YKT_CUR.T_CARD c on a.cardno=c.cardno "
						+ " left join ykt_cur.t_customer cus on a.custid=cus.custid "
						+ " left join ykt_cur.t_custtype ctf on cus.custtype=ctf.custtype "
						+ " where a.cardno="
						+ cardno
						+ " and a.status='1' fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select a.*,cus.custtype,cus.stuempno,cus.custname,c.cardtype,c.opendate,c.expiredate,('0'||c.lossflag||c.frozeflag||'0'||c.badflag||'00000') as cardstatus,cus.deptcode,ctf.custtypename from ykt_cur.t_account a "
						+ " left join YKT_CUR.T_CARD c on a.cardno=c.cardno "
						+ " left join ykt_cur.t_customer cus on a.custid=cus.custid "
						+ " left join ykt_cur.t_custtype ctf on cus.custtype=ctf.custtype "
						+ " where a.cardno="
						+ cardno
						+ " and a.status='1' and rownum=1";
			}
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					AccountDTO temp_DTO = new AccountDTO();
					temp_DTO.setAccno(result.getString("accno"));
					// temp_DTO.setAcctype(result.getLong("acctype"));
					temp_DTO.setCardno(result.getLong("cardno"));
					temp_DTO.setPurseno(result.getLong("purseno"));
					temp_DTO.setCardtype(result.getLong("cardtype"));
					temp_DTO.setCustid(result.getLong("custid"));
					temp_DTO.setCustname(result.getString("custname"));
					temp_DTO.setOpendate(result.getString("opendate"));
					temp_DTO.setExpiredate(result.getString("expiredate"));
					temp_DTO.setClosedate(result.getString("closedate"));
					temp_DTO.setLastcardcnt(result.getInt("lastcardcnt"));
					temp_DTO.setCusttype(result.getLong("custtype"));
					temp_DTO.setStuempno(result.getString("stuempno"));
					temp_DTO.setBalance(result.getFloat("balance"));
					temp_DTO.setAvailbal(result.getFloat("availbal"));
					temp_DTO.setFrozebal(result.getFloat("subsidybal"));// 带领补助金额
					temp_DTO.setLastcardbal(result.getFloat("cardbal"));
					temp_DTO.setCardstatus(result.getString("cardstatus"));
					String deptName = (String) YKTDictionary.getInstance()
							.getDictionValue(KSConstant.DICT_DEPTNAME,
									result.getString("deptcode"));
					temp_DTO.setDeptname(deptName);
					temp_DTO.setCusttypename(result.getString("custtypename"));
					return temp_DTO;
				}
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取帐户信息失败" + e1.getMessage() + ",cardno[" + cardno
					+ "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取帐户信息失败" + e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

	public ArrayList getAccountInfo(String stuempno,String cardphytype)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			// 只查询正常和写卡失败的记录
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			sql = "select a.*,cus.custtype,cus.stuempno,cus.custname,c.cardtype,c.opendate,c.expiredate,"
				+ "('0'||c.lossflag||c.frozeflag||'0'||c.badflag||'00000') as cardstatus,"
				+ "cus.deptcode,ctf.custtypename from ykt_cur.t_account a "
				+ " join YKT_CUR.T_CARD c on a.cardno=c.cardno "
				+ " join ykt_cur.t_customer cus on a.custid=cus.custid "
				+ " join ykt_cur.t_custtype ctf on cus.custtype=ctf.custtype "
				+ "where a.cardno>0 and upper(cus.stuempno)='"
				+ stuempno
				+ "' and a.status='1' and c.status='1' and c.lossflag='0' and c.frozeflag='0'";
			
			if(!"0".equals(cardphytype)){
				sql+=" and c.cardphytype="+cardphytype;
			}
			if ("db2".equalsIgnoreCase(database)) {
				sql += " fetch first 1 rows only ";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql += " and rownum=1";
			}

			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList accounts = new ArrayList();
			while (result.next()) {
				AccountDTO temp_DTO = new AccountDTO();
				temp_DTO.setAccno(result.getString("accno"));
				// temp_DTO.setAcctype(result.getLong("acctype"));
				temp_DTO.setCardno(result.getLong("cardno"));
				temp_DTO.setPurseno(result.getLong("purseno"));
				temp_DTO.setCardtype(result.getLong("cardtype"));
				temp_DTO.setCustid(result.getLong("custid"));
				temp_DTO.setCustname(result.getString("custname"));
				temp_DTO.setOpendate(result.getString("opendate"));
				temp_DTO.setExpiredate(result.getString("expiredate"));
				temp_DTO.setClosedate(result.getString("closedate"));
				temp_DTO.setLastcardcnt(result.getInt("lastcardcnt"));
				temp_DTO.setCusttype(result.getLong("custtype"));
				temp_DTO.setStuempno(result.getString("stuempno"));
				temp_DTO.setBalance(result.getFloat("balance"));
				temp_DTO.setAvailbal(result.getFloat("availbal"));
				temp_DTO.setFrozebal(result.getFloat("frozebal"));
				temp_DTO.setLastcardbal(result.getFloat("lastcardbal"));
				temp_DTO.setCardstatus(result.getString("cardstatus"));
				String deptName = (String) YKTDictionary.getInstance()
						.getDictionValue(KSConstant.DICT_DEPTNAME,
								result.getString("deptcode"));
				temp_DTO.setDeptname(deptName);
				temp_DTO.setCusttypename(result.getString("custtypename"));

				accounts.add(temp_DTO);
			}
			return accounts;
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

	public ArrayList getLossAccountInfo(String stuempno,String cardphytype)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			// 只查询正常和写卡失败的记录
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			sql = "select a.*,cus.custtype,cus.stuempno,cus.custname,c.cardtype,c.opendate,c.expiredate,('0'||c.lossflag||c.frozeflag||'0'||c.badflag||'00000') as cardstatus,cus.deptcode,ctf.custtypename from ykt_cur.t_account a "
				+ " join YKT_CUR.T_CARD c on a.cardno=c.cardno "
				+ " join ykt_cur.t_customer cus on a.custid=cus.custid "
				+ " join ykt_cur.t_custtype ctf on cus.custtype=ctf.custtype "
				+ "where a.cardno>0 and upper(cus.stuempno)='"
				+ stuempno
				+ "' and a.status='1' and c.lossflag='1'";
			
			if(!"0".equals(cardphytype)){
				sql+=" and c.cardphytype="+cardphytype;
			}
			if ("db2".equalsIgnoreCase(database)) {
				sql+= " fetch first 1 rows only ";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql += " and rownum=1";
			}
			
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList accounts = new ArrayList();
			while (result.next()) {
				AccountDTO temp_DTO = new AccountDTO();
				temp_DTO.setAccno(result.getString("accno"));
				// temp_DTO.setAcctype(result.getLong("acctype"));
				temp_DTO.setCardno(result.getLong("cardno"));
				temp_DTO.setPurseno(result.getLong("purseno"));
				temp_DTO.setCardtype(result.getLong("cardtype"));
				temp_DTO.setCustid(result.getLong("custid"));
				temp_DTO.setCustname(result.getString("custname"));
				temp_DTO.setOpendate(result.getString("opendate"));
				temp_DTO.setExpiredate(result.getString("expiredate"));
				temp_DTO.setClosedate(result.getString("closedate"));
				temp_DTO.setLastcardcnt(result.getInt("lastcardcnt"));
				temp_DTO.setCusttype(result.getLong("custtype"));
				temp_DTO.setStuempno(result.getString("stuempno"));
				temp_DTO.setBalance(result.getFloat("balance"));
				temp_DTO.setAvailbal(result.getFloat("availbal"));
				temp_DTO.setFrozebal(result.getFloat("frozebal"));
				temp_DTO.setLastcardbal(result.getFloat("lastcardbal"));
				temp_DTO.setCardstatus(result.getString("cardstatus"));
				String deptName = (String) YKTDictionary.getInstance()
						.getDictionValue(KSConstant.DICT_DEPTNAME,
								result.getString("deptcode"));
				temp_DTO.setDeptname(deptName);
				temp_DTO.setCusttypename(result.getString("custtypename"));
				accounts.add(temp_DTO);
			}
			return accounts;
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

	public int getdevidFromip(String ip) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select deviceid from ykt_cur.T_DEVICE where ip='" + ip
					+ "' and status='1'";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			if (result.next()) {
				return result.getInt("deviceid");
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
		return -1;

	}

	/**
	 * Description: 更新卡信息需要的后台信息
	 * 
	 * @param @param cardphyid
	 * @param @return
	 * @param @throws ClassNotFoundException
	 * @param @throws SQLException
	 * @param @throws Exception
	 * @return UpdateInfoDTO Modify History: 2010-8-2 Linqing.He create
	 */
	public UpdateInfoDTO getUpdateInfoByCardphyid(String cardphyid)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select a.accno,a.accname,a.custid,a.cardno,c.cardtype,a.balance,a.availbal,a.frozebal,"
						+ "c.opendate,c.expiredate,cus.stuempno,c.feetype,fee.feename "
						+ "from ykt_cur.t_account a "
						+ " left join YKT_CUR.T_CARD c on a.cardno=c.cardno "
						+ " left join ykt_cur.t_customer cus on a.custid=cus.custid "
						+ " left join ykt_cur.t_feetype fee on c.feetype=fee.feetype "
						+ " where c.cardphyid='"
						+ cardphyid
						+ "' and a.status='1' fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select a.accno,a.accname,a.custid,a.cardno,c.cardtype,a.balance,a.availbal,a.frozebal,"
						+ "c.opendate,c.expiredate,cus.stuempno,c.feetype,fee.feename "
						+ "from ykt_cur.t_account a "
						+ " left join YKT_CUR.T_CARD c on a.cardno=c.cardno "
						+ " left join ykt_cur.t_customer cus on a.custid=cus.custid "
						+ " left join ykt_cur.t_feetype fee on c.feetype=fee.feetype "
						+ " where c.cardphyid='"
						+ cardphyid
						+ "' and a.status='1' and rownum=1";
			}
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					UpdateInfoDTO temp_DTO = new UpdateInfoDTO();
					temp_DTO.setAccname(result.getString("accname"));
					temp_DTO.setAvailbal(result.getFloat("availbal"));
					temp_DTO.setBalance(result.getFloat("balance"));
					temp_DTO.setCardno(result.getLong("cardno"));
					temp_DTO.setCardphyid(cardphyid);
					temp_DTO.setCardtype(result.getLong("cardtype"));
					temp_DTO.setCustid(result.getLong("custid"));
					temp_DTO.setExpiredate(result.getString("expiredate"));
					temp_DTO.setFeename(result.getString("feename"));
					temp_DTO.setFeetype(result.getLong("feetype"));
					temp_DTO.setFrozebal(result.getFloat("frozebal"));
					temp_DTO.setOpendate(result.getString("opendate"));
					temp_DTO.setStuempno(result.getString("stuempno"));
					return temp_DTO;
				}
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取帐户信息失败" + e1.getMessage() + ",cardphyid[" + cardphyid
					+ "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取帐户信息失败" + e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

}

package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.AccountDTO;

public class DB2AccountDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2AccountDAO.class);

	public DB2AccountDAO() {
	}

	public AccountDTO getAccountInfoByCardId(String cardId)
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
				sql = "select a.*,c.begin_time,c.end_time, c.state_id,cus.classdept_no,ctf.Type_name from ykt_cur.T_AIF_Account a "
						+ " join YKT_CUR.T_PIF_CARD c on a.card_id=c.card_id "
						+ " join ykt_cur.t_cif_customer cus on a.Customer_id=cus.cut_id "
						+ " join ykt_cur.t_cif_cuttypefee ctf on cus.cut_type=ctf.cut_type "
						+ " where a.Card_id="
						+ cardId
						+ " and a.current_state=1 and a.ACT_TYPE=1 fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select a.*,c.begin_time,c.end_time, c.state_id,cus.classdept_no,ctf.Type_name from ykt_cur.T_AIF_Account a "
						+ " join YKT_CUR.T_PIF_CARD c on a.card_id=c.card_id "
						+ " join ykt_cur.t_cif_customer cus on a.Customer_id=cus.cut_id "
						+ " join ykt_cur.t_cif_cuttypefee ctf on cus.cut_type=ctf.cut_type "
						+ " where a.Card_id="
						+ cardId
						+ " and a.current_state=1 and a.ACT_TYPE=1 and rownum=1";
			}
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					AccountDTO temp_DTO = new AccountDTO();
					temp_DTO.setAccount_id(result.getString("Account_id"));
					temp_DTO.setAct_type(result.getLong("Act_type"));
					temp_DTO.setSubno(result.getString("Subno"));
					temp_DTO.setCard_id(result.getLong("Card_id"));
					temp_DTO.setPurse_id(result.getLong("Purse_id"));
					temp_DTO.setCard_type(result.getLong("Card_type"));
					temp_DTO.setCustomer_id(result.getLong("Customer_id"));
					temp_DTO.setCut_name(result.getString("Cut_name"));
					temp_DTO.setOpen_Date(result.getString("begin_time"));
					temp_DTO.setClose_Date(result.getString("end_time"));
					temp_DTO.setCon_Count(result.getInt("Consume_Count"));
					temp_DTO.setCut_type(result.getLong("Cut_type"));
					temp_DTO.setStuEmp_no(result.getString("StuEmp_no"));
					temp_DTO.setCur_Bala(result.getFloat("Cur_Bala"));
					temp_DTO.setCur_FreeBala(result.getFloat("Cur_FreeBala"));
					temp_DTO.setCur_FrozeBala(result.getFloat("Cur_FrozeBala"));
					temp_DTO.setState_id(result.getString("state_id"));
					String deptName = (String) YKTDictionary.getInstance()
							.getDictionValue(KSConstant.DICT_DEPTNAME,
									result.getString("classdept_no"));
					temp_DTO.setClassDept_name(deptName);
					temp_DTO.setType_name(result.getString("Type_name"));
					temp_DTO.setCardBalance(result.getFloat("card_balance"));
					return temp_DTO;
				}
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取帐户信息失败" + e1.getMessage() + ",cardno[" + cardId
					+ "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取帐户信息失败" + e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

	public ArrayList getAccountInfo(String stuempno)
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
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select a.*,c.begin_time,c.end_time,c.state_id,cus.ClassDept_name,ctf.Type_name from ykt_cur.T_AIF_Account a "
						+ "join YKT_CUR.T_PIF_CARD c on a.card_id=c.card_id "
						+ "join ykt_cur.t_cif_customer cus on a.Customer_id=cus.cut_id "
						+ "join ykt_cur.t_cif_cuttypefee ctf on cus.cut_type=ctf.cut_type "
						+ "where a.Card_id>0 and a.StuEmp_no='"
						+ stuempno
						+ "' and a.current_state=1 and c.STATE_ID='1000' fetch first 1 rows only ";
//						+ "where a.Card_id>0 and a.CUSTOMER_ID="
//						+ stuempno
//						+ " and a.current_state=1 and c.STATE_ID='1000' fetch first 1 rows only ";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select a.*,c.begin_time,c.end_time,c.state_id,cus.ClassDept_name,ctf.Type_name from ykt_cur.T_AIF_Account a "
						+ "join YKT_CUR.T_PIF_CARD c on a.card_id=c.card_id "
						+ "join ykt_cur.t_cif_customer cus on a.Customer_id=cus.cut_id "
						+ "join ykt_cur.t_cif_cuttypefee ctf on cus.cut_type=ctf.cut_type "
						+ "where a.Card_id>0 and cus.StuEmp_no='"
						+ stuempno
						+ "' and a.current_state=1 and c.STATE_ID='1000' and rownum=1";
				
//						+ "where a.Card_id>0 and a.CUSTOMER_ID="
//						+ stuempno
//						+ " and a.current_state=1 and c.STATE_ID='1000' and rownum=1";
			}
			

			// + " (c.state_id = '" + KSConstant.CARDSTAT_NORMAL + "' or
			// c.state_id='"
			// + KSConstant.CARDSTAT_WFAIL + "' ) ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList accounts = new ArrayList();
			while (result.next()) {
				AccountDTO temp_DTO = new AccountDTO();
				temp_DTO.setAccount_id(result.getString("Account_id"));
				temp_DTO.setAct_type(result.getLong("Act_type"));
				temp_DTO.setSubno(result.getString("Subno"));
				temp_DTO.setCard_id(result.getLong("Card_id"));
				temp_DTO.setPurse_id(result.getLong("Purse_id"));
				temp_DTO.setCard_type(result.getLong("Card_type"));
				temp_DTO.setCustomer_id(result.getLong("Customer_id"));
				temp_DTO.setCut_name(result.getString("Cut_name"));
				temp_DTO.setOpen_Date(result.getString("begin_time"));
				temp_DTO.setClose_Date(result.getString("end_time"));
				temp_DTO.setCon_Count(result.getInt("Consume_Count"));
				temp_DTO.setCut_type(result.getLong("Cut_type"));
				temp_DTO.setStuEmp_no(result.getString("StuEmp_no"));
				temp_DTO.setCur_Bala(result.getFloat("Cur_Bala"));
				temp_DTO.setCur_FreeBala(result.getFloat("Cur_FreeBala"));
				temp_DTO.setCur_FrozeBala(result.getFloat("Cur_FrozeBala"));
				temp_DTO.setState_id(result.getString("state_id"));
				temp_DTO.setClassDept_name(result.getString("ClassDept_name"));
				temp_DTO.setType_name(result.getString("Type_name"));
				temp_DTO.setCardBalance(result.getFloat("card_balance"));
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
	
	public ArrayList getLossAccountInfo(String stuempno)
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
	if ("db2".equalsIgnoreCase(database)) {
		sql = "select a.*,c.begin_time,c.end_time,c.state_id,cus.ClassDept_name,ctf.Type_name from ykt_cur.T_AIF_Account a "
				+ "join YKT_CUR.T_PIF_CARD c on a.card_id=c.card_id "
				+ "join ykt_cur.t_cif_customer cus on a.Customer_id=cus.cut_id "
				+ "join ykt_cur.t_cif_cuttypefee ctf on cus.cut_type=ctf.cut_type "
				+ "where a.Card_id>0 and a.StuEmp_no='"
				+ stuempno
				+ "' and a.current_state=1 and c.STATE_ID<>'1000' fetch first 1 rows only ";
//				+ "where a.Card_id>0 and a.CUSTOMER_ID="
//				+ stuempno
//				+ " and a.current_state=1 and c.STATE_ID<>'1000' fetch first 1 rows only ";
	} else if ("oracle".equalsIgnoreCase(database)) {
		sql = "select a.*,c.begin_time,c.end_time,c.state_id,cus.ClassDept_name,ctf.Type_name from ykt_cur.T_AIF_Account a "
				+ "join YKT_CUR.T_PIF_CARD c on a.card_id=c.card_id "
				+ "join ykt_cur.t_cif_customer cus on a.Customer_id=cus.cut_id "
				+ "join ykt_cur.t_cif_cuttypefee ctf on cus.cut_type=ctf.cut_type "
				+ "where a.Card_id>0 and a.StuEmp_no='"
				+ stuempno
				+ "' and a.current_state=1 and c.STATE_ID<>'1000' and rownum=1";
//				+ "where a.Card_id>0 and a.CUSTOMER_ID="
//				+ stuempno
//				+ " and a.current_state=1 and c.STATE_ID<>'1000' and rownum=1";
	}

	// + " (c.state_id = '" + KSConstant.CARDSTAT_NORMAL + "' or
	// c.state_id='"
	// + KSConstant.CARDSTAT_WFAIL + "' ) ";
	stm = conn.prepareStatement(sql);
	result = stm.executeQuery();
	ArrayList accounts = new ArrayList();
	while (result.next()) {
		AccountDTO temp_DTO = new AccountDTO();
		temp_DTO.setAccount_id(result.getString("Account_id"));
		temp_DTO.setAct_type(result.getLong("Act_type"));
		temp_DTO.setSubno(result.getString("Subno"));
		temp_DTO.setCard_id(result.getLong("Card_id"));
		temp_DTO.setPurse_id(result.getLong("Purse_id"));
		temp_DTO.setCard_type(result.getLong("Card_type"));
		temp_DTO.setCustomer_id(result.getLong("Customer_id"));
		temp_DTO.setCut_name(result.getString("Cut_name"));
		temp_DTO.setOpen_Date(result.getString("begin_time"));
		temp_DTO.setClose_Date(result.getString("end_time"));
		temp_DTO.setCon_Count(result.getInt("Consume_Count"));
		temp_DTO.setCut_type(result.getLong("Cut_type"));
		temp_DTO.setStuEmp_no(result.getString("StuEmp_no"));
		temp_DTO.setCur_Bala(result.getFloat("Cur_Bala"));
		temp_DTO.setCur_FreeBala(result.getFloat("Cur_FreeBala"));
		temp_DTO.setCur_FrozeBala(result.getFloat("Cur_FrozeBala"));
		temp_DTO.setState_id(result.getString("state_id"));
		temp_DTO.setClassDept_name(result.getString("ClassDept_name"));
		temp_DTO.setType_name(result.getString("Type_name"));
		temp_DTO.setCardBalance(result.getFloat("card_balance"));
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

}

package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.*;
import java.util.*;
import com.kingstargroup.fdykt.dto.CustomerDTO;

public class DB2CustomerDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2CustomerDAO.class);

	public DB2CustomerDAO() {
		
		
	}
	
	
	
	public  String getCustomerByCard(String cardId) throws  ClassNotFoundException, SQLException, Exception{
		
		String sql="";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			try {
				sql = " select t1.* from t_cif_customer t1,t_pif_card t2 "
				     +" where  t1.cut_id = t2.cosumer_id and t2.card_id="+cardId;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				result.next();
				CustomerDTO temp = new CustomerDTO();
				return result.getString("stuemp_no").toString();
			} finally {
				if (stm != null) {
					stm.close();
				}
				
			}
		} catch (SQLException e) {
			logger.error("查询数据库失败");
			e.printStackTrace();
			return null;
		} catch (Exception e) {
			logger.error("查询数据库失败");
			e.printStackTrace();
			return null;
		}
	}
		

	public void UpdateCustomer(CustomerDTO customer)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
        
		try {
			conn = getConnection();
			try {
				String stuempid = customer.getStuemp_no();
				sql = "update ykt_cur.t_cif_customer set password='"
						+ customer.getPassword() + "' where stuemp_no='"
						+ stuempid + "'";
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e) {
			logger.error("查询数据库失败");
			e.printStackTrace();
		} catch (Exception e) {
			logger.error("查询数据库失败");
			e.printStackTrace();
		}
	}

	public ArrayList RetriveCustomer(String sql) throws ClassNotFoundException,
			SQLException, Exception {
		Connection conn = null;
		PreparedStatement stm = null;
		ArrayList customers = null;
		try {
			ResultSet result;
			customers = new ArrayList();
			conn = getConnection();
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				while (result.next()) {
					CustomerDTO temp = new CustomerDTO();
					temp.setAddress(result.getString("Address"));
					temp.setArea(result.getInt("Area"));
					temp.setCan_time(result.getString("Can_time"));
					temp.setClassdept_name(result.getString("Classdept_name"));
					temp.setClassdept_no(result.getString("Classdept_no"));
					temp.setComments(result.getString("Comments"));
					temp.setCut_id(result.getInt("Cut_id"));
					temp.setCut_name(result.getString("Cut_name"));
					temp.setCut_state(result.getInt("Cut_state"));
					temp.setCut_type(result.getInt("Cut_type"));
					temp.setMan(result.getString("Man"));
					temp.setMan_id(result.getString("Man_id"));
					temp.setNation(result.getInt("Nation"));
					temp.setPassword(result.getString("Password"));
					temp.setReg_time(result.getString("Reg_time"));
					temp.setSex(result.getString("Sex"));
					temp.setStuemp_no(result.getString("Stuemp_no"));
					temp.setTel(result.getString("Tel"));
					customers.add(temp);
				}
				return customers;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e) {
			logger.error("查询客户信息失败");
			return null;
		} catch (Exception e) {
			logger.error("查询客户信息失败");
			return null;
		}
		
	}
}

package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dto.CustomerDTO;

public class DB2CustomerDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2CustomerDAO.class);

	public DB2CustomerDAO() {
	}

	public CustomerDTO getCustomer(long custid) {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();

			sql = "select * from ykt_cur.t_customer cust where cust.custid= "
					+ custid;

			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					CustomerDTO temp = new CustomerDTO();
					temp.setAddr(result.getString("addr"));
					temp.setAreacode(result.getString("areacode"));
					temp.setClasscode(result.getString("classcode"));
					temp.setDeptcode(result.getString("deptcode"));
					temp.setDeptfullname(result.getString("deptfullname"));
					temp.setCustid(result.getLong("custid"));
					temp.setCustname(result.getString("custname"));
					temp.setStatus(result.getString("status"));
					temp.setCusttype(result.getLong("custtype"));
					temp.setNation(result.getString("nation"));
					temp.setOpendate(result.getString("opendate"));
					temp.setSex(result.getString("sex"));
					temp.setStuempno(result.getString("stuempno"));
					temp.setTel(result.getString("tel"));
					return temp;
				}
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ȡ�ʻ���Ϣʧ��" + e1.getMessage() + ",custid[" + custid
					+ "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("��ȡ�ʻ���Ϣʧ��" + e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

	// public void UpdateCustomer(CustomerDTO customer)
	// throws ClassNotFoundException, SQLException, Exception {
	// String sql = "";
	// Connection conn = null;
	// PreparedStatement stm = null;
	//
	// try {
	// conn = getConnection();
	// try {
	// String stuempid = customer.getStuempno();
	// sql = "update ykt_cur.t_customer set password='"
	// + customer.getPassword() + "' where stuempno='"
	// + stuempid + "'";
	// stm = conn.prepareStatement(sql);
	// stm.executeUpdate();
	// } finally {
	// if (stm != null) {
	// stm.close();
	// }
	// }
	// } catch (SQLException e) {
	// logger.error("��ѯ���ݿ�ʧ��");
	// e.printStackTrace();
	// } catch (Exception e) {
	// logger.error("��ѯ���ݿ�ʧ��");
	// e.printStackTrace();
	// }
	// }

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

					temp.setAddr(result.getString("addr"));
					temp.setAreacode(result.getString("areacode"));
					temp.setClasscode(result.getString("classcode"));
					temp.setDeptcode(result.getString("deptcode"));
					temp.setDeptfullname(result.getString("deptfullname"));
					temp.setCustid(result.getLong("custid"));
					temp.setCustname(result.getString("custname"));
					temp.setStatus(result.getString("status"));
					temp.setCusttype(result.getLong("custtype"));
					temp.setNation(result.getString("nation"));
					temp.setOpendate(result.getString("opendate"));
					temp.setSex(result.getString("Sex"));
					temp.setStuempno(result.getString("stuempno"));
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
			logger.error("��ѯ�ͻ���Ϣʧ��");
			return null;
		} catch (Exception e) {
			logger.error("��ѯ�ͻ���Ϣʧ��");
			return null;
		}

	}
}

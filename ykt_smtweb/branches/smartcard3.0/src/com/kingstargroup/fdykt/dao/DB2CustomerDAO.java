package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.dto.NewCardInfoDTO;

public class DB2CustomerDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2CustomerDAO.class);

	public DB2CustomerDAO() {
	}
	
	public NewCardInfoDTO getPhoto(String custid){
		String sql="";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			sql="select photo.photo from ykt_cur.t_photo photo where photo.custid="+custid;
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					NewCardInfoDTO temp = new NewCardInfoDTO();
					temp.setMinphoto(result.getBlob("photo"));
					return temp;
				}
			}catch (Exception e) {
				e.printStackTrace();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (Exception e) {
			logger.error("读取新卡信息失败" + e.getMessage() + ",custid[" + custid
					+ "]");
			e.printStackTrace();
		}
		return null;
	}
	
	public NewCardInfoDTO getNewCardInfo(String showcardno){
		String sql="";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			sql="select cust.custid,cust.custname,cust.stuempno,ncc.showcardno,card.cardphyid,ncc.status " +
					"from ykt_cur.t_customer cust,ykt_cur.t_newcardchange ncc,ykt_cur.t_card card " +
					"where ncc.stuempno=cust.stuempno and cust.custid=card.custid and card.status='1' and ncc.showcardno='"+showcardno+"'";
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					NewCardInfoDTO temp = new NewCardInfoDTO();
					temp.setCustid(result.getLong("custid"));
					temp.setCustname(result.getString("custname"));
					temp.setStuempno(result.getString("stuempno"));
					temp.setShowcardno(result.getString("showcardno"));
					temp.setOldcardphyid(result.getString("cardphyid"));
					temp.setStatus(result.getInt("status"));
					return temp;
				}
			}catch (Exception e) {
				e.printStackTrace();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (Exception e) {
			logger.error("读取新卡信息失败" + e.getMessage() + ",showcardno[" + showcardno
					+ "]");
			e.printStackTrace();
		}
		return null;
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
			}catch (Exception e) {
				e.printStackTrace();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("读取帐户信息失败" + e1.getMessage() + ",custid[" + custid
					+ "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("读取帐户信息失败" + e.getMessage());
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
	// logger.error("查询数据库失败");
	// e.printStackTrace();
	// } catch (Exception e) {
	// logger.error("查询数据库失败");
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
			} catch (Exception e) {
				e.printStackTrace();
				return null;
			}finally {
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

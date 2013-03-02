package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.util.DateUtil;

public class DB2CustomerDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2CustomerDAO.class);

	public DB2CustomerDAO() {
		
	}
	
	public  boolean insertCheck(int custId,int cardId,String phyId) throws  Exception{
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
        
		try {
			conn = getConnection();
			try {
				updateKey();
			 int key =	getKey();
		     String attdate =DateUtil.getNow("yyyyMMdd");
		     String atttime = DateUtil.getNow("HHmmss");
			 sql =" insert into ykt_ck.t_attserial_record    values " 
			 		+"("+key+","+custId+","+cardId+",'"+phyId+"', '' ,'"+attdate+"','"+atttime+"', 'web' ,'"+attdate+"','"+atttime+"','0' )" ;
				
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
				return true;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e) {
			logger.error("查询数据库失败");
			e.printStackTrace();
			return false;
		} catch (Exception e) {
			logger.error("查询数据库失败");
			e.printStackTrace();
			return false;
		}

	}
	
	public int  getKey()throws Exception{
		int key=0;
		try{
			String sql = "";
			Connection conn = null;
			PreparedStatement stm = null;
			ResultSet result = null;
			
			 try {
				    conn = getConnection();
					sql =" select   key_value from   YKT_Cur.t_pif_syskey where key_code='T_Check'" ;
					stm = conn.prepareStatement(sql);
					result = stm.executeQuery();	
					while (result.next()) {
						key =  result.getInt("key_value");
						return key;
					}
			     }  
			    finally {
			 	  if (stm != null) {
					stm.close();
			 	  }
			    }
			    return key;
				} catch (SQLException e) {
					logger.error("查询数据库失败");
					e.printStackTrace();
					return key;
				} catch (Exception e) {
					logger.error("查询数据库失败");
					e.printStackTrace();
					return key;
				}
		
	}
	
	public void  updateKey()throws Exception{
		try{
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		
		 try {
			    conn = getConnection();
				sql =" update   YKT_Cur.t_pif_syskey set   key_value=key_value-1 where key_code='T_Check'" ;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();	
		     }  
		    finally {
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
	
	public List getManualCheckList(int custId, String attDate) throws Exception {
		Connection conn = null;
		PreparedStatement stm = null;
		ArrayList check = new ArrayList();
		try {
			ResultSet result;
			
			conn = getConnection();
			
		    StringBuffer querySql = new StringBuffer(1024);
		    querySql.append(" select rec.CUST_ID cust_id, rec.ATT_DATE att_date,info.IFOFFICE IFOFFICE")
				.append(" from YKT_CK.T_ATTSERIAL_RECORD rec")
				.append(" left join YKT_CK.T_CLERKINFO info on rec.CUST_ID=info.CUST_ID")
				.append(" where rec.ATT_DATE='").append(attDate)
				.append("' and rec.CUST_ID=").append(custId);
		
		stm = conn.prepareStatement(querySql.toString());
		result = stm.executeQuery();
		while (result.next()) {
			  Map  temp = new HashMap();
			  temp.put("cust_id",new Integer(result.getInt("cust_id")));
			 // temp.put("att_date",result.getString("ifoffice"));
			  temp.put("IFOFFICE",result.getString("IFOFFICE"));
			  check.add(temp);
		}
		return check;
		
	} catch (SQLException e) {
		logger.error("查询考勤信息失败");
		return null;
	} catch (Exception e) {
		logger.error("查询考勤信息失败");
		return null;
	}finally {
		if (stm != null) {
			stm.close();
		}
	}
	
}
		

	
	public boolean  getCheckManBycutId(int cutid){
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			   try{
				sql =" select cust_id from  YKT_CK.T_CLERKINFO  ck where ck.cust_id="+cutid ;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				while (result.next()) {
					return true;
				}
					return false;
			   }finally {
						if (stm != null) {
							stm.close();
						}
			    }
			} catch (SQLException e) {
				logger.error("查询数据库失败");
				e.printStackTrace();
				return false;
			} catch (Exception e) {
				logger.error("查询数据库失败");
				e.printStackTrace();
				return false;
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
	
	public ArrayList CheckCustomer(String sql) throws ClassNotFoundException,
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
			temp.setCardId(result.getInt("card_id"));
			temp.setPhyId(result.getString("physical_no"));
			
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

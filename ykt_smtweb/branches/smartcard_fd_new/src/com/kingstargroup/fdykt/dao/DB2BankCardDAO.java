package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dto.BankCheckDTO;

public class DB2BankCardDAO extends DB2ActionDAO{
	
	private static final Logger logger = Logger.getLogger(DB2BankCardDAO.class);
    
	public  List  getBankCard() 
    	throws  SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		List list  = new ArrayList();
		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_bank_check ";
			}
			try{
				stm= conn.prepareStatement(sql);
				result = stm.executeQuery();
				while (result.next()) {
					BankCheckDTO tempDTO = new BankCheckDTO();
					tempDTO.setBankName(result.getString("bank_name"));
					tempDTO.setBanktype(result.getString("bank_type"));
					tempDTO.setCardHead(result.getString("card_head"));
					tempDTO.setCardLength(result.getInt("card_length"));
					list.add(tempDTO);
				}
				return list;
			}catch (SQLException e1) {
				logger.error("读取银行字典表失败");
				throw (e1);
			}
		} catch (Exception e) {
			logger.error("读取银行字典表失败");
			throw (e);
    	} finally {
			if (stm != null) {
				stm.close();
			}
		}
	} 

}

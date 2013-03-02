package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;

public class ErrCodeDAO extends DB2ActionDAO{
	
	public  ErrCodeDAO()
	{
		
	}
	
	public  String getMsg(int code) throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			String msg="";
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)){
				 sql = " select Emsg from  ykt_cur.t_pif_errcode where Ecode="+code;
				try {
					stm = conn.prepareStatement(sql);
					result = stm.executeQuery();
					if (result.next()) {
						msg =	result.getString("Emsg");
					}else{
						msg =  "未知消息，代码未定义";
					}
				}catch(SQLException e){
					msg ="系统异常，无法查询字典信息";
					throw (e);
				}
			}
			return  msg;
		 }catch(Exception e){
				throw (e);
		}finally {
			if (stm != null) {
				stm.close();
			}
		}
	}
	
	private static final Logger logger=  Logger.getLogger(ErrCodeDAO.class);

}

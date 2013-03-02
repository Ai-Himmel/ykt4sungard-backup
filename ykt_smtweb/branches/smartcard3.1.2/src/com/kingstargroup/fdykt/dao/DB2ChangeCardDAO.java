package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dto.BrastransdtlDTO;
import com.kingstargroup.fdykt.util.DateUtil;

public class DB2ChangeCardDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DB2ChangeCardDAO.class);


	public void updateChangeCardStatus(String stage,String showcardno)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			sql = "update ykt_cur.t_newcardchange set status=";
			if("2".equals(stage)){
				sql+="2";
			}else if("3".equals(stage)){
				sql+="3";
			}else{
				sql+="1";
			}
			sql+=",lastsaved='"+DateUtil.getNow()+"'  where showcardno='"+showcardno+"'";

			stm = conn.prepareStatement(sql);
			stm.execute();
			conn.commit();
		} catch (SQLException e1) {
			logger.error("update ÐÂÉúÐ´¿¨×´Ì¬Ê§°Ü£¬ÏÔÊ¾¿¨ºÅ["+showcardno+"]×´Ì¬["+stage+"]");
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

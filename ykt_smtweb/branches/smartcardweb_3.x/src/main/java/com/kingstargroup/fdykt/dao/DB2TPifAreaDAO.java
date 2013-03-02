/**
 * 
 */
package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.kingstargroup.fdykt.dto.TPifAreaDTO;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: DB2TPifAreaDAO.java<br>
 * Description: <br>
 * Modify History����Change Log��: <br>
 * �������ͣ��������޸ĵȣ� �������� ������ �������ݼ���<br>
 * ���� Aug 11, 2006 ������ <br>
 * <p>
 * 
 * @author ������
 * @version 1.0
 * @since 1.0
 */
public class DB2TPifAreaDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2TPifAreaDAO.class);

	/**
	 * 
	 */
	public DB2TPifAreaDAO() {
		super();
		// TODO Auto-generated constructor stub
	}

	public ArrayList DB2getSchoolArea() throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		try {
			conn = getConnection();
			try {
				sql = "select a.* from ykt_cur.t_area a "
						+ " where a.fareacode=1 ";
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				ArrayList areas = new ArrayList();
				while (result.next()) {
					TPifAreaDTO temp_DTO = new TPifAreaDTO();
					temp_DTO.setAreacode(result.getString("areacode"));
					temp_DTO.setAreaname(result.getString("areaname"));
					temp_DTO.setAddr(result.getString("addr"));
					temp_DTO.setArealevel(result.getLong("arealevel"));
					temp_DTO.setRemark(result.getString("remark"));
					temp_DTO.setFareacode(result.getString("fareacode"));
					areas.add(temp_DTO);
				}
				return areas;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("DB2getSchoolArea(),��ȡ������Ϣʧ��", e1); //$NON-NLS-1$
			return null;
		} catch (Exception e) {
			logger.error("��ȡ������Ϣʧ��" + e.getMessage());
			return null;
		}
		
	}
}

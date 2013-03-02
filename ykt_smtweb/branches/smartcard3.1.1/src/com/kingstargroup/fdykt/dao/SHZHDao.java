package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.util.DBUtil;
import com.kingstargroup.fdykt.util.Transformer;

public class SHZHDao {
	private static final Logger logger = Logger.getLogger(SHZHDao.class);

	private static Transformer transformer = new Transformer();

	/**
	 * ���ѧ��������Ϣ:XS_XSJBSJB
	 * 
	 * XH:ѧ�ţ�BH:��ţ�XM:������CSRQ:�������ڣ�JG:���ᣬXJZT:ѧ��״̬
	 * 
	 * @return
	 * @throws SQLException
	 */
	public static List<Map> getXsjbsj(String xh) throws SQLException {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		List<Map> result = new ArrayList<Map>();
		try {
			conn = DBUtil.getConnection();
			if (conn == null) {
				throw new RuntimeException("���������ʧ��");
			}
			stmt = conn.createStatement();
			String sql = "select XH,BH,XM,CSRQ,JG,XJZT from sharedb.XS_XSJBSJB where XH='" + xh + "'";
			logger.debug(sql);
			rs = stmt.executeQuery(sql);
			result = transformer.transformToMap(rs);
		} finally {
			DBUtil.closeResultSet(rs);
			DBUtil.closeStatement(stmt);
			DBUtil.closeConnection(conn);
		}
		return result;
	}

	/**
	 * ���ѧ����ѧ����Ϣ:XS_JXJB
	 * 
	 * XH:ѧ�ţ�JXJBH:��ѧ���ţ�JXJDJ:��ѧ��ȼ���JXJLXM:��ѧ�������룬JXJE:��ѧ��HJNY:������
	 * 
	 * @return
	 * @throws SQLException 
	 */
	public static List<Map> getXsjxj(String xh) throws SQLException {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		List<Map> result = new ArrayList<Map>();
		try {
			conn = DBUtil.getConnection();
			if (conn == null) {
				throw new RuntimeException("���������ʧ��");
			}
			stmt = conn.createStatement();
			String sql = "select JXJBH,JXJDJ,JXJLXM,JXJE,HJNY from sharedb.XS_JXJB where XH='" + xh + "' order by HJNY desc";
			logger.debug(sql);
			rs = stmt.executeQuery(sql);
			result = transformer.transformToMap(rs);
		} finally {
			DBUtil.closeResultSet(rs);
			DBUtil.closeStatement(stmt);
			DBUtil.closeConnection(conn);
		}
		return result;
	}

	/**
	 * ���ѧ���ɼ�:XS_JXJB
	 * 
	 * XH:ѧ�ţ�XN:ѧ�꣬XQ:ѧ�ڣ�KCMC:�γ����ƣ�XF:ѧ�֣�PSCJ:ƽʱ�ɼ���QZCJ:���гɼ���QMCJ:��ĩ�ɼ���ZPCJ1:�����ɼ�1��
	 * ZPCJ2:�����ɼ�2
	 * 
	 * @return
	 * @throws SQLException 
	 */
	public static List<Map> getXscj(String xh) throws SQLException {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		List<Map> result = new ArrayList<Map>();
		try {
			conn = DBUtil.getConnection();
			if (conn == null) {
				throw new RuntimeException("���������ʧ��");
			}
			stmt = conn.createStatement();
			String sql = "select XN,XQ,KCMC,XF,PSCJ,QZCJ,QMCJ,ZPCJ1,ZPCJ2 from sharedb.XS_CJB where XH='"+xh +"' order by XN desc,XQ desc";
			logger.debug(sql);
			rs = stmt.executeQuery(sql);
			result = transformer.transformToMap(rs);
		} finally {
			DBUtil.closeResultSet(rs);
			DBUtil.closeStatement(stmt);
			DBUtil.closeConnection(conn);
		}
		return result;
	}
}

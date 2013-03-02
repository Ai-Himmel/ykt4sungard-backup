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
	 * 获得学生基本信息:XS_XSJBSJB
	 * 
	 * XH:学号，BH:班号，XM:姓名，CSRQ:出生日期，JG:籍贯，XJZT:学籍状态
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
				throw new RuntimeException("共享库连接失败");
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
	 * 获得学生奖学金信息:XS_JXJB
	 * 
	 * XH:学号，JXJBH:奖学金编号，JXJDJ:奖学金等级，JXJLXM:奖学金类型码，JXJE:奖学金额，HJNY:获奖年月
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
				throw new RuntimeException("共享库连接失败");
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
	 * 获得学生成绩:XS_JXJB
	 * 
	 * XH:学号，XN:学年，XQ:学期，KCMC:课程名称，XF:学分，PSCJ:平时成绩，QZCJ:期中成绩，QMCJ:期末成绩，ZPCJ1:总评成绩1，
	 * ZPCJ2:总评成绩2
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
				throw new RuntimeException("共享库连接失败");
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

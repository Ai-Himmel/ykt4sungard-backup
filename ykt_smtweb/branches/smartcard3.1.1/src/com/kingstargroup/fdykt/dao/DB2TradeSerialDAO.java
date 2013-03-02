package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.dto.TTifSubsidyDTO;
import com.kingstargroup.fdykt.dto.TradeSerialDTO;

public class DB2TradeSerialDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DB2TradeSerialDAO.class);

	public DB2TradeSerialDAO() {
	}

	public String getFeeTypeName(int feeType) throws Exception {
		String freetype = (String) YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_FEETYPE, String.valueOf(feeType));
		if (null == freetype) {
			return "";
		}
		return freetype;
	}

	public String getAreaName(long deviceId) throws Exception {
		String areaName = (String) YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_AREADEV, String.valueOf(deviceId));
		if (null == areaName) {
			return "";
		}
		return areaName;
	}

	public String getSerialType(String code) throws Exception {
		String type = (String) YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_SERIALTYPE, code);
		if (null == type) {
			return "";
		}
		return type;
	}

	public String getSidyStatus(String code) throws Exception {
		String status = (String) YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_SIDY_STATUS, code);
		if (null == status) {
			return "";
		}
		return status;
	}

	public String getSidyType(String code) throws Exception {
		String type = (String) YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_SIDY_TYPE, code);
		if (null == type) {
			return "";
		}
		return type;
	}

	public ArrayList getTSByCardno(String cardno, String begindate,
			String enddate, int page) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardno(cardno);
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				if (accDto!=null && accDto.getCustid() > 0) {
					sql = "select * from "
							+ "(select custid,cardno,transcode,termid,transdate,transtime,cardcnt,"
							//+ "(case when (cardaftbal-cardbefbal)>0 then  (cardaftbal-cardbefbal) else amount end) tradefee,cardbefbal,cardaftbal "
							+ "(cardaftbal-cardbefbal) tradefee,cardbefbal,cardaftbal,remark "
							+ "from ykt_cur.v_transdtl t where t.custid="
							+ accDto.getCustid()
							+ " and t.transdate>='"
							+ begindate
							+ "' and t.transdate<='"
							+ enddate
//							+ "' and t.status=3  ) tt order by transdate desc,cardno desc,cardcnt desc,transtime desc fetch first 1000 rows only with ur";
							+ "' and t.status=3  ) tt order by transdate desc,transtime desc fetch first 1000 rows only with ur";
				} else {
					sql = "select * from "
							+ "(select custid,cardno,transcode,termid,transdate,transtime,cardcnt,"
							//+ "(case when (cardaftbal-cardbefbal)>0 then  (cardaftbal-cardbefbal) else amount end) tradefee,cardbefbal,cardaftbal "
							+ "(cardaftbal-cardbefbal) tradefee,cardbefbal,cardaftbal,remark "
							+ "from ykt_cur.v_transdtl t where t.cardno="
							+ cardno
							+ "' and t.transdate>='"
							+ begindate
							+ "' and t.transdate<='"
							+ enddate
//							+ "' and t.status=3  ) tt order by transdate desc,cardno desc,cardcnt desc,transtime desc fetch first 1000 rows only with ur";
							+ "' and t.status=3  ) tt order by transdate desc,transtime desc fetch first 1000 rows only with ur";
				}

			} else if ("oracle".equalsIgnoreCase(database)) {
				if (accDto!=null && accDto.getCustid() > 0) {
					sql = "select * from "
							+ "(select custid,cardno,transcode,termid,transdate,transtime,cardcnt,"							
							//+ "(case when (cardaftbal-cardbefbal)>0 then  (cardaftbal-cardbefbal) else amount end) tradefee,cardbefbal,cardaftbal "
							+ "(cardaftbal-cardbefbal) tradefee,cardbefbal,cardaftbal,remark "
							+ "from ykt_cur.v_transdtl t where t.custid="
							+ accDto.getCustid()
							+ " and t.transdate>='"
							+ begindate
							+ "' and t.transdate<='"
							+ enddate
//							+ "' and t.status=3  ) tt where rownum <=1000 order by transdate desc,cardno desc, cardcnt desc,transtime desc";
							+ "' and t.status=3  " +
									"and (t.transcode=3140 or t.transcode=3141 or t.transcode=3160 or t.transcode=3161 " +
									"or t.transcode=3170 or t.transcode=3180 or t.transcode=3200 or t.transcode=3210 " +
									"or t.transcode=3220 or t.transcode=3230 or t.transcode=3040 or t.transcode=3050 " +
									"or t.transcode=3060 or t.transcode=3070 or t.transcode=3080 or t.transcode=3100 " +
									"or t.transcode=6040 or t.transcode=6050 or t.transcode=6230 or t.transcode=6240 " +
									"or t.transcode=6020 or t.transcode=3101 or t.transcode=3270)) tt where rownum <=1000 order by transdate desc,transtime desc";
				} else {
					sql = "select * from "
							+ "(select custid,cardno,transcode,termid,transdate,transtime,cardcnt,"
							//+ "(case when (cardaftbal-cardbefbal)>0 then  (cardaftbal-cardbefbal) else amount end) tradefee,cardbefbal,cardaftbal "
							+ "(cardaftbal-cardbefbal) tradefee,cardbefbal,cardaftbal,remark "
							+ "from ykt_cur.v_transdtl t where t.cardno='"
							+ cardno
							+ "' and t.transdate>='"
							+ begindate
							+ "' and t.transdate<='"
							+ enddate
//							+ "' and t.status=3  ) tt where rownum <=1000 order by transdate desc,cardno desc, cardcnt desc,transtime desc";
							+ "' and t.status=3  " +
							"and (t.transcode=3140 or t.transcode=3141 or t.transcode=3160 or t.transcode=3161 " +
									"or t.transcode=3170 or t.transcode=3180 or t.transcode=3200 or t.transcode=3210 " +
									"or t.transcode=3220 or t.transcode=3230 or t.transcode=3040 or t.transcode=3050 " +
									"or t.transcode=3060 or t.transcode=3070 or t.transcode=3080 or t.transcode=3100 " +
									"or t.transcode=6040 or t.transcode=6050 or t.transcode=6230 or t.transcode=6240 " +
									"or t.transcode=6020 or t.transcode=3101 or t.transcode=3270)) tt where rownum <=1000 order by transdate desc,transtime desc";
				}

			}
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				ArrayList tradeserials = new ArrayList();
				int start = 0;
				while ((start++ < page - 1) && result.next()) {
					;
				}
				int count = 10;
				while (result.next() && (count-- > 0)) {
					TradeSerialDTO temp_TradeSerialDTO = new TradeSerialDTO();
					temp_TradeSerialDTO.setCustid(result.getLong("custid"));
					temp_TradeSerialDTO.setCardno(result.getLong("cardno"));
					temp_TradeSerialDTO.setTransname(getSerialType(result
							.getString("transcode")));
					temp_TradeSerialDTO.setAreaname(getAreaName(result
							.getLong("termid")));

					temp_TradeSerialDTO.setTransdate(result
							.getString("transdate"));
					temp_TradeSerialDTO.setTranstime(result
							.getString("transtime"));
					temp_TradeSerialDTO.setCardcnt(result.getLong("cardcnt"));

					temp_TradeSerialDTO.setAmount(result.getFloat("tradefee"));

					temp_TradeSerialDTO.setCardaftbal(result
							.getFloat("cardaftbal"));
					temp_TradeSerialDTO.setCardbefbal(result
							.getFloat("cardbefbal"));
					temp_TradeSerialDTO.setRemark(result
							.getString("remark"));
					tradeserials.add(temp_TradeSerialDTO);
				}
				return tradeserials;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}

		} catch (SQLException e1) {
			logger.error("查询交易流水失败,cardno[" + cardno + "]");
			return null;
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (stm != null) {
				stm.close();
			}
		}

	}

	/**
	 * File name: DB2TradeSerialDAO.java<br>
	 * Description: <br>
	 * 根据卡号和时间查询补助流水 Return:
	 * 
	 * @param cardId
	 *            Return:
	 * @param begindate
	 *            Return:
	 * @param enddate
	 *            Return:
	 * @param page
	 *            Return:
	 * @return Return:
	 * @throws ClassNotFoundException
	 *             Return:
	 * @throws SQLException
	 *             Return:
	 * @throws Exception
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-4-11 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public ArrayList getAssistanceSerial(long cardno, String sidyno, int page)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select * from ykt_cur.t_subsidy where CARDNO=" + cardno
					+ " and (status='2') and SUBSIDYNO>" + sidyno
					+ " order by SUBSIDYNO desc";
			logger.debug("sql [" + sql + "]");
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList sidys = new ArrayList();
			int start = 0;
			while ((start++ < page - 1) && result.next()) {
				;
			}
			int count = 10;
			while (result.next() && (count-- > 0)) {
				TTifSubsidyDTO ttifsubsidydto = new TTifSubsidyDTO();
				ttifsubsidydto.setAmount(Double.parseDouble(result
						.getString("amount")));
				ttifsubsidydto.setBatchno(result.getString("batchno"));
				ttifsubsidydto.setCardno(Long.parseLong(result
						.getString("cardno")));
				ttifsubsidydto.setCustid(Long.parseLong(result
						.getString("custid")));
				ttifsubsidydto.setErrmsg(result.getString("errmsg"));
				ttifsubsidydto.setGetdate(result.getString("getdate"));
				ttifsubsidydto.setGettime(result.getString("gettime"));
				ttifsubsidydto.setPaytype(Long.parseLong(result
						.getString("paytype")));
				ttifsubsidydto.setPutdate(result.getString("putdate"));
				ttifsubsidydto.setPuttime(result.getString("puttime"));
				ttifsubsidydto.setSeqno(Long.parseLong(result
						.getString("seqno")));
				ttifsubsidydto.setStatus("未领取");
				ttifsubsidydto.setSubsidyno(Long.parseLong(result
						.getString("subsidyno")));
				ttifsubsidydto.setStuempno(result.getString("stuempno"));
				ttifsubsidydto.setSubsidytype(result.getString("subsidytype"));
				ttifsubsidydto.setSummary(result.getString("summary"));
				sidys.add(ttifsubsidydto);
			}
			return sidys;

		} catch (SQLException e1) {
			logger.error("查询补助流水失败,cardno[" + cardno + "]");
			e1.printStackTrace();
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
	
	public ArrayList getAssistanceSerial(long custid, int page)
	throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		
		try {
			conn = getConnection();
			sql = "select * from ykt_cur.t_subsidy where custid=" + custid
					+ " and status='2' order by SUBSIDYNO desc";
			logger.debug("sql [" + sql + "]");
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList sidys = new ArrayList();
			int start = 0;
			while ((start++ < page - 1) && result.next()) {
				;
			}
			int count = 10;
			while (result.next() && (count-- > 0)) {
				TTifSubsidyDTO ttifsubsidydto = new TTifSubsidyDTO();
				ttifsubsidydto.setAmount(Double.parseDouble(result
						.getString("amount")));
				ttifsubsidydto.setBatchno(result.getString("batchno"));
				ttifsubsidydto.setCardno(Long.parseLong(result
						.getString("cardno")));
				ttifsubsidydto.setCustid(Long.parseLong(result
						.getString("custid")));
				ttifsubsidydto.setErrmsg(result.getString("errmsg"));
				ttifsubsidydto.setGetdate(result.getString("getdate"));
				ttifsubsidydto.setGettime(result.getString("gettime"));
				ttifsubsidydto.setPaytype(Long.parseLong(result
						.getString("paytype")));
				ttifsubsidydto.setPutdate(result.getString("putdate"));
				ttifsubsidydto.setPuttime(result.getString("puttime"));
				ttifsubsidydto.setSeqno(Long.parseLong(result
						.getString("seqno")));
				ttifsubsidydto.setStatus("未领取");
				ttifsubsidydto.setSubsidyno(Long.parseLong(result
						.getString("subsidyno")));
				ttifsubsidydto.setStuempno(result.getString("stuempno"));
				ttifsubsidydto.setSubsidytype(result.getString("subsidytype"));
				ttifsubsidydto.setSummary(result.getString("summary"));
				sidys.add(ttifsubsidydto);
			}
			return sidys;
		
		} catch (SQLException e1) {
			logger.error("查询补助流水失败,custid[" + custid + "]");
			e1.printStackTrace();
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

	/**
	 * File name: DB2TradeSerialDAO.java<br>
	 * Description: <br>
	 * 查询补助流水的条数
	 * 
	 * Return:
	 * 
	 * @param cardId
	 *            Return:
	 * @param begindate
	 *            Return:
	 * @param enddate
	 *            Return:
	 * @return Return:
	 * @throws ClassNotFoundException
	 *             Return:
	 * @throws SQLException
	 *             Return:
	 * @throws Exception
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-4-11 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public int getSidyCountByCardno(String cardno, String begindate,
			String enddate) throws ClassNotFoundException, SQLException,
			Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			// DB2AccountDAO acc = new DB2AccountDAO();
			// AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_subsidy where cardno="
					+ cardno + " and PUTDATE>='" + begindate
					+ "' and PUTDATE<='" + enddate
					+ "' and (status='2' or status='3')";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			result.next();
			return result.getInt("count");
		} catch (SQLException e1) {
			logger.error("查询流水数失败");
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

	public int getSidyCountByCardNo(long cardno) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_subsidy where cardno="
					+ cardno + " and status='2' ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			if (result.next()) {
				return result.getInt("count");
			} else {
				return 0;
			}

		} catch (SQLException e1) {
			logger.error("查询流水数失败");
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

	/**
	 * File name: DB2TradeSerialDAO.java<br>
	 * Description: <br>
	 * 查询没有领取的补助的条数 Return:
	 * 
	 * @param cardId
	 *            Return:
	 * @return Return:
	 * @throws ClassNotFoundException
	 *             Return:
	 * @throws SQLException
	 *             Return:
	 * @throws Exception
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-4-13 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public int getSidyCountByCardId(long cardno, String sidyno)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_subsidy where cardno ="
					+ cardno + " and (status='2') ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			if (result.next()) {
				return result.getInt("count");
			} else {
				return 0;
			}

		} catch (SQLException e1) {
			logger.error("查询流水数失败");
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
	
	public int getSidyCountByCustid(long custid)
	throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		
		try {
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_subsidy where custid ="
					+ custid + " and status='2' ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			if (result.next()) {
				return result.getInt("count");
			} else {
				return 0;
			}
		
		} catch (SQLException e1) {
			logger.error("查询流水数失败");
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

	/**
	 * File name: DB2TradeSerialDAO.java<br>
	 * Description: <br>
	 * 返回一笔没有领取的最早的补助 没有则返回ｎｕｌｌ Return:
	 * 
	 * @param cardId
	 *            Return:
	 * @return Return:
	 * @throws ClassNotFoundException
	 *             Return:
	 * @throws SQLException
	 *             Return:
	 * @throws Exception
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-4-13 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public TTifSubsidyDTO getAssistanceByCardId(long cardno, String sidyno)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_subsidy where cardno = "
						+ cardno + " and status='2' and SUBSIDYNO>" + sidyno
						+ " order by SUBSIDYNO fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_tif_subsidy where cardno = "
						+ cardno + " and status='2' and SUBSIDYNO>" + sidyno
						+ " and rownum=1 order by SUBSIDYNO";
			}
			logger.debug("sql [" + sql + "]");
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			TTifSubsidyDTO ttifsubsidydto = null;

			if (result.next()) {
				ttifsubsidydto = new TTifSubsidyDTO();
				ttifsubsidydto.setAmount(Long.parseLong(result
						.getString("amount")));
				ttifsubsidydto.setBatchno(result.getString("batchno"));
				ttifsubsidydto.setCardno(Long.parseLong(result
						.getString("cardno")));
				ttifsubsidydto.setCustid(Long.parseLong(result
						.getString("custid")));
				ttifsubsidydto.setErrmsg(result.getString("errmsg"));
				ttifsubsidydto.setGetdate(result.getString("getdate"));
				ttifsubsidydto.setGettime(result.getString("gettime"));
				ttifsubsidydto.setPaytype(Long.parseLong(result
						.getString("paytype")));
				ttifsubsidydto.setPutdate(result.getString("putdate"));
				ttifsubsidydto.setPuttime(result.getString("puttime"));
				ttifsubsidydto.setSeqno(Long.parseLong(result
						.getString("seqno")));
				ttifsubsidydto.setStatus(result.getString("status"));
				ttifsubsidydto.setSubsidyno(Long.parseLong(result
						.getString("subsidyno")));
				ttifsubsidydto.setStuempno(result.getString("stuempno"));
				ttifsubsidydto.setSubsidytype(result.getString("subsidytype"));
				ttifsubsidydto.setSummary(result.getString("summary"));
			}
			return ttifsubsidydto;

		} catch (SQLException e1) {
			logger.error("查询补助流水失败,cardId[" + cardno + "]");
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

	/**
	 * File name: DB2TradeSerialDAO.java<br>
	 * Description: <br>
	 * 查询没有领取的补助的条数 Return:
	 * 
	 * @param cardId
	 *            Return:
	 * @return Return:
	 * @throws ClassNotFoundException
	 *             Return:
	 * @throws SQLException
	 *             Return:
	 * @throws Exception
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-4-13 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	// public int getSidyCountByCustNo(long custid) throws
	// ClassNotFoundException,
	// SQLException, Exception {
	// String sql = "";
	// Connection conn = null;
	// PreparedStatement stm = null;
	// ResultSet result = null;
	//
	// try {
	// conn = getConnection();
	// sql = "select count(*) count from ykt_cur.t_tif_subsidy where custid="
	// + custid + " and status='2' ";
	// stm = conn.prepareStatement(sql);
	// result = stm.executeQuery();
	// if (result.next()) {
	// return result.getInt("count");
	// } else {
	// return 0;
	// }
	//
	// } catch (SQLException e1) {
	// logger.error("查询流水数失败");
	// throw (e1);
	// } catch (Exception e) {
	// e.printStackTrace();
	// throw (e);
	// } finally {
	// if (stm != null) {
	// stm.close();
	// }
	// }
	// }
	// public ArrayList getTradeSerialByCollDate(String stuempno,
	// String begindate, String enddate, int page, HashMap device,
	// HashMap trademsg) throws ClassNotFoundException, SQLException,
	// Exception {
	// String sql = "";
	// Connection conn = null;
	// PreparedStatement stm = null;
	// ResultSet result = null;
	//
	// try {
	// conn = getConnection();
	//
	// sql = "select tradelog.* from ykt_cur.T_TIF_TradeLog tradelog "
	// + "join ykt_cur.T_AIF_Account account on
	// tradelog.Act_id=account.Account_id "
	// + "join ykt_cur.t_customer customer on
	// account.Customer_id=customer.Cut_id, "
	// + "(select Serino,Seri_type,Fee_type,Act_id , "
	// + "row_number() over (order by Serino,Seri_type,Fee_type,Act_id ) num "
	// + "from ykt_cur.T_TIF_TradeLog tradelog "
	// + "join ykt_cur.T_AIF_Account account on
	// tradelog.Act_id=account.Account_id "
	// + "join ykt_cur.t_customer customer on
	// account.Customer_id=customer.Cut_id "
	// + "where customer.stuemp_no='"
	// + stuempno
	// + "'"
	// + "and tradelog.operate_date>='"
	// + begindate
	// + "' and tradelog.operate_date<='"
	// + enddate
	// + "' "
	// + ") tt where tradelog.Serino=tt.Serino and
	// tradelog.Seri_type=tt.Seri_type and "
	// + "tradelog.Fee_type=tt.Fee_type and tradelog.Act_id=tt.Act_id and "
	// + " customer.stuemp_no='" + stuempno + "' "
	// + "and tradelog.operate_date>='" + begindate
	// + "' and tradelog.operate_date<='" + enddate + "' "
	// + "and tt.num>=" + page + " and tt.num<=" + (page + 9);
	// // System.out.println(sql);
	// /*
	// * sql = "SELECT T.* FROM YKT_CUR.T_TIF_TRADESERIAL T,(SELECT
	// * SERIAL_NO,ROW_NUMBER() OVER (ORDER BY SERIAL_NO) NUM FROM
	// * YKT_CUR.T_TIF_TRADESERIAL t2 join ykt_cur.t_customer c1 on
	// * t2.customer_id=c1.cut_id where c1.stuemp_no='" + stuempno + "'
	// * and t2.operate_date<='" + enddate + "' and t2.operate_date>='" +
	// * begindate + "') T1 WHERE T.SERIAL_NO=T1.SERIAL_NO AND T1.NUM>=" +
	// * page + " and T1.NUM<=" + (page + 9);
	// */
	// try {
	// stm = conn.prepareStatement(sql);
	// result = stm.executeQuery();
	// ArrayList tradeserials = new ArrayList();
	//
	// while (result.next()) {
	// TradeSerialDTO temp_TradeSerialDTO = new TradeSerialDTO();
	// temp_TradeSerialDTO.setSerial_type((String) trademsg
	// .get(result.getString("Seri_type")));
	// temp_TradeSerialDTO.setArea_name(getAreaName(result
	// .getInt("Device_Id")));
	// temp_TradeSerialDTO.setDict_caption(getFeeTypeName(result
	// .getInt("Fee_Type")));
	// temp_TradeSerialDTO.setOperate_Date(result
	// .getString("Operate_Date"));
	// temp_TradeSerialDTO.setOperate_time(result
	// .getString("Operate_time"));
	// temp_TradeSerialDTO.setTrade_Fee(result.getFloat("Op_Fee"));
	// temp_TradeSerialDTO.setFreeBala(result.getFloat("New_Fee")
	// - result.getFloat("Cur_FrozeBala"));
	// temp_TradeSerialDTO.setFrozeBala(result
	// .getFloat("Cur_FrozeBala"));
	// tradeserials.add(temp_TradeSerialDTO);
	// }
	// return tradeserials;
	// } finally {
	// if (stm != null) {
	// stm.close();
	// }
	// }
	// } catch (SQLException e1) {
	// logger.error("查询流水失败,stuempno[" + stuempno + "]");
	// return null;
	// } catch (Exception e) {
	// e.printStackTrace();
	// return null;
	// }
	// }
	public int getCountByCardno(String cardno, String begindate, String enddate)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {

			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardno(cardno);
			conn = getConnection();
			if (accDto!=null && accDto.getCustid() > 0)  {
				sql = "select count(*) count "
						+ "from ykt_cur.v_transdtl t where t.custid=" + accDto.getCustid()
						+ " and t.transdate>='"+ begindate 
						+ "' and t.transdate<='" + enddate
						+ "' and t.status=3 " +
						"and (t.transcode=3140 or t.transcode=3141 or t.transcode=3160 or t.transcode=3161 " +
						"or t.transcode=3170 or t.transcode=3180 or t.transcode=3200 or t.transcode=3210 " +
						"or t.transcode=3220 or t.transcode=3230 or t.transcode=3040 or t.transcode=3050 " +
						"or t.transcode=3060 or t.transcode=3070 or t.transcode=3080 or t.transcode=3100 " +
						"or t.transcode=6040 or t.transcode=6050 or t.transcode=6230 or t.transcode=6240 " +
						"or t.transcode=6020 or t.transcode=3101 or t.transcode=3270) ";
			} else {
				sql = "select count(*) count "
						+ "from ykt_cur.v_transdtl t where t.cardno='" + cardno
						+ "' and t.transdate>='" + begindate
						+ "' and t.transdate<='" + enddate
						+ "' and t.status=3  " +
						"and (t.transcode=3140 or t.transcode=3141 or t.transcode=3160 or t.transcode=3161 " +
						"or t.transcode=3170 or t.transcode=3180 or t.transcode=3200 or t.transcode=3210 " +
						"or t.transcode=3220 or t.transcode=3230 or t.transcode=3040 or t.transcode=3050 " +
						"or t.transcode=3060 or t.transcode=3070 or t.transcode=3080 or t.transcode=3100 " +
						"or t.transcode=6040 or t.transcode=6050 or t.transcode=6230 or t.transcode=6240 " +
						"or t.transcode=6020 or t.transcode=3101 or t.transcode=3270) ";
			}

			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				result.next();
				return result.getInt("count");
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("查询流水数失败");
			e1.printStackTrace();
			return 0;
		} catch (Exception e) {
			e.printStackTrace();
			return 0;
		}
	}

	public CustomerDTO getcustomer(long custid) throws ClassNotFoundException,
			SQLException, Exception {
		CustomerDTO dto = null;
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_customer where custid=" + custid
						+ " fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_customer where custid=" + custid
						+ " and rownum=1 ";
			}

			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();

			if (result.next()) {
				dto = new CustomerDTO();
				dto.setCustid(result.getLong("custid"));
				dto.setCustname(result.getString("custname"));
				dto.setStuempno(result.getString("stuempno"));

			}
			return dto;

		} catch (SQLException e1) {
			logger.error("查询客户信息失败,custNo[" + custid + "]");
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

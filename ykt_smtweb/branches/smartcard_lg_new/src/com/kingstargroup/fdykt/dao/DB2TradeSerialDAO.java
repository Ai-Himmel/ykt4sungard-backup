package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

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

	public String getAreaName(int deviceId) throws Exception {
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

	public ArrayList getTSByCardId(String cardId, String begindate,
			String enddate, int page) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select * from ("
						+ "select Act_id,Seri_type,Device_Id,Comments,Operate_Date,Operate_time,(case when outorin =1 then -1 else 1 end)*Op_Fee Op_Fee,New_Fee,his.Cur_FrozeBala "
						+ "from ykt_his.t_tif_tradelog_his his "
						+ "where his.Act_id='"
						+ accDto.getAccount_id()
						+ "' and  his.operate_date>='"
						+ begindate
						+ "' and his.operate_date<='"
						+ enddate
						+ "'  union all "
						+ "select Act_id,Seri_type,Device_Id,Comments,Operate_Date,Operate_time,(case when outorin =1 then -1 else 1 end)*Op_Fee Op_Fee,New_Fee,log.Cur_FrozeBala "
						+ "from ykt_cur.T_TIF_TradeLog  log "
						+ "where log.Act_id='"
						+ accDto.getAccount_id()
						+ "' and log.operate_date>='"
						+ begindate
						+ "' and log.operate_date<='"
						+ enddate
						+ "' )  tt order by Operate_Date desc,Operate_time desc fetch first 1000 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from ("
						+ "select Act_id,Seri_type,Device_Id,Comments,Operate_Date,Operate_time,(case when outorin =1 then -1 else 1 end)*Op_Fee Op_Fee,New_Fee,his.Cur_FrozeBala "
						+ "from ykt_his.t_tif_tradelog_his his "
						+ "where his.Act_id='"
						+ accDto.getAccount_id()
						+ "' and  his.operate_date>='"
						+ begindate
						+ "' and his.operate_date<='"
						+ enddate
						+ "'  union all "
						+ "select Act_id,Seri_type,Device_Id,Comments,Operate_Date,Operate_time,(case when outorin =1 then -1 else 1 end)*Op_Fee Op_Fee,New_Fee,log.Cur_FrozeBala "
						+ "from ykt_cur.T_TIF_TradeLog log "
						+ "where log.Act_id='"
						+ accDto.getAccount_id()
						+ "' and log.operate_date>='"
						+ begindate
						+ "' and log.operate_date<='"
						+ enddate
						+ "' )  tt where rownum <=1000 order by Operate_Date desc,Operate_time desc";
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
					temp_TradeSerialDTO.setSerial_type(getSerialType(result
							.getString("Seri_type")));
					temp_TradeSerialDTO.setArea_name(getAreaName(result
							.getInt("Device_Id")));
					temp_TradeSerialDTO.setDict_caption(result
							.getString("Comments"));
					temp_TradeSerialDTO.setOperate_Date(result
							.getString("Operate_Date"));
					temp_TradeSerialDTO.setOperate_time(result
							.getString("Operate_time"));
					temp_TradeSerialDTO.setTrade_Fee(result.getFloat("Op_Fee"));
					temp_TradeSerialDTO.setFreeBala(result.getFloat("New_Fee")
							- result.getFloat("Cur_FrozeBala"));
					temp_TradeSerialDTO.setFrozeBala(result
							.getFloat("Cur_FrozeBala"));
					tradeserials.add(temp_TradeSerialDTO);
				}
				return tradeserials;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}

		} catch (SQLException e1) {
			logger.error("查询交易流水失败,cardno[" + cardId + "]");
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
	public ArrayList getAssistanceSerial(String cardId, String begindate,
			String enddate, int page) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			sql = "select * from ykt_cur.t_tif_subsidy where cust_no="
					+ accDto.getCustomer_id() + " and tx_date>='" + begindate
					+ "' and tx_date<='" + enddate
					+ "' and status<>'1' order by status,get_date desc  ";
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
				ttifsubsidydto.setBatchNo(result.getString("batch_no"));
				ttifsubsidydto.setCardNo(Integer.valueOf(result
						.getString("card_no")));
				ttifsubsidydto.setCustNo(Integer.valueOf(result
						.getString("cust_no")));
				ttifsubsidydto.setExpireDate(result.getString("expire_date"));
				ttifsubsidydto.setGetDate(result.getString("get_date"));
				ttifsubsidydto.setGetTime(result.getString("get_time"));
				ttifsubsidydto.setStatus(getSidyStatus(result
						.getString("status")));
				ttifsubsidydto.setSubsidyNo(result.getString("subsidy_no"));
				ttifsubsidydto.setSubsidytype(getSidyType(result
						.getString("subsidytype")));
				ttifsubsidydto.setSummary(result.getString("summary"));
				ttifsubsidydto.setTxDate(result.getString("tx_date"));
				ttifsubsidydto.setTxTime(result.getString("tx_time"));
				sidys.add(ttifsubsidydto);
			}
			return sidys;

		} catch (SQLException e1) {
			logger.error("查询补助流水失败,cardno[" + cardId + "]");
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
     
	public ArrayList getAssistanceSerial(String cardId, 
			 int page) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			sql = "select * from ykt_cur.t_tif_subsidy where cust_no="
					+ accDto.getCustomer_id() 
					+ " and status='2' order by tx_date  ";
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
				ttifsubsidydto.setSubsidyNo(result.getString("subsidy_no"));
				ttifsubsidydto.setBatchNo(result.getString("batch_no"));
				ttifsubsidydto.setCardNo(Integer.valueOf(result
						.getString("card_no")));
				ttifsubsidydto.setCustNo(Integer.valueOf(result
						.getString("cust_no")));
				ttifsubsidydto.setExpireDate(result.getString("expire_date"));
				ttifsubsidydto.setGetDate(result.getString("get_date"));
				ttifsubsidydto.setGetTime(result.getString("get_time"));
				ttifsubsidydto.setStatus(getSidyStatus(result
						.getString("status")));
				ttifsubsidydto.setSubsidyNo(result.getString("subsidy_no"));
				ttifsubsidydto.setSubsidytype(getSidyType(result
						.getString("subsidytype")));
				ttifsubsidydto.setSummary(result.getString("summary"));
				ttifsubsidydto.setTxDate(result.getString("tx_date"));
				ttifsubsidydto.setTxTime(result.getString("tx_time"));
				sidys.add(ttifsubsidydto);
			}
			return sidys;

		} catch (SQLException e1) {
			logger.error("查询补助流水失败,cardno[" + cardId + "]");
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
	public TTifSubsidyDTO getAssistanceByCustNo(String custNo)
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
				sql = "select * from ykt_cur.t_tif_subsidy where cust_no="
						+ custNo + " and status='2' fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_tif_subsidy where cust_no="
						+ custNo + " and status='2' and rownum=1 ";
			}
			logger.debug("sql [" + sql + "]");
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			TTifSubsidyDTO ttifsubsidydto = null;

			if (result.next()) {
				ttifsubsidydto = new TTifSubsidyDTO();
				ttifsubsidydto.setAmount(Double.parseDouble(result
						.getString("amount")));
				ttifsubsidydto.setBatchNo(result.getString("batch_no"));
				ttifsubsidydto.setCardNo(Integer.valueOf(result
						.getString("card_no")));
				ttifsubsidydto.setCustNo(Integer.valueOf(result
						.getString("cust_no")));
				ttifsubsidydto.setExpireDate(result.getString("expire_date"));
				ttifsubsidydto.setGetDate(result.getString("get_date"));
				ttifsubsidydto.setGetTime(result.getString("get_time"));
				ttifsubsidydto.setStatus(getSidyStatus(result
						.getString("status")));
				ttifsubsidydto.setSubsidyNo(result.getString("subsidy_no"));
				ttifsubsidydto.setSubsidytype(getSidyType(result
						.getString("subsidytype")));
				ttifsubsidydto.setSummary(result.getString("summary"));
				ttifsubsidydto.setTxDate(result.getString("tx_date"));
				ttifsubsidydto.setTxTime(result.getString("tx_time"));
			}
			return ttifsubsidydto;

		} catch (SQLException e1) {
			logger.error("查询补助流水失败,custNo[" + custNo + "]");
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

	public TTifSubsidyDTO getLatestAssistanceByCustNo(String custNo)
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
				sql = "select * from ykt_cur.t_tif_subsidy where cust_no="
						+ custNo
						+ " and status='3' order by get_date desc,get_time desc fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from ykt_cur.t_tif_subsidy where cust_no="
						+ custNo
						+ " and status='2' and rownum=1 order by get_date desc,get_time desc";
			}
			logger.debug("sql [" + sql + "]");
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			TTifSubsidyDTO ttifsubsidydto = null;

			if (result.next()) {
				ttifsubsidydto = new TTifSubsidyDTO();
				ttifsubsidydto.setAmount(Double.parseDouble(result
						.getString("amount")));
				ttifsubsidydto.setBatchNo(result.getString("batch_no"));
				ttifsubsidydto.setCardNo(Integer.valueOf(result
						.getString("card_no")));
				ttifsubsidydto.setCustNo(Integer.valueOf(result
						.getString("cust_no")));
				ttifsubsidydto.setExpireDate(result.getString("expire_date"));
				ttifsubsidydto.setGetDate(result.getString("get_date"));
				ttifsubsidydto.setGetTime(result.getString("get_time"));
				ttifsubsidydto.setStatus(getSidyStatus(result
						.getString("status")));
				ttifsubsidydto.setSubsidyNo(result.getString("subsidy_no"));
				ttifsubsidydto.setSubsidytype(getSidyType(result
						.getString("subsidytype")));
				ttifsubsidydto.setSummary(result.getString("summary"));
				ttifsubsidydto.setTxDate(result.getString("tx_date"));
				ttifsubsidydto.setTxTime(result.getString("tx_time"));
			}
			return ttifsubsidydto;

		} catch (SQLException e1) {
			logger.error("查询补助流水失败,custNo[" + custNo + "]");
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
	public int getSidyCountByCardId(String cardId, String begindate,
			String enddate) throws ClassNotFoundException, SQLException,
			Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_tif_subsidy where cust_no="
					+ accDto.getCustomer_id()
					+ " and tx_date>='"
					+ begindate
					+ "' and tx_date<='" + enddate + "' ";
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
    //取得所有未领取的补助
	public int getSidyCountByCardId(String cardId) throws ClassNotFoundException, SQLException,
			Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_tif_subsidy where cust_no="
					+ accDto.getCustomer_id()
					+ " and status='2'" ;
				
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
	public int getSidyCountByCustNo(String custNo)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select count(*) count from ykt_cur.t_tif_subsidy where cust_no="
					+ custNo + " and status='2' ";
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

	public ArrayList getTradeSerialByCollDate(String stuempno,
			String begindate, String enddate, int page, HashMap device,
			HashMap trademsg) throws ClassNotFoundException, SQLException,
			Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();

			sql = "select tradelog.* from ykt_cur.T_TIF_TradeLog tradelog "
					+ "join ykt_cur.T_AIF_Account account on tradelog.Act_id=account.Account_id "
					+ "join ykt_cur.T_CIF_Customer customer on account.Customer_id=customer.Cut_id, "
					+ "(select Serino,Seri_type,Fee_type,Act_id , "
					+ "row_number() over (order by Serino,Seri_type,Fee_type,Act_id ) num "
					+ "from ykt_cur.T_TIF_TradeLog  tradelog "
					+ "join ykt_cur.T_AIF_Account  account on tradelog.Act_id=account.Account_id "
					+ "join ykt_cur.T_CIF_Customer  customer on account.Customer_id=customer.Cut_id "
					+ "where  customer.stuemp_no='"
					+ stuempno
					+ "'"
					+ "and tradelog.operate_date>='"
					+ begindate
					+ "' and tradelog.operate_date<='"
					+ enddate
					+ "' "
					+ ") tt where tradelog.Serino=tt.Serino and tradelog.Seri_type=tt.Seri_type and "
					+ "tradelog.Fee_type=tt.Fee_type and tradelog.Act_id=tt.Act_id and "
					+ " customer.stuemp_no='" + stuempno + "' "
					+ "and tradelog.operate_date>='" + begindate
					+ "' and tradelog.operate_date<='" + enddate + "' "
					+ "and tt.num>=" + page + " and tt.num<=" + (page + 9);
			// System.out.println(sql);
			/*
			 * sql = "SELECT T.* FROM YKT_CUR.T_TIF_TRADESERIAL T,(SELECT
			 * SERIAL_NO,ROW_NUMBER() OVER (ORDER BY SERIAL_NO) NUM FROM
			 * YKT_CUR.T_TIF_TRADESERIAL t2 join YKT_CUR.T_CIF_CUSTOMER c1 on
			 * t2.customer_id=c1.cut_id where c1.stuemp_no='" + stuempno + "'
			 * and t2.operate_date<='" + enddate + "' and t2.operate_date>='" +
			 * begindate + "') T1 WHERE T.SERIAL_NO=T1.SERIAL_NO AND T1.NUM>=" +
			 * page + " and T1.NUM<=" + (page + 9);
			 */
			try {
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				ArrayList tradeserials = new ArrayList();

				while (result.next()) {
					TradeSerialDTO temp_TradeSerialDTO = new TradeSerialDTO();
					temp_TradeSerialDTO.setSerial_type((String) trademsg
							.get(result.getString("Seri_type")));
					temp_TradeSerialDTO.setArea_name(getAreaName(result
							.getInt("Device_Id")));
					temp_TradeSerialDTO.setDict_caption(getFeeTypeName(result
							.getInt("Fee_Type")));
					temp_TradeSerialDTO.setOperate_Date(result
							.getString("Operate_Date"));
					temp_TradeSerialDTO.setOperate_time(result
							.getString("Operate_time"));
					temp_TradeSerialDTO.setTrade_Fee(result.getFloat("Op_Fee"));
					temp_TradeSerialDTO.setFreeBala(result.getFloat("New_Fee")
							- result.getFloat("Cur_FrozeBala"));
					temp_TradeSerialDTO.setFrozeBala(result
							.getFloat("Cur_FrozeBala"));
					tradeserials.add(temp_TradeSerialDTO);
				}
				return tradeserials;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("查询流水失败,stuempno[" + stuempno + "]");
			return null;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	public int getCountByCardId(String cardId, String begindate, String enddate)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select count(*)  count from ("
					+ "select Act_id,Seri_type,Device_Id,Fee_Type,Operate_Date,Operate_time,Op_Fee,New_Fee,his.Cur_FrozeBala "
					+ "from ykt_his.t_tif_tradelog_his his "
					+ "join ykt_cur.T_AIF_Account account on his.Act_id=account.Account_id "
					+ "where his.operate_date>='"
					+ begindate
					+ "' and his.operate_date<='"
					+ enddate
					+ "' and account.card_id="
					+ cardId
					+ " union all "
					+ "select Act_id,Seri_type,Device_Id,Fee_Type,Operate_Date,Operate_time,Op_Fee,New_Fee,log.Cur_FrozeBala "
					+ "from ykt_cur.T_TIF_TradeLog  log "
					+ "join ykt_cur.T_AIF_Account  account on log.Act_id=account.Account_id  "
					+ "where log.operate_date>='" + begindate
					+ "' and log.operate_date<='" + enddate
					+ "' and account.card_id=" + cardId + ") tt";
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
			return 0;
		} catch (Exception e) {
			e.printStackTrace();
			return 0;
		}
	}

	public int getCount(String stuempno, String begindate, String enddate)
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
				sql = "select count(*)  count from ykt_cur.T_TIF_TradeLog  tradelog "
						+ "join ykt_cur.T_AIF_Account  account on tradelog.Act_id=account.Account_id "
						+ "join ykt_cur.T_CIF_Customer  customer on account.Customer_id=customer.Cut_id "
						+ "where customer.stuemp_no='"
						+ stuempno
						+ "' "
						+ "and tradelog.operate_date>='"
						+ begindate
						+ "' and tradelog.operate_date<='"
						+ enddate
						+ "' fetch first 1000 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select count(*)  count from ykt_cur.T_TIF_TradeLog tradelog "
						+ "join ykt_cur.T_AIF_Account account on tradelog.Act_id=account.Account_id "
						+ "join ykt_cur.T_CIF_Customer customer on account.Customer_id=customer.Cut_id "
						+ "where customer.stuemp_no='"
						+ stuempno
						+ "' "
						+ "and tradelog.operate_date>='"
						+ begindate
						+ "' and tradelog.operate_date<='"
						+ enddate
						+ "' and rownum<=1000";
			}

			/*
			 * sql = "SELECT count(*) count FROM YKT_CUR.T_TIF_TRADESERIAL t1
			 * join YKT_CUR.T_CIF_CUSTOMER c1 on t1.customer_id=c1.cut_id where
			 * c1.stuemp_no='" + stuempno + "' and t1.operate_date<='" +
			 * enddate + "' and t1.operate_date>='" + begindate + "'";
			 */
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
			logger.error("读取流水总数失败");
			return 0;
		} catch (Exception e) {
			e.printStackTrace();
			return 0;
		}
	}

	public void createTradeSerial(TradeSerialDTO tradeserial)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "select key_value from YKT_CUR.T_PIF_SYSKEY where key_code='T_TIF_TRADESERIAL'";
				stm = conn.prepareStatement(sql);
				ResultSet temp = stm.executeQuery();
				temp.next();
				tradeserial.setSerial_no(temp.getLong("key_value") + 1);
				sql = "update YKT_CUR.T_PIF_SYSKEY set key_value="
						+ (temp.getInt("key_value") + 1)
						+ " where key_code='T_TIF_TRADESERIAL'";
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
				sql = "Select Logic_Date from YKT_CUR.T_PIF_SYSTIME";
				stm = conn.prepareStatement(sql);
				temp = stm.executeQuery();
				temp.next();
				tradeserial.setEnterAct_Date(temp.getString("Logic_Date"));
				sql = "insert into YKT_CUR.T_TIF_TRADESERIAL(operate_date,operate_time,"
						+ "collect_date,collect_time,enteract_date,enteract_time,serial_no,"
						+ "serial_type,serial_state,card_id,maindevice_id,device_id,devphy999_id,purse_id,customer_id,oper_code) values('"
						+ tradeserial.getOperate_Date()
						+ "','"
						+ tradeserial.getOperate_time()
						+ "','"
						+ tradeserial.getCollect_Date()
						+ "','"
						+ tradeserial.getCollect_time()
						+ "','"
						+ tradeserial.getEnterAct_Date()
						+ "','"
						+ tradeserial.getEnterAct_time()
						+ "',"
						+ tradeserial.getSerial_no()
						+ ","
						+ tradeserial.getSerial_type()
						+ ","
						+ tradeserial.getSerial_state()
						+ ","
						+ tradeserial.getCard_id()
						+ ",0,0,'0',1,"
						+ tradeserial.getCustomer_id() + ",'web')";
				stm = conn.prepareStatement(sql);
				stm.execute();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("生成流水失败:cardno[" + tradeserial.getCard_id() + "]");
		} catch (Exception e) {
			logger.error("生成流水失败:cardno[" + tradeserial.getCard_id() + "]");
		}
	}

	public CustomerDTO getcustomer(Integer cutId)
			throws ClassNotFoundException, SQLException, Exception {
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
				sql = "select * from YKT_CUR.T_CIF_CUSTOMER where CUT_ID="
						+ cutId + " fetch first 1 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from YKT_CUR.T_CIF_CUSTOMER where CUT_ID="
						+ cutId + " and rownum=1 ";
			}
			logger.debug("sql [" + sql + "]");
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();

			if (result.next()) {
				dto = new CustomerDTO();
				dto.setCut_id(result.getInt("CUT_ID"));
				dto.setCut_name(result.getString("CUT_NAME"));
				dto.setStuemp_no(result.getString("STUEMP_NO"));

			}
			return dto;

		} catch (SQLException e1) {
			logger.error("查询客户信息失败,custNo[" + cutId + "]");
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

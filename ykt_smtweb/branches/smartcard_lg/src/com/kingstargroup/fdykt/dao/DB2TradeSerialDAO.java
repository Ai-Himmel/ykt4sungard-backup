package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.*;
import java.util.*;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.AccountDTO;
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
		String freetype = (String)YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_FEETYPE,String.valueOf(feeType));
		if(null == freetype){
			return "";
		}
		return freetype;
	}

	public String getAreaName(int deviceId) throws Exception {
		String areaName = (String)YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_AREADEV,String.valueOf(deviceId));
		if(null == areaName){
			return "";
		}
		return areaName;
	}

	public String getSerialType(String code)throws Exception{
		String type = (String)YKTDictionary.getInstance().getDictionValue(
				KSConstant.DICT_SERIALTYPE,code);
		if(null == type){
			return "";
		}
		return type;
	}
	public ArrayList getTSByCardId(String cardId, String begindate,
			String enddate, int page)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			DB2AccountDAO acc = new DB2AccountDAO();
			AccountDTO accDto = acc.getAccountInfoByCardId(cardId);
			conn = getConnection();
			sql = "select * from ("
					+ "select Act_id,Seri_type,Device_Id,Comments,Operate_Date,Operate_time,(case when outorin =1 then -1 else 1 end)*Op_Fee Op_Fee,New_Fee,his.Cur_FrozeBala "
					+ "from ykt_his.t_tif_tradelog_his as his "
					+ "where his.Act_id='" + accDto.getAccount_id()
					+ "' and  his.operate_date>='"
					+ begindate
					+ "' and his.operate_date<='"
					+ enddate
					+ "'  union all "
					+ "select Act_id,Seri_type,Device_Id,Comments,Operate_Date,Operate_time,(case when outorin =1 then -1 else 1 end)*Op_Fee Op_Fee,New_Fee,log.Cur_FrozeBala "
					+ "from ykt_cur.T_TIF_TradeLog as log "
					+ "where log.Act_id='" + accDto.getAccount_id()
					+ "' and log.operate_date>='"
					+ begindate
					+ "' and log.operate_date<='"
					+ enddate
					+ "' ) as tt order by Operate_Date desc,Operate_time desc fetch first 1000 rows only with ur";
			logger.debug("sql [" + sql + "]");
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
				temp_TradeSerialDTO.setDict_caption(result.getString("Comments"));
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

		} catch (SQLException e1) {
			logger.error("查询交易流水失败,cardno[" + cardId + "]");
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

			sql = "select tradelog.* from ykt_cur.T_TIF_TradeLog as tradelog "
					+ "join ykt_cur.T_AIF_Account as account on tradelog.Act_id=account.Account_id "
					+ "join ykt_cur.T_CIF_Customer as customer on account.Customer_id=customer.Cut_id, "
					+ "(select Serino,Seri_type,Fee_type,Act_id , "
					+ "row_number() over (order by Serino,Seri_type,Fee_type,Act_id ) as num "
					+ "from ykt_cur.T_TIF_TradeLog as tradelog "
					+ "join ykt_cur.T_AIF_Account as account on tradelog.Act_id=account.Account_id "
					+ "join ykt_cur.T_CIF_Customer as customer on account.Customer_id=customer.Cut_id "
					+ "where  customer.stuemp_no='"
					+ stuempno
					+ "'"
					+ "and tradelog.operate_date>='"
					+ begindate
					+ "' and tradelog.operate_date<='"
					+ enddate
					+ "' "
					+ ")as tt  where tradelog.Serino=tt.Serino and tradelog.Seri_type=tt.Seri_type and "
					+ "tradelog.Fee_type=tt.Fee_type and tradelog.Act_id=tt.Act_id and "
					+ " customer.stuemp_no='" + stuempno + "' "
					+ "and tradelog.operate_date>='" + begindate
					+ "' and tradelog.operate_date<='" + enddate + "' "
					+ "and tt.num>=" + page + " and tt.num<=" + (page + 9)+" with ur";
			// System.out.println(sql);
			/*
			 * sql = "SELECT T.* FROM YKT_CUR.T_TIF_TRADESERIAL as T,(SELECT
			 * SERIAL_NO,ROW_NUMBER() OVER (ORDER BY SERIAL_NO) AS NUM FROM
			 * YKT_CUR.T_TIF_TRADESERIAL as t2 join YKT_CUR.T_CIF_CUSTOMER as c1
			 * on t2.customer_id=c1.cut_id where c1.stuemp_no='" + stuempno + "'
			 * and t2.operate_date<='" + enddate + "' and t2.operate_date>='" +
			 * begindate + "') AS T1 WHERE T.SERIAL_NO=T1.SERIAL_NO AND
			 * T1.NUM>=" + page + " and T1.NUM<=" + (page + 9);
			 */
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList tradeserials = new ArrayList();

			while (result.next()) {
				TradeSerialDTO temp_TradeSerialDTO = new TradeSerialDTO();
				temp_TradeSerialDTO.setSerial_type((String) trademsg.get(result
						.getString("Seri_type")));
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

		} catch (SQLException e1) {
			logger.error("查询流水失败,stuempno[" + stuempno + "]");
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

	public int getCountByCardId(String cardId, String begindate, String enddate)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select count(*) as count from ("
					+ "select Act_id,Seri_type,Device_Id,Fee_Type,Operate_Date,Operate_time,Op_Fee,New_Fee,his.Cur_FrozeBala "
					+ "from ykt_his.t_tif_tradelog_his as his "
					+ "join ykt_cur.T_AIF_Account as account on his.Act_id=account.Account_id "
					+ "where his.operate_date>='"
					+ begindate
					+ "' and his.operate_date<='"
					+ enddate
					+ "' and account.card_id="
					+ cardId
					+ " union all "
					+ "select Act_id,Seri_type,Device_Id,Fee_Type,Operate_Date,Operate_time,Op_Fee,New_Fee,log.Cur_FrozeBala "
					+ "from ykt_cur.T_TIF_TradeLog as log "
					+ "join ykt_cur.T_AIF_Account as account on log.Act_id=account.Account_id  "
					+ "where log.operate_date>='" + begindate
					+ "' and log.operate_date<='" + enddate
					+ "' and account.card_id=" + cardId + ") as tt with ur";
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

	public int getCount(String stuempno, String begindate, String enddate)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select count(*) as count from ykt_cur.T_TIF_TradeLog as tradelog "
					+ "join ykt_cur.T_AIF_Account as account on tradelog.Act_id=account.Account_id "
					+ "join ykt_cur.T_CIF_Customer as customer on account.Customer_id=customer.Cut_id "
					+ "where customer.stuemp_no='"
					+ stuempno
					+ "' "
					+ "and tradelog.operate_date>='"
					+ begindate
					+ "' and tradelog.operate_date<='"
					+ enddate
					+ "' fetch first 1000 rows only with ur";

			/*
			 * sql = "SELECT count(*) as count FROM YKT_CUR.T_TIF_TRADESERIAL as
			 * t1 join YKT_CUR.T_CIF_CUSTOMER as c1 on t1.customer_id=c1.cut_id
			 * where c1.stuemp_no='" + stuempno + "' and t1.operate_date<='" +
			 * enddate + "' and t1.operate_date>='" + begindate + "'";
			 */
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			result.next();
			return result.getInt("count");
		} catch (SQLException e1) {
			logger.error("读取流水总数失败");
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

	public void createTradeSerial(TradeSerialDTO tradeserial)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
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
		} catch (SQLException e1) {
			logger.error("生成流水失败:cardno[" + tradeserial.getCard_id() + "]");
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

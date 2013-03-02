package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.ParklogDTO;

public class DB2ParklogDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2ParklogDAO.class);

	public DB2ParklogDAO() {
	}

	public ArrayList getPLByCardId(String cardId, String begindate,
			String enddate, int page) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			String database = KSConfiguration.getInstance().getProperty(
					"database", "db2");
			if ("db2".equalsIgnoreCase(database)) {
				sql = "select * from ("
						+ "select c.cut_name,a.checkintime,a.checkouttime,a.checkinplace,a.checkoutplace,a.carnumber "
						+ "from ykt_cur.t_pif_carpark_log a,ykt_cur.t_pif_card b,ykt_cur.t_cif_customer c "
						+ "where a.physicalno=b.physical_no and b.cosumer_id=c.cut_id and  a.checkintime>='"
						+ begindate
						+ "' and a.checkintime<='"
						+ enddate
						+ "' and b.card_id="
						+ cardId
						+ ")  tt order by checkintime desc fetch first 1000 rows only";
			} else if ("oracle".equalsIgnoreCase(database)) {
				sql = "select * from ("
						+ "select c.cut_name,a.checkintime,a.checkouttime,a.checkinplace,a.checkoutplace,a.carnumber "
						+ "from ykt_cur.t_pif_carpark_log a,ykt_cur.t_pif_card b,ykt_cur.t_cif_customer c "
						+ "where a.physicalno=substr(b.physical_no,0,6) and b.cosumer_id=c.cut_id and  a.checkintime>='"
						+ begindate + "' and a.checkintime<='" + enddate
						+ "' and b.card_id=" + cardId
						+ ")  tt where rownum <=1000 order by checkintime desc";
			}
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			ArrayList parklogs = new ArrayList();
			int start = 0;
			while ((start++ < page - 1) && result.next()) {
				;
			}
			int count = 10;
			while (result.next() && (count-- > 0)) {
				ParklogDTO parklogdto = new ParklogDTO();
				parklogdto.setCarnumber(result.getString("carnumber"));
				String checkinplace = (String) YKTDictionary.getInstance()
						.getDictionValue(KSConstant.DICT_PARK,
								result.getString("checkinplace"));
				parklogdto.setCheckinplace(checkinplace == null ? result
						.getString("checkinplace") : checkinplace);
				parklogdto.setCheckintime(result.getString("checkintime"));
				String checkoutplace = (String) YKTDictionary.getInstance()
						.getDictionValue(KSConstant.DICT_PARK,
								result.getString("checkoutplace"));
				parklogdto.setCheckoutplace(checkoutplace == null ? result
						.getString("checkoutplace") : checkoutplace);
				parklogdto.setCheckouttime(result.getString("checkouttime"));
				parklogdto.setCustname(result.getString("cut_name"));
				parklogs.add(parklogdto);
			}
			return parklogs;

		} catch (SQLException e1) {
			logger.error("查询交易流水失败,cardno[" + cardId + "]");
			e1.printStackTrace();
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

	public int getCountByCardId(String cardId, String begindate, String enddate)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();

			sql = "select count(a.dataid) as count "
					+ "from ykt_cur.t_pif_carpark_log a,ykt_cur.t_pif_card b "
					+ "where a.physicalno=substr(b.physical_no,0,6) and a.checkintime>='"
					+ begindate + "' and a.checkintime<='" + enddate
					+ "' and b.card_id=" + cardId;
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

}

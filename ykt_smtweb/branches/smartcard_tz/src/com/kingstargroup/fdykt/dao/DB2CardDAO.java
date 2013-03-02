package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.*;
import java.util.*;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.*;

public class DB2CardDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2CardDAO.class);

	public CardDTO getCardInfo(String cardId) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select * from YKT_CUR.T_PIF_CARD where Card_id=" + cardId;
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			result.next();
			CardDTO temp = new CardDTO();
			temp.setCardId(result.getString("Card_id"));
			temp.setCosumerId(result.getString("Cosumer_id"));
			temp.setStateId(result.getString("State_id"));
			return temp;
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + cardId);
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

	public CardDTO getCardInfoByIdPwd(String phisicalNo, String pwd)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select * from ykt_cur.T_PIF_Card as card where card.physical_No='"
					+ phisicalNo
					+ "' and card.password='"
					+ pwd
					+ "'"
					+ " and state_id <> '2000' ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();

			if (result.next()) {
				CardDTO temp = new CardDTO();
				temp.setCardId(result.getString("Card_id"));
				temp.setCosumerId(result.getString("Cosumer_id"));
				temp.setStateId(result.getString("State_id"));
				return temp;
			}
			return null;
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + phisicalNo
					+ "����[" + pwd + "]");
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

	public String getEndDate() throws ClassNotFoundException, SQLException,
			Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "Select value from YKT_CUR.T_PIF_CUR_SYSPARA where id=9";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			result.next();
			String enddate;
			int v = result.getInt("value");
			Calendar now = Calendar.getInstance();
			now.add(Calendar.DATE, v);
			String year = (new Integer(now.get(Calendar.YEAR))).toString();
			String month = (new Integer(now.get(Calendar.MONTH) + 1))
					.toString();
			if (month.length() == 1) {
				month = "0" + month;
			}
			String day = (new Integer(now.get(Calendar.DATE))).toString();
			if (day.length() == 1) {
				day = "0" + day;
			}
			enddate = year + month + day;
			return enddate;
		} catch (SQLException e1) {
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

	public void createLossInfo(CardLossInfoDTO lossinfo)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			sql = "insert into YKT_CUR.T_PIF_CARDLOSSINFO values('"
					+ lossinfo.getOperateDate() + "','"
					+ lossinfo.getOperateTime() + "'," + lossinfo.getCardId()
					+ "," + lossinfo.getStateId() + ",'"
					+ lossinfo.getBeginDate() + "','" + lossinfo.getEndDate()
					+ "')";
			stm = conn.prepareStatement(sql);
			stm.execute();
		} catch (SQLException e1) {
			logger.error("��ʧ��Ϣ��д��ʧ��,����[" + lossinfo.getCardId());
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

	public void createBlackSheet(BlackSheetDTO blacksheet)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			sql = "insert into YKT_CUR.T_TIF_BLACK_SHEET values("
					+ blacksheet.getCardId() + ",'" + blacksheet.getVolume()
					+ "','" + blacksheet.getValiddate() + "',"
					+ blacksheet.getStateId() + "," + blacksheet.getIsAd()
					+ ",'" + blacksheet.getOperateDate() + "','"
					+ blacksheet.getOperateTime() + "','','')";
			logger.debug("create black sql [ " + sql + "]");
			stm = conn.prepareStatement(sql);
			stm.execute();
		} catch (SQLException e1) {
			logger.error("���������ʧ��,����[" + blacksheet.getCardId() + "]");
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

	public void createMesList(MesListDTO meslist)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		Statement stm = null;
		ResultSet result = null;
		Statement updateStm = null;
		try {
			// ������ݿ�����
			conn = getConnection();
			// ��������Ҫ�㲥���豸 ID
			ArrayList sysID = new ArrayList(1000);
			sql = "select system_id from YKT_CUR.T_PIF_SUBSYSTEM where "
					+ " system_type=12 and state=3";
			stm = conn.createStatement();
			result = stm.executeQuery(sql);
			while (result.next()) {
				sysID.add(result.getString("system_id"));
			}
			// �������µ� Statement
			updateStm = conn.createStatement();
			// ȡ�ù㲥��¼������
			Object[] systemIDAry = sysID.toArray();
			if (systemIDAry.length == 0) {
				return;
			}
			/*
			 * sql = "select key_value from YKT_CUR.T_PIF_SYSKEY where " + "
			 * key_code='T_TIF_MESLIST'"; ResultSet temp =
			 * stm.executeQuery(sql); int currMesID = 0; if (temp.next()) {
			 * currMesID = temp.getInt("key_value"); // ���¹㲥��¼�����ĵ�ǰֵ sql =
			 * "update YKT_CUR.T_PIF_SYSKEY set key_value=" + (currMesID +
			 * systemIDAry.length) + " where key_code='T_TIF_MESLIST'";
			 * stm.executeUpdate(sql); } else { throw new SQLException("No
			 * primary key generate!"); }
			 */
			// Ϊ�����豸���ӹ㲥��¼
			for (int i = 0; i < systemIDAry.length; ++i) {
				meslist.setDeviceId((String) systemIDAry[i]);
				StringBuffer sqlBuf = new StringBuffer(1024);
				sqlBuf
						.append(
								"insert into YKT_CUR.T_TIF_MESLIST(funid,stateid")
						.append(
								",sendcount,level,device_id,devid,indt,startdt,enddt")
						.append(
								",ecode,emsg,incontent,outcontent,pfunid,max_send_cnt)values(")
						.append(meslist.getFunId()).append(",").append(
								meslist.getStateId()).append(",0,").append(
								meslist.getLevel()).append(",").append(
								meslist.getDeviceId()).append(",0,'").append(
								meslist.getIndt()).append("','','',").append(
								meslist.getEcode()).append(",'','").append(
								meslist.getIncontent()).append("','',0,100)");
				// logger.error("sql [" + sqlBuf.toString() + "]");
				updateStm.addBatch(sqlBuf.toString());
			}
			// ���������¼
			updateStm.executeBatch();
		} catch (SQLException e1) {
			e1.printStackTrace();
			logger.error("��ʧ������Ϣ����ʧ��");
			throw (e1);
		} catch (Exception e) {
			e.printStackTrace();
			throw (e);
		} finally {
			if (updateStm != null) {
				updateStm.close();
			}
			if (stm != null) {
				stm.close();
			}
		}
	}

	public void updateCardState(String cardId, String state_id)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			sql = "update YKT_CUR.T_PIF_CARD set state_id='" + state_id
					+ "' where card_id=" + cardId;
			stm = conn.prepareStatement(sql);
			stm.executeUpdate();
		} catch (SQLException e1) {
			logger.error("���¿�״̬ʧ��,����[" + cardId + "]state[" + state_id + "]");
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

	public void updateCardPassword(String physicalNo, String password)
			throws Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			sql = "update ykt_cur.t_pif_card set password='" + password
					+ "' where physical_No='" + physicalNo + "'"
					+ " and state_id <> '2000' ";
			// logger.debug("sql[" + sql + "]");
			stm = conn.prepareStatement(sql);
			stm.executeUpdate();
		} catch (SQLException el) {
			logger.error("�޸�����ʧ��,physicalNo[" + physicalNo + "]");
			el.printStackTrace();
			throw (el);
		} finally {
			if (stm != null)
				stm.close();
		}
	}

	public void updateCardPassword(int cardId, String password)
			throws Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			sql = "update ykt_cur.t_pif_card set password='" + password
					+ "' where card_id=" + cardId + " and state_id <> '2000' ";
			// logger.debug("sql[" + sql + "]");
			stm = conn.prepareStatement(sql);
			stm.executeUpdate();
		} catch (SQLException el) {
			logger.error("�޸�����ʧ��,cardId[" + cardId + "]");
			// conn.rollback();
			el.printStackTrace();
			throw (el);
		} finally {
			if (stm != null)
				stm.close();
		}
	}

	public void updateLossState(String sysdate, String cardid)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			sql = "update ykt_cur.t_pif_cardlossinfo set state_id = 2, end_date = '"
					+ sysdate + "' where state_id = 1 and card_id=" + cardid;
			stm = conn.prepareStatement(sql);
			stm.executeUpdate();
		} catch (SQLException e1) {
			logger.error("���¿���ʧ��ʧ��,cardno[" + cardid + "]");
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

	public int isCancel(String cutid, String cardid)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			// ����������(д��ʧ�ܵĿ�)
			sql = "select type_id from YKT_CUR.T_PIF_CARD where COSUMER_ID="
					+ cutid + " and (state_id='" + KSConstant.CARDSTAT_NORMAL
					+ "' or state_id='" + KSConstant.CARDSTAT_WFAIL + "') "
					+ " and card_id<>" + cardid;
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			if (result.next()) {
				/*
				 * int type = result.getInt("type_id"); if (type ==
				 * KSConstant.CARDTYPE_MAIN) { return
				 * KSConstant.MAINCARD_UNLOSSED; // �ÿͻ���ʽ��δ��ʧ,���ܰ���ʱ�� } else {
				 * return KSConstant.TEMPCARD_EXISTS; // �ÿͻ���һ����ʱ��������ʹ��,�����ٰ���ʱ�� }
				 */
				return KSConstant.MAINCARD_UNLOSSED;
			} else {
				return 0; //
			}
		} catch (SQLException e1) {
			logger.error("��ѯ��״̬ʧ��,custid[" + cutid + "]");
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

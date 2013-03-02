package com.kingstargroup.fdykt.dao;

import org.apache.log4j.Logger;

import java.sql.*;
import java.util.*;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dto.*;

public class DB2CardDAO extends DB2ActionDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2CardDAO.class);
	
	public  List getBmTestInfo(String cardId,int page) throws ClassNotFoundException,
	SQLException, Exception {
		
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		ArrayList list = new ArrayList();
		try {
			conn = getConnection();
			try {
				sql = "select b.student_no,s.cut_name stu_name,d.test_cat_name,b.if_pay,b.fee_payed,b.pay_time from YKT_CUR.T_PIF_CARD a,ykt_cur.t_cif_customer s,ykt_bm.bm_stu_bm b,ykt_bm.bm_test c,ykt_bm.bm_test_cat d where a.Card_id='"
						+ cardId +"' and a.cosumer_id=s.cut_id and s.stuemp_no=b.student_no and b.test_id=c.id and c.test_cat_id=d.id and pay_time=(select max(e.pay_time) from ykt_bm.bm_stu_bm e, YKT_CUR.T_PIF_CARD f,ykt_cur.t_cif_customer g where f.card_id='"+cardId+"' and f.cosumer_id=g.cut_id and g.stuemp_no=e.student_no)";
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				
				int start = 0;
				while ((start++ < page - 1) && result.next()) {
					;
				}
				int count = 10;
				while (result.next() && (count-- > 0)) {
					BmTestDTO temp = new BmTestDTO();
					temp.setStudent_no(result.getString("student_no"));
					temp.setStu_name(result.getString("stu_name"));
					temp.setTest_cat_name(result.getString("test_cat_name"));
					temp.setIf_pay(result.getString("if_pay"));
					temp.setFee_payed(result.getString("fee_payed"));
					temp.setPay_time(result.getString("pay_time"));
					list.add(temp);
				}
				return list;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + cardId);
			return null;
		} catch (Exception e) {
			logger.error("��ȡ����Ϣʧ��[" + e.getMessage() + "]����:" + cardId);
			return null;
		}
	}
	
	public int getBmTestInfoCount(String cardId) throws ClassNotFoundException, SQLException,
			Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();

			sql = "select count(*) count from YKT_CUR.T_PIF_CARD a,ykt_cur.t_cif_customer s,ykt_bm.bm_stu_bm b,ykt_bm.bm_test c,ykt_bm.bm_test_cat d where a.Card_id='"
						+ cardId +"' and a.cosumer_id=s.cut_id and s.stuemp_no=b.student_no and b.test_id=c.id and c.test_cat_id=d.id and pay_time=(select max(e.pay_time) from ykt_bm.bm_stu_bm e, YKT_CUR.T_PIF_CARD f,ykt_cur.t_cif_customer g where f.card_id='"+cardId+"' and f.cosumer_id=g.cut_id and g.stuemp_no=e.student_no)";
			
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			result.next();
			return result.getInt("count");
		} catch (SQLException e1) {
			logger.error("��ѯ��ˮ��ʧ��");
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
	

	public CardDTO getCardInfo(String cardId) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			try {
				sql = "select * from YKT_CUR.T_PIF_CARD where Card_id="
						+ cardId;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				result.next();
				CardDTO temp = new CardDTO();
				temp.setCardId(result.getString("card_id"));
				temp.setCosumerId(result.getString("cosumer_id"));
				temp.setStateId(result.getString("state_id"));
				temp.setPhysicalNo(result.getString("physical_no"));
				return temp;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + cardId);
			return null;
		} catch (Exception e) {
			logger.error("��ȡ����Ϣʧ��[" + e.getMessage() + "]����:" + cardId);
			return null;
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
			try {
				sql = "select * from ykt_cur.T_PIF_Card card where card.physical_No='"
						+ phisicalNo
						+ "' " 
						+ " and card.password='" 
						+  pwd 
						+ "'"
						+ " and state_id <> '2000' ";
					   
			   	
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				CardDTO temp = null;
				if (result.next()) {
					temp = new CardDTO();
					temp.setCardId(result.getString("Card_id"));
					temp.setCosumerId(result.getString("Cosumer_id"));
					temp.setStateId(result.getString("State_id"));
				}
				return temp;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}

		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + phisicalNo
					+ "����[" + pwd + "]");
			return null;
		} catch (Exception e) {
			logger.error("��ȡ����Ϣʧ��[" + e.getMessage() + "]����:" + phisicalNo
					+ "����[" + pwd + "]");
			return null;
		}

	}

	public CardDTO getCardInfoById(String phisicalNo)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select * from ykt_cur.T_PIF_Card card where card.physical_No='"
					+ phisicalNo + "'" + " and state_id <> '2000' ";
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
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + phisicalNo);
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
			try {
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
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("getEndDate()", e1); //$NON-NLS-1$
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("getEndDate()", e); //$NON-NLS-1$
			e.printStackTrace();
		}
		return "";
	}

	public void createLossInfo(CardLossInfoDTO lossinfo)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		try {
			conn = getConnection();
			try {
				sql = "insert into YKT_CUR.T_PIF_CARDLOSSINFO values('"
						+ lossinfo.getOperateDate() + "','"
						+ lossinfo.getOperateTime() + "',"
						+ lossinfo.getCardId() + "," + lossinfo.getStateId()
						+ ",'" + lossinfo.getBeginDate() + "','"
						+ lossinfo.getEndDate() + "')";
				stm = conn.prepareStatement(sql);
				stm.execute();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ʧ��Ϣ��д��ʧ��,����[" + lossinfo.getCardId());
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("��ʧ��Ϣ��д��ʧ��,����[" + lossinfo.getCardId());
			e.printStackTrace();
		}
	}

	public void createBlackSheet(BlackSheetDTO blacksheet)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "insert into YKT_CUR.T_TIF_BLACK_SHEET values("
						+ blacksheet.getCardId() + ",'"
						+ blacksheet.getVolume() + "','"
						+ blacksheet.getValiddate() + "',"
						+ blacksheet.getStateId() + "," + blacksheet.getIsAd()
						+ ",'" + blacksheet.getOperateDate() + "','"
						+ blacksheet.getOperateTime() + "','','')";
				logger.debug("create black sql [ " + sql + "]");
				stm = conn.prepareStatement(sql);
				stm.execute();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("���������ʧ��,����[" + blacksheet.getCardId() + "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("���������ʧ��,����[" + blacksheet.getCardId() + "]");
			e.printStackTrace();
		}
	}

	private int getSequence(Connection conn, String sequenceTable)
			throws ClassNotFoundException, SQLException, Exception {
		Statement stm = null;
		ResultSet result = null;
		String sql = "select " + sequenceTable
				+ ".nextval mysequence from dual";
		stm = conn.createStatement();
		result = stm.executeQuery(sql);
		int ret = 0;
		if (result.next()) {
			ret = result.getInt("mysequence");
		}
		return ret;
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
			try {
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
				int sequence = 0;
				for (int i = 0; i < systemIDAry.length; ++i) {

					meslist.setDeviceId((String) systemIDAry[i]);
					StringBuffer sqlBuf = new StringBuffer(1024);
					String database = KSConfiguration.getInstance()
							.getProperty("database", "db2");
					if ("db2".equalsIgnoreCase(database)) {
						sqlBuf
								.append(
										"insert into YKT_CUR.T_TIF_MESLIST(funid,stateid")
								.append(
										",sendcount,level,device_id,devid,indt,startdt,enddt")
								.append(
										",ecode,emsg,incontent,outcontent,pfunid,max_send_cnt,recvcount,seq,msgtype)values(")
								.append(meslist.getFunId()).append(",").append(
										meslist.getStateId()).append(",0,")
								.append(meslist.getLevel()).append(",").append(
										meslist.getDeviceId()).append(",0,'")
								.append(meslist.getIndt()).append("','','',")
								.append(meslist.getEcode()).append(",'','")
								.append(meslist.getIncontent()).append(
										"','',0,100,0,0,1)");
					} else if ("oracle".equalsIgnoreCase(database)) {
						sequence = getSequence(conn, "ykt_cur.S_T_TIF_MESLIST");
						sqlBuf
								.append(
										"insert into YKT_CUR.T_TIF_MESLIST(mesid,funid,stateid")
								.append(
										",sendcount,\"LEVEL\",device_id,devid,indt,startdt,enddt")
								.append(
										",ecode,emsg,incontent,outcontent,pfunid,max_send_cnt,recvcount,seq,msgtype)values(")
								.append(sequence).append(",").append(
										meslist.getFunId()).append(",").append(
										meslist.getStateId()).append(",0,")
								.append(meslist.getLevel()).append(",").append(
										meslist.getDeviceId()).append(",0,'")
								.append(meslist.getIndt()).append("','','',")
								.append(meslist.getEcode()).append(",'','")
								.append(meslist.getIncontent()).append(
										"','',0,100,0,0,1)");
					}

					// logger.error("sql [" + sqlBuf.toString() + "]");
					updateStm.addBatch(sqlBuf.toString());
				}
				// ���������¼
				updateStm.executeBatch();
			} finally {
				if (updateStm != null) {
					updateStm.close();
				}
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ʧ������Ϣ����ʧ��");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("��ʧ������Ϣ����ʧ��");
			e.printStackTrace();
		}
	}

	public void updateCardState(String cardId, String state_id)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "update YKT_CUR.T_PIF_CARD set state_id='" + state_id
						+ "' where card_id=" + cardId;
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("���¿�״̬ʧ��,����[" + cardId + "]state[" + state_id + "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("���¿�״̬ʧ��,����[" + cardId + "]state[" + state_id + "]");
			e.printStackTrace();
		}
	}

	public void updateCardPassword(String physicalNo, String password)
			throws Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "update ykt_cur.t_pif_card set password='" + password
						+ "' where physical_No='" + physicalNo + "'"
						+ " and state_id <> '2000' ";
				// logger.debug("sql[" + sql + "]");
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
			} finally {
				if (stm != null)
					stm.close();
			}
		} catch (SQLException el) {
			logger.error("�޸�����ʧ��,physicalNo[" + physicalNo + "]");
			el.printStackTrace();
		} catch (Exception e) {
			logger.error("�޸�����ʧ��,physicalNo[" + physicalNo + "]");
			e.printStackTrace();
		}
	}

	public void updateCardPassword(int cardId, String password)
			throws Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "update ykt_cur.t_pif_card set password='" + password
						+ "' where card_id=" + cardId
						+ " and state_id <> '2000' ";
				// logger.debug("sql[" + sql + "]");
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
			} finally {
				if (stm != null)
					stm.close();
			}
		} catch (SQLException el) {
			logger.error("�޸�����ʧ��,cardId[" + cardId + "]");
			el.printStackTrace();
		} catch (Exception e) {
			logger.error("�޸�����ʧ��,cardId[" + cardId + "]");
			e.printStackTrace();
		}
	}

	public void updateLossState(String sysdate, String cardid)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "update ykt_cur.t_pif_cardlossinfo set state_id = 2, end_date = '"
						+ sysdate
						+ "' where state_id = 1 and card_id="
						+ cardid;
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("���¿���ʧ��ʧ��,cardno[" + cardid + "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("���¿���ʧ��ʧ��,cardno[" + cardid + "]");
			e.printStackTrace();
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
			try {
				sql = "select type_id from YKT_CUR.T_PIF_CARD where COSUMER_ID="
						+ cutid
						+ " and (state_id='"
						+ KSConstant.CARDSTAT_NORMAL
						+ "' or state_id='"
						+ KSConstant.CARDSTAT_WFAIL
						+ "') "
						+ " and card_id<>"
						+ cardid;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
					/*
					 * int type = result.getInt("type_id"); if (type ==
					 * KSConstant.CARDTYPE_MAIN) { return
					 * KSConstant.MAINCARD_UNLOSSED; // �ÿͻ���ʽ��δ��ʧ,���ܰ���ʱ�� } else {
					 * return KSConstant.TEMPCARD_EXISTS; //
					 * �ÿͻ���һ����ʱ��������ʹ��,�����ٰ���ʱ�� }
					 */
					return KSConstant.MAINCARD_UNLOSSED;
				} else {
					return 0; //
				}
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ѯ��״̬ʧ��,custid[" + cutid + "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("��ѯ��״̬ʧ��,custid[" + cutid + "]");
			e.printStackTrace();
		}
		return 0;
	}
}

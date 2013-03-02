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

	public CardDTO getCardInfo(String cardno) throws ClassNotFoundException,
			SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			try {
				sql = "select cardno,custid,('0'||lossflag||frozeflag||'0'||badflag||'00000') as cardstatus,cardphyid,cardpwd from ykt_cur.t_card where cardno="
						+ cardno;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				result.next();
				CardDTO temp = new CardDTO();
				temp.setCardno(result.getLong("cardno"));
				temp.setCustid(result.getLong("custid"));
				temp.setCardpwd(result.getString("cardpwd"));
				temp.setCardstatus(result.getString("cardstatus"));
				temp.setCardphyid(result.getString("cardphyid"));
				return temp;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + cardno);
			return null;
		} catch (Exception e) {
			logger.error("��ȡ����Ϣʧ��[" + e.getMessage() + "]����:" + cardno);
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
				sql = "select cardno,custid,('0'||lossflag||frozeflag||'0'||badflag||'00000') as cardstatus,cardphyid from ykt_cur.t_card card where card.cardphyid='"
						+ phisicalNo
						+ "' and card.cardpwd='"
						+ pwd
						+ "'"
						+ " and status = '1' ";
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				CardDTO temp = null;
				if (result.next()) {
					temp = new CardDTO();
					temp.setCardno(result.getLong("cardno"));
					temp.setCustid(result.getLong("custid"));
					temp.setCardstatus(result.getString("cardstatus"));
					temp.setCardphyid(result.getString("cardphyid"));
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
	
	public CardDTO getCardInfoByPhyid(String phisicalNo)throws SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		
		try {
			conn = getConnection();
			try {
				sql = "select cardno,custid,('0'||lossflag||frozeflag||'0'||badflag||'00000') as cardstatus,cardphyid,cardpwd from ykt_cur.t_card card where card.cardphyid='"
						+ phisicalNo
						+ "'"
						+ " and status = '1' ";
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				CardDTO temp = null;
				if (result.next()) {
					temp = new CardDTO();
					temp.setCardno(result.getLong("cardno"));
					temp.setCustid(result.getLong("custid"));
					temp.setCardstatus(result.getString("cardstatus"));
					temp.setCardphyid(result.getString("cardphyid"));
					temp.setCardpwd(result.getString("cardpwd"));
				}
				return temp;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + phisicalNo);
			return null;
		} catch (Exception e) {
			logger.error("��ȡ����Ϣʧ��[" + e.getMessage() + "]����:" + phisicalNo);
			return null;
		}

	}
	
	public ArrayList getCardInfoListByPhyid(String phisicalNo)throws SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;
		
		try {
			conn = getConnection();
			try {
				sql = "select cardno,custid,('0'||lossflag||frozeflag||'0'||badflag||'00000') as cardstatus,cardphyid,cardpwd from ykt_cur.t_card card where card.cardphyid='"
						+ phisicalNo
						+ "'";
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				ArrayList cardlist = new ArrayList();
				while (result.next()) {
					CardDTO temp = new CardDTO();
					temp.setCardno(result.getLong("cardno"));
					temp.setCustid(result.getLong("custid"));
					temp.setCardstatus(result.getString("cardstatus"));
					temp.setCardphyid(result.getString("cardphyid"));
					temp.setCardpwd(result.getString("cardpwd"));
					cardlist.add(temp);
				}
					
				return cardlist;
			} finally {
				if (stm != null) {
					stm.close();
				}
			}
		
		} catch (SQLException e1) {
			logger.error("��ȡ����Ϣʧ��[" + e1.getMessage() + "]����:" + phisicalNo);
			return null;
		} catch (Exception e) {
			logger.error("��ȡ����Ϣʧ��[" + e.getMessage() + "]����:" + phisicalNo);
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
			sql = "select cardno,custid,('0'||lossflag||frozeflag||'0'||badflag||'00000') as cardstatus,cardphyid from ykt_cur.t_card card where card.cardphyid='"
					+ phisicalNo
					+ "'"
					+ " and ('0'||lossflag||frozeflag||'0'||badflag||'00000') ='0000000000' and status='1'";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();

			if (result.next()) {
				CardDTO temp = new CardDTO();
				temp.setCardno(result.getLong("cardno"));
				temp.setCustid(result.getLong("custid"));
				temp.setCardstatus(result.getString("cardstatus"));
				temp.setCardphyid(result.getString("cardphyid"));
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

	public String getCardDeadlineDateById(String phisicalNo)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select EXPIREDATE from ykt_cur.t_card card where card.cardphyid='"
					+ phisicalNo + "'" + " and status='1'";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();

			if (result.next()) {
				String expiredate = result.getString("EXPIREDATE");
				if(expiredate.length()>6){
					expiredate = expiredate.substring(2,8);
				}
				return expiredate;
			}
			return "";
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

	public void updateCardPassword(String physicalNo, String password)
			throws Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "update ykt_cur.t_card set cardpwd='" + password
						+ "' where cardphyid='" + physicalNo + "'"
						+ " and status='1' ";
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

	public void updateCardPassword(int cardno, String password)
			throws Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;

		try {
			conn = getConnection();
			try {
				sql = "update ykt_cur.t_card set cardpwd='" + password
						+ "' where cardno=" + cardno + " and status = '1' ";
				// logger.debug("sql[" + sql + "]");
				stm = conn.prepareStatement(sql);
				stm.executeUpdate();
			} finally {
				if (stm != null)
					stm.close();
			}
		} catch (SQLException el) {
			logger.error("�޸�����ʧ��,cardId[" + cardno + "]");
			el.printStackTrace();
		} catch (Exception e) {
			logger.error("�޸�����ʧ��,cardId[" + cardno + "]");
			e.printStackTrace();
		}
	}

	public int isCancel(String custid, String cardno)
			throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			// ����������(д��ʧ�ܵĿ�)
			try {
				sql = "select cardno from ykt_cur.t_card where custid="
						+ custid
						+ " and (lossdate='' or lossdate is null) and status='1' "
						+ " and cardno<>" + cardno;
				stm = conn.prepareStatement(sql);
				result = stm.executeQuery();
				if (result.next()) {
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
			logger.error("��ѯ��״̬ʧ��,custid[" + custid + "]");
			e1.printStackTrace();
		} catch (Exception e) {
			logger.error("��ѯ��״̬ʧ��,custid[" + custid + "]");
			e.printStackTrace();
		}
		return 0;
	}

	public int getSysParaCardcndVal()throws ClassNotFoundException, SQLException, Exception {
		String sql = "";
		Connection conn = null;
		PreparedStatement stm = null;
		ResultSet result = null;

		try {
			conn = getConnection();
			sql = "select paraval from ykt_cur.t_syspara where paraid=23 ";
			stm = conn.prepareStatement(sql);
			result = stm.executeQuery();
			if (result.next()) {
				int cardcnt = result.getInt("paraval");
				return cardcnt;
			}
			
		} catch (SQLException e1) {
			logger.error("��ȡȫ�ֱ�����ʽ������ʧ��");
			e1.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (stm != null) {
				stm.close();
			}
		}
		return 0;

	}
}

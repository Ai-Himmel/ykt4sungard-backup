/**
 * 
 */
package com.kingstargroup.ecard.hibernate.card;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.lang.FastStringBuffer;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: CardPersistence.java
 * Description: ����־ò�������
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CardPersistence extends BasicPersistence {

	/**
	 * Description:
	 * @param customerId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public List getAvailableCards(String customerId) throws DBSystemException {	
		
		Session s = getSession();
		try {
			StringBuffer hsql = new StringBuffer();			
			hsql.append("from TPifCard card where")
				.append(" card.cosumerId = ? AND card.stateId <> ? order by card.cardId desc");
			Query q = s.createQuery(hsql.toString());
			q.setInteger(0, Integer.parseInt(customerId));
			q.setString(1, EcardConstants.CARD_WRITE_OFF_STATUS);						
			return q.list();
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public TPifCard getCardById(Integer cardId) throws DBSystemException {
		Session s = getSession();
		try {
			return (TPifCard) s.get(TPifCard.class, cardId);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	/**
	 * Description:�õ���ǰ����ʹ�õĿ�
	 * @param customerId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TPifCard getCurrentValidCard(String customerId) throws DBSystemException {
		Session s = getSession();
		try {
			StringBuffer hsql = new StringBuffer();			
			hsql.append("from TPifCard card where")
				.append(" card.cosumerId = ? AND card.stateId like ?")
				.append(" order by card.stateId asc");
			Query q = s.createQuery(hsql.toString());
			q.setInteger(0, Integer.parseInt(customerId));
			q.setString(1, "10%");//����Ϊ����״̬�Ŀ�
			return (TPifCard) q.uniqueResult();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:����ָ��������
	 * @param card
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void update(TPifCard card) throws DBSystemException {
		Session s = getSession();
		try {
			s.update(card);
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		}
	}
	
	/**
	 * Description:����ѧ/���ź�״̬�õ���Ӧ�Ŀ�����
	 * @param customerId
	 * @param state
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TPifCard getCardByCusIdAndState(String customerId, String state) throws DBSystemException {
		Session s = getSession();
		try {
			FastStringBuffer buff = new FastStringBuffer();
			buff.append(" from TPifCard card where card.cosumerId = ?")
				.append(" and card.stateId = ?");
			Query query = s.createQuery(buff.toString());
			query.setInteger(0, Integer.parseInt(customerId));
			query.setString(1, state);
			return (TPifCard) query.uniqueResult();
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		}
	}
	
	/**
	 * Description:����һ������ʧ��Ϣ
	 * @param lossInfo
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void addCardLossInfo(TPifCardlossinfo lossInfo) throws DBSystemException {
		Session s = getSession();
		try {
			s.save(lossInfo);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:���ݿ��ź�״̬���¶�Ӧ�Ŀ���ʧ��Ϣ
	 * @param endDate
	 * @param cardId
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void updateLossInfo(String endDate, Integer cardId) throws DBSystemException {
		Session s = getSession();
		try {
			FastStringBuffer buff = new FastStringBuffer();
			buff.append("from TPifCardlossinfo lossinfo ")
			.append("where lossinfo.stateId = :oldStateId ")
			.append("and lossinfo.id.cardId = :cardId");
			Query query = s.createQuery(buff.toString());
			query.setInteger("oldStateId", 1);
			query.setInteger("cardId", cardId.intValue());
			Iterator it = query.iterate();
			while (it.hasNext()) {
				TPifCardlossinfo loss = (TPifCardlossinfo) it.next();
				loss.setStateId(new Integer(2));
				loss.setEndDate(endDate);
				s.update(loss);
			}
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		}
	}
	/**
	 * Description:�õ���ʧ�����²�����ʽ����Ҫ������
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public int getReapplyDays() throws DBSystemException {
		Session s = getSession();
		try {
			TPifCurSyspara para = (TPifCurSyspara) s.get(TPifCurSyspara.class, new Integer(EcardConstants.REAPPLY_DAYS_ID));
			return Integer.parseInt(para.getValue());
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:����һ����������¼
	 * @param blackSheet
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void addBlackSheet(TTifBlackSheet blackSheet) throws DBSystemException {
		Session s = getSession();
		try {
			s.save(blackSheet);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:������ϵͳ���ͺ���ϵͳ״̬�õ���ϵͳID�б�
	 * @param type
	 * @param state
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public List getSubSysIdByTypeAndState(int type, int state) throws DBSystemException {
		Session s = getSession();
		try {
			FastStringBuffer buff = new FastStringBuffer();
			buff.append(" from TPifSubsystem subsys")
				.append(" where subsys.systemType = ? and subsys.state = ?");			
			Query query = s.createQuery(buff.toString());
			query.setInteger(0, type);
			query.setInteger(1, state);
			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:�õ�������ˮ���е���ˮ��
	 * @param keyCode
	 * @throws DBSystemException
	 * Modify History:
	 */
	public int getKeyvalueByCode(String keyCode) throws DBSystemException {
		Session s = getSession();
		try {						
			TPifSyskey key = (TPifSyskey) s.get(TPifSyskey.class, keyCode);
			int serialNo = key.getKeyValue().intValue() + 1;
			key.setKeyValue(new Long(String.valueOf(serialNo)));
			s.update(key);
			return serialNo;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:���һ����Ϣ����
	 * @param msg
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void addMsg(TTifMeslist msg) throws DBSystemException {
		Session s = getSession();
		try {
			s.save(msg);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:����һ��������ˮ
	 * @param serial
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void addTradeSerial(TTifTradeserial serial) throws DBSystemException {
		Session s = getSession();
		try {
			s.save(serial);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public TCifDept getDept(String deptNo) throws DBSystemException {
		Session s = getSession();
		TCifDept tcifdept = null;
		try {
			FastStringBuffer buff = new FastStringBuffer();
			buff.append(" from TCifDept dept")
				.append(" where dept.deptCode = ? ");			
			Query query = s.createQuery(buff.toString());
			query.setString(0, deptNo);
			List list = query.list();
			if(list!=null&&list.size()>0){
				tcifdept = (TCifDept)list.get(0);
			}
			return tcifdept;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(CardPersistence.class);
}

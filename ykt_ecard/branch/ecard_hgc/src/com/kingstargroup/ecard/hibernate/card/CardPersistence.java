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
 * Description: 卡表持久操作对象
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-2  
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
	 * Description:得到当前正在使用的卡
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
			q.setString(1, "10%");//代表为正常状态的卡
			return (TPifCard) q.uniqueResult();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:更新指定卡对象
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
	 * Description:根据学/工号和状态得到对应的卡对象
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
	 * Description:增加一条卡挂失信息
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
	 * Description:根据卡号和状态更新对应的卡挂失信息
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
	 * Description:得到挂失后重新补办正式卡需要的天数
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
	 * Description:增加一条黑名单记录
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
	 * Description:根据子系统类型和子系统状态得到子系统ID列表
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
	 * Description:得到插入流水表中的流水号
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
	 * Description:添加一个信息队列
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
	 * Description:增加一条交易流水
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

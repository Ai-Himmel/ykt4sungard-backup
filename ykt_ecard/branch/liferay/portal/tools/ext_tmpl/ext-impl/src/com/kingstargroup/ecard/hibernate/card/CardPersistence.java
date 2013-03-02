/**
 * 
 */
package com.kingstargroup.ecard.hibernate.card;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.service.persistence.BasePersistence;


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
public class CardPersistence extends BasePersistence {

	/**
	 * Description:
	 * @param customerId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public List getAvailableCards(String custid) throws DBSystemException {	
		
		Session session = null;		
		try {
			session = openSession();
			StringBuffer hsql = new StringBuffer();			
			hsql.append("from TCard card where")
				.append(" card.custid = ? and (card.status||card.lossflag||card.frozeflag||card.badflag) <> ? order by card.cardno desc");
			Query q = session.createQuery(hsql.toString());
			q.setInteger(0, Integer.parseInt(custid));
			q.setString(1, EcardConstants.CARD_WRITE_OFF_STATUS);						
			return q.list();
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}finally{			
			closeSession(session);
		}
	}
	
	public TCard getCardByno(Long cardno) throws DBSystemException {
		Session session = null;		
		try {
			session = openSession();
			return (TCard) session.get(TCard.class, cardno);
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
	public TCard getCurrentValidCard(String custid) throws DBSystemException {
		Session session = null;		
		try {
			session = openSession();
			StringBuffer hsql = new StringBuffer();			
			hsql.append("from TCard card where")
				.append(" card.custid = ? and (card.status||card.lossflag||card.frozeflag||card.badflag) = ?")
				.append(" order by card.status asc");
			Query q = session.createQuery(hsql.toString());
			q.setInteger(0, Integer.parseInt(custid));
			q.setString(1, "1000");//����Ϊ����״̬�Ŀ�
			return (TCard) q.uniqueResult();
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
	public void update(TCard card) throws DBSystemException {
		Session session = null;		
		try {
			session = openSession();
			session.update(card);
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
	public TCard getCardByCustidAndState(String custid, String state) throws DBSystemException {
		Session session = null;		
		try {
			session = openSession();
			StringMaker buff = new StringMaker();
			buff.append(" from TCard card where card.costid = ?")
				.append(" and (card.status||card.lossflag||card.frozeflag||card.badflag) = ?");
			Query query = session.createQuery(buff.toString());
			query.setInteger(0, Integer.parseInt(custid));
			query.setString(1, state);
			return (TCard) query.uniqueResult();
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		}
	}
	
	
	
	public TDept getDept(String deptcode) throws DBSystemException {
		Session session = null;	
		TDept tdept = null;	
		try {
			session = openSession();
			StringMaker buff = new StringMaker();
			buff.append(" from TDept dept")
				.append(" where dept.deptcode = ? ");			
			Query query = session.createQuery(buff.toString());
			query.setString(0, deptcode);
			List list = query.list();
			if(list!=null&&list.size()>0){
				tdept = (TDept)list.get(0);
			}
			return tdept;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(CardPersistence.class);
}

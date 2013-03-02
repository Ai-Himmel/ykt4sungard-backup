/**
 * 
 */
package com.kingstargroup.ecard.hibernate.picdelay;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Property;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PicDelayPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * �������� ������ ����ʱ�� ��������<br>
 * ===================================<br>
 * ���� Xiao Qi 2005-9-28 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class PicDelayPersistence extends BasePersistence {

	/**
	 * Description:���һ���µ���Ƭ����������Ϣ
	 * 
	 * @param delay
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public void saveOrUpdate(EcardPicDelay delay) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.saveOrUpdate(delay);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:
	 * 
	 * @param status
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public List getDelays(String status) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Criteria criteria = s.createCriteria(EcardPicDelay.class);
			criteria.add(org.hibernate.criterion.Expression
					.eq("status", status));
			criteria.addOrder(Property.forName("curStuempNo").desc());
			return criteria.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:���ݿͻ�ID�õ��˿ͻ���Ӧ����Ƭ������Ϣ
	 * 
	 * @param curStuempId
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public EcardPicDelay getDelayById(String curStuempId)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			return (EcardPicDelay) s.get(EcardPicDelay.class, curStuempId);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:���ݿͻ���ѧ����ɾ���˿ͻ�����Ƭ������Ϣ
	 * 
	 * @param id
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public void deleteDelayById(String id) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			EcardPicDelay delay = (EcardPicDelay) getDelayById(id);
			if (delay != null) {
				s.delete(delay);
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:����һ����Ƭ���õ�����Ϣ
	 * 
	 * @param file
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public void addPostponeFile(PostponeFiles file) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.save(file);
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:����id���ض�Ӧ����Ϣ
	 * 
	 * @param id
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public PostponeFiles getPostponeFile(int id) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			return (PostponeFiles) s.get(PostponeFiles.class, new Integer(id));
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:��ҳ��ѯ��Ƭ���õĵ�����Ϣ
	 * 
	 * @param page
	 * @param size
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public ResultPage getPostponeFiles(int page, int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Criteria criteria = s.createCriteria(PostponeFiles.class);
			criteria.setProjection(Projections.alias(Projections.rowCount(),
					"countRecords"));
			int totalRecords = ((Integer) criteria.uniqueResult()).intValue();
			criteria.setProjection(null);
			criteria.addOrder(Property.forName("id").desc());
			ResultPage result = new ResultPage(criteria, page, size);
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			throw new DBSystemException(e.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory
			.getLog(PicDelayPersistence.class);

}

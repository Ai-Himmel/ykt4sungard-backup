/**
 * 
 */
package com.kingstargroup.ecard.hibernate.information;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.criterion.Expression;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Property;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name:
 * InformationPersistence.java Description: Modify History: �������� ������ ����ʱ�� ��������
 * =================================== ���� Xiao Qi 2005-9-8
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class InformationPersistence extends BasePersistence {
	/**
	 * Description: ���洫�����Ϣ����
	 * 
	 * @param info
	 *            Ҫ�������Ϣ���� Modify History:
	 */
	public void add(EcardInformation info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.saveOrUpdate(info);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description: ���ݴ����id�õ���Ӧ����Ϣ����
	 * 
	 * @param id
	 *            ����id
	 * @return Modify History:
	 */
	public EcardInformation getInfoById(String id) throws DBSystemException {
		EcardInformation info = null;
		Session s = null;
		try {
			s = openSession();
			info = (EcardInformation) s.get(EcardInformation.class,
					new Integer(id));
			return info;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	public boolean update(EcardInformation info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.update(info);
			return true;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:�����û��ṩ�Ĳ�ѯ��ȡ�ö�Ӧ����
	 * 
	 * @param title
	 *            ��ѯ����
	 * @param content
	 *            ��ѯ����
	 * @param infoType
	 *            ��ѯ��Ϣ����
	 * @param page
	 *            ��Ҫ��ѯ��ҳ��
	 * @return Modify History:
	 */
	public ResultPage search(String title, String content, List infoType,
			int page, int size) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Criteria criteria = s.createCriteria(EcardInformation.class);
			criteria.add(Expression.in("infoType", infoType));

			if (title != null && !title.equals("")) {
				criteria.add(Expression.like("infoTitle", "%" + title + "%"));
			}
			if (content != null && !content.equals("")) {
				criteria.add(Expression
						.like("infoContent", "%" + content + "%"));
			}
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
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	public List search(String title) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Criteria criteria = s.createCriteria(EcardInformation.class);
			if (title != null && !title.equals("")) {
				criteria.add(Expression.like("infoTitle", "%" + title + "%"));
			}
			criteria.addOrder(Property.forName("createDate").desc());
			return criteria.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex);
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:���ݴ���Ҫɾ����ID����ɾ����Ӧ������
	 * 
	 * @param ids
	 *            Ҫɾ����ID����
	 * @return Modify History:
	 */
	public boolean deleteInfosByIds(String[] ids) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			for (int i = 0; i < ids.length; i++) {
				s.delete(getInfoById(ids[i]));
			}
			return true;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory
			.getLog(InformationPersistence.class);
}

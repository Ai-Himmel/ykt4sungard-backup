/**
 * 
 */
package com.kingstargroup.ecard.hibernate.infotype;

import java.util.Iterator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: InfoTypePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * �������� ������ ����ʱ�� ��������<br>
 * ===================================<br>
 * ���� Xiao Qi 2005-9-22 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class InfoTypePersistence extends BasePersistence {

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
	 * @return Modify History:��������˳��
	 */
	public ResultPage search(String infoType, String infoName, int page,
			int size) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			StringMaker countStr = new StringMaker("SELECT COUNT(*) ");
			StringMaker maker = new StringMaker();
			maker.append("FROM com.kingstargroup.ecard.hibernate.infotype.InfoType ");
			maker.append("where 1=1 ");
			if (infoType != null && !infoType.equals("")) {
				maker.append("and info_type like '%").append(infoType)
						.append("%'");
			}
			if (infoName != null && !infoName.equals("")) {
				maker.append("and info_name like '%").append(infoName)
						.append("%'");
			}
			
			
			Query q = s.createQuery(countStr.append(maker).toString());

			Long count = null;
		
			Iterator itr = q.list().iterator();
		
			if (itr.hasNext()) {
				count = (Long)itr.next();
			}
		
			if (count == null) {
				count = new Long(0);
			}

			maker.append(" order by substr(info_type, 3) desc");

			Query query = s.createQuery(maker.toString());
			ResultPage result = new ResultPage(query, page, size);
			int quotient = (int)(count / size);
			int remainder = (int)(count % size);
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


	/**
	 * Description:��������id�õ����Ͷ���
	 * 
	 * @param id
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public InfoType getTypeById(String id) throws DBSystemException {
		InfoType type = null;
		Session s = null;
		try {
			s = openSession();
			type = (InfoType) s.get(InfoType.class, id);
			return type;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description:���ݴ��������IDɾ����Ӧ����Ϣ���Ͷ���
	 * 
	 * @param ids
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public boolean deleteTypesByIds(String[] ids) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			for (int i = 0; i < ids.length; i++) {
				s.delete(getTypeById(ids[i]));
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
			.getLog(InfoTypePersistence.class);
}

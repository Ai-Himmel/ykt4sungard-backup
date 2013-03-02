/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchPropertiesException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="PropertiesPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class PropertiesPersistence extends BasePersistence {
	public com.liferay.portal.model.Properties create(PropertiesPK propertiesPK) {
		return new com.liferay.portal.model.Properties(propertiesPK);
	}

	public com.liferay.portal.model.Properties remove(PropertiesPK propertiesPK)
		throws NoSuchPropertiesException, SystemException {
		Session session = null;

		try {
			session = openSession();

			PropertiesHBM propertiesHBM = (PropertiesHBM)session.get(PropertiesHBM.class,
					propertiesPK);

			if (propertiesHBM == null) {
				_log.warn("No Properties exists with the primary key of " +
					propertiesPK.toString());
				throw new NoSuchPropertiesException(propertiesPK.toString());
			}

			com.liferay.portal.model.Properties properties = PropertiesHBMUtil.model(propertiesHBM);
			session.delete(propertiesHBM);
			session.flush();
			PropertiesPool.remove(propertiesPK);

			return properties;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Properties update(
		com.liferay.portal.model.Properties properties)
		throws SystemException {
		Session session = null;

		try {
			if (properties.isNew() || properties.isModified()) {
				session = openSession();

				if (properties.isNew()) {
					PropertiesHBM propertiesHBM = new PropertiesHBM(properties.getCompanyId(),
							properties.getType(), properties.getProperties());
					session.save(propertiesHBM);
					session.flush();
				}
				else {
					PropertiesHBM propertiesHBM = (PropertiesHBM)session.get(PropertiesHBM.class,
							properties.getPrimaryKey());

					if (propertiesHBM != null) {
						propertiesHBM.setProperties(properties.getProperties());
						session.flush();
					}
					else {
						propertiesHBM = new PropertiesHBM(properties.getCompanyId(),
								properties.getType(), properties.getProperties());
						session.save(propertiesHBM);
						session.flush();
					}
				}

				properties.setNew(false);
				properties.setModified(false);
				properties.protect();
				PropertiesPool.put(properties.getPrimaryKey(), properties);
			}

			return properties;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Properties findByPrimaryKey(
		PropertiesPK propertiesPK)
		throws NoSuchPropertiesException, SystemException {
		com.liferay.portal.model.Properties properties = PropertiesPool.get(propertiesPK);
		Session session = null;

		try {
			if (properties == null) {
				session = openSession();

				PropertiesHBM propertiesHBM = (PropertiesHBM)session.get(PropertiesHBM.class,
						propertiesPK);

				if (propertiesHBM == null) {
					_log.warn("No Properties exists with the primary key of " +
						propertiesPK.toString());
					throw new NoSuchPropertiesException(propertiesPK.toString());
				}

				properties = PropertiesHBMUtil.model(propertiesHBM);
			}

			return properties;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Properties IN CLASS com.liferay.portal.service.persistence.PropertiesHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PropertiesHBM propertiesHBM = (PropertiesHBM)itr.next();
				list.add(PropertiesHBMUtil.model(propertiesHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(String companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Properties IN CLASS com.liferay.portal.service.persistence.PropertiesHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					PropertiesHBM propertiesHBM = (PropertiesHBM)itr.next();
					list.add(PropertiesHBMUtil.model(propertiesHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						PropertiesHBM propertiesHBM = (PropertiesHBM)sr.get(0);
						list.add(PropertiesHBMUtil.model(propertiesHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Properties findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchPropertiesException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPropertiesException();
		}
		else {
			return (com.liferay.portal.model.Properties)list.get(0);
		}
	}

	public com.liferay.portal.model.Properties findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchPropertiesException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPropertiesException();
		}
		else {
			return (com.liferay.portal.model.Properties)list.get(0);
		}
	}

	public com.liferay.portal.model.Properties[] findByCompanyId_PrevAndNext(
		PropertiesPK propertiesPK, String companyId, OrderByComparator obc)
		throws NoSuchPropertiesException, SystemException {
		com.liferay.portal.model.Properties properties = findByPrimaryKey(propertiesPK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Properties IN CLASS com.liferay.portal.service.persistence.PropertiesHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portal.model.Properties[] array = new com.liferay.portal.model.Properties[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					PropertiesHBM propertiesHBM = (PropertiesHBM)sr.get(0);

					if (propertiesHBM == null) {
						break;
					}

					com.liferay.portal.model.Properties curProperties = PropertiesHBMUtil.model(propertiesHBM);
					int value = obc.compare(properties, curProperties);

					if (value == 0) {
						if (!properties.equals(curProperties)) {
							break;
						}

						array[1] = curProperties;

						if (sr.previous()) {
							array[0] = PropertiesHBMUtil.model((PropertiesHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = PropertiesHBMUtil.model((PropertiesHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Properties IN CLASS com.liferay.portal.service.persistence.PropertiesHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PropertiesHBM propertiesHBM = (PropertiesHBM)itr.next();
				list.add(PropertiesHBMUtil.model(propertiesHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Properties IN CLASS com.liferay.portal.service.persistence.PropertiesHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				PropertiesHBM propertiesHBM = (PropertiesHBM)itr.next();
				PropertiesPool.remove((PropertiesPK)propertiesHBM.getPrimaryKey());
				session.delete(propertiesHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Properties IN CLASS com.liferay.portal.service.persistence.PropertiesHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	private static final Log _log = LogFactory.getLog(PropertiesPersistence.class);
}
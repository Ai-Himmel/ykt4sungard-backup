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

import com.liferay.portal.NoSuchPortletException;
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
 * <a href="PortletPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class PortletPersistence extends BasePersistence {
	public com.liferay.portal.model.Portlet create(PortletPK portletPK) {
		return new com.liferay.portal.model.Portlet(portletPK);
	}

	public com.liferay.portal.model.Portlet remove(PortletPK portletPK)
		throws NoSuchPortletException, SystemException {
		Session session = null;

		try {
			session = openSession();

			PortletHBM portletHBM = (PortletHBM)session.get(PortletHBM.class,
					portletPK);

			if (portletHBM == null) {
				_log.warn("No Portlet exists with the primary key of " +
					portletPK.toString());
				throw new NoSuchPortletException(portletPK.toString());
			}

			com.liferay.portal.model.Portlet portlet = PortletHBMUtil.model(portletHBM);
			session.delete(portletHBM);
			session.flush();
			PortletPool.remove(portletPK);

			return portlet;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Portlet update(
		com.liferay.portal.model.Portlet portlet) throws SystemException {
		Session session = null;

		try {
			if (portlet.isNew() || portlet.isModified()) {
				session = openSession();

				if (portlet.isNew()) {
					PortletHBM portletHBM = new PortletHBM(portlet.getPortletId(),
							portlet.getCompanyId(), portlet.getNarrow(),
							portlet.getRoles(), portlet.getActive());
					session.save(portletHBM);
					session.flush();
				}
				else {
					PortletHBM portletHBM = (PortletHBM)session.get(PortletHBM.class,
							portlet.getPrimaryKey());

					if (portletHBM != null) {
						portletHBM.setNarrow(portlet.getNarrow());
						portletHBM.setRoles(portlet.getRoles());
						portletHBM.setActive(portlet.getActive());
						session.flush();
					}
					else {
						portletHBM = new PortletHBM(portlet.getPortletId(),
								portlet.getCompanyId(), portlet.getNarrow(),
								portlet.getRoles(), portlet.getActive());
						session.save(portletHBM);
						session.flush();
					}
				}

				portlet.setNew(false);
				portlet.setModified(false);
				portlet.protect();
				PortletPool.put(portlet.getPrimaryKey(), portlet);
			}

			return portlet;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Portlet findByPrimaryKey(
		PortletPK portletPK) throws NoSuchPortletException, SystemException {
		com.liferay.portal.model.Portlet portlet = PortletPool.get(portletPK);
		Session session = null;

		try {
			if (portlet == null) {
				session = openSession();

				PortletHBM portletHBM = (PortletHBM)session.get(PortletHBM.class,
						portletPK);

				if (portletHBM == null) {
					_log.warn("No Portlet exists with the primary key of " +
						portletPK.toString());
					throw new NoSuchPortletException(portletPK.toString());
				}

				portlet = PortletHBMUtil.model(portletHBM);
			}

			return portlet;
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
				"FROM Portlet IN CLASS com.liferay.portal.service.persistence.PortletHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PortletHBM portletHBM = (PortletHBM)itr.next();
				list.add(PortletHBMUtil.model(portletHBM));
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
				"FROM Portlet IN CLASS com.liferay.portal.service.persistence.PortletHBM WHERE ");
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
					PortletHBM portletHBM = (PortletHBM)itr.next();
					list.add(PortletHBMUtil.model(portletHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						PortletHBM portletHBM = (PortletHBM)sr.get(0);
						list.add(PortletHBMUtil.model(portletHBM));

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

	public com.liferay.portal.model.Portlet findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchPortletException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPortletException();
		}
		else {
			return (com.liferay.portal.model.Portlet)list.get(0);
		}
	}

	public com.liferay.portal.model.Portlet findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchPortletException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPortletException();
		}
		else {
			return (com.liferay.portal.model.Portlet)list.get(0);
		}
	}

	public com.liferay.portal.model.Portlet[] findByCompanyId_PrevAndNext(
		PortletPK portletPK, String companyId, OrderByComparator obc)
		throws NoSuchPortletException, SystemException {
		com.liferay.portal.model.Portlet portlet = findByPrimaryKey(portletPK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Portlet IN CLASS com.liferay.portal.service.persistence.PortletHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portal.model.Portlet[] array = new com.liferay.portal.model.Portlet[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					PortletHBM portletHBM = (PortletHBM)sr.get(0);

					if (portletHBM == null) {
						break;
					}

					com.liferay.portal.model.Portlet curPortlet = PortletHBMUtil.model(portletHBM);
					int value = obc.compare(portlet, curPortlet);

					if (value == 0) {
						if (!portlet.equals(curPortlet)) {
							break;
						}

						array[1] = curPortlet;

						if (sr.previous()) {
							array[0] = PortletHBMUtil.model((PortletHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = PortletHBMUtil.model((PortletHBM)sr.get(
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
				"FROM Portlet IN CLASS com.liferay.portal.service.persistence.PortletHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PortletHBM portletHBM = (PortletHBM)itr.next();
				list.add(PortletHBMUtil.model(portletHBM));
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
				"FROM Portlet IN CLASS com.liferay.portal.service.persistence.PortletHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				PortletHBM portletHBM = (PortletHBM)itr.next();
				PortletPool.remove((PortletPK)portletHBM.getPrimaryKey());
				session.delete(portletHBM);
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
				"FROM Portlet IN CLASS com.liferay.portal.service.persistence.PortletHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(PortletPersistence.class);
}
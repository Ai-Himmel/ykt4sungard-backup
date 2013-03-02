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

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="LayoutPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class LayoutPersistence extends BasePersistence {
	public com.liferay.portal.model.Layout create(LayoutPK layoutPK) {
		return new com.liferay.portal.model.Layout(layoutPK);
	}

	public com.liferay.portal.model.Layout remove(LayoutPK layoutPK)
		throws NoSuchLayoutException, SystemException {
		Session session = null;

		try {
			session = openSession();

			LayoutHBM layoutHBM = (LayoutHBM)session.get(LayoutHBM.class,
					layoutPK);

			if (layoutHBM == null) {
				_log.warn("No Layout exists with the primary key of " +
					layoutPK.toString());
				throw new NoSuchLayoutException(layoutPK.toString());
			}

			com.liferay.portal.model.Layout layout = LayoutHBMUtil.model(layoutHBM);
			session.delete(layoutHBM);
			session.flush();
			LayoutPool.remove(layoutPK);

			return layout;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Layout update(
		com.liferay.portal.model.Layout layout) throws SystemException {
		Session session = null;

		try {
			if (layout.isNew() || layout.isModified()) {
				session = openSession();

				if (layout.isNew()) {
					LayoutHBM layoutHBM = new LayoutHBM(layout.getLayoutId(),
							layout.getUserId(), layout.getCompanyId(),
							layout.getParentLayoutId(), layout.getName(),
							layout.getType(), layout.getTypeSettings(),
							layout.getFriendlyURL(), layout.getPriority());
					session.save(layoutHBM);
					session.flush();
				}
				else {
					LayoutHBM layoutHBM = (LayoutHBM)session.get(LayoutHBM.class,
							layout.getPrimaryKey());

					if (layoutHBM != null) {
						layoutHBM.setCompanyId(layout.getCompanyId());
						layoutHBM.setParentLayoutId(layout.getParentLayoutId());
						layoutHBM.setName(layout.getName());
						layoutHBM.setType(layout.getType());
						layoutHBM.setTypeSettings(layout.getTypeSettings());
						layoutHBM.setFriendlyURL(layout.getFriendlyURL());
						layoutHBM.setPriority(layout.getPriority());
						session.flush();
					}
					else {
						layoutHBM = new LayoutHBM(layout.getLayoutId(),
								layout.getUserId(), layout.getCompanyId(),
								layout.getParentLayoutId(), layout.getName(),
								layout.getType(), layout.getTypeSettings(),
								layout.getFriendlyURL(), layout.getPriority());
						session.save(layoutHBM);
						session.flush();
					}
				}

				layout.setNew(false);
				layout.setModified(false);
				layout.protect();
				LayoutPool.put(layout.getPrimaryKey(), layout);
			}

			return layout;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Layout findByPrimaryKey(LayoutPK layoutPK)
		throws NoSuchLayoutException, SystemException {
		com.liferay.portal.model.Layout layout = LayoutPool.get(layoutPK);
		Session session = null;

		try {
			if (layout == null) {
				session = openSession();

				LayoutHBM layoutHBM = (LayoutHBM)session.get(LayoutHBM.class,
						layoutPK);

				if (layoutHBM == null) {
					_log.warn("No Layout exists with the primary key of " +
						layoutPK.toString());
					throw new NoSuchLayoutException(layoutPK.toString());
				}

				layout = LayoutHBMUtil.model(layoutHBM);
			}

			return layout;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				LayoutHBM layoutHBM = (LayoutHBM)itr.next();
				list.add(LayoutHBMUtil.model(layoutHBM));
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

	public List findByUserId(String userId, int begin, int end)
		throws SystemException {
		return findByUserId(userId, begin, end, null);
	}

	public List findByUserId(String userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentLayoutId ASC").append(", ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					LayoutHBM layoutHBM = (LayoutHBM)itr.next();
					list.add(LayoutHBMUtil.model(layoutHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						LayoutHBM layoutHBM = (LayoutHBM)sr.get(0);
						list.add(LayoutHBMUtil.model(layoutHBM));

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

	public com.liferay.portal.model.Layout findByUserId_First(String userId,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchLayoutException();
		}
		else {
			return (com.liferay.portal.model.Layout)list.get(0);
		}
	}

	public com.liferay.portal.model.Layout findByUserId_Last(String userId,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchLayoutException();
		}
		else {
			return (com.liferay.portal.model.Layout)list.get(0);
		}
	}

	public com.liferay.portal.model.Layout[] findByUserId_PrevAndNext(
		LayoutPK layoutPK, String userId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		com.liferay.portal.model.Layout layout = findByPrimaryKey(layoutPK);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentLayoutId ASC").append(", ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portal.model.Layout[] array = new com.liferay.portal.model.Layout[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					LayoutHBM layoutHBM = (LayoutHBM)sr.get(0);

					if (layoutHBM == null) {
						break;
					}

					com.liferay.portal.model.Layout curLayout = LayoutHBMUtil.model(layoutHBM);
					int value = obc.compare(layout, curLayout);

					if (value == 0) {
						if (!layout.equals(curLayout)) {
							break;
						}

						array[1] = curLayout;

						if (sr.previous()) {
							array[0] = LayoutHBMUtil.model((LayoutHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = LayoutHBMUtil.model((LayoutHBM)sr.get(0));
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

	public List findByU_P(String userId, String parentLayoutId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentLayoutId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentLayoutId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				LayoutHBM layoutHBM = (LayoutHBM)itr.next();
				list.add(LayoutHBMUtil.model(layoutHBM));
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

	public List findByU_P(String userId, String parentLayoutId, int begin,
		int end) throws SystemException {
		return findByU_P(userId, parentLayoutId, begin, end, null);
	}

	public List findByU_P(String userId, String parentLayoutId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentLayoutId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentLayoutId ASC").append(", ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentLayoutId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					LayoutHBM layoutHBM = (LayoutHBM)itr.next();
					list.add(LayoutHBMUtil.model(layoutHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						LayoutHBM layoutHBM = (LayoutHBM)sr.get(0);
						list.add(LayoutHBMUtil.model(layoutHBM));

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

	public com.liferay.portal.model.Layout findByU_P_First(String userId,
		String parentLayoutId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		List list = findByU_P(userId, parentLayoutId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchLayoutException();
		}
		else {
			return (com.liferay.portal.model.Layout)list.get(0);
		}
	}

	public com.liferay.portal.model.Layout findByU_P_Last(String userId,
		String parentLayoutId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		int count = countByU_P(userId, parentLayoutId);
		List list = findByU_P(userId, parentLayoutId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchLayoutException();
		}
		else {
			return (com.liferay.portal.model.Layout)list.get(0);
		}
	}

	public com.liferay.portal.model.Layout[] findByU_P_PrevAndNext(
		LayoutPK layoutPK, String userId, String parentLayoutId,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		com.liferay.portal.model.Layout layout = findByPrimaryKey(layoutPK);
		int count = countByU_P(userId, parentLayoutId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentLayoutId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentLayoutId ASC").append(", ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentLayoutId);

			com.liferay.portal.model.Layout[] array = new com.liferay.portal.model.Layout[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					LayoutHBM layoutHBM = (LayoutHBM)sr.get(0);

					if (layoutHBM == null) {
						break;
					}

					com.liferay.portal.model.Layout curLayout = LayoutHBMUtil.model(layoutHBM);
					int value = obc.compare(layout, curLayout);

					if (value == 0) {
						if (!layout.equals(curLayout)) {
							break;
						}

						array[1] = curLayout;

						if (sr.previous()) {
							array[0] = LayoutHBMUtil.model((LayoutHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = LayoutHBMUtil.model((LayoutHBM)sr.get(0));
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

	public com.liferay.portal.model.Layout findByU_F(String userId,
		String friendlyURL) throws NoSuchLayoutException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("friendlyURL = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, friendlyURL);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchLayoutException();
			}

			LayoutHBM layoutHBM = (LayoutHBM)itr.next();

			return LayoutHBMUtil.model(layoutHBM);
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
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				LayoutHBM layoutHBM = (LayoutHBM)itr.next();
				list.add(LayoutHBMUtil.model(layoutHBM));
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

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				LayoutHBM layoutHBM = (LayoutHBM)itr.next();
				LayoutPool.remove((LayoutPK)layoutHBM.getPrimaryKey());
				session.delete(layoutHBM);
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

	public void removeByU_P(String userId, String parentLayoutId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentLayoutId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentLayoutId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				LayoutHBM layoutHBM = (LayoutHBM)itr.next();
				LayoutPool.remove((LayoutPK)layoutHBM.getPrimaryKey());
				session.delete(layoutHBM);
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

	public void removeByU_F(String userId, String friendlyURL)
		throws NoSuchLayoutException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("friendlyURL = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentLayoutId ASC").append(", ");
			query.append("priority ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, friendlyURL);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				LayoutHBM layoutHBM = (LayoutHBM)itr.next();
				LayoutPool.remove((LayoutPK)layoutHBM.getPrimaryKey());
				session.delete(layoutHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchLayoutException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

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

	public int countByU_P(String userId, String parentLayoutId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentLayoutId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentLayoutId);

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

	public int countByU_F(String userId, String friendlyURL)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Layout IN CLASS com.liferay.portal.service.persistence.LayoutHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("friendlyURL = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, friendlyURL);

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

	private static final Log _log = LogFactory.getLog(LayoutPersistence.class);
}
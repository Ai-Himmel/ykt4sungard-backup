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

import com.liferay.portal.NoSuchUserTrackerException;
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
 * <a href="UserTrackerPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserTrackerPersistence extends BasePersistence {
	public com.liferay.portal.model.UserTracker create(String userTrackerId) {
		return new com.liferay.portal.model.UserTracker(userTrackerId);
	}

	public com.liferay.portal.model.UserTracker remove(String userTrackerId)
		throws NoSuchUserTrackerException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserTrackerHBM userTrackerHBM = (UserTrackerHBM)session.get(UserTrackerHBM.class,
					userTrackerId);

			if (userTrackerHBM == null) {
				_log.warn("No UserTracker exists with the primary key of " +
					userTrackerId.toString());
				throw new NoSuchUserTrackerException(userTrackerId.toString());
			}

			com.liferay.portal.model.UserTracker userTracker = UserTrackerHBMUtil.model(userTrackerHBM);
			session.delete(userTrackerHBM);
			session.flush();
			UserTrackerPool.remove(userTrackerId);

			return userTracker;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.UserTracker update(
		com.liferay.portal.model.UserTracker userTracker)
		throws SystemException {
		Session session = null;

		try {
			if (userTracker.isNew() || userTracker.isModified()) {
				session = openSession();

				if (userTracker.isNew()) {
					UserTrackerHBM userTrackerHBM = new UserTrackerHBM(userTracker.getUserTrackerId(),
							userTracker.getCompanyId(),
							userTracker.getUserId(),
							userTracker.getModifiedDate(),
							userTracker.getRemoteAddr(),
							userTracker.getRemoteHost(),
							userTracker.getUserAgent());
					session.save(userTrackerHBM);
					session.flush();
				}
				else {
					UserTrackerHBM userTrackerHBM = (UserTrackerHBM)session.get(UserTrackerHBM.class,
							userTracker.getPrimaryKey());

					if (userTrackerHBM != null) {
						userTrackerHBM.setCompanyId(userTracker.getCompanyId());
						userTrackerHBM.setUserId(userTracker.getUserId());
						userTrackerHBM.setModifiedDate(userTracker.getModifiedDate());
						userTrackerHBM.setRemoteAddr(userTracker.getRemoteAddr());
						userTrackerHBM.setRemoteHost(userTracker.getRemoteHost());
						userTrackerHBM.setUserAgent(userTracker.getUserAgent());
						session.flush();
					}
					else {
						userTrackerHBM = new UserTrackerHBM(userTracker.getUserTrackerId(),
								userTracker.getCompanyId(),
								userTracker.getUserId(),
								userTracker.getModifiedDate(),
								userTracker.getRemoteAddr(),
								userTracker.getRemoteHost(),
								userTracker.getUserAgent());
						session.save(userTrackerHBM);
						session.flush();
					}
				}

				userTracker.setNew(false);
				userTracker.setModified(false);
				userTracker.protect();
				UserTrackerPool.put(userTracker.getPrimaryKey(), userTracker);
			}

			return userTracker;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.UserTracker findByPrimaryKey(
		String userTrackerId)
		throws NoSuchUserTrackerException, SystemException {
		com.liferay.portal.model.UserTracker userTracker = UserTrackerPool.get(userTrackerId);
		Session session = null;

		try {
			if (userTracker == null) {
				session = openSession();

				UserTrackerHBM userTrackerHBM = (UserTrackerHBM)session.get(UserTrackerHBM.class,
						userTrackerId);

				if (userTrackerHBM == null) {
					_log.warn("No UserTracker exists with the primary key of " +
						userTrackerId.toString());
					throw new NoSuchUserTrackerException(userTrackerId.toString());
				}

				userTracker = UserTrackerHBMUtil.model(userTrackerHBM);
			}

			return userTracker;
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
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
				list.add(UserTrackerHBMUtil.model(userTrackerHBM));
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
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
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
					UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
					list.add(UserTrackerHBMUtil.model(userTrackerHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						UserTrackerHBM userTrackerHBM = (UserTrackerHBM)sr.get(0);
						list.add(UserTrackerHBMUtil.model(userTrackerHBM));

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

	public com.liferay.portal.model.UserTracker findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchUserTrackerException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchUserTrackerException();
		}
		else {
			return (com.liferay.portal.model.UserTracker)list.get(0);
		}
	}

	public com.liferay.portal.model.UserTracker findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchUserTrackerException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchUserTrackerException();
		}
		else {
			return (com.liferay.portal.model.UserTracker)list.get(0);
		}
	}

	public com.liferay.portal.model.UserTracker[] findByCompanyId_PrevAndNext(
		String userTrackerId, String companyId, OrderByComparator obc)
		throws NoSuchUserTrackerException, SystemException {
		com.liferay.portal.model.UserTracker userTracker = findByPrimaryKey(userTrackerId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portal.model.UserTracker[] array = new com.liferay.portal.model.UserTracker[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					UserTrackerHBM userTrackerHBM = (UserTrackerHBM)sr.get(0);

					if (userTrackerHBM == null) {
						break;
					}

					com.liferay.portal.model.UserTracker curUserTracker = UserTrackerHBMUtil.model(userTrackerHBM);
					int value = obc.compare(userTracker, curUserTracker);

					if (value == 0) {
						if (!userTracker.equals(curUserTracker)) {
							break;
						}

						array[1] = curUserTracker;

						if (sr.previous()) {
							array[0] = UserTrackerHBMUtil.model((UserTrackerHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = UserTrackerHBMUtil.model((UserTrackerHBM)sr.get(
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

	public List findByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
				list.add(UserTrackerHBMUtil.model(userTrackerHBM));
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
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
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
					UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
					list.add(UserTrackerHBMUtil.model(userTrackerHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						UserTrackerHBM userTrackerHBM = (UserTrackerHBM)sr.get(0);
						list.add(UserTrackerHBMUtil.model(userTrackerHBM));

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

	public com.liferay.portal.model.UserTracker findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchUserTrackerException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchUserTrackerException();
		}
		else {
			return (com.liferay.portal.model.UserTracker)list.get(0);
		}
	}

	public com.liferay.portal.model.UserTracker findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchUserTrackerException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchUserTrackerException();
		}
		else {
			return (com.liferay.portal.model.UserTracker)list.get(0);
		}
	}

	public com.liferay.portal.model.UserTracker[] findByUserId_PrevAndNext(
		String userTrackerId, String userId, OrderByComparator obc)
		throws NoSuchUserTrackerException, SystemException {
		com.liferay.portal.model.UserTracker userTracker = findByPrimaryKey(userTrackerId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portal.model.UserTracker[] array = new com.liferay.portal.model.UserTracker[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					UserTrackerHBM userTrackerHBM = (UserTrackerHBM)sr.get(0);

					if (userTrackerHBM == null) {
						break;
					}

					com.liferay.portal.model.UserTracker curUserTracker = UserTrackerHBMUtil.model(userTrackerHBM);
					int value = obc.compare(userTracker, curUserTracker);

					if (value == 0) {
						if (!userTracker.equals(curUserTracker)) {
							break;
						}

						array[1] = curUserTracker;

						if (sr.previous()) {
							array[0] = UserTrackerHBMUtil.model((UserTrackerHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = UserTrackerHBMUtil.model((UserTrackerHBM)sr.get(
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
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
				list.add(UserTrackerHBMUtil.model(userTrackerHBM));
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
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
				UserTrackerPool.remove((String)userTrackerHBM.getPrimaryKey());
				session.delete(userTrackerHBM);
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

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserTrackerHBM userTrackerHBM = (UserTrackerHBM)itr.next();
				UserTrackerPool.remove((String)userTrackerHBM.getPrimaryKey());
				session.delete(userTrackerHBM);
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
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
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

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM UserTracker IN CLASS com.liferay.portal.service.persistence.UserTrackerHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(UserTrackerPersistence.class);
}
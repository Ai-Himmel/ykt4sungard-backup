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

import com.liferay.portal.NoSuchUserTrackerPathException;
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
 * <a href="UserTrackerPathPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserTrackerPathPersistence extends BasePersistence {
	public com.liferay.portal.model.UserTrackerPath create(
		String userTrackerPathId) {
		return new com.liferay.portal.model.UserTrackerPath(userTrackerPathId);
	}

	public com.liferay.portal.model.UserTrackerPath remove(
		String userTrackerPathId)
		throws NoSuchUserTrackerPathException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)session.get(UserTrackerPathHBM.class,
					userTrackerPathId);

			if (userTrackerPathHBM == null) {
				_log.warn("No UserTrackerPath exists with the primary key of " +
					userTrackerPathId.toString());
				throw new NoSuchUserTrackerPathException(userTrackerPathId.toString());
			}

			com.liferay.portal.model.UserTrackerPath userTrackerPath = UserTrackerPathHBMUtil.model(userTrackerPathHBM);
			session.delete(userTrackerPathHBM);
			session.flush();
			UserTrackerPathPool.remove(userTrackerPathId);

			return userTrackerPath;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.UserTrackerPath update(
		com.liferay.portal.model.UserTrackerPath userTrackerPath)
		throws SystemException {
		Session session = null;

		try {
			if (userTrackerPath.isNew() || userTrackerPath.isModified()) {
				session = openSession();

				if (userTrackerPath.isNew()) {
					UserTrackerPathHBM userTrackerPathHBM = new UserTrackerPathHBM(userTrackerPath.getUserTrackerPathId(),
							userTrackerPath.getUserTrackerId(),
							userTrackerPath.getPath(),
							userTrackerPath.getPathDate());
					session.save(userTrackerPathHBM);
					session.flush();
				}
				else {
					UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)session.get(UserTrackerPathHBM.class,
							userTrackerPath.getPrimaryKey());

					if (userTrackerPathHBM != null) {
						userTrackerPathHBM.setUserTrackerId(userTrackerPath.getUserTrackerId());
						userTrackerPathHBM.setPath(userTrackerPath.getPath());
						userTrackerPathHBM.setPathDate(userTrackerPath.getPathDate());
						session.flush();
					}
					else {
						userTrackerPathHBM = new UserTrackerPathHBM(userTrackerPath.getUserTrackerPathId(),
								userTrackerPath.getUserTrackerId(),
								userTrackerPath.getPath(),
								userTrackerPath.getPathDate());
						session.save(userTrackerPathHBM);
						session.flush();
					}
				}

				userTrackerPath.setNew(false);
				userTrackerPath.setModified(false);
				userTrackerPath.protect();
				UserTrackerPathPool.put(userTrackerPath.getPrimaryKey(),
					userTrackerPath);
			}

			return userTrackerPath;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.UserTrackerPath findByPrimaryKey(
		String userTrackerPathId)
		throws NoSuchUserTrackerPathException, SystemException {
		com.liferay.portal.model.UserTrackerPath userTrackerPath = UserTrackerPathPool.get(userTrackerPathId);
		Session session = null;

		try {
			if (userTrackerPath == null) {
				session = openSession();

				UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)session.get(UserTrackerPathHBM.class,
						userTrackerPathId);

				if (userTrackerPathHBM == null) {
					_log.warn(
						"No UserTrackerPath exists with the primary key of " +
						userTrackerPathId.toString());
					throw new NoSuchUserTrackerPathException(userTrackerPathId.toString());
				}

				userTrackerPath = UserTrackerPathHBMUtil.model(userTrackerPathHBM);
			}

			return userTrackerPath;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByUserTrackerId(String userTrackerId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTrackerPath IN CLASS com.liferay.portal.service.persistence.UserTrackerPathHBM WHERE ");
			query.append("userTrackerId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userTrackerId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)itr.next();
				list.add(UserTrackerPathHBMUtil.model(userTrackerPathHBM));
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

	public List findByUserTrackerId(String userTrackerId, int begin, int end)
		throws SystemException {
		return findByUserTrackerId(userTrackerId, begin, end, null);
	}

	public List findByUserTrackerId(String userTrackerId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTrackerPath IN CLASS com.liferay.portal.service.persistence.UserTrackerPathHBM WHERE ");
			query.append("userTrackerId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userTrackerId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)itr.next();
					list.add(UserTrackerPathHBMUtil.model(userTrackerPathHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)sr.get(0);
						list.add(UserTrackerPathHBMUtil.model(
								userTrackerPathHBM));

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

	public com.liferay.portal.model.UserTrackerPath findByUserTrackerId_First(
		String userTrackerId, OrderByComparator obc)
		throws NoSuchUserTrackerPathException, SystemException {
		List list = findByUserTrackerId(userTrackerId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchUserTrackerPathException();
		}
		else {
			return (com.liferay.portal.model.UserTrackerPath)list.get(0);
		}
	}

	public com.liferay.portal.model.UserTrackerPath findByUserTrackerId_Last(
		String userTrackerId, OrderByComparator obc)
		throws NoSuchUserTrackerPathException, SystemException {
		int count = countByUserTrackerId(userTrackerId);
		List list = findByUserTrackerId(userTrackerId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchUserTrackerPathException();
		}
		else {
			return (com.liferay.portal.model.UserTrackerPath)list.get(0);
		}
	}

	public com.liferay.portal.model.UserTrackerPath[] findByUserTrackerId_PrevAndNext(
		String userTrackerPathId, String userTrackerId, OrderByComparator obc)
		throws NoSuchUserTrackerPathException, SystemException {
		com.liferay.portal.model.UserTrackerPath userTrackerPath = findByPrimaryKey(userTrackerPathId);
		int count = countByUserTrackerId(userTrackerId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTrackerPath IN CLASS com.liferay.portal.service.persistence.UserTrackerPathHBM WHERE ");
			query.append("userTrackerId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userTrackerId);

			com.liferay.portal.model.UserTrackerPath[] array = new com.liferay.portal.model.UserTrackerPath[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)sr.get(0);

					if (userTrackerPathHBM == null) {
						break;
					}

					com.liferay.portal.model.UserTrackerPath curUserTrackerPath = UserTrackerPathHBMUtil.model(userTrackerPathHBM);
					int value = obc.compare(userTrackerPath, curUserTrackerPath);

					if (value == 0) {
						if (!userTrackerPath.equals(curUserTrackerPath)) {
							break;
						}

						array[1] = curUserTrackerPath;

						if (sr.previous()) {
							array[0] = UserTrackerPathHBMUtil.model((UserTrackerPathHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = UserTrackerPathHBMUtil.model((UserTrackerPathHBM)sr.get(
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
				"FROM UserTrackerPath IN CLASS com.liferay.portal.service.persistence.UserTrackerPathHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)itr.next();
				list.add(UserTrackerPathHBMUtil.model(userTrackerPathHBM));
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

	public void removeByUserTrackerId(String userTrackerId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM UserTrackerPath IN CLASS com.liferay.portal.service.persistence.UserTrackerPathHBM WHERE ");
			query.append("userTrackerId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userTrackerId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				UserTrackerPathHBM userTrackerPathHBM = (UserTrackerPathHBM)itr.next();
				UserTrackerPathPool.remove((String)userTrackerPathHBM.getPrimaryKey());
				session.delete(userTrackerPathHBM);
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

	public int countByUserTrackerId(String userTrackerId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM UserTrackerPath IN CLASS com.liferay.portal.service.persistence.UserTrackerPathHBM WHERE ");
			query.append("userTrackerId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userTrackerId);

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

	private static final Log _log = LogFactory.getLog(UserTrackerPathPersistence.class);
}
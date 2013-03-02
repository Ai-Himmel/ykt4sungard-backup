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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.blogs.NoSuchUserException;

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
 * <a href="BlogsUserPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsUserPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsUser create(String userId) {
		return new com.liferay.portlet.blogs.model.BlogsUser(userId);
	}

	public com.liferay.portlet.blogs.model.BlogsUser remove(String userId)
		throws NoSuchUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsUserHBM blogsUserHBM = (BlogsUserHBM)session.get(BlogsUserHBM.class,
					userId);

			if (blogsUserHBM == null) {
				_log.warn("No BlogsUser exists with the primary key of " +
					userId.toString());
				throw new NoSuchUserException(userId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsUser blogsUser = BlogsUserHBMUtil.model(blogsUserHBM);
			session.delete(blogsUserHBM);
			session.flush();
			BlogsUserPool.remove(userId);

			return blogsUser;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsUser update(
		com.liferay.portlet.blogs.model.BlogsUser blogsUser)
		throws SystemException {
		Session session = null;

		try {
			if (blogsUser.isNew() || blogsUser.isModified()) {
				session = openSession();

				if (blogsUser.isNew()) {
					BlogsUserHBM blogsUserHBM = new BlogsUserHBM(blogsUser.getUserId(),
							blogsUser.getCompanyId(), blogsUser.getEntryId(),
							blogsUser.getLastPostDate());
					session.save(blogsUserHBM);
					session.flush();
				}
				else {
					BlogsUserHBM blogsUserHBM = (BlogsUserHBM)session.get(BlogsUserHBM.class,
							blogsUser.getPrimaryKey());

					if (blogsUserHBM != null) {
						blogsUserHBM.setCompanyId(blogsUser.getCompanyId());
						blogsUserHBM.setEntryId(blogsUser.getEntryId());
						blogsUserHBM.setLastPostDate(blogsUser.getLastPostDate());
						session.flush();
					}
					else {
						blogsUserHBM = new BlogsUserHBM(blogsUser.getUserId(),
								blogsUser.getCompanyId(),
								blogsUser.getEntryId(),
								blogsUser.getLastPostDate());
						session.save(blogsUserHBM);
						session.flush();
					}
				}

				blogsUser.setNew(false);
				blogsUser.setModified(false);
				blogsUser.protect();
				BlogsUserPool.put(blogsUser.getPrimaryKey(), blogsUser);
			}

			return blogsUser;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsUser findByPrimaryKey(
		String userId) throws NoSuchUserException, SystemException {
		com.liferay.portlet.blogs.model.BlogsUser blogsUser = BlogsUserPool.get(userId);
		Session session = null;

		try {
			if (blogsUser == null) {
				session = openSession();

				BlogsUserHBM blogsUserHBM = (BlogsUserHBM)session.get(BlogsUserHBM.class,
						userId);

				if (blogsUserHBM == null) {
					_log.warn("No BlogsUser exists with the primary key of " +
						userId.toString());
					throw new NoSuchUserException(userId.toString());
				}

				blogsUser = BlogsUserHBMUtil.model(blogsUserHBM);
			}

			return blogsUser;
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
				"FROM BlogsUser IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsUserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("lastPostDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsUserHBM blogsUserHBM = (BlogsUserHBM)itr.next();
				list.add(BlogsUserHBMUtil.model(blogsUserHBM));
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
				"FROM BlogsUser IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsUserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("lastPostDate DESC");
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
					BlogsUserHBM blogsUserHBM = (BlogsUserHBM)itr.next();
					list.add(BlogsUserHBMUtil.model(blogsUserHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsUserHBM blogsUserHBM = (BlogsUserHBM)sr.get(0);
						list.add(BlogsUserHBMUtil.model(blogsUserHBM));

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

	public com.liferay.portlet.blogs.model.BlogsUser findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchUserException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsUser)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsUser findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchUserException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsUser)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsUser[] findByCompanyId_PrevAndNext(
		String userId, String companyId, OrderByComparator obc)
		throws NoSuchUserException, SystemException {
		com.liferay.portlet.blogs.model.BlogsUser blogsUser = findByPrimaryKey(userId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsUser IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsUserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("lastPostDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.blogs.model.BlogsUser[] array = new com.liferay.portlet.blogs.model.BlogsUser[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsUserHBM blogsUserHBM = (BlogsUserHBM)sr.get(0);

					if (blogsUserHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsUser curBlogsUser = BlogsUserHBMUtil.model(blogsUserHBM);
					int value = obc.compare(blogsUser, curBlogsUser);

					if (value == 0) {
						if (!blogsUser.equals(curBlogsUser)) {
							break;
						}

						array[1] = curBlogsUser;

						if (sr.previous()) {
							array[0] = BlogsUserHBMUtil.model((BlogsUserHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsUserHBMUtil.model((BlogsUserHBM)sr.get(
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
				"FROM BlogsUser IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsUserHBM ");
			query.append("ORDER BY ");
			query.append("lastPostDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsUserHBM blogsUserHBM = (BlogsUserHBM)itr.next();
				list.add(BlogsUserHBMUtil.model(blogsUserHBM));
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
				"FROM BlogsUser IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsUserHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("lastPostDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsUserHBM blogsUserHBM = (BlogsUserHBM)itr.next();
				BlogsUserPool.remove((String)blogsUserHBM.getPrimaryKey());
				session.delete(blogsUserHBM);
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
				"FROM BlogsUser IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsUserHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(BlogsUserPersistence.class);
}
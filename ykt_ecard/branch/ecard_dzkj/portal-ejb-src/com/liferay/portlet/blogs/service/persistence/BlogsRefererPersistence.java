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

import com.liferay.portlet.blogs.NoSuchRefererException;

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
 * <a href="BlogsRefererPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsRefererPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsReferer create(String refererId) {
		return new com.liferay.portlet.blogs.model.BlogsReferer(refererId);
	}

	public com.liferay.portlet.blogs.model.BlogsReferer remove(String refererId)
		throws NoSuchRefererException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)session.get(BlogsRefererHBM.class,
					refererId);

			if (blogsRefererHBM == null) {
				_log.warn("No BlogsReferer exists with the primary key of " +
					refererId.toString());
				throw new NoSuchRefererException(refererId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsReferer blogsReferer = BlogsRefererHBMUtil.model(blogsRefererHBM);
			session.delete(blogsRefererHBM);
			session.flush();
			BlogsRefererPool.remove(refererId);

			return blogsReferer;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsReferer update(
		com.liferay.portlet.blogs.model.BlogsReferer blogsReferer)
		throws SystemException {
		Session session = null;

		try {
			if (blogsReferer.isNew() || blogsReferer.isModified()) {
				session = openSession();

				if (blogsReferer.isNew()) {
					BlogsRefererHBM blogsRefererHBM = new BlogsRefererHBM(blogsReferer.getRefererId(),
							blogsReferer.getEntryId(), blogsReferer.getUrl(),
							blogsReferer.getType(), blogsReferer.getQuantity());
					session.save(blogsRefererHBM);
					session.flush();
				}
				else {
					BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)session.get(BlogsRefererHBM.class,
							blogsReferer.getPrimaryKey());

					if (blogsRefererHBM != null) {
						blogsRefererHBM.setEntryId(blogsReferer.getEntryId());
						blogsRefererHBM.setUrl(blogsReferer.getUrl());
						blogsRefererHBM.setType(blogsReferer.getType());
						blogsRefererHBM.setQuantity(blogsReferer.getQuantity());
						session.flush();
					}
					else {
						blogsRefererHBM = new BlogsRefererHBM(blogsReferer.getRefererId(),
								blogsReferer.getEntryId(),
								blogsReferer.getUrl(), blogsReferer.getType(),
								blogsReferer.getQuantity());
						session.save(blogsRefererHBM);
						session.flush();
					}
				}

				blogsReferer.setNew(false);
				blogsReferer.setModified(false);
				blogsReferer.protect();
				BlogsRefererPool.put(blogsReferer.getPrimaryKey(), blogsReferer);
			}

			return blogsReferer;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsReferer findByPrimaryKey(
		String refererId) throws NoSuchRefererException, SystemException {
		com.liferay.portlet.blogs.model.BlogsReferer blogsReferer = BlogsRefererPool.get(refererId);
		Session session = null;

		try {
			if (blogsReferer == null) {
				session = openSession();

				BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)session.get(BlogsRefererHBM.class,
						refererId);

				if (blogsRefererHBM == null) {
					_log.warn("No BlogsReferer exists with the primary key of " +
						refererId.toString());
					throw new NoSuchRefererException(refererId.toString());
				}

				blogsReferer = BlogsRefererHBMUtil.model(blogsRefererHBM);
			}

			return blogsReferer;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByEntryId(String entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("type_ ASC").append(", ");
			query.append("quantity ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
				list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));
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

	public List findByEntryId(String entryId, int begin, int end)
		throws SystemException {
		return findByEntryId(entryId, begin, end, null);
	}

	public List findByEntryId(String entryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("type_ ASC").append(", ");
				query.append("quantity ASC").append(", ");
				query.append("url ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
					list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)sr.get(0);
						list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));

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

	public com.liferay.portlet.blogs.model.BlogsReferer findByEntryId_First(
		String entryId, OrderByComparator obc)
		throws NoSuchRefererException, SystemException {
		List list = findByEntryId(entryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchRefererException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsReferer)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsReferer findByEntryId_Last(
		String entryId, OrderByComparator obc)
		throws NoSuchRefererException, SystemException {
		int count = countByEntryId(entryId);
		List list = findByEntryId(entryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchRefererException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsReferer)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsReferer[] findByEntryId_PrevAndNext(
		String refererId, String entryId, OrderByComparator obc)
		throws NoSuchRefererException, SystemException {
		com.liferay.portlet.blogs.model.BlogsReferer blogsReferer = findByPrimaryKey(refererId);
		int count = countByEntryId(entryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("type_ ASC").append(", ");
				query.append("quantity ASC").append(", ");
				query.append("url ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			com.liferay.portlet.blogs.model.BlogsReferer[] array = new com.liferay.portlet.blogs.model.BlogsReferer[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)sr.get(0);

					if (blogsRefererHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsReferer curBlogsReferer =
						BlogsRefererHBMUtil.model(blogsRefererHBM);
					int value = obc.compare(blogsReferer, curBlogsReferer);

					if (value == 0) {
						if (!blogsReferer.equals(curBlogsReferer)) {
							break;
						}

						array[1] = curBlogsReferer;

						if (sr.previous()) {
							array[0] = BlogsRefererHBMUtil.model((BlogsRefererHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsRefererHBMUtil.model((BlogsRefererHBM)sr.get(
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

	public List findByE_T(String entryId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("type_ ASC").append(", ");
			query.append("quantity ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
				list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));
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

	public List findByE_T(String entryId, String type, int begin, int end)
		throws SystemException {
		return findByE_T(entryId, type, begin, end, null);
	}

	public List findByE_T(String entryId, String type, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("type_ ASC").append(", ");
				query.append("quantity ASC").append(", ");
				query.append("url ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setString(queryPos++, type);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
					list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)sr.get(0);
						list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));

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

	public com.liferay.portlet.blogs.model.BlogsReferer findByE_T_First(
		String entryId, String type, OrderByComparator obc)
		throws NoSuchRefererException, SystemException {
		List list = findByE_T(entryId, type, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchRefererException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsReferer)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsReferer findByE_T_Last(
		String entryId, String type, OrderByComparator obc)
		throws NoSuchRefererException, SystemException {
		int count = countByE_T(entryId, type);
		List list = findByE_T(entryId, type, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchRefererException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsReferer)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsReferer[] findByE_T_PrevAndNext(
		String refererId, String entryId, String type, OrderByComparator obc)
		throws NoSuchRefererException, SystemException {
		com.liferay.portlet.blogs.model.BlogsReferer blogsReferer = findByPrimaryKey(refererId);
		int count = countByE_T(entryId, type);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("type_ ASC").append(", ");
				query.append("quantity ASC").append(", ");
				query.append("url ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setString(queryPos++, type);

			com.liferay.portlet.blogs.model.BlogsReferer[] array = new com.liferay.portlet.blogs.model.BlogsReferer[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)sr.get(0);

					if (blogsRefererHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsReferer curBlogsReferer =
						BlogsRefererHBMUtil.model(blogsRefererHBM);
					int value = obc.compare(blogsReferer, curBlogsReferer);

					if (value == 0) {
						if (!blogsReferer.equals(curBlogsReferer)) {
							break;
						}

						array[1] = curBlogsReferer;

						if (sr.previous()) {
							array[0] = BlogsRefererHBMUtil.model((BlogsRefererHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsRefererHBMUtil.model((BlogsRefererHBM)sr.get(
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
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("type_ ASC").append(", ");
			query.append("quantity ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
				list.add(BlogsRefererHBMUtil.model(blogsRefererHBM));
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

	public void removeByEntryId(String entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("type_ ASC").append(", ");
			query.append("quantity ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
				BlogsRefererPool.remove((String)blogsRefererHBM.getPrimaryKey());
				session.delete(blogsRefererHBM);
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

	public void removeByE_T(String entryId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("type_ ASC").append(", ");
			query.append("quantity ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsRefererHBM blogsRefererHBM = (BlogsRefererHBM)itr.next();
				BlogsRefererPool.remove((String)blogsRefererHBM.getPrimaryKey());
				session.delete(blogsRefererHBM);
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

	public int countByEntryId(String entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

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

	public int countByE_T(String entryId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsReferer IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsRefererHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setString(queryPos++, type);

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

	private static final Log _log = LogFactory.getLog(BlogsRefererPersistence.class);
}
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

import com.liferay.portlet.blogs.NoSuchLinkException;

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
 * <a href="BlogsLinkPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsLinkPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsLink create(String linkId) {
		return new com.liferay.portlet.blogs.model.BlogsLink(linkId);
	}

	public com.liferay.portlet.blogs.model.BlogsLink remove(String linkId)
		throws NoSuchLinkException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)session.get(BlogsLinkHBM.class,
					linkId);

			if (blogsLinkHBM == null) {
				_log.warn("No BlogsLink exists with the primary key of " +
					linkId.toString());
				throw new NoSuchLinkException(linkId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsLink blogsLink = BlogsLinkHBMUtil.model(blogsLinkHBM);
			session.delete(blogsLinkHBM);
			session.flush();
			BlogsLinkPool.remove(linkId);

			return blogsLink;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsLink update(
		com.liferay.portlet.blogs.model.BlogsLink blogsLink)
		throws SystemException {
		Session session = null;

		try {
			if (blogsLink.isNew() || blogsLink.isModified()) {
				session = openSession();

				if (blogsLink.isNew()) {
					BlogsLinkHBM blogsLinkHBM = new BlogsLinkHBM(blogsLink.getLinkId(),
							blogsLink.getCompanyId(), blogsLink.getUserId(),
							blogsLink.getCreateDate(),
							blogsLink.getModifiedDate(), blogsLink.getName(),
							blogsLink.getUrl());
					session.save(blogsLinkHBM);
					session.flush();
				}
				else {
					BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)session.get(BlogsLinkHBM.class,
							blogsLink.getPrimaryKey());

					if (blogsLinkHBM != null) {
						blogsLinkHBM.setCompanyId(blogsLink.getCompanyId());
						blogsLinkHBM.setUserId(blogsLink.getUserId());
						blogsLinkHBM.setCreateDate(blogsLink.getCreateDate());
						blogsLinkHBM.setModifiedDate(blogsLink.getModifiedDate());
						blogsLinkHBM.setName(blogsLink.getName());
						blogsLinkHBM.setUrl(blogsLink.getUrl());
						session.flush();
					}
					else {
						blogsLinkHBM = new BlogsLinkHBM(blogsLink.getLinkId(),
								blogsLink.getCompanyId(),
								blogsLink.getUserId(),
								blogsLink.getCreateDate(),
								blogsLink.getModifiedDate(),
								blogsLink.getName(), blogsLink.getUrl());
						session.save(blogsLinkHBM);
						session.flush();
					}
				}

				blogsLink.setNew(false);
				blogsLink.setModified(false);
				blogsLink.protect();
				BlogsLinkPool.put(blogsLink.getPrimaryKey(), blogsLink);
			}

			return blogsLink;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsLink findByPrimaryKey(
		String linkId) throws NoSuchLinkException, SystemException {
		com.liferay.portlet.blogs.model.BlogsLink blogsLink = BlogsLinkPool.get(linkId);
		Session session = null;

		try {
			if (blogsLink == null) {
				session = openSession();

				BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)session.get(BlogsLinkHBM.class,
						linkId);

				if (blogsLinkHBM == null) {
					_log.warn("No BlogsLink exists with the primary key of " +
						linkId.toString());
					throw new NoSuchLinkException(linkId.toString());
				}

				blogsLink = BlogsLinkHBMUtil.model(blogsLinkHBM);
			}

			return blogsLink;
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
				list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC").append(", ");
				query.append("url ASC");
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
					BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
					list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)sr.get(0);
						list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));

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

	public com.liferay.portlet.blogs.model.BlogsLink findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchLinkException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchLinkException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsLink)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsLink findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchLinkException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchLinkException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsLink)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsLink[] findByCompanyId_PrevAndNext(
		String linkId, String companyId, OrderByComparator obc)
		throws NoSuchLinkException, SystemException {
		com.liferay.portlet.blogs.model.BlogsLink blogsLink = findByPrimaryKey(linkId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC").append(", ");
				query.append("url ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.blogs.model.BlogsLink[] array = new com.liferay.portlet.blogs.model.BlogsLink[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)sr.get(0);

					if (blogsLinkHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsLink curBlogsLink = BlogsLinkHBMUtil.model(blogsLinkHBM);
					int value = obc.compare(blogsLink, curBlogsLink);

					if (value == 0) {
						if (!blogsLink.equals(curBlogsLink)) {
							break;
						}

						array[1] = curBlogsLink;

						if (sr.previous()) {
							array[0] = BlogsLinkHBMUtil.model((BlogsLinkHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsLinkHBMUtil.model((BlogsLinkHBM)sr.get(
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
				list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC").append(", ");
				query.append("url ASC");
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
					BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
					list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)sr.get(0);
						list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));

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

	public com.liferay.portlet.blogs.model.BlogsLink findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchLinkException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchLinkException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsLink)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsLink findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchLinkException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchLinkException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsLink)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsLink[] findByUserId_PrevAndNext(
		String linkId, String userId, OrderByComparator obc)
		throws NoSuchLinkException, SystemException {
		com.liferay.portlet.blogs.model.BlogsLink blogsLink = findByPrimaryKey(linkId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC").append(", ");
				query.append("url ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.blogs.model.BlogsLink[] array = new com.liferay.portlet.blogs.model.BlogsLink[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)sr.get(0);

					if (blogsLinkHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsLink curBlogsLink = BlogsLinkHBMUtil.model(blogsLinkHBM);
					int value = obc.compare(blogsLink, curBlogsLink);

					if (value == 0) {
						if (!blogsLink.equals(curBlogsLink)) {
							break;
						}

						array[1] = curBlogsLink;

						if (sr.previous()) {
							array[0] = BlogsLinkHBMUtil.model((BlogsLinkHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsLinkHBMUtil.model((BlogsLinkHBM)sr.get(
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM ");
			query.append("ORDER BY ");
			query.append("name ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
				list.add(BlogsLinkHBMUtil.model(blogsLinkHBM));
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
				BlogsLinkPool.remove((String)blogsLinkHBM.getPrimaryKey());
				session.delete(blogsLinkHBM);
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC").append(", ");
			query.append("url ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsLinkHBM blogsLinkHBM = (BlogsLinkHBM)itr.next();
				BlogsLinkPool.remove((String)blogsLinkHBM.getPrimaryKey());
				session.delete(blogsLinkHBM);
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
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
				"FROM BlogsLink IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsLinkHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(BlogsLinkPersistence.class);
}
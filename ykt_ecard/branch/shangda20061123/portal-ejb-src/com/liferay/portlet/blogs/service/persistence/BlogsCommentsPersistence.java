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

import com.liferay.portlet.blogs.NoSuchCommentsException;

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
 * <a href="BlogsCommentsPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsCommentsPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsComments create(
		String commentsId) {
		return new com.liferay.portlet.blogs.model.BlogsComments(commentsId);
	}

	public com.liferay.portlet.blogs.model.BlogsComments remove(
		String commentsId) throws NoSuchCommentsException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)session.get(BlogsCommentsHBM.class,
					commentsId);

			if (blogsCommentsHBM == null) {
				_log.warn("No BlogsComments exists with the primary key of " +
					commentsId.toString());
				throw new NoSuchCommentsException(commentsId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsComments blogsComments = BlogsCommentsHBMUtil.model(blogsCommentsHBM);
			session.delete(blogsCommentsHBM);
			session.flush();
			BlogsCommentsPool.remove(commentsId);

			return blogsComments;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments update(
		com.liferay.portlet.blogs.model.BlogsComments blogsComments)
		throws SystemException {
		Session session = null;

		try {
			if (blogsComments.isNew() || blogsComments.isModified()) {
				session = openSession();

				if (blogsComments.isNew()) {
					BlogsCommentsHBM blogsCommentsHBM = new BlogsCommentsHBM(blogsComments.getCommentsId(),
							blogsComments.getCompanyId(),
							blogsComments.getUserId(),
							blogsComments.getUserName(),
							blogsComments.getCreateDate(),
							blogsComments.getModifiedDate(),
							blogsComments.getEntryId(),
							blogsComments.getContent());
					session.save(blogsCommentsHBM);
					session.flush();
				}
				else {
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)session.get(BlogsCommentsHBM.class,
							blogsComments.getPrimaryKey());

					if (blogsCommentsHBM != null) {
						blogsCommentsHBM.setCompanyId(blogsComments.getCompanyId());
						blogsCommentsHBM.setUserId(blogsComments.getUserId());
						blogsCommentsHBM.setUserName(blogsComments.getUserName());
						blogsCommentsHBM.setCreateDate(blogsComments.getCreateDate());
						blogsCommentsHBM.setModifiedDate(blogsComments.getModifiedDate());
						blogsCommentsHBM.setEntryId(blogsComments.getEntryId());
						blogsCommentsHBM.setContent(blogsComments.getContent());
						session.flush();
					}
					else {
						blogsCommentsHBM = new BlogsCommentsHBM(blogsComments.getCommentsId(),
								blogsComments.getCompanyId(),
								blogsComments.getUserId(),
								blogsComments.getUserName(),
								blogsComments.getCreateDate(),
								blogsComments.getModifiedDate(),
								blogsComments.getEntryId(),
								blogsComments.getContent());
						session.save(blogsCommentsHBM);
						session.flush();
					}
				}

				blogsComments.setNew(false);
				blogsComments.setModified(false);
				blogsComments.protect();
				BlogsCommentsPool.put(blogsComments.getPrimaryKey(),
					blogsComments);
			}

			return blogsComments;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments findByPrimaryKey(
		String commentsId) throws NoSuchCommentsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsComments blogsComments = BlogsCommentsPool.get(commentsId);
		Session session = null;

		try {
			if (blogsComments == null) {
				session = openSession();

				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)session.get(BlogsCommentsHBM.class,
						commentsId);

				if (blogsCommentsHBM == null) {
					_log.warn(
						"No BlogsComments exists with the primary key of " +
						commentsId.toString());
					throw new NoSuchCommentsException(commentsId.toString());
				}

				blogsComments = BlogsCommentsHBMUtil.model(blogsCommentsHBM);
			}

			return blogsComments;
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("commentsId ASC").append(", ");
				query.append("createDate ASC");
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
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
					list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)sr.get(0);
						list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsComments findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCommentsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsComments)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCommentsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsComments)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments[] findByCompanyId_PrevAndNext(
		String commentsId, String companyId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsComments blogsComments = findByPrimaryKey(commentsId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("commentsId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.blogs.model.BlogsComments[] array = new com.liferay.portlet.blogs.model.BlogsComments[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)sr.get(0);

					if (blogsCommentsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsComments curBlogsComments =
						BlogsCommentsHBMUtil.model(blogsCommentsHBM);
					int value = obc.compare(blogsComments, curBlogsComments);

					if (value == 0) {
						if (!blogsComments.equals(curBlogsComments)) {
							break;
						}

						array[1] = curBlogsComments;

						if (sr.previous()) {
							array[0] = BlogsCommentsHBMUtil.model((BlogsCommentsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsCommentsHBMUtil.model((BlogsCommentsHBM)sr.get(
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("commentsId ASC").append(", ");
				query.append("createDate ASC");
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
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
					list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)sr.get(0);
						list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsComments findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCommentsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsComments)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCommentsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsComments)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments[] findByUserId_PrevAndNext(
		String commentsId, String userId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsComments blogsComments = findByPrimaryKey(commentsId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("commentsId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.blogs.model.BlogsComments[] array = new com.liferay.portlet.blogs.model.BlogsComments[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)sr.get(0);

					if (blogsCommentsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsComments curBlogsComments =
						BlogsCommentsHBMUtil.model(blogsCommentsHBM);
					int value = obc.compare(blogsComments, curBlogsComments);

					if (value == 0) {
						if (!blogsComments.equals(curBlogsComments)) {
							break;
						}

						array[1] = curBlogsComments;

						if (sr.previous()) {
							array[0] = BlogsCommentsHBMUtil.model((BlogsCommentsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsCommentsHBMUtil.model((BlogsCommentsHBM)sr.get(
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

	public List findByEntryId(String entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("commentsId ASC").append(", ");
				query.append("createDate ASC");
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
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
					list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)sr.get(0);
						list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsComments findByEntryId_First(
		String entryId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		List list = findByEntryId(entryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCommentsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsComments)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments findByEntryId_Last(
		String entryId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		int count = countByEntryId(entryId);
		List list = findByEntryId(entryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCommentsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsComments)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsComments[] findByEntryId_PrevAndNext(
		String commentsId, String entryId, OrderByComparator obc)
		throws NoSuchCommentsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsComments blogsComments = findByPrimaryKey(commentsId);
		int count = countByEntryId(entryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("commentsId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			com.liferay.portlet.blogs.model.BlogsComments[] array = new com.liferay.portlet.blogs.model.BlogsComments[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)sr.get(0);

					if (blogsCommentsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsComments curBlogsComments =
						BlogsCommentsHBMUtil.model(blogsCommentsHBM);
					int value = obc.compare(blogsComments, curBlogsComments);

					if (value == 0) {
						if (!blogsComments.equals(curBlogsComments)) {
							break;
						}

						array[1] = curBlogsComments;

						if (sr.previous()) {
							array[0] = BlogsCommentsHBMUtil.model((BlogsCommentsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsCommentsHBMUtil.model((BlogsCommentsHBM)sr.get(
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				list.add(BlogsCommentsHBMUtil.model(blogsCommentsHBM));
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				BlogsCommentsPool.remove((String)blogsCommentsHBM.getPrimaryKey());
				session.delete(blogsCommentsHBM);
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				BlogsCommentsPool.remove((String)blogsCommentsHBM.getPrimaryKey());
				session.delete(blogsCommentsHBM);
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

	public void removeByEntryId(String entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("commentsId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsCommentsHBM blogsCommentsHBM = (BlogsCommentsHBM)itr.next();
				BlogsCommentsPool.remove((String)blogsCommentsHBM.getPrimaryKey());
				session.delete(blogsCommentsHBM);
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
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
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
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

	public int countByEntryId(String entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsComments IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCommentsHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(BlogsCommentsPersistence.class);
}
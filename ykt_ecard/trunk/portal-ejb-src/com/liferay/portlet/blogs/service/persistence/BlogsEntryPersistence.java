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

import com.liferay.portlet.blogs.NoSuchEntryException;

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
 * <a href="BlogsEntryPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsEntry create(String entryId) {
		return new com.liferay.portlet.blogs.model.BlogsEntry(entryId);
	}

	public com.liferay.portlet.blogs.model.BlogsEntry remove(String entryId)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)session.get(BlogsEntryHBM.class,
					entryId);

			if (blogsEntryHBM == null) {
				_log.warn("No BlogsEntry exists with the primary key of " +
					entryId.toString());
				throw new NoSuchEntryException(entryId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
			session.delete(blogsEntryHBM);
			session.flush();
			BlogsEntryPool.remove(entryId);

			return blogsEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry update(
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry)
		throws SystemException {
		Session session = null;

		try {
			if (blogsEntry.isNew() || blogsEntry.isModified()) {
				session = openSession();

				if (blogsEntry.isNew()) {
					BlogsEntryHBM blogsEntryHBM = new BlogsEntryHBM(blogsEntry.getEntryId(),
							blogsEntry.getCompanyId(), blogsEntry.getUserId(),
							blogsEntry.getCreateDate(),
							blogsEntry.getModifiedDate(),
							blogsEntry.getCategoryId(), blogsEntry.getTitle(),
							blogsEntry.getContent(),
							blogsEntry.getDisplayDate(),
							blogsEntry.getSharing(),
							blogsEntry.getCommentable(),
							blogsEntry.getPropsCount(),
							blogsEntry.getCommentsCount());
					session.save(blogsEntryHBM);
					session.flush();
				}
				else {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)session.get(BlogsEntryHBM.class,
							blogsEntry.getPrimaryKey());

					if (blogsEntryHBM != null) {
						blogsEntryHBM.setCompanyId(blogsEntry.getCompanyId());
						blogsEntryHBM.setUserId(blogsEntry.getUserId());
						blogsEntryHBM.setCreateDate(blogsEntry.getCreateDate());
						blogsEntryHBM.setModifiedDate(blogsEntry.getModifiedDate());
						blogsEntryHBM.setCategoryId(blogsEntry.getCategoryId());
						blogsEntryHBM.setTitle(blogsEntry.getTitle());
						blogsEntryHBM.setContent(blogsEntry.getContent());
						blogsEntryHBM.setDisplayDate(blogsEntry.getDisplayDate());
						blogsEntryHBM.setSharing(blogsEntry.getSharing());
						blogsEntryHBM.setCommentable(blogsEntry.getCommentable());
						blogsEntryHBM.setPropsCount(blogsEntry.getPropsCount());
						blogsEntryHBM.setCommentsCount(blogsEntry.getCommentsCount());
						session.flush();
					}
					else {
						blogsEntryHBM = new BlogsEntryHBM(blogsEntry.getEntryId(),
								blogsEntry.getCompanyId(),
								blogsEntry.getUserId(),
								blogsEntry.getCreateDate(),
								blogsEntry.getModifiedDate(),
								blogsEntry.getCategoryId(),
								blogsEntry.getTitle(), blogsEntry.getContent(),
								blogsEntry.getDisplayDate(),
								blogsEntry.getSharing(),
								blogsEntry.getCommentable(),
								blogsEntry.getPropsCount(),
								blogsEntry.getCommentsCount());
						session.save(blogsEntryHBM);
						session.flush();
					}
				}

				blogsEntry.setNew(false);
				blogsEntry.setModified(false);
				blogsEntry.protect();
				BlogsEntryPool.put(blogsEntry.getPrimaryKey(), blogsEntry);
			}

			return blogsEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByPrimaryKey(
		String entryId) throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = BlogsEntryPool.get(entryId);
		Session session = null;

		try {
			if (blogsEntry == null) {
				session = openSession();

				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)session.get(BlogsEntryHBM.class,
						entryId);

				if (blogsEntryHBM == null) {
					_log.warn("No BlogsEntry exists with the primary key of " +
						entryId.toString());
					throw new NoSuchEntryException(entryId.toString());
				}

				blogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
			}

			return blogsEntry;
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
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
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
					list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);
						list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsEntry findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry[] findByCompanyId_PrevAndNext(
		String entryId, String companyId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = findByPrimaryKey(entryId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.blogs.model.BlogsEntry[] array = new com.liferay.portlet.blogs.model.BlogsEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);

					if (blogsEntryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsEntry curBlogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
					int value = obc.compare(blogsEntry, curBlogsEntry);

					if (value == 0) {
						if (!blogsEntry.equals(curBlogsEntry)) {
							break;
						}

						array[1] = curBlogsEntry;

						if (sr.previous()) {
							array[0] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
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
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
					list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);
						list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsEntry findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry[] findByUserId_PrevAndNext(
		String entryId, String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = findByPrimaryKey(entryId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.blogs.model.BlogsEntry[] array = new com.liferay.portlet.blogs.model.BlogsEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);

					if (blogsEntryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsEntry curBlogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
					int value = obc.compare(blogsEntry, curBlogsEntry);

					if (value == 0) {
						if (!blogsEntry.equals(curBlogsEntry)) {
							break;
						}

						array[1] = curBlogsEntry;

						if (sr.previous()) {
							array[0] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
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

	public List findByCategoryId(String categoryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("categoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, categoryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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

	public List findByCategoryId(String categoryId, int begin, int end)
		throws SystemException {
		return findByCategoryId(categoryId, begin, end, null);
	}

	public List findByCategoryId(String categoryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("categoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, categoryId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
					list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);
						list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsEntry findByCategoryId_First(
		String categoryId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByCategoryId(categoryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByCategoryId_Last(
		String categoryId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByCategoryId(categoryId);
		List list = findByCategoryId(categoryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry[] findByCategoryId_PrevAndNext(
		String entryId, String categoryId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = findByPrimaryKey(entryId);
		int count = countByCategoryId(categoryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("categoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, categoryId);

			com.liferay.portlet.blogs.model.BlogsEntry[] array = new com.liferay.portlet.blogs.model.BlogsEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);

					if (blogsEntryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsEntry curBlogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
					int value = obc.compare(blogsEntry, curBlogsEntry);

					if (value == 0) {
						if (!blogsEntry.equals(curBlogsEntry)) {
							break;
						}

						array[1] = curBlogsEntry;

						if (sr.previous()) {
							array[0] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
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

	public List findByU_C(String userId, String categoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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

	public List findByU_C(String userId, String categoryId, int begin, int end)
		throws SystemException {
		return findByU_C(userId, categoryId, begin, end, null);
	}

	public List findByU_C(String userId, String categoryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
					list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);
						list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsEntry findByU_C_First(
		String userId, String categoryId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByU_C(userId, categoryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByU_C_Last(
		String userId, String categoryId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByU_C(userId, categoryId);
		List list = findByU_C(userId, categoryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry[] findByU_C_PrevAndNext(
		String entryId, String userId, String categoryId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = findByPrimaryKey(entryId);
		int count = countByU_C(userId, categoryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);

			com.liferay.portlet.blogs.model.BlogsEntry[] array = new com.liferay.portlet.blogs.model.BlogsEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);

					if (blogsEntryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsEntry curBlogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
					int value = obc.compare(blogsEntry, curBlogsEntry);

					if (value == 0) {
						if (!blogsEntry.equals(curBlogsEntry)) {
							break;
						}

						array[1] = curBlogsEntry;

						if (sr.previous()) {
							array[0] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
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

	public List findByU_S(String userId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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

	public List findByU_S(String userId, boolean sharing, int begin, int end)
		throws SystemException {
		return findByU_S(userId, sharing, begin, end, null);
	}

	public List findByU_S(String userId, boolean sharing, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
					list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);
						list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsEntry findByU_S_First(
		String userId, boolean sharing, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByU_S(userId, sharing, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByU_S_Last(
		String userId, boolean sharing, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByU_S(userId, sharing);
		List list = findByU_S(userId, sharing, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry[] findByU_S_PrevAndNext(
		String entryId, String userId, boolean sharing, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = findByPrimaryKey(entryId);
		int count = countByU_S(userId, sharing);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			com.liferay.portlet.blogs.model.BlogsEntry[] array = new com.liferay.portlet.blogs.model.BlogsEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);

					if (blogsEntryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsEntry curBlogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
					int value = obc.compare(blogsEntry, curBlogsEntry);

					if (value == 0) {
						if (!blogsEntry.equals(curBlogsEntry)) {
							break;
						}

						array[1] = curBlogsEntry;

						if (sr.previous()) {
							array[0] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
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

	public List findByU_C_S(String userId, String categoryId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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

	public List findByU_C_S(String userId, String categoryId, boolean sharing,
		int begin, int end) throws SystemException {
		return findByU_C_S(userId, categoryId, sharing, begin, end, null);
	}

	public List findByU_C_S(String userId, String categoryId, boolean sharing,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);
			q.setBoolean(queryPos++, sharing);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
					list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);
						list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsEntry findByU_C_S_First(
		String userId, String categoryId, boolean sharing, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByU_C_S(userId, categoryId, sharing, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry findByU_C_S_Last(
		String userId, String categoryId, boolean sharing, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByU_C_S(userId, categoryId, sharing);
		List list = findByU_C_S(userId, categoryId, sharing, count - 1, count,
				obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsEntry)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsEntry[] findByU_C_S_PrevAndNext(
		String entryId, String userId, String categoryId, boolean sharing,
		OrderByComparator obc) throws NoSuchEntryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = findByPrimaryKey(entryId);
		int count = countByU_C_S(userId, categoryId, sharing);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("displayDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);
			q.setBoolean(queryPos++, sharing);

			com.liferay.portlet.blogs.model.BlogsEntry[] array = new com.liferay.portlet.blogs.model.BlogsEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)sr.get(0);

					if (blogsEntryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsEntry curBlogsEntry = BlogsEntryHBMUtil.model(blogsEntryHBM);
					int value = obc.compare(blogsEntry, curBlogsEntry);

					if (value == 0) {
						if (!blogsEntry.equals(curBlogsEntry)) {
							break;
						}

						array[1] = curBlogsEntry;

						if (sr.previous()) {
							array[0] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsEntryHBMUtil.model((BlogsEntryHBM)sr.get(
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				list.add(BlogsEntryHBMUtil.model(blogsEntryHBM));
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				BlogsEntryPool.remove((String)blogsEntryHBM.getPrimaryKey());
				session.delete(blogsEntryHBM);
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				BlogsEntryPool.remove((String)blogsEntryHBM.getPrimaryKey());
				session.delete(blogsEntryHBM);
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

	public void removeByCategoryId(String categoryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("categoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, categoryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				BlogsEntryPool.remove((String)blogsEntryHBM.getPrimaryKey());
				session.delete(blogsEntryHBM);
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

	public void removeByU_C(String userId, String categoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				BlogsEntryPool.remove((String)blogsEntryHBM.getPrimaryKey());
				session.delete(blogsEntryHBM);
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

	public void removeByU_S(String userId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				BlogsEntryPool.remove((String)blogsEntryHBM.getPrimaryKey());
				session.delete(blogsEntryHBM);
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

	public void removeByU_C_S(String userId, String categoryId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("displayDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsEntryHBM blogsEntryHBM = (BlogsEntryHBM)itr.next();
				BlogsEntryPool.remove((String)blogsEntryHBM.getPrimaryKey());
				session.delete(blogsEntryHBM);
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
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
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
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

	public int countByCategoryId(String categoryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("categoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, categoryId);

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

	public int countByU_C(String userId, String categoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);

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

	public int countByU_S(String userId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

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

	public int countByU_C_S(String userId, String categoryId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsEntry IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsEntryHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, categoryId);
			q.setBoolean(queryPos++, sharing);

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

	private static final Log _log = LogFactory.getLog(BlogsEntryPersistence.class);
}
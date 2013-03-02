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

import com.liferay.portlet.blogs.NoSuchCategoryException;

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
 * <a href="BlogsCategoryPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsCategoryPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsCategory create(
		String categoryId) {
		return new com.liferay.portlet.blogs.model.BlogsCategory(categoryId);
	}

	public com.liferay.portlet.blogs.model.BlogsCategory remove(
		String categoryId) throws NoSuchCategoryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)session.get(BlogsCategoryHBM.class,
					categoryId);

			if (blogsCategoryHBM == null) {
				_log.warn("No BlogsCategory exists with the primary key of " +
					categoryId.toString());
				throw new NoSuchCategoryException(categoryId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsCategory blogsCategory = BlogsCategoryHBMUtil.model(blogsCategoryHBM);
			session.delete(blogsCategoryHBM);
			session.flush();
			BlogsCategoryPool.remove(categoryId);

			return blogsCategory;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsCategory update(
		com.liferay.portlet.blogs.model.BlogsCategory blogsCategory)
		throws SystemException {
		Session session = null;

		try {
			if (blogsCategory.isNew() || blogsCategory.isModified()) {
				session = openSession();

				if (blogsCategory.isNew()) {
					BlogsCategoryHBM blogsCategoryHBM = new BlogsCategoryHBM(blogsCategory.getCategoryId(),
							blogsCategory.getCompanyId(),
							blogsCategory.getUserId(),
							blogsCategory.getCreateDate(),
							blogsCategory.getModifiedDate(),
							blogsCategory.getName());
					session.save(blogsCategoryHBM);
					session.flush();
				}
				else {
					BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)session.get(BlogsCategoryHBM.class,
							blogsCategory.getPrimaryKey());

					if (blogsCategoryHBM != null) {
						blogsCategoryHBM.setCompanyId(blogsCategory.getCompanyId());
						blogsCategoryHBM.setUserId(blogsCategory.getUserId());
						blogsCategoryHBM.setCreateDate(blogsCategory.getCreateDate());
						blogsCategoryHBM.setModifiedDate(blogsCategory.getModifiedDate());
						blogsCategoryHBM.setName(blogsCategory.getName());
						session.flush();
					}
					else {
						blogsCategoryHBM = new BlogsCategoryHBM(blogsCategory.getCategoryId(),
								blogsCategory.getCompanyId(),
								blogsCategory.getUserId(),
								blogsCategory.getCreateDate(),
								blogsCategory.getModifiedDate(),
								blogsCategory.getName());
						session.save(blogsCategoryHBM);
						session.flush();
					}
				}

				blogsCategory.setNew(false);
				blogsCategory.setModified(false);
				blogsCategory.protect();
				BlogsCategoryPool.put(blogsCategory.getPrimaryKey(),
					blogsCategory);
			}

			return blogsCategory;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsCategory findByPrimaryKey(
		String categoryId) throws NoSuchCategoryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsCategory blogsCategory = BlogsCategoryPool.get(categoryId);
		Session session = null;

		try {
			if (blogsCategory == null) {
				session = openSession();

				BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)session.get(BlogsCategoryHBM.class,
						categoryId);

				if (blogsCategoryHBM == null) {
					_log.warn(
						"No BlogsCategory exists with the primary key of " +
						categoryId.toString());
					throw new NoSuchCategoryException(categoryId.toString());
				}

				blogsCategory = BlogsCategoryHBMUtil.model(blogsCategoryHBM);
			}

			return blogsCategory;
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
				list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
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
					BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
					list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)sr.get(0);
						list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsCategory findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsCategory)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsCategory findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsCategory)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsCategory[] findByCompanyId_PrevAndNext(
		String categoryId, String companyId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsCategory blogsCategory = findByPrimaryKey(categoryId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.blogs.model.BlogsCategory[] array = new com.liferay.portlet.blogs.model.BlogsCategory[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)sr.get(0);

					if (blogsCategoryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsCategory curBlogsCategory =
						BlogsCategoryHBMUtil.model(blogsCategoryHBM);
					int value = obc.compare(blogsCategory, curBlogsCategory);

					if (value == 0) {
						if (!blogsCategory.equals(curBlogsCategory)) {
							break;
						}

						array[1] = curBlogsCategory;

						if (sr.previous()) {
							array[0] = BlogsCategoryHBMUtil.model((BlogsCategoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsCategoryHBMUtil.model((BlogsCategoryHBM)sr.get(
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
				list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
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
					BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
					list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)sr.get(0);
						list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));

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

	public com.liferay.portlet.blogs.model.BlogsCategory findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsCategory)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsCategory findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsCategory)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsCategory[] findByUserId_PrevAndNext(
		String categoryId, String userId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		com.liferay.portlet.blogs.model.BlogsCategory blogsCategory = findByPrimaryKey(categoryId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.blogs.model.BlogsCategory[] array = new com.liferay.portlet.blogs.model.BlogsCategory[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)sr.get(0);

					if (blogsCategoryHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsCategory curBlogsCategory =
						BlogsCategoryHBMUtil.model(blogsCategoryHBM);
					int value = obc.compare(blogsCategory, curBlogsCategory);

					if (value == 0) {
						if (!blogsCategory.equals(curBlogsCategory)) {
							break;
						}

						array[1] = curBlogsCategory;

						if (sr.previous()) {
							array[0] = BlogsCategoryHBMUtil.model((BlogsCategoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsCategoryHBMUtil.model((BlogsCategoryHBM)sr.get(
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
				list.add(BlogsCategoryHBMUtil.model(blogsCategoryHBM));
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
				BlogsCategoryPool.remove((String)blogsCategoryHBM.getPrimaryKey());
				session.delete(blogsCategoryHBM);
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsCategoryHBM blogsCategoryHBM = (BlogsCategoryHBM)itr.next();
				BlogsCategoryPool.remove((String)blogsCategoryHBM.getPrimaryKey());
				session.delete(blogsCategoryHBM);
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
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
				"FROM BlogsCategory IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsCategoryHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(BlogsCategoryPersistence.class);
}
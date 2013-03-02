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

import com.liferay.portlet.blogs.NoSuchPropsException;

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
 * <a href="BlogsPropsPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsPropsPersistence extends BasePersistence {
	public com.liferay.portlet.blogs.model.BlogsProps create(String propsId) {
		return new com.liferay.portlet.blogs.model.BlogsProps(propsId);
	}

	public com.liferay.portlet.blogs.model.BlogsProps remove(String propsId)
		throws NoSuchPropsException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)session.get(BlogsPropsHBM.class,
					propsId);

			if (blogsPropsHBM == null) {
				_log.warn("No BlogsProps exists with the primary key of " +
					propsId.toString());
				throw new NoSuchPropsException(propsId.toString());
			}

			com.liferay.portlet.blogs.model.BlogsProps blogsProps = BlogsPropsHBMUtil.model(blogsPropsHBM);
			session.delete(blogsPropsHBM);
			session.flush();
			BlogsPropsPool.remove(propsId);

			return blogsProps;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps update(
		com.liferay.portlet.blogs.model.BlogsProps blogsProps)
		throws SystemException {
		Session session = null;

		try {
			if (blogsProps.isNew() || blogsProps.isModified()) {
				session = openSession();

				if (blogsProps.isNew()) {
					BlogsPropsHBM blogsPropsHBM = new BlogsPropsHBM(blogsProps.getPropsId(),
							blogsProps.getCompanyId(), blogsProps.getUserId(),
							blogsProps.getUserName(),
							blogsProps.getCreateDate(),
							blogsProps.getModifiedDate(),
							blogsProps.getEntryId(), blogsProps.getQuantity());
					session.save(blogsPropsHBM);
					session.flush();
				}
				else {
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)session.get(BlogsPropsHBM.class,
							blogsProps.getPrimaryKey());

					if (blogsPropsHBM != null) {
						blogsPropsHBM.setCompanyId(blogsProps.getCompanyId());
						blogsPropsHBM.setUserId(blogsProps.getUserId());
						blogsPropsHBM.setUserName(blogsProps.getUserName());
						blogsPropsHBM.setCreateDate(blogsProps.getCreateDate());
						blogsPropsHBM.setModifiedDate(blogsProps.getModifiedDate());
						blogsPropsHBM.setEntryId(blogsProps.getEntryId());
						blogsPropsHBM.setQuantity(blogsProps.getQuantity());
						session.flush();
					}
					else {
						blogsPropsHBM = new BlogsPropsHBM(blogsProps.getPropsId(),
								blogsProps.getCompanyId(),
								blogsProps.getUserId(),
								blogsProps.getUserName(),
								blogsProps.getCreateDate(),
								blogsProps.getModifiedDate(),
								blogsProps.getEntryId(),
								blogsProps.getQuantity());
						session.save(blogsPropsHBM);
						session.flush();
					}
				}

				blogsProps.setNew(false);
				blogsProps.setModified(false);
				blogsProps.protect();
				BlogsPropsPool.put(blogsProps.getPrimaryKey(), blogsProps);
			}

			return blogsProps;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps findByPrimaryKey(
		String propsId) throws NoSuchPropsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsProps blogsProps = BlogsPropsPool.get(propsId);
		Session session = null;

		try {
			if (blogsProps == null) {
				session = openSession();

				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)session.get(BlogsPropsHBM.class,
						propsId);

				if (blogsPropsHBM == null) {
					_log.warn("No BlogsProps exists with the primary key of " +
						propsId.toString());
					throw new NoSuchPropsException(propsId.toString());
				}

				blogsProps = BlogsPropsHBMUtil.model(blogsPropsHBM);
			}

			return blogsProps;
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
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
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
					list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);
						list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsProps findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps[] findByCompanyId_PrevAndNext(
		String propsId, String companyId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsProps blogsProps = findByPrimaryKey(propsId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.blogs.model.BlogsProps[] array = new com.liferay.portlet.blogs.model.BlogsProps[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);

					if (blogsPropsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsProps curBlogsProps = BlogsPropsHBMUtil.model(blogsPropsHBM);
					int value = obc.compare(blogsProps, curBlogsProps);

					if (value == 0) {
						if (!blogsProps.equals(curBlogsProps)) {
							break;
						}

						array[1] = curBlogsProps;

						if (sr.previous()) {
							array[0] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
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
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
					list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);
						list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsProps findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps[] findByUserId_PrevAndNext(
		String propsId, String userId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsProps blogsProps = findByPrimaryKey(propsId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.blogs.model.BlogsProps[] array = new com.liferay.portlet.blogs.model.BlogsProps[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);

					if (blogsPropsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsProps curBlogsProps = BlogsPropsHBMUtil.model(blogsPropsHBM);
					int value = obc.compare(blogsProps, curBlogsProps);

					if (value == 0) {
						if (!blogsProps.equals(curBlogsProps)) {
							break;
						}

						array[1] = curBlogsProps;

						if (sr.previous()) {
							array[0] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
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
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
					list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);
						list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsProps findByEntryId_First(
		String entryId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		List list = findByEntryId(entryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps findByEntryId_Last(
		String entryId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		int count = countByEntryId(entryId);
		List list = findByEntryId(entryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps[] findByEntryId_PrevAndNext(
		String propsId, String entryId, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsProps blogsProps = findByPrimaryKey(propsId);
		int count = countByEntryId(entryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			com.liferay.portlet.blogs.model.BlogsProps[] array = new com.liferay.portlet.blogs.model.BlogsProps[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);

					if (blogsPropsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsProps curBlogsProps = BlogsPropsHBMUtil.model(blogsPropsHBM);
					int value = obc.compare(blogsProps, curBlogsProps);

					if (value == 0) {
						if (!blogsProps.equals(curBlogsProps)) {
							break;
						}

						array[1] = curBlogsProps;

						if (sr.previous()) {
							array[0] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
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

	public com.liferay.portlet.blogs.model.BlogsProps findByU_E(String userId,
		String entryId) throws NoSuchPropsException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchPropsException();
			}

			BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();

			return BlogsPropsHBMUtil.model(blogsPropsHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByE_Q(String entryId, int quantity)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("quantity = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setInteger(queryPos++, quantity);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
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

	public List findByE_Q(String entryId, int quantity, int begin, int end)
		throws SystemException {
		return findByE_Q(entryId, quantity, begin, end, null);
	}

	public List findByE_Q(String entryId, int quantity, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("quantity = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setInteger(queryPos++, quantity);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
					list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);
						list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));

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

	public com.liferay.portlet.blogs.model.BlogsProps findByE_Q_First(
		String entryId, int quantity, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		List list = findByE_Q(entryId, quantity, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps findByE_Q_Last(
		String entryId, int quantity, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		int count = countByE_Q(entryId, quantity);
		List list = findByE_Q(entryId, quantity, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPropsException();
		}
		else {
			return (com.liferay.portlet.blogs.model.BlogsProps)list.get(0);
		}
	}

	public com.liferay.portlet.blogs.model.BlogsProps[] findByE_Q_PrevAndNext(
		String propsId, String entryId, int quantity, OrderByComparator obc)
		throws NoSuchPropsException, SystemException {
		com.liferay.portlet.blogs.model.BlogsProps blogsProps = findByPrimaryKey(propsId);
		int count = countByE_Q(entryId, quantity);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("quantity = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("entryId ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setInteger(queryPos++, quantity);

			com.liferay.portlet.blogs.model.BlogsProps[] array = new com.liferay.portlet.blogs.model.BlogsProps[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)sr.get(0);

					if (blogsPropsHBM == null) {
						break;
					}

					com.liferay.portlet.blogs.model.BlogsProps curBlogsProps = BlogsPropsHBMUtil.model(blogsPropsHBM);
					int value = obc.compare(blogsProps, curBlogsProps);

					if (value == 0) {
						if (!blogsProps.equals(curBlogsProps)) {
							break;
						}

						array[1] = curBlogsProps;

						if (sr.previous()) {
							array[0] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BlogsPropsHBMUtil.model((BlogsPropsHBM)sr.get(
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				list.add(BlogsPropsHBMUtil.model(blogsPropsHBM));
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				BlogsPropsPool.remove((String)blogsPropsHBM.getPrimaryKey());
				session.delete(blogsPropsHBM);
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				BlogsPropsPool.remove((String)blogsPropsHBM.getPrimaryKey());
				session.delete(blogsPropsHBM);
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				BlogsPropsPool.remove((String)blogsPropsHBM.getPrimaryKey());
				session.delete(blogsPropsHBM);
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

	public void removeByU_E(String userId, String entryId)
		throws NoSuchPropsException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("entryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, entryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				BlogsPropsPool.remove((String)blogsPropsHBM.getPrimaryKey());
				session.delete(blogsPropsHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchPropsException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByE_Q(String entryId, int quantity)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("quantity = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("entryId ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setInteger(queryPos++, quantity);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BlogsPropsHBM blogsPropsHBM = (BlogsPropsHBM)itr.next();
				BlogsPropsPool.remove((String)blogsPropsHBM.getPrimaryKey());
				session.delete(blogsPropsHBM);
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
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
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
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

	public int countByU_E(String userId, String entryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("entryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
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

	public int countByE_Q(String entryId, int quantity)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BlogsProps IN CLASS com.liferay.portlet.blogs.service.persistence.BlogsPropsHBM WHERE ");
			query.append("entryId = ?");
			query.append(" AND ");
			query.append("quantity = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, entryId);
			q.setInteger(queryPos++, quantity);

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

	private static final Log _log = LogFactory.getLog(BlogsPropsPersistence.class);
}
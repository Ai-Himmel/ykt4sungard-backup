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

package com.liferay.portlet.bookmarks.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.bookmarks.NoSuchEntryException;

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
 * <a href="BookmarksEntryPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksEntryPersistence extends BasePersistence {
	public com.liferay.portlet.bookmarks.model.BookmarksEntry create(
		String entryId) {
		return new com.liferay.portlet.bookmarks.model.BookmarksEntry(entryId);
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry remove(
		String entryId) throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)session.get(BookmarksEntryHBM.class,
					entryId);

			if (bookmarksEntryHBM == null) {
				_log.warn("No BookmarksEntry exists with the primary key of " +
					entryId.toString());
				throw new NoSuchEntryException(entryId.toString());
			}

			com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = BookmarksEntryHBMUtil.model(bookmarksEntryHBM);
			session.delete(bookmarksEntryHBM);
			session.flush();
			BookmarksEntryPool.remove(entryId);

			return bookmarksEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry update(
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry)
		throws SystemException {
		Session session = null;

		try {
			if (bookmarksEntry.isNew() || bookmarksEntry.isModified()) {
				session = openSession();

				if (bookmarksEntry.isNew()) {
					BookmarksEntryHBM bookmarksEntryHBM = new BookmarksEntryHBM(bookmarksEntry.getEntryId(),
							bookmarksEntry.getGroupId(),
							bookmarksEntry.getCompanyId(),
							bookmarksEntry.getUserId(),
							bookmarksEntry.getCreateDate(),
							bookmarksEntry.getModifiedDate(),
							bookmarksEntry.getFolderId(),
							bookmarksEntry.getName(), bookmarksEntry.getUrl(),
							bookmarksEntry.getComments(),
							bookmarksEntry.getVisits());
					session.save(bookmarksEntryHBM);
					session.flush();
				}
				else {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)session.get(BookmarksEntryHBM.class,
							bookmarksEntry.getPrimaryKey());

					if (bookmarksEntryHBM != null) {
						bookmarksEntryHBM.setGroupId(bookmarksEntry.getGroupId());
						bookmarksEntryHBM.setCompanyId(bookmarksEntry.getCompanyId());
						bookmarksEntryHBM.setUserId(bookmarksEntry.getUserId());
						bookmarksEntryHBM.setCreateDate(bookmarksEntry.getCreateDate());
						bookmarksEntryHBM.setModifiedDate(bookmarksEntry.getModifiedDate());
						bookmarksEntryHBM.setFolderId(bookmarksEntry.getFolderId());
						bookmarksEntryHBM.setName(bookmarksEntry.getName());
						bookmarksEntryHBM.setUrl(bookmarksEntry.getUrl());
						bookmarksEntryHBM.setComments(bookmarksEntry.getComments());
						bookmarksEntryHBM.setVisits(bookmarksEntry.getVisits());
						session.flush();
					}
					else {
						bookmarksEntryHBM = new BookmarksEntryHBM(bookmarksEntry.getEntryId(),
								bookmarksEntry.getGroupId(),
								bookmarksEntry.getCompanyId(),
								bookmarksEntry.getUserId(),
								bookmarksEntry.getCreateDate(),
								bookmarksEntry.getModifiedDate(),
								bookmarksEntry.getFolderId(),
								bookmarksEntry.getName(),
								bookmarksEntry.getUrl(),
								bookmarksEntry.getComments(),
								bookmarksEntry.getVisits());
						session.save(bookmarksEntryHBM);
						session.flush();
					}
				}

				bookmarksEntry.setNew(false);
				bookmarksEntry.setModified(false);
				bookmarksEntry.protect();
				BookmarksEntryPool.put(bookmarksEntry.getPrimaryKey(),
					bookmarksEntry);
			}

			return bookmarksEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByPrimaryKey(
		String entryId) throws NoSuchEntryException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = BookmarksEntryPool.get(entryId);
		Session session = null;

		try {
			if (bookmarksEntry == null) {
				session = openSession();

				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)session.get(BookmarksEntryHBM.class,
						entryId);

				if (bookmarksEntryHBM == null) {
					_log.warn(
						"No BookmarksEntry exists with the primary key of " +
						entryId.toString());
					throw new NoSuchEntryException(entryId.toString());
				}

				bookmarksEntry = BookmarksEntryHBMUtil.model(bookmarksEntryHBM);
			}

			return bookmarksEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
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

	public List findByGroupId(String groupId, int begin, int end)
		throws SystemException {
		return findByGroupId(groupId, begin, end, null);
	}

	public List findByGroupId(String groupId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
					list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);
						list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByGroupId_PrevAndNext(
		String entryId, String groupId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = findByPrimaryKey(entryId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.bookmarks.model.BookmarksEntry[] array = new com.liferay.portlet.bookmarks.model.BookmarksEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);

					if (bookmarksEntryHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksEntry curBookmarksEntry =
						BookmarksEntryHBMUtil.model(bookmarksEntryHBM);
					int value = obc.compare(bookmarksEntry, curBookmarksEntry);

					if (value == 0) {
						if (!bookmarksEntry.equals(curBookmarksEntry)) {
							break;
						}

						array[1] = curBookmarksEntry;

						if (sr.previous()) {
							array[0] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
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

	public List findByG_U(String groupId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
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

	public List findByG_U(String groupId, String userId, int begin, int end)
		throws SystemException {
		return findByG_U(groupId, userId, begin, end, null);
	}

	public List findByG_U(String groupId, String userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
					list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);
						list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_First(
		String groupId, String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByG_U(groupId, userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_Last(
		String groupId, String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByG_U(groupId, userId);
		List list = findByG_U(groupId, userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByG_U_PrevAndNext(
		String entryId, String groupId, String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = findByPrimaryKey(entryId);
		int count = countByG_U(groupId, userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			com.liferay.portlet.bookmarks.model.BookmarksEntry[] array = new com.liferay.portlet.bookmarks.model.BookmarksEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);

					if (bookmarksEntryHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksEntry curBookmarksEntry =
						BookmarksEntryHBMUtil.model(bookmarksEntryHBM);
					int value = obc.compare(bookmarksEntry, curBookmarksEntry);

					if (value == 0) {
						if (!bookmarksEntry.equals(curBookmarksEntry)) {
							break;
						}

						array[1] = curBookmarksEntry;

						if (sr.previous()) {
							array[0] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
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

	public List findByG_F(String groupId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, folderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
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

	public List findByG_F(String groupId, String folderId, int begin, int end)
		throws SystemException {
		return findByG_F(groupId, folderId, begin, end, null);
	}

	public List findByG_F(String groupId, String folderId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, folderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
					list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);
						list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_F_First(
		String groupId, String folderId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByG_F(groupId, folderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_F_Last(
		String groupId, String folderId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByG_F(groupId, folderId);
		List list = findByG_F(groupId, folderId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByG_F_PrevAndNext(
		String entryId, String groupId, String folderId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = findByPrimaryKey(entryId);
		int count = countByG_F(groupId, folderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, folderId);

			com.liferay.portlet.bookmarks.model.BookmarksEntry[] array = new com.liferay.portlet.bookmarks.model.BookmarksEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);

					if (bookmarksEntryHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksEntry curBookmarksEntry =
						BookmarksEntryHBMUtil.model(bookmarksEntryHBM);
					int value = obc.compare(bookmarksEntry, curBookmarksEntry);

					if (value == 0) {
						if (!bookmarksEntry.equals(curBookmarksEntry)) {
							break;
						}

						array[1] = curBookmarksEntry;

						if (sr.previous()) {
							array[0] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
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

	public List findByG_U_F(String groupId, String userId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, folderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
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

	public List findByG_U_F(String groupId, String userId, String folderId,
		int begin, int end) throws SystemException {
		return findByG_U_F(groupId, userId, folderId, begin, end, null);
	}

	public List findByG_U_F(String groupId, String userId, String folderId,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, folderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
					list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);
						list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_F_First(
		String groupId, String userId, String folderId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByG_U_F(groupId, userId, folderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_F_Last(
		String groupId, String userId, String folderId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByG_U_F(groupId, userId, folderId);
		List list = findByG_U_F(groupId, userId, folderId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksEntry)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByG_U_F_PrevAndNext(
		String entryId, String groupId, String userId, String folderId,
		OrderByComparator obc) throws NoSuchEntryException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = findByPrimaryKey(entryId);
		int count = countByG_U_F(groupId, userId, folderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("folderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, folderId);

			com.liferay.portlet.bookmarks.model.BookmarksEntry[] array = new com.liferay.portlet.bookmarks.model.BookmarksEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)sr.get(0);

					if (bookmarksEntryHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksEntry curBookmarksEntry =
						BookmarksEntryHBMUtil.model(bookmarksEntryHBM);
					int value = obc.compare(bookmarksEntry, curBookmarksEntry);

					if (value == 0) {
						if (!bookmarksEntry.equals(curBookmarksEntry)) {
							break;
						}

						array[1] = curBookmarksEntry;

						if (sr.previous()) {
							array[0] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksEntryHBMUtil.model((BookmarksEntryHBM)sr.get(
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
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				list.add(BookmarksEntryHBMUtil.model(bookmarksEntryHBM));
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

	public void removeByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				BookmarksEntryPool.remove((String)bookmarksEntryHBM.getPrimaryKey());
				session.delete(bookmarksEntryHBM);
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

	public void removeByG_U(String groupId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				BookmarksEntryPool.remove((String)bookmarksEntryHBM.getPrimaryKey());
				session.delete(bookmarksEntryHBM);
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

	public void removeByG_F(String groupId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, folderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				BookmarksEntryPool.remove((String)bookmarksEntryHBM.getPrimaryKey());
				session.delete(bookmarksEntryHBM);
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

	public void removeByG_U_F(String groupId, String userId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("folderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, folderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksEntryHBM bookmarksEntryHBM = (BookmarksEntryHBM)itr.next();
				BookmarksEntryPool.remove((String)bookmarksEntryHBM.getPrimaryKey());
				session.delete(bookmarksEntryHBM);
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

	public int countByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

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

	public int countByG_U(String groupId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
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

	public int countByG_F(String groupId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, folderId);

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

	public int countByG_U_F(String groupId, String userId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BookmarksEntry IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, folderId);

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

	private static final Log _log = LogFactory.getLog(BookmarksEntryPersistence.class);
}
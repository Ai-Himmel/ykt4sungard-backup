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

import com.liferay.portlet.bookmarks.NoSuchFolderException;

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
 * <a href="BookmarksFolderPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksFolderPersistence extends BasePersistence {
	public com.liferay.portlet.bookmarks.model.BookmarksFolder create(
		String folderId) {
		return new com.liferay.portlet.bookmarks.model.BookmarksFolder(folderId);
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder remove(
		String folderId) throws NoSuchFolderException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)session.get(BookmarksFolderHBM.class,
					folderId);

			if (bookmarksFolderHBM == null) {
				_log.warn("No BookmarksFolder exists with the primary key of " +
					folderId.toString());
				throw new NoSuchFolderException(folderId.toString());
			}

			com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = BookmarksFolderHBMUtil.model(bookmarksFolderHBM);
			session.delete(bookmarksFolderHBM);
			session.flush();
			BookmarksFolderPool.remove(folderId);

			return bookmarksFolder;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder update(
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder)
		throws SystemException {
		Session session = null;

		try {
			if (bookmarksFolder.isNew() || bookmarksFolder.isModified()) {
				session = openSession();

				if (bookmarksFolder.isNew()) {
					BookmarksFolderHBM bookmarksFolderHBM = new BookmarksFolderHBM(bookmarksFolder.getFolderId(),
							bookmarksFolder.getGroupId(),
							bookmarksFolder.getCompanyId(),
							bookmarksFolder.getUserId(),
							bookmarksFolder.getCreateDate(),
							bookmarksFolder.getModifiedDate(),
							bookmarksFolder.getParentFolderId(),
							bookmarksFolder.getName());
					session.save(bookmarksFolderHBM);
					session.flush();
				}
				else {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)session.get(BookmarksFolderHBM.class,
							bookmarksFolder.getPrimaryKey());

					if (bookmarksFolderHBM != null) {
						bookmarksFolderHBM.setGroupId(bookmarksFolder.getGroupId());
						bookmarksFolderHBM.setCompanyId(bookmarksFolder.getCompanyId());
						bookmarksFolderHBM.setUserId(bookmarksFolder.getUserId());
						bookmarksFolderHBM.setCreateDate(bookmarksFolder.getCreateDate());
						bookmarksFolderHBM.setModifiedDate(bookmarksFolder.getModifiedDate());
						bookmarksFolderHBM.setParentFolderId(bookmarksFolder.getParentFolderId());
						bookmarksFolderHBM.setName(bookmarksFolder.getName());
						session.flush();
					}
					else {
						bookmarksFolderHBM = new BookmarksFolderHBM(bookmarksFolder.getFolderId(),
								bookmarksFolder.getGroupId(),
								bookmarksFolder.getCompanyId(),
								bookmarksFolder.getUserId(),
								bookmarksFolder.getCreateDate(),
								bookmarksFolder.getModifiedDate(),
								bookmarksFolder.getParentFolderId(),
								bookmarksFolder.getName());
						session.save(bookmarksFolderHBM);
						session.flush();
					}
				}

				bookmarksFolder.setNew(false);
				bookmarksFolder.setModified(false);
				bookmarksFolder.protect();
				BookmarksFolderPool.put(bookmarksFolder.getPrimaryKey(),
					bookmarksFolder);
			}

			return bookmarksFolder;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByPrimaryKey(
		String folderId) throws NoSuchFolderException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = BookmarksFolderPool.get(folderId);
		Session session = null;

		try {
			if (bookmarksFolder == null) {
				session = openSession();

				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)session.get(BookmarksFolderHBM.class,
						folderId);

				if (bookmarksFolderHBM == null) {
					_log.warn(
						"No BookmarksFolder exists with the primary key of " +
						folderId.toString());
					throw new NoSuchFolderException(folderId.toString());
				}

				bookmarksFolder = BookmarksFolderHBMUtil.model(bookmarksFolderHBM);
			}

			return bookmarksFolder;
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
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
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
					list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);
						list.add(BookmarksFolderHBMUtil.model(
								bookmarksFolderHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByGroupId_PrevAndNext(
		String folderId, String groupId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = findByPrimaryKey(folderId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.bookmarks.model.BookmarksFolder[] array = new com.liferay.portlet.bookmarks.model.BookmarksFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);

					if (bookmarksFolderHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksFolder curBookmarksFolder =
						BookmarksFolderHBMUtil.model(bookmarksFolderHBM);
					int value = obc.compare(bookmarksFolder, curBookmarksFolder);

					if (value == 0) {
						if (!bookmarksFolder.equals(curBookmarksFolder)) {
							break;
						}

						array[1] = curBookmarksFolder;

						if (sr.previous()) {
							array[0] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
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
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
					list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);
						list.add(BookmarksFolderHBMUtil.model(
								bookmarksFolderHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_First(
		String groupId, String userId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		List list = findByG_U(groupId, userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_Last(
		String groupId, String userId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		int count = countByG_U(groupId, userId);
		List list = findByG_U(groupId, userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByG_U_PrevAndNext(
		String folderId, String groupId, String userId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = findByPrimaryKey(folderId);
		int count = countByG_U(groupId, userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			com.liferay.portlet.bookmarks.model.BookmarksFolder[] array = new com.liferay.portlet.bookmarks.model.BookmarksFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);

					if (bookmarksFolderHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksFolder curBookmarksFolder =
						BookmarksFolderHBMUtil.model(bookmarksFolderHBM);
					int value = obc.compare(bookmarksFolder, curBookmarksFolder);

					if (value == 0) {
						if (!bookmarksFolder.equals(curBookmarksFolder)) {
							break;
						}

						array[1] = curBookmarksFolder;

						if (sr.previous()) {
							array[0] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
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

	public List findByG_P(String groupId, String parentFolderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, parentFolderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
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

	public List findByG_P(String groupId, String parentFolderId, int begin,
		int end) throws SystemException {
		return findByG_P(groupId, parentFolderId, begin, end, null);
	}

	public List findByG_P(String groupId, String parentFolderId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, parentFolderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
					list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);
						list.add(BookmarksFolderHBMUtil.model(
								bookmarksFolderHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_P_First(
		String groupId, String parentFolderId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		List list = findByG_P(groupId, parentFolderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_P_Last(
		String groupId, String parentFolderId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		int count = countByG_P(groupId, parentFolderId);
		List list = findByG_P(groupId, parentFolderId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByG_P_PrevAndNext(
		String folderId, String groupId, String parentFolderId,
		OrderByComparator obc) throws NoSuchFolderException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = findByPrimaryKey(folderId);
		int count = countByG_P(groupId, parentFolderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, parentFolderId);

			com.liferay.portlet.bookmarks.model.BookmarksFolder[] array = new com.liferay.portlet.bookmarks.model.BookmarksFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);

					if (bookmarksFolderHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksFolder curBookmarksFolder =
						BookmarksFolderHBMUtil.model(bookmarksFolderHBM);
					int value = obc.compare(bookmarksFolder, curBookmarksFolder);

					if (value == 0) {
						if (!bookmarksFolder.equals(curBookmarksFolder)) {
							break;
						}

						array[1] = curBookmarksFolder;

						if (sr.previous()) {
							array[0] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
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

	public List findByG_U_P(String groupId, String userId, String parentFolderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentFolderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
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

	public List findByG_U_P(String groupId, String userId,
		String parentFolderId, int begin, int end) throws SystemException {
		return findByG_U_P(groupId, userId, parentFolderId, begin, end, null);
	}

	public List findByG_U_P(String groupId, String userId,
		String parentFolderId, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentFolderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
					list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);
						list.add(BookmarksFolderHBMUtil.model(
								bookmarksFolderHBM));

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

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_P_First(
		String groupId, String userId, String parentFolderId,
		OrderByComparator obc) throws NoSuchFolderException, SystemException {
		List list = findByG_U_P(groupId, userId, parentFolderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_P_Last(
		String groupId, String userId, String parentFolderId,
		OrderByComparator obc) throws NoSuchFolderException, SystemException {
		int count = countByG_U_P(groupId, userId, parentFolderId);
		List list = findByG_U_P(groupId, userId, parentFolderId, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.bookmarks.model.BookmarksFolder)list.get(0);
		}
	}

	public com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByG_U_P_PrevAndNext(
		String folderId, String groupId, String userId, String parentFolderId,
		OrderByComparator obc) throws NoSuchFolderException, SystemException {
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = findByPrimaryKey(folderId);
		int count = countByG_U_P(groupId, userId, parentFolderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentFolderId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentFolderId);

			com.liferay.portlet.bookmarks.model.BookmarksFolder[] array = new com.liferay.portlet.bookmarks.model.BookmarksFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)sr.get(0);

					if (bookmarksFolderHBM == null) {
						break;
					}

					com.liferay.portlet.bookmarks.model.BookmarksFolder curBookmarksFolder =
						BookmarksFolderHBMUtil.model(bookmarksFolderHBM);
					int value = obc.compare(bookmarksFolder, curBookmarksFolder);

					if (value == 0) {
						if (!bookmarksFolder.equals(curBookmarksFolder)) {
							break;
						}

						array[1] = curBookmarksFolder;

						if (sr.previous()) {
							array[0] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BookmarksFolderHBMUtil.model((BookmarksFolderHBM)sr.get(
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				list.add(BookmarksFolderHBMUtil.model(bookmarksFolderHBM));
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				BookmarksFolderPool.remove((String)bookmarksFolderHBM.getPrimaryKey());
				session.delete(bookmarksFolderHBM);
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				BookmarksFolderPool.remove((String)bookmarksFolderHBM.getPrimaryKey());
				session.delete(bookmarksFolderHBM);
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

	public void removeByG_P(String groupId, String parentFolderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, parentFolderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				BookmarksFolderPool.remove((String)bookmarksFolderHBM.getPrimaryKey());
				session.delete(bookmarksFolderHBM);
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

	public void removeByG_U_P(String groupId, String userId,
		String parentFolderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentFolderId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentFolderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BookmarksFolderHBM bookmarksFolderHBM = (BookmarksFolderHBM)itr.next();
				BookmarksFolderPool.remove((String)bookmarksFolderHBM.getPrimaryKey());
				session.delete(bookmarksFolderHBM);
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
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
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
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

	public int countByG_P(String groupId, String parentFolderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, parentFolderId);

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

	public int countByG_U_P(String groupId, String userId, String parentFolderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BookmarksFolder IN CLASS com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, parentFolderId);

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

	private static final Log _log = LogFactory.getLog(BookmarksFolderPersistence.class);
}
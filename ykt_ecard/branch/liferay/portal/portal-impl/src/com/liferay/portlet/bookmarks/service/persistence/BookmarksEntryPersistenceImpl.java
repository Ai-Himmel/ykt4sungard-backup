/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.uuid.PortalUUIDUtil;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.bookmarks.NoSuchEntryException;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.impl.BookmarksEntryImpl;
import com.liferay.portlet.bookmarks.model.impl.BookmarksEntryModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="BookmarksEntryPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BookmarksEntryPersistenceImpl extends BasePersistence
	implements BookmarksEntryPersistence {
	public BookmarksEntry create(long entryId) {
		BookmarksEntry bookmarksEntry = new BookmarksEntryImpl();

		bookmarksEntry.setNew(true);
		bookmarksEntry.setPrimaryKey(entryId);

		String uuid = PortalUUIDUtil.generate();

		bookmarksEntry.setUuid(uuid);

		return bookmarksEntry;
	}

	public BookmarksEntry remove(long entryId)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BookmarksEntry bookmarksEntry = (BookmarksEntry)session.get(BookmarksEntryImpl.class,
					new Long(entryId));

			if (bookmarksEntry == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No BookmarksEntry exists with the primary key " +
						entryId);
				}

				throw new NoSuchEntryException(
					"No BookmarksEntry exists with the primary key " + entryId);
			}

			return remove(bookmarksEntry);
		}
		catch (NoSuchEntryException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public BookmarksEntry remove(BookmarksEntry bookmarksEntry)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(bookmarksEntry);
		}

		bookmarksEntry = removeImpl(bookmarksEntry);

		if (listener != null) {
			listener.onAfterRemove(bookmarksEntry);
		}

		return bookmarksEntry;
	}

	protected BookmarksEntry removeImpl(BookmarksEntry bookmarksEntry)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(bookmarksEntry);

			session.flush();

			return bookmarksEntry;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(BookmarksEntry.class.getName());
		}
	}

	public BookmarksEntry update(BookmarksEntry bookmarksEntry)
		throws SystemException {
		return update(bookmarksEntry, false);
	}

	public BookmarksEntry update(BookmarksEntry bookmarksEntry, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = bookmarksEntry.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(bookmarksEntry);
			}
			else {
				listener.onBeforeUpdate(bookmarksEntry);
			}
		}

		bookmarksEntry = updateImpl(bookmarksEntry, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(bookmarksEntry);
			}
			else {
				listener.onAfterUpdate(bookmarksEntry);
			}
		}

		return bookmarksEntry;
	}

	public BookmarksEntry updateImpl(
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry,
		boolean merge) throws SystemException {
		if (Validator.isNull(bookmarksEntry.getUuid())) {
			String uuid = PortalUUIDUtil.generate();

			bookmarksEntry.setUuid(uuid);
		}

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(bookmarksEntry);
			}
			else {
				if (bookmarksEntry.isNew()) {
					session.save(bookmarksEntry);
				}
			}

			session.flush();

			bookmarksEntry.setNew(false);

			return bookmarksEntry;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(BookmarksEntry.class.getName());
		}
	}

	public BookmarksEntry findByPrimaryKey(long entryId)
		throws NoSuchEntryException, SystemException {
		BookmarksEntry bookmarksEntry = fetchByPrimaryKey(entryId);

		if (bookmarksEntry == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No BookmarksEntry exists with the primary key " +
					entryId);
			}

			throw new NoSuchEntryException(
				"No BookmarksEntry exists with the primary key " + entryId);
		}

		return bookmarksEntry;
	}

	public BookmarksEntry fetchByPrimaryKey(long entryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (BookmarksEntry)session.get(BookmarksEntryImpl.class,
				new Long(entryId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByUuid(String uuid) throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "findByUuid";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { uuid };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("folderId ASC, ");
				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public List findByUuid(String uuid, int begin, int end)
		throws SystemException {
		return findByUuid(uuid, begin, end, null);
	}

	public List findByUuid(String uuid, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "findByUuid";
		String[] finderParams = new String[] {
				String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				uuid,
				
				String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("folderId ASC, ");
					query.append("name ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
				}

				List list = QueryUtil.list(q, getDialect(), begin, end);

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public BookmarksEntry findByUuid_First(String uuid, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByUuid(uuid, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BookmarksEntry exists with the key {");

			msg.append("uuid=" + uuid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchEntryException(msg.toString());
		}
		else {
			return (BookmarksEntry)list.get(0);
		}
	}

	public BookmarksEntry findByUuid_Last(String uuid, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByUuid(uuid);

		List list = findByUuid(uuid, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BookmarksEntry exists with the key {");

			msg.append("uuid=" + uuid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchEntryException(msg.toString());
		}
		else {
			return (BookmarksEntry)list.get(0);
		}
	}

	public BookmarksEntry[] findByUuid_PrevAndNext(long entryId, String uuid,
		OrderByComparator obc) throws NoSuchEntryException, SystemException {
		BookmarksEntry bookmarksEntry = findByPrimaryKey(entryId);

		int count = countByUuid(uuid);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

			if (uuid == null) {
				query.append("uuid_ IS NULL");
			}
			else {
				query.append("uuid_ = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("folderId ASC, ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			if (uuid != null) {
				q.setString(queryPos++, uuid);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					bookmarksEntry);

			BookmarksEntry[] array = new BookmarksEntryImpl[3];

			array[0] = (BookmarksEntry)objArray[0];
			array[1] = (BookmarksEntry)objArray[1];
			array[2] = (BookmarksEntry)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByFolderId(long folderId) throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "findByFolderId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(folderId) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

				query.append("folderId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("folderId ASC, ");
				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public List findByFolderId(long folderId, int begin, int end)
		throws SystemException {
		return findByFolderId(folderId, begin, end, null);
	}

	public List findByFolderId(long folderId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "findByFolderId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(folderId),
				
				String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

				query.append("folderId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("folderId ASC, ");
					query.append("name ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				List list = QueryUtil.list(q, getDialect(), begin, end);

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public BookmarksEntry findByFolderId_First(long folderId,
		OrderByComparator obc) throws NoSuchEntryException, SystemException {
		List list = findByFolderId(folderId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BookmarksEntry exists with the key {");

			msg.append("folderId=" + folderId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchEntryException(msg.toString());
		}
		else {
			return (BookmarksEntry)list.get(0);
		}
	}

	public BookmarksEntry findByFolderId_Last(long folderId,
		OrderByComparator obc) throws NoSuchEntryException, SystemException {
		int count = countByFolderId(folderId);

		List list = findByFolderId(folderId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BookmarksEntry exists with the key {");

			msg.append("folderId=" + folderId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchEntryException(msg.toString());
		}
		else {
			return (BookmarksEntry)list.get(0);
		}
	}

	public BookmarksEntry[] findByFolderId_PrevAndNext(long entryId,
		long folderId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		BookmarksEntry bookmarksEntry = findByPrimaryKey(entryId);

		int count = countByFolderId(folderId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

			query.append("folderId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("folderId ASC, ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, folderId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					bookmarksEntry);

			BookmarksEntry[] array = new BookmarksEntryImpl[3];

			array[0] = (BookmarksEntry)objArray[0];
			array[1] = (BookmarksEntry)objArray[1];
			array[2] = (BookmarksEntry)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			DynamicQuery query = queryInitializer.initialize(session);

			return query.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			DynamicQuery query = queryInitializer.initialize(session);

			query.setLimit(begin, end);

			return query.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		return findAll(QueryUtil.ALL_POS, QueryUtil.ALL_POS, null);
	}

	public List findAll(int begin, int end) throws SystemException {
		return findAll(begin, end, null);
	}

	public List findAll(int begin, int end, OrderByComparator obc)
		throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "findAll";
		String[] finderParams = new String[] {
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("folderId ASC, ");
					query.append("name ASC");
				}

				Query q = session.createQuery(query.toString());

				List list = QueryUtil.list(q, getDialect(), begin, end);

				if (obc == null) {
					Collections.sort(list);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public void removeByUuid(String uuid) throws SystemException {
		Iterator itr = findByUuid(uuid).iterator();

		while (itr.hasNext()) {
			BookmarksEntry bookmarksEntry = (BookmarksEntry)itr.next();

			remove(bookmarksEntry);
		}
	}

	public void removeByFolderId(long folderId) throws SystemException {
		Iterator itr = findByFolderId(folderId).iterator();

		while (itr.hasNext()) {
			BookmarksEntry bookmarksEntry = (BookmarksEntry)itr.next();

			remove(bookmarksEntry);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((BookmarksEntry)itr.next());
		}
	}

	public int countByUuid(String uuid) throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "countByUuid";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { uuid };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
				}

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	public int countByFolderId(long folderId) throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "countByFolderId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(folderId) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.bookmarks.model.BookmarksEntry WHERE ");

				query.append("folderId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	public int countAll() throws SystemException {
		boolean finderClassNameCacheEnabled = BookmarksEntryModelImpl.CACHE_ENABLED;
		String finderClassName = BookmarksEntry.class.getName();
		String finderMethodName = "countAll";
		String[] finderParams = new String[] {  };
		Object[] finderArgs = new Object[] {  };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				Query q = session.createQuery(
						"SELECT COUNT(*) FROM com.liferay.portlet.bookmarks.model.BookmarksEntry");

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	protected void initDao() {
	}

	private static ModelListener _getListener() {
		if (Validator.isNotNull(_LISTENER)) {
			try {
				return (ModelListener)Class.forName(_LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		return null;
	}

	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.bookmarks.model.BookmarksEntry"));
	private static Log _log = LogFactory.getLog(BookmarksEntryPersistenceImpl.class);
}
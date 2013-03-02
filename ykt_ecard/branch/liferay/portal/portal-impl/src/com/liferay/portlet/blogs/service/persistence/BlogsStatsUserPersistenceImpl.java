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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.blogs.NoSuchStatsUserException;
import com.liferay.portlet.blogs.model.BlogsStatsUser;
import com.liferay.portlet.blogs.model.impl.BlogsStatsUserImpl;
import com.liferay.portlet.blogs.model.impl.BlogsStatsUserModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="BlogsStatsUserPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsStatsUserPersistenceImpl extends BasePersistence
	implements BlogsStatsUserPersistence {
	public BlogsStatsUser create(long statsUserId) {
		BlogsStatsUser blogsStatsUser = new BlogsStatsUserImpl();

		blogsStatsUser.setNew(true);
		blogsStatsUser.setPrimaryKey(statsUserId);

		return blogsStatsUser;
	}

	public BlogsStatsUser remove(long statsUserId)
		throws NoSuchStatsUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BlogsStatsUser blogsStatsUser = (BlogsStatsUser)session.get(BlogsStatsUserImpl.class,
					new Long(statsUserId));

			if (blogsStatsUser == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No BlogsStatsUser exists with the primary key " +
						statsUserId);
				}

				throw new NoSuchStatsUserException(
					"No BlogsStatsUser exists with the primary key " +
					statsUserId);
			}

			return remove(blogsStatsUser);
		}
		catch (NoSuchStatsUserException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public BlogsStatsUser remove(BlogsStatsUser blogsStatsUser)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(blogsStatsUser);
		}

		blogsStatsUser = removeImpl(blogsStatsUser);

		if (listener != null) {
			listener.onAfterRemove(blogsStatsUser);
		}

		return blogsStatsUser;
	}

	protected BlogsStatsUser removeImpl(BlogsStatsUser blogsStatsUser)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(blogsStatsUser);

			session.flush();

			return blogsStatsUser;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(BlogsStatsUser.class.getName());
		}
	}

	public BlogsStatsUser update(BlogsStatsUser blogsStatsUser)
		throws SystemException {
		return update(blogsStatsUser, false);
	}

	public BlogsStatsUser update(BlogsStatsUser blogsStatsUser, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = blogsStatsUser.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(blogsStatsUser);
			}
			else {
				listener.onBeforeUpdate(blogsStatsUser);
			}
		}

		blogsStatsUser = updateImpl(blogsStatsUser, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(blogsStatsUser);
			}
			else {
				listener.onAfterUpdate(blogsStatsUser);
			}
		}

		return blogsStatsUser;
	}

	public BlogsStatsUser updateImpl(
		com.liferay.portlet.blogs.model.BlogsStatsUser blogsStatsUser,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(blogsStatsUser);
			}
			else {
				if (blogsStatsUser.isNew()) {
					session.save(blogsStatsUser);
				}
			}

			session.flush();

			blogsStatsUser.setNew(false);

			return blogsStatsUser;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(BlogsStatsUser.class.getName());
		}
	}

	public BlogsStatsUser findByPrimaryKey(long statsUserId)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = fetchByPrimaryKey(statsUserId);

		if (blogsStatsUser == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No BlogsStatsUser exists with the primary key " +
					statsUserId);
			}

			throw new NoSuchStatsUserException(
				"No BlogsStatsUser exists with the primary key " + statsUserId);
		}

		return blogsStatsUser;
	}

	public BlogsStatsUser fetchByPrimaryKey(long statsUserId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (BlogsStatsUser)session.get(BlogsStatsUserImpl.class,
				new Long(statsUserId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByGroupId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(groupId) };

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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("entryCount DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

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

	public List findByGroupId(long groupId, int begin, int end)
		throws SystemException {
		return findByGroupId(groupId, begin, end, null);
	}

	public List findByGroupId(long groupId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByGroupId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("entryCount DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

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

	public BlogsStatsUser findByGroupId_First(long groupId,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser findByGroupId_Last(long groupId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser[] findByGroupId_PrevAndNext(long statsUserId,
		long groupId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = findByPrimaryKey(statsUserId);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("entryCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					blogsStatsUser);

			BlogsStatsUser[] array = new BlogsStatsUserImpl[3];

			array[0] = (BlogsStatsUser)objArray[0];
			array[1] = (BlogsStatsUser)objArray[1];
			array[2] = (BlogsStatsUser)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByUserId(long userId) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByUserId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(userId) };

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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("userId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("entryCount DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, userId);

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

	public List findByUserId(long userId, int begin, int end)
		throws SystemException {
		return findByUserId(userId, begin, end, null);
	}

	public List findByUserId(long userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByUserId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(userId),
				
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("userId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("entryCount DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, userId);

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

	public BlogsStatsUser findByUserId_First(long userId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser findByUserId_Last(long userId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		int count = countByUserId(userId);

		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser[] findByUserId_PrevAndNext(long statsUserId,
		long userId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = findByPrimaryKey(statsUserId);

		int count = countByUserId(userId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

			query.append("userId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("entryCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, userId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					blogsStatsUser);

			BlogsStatsUser[] array = new BlogsStatsUserImpl[3];

			array[0] = (BlogsStatsUser)objArray[0];
			array[1] = (BlogsStatsUser)objArray[1];
			array[2] = (BlogsStatsUser)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public BlogsStatsUser findByG_U(long groupId, long userId)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = fetchByG_U(groupId, userId);

		if (blogsStatsUser == null) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchStatsUserException(msg.toString());
		}

		return blogsStatsUser;
	}

	public BlogsStatsUser fetchByG_U(long groupId, long userId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "fetchByG_U";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), new Long(userId) };

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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("userId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("entryCount DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setLong(queryPos++, userId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (BlogsStatsUser)list.get(0);
				}
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			List list = (List)result;

			if (list.size() == 0) {
				return null;
			}
			else {
				return (BlogsStatsUser)list.get(0);
			}
		}
	}

	public List findByG_E(long groupId, int entryCount)
		throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByG_E";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), new Integer(entryCount)
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("entryCount != ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("entryCount DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setInteger(queryPos++, entryCount);

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

	public List findByG_E(long groupId, int entryCount, int begin, int end)
		throws SystemException {
		return findByG_E(groupId, entryCount, begin, end, null);
	}

	public List findByG_E(long groupId, int entryCount, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByG_E";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), new Integer(entryCount),
				
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("entryCount != ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("entryCount DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setInteger(queryPos++, entryCount);

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

	public BlogsStatsUser findByG_E_First(long groupId, int entryCount,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		List list = findByG_E(groupId, entryCount, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("entryCount=" + entryCount);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser findByG_E_Last(long groupId, int entryCount,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		int count = countByG_E(groupId, entryCount);

		List list = findByG_E(groupId, entryCount, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("entryCount=" + entryCount);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser[] findByG_E_PrevAndNext(long statsUserId,
		long groupId, int entryCount, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = findByPrimaryKey(statsUserId);

		int count = countByG_E(groupId, entryCount);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("entryCount != ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("entryCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setInteger(queryPos++, entryCount);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					blogsStatsUser);

			BlogsStatsUser[] array = new BlogsStatsUserImpl[3];

			array[0] = (BlogsStatsUser)objArray[0];
			array[1] = (BlogsStatsUser)objArray[1];
			array[2] = (BlogsStatsUser)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByC_E(long companyId, int entryCount)
		throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByC_E";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Integer(entryCount)
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("entryCount != ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("entryCount DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setInteger(queryPos++, entryCount);

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

	public List findByC_E(long companyId, int entryCount, int begin, int end)
		throws SystemException {
		return findByC_E(companyId, entryCount, begin, end, null);
	}

	public List findByC_E(long companyId, int entryCount, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "findByC_E";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Integer(entryCount),
				
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("entryCount != ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("entryCount DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setInteger(queryPos++, entryCount);

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

	public BlogsStatsUser findByC_E_First(long companyId, int entryCount,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		List list = findByC_E(companyId, entryCount, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("entryCount=" + entryCount);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser findByC_E_Last(long companyId, int entryCount,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		int count = countByC_E(companyId, entryCount);

		List list = findByC_E(companyId, entryCount, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No BlogsStatsUser exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("entryCount=" + entryCount);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (BlogsStatsUser)list.get(0);
		}
	}

	public BlogsStatsUser[] findByC_E_PrevAndNext(long statsUserId,
		long companyId, int entryCount, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = findByPrimaryKey(statsUserId);

		int count = countByC_E(companyId, entryCount);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

			query.append("companyId = ?");

			query.append(" AND ");

			query.append("entryCount != ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("entryCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			q.setInteger(queryPos++, entryCount);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					blogsStatsUser);

			BlogsStatsUser[] array = new BlogsStatsUserImpl[3];

			array[0] = (BlogsStatsUser)objArray[0];
			array[1] = (BlogsStatsUser)objArray[1];
			array[2] = (BlogsStatsUser)objArray[2];

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
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("entryCount DESC");
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

	public void removeByGroupId(long groupId) throws SystemException {
		Iterator itr = findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			BlogsStatsUser blogsStatsUser = (BlogsStatsUser)itr.next();

			remove(blogsStatsUser);
		}
	}

	public void removeByUserId(long userId) throws SystemException {
		Iterator itr = findByUserId(userId).iterator();

		while (itr.hasNext()) {
			BlogsStatsUser blogsStatsUser = (BlogsStatsUser)itr.next();

			remove(blogsStatsUser);
		}
	}

	public void removeByG_U(long groupId, long userId)
		throws NoSuchStatsUserException, SystemException {
		BlogsStatsUser blogsStatsUser = findByG_U(groupId, userId);

		remove(blogsStatsUser);
	}

	public void removeByG_E(long groupId, int entryCount)
		throws SystemException {
		Iterator itr = findByG_E(groupId, entryCount).iterator();

		while (itr.hasNext()) {
			BlogsStatsUser blogsStatsUser = (BlogsStatsUser)itr.next();

			remove(blogsStatsUser);
		}
	}

	public void removeByC_E(long companyId, int entryCount)
		throws SystemException {
		Iterator itr = findByC_E(companyId, entryCount).iterator();

		while (itr.hasNext()) {
			BlogsStatsUser blogsStatsUser = (BlogsStatsUser)itr.next();

			remove(blogsStatsUser);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((BlogsStatsUser)itr.next());
		}
	}

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "countByGroupId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(groupId) };

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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

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

	public int countByUserId(long userId) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "countByUserId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(userId) };

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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("userId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, userId);

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

	public int countByG_U(long groupId, long userId) throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "countByG_U";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), new Long(userId) };

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
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("userId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setLong(queryPos++, userId);

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

	public int countByG_E(long groupId, int entryCount)
		throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "countByG_E";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), new Integer(entryCount)
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

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("entryCount != ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setInteger(queryPos++, entryCount);

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

	public int countByC_E(long companyId, int entryCount)
		throws SystemException {
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
		String finderMethodName = "countByC_E";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Integer(entryCount)
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

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.blogs.model.BlogsStatsUser WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("entryCount != ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setInteger(queryPos++, entryCount);

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
		boolean finderClassNameCacheEnabled = BlogsStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = BlogsStatsUser.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.blogs.model.BlogsStatsUser");

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
				"value.object.listener.com.liferay.portlet.blogs.model.BlogsStatsUser"));
	private static Log _log = LogFactory.getLog(BlogsStatsUserPersistenceImpl.class);
}
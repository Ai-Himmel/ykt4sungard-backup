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

package com.liferay.portlet.messageboards.service.persistence;

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

import com.liferay.portlet.messageboards.NoSuchStatsUserException;
import com.liferay.portlet.messageboards.model.MBStatsUser;
import com.liferay.portlet.messageboards.model.impl.MBStatsUserImpl;
import com.liferay.portlet.messageboards.model.impl.MBStatsUserModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="MBStatsUserPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBStatsUserPersistenceImpl extends BasePersistence
	implements MBStatsUserPersistence {
	public MBStatsUser create(long statsUserId) {
		MBStatsUser mbStatsUser = new MBStatsUserImpl();

		mbStatsUser.setNew(true);
		mbStatsUser.setPrimaryKey(statsUserId);

		return mbStatsUser;
	}

	public MBStatsUser remove(long statsUserId)
		throws NoSuchStatsUserException, SystemException {
		Session session = null;

		try {
			session = openSession();

			MBStatsUser mbStatsUser = (MBStatsUser)session.get(MBStatsUserImpl.class,
					new Long(statsUserId));

			if (mbStatsUser == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No MBStatsUser exists with the primary key " +
						statsUserId);
				}

				throw new NoSuchStatsUserException(
					"No MBStatsUser exists with the primary key " +
					statsUserId);
			}

			return remove(mbStatsUser);
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

	public MBStatsUser remove(MBStatsUser mbStatsUser)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(mbStatsUser);
		}

		mbStatsUser = removeImpl(mbStatsUser);

		if (listener != null) {
			listener.onAfterRemove(mbStatsUser);
		}

		return mbStatsUser;
	}

	protected MBStatsUser removeImpl(MBStatsUser mbStatsUser)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(mbStatsUser);

			session.flush();

			return mbStatsUser;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(MBStatsUser.class.getName());
		}
	}

	public MBStatsUser update(MBStatsUser mbStatsUser)
		throws SystemException {
		return update(mbStatsUser, false);
	}

	public MBStatsUser update(MBStatsUser mbStatsUser, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = mbStatsUser.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mbStatsUser);
			}
			else {
				listener.onBeforeUpdate(mbStatsUser);
			}
		}

		mbStatsUser = updateImpl(mbStatsUser, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mbStatsUser);
			}
			else {
				listener.onAfterUpdate(mbStatsUser);
			}
		}

		return mbStatsUser;
	}

	public MBStatsUser updateImpl(
		com.liferay.portlet.messageboards.model.MBStatsUser mbStatsUser,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(mbStatsUser);
			}
			else {
				if (mbStatsUser.isNew()) {
					session.save(mbStatsUser);
				}
			}

			session.flush();

			mbStatsUser.setNew(false);

			return mbStatsUser;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(MBStatsUser.class.getName());
		}
	}

	public MBStatsUser findByPrimaryKey(long statsUserId)
		throws NoSuchStatsUserException, SystemException {
		MBStatsUser mbStatsUser = fetchByPrimaryKey(statsUserId);

		if (mbStatsUser == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No MBStatsUser exists with the primary key " +
					statsUserId);
			}

			throw new NoSuchStatsUserException(
				"No MBStatsUser exists with the primary key " + statsUserId);
		}

		return mbStatsUser;
	}

	public MBStatsUser fetchByPrimaryKey(long statsUserId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (MBStatsUser)session.get(MBStatsUserImpl.class,
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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("messageCount DESC");

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("messageCount DESC");
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

	public MBStatsUser findByGroupId_First(long groupId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (MBStatsUser)list.get(0);
		}
	}

	public MBStatsUser findByGroupId_Last(long groupId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (MBStatsUser)list.get(0);
		}
	}

	public MBStatsUser[] findByGroupId_PrevAndNext(long statsUserId,
		long groupId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		MBStatsUser mbStatsUser = findByPrimaryKey(statsUserId);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("messageCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					mbStatsUser);

			MBStatsUser[] array = new MBStatsUserImpl[3];

			array[0] = (MBStatsUser)objArray[0];
			array[1] = (MBStatsUser)objArray[1];
			array[2] = (MBStatsUser)objArray[2];

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("userId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("messageCount DESC");

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("userId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("messageCount DESC");
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

	public MBStatsUser findByUserId_First(long userId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (MBStatsUser)list.get(0);
		}
	}

	public MBStatsUser findByUserId_Last(long userId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		int count = countByUserId(userId);

		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (MBStatsUser)list.get(0);
		}
	}

	public MBStatsUser[] findByUserId_PrevAndNext(long statsUserId,
		long userId, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		MBStatsUser mbStatsUser = findByPrimaryKey(statsUserId);

		int count = countByUserId(userId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

			query.append("userId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("messageCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, userId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					mbStatsUser);

			MBStatsUser[] array = new MBStatsUserImpl[3];

			array[0] = (MBStatsUser)objArray[0];
			array[1] = (MBStatsUser)objArray[1];
			array[2] = (MBStatsUser)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public MBStatsUser findByG_U(long groupId, long userId)
		throws NoSuchStatsUserException, SystemException {
		MBStatsUser mbStatsUser = fetchByG_U(groupId, userId);

		if (mbStatsUser == null) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchStatsUserException(msg.toString());
		}

		return mbStatsUser;
	}

	public MBStatsUser fetchByG_U(long groupId, long userId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("userId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("messageCount DESC");

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
					return (MBStatsUser)list.get(0);
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
				return (MBStatsUser)list.get(0);
			}
		}
	}

	public List findByG_M(long groupId, int messageCount)
		throws SystemException {
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
		String finderMethodName = "findByG_M";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), new Integer(messageCount)
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("messageCount != ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("messageCount DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setInteger(queryPos++, messageCount);

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

	public List findByG_M(long groupId, int messageCount, int begin, int end)
		throws SystemException {
		return findByG_M(groupId, messageCount, begin, end, null);
	}

	public List findByG_M(long groupId, int messageCount, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
		String finderMethodName = "findByG_M";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), new Integer(messageCount),
				
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("messageCount != ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("messageCount DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setInteger(queryPos++, messageCount);

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

	public MBStatsUser findByG_M_First(long groupId, int messageCount,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		List list = findByG_M(groupId, messageCount, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("messageCount=" + messageCount);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (MBStatsUser)list.get(0);
		}
	}

	public MBStatsUser findByG_M_Last(long groupId, int messageCount,
		OrderByComparator obc) throws NoSuchStatsUserException, SystemException {
		int count = countByG_M(groupId, messageCount);

		List list = findByG_M(groupId, messageCount, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBStatsUser exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("messageCount=" + messageCount);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchStatsUserException(msg.toString());
		}
		else {
			return (MBStatsUser)list.get(0);
		}
	}

	public MBStatsUser[] findByG_M_PrevAndNext(long statsUserId, long groupId,
		int messageCount, OrderByComparator obc)
		throws NoSuchStatsUserException, SystemException {
		MBStatsUser mbStatsUser = findByPrimaryKey(statsUserId);

		int count = countByG_M(groupId, messageCount);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("messageCount != ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("messageCount DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setInteger(queryPos++, messageCount);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					mbStatsUser);

			MBStatsUser[] array = new MBStatsUserImpl[3];

			array[0] = (MBStatsUser)objArray[0];
			array[1] = (MBStatsUser)objArray[1];
			array[2] = (MBStatsUser)objArray[2];

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("messageCount DESC");
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
			MBStatsUser mbStatsUser = (MBStatsUser)itr.next();

			remove(mbStatsUser);
		}
	}

	public void removeByUserId(long userId) throws SystemException {
		Iterator itr = findByUserId(userId).iterator();

		while (itr.hasNext()) {
			MBStatsUser mbStatsUser = (MBStatsUser)itr.next();

			remove(mbStatsUser);
		}
	}

	public void removeByG_U(long groupId, long userId)
		throws NoSuchStatsUserException, SystemException {
		MBStatsUser mbStatsUser = findByG_U(groupId, userId);

		remove(mbStatsUser);
	}

	public void removeByG_M(long groupId, int messageCount)
		throws SystemException {
		Iterator itr = findByG_M(groupId, messageCount).iterator();

		while (itr.hasNext()) {
			MBStatsUser mbStatsUser = (MBStatsUser)itr.next();

			remove(mbStatsUser);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((MBStatsUser)itr.next());
		}
	}

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

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

	public int countByG_M(long groupId, int messageCount)
		throws SystemException {
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
		String finderMethodName = "countByG_M";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), new Integer(messageCount)
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
					"FROM com.liferay.portlet.messageboards.model.MBStatsUser WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("messageCount != ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setInteger(queryPos++, messageCount);

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
		boolean finderClassNameCacheEnabled = MBStatsUserModelImpl.CACHE_ENABLED;
		String finderClassName = MBStatsUser.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.messageboards.model.MBStatsUser");

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
				"value.object.listener.com.liferay.portlet.messageboards.model.MBStatsUser"));
	private static Log _log = LogFactory.getLog(MBStatsUserPersistenceImpl.class);
}
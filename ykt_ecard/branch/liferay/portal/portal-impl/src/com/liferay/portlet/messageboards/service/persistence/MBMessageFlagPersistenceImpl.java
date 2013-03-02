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

import com.liferay.portlet.messageboards.NoSuchMessageFlagException;
import com.liferay.portlet.messageboards.model.MBMessageFlag;
import com.liferay.portlet.messageboards.model.impl.MBMessageFlagImpl;
import com.liferay.portlet.messageboards.model.impl.MBMessageFlagModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="MBMessageFlagPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageFlagPersistenceImpl extends BasePersistence
	implements MBMessageFlagPersistence {
	public MBMessageFlag create(long messageFlagId) {
		MBMessageFlag mbMessageFlag = new MBMessageFlagImpl();

		mbMessageFlag.setNew(true);
		mbMessageFlag.setPrimaryKey(messageFlagId);

		return mbMessageFlag;
	}

	public MBMessageFlag remove(long messageFlagId)
		throws NoSuchMessageFlagException, SystemException {
		Session session = null;

		try {
			session = openSession();

			MBMessageFlag mbMessageFlag = (MBMessageFlag)session.get(MBMessageFlagImpl.class,
					new Long(messageFlagId));

			if (mbMessageFlag == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No MBMessageFlag exists with the primary key " +
						messageFlagId);
				}

				throw new NoSuchMessageFlagException(
					"No MBMessageFlag exists with the primary key " +
					messageFlagId);
			}

			return remove(mbMessageFlag);
		}
		catch (NoSuchMessageFlagException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public MBMessageFlag remove(MBMessageFlag mbMessageFlag)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(mbMessageFlag);
		}

		mbMessageFlag = removeImpl(mbMessageFlag);

		if (listener != null) {
			listener.onAfterRemove(mbMessageFlag);
		}

		return mbMessageFlag;
	}

	protected MBMessageFlag removeImpl(MBMessageFlag mbMessageFlag)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(mbMessageFlag);

			session.flush();

			return mbMessageFlag;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(MBMessageFlag.class.getName());
		}
	}

	public MBMessageFlag update(MBMessageFlag mbMessageFlag)
		throws SystemException {
		return update(mbMessageFlag, false);
	}

	public MBMessageFlag update(MBMessageFlag mbMessageFlag, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = mbMessageFlag.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(mbMessageFlag);
			}
			else {
				listener.onBeforeUpdate(mbMessageFlag);
			}
		}

		mbMessageFlag = updateImpl(mbMessageFlag, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(mbMessageFlag);
			}
			else {
				listener.onAfterUpdate(mbMessageFlag);
			}
		}

		return mbMessageFlag;
	}

	public MBMessageFlag updateImpl(
		com.liferay.portlet.messageboards.model.MBMessageFlag mbMessageFlag,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(mbMessageFlag);
			}
			else {
				if (mbMessageFlag.isNew()) {
					session.save(mbMessageFlag);
				}
			}

			session.flush();

			mbMessageFlag.setNew(false);

			return mbMessageFlag;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(MBMessageFlag.class.getName());
		}
	}

	public MBMessageFlag findByPrimaryKey(long messageFlagId)
		throws NoSuchMessageFlagException, SystemException {
		MBMessageFlag mbMessageFlag = fetchByPrimaryKey(messageFlagId);

		if (mbMessageFlag == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No MBMessageFlag exists with the primary key " +
					messageFlagId);
			}

			throw new NoSuchMessageFlagException(
				"No MBMessageFlag exists with the primary key " +
				messageFlagId);
		}

		return mbMessageFlag;
	}

	public MBMessageFlag fetchByPrimaryKey(long messageFlagId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (MBMessageFlag)session.get(MBMessageFlagImpl.class,
				new Long(messageFlagId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByUserId(long userId) throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("userId = ?");

				query.append(" ");

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
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("userId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
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

	public MBMessageFlag findByUserId_First(long userId, OrderByComparator obc)
		throws NoSuchMessageFlagException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBMessageFlag exists with the key {");

			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchMessageFlagException(msg.toString());
		}
		else {
			return (MBMessageFlag)list.get(0);
		}
	}

	public MBMessageFlag findByUserId_Last(long userId, OrderByComparator obc)
		throws NoSuchMessageFlagException, SystemException {
		int count = countByUserId(userId);

		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBMessageFlag exists with the key {");

			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchMessageFlagException(msg.toString());
		}
		else {
			return (MBMessageFlag)list.get(0);
		}
	}

	public MBMessageFlag[] findByUserId_PrevAndNext(long messageFlagId,
		long userId, OrderByComparator obc)
		throws NoSuchMessageFlagException, SystemException {
		MBMessageFlag mbMessageFlag = findByPrimaryKey(messageFlagId);

		int count = countByUserId(userId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

			query.append("userId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, userId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					mbMessageFlag);

			MBMessageFlag[] array = new MBMessageFlagImpl[3];

			array[0] = (MBMessageFlag)objArray[0];
			array[1] = (MBMessageFlag)objArray[1];
			array[2] = (MBMessageFlag)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByMessageId(long messageId) throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
		String finderMethodName = "findByMessageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(messageId) };

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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("messageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, messageId);

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

	public List findByMessageId(long messageId, int begin, int end)
		throws SystemException {
		return findByMessageId(messageId, begin, end, null);
	}

	public List findByMessageId(long messageId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
		String finderMethodName = "findByMessageId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(messageId),
				
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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("messageId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, messageId);

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

	public MBMessageFlag findByMessageId_First(long messageId,
		OrderByComparator obc)
		throws NoSuchMessageFlagException, SystemException {
		List list = findByMessageId(messageId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBMessageFlag exists with the key {");

			msg.append("messageId=" + messageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchMessageFlagException(msg.toString());
		}
		else {
			return (MBMessageFlag)list.get(0);
		}
	}

	public MBMessageFlag findByMessageId_Last(long messageId,
		OrderByComparator obc)
		throws NoSuchMessageFlagException, SystemException {
		int count = countByMessageId(messageId);

		List list = findByMessageId(messageId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No MBMessageFlag exists with the key {");

			msg.append("messageId=" + messageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchMessageFlagException(msg.toString());
		}
		else {
			return (MBMessageFlag)list.get(0);
		}
	}

	public MBMessageFlag[] findByMessageId_PrevAndNext(long messageFlagId,
		long messageId, OrderByComparator obc)
		throws NoSuchMessageFlagException, SystemException {
		MBMessageFlag mbMessageFlag = findByPrimaryKey(messageFlagId);

		int count = countByMessageId(messageId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

			query.append("messageId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, messageId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					mbMessageFlag);

			MBMessageFlag[] array = new MBMessageFlagImpl[3];

			array[0] = (MBMessageFlag)objArray[0];
			array[1] = (MBMessageFlag)objArray[1];
			array[2] = (MBMessageFlag)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public MBMessageFlag findByU_M(long userId, long messageId)
		throws NoSuchMessageFlagException, SystemException {
		MBMessageFlag mbMessageFlag = fetchByU_M(userId, messageId);

		if (mbMessageFlag == null) {
			StringMaker msg = new StringMaker();

			msg.append("No MBMessageFlag exists with the key {");

			msg.append("userId=" + userId);

			msg.append(", ");
			msg.append("messageId=" + messageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchMessageFlagException(msg.toString());
		}

		return mbMessageFlag;
	}

	public MBMessageFlag fetchByU_M(long userId, long messageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
		String finderMethodName = "fetchByU_M";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(userId), new Long(messageId) };

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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("userId = ?");

				query.append(" AND ");

				query.append("messageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, userId);

				q.setLong(queryPos++, messageId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (MBMessageFlag)list.get(0);
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
				return (MBMessageFlag)list.get(0);
			}
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
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
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

	public void removeByUserId(long userId) throws SystemException {
		Iterator itr = findByUserId(userId).iterator();

		while (itr.hasNext()) {
			MBMessageFlag mbMessageFlag = (MBMessageFlag)itr.next();

			remove(mbMessageFlag);
		}
	}

	public void removeByMessageId(long messageId) throws SystemException {
		Iterator itr = findByMessageId(messageId).iterator();

		while (itr.hasNext()) {
			MBMessageFlag mbMessageFlag = (MBMessageFlag)itr.next();

			remove(mbMessageFlag);
		}
	}

	public void removeByU_M(long userId, long messageId)
		throws NoSuchMessageFlagException, SystemException {
		MBMessageFlag mbMessageFlag = findByU_M(userId, messageId);

		remove(mbMessageFlag);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((MBMessageFlag)itr.next());
		}
	}

	public int countByUserId(long userId) throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

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

	public int countByMessageId(long messageId) throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
		String finderMethodName = "countByMessageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(messageId) };

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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("messageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, messageId);

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

	public int countByU_M(long userId, long messageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
		String finderMethodName = "countByU_M";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(userId), new Long(messageId) };

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
					"FROM com.liferay.portlet.messageboards.model.MBMessageFlag WHERE ");

				query.append("userId = ?");

				query.append(" AND ");

				query.append("messageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, userId);

				q.setLong(queryPos++, messageId);

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
		boolean finderClassNameCacheEnabled = MBMessageFlagModelImpl.CACHE_ENABLED;
		String finderClassName = MBMessageFlag.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.messageboards.model.MBMessageFlag");

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
				"value.object.listener.com.liferay.portlet.messageboards.model.MBMessageFlag"));
	private static Log _log = LogFactory.getLog(MBMessageFlagPersistenceImpl.class);
}
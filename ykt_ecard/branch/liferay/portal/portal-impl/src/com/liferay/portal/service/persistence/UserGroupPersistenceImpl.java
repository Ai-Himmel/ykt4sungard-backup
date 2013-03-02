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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchUserGroupException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.UserGroupImpl;
import com.liferay.portal.model.impl.UserGroupModelImpl;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Hibernate;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import org.springframework.dao.DataAccessException;

import org.springframework.jdbc.core.SqlParameter;
import org.springframework.jdbc.object.MappingSqlQuery;
import org.springframework.jdbc.object.SqlUpdate;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="UserGroupPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserGroupPersistenceImpl extends BasePersistence
	implements UserGroupPersistence {
	public UserGroup create(long userGroupId) {
		UserGroup userGroup = new UserGroupImpl();

		userGroup.setNew(true);
		userGroup.setPrimaryKey(userGroupId);

		return userGroup;
	}

	public UserGroup remove(long userGroupId)
		throws NoSuchUserGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			UserGroup userGroup = (UserGroup)session.get(UserGroupImpl.class,
					new Long(userGroupId));

			if (userGroup == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No UserGroup exists with the primary key " +
						userGroupId);
				}

				throw new NoSuchUserGroupException(
					"No UserGroup exists with the primary key " + userGroupId);
			}

			return remove(userGroup);
		}
		catch (NoSuchUserGroupException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public UserGroup remove(UserGroup userGroup) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(userGroup);
		}

		userGroup = removeImpl(userGroup);

		if (listener != null) {
			listener.onAfterRemove(userGroup);
		}

		return userGroup;
	}

	protected UserGroup removeImpl(UserGroup userGroup)
		throws SystemException {
		try {
			clearUsers.clear(userGroup.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(userGroup);

			session.flush();

			return userGroup;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(UserGroup.class.getName());
		}
	}

	public UserGroup update(UserGroup userGroup) throws SystemException {
		return update(userGroup, false);
	}

	public UserGroup update(UserGroup userGroup, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = userGroup.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(userGroup);
			}
			else {
				listener.onBeforeUpdate(userGroup);
			}
		}

		userGroup = updateImpl(userGroup, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(userGroup);
			}
			else {
				listener.onAfterUpdate(userGroup);
			}
		}

		return userGroup;
	}

	public UserGroup updateImpl(com.liferay.portal.model.UserGroup userGroup,
		boolean merge) throws SystemException {
		FinderCache.clearCache("Users_UserGroups");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(userGroup);
			}
			else {
				if (userGroup.isNew()) {
					session.save(userGroup);
				}
			}

			session.flush();

			userGroup.setNew(false);

			return userGroup;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(UserGroup.class.getName());
		}
	}

	public UserGroup findByPrimaryKey(long userGroupId)
		throws NoSuchUserGroupException, SystemException {
		UserGroup userGroup = fetchByPrimaryKey(userGroupId);

		if (userGroup == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No UserGroup exists with the primary key " +
					userGroupId);
			}

			throw new NoSuchUserGroupException(
				"No UserGroup exists with the primary key " + userGroupId);
		}

		return userGroup;
	}

	public UserGroup fetchByPrimaryKey(long userGroupId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (UserGroup)session.get(UserGroupImpl.class,
				new Long(userGroupId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "findByCompanyId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(companyId) };

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

				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

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

	public List findByCompanyId(long companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(long companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "findByCompanyId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId),
				
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

				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("name ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

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

	public UserGroup findByCompanyId_First(long companyId, OrderByComparator obc)
		throws NoSuchUserGroupException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No UserGroup exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchUserGroupException(msg.toString());
		}
		else {
			return (UserGroup)list.get(0);
		}
	}

	public UserGroup findByCompanyId_Last(long companyId, OrderByComparator obc)
		throws NoSuchUserGroupException, SystemException {
		int count = countByCompanyId(companyId);

		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No UserGroup exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchUserGroupException(msg.toString());
		}
		else {
			return (UserGroup)list.get(0);
		}
	}

	public UserGroup[] findByCompanyId_PrevAndNext(long userGroupId,
		long companyId, OrderByComparator obc)
		throws NoSuchUserGroupException, SystemException {
		UserGroup userGroup = findByPrimaryKey(userGroupId);

		int count = countByCompanyId(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

			query.append("companyId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					userGroup);

			UserGroup[] array = new UserGroupImpl[3];

			array[0] = (UserGroup)objArray[0];
			array[1] = (UserGroup)objArray[1];
			array[2] = (UserGroup)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByC_P(long companyId, long parentUserGroupId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "findByC_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(parentUserGroupId)
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

				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("parentUserGroupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, parentUserGroupId);

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

	public List findByC_P(long companyId, long parentUserGroupId, int begin,
		int end) throws SystemException {
		return findByC_P(companyId, parentUserGroupId, begin, end, null);
	}

	public List findByC_P(long companyId, long parentUserGroupId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "findByC_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(parentUserGroupId),
				
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

				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("parentUserGroupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("name ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, parentUserGroupId);

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

	public UserGroup findByC_P_First(long companyId, long parentUserGroupId,
		OrderByComparator obc) throws NoSuchUserGroupException, SystemException {
		List list = findByC_P(companyId, parentUserGroupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No UserGroup exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("parentUserGroupId=" + parentUserGroupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchUserGroupException(msg.toString());
		}
		else {
			return (UserGroup)list.get(0);
		}
	}

	public UserGroup findByC_P_Last(long companyId, long parentUserGroupId,
		OrderByComparator obc) throws NoSuchUserGroupException, SystemException {
		int count = countByC_P(companyId, parentUserGroupId);

		List list = findByC_P(companyId, parentUserGroupId, count - 1, count,
				obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No UserGroup exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("parentUserGroupId=" + parentUserGroupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchUserGroupException(msg.toString());
		}
		else {
			return (UserGroup)list.get(0);
		}
	}

	public UserGroup[] findByC_P_PrevAndNext(long userGroupId, long companyId,
		long parentUserGroupId, OrderByComparator obc)
		throws NoSuchUserGroupException, SystemException {
		UserGroup userGroup = findByPrimaryKey(userGroupId);

		int count = countByC_P(companyId, parentUserGroupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

			query.append("companyId = ?");

			query.append(" AND ");

			query.append("parentUserGroupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			q.setLong(queryPos++, parentUserGroupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					userGroup);

			UserGroup[] array = new UserGroupImpl[3];

			array[0] = (UserGroup)objArray[0];
			array[1] = (UserGroup)objArray[1];
			array[2] = (UserGroup)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public UserGroup findByC_N(long companyId, String name)
		throws NoSuchUserGroupException, SystemException {
		UserGroup userGroup = fetchByC_N(companyId, name);

		if (userGroup == null) {
			StringMaker msg = new StringMaker();

			msg.append("No UserGroup exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchUserGroupException(msg.toString());
		}

		return userGroup;
	}

	public UserGroup fetchByC_N(long companyId, String name)
		throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "fetchByC_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), name };

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

				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (name != null) {
					q.setString(queryPos++, name);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (UserGroup)list.get(0);
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
				return (UserGroup)list.get(0);
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
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
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

				query.append("FROM com.liferay.portal.model.UserGroup ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

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

	public void removeByCompanyId(long companyId) throws SystemException {
		Iterator itr = findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			UserGroup userGroup = (UserGroup)itr.next();

			remove(userGroup);
		}
	}

	public void removeByC_P(long companyId, long parentUserGroupId)
		throws SystemException {
		Iterator itr = findByC_P(companyId, parentUserGroupId).iterator();

		while (itr.hasNext()) {
			UserGroup userGroup = (UserGroup)itr.next();

			remove(userGroup);
		}
	}

	public void removeByC_N(long companyId, String name)
		throws NoSuchUserGroupException, SystemException {
		UserGroup userGroup = findByC_N(companyId, name);

		remove(userGroup);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((UserGroup)itr.next());
		}
	}

	public int countByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "countByCompanyId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(companyId) };

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
				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

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

	public int countByC_P(long companyId, long parentUserGroupId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "countByC_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(parentUserGroupId)
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
				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("parentUserGroupId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, parentUserGroupId);

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

	public int countByC_N(long companyId, String name)
		throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
		String finderMethodName = "countByC_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), name };

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
				query.append("FROM com.liferay.portal.model.UserGroup WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (name != null) {
					q.setString(queryPos++, name);
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

	public int countAll() throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED;
		String finderClassName = UserGroup.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.UserGroup");

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

	public List getUsers(long pk)
		throws NoSuchUserGroupException, SystemException {
		return getUsers(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getUsers(long pk, int begin, int end)
		throws NoSuchUserGroupException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchUserGroupException, SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED_USERS_USERGROUPS;
		String finderClassName = "Users_UserGroups";
		String finderMethodName = "getUsers";
		String[] finderParams = new String[] {
				Long.class.getName(), "java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(pk), String.valueOf(begin), String.valueOf(end),
				String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = HibernateUtil.openSession();

				StringMaker sm = new StringMaker();

				sm.append(_SQL_GETUSERS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("User_",
					com.liferay.portal.model.impl.UserImpl.class);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(pk);

				List list = QueryUtil.list(q, getDialect(), begin, end);

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public int getUsersSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED_USERS_USERGROUPS;
		String finderClassName = "Users_UserGroups";
		String finderMethodName = "getUsersSize";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(pk) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				SQLQuery q = session.createSQLQuery(_SQL_GETUSERSSIZE);

				q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(pk);

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

	public boolean containsUser(long pk, long userPK) throws SystemException {
		boolean finderClassNameCacheEnabled = UserGroupModelImpl.CACHE_ENABLED_USERS_USERGROUPS;
		String finderClassName = "Users_UserGroups";
		String finderMethodName = "containsUsers";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(userPK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsUser.contains(pk, userPK));

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, value);

				return value.booleanValue();
			}
			catch (DataAccessException dae) {
				throw new SystemException(dae);
			}
		}
		else {
			return ((Boolean)result).booleanValue();
		}
	}

	public boolean containsUsers(long pk) throws SystemException {
		if (getUsersSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addUser(long pk, long userPK)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			addUser.add(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void addUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			addUser.add(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void addUsers(long pk, long[] userPKs)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			for (int i = 0; i < userPKs.length; i++) {
				addUser.add(pk, userPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void addUsers(long pk, List users)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			for (int i = 0; i < users.size(); i++) {
				com.liferay.portal.model.User user = (com.liferay.portal.model.User)users.get(i);

				addUser.add(pk, user.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void clearUsers(long pk)
		throws NoSuchUserGroupException, SystemException {
		try {
			clearUsers.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void removeUser(long pk, long userPK)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			removeUser.remove(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void removeUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			removeUser.remove(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void removeUsers(long pk, long[] userPKs)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			for (int i = 0; i < userPKs.length; i++) {
				removeUser.remove(pk, userPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void removeUsers(long pk, List users)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			for (int i = 0; i < users.size(); i++) {
				com.liferay.portal.model.User user = (com.liferay.portal.model.User)users.get(i);

				removeUser.remove(pk, user.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void setUsers(long pk, long[] userPKs)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			clearUsers.clear(pk);

			for (int i = 0; i < userPKs.length; i++) {
				addUser.add(pk, userPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	public void setUsers(long pk, List users)
		throws NoSuchUserGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			clearUsers.clear(pk);

			for (int i = 0; i < users.size(); i++) {
				com.liferay.portal.model.User user = (com.liferay.portal.model.User)users.get(i);

				addUser.add(pk, user.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_UserGroups");
		}
	}

	protected void initDao() {
		containsUser = new ContainsUser(this);

		addUser = new AddUser(this);
		clearUsers = new ClearUsers(this);
		removeUser = new RemoveUser(this);
	}

	protected ContainsUser containsUser;
	protected AddUser addUser;
	protected ClearUsers clearUsers;
	protected RemoveUser removeUser;

	protected class ContainsUser extends MappingSqlQuery {
		protected ContainsUser(UserGroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSUSER);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long userGroupId, long userId) {
			List results = execute(new Object[] {
						new Long(userGroupId), new Long(userId)
					});

			if (results.size() > 0) {
				Integer count = (Integer)results.get(0);

				if (count.intValue() > 0) {
					return true;
				}
			}

			return false;
		}
	}

	protected class AddUser extends SqlUpdate {
		protected AddUser(UserGroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Users_UserGroups (userGroupId, userId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long userGroupId, long userId) {
			if (!_persistenceImpl.containsUser.contains(userGroupId, userId)) {
				update(new Object[] { new Long(userGroupId), new Long(userId) });
			}
		}

		private UserGroupPersistenceImpl _persistenceImpl;
	}

	protected class ClearUsers extends SqlUpdate {
		protected ClearUsers(UserGroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_UserGroups WHERE userGroupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long userGroupId) {
			update(new Object[] { new Long(userGroupId) });
		}
	}

	protected class RemoveUser extends SqlUpdate {
		protected RemoveUser(UserGroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_UserGroups WHERE userGroupId = ? AND userId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long userGroupId, long userId) {
			update(new Object[] { new Long(userGroupId), new Long(userId) });
		}
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

	private static final String _SQL_GETUSERS = "SELECT {User_.*} FROM User_ INNER JOIN Users_UserGroups ON (Users_UserGroups.userId = User_.userId) WHERE (Users_UserGroups.userGroupId = ?)";
	private static final String _SQL_GETUSERSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_UserGroups WHERE userGroupId = ?";
	private static final String _SQL_CONTAINSUSER = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_UserGroups WHERE userGroupId = ? AND userId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.UserGroup"));
	private static Log _log = LogFactory.getLog(UserGroupPersistenceImpl.class);
}
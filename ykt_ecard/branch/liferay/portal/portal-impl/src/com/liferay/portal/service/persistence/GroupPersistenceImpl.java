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

import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.GroupModelImpl;
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
 * <a href="GroupPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupPersistenceImpl extends BasePersistence
	implements GroupPersistence {
	public Group create(long groupId) {
		Group group = new GroupImpl();

		group.setNew(true);
		group.setPrimaryKey(groupId);

		return group;
	}

	public Group remove(long groupId)
		throws NoSuchGroupException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Group group = (Group)session.get(GroupImpl.class, new Long(groupId));

			if (group == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Group exists with the primary key " +
						groupId);
				}

				throw new NoSuchGroupException(
					"No Group exists with the primary key " + groupId);
			}

			return remove(group);
		}
		catch (NoSuchGroupException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Group remove(Group group) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(group);
		}

		group = removeImpl(group);

		if (listener != null) {
			listener.onAfterRemove(group);
		}

		return group;
	}

	protected Group removeImpl(Group group) throws SystemException {
		try {
			clearOrganizations.clear(group.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}

		try {
			clearPermissions.clear(group.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}

		try {
			clearRoles.clear(group.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}

		try {
			clearUserGroups.clear(group.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}

		try {
			clearUsers.clear(group.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Users_Groups");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(group);

			session.flush();

			return group;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Group.class.getName());
		}
	}

	public Group update(Group group) throws SystemException {
		return update(group, false);
	}

	public Group update(Group group, boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = group.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(group);
			}
			else {
				listener.onBeforeUpdate(group);
			}
		}

		group = updateImpl(group, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(group);
			}
			else {
				listener.onAfterUpdate(group);
			}
		}

		return group;
	}

	public Group updateImpl(com.liferay.portal.model.Group group, boolean merge)
		throws SystemException {
		FinderCache.clearCache("Groups_Orgs");
		FinderCache.clearCache("Groups_Permissions");
		FinderCache.clearCache("Groups_Roles");
		FinderCache.clearCache("Groups_UserGroups");
		FinderCache.clearCache("Users_Groups");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(group);
			}
			else {
				if (group.isNew()) {
					session.save(group);
				}
			}

			session.flush();

			group.setNew(false);

			return group;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Group.class.getName());
		}
	}

	public Group findByPrimaryKey(long groupId)
		throws NoSuchGroupException, SystemException {
		Group group = fetchByPrimaryKey(groupId);

		if (group == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Group exists with the primary key " + groupId);
			}

			throw new NoSuchGroupException(
				"No Group exists with the primary key " + groupId);
		}

		return group;
	}

	public Group fetchByPrimaryKey(long groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Group)session.get(GroupImpl.class, new Long(groupId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Group findByLiveGroupId(long liveGroupId)
		throws NoSuchGroupException, SystemException {
		Group group = fetchByLiveGroupId(liveGroupId);

		if (group == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Group exists with the key {");

			msg.append("liveGroupId=" + liveGroupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchGroupException(msg.toString());
		}

		return group;
	}

	public Group fetchByLiveGroupId(long liveGroupId) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
		String finderMethodName = "fetchByLiveGroupId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(liveGroupId) };

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

				query.append("FROM com.liferay.portal.model.Group WHERE ");

				query.append("liveGroupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, liveGroupId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Group)list.get(0);
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
				return (Group)list.get(0);
			}
		}
	}

	public Group findByC_N(long companyId, String name)
		throws NoSuchGroupException, SystemException {
		Group group = fetchByC_N(companyId, name);

		if (group == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Group exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchGroupException(msg.toString());
		}

		return group;
	}

	public Group fetchByC_N(long companyId, String name)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
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

				query.append("FROM com.liferay.portal.model.Group WHERE ");

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
					return (Group)list.get(0);
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
				return (Group)list.get(0);
			}
		}
	}

	public Group findByC_F(long companyId, String friendlyURL)
		throws NoSuchGroupException, SystemException {
		Group group = fetchByC_F(companyId, friendlyURL);

		if (group == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Group exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("friendlyURL=" + friendlyURL);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchGroupException(msg.toString());
		}

		return group;
	}

	public Group fetchByC_F(long companyId, String friendlyURL)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
		String finderMethodName = "fetchByC_F";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), friendlyURL };

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

				query.append("FROM com.liferay.portal.model.Group WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (friendlyURL == null) {
					query.append("friendlyURL IS NULL");
				}
				else {
					query.append("lower(friendlyURL) = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (friendlyURL != null) {
					q.setString(queryPos++, friendlyURL);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Group)list.get(0);
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
				return (Group)list.get(0);
			}
		}
	}

	public Group findByC_C_C(long companyId, long classNameId, long classPK)
		throws NoSuchGroupException, SystemException {
		Group group = fetchByC_C_C(companyId, classNameId, classPK);

		if (group == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Group exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("classNameId=" + classNameId);

			msg.append(", ");
			msg.append("classPK=" + classPK);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchGroupException(msg.toString());
		}

		return group;
	}

	public Group fetchByC_C_C(long companyId, long classNameId, long classPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
		String finderMethodName = "fetchByC_C_C";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(classNameId), new Long(classPK)
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

				query.append("FROM com.liferay.portal.model.Group WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("classNameId = ?");

				query.append(" AND ");

				query.append("classPK = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, classNameId);

				q.setLong(queryPos++, classPK);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Group)list.get(0);
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
				return (Group)list.get(0);
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
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
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

				query.append("FROM com.liferay.portal.model.Group ");

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

	public void removeByLiveGroupId(long liveGroupId)
		throws NoSuchGroupException, SystemException {
		Group group = findByLiveGroupId(liveGroupId);

		remove(group);
	}

	public void removeByC_N(long companyId, String name)
		throws NoSuchGroupException, SystemException {
		Group group = findByC_N(companyId, name);

		remove(group);
	}

	public void removeByC_F(long companyId, String friendlyURL)
		throws NoSuchGroupException, SystemException {
		Group group = findByC_F(companyId, friendlyURL);

		remove(group);
	}

	public void removeByC_C_C(long companyId, long classNameId, long classPK)
		throws NoSuchGroupException, SystemException {
		Group group = findByC_C_C(companyId, classNameId, classPK);

		remove(group);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Group)itr.next());
		}
	}

	public int countByLiveGroupId(long liveGroupId) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
		String finderMethodName = "countByLiveGroupId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(liveGroupId) };

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
				query.append("FROM com.liferay.portal.model.Group WHERE ");

				query.append("liveGroupId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, liveGroupId);

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
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
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
				query.append("FROM com.liferay.portal.model.Group WHERE ");

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

	public int countByC_F(long companyId, String friendlyURL)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
		String finderMethodName = "countByC_F";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), friendlyURL };

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
				query.append("FROM com.liferay.portal.model.Group WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (friendlyURL == null) {
					query.append("friendlyURL IS NULL");
				}
				else {
					query.append("lower(friendlyURL) = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (friendlyURL != null) {
					q.setString(queryPos++, friendlyURL);
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

	public int countByC_C_C(long companyId, long classNameId, long classPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
		String finderMethodName = "countByC_C_C";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(classNameId), new Long(classPK)
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
				query.append("FROM com.liferay.portal.model.Group WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("classNameId = ?");

				query.append(" AND ");

				query.append("classPK = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, classNameId);

				q.setLong(queryPos++, classPK);

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
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED;
		String finderClassName = Group.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Group");

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

	public List getOrganizations(long pk)
		throws NoSuchGroupException, SystemException {
		return getOrganizations(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getOrganizations(long pk, int begin, int end)
		throws NoSuchGroupException, SystemException {
		return getOrganizations(pk, begin, end, null);
	}

	public List getOrganizations(long pk, int begin, int end,
		OrderByComparator obc) throws NoSuchGroupException, SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_ORGS;
		String finderClassName = "Groups_Orgs";
		String finderMethodName = "getOrganizations";
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

				sm.append(_SQL_GETORGANIZATIONS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("Organization_.name ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("Organization_",
					com.liferay.portal.model.impl.OrganizationImpl.class);

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

	public int getOrganizationsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_ORGS;
		String finderClassName = "Groups_Orgs";
		String finderMethodName = "getOrganizationsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETORGANIZATIONSSIZE);

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

	public boolean containsOrganization(long pk, long organizationPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_ORGS;
		String finderClassName = "Groups_Orgs";
		String finderMethodName = "containsOrganizations";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(pk),
				
				new Long(organizationPK)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsOrganization.contains(
							pk, organizationPK));

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

	public boolean containsOrganizations(long pk) throws SystemException {
		if (getOrganizationsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addOrganization(long pk, long organizationPK)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			addOrganization.add(pk, organizationPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void addOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			addOrganization.add(pk, organization.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void addOrganizations(long pk, long[] organizationPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			for (int i = 0; i < organizationPKs.length; i++) {
				addOrganization.add(pk, organizationPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void addOrganizations(long pk, List organizations)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			for (int i = 0; i < organizations.size(); i++) {
				com.liferay.portal.model.Organization organization = (com.liferay.portal.model.Organization)organizations.get(i);

				addOrganization.add(pk, organization.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void clearOrganizations(long pk)
		throws NoSuchGroupException, SystemException {
		try {
			clearOrganizations.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeOrganization(long pk, long organizationPK)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			removeOrganization.remove(pk, organizationPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			removeOrganization.remove(pk, organization.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeOrganizations(long pk, long[] organizationPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			for (int i = 0; i < organizationPKs.length; i++) {
				removeOrganization.remove(pk, organizationPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeOrganizations(long pk, List organizations)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			for (int i = 0; i < organizations.size(); i++) {
				com.liferay.portal.model.Organization organization = (com.liferay.portal.model.Organization)organizations.get(i);

				removeOrganization.remove(pk, organization.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void setOrganizations(long pk, long[] organizationPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			clearOrganizations.clear(pk);

			for (int i = 0; i < organizationPKs.length; i++) {
				addOrganization.add(pk, organizationPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void setOrganizations(long pk, List organizations)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException, SystemException {
		try {
			clearOrganizations.clear(pk);

			for (int i = 0; i < organizations.size(); i++) {
				com.liferay.portal.model.Organization organization = (com.liferay.portal.model.Organization)organizations.get(i);

				addOrganization.add(pk, organization.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public List getPermissions(long pk)
		throws NoSuchGroupException, SystemException {
		return getPermissions(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getPermissions(long pk, int begin, int end)
		throws NoSuchGroupException, SystemException {
		return getPermissions(pk, begin, end, null);
	}

	public List getPermissions(long pk, int begin, int end,
		OrderByComparator obc) throws NoSuchGroupException, SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
		String finderClassName = "Groups_Permissions";
		String finderMethodName = "getPermissions";
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

				sm.append(_SQL_GETPERMISSIONS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("Permission_",
					com.liferay.portal.model.impl.PermissionImpl.class);

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

	public int getPermissionsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
		String finderClassName = "Groups_Permissions";
		String finderMethodName = "getPermissionsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETPERMISSIONSSIZE);

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

	public boolean containsPermission(long pk, long permissionPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
		String finderClassName = "Groups_Permissions";
		String finderMethodName = "containsPermissions";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(permissionPK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsPermission.contains(
							pk, permissionPK));

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

	public boolean containsPermissions(long pk) throws SystemException {
		if (getPermissionsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addPermission(long pk, long permissionPK)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			addPermission.add(pk, permissionPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void addPermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			addPermission.add(pk, permission.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void addPermissions(long pk, long[] permissionPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			for (int i = 0; i < permissionPKs.length; i++) {
				addPermission.add(pk, permissionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void addPermissions(long pk, List permissions)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			for (int i = 0; i < permissions.size(); i++) {
				com.liferay.portal.model.Permission permission = (com.liferay.portal.model.Permission)permissions.get(i);

				addPermission.add(pk, permission.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void clearPermissions(long pk)
		throws NoSuchGroupException, SystemException {
		try {
			clearPermissions.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removePermission(long pk, long permissionPK)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			removePermission.remove(pk, permissionPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removePermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			removePermission.remove(pk, permission.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removePermissions(long pk, long[] permissionPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			for (int i = 0; i < permissionPKs.length; i++) {
				removePermission.remove(pk, permissionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removePermissions(long pk, List permissions)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			for (int i = 0; i < permissions.size(); i++) {
				com.liferay.portal.model.Permission permission = (com.liferay.portal.model.Permission)permissions.get(i);

				removePermission.remove(pk, permission.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void setPermissions(long pk, long[] permissionPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			clearPermissions.clear(pk);

			for (int i = 0; i < permissionPKs.length; i++) {
				addPermission.add(pk, permissionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void setPermissions(long pk, List permissions)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException, SystemException {
		try {
			clearPermissions.clear(pk);

			for (int i = 0; i < permissions.size(); i++) {
				com.liferay.portal.model.Permission permission = (com.liferay.portal.model.Permission)permissions.get(i);

				addPermission.add(pk, permission.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public List getRoles(long pk) throws NoSuchGroupException, SystemException {
		return getRoles(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getRoles(long pk, int begin, int end)
		throws NoSuchGroupException, SystemException {
		return getRoles(pk, begin, end, null);
	}

	public List getRoles(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_ROLES;
		String finderClassName = "Groups_Roles";
		String finderMethodName = "getRoles";
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

				sm.append(_SQL_GETROLES);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("Role_.name ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("Role_",
					com.liferay.portal.model.impl.RoleImpl.class);

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

	public int getRolesSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_ROLES;
		String finderClassName = "Groups_Roles";
		String finderMethodName = "getRolesSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETROLESSIZE);

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

	public boolean containsRole(long pk, long rolePK) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_ROLES;
		String finderClassName = "Groups_Roles";
		String finderMethodName = "containsRoles";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(rolePK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsRole.contains(pk, rolePK));

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

	public boolean containsRoles(long pk) throws SystemException {
		if (getRolesSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addRole(long pk, long rolePK)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			addRole.add(pk, rolePK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void addRole(long pk, com.liferay.portal.model.Role role)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			addRole.add(pk, role.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void addRoles(long pk, long[] rolePKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			for (int i = 0; i < rolePKs.length; i++) {
				addRole.add(pk, rolePKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void addRoles(long pk, List roles)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			for (int i = 0; i < roles.size(); i++) {
				com.liferay.portal.model.Role role = (com.liferay.portal.model.Role)roles.get(i);

				addRole.add(pk, role.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void clearRoles(long pk)
		throws NoSuchGroupException, SystemException {
		try {
			clearRoles.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void removeRole(long pk, long rolePK)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			removeRole.remove(pk, rolePK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void removeRole(long pk, com.liferay.portal.model.Role role)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			removeRole.remove(pk, role.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void removeRoles(long pk, long[] rolePKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			for (int i = 0; i < rolePKs.length; i++) {
				removeRole.remove(pk, rolePKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void removeRoles(long pk, List roles)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			for (int i = 0; i < roles.size(); i++) {
				com.liferay.portal.model.Role role = (com.liferay.portal.model.Role)roles.get(i);

				removeRole.remove(pk, role.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void setRoles(long pk, long[] rolePKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			clearRoles.clear(pk);

			for (int i = 0; i < rolePKs.length; i++) {
				addRole.add(pk, rolePKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public void setRoles(long pk, List roles)
		throws NoSuchGroupException, com.liferay.portal.NoSuchRoleException, 
			SystemException {
		try {
			clearRoles.clear(pk);

			for (int i = 0; i < roles.size(); i++) {
				com.liferay.portal.model.Role role = (com.liferay.portal.model.Role)roles.get(i);

				addRole.add(pk, role.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Roles");
		}
	}

	public List getUserGroups(long pk)
		throws NoSuchGroupException, SystemException {
		return getUserGroups(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getUserGroups(long pk, int begin, int end)
		throws NoSuchGroupException, SystemException {
		return getUserGroups(pk, begin, end, null);
	}

	public List getUserGroups(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_USERGROUPS;
		String finderClassName = "Groups_UserGroups";
		String finderMethodName = "getUserGroups";
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

				sm.append(_SQL_GETUSERGROUPS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("UserGroup.name ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("UserGroup",
					com.liferay.portal.model.impl.UserGroupImpl.class);

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

	public int getUserGroupsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_USERGROUPS;
		String finderClassName = "Groups_UserGroups";
		String finderMethodName = "getUserGroupsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETUSERGROUPSSIZE);

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

	public boolean containsUserGroup(long pk, long userGroupPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_GROUPS_USERGROUPS;
		String finderClassName = "Groups_UserGroups";
		String finderMethodName = "containsUserGroups";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(userGroupPK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsUserGroup.contains(pk,
							userGroupPK));

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

	public boolean containsUserGroups(long pk) throws SystemException {
		if (getUserGroupsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addUserGroup(long pk, long userGroupPK)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			addUserGroup.add(pk, userGroupPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void addUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			addUserGroup.add(pk, userGroup.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void addUserGroups(long pk, long[] userGroupPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			for (int i = 0; i < userGroupPKs.length; i++) {
				addUserGroup.add(pk, userGroupPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void addUserGroups(long pk, List userGroups)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			for (int i = 0; i < userGroups.size(); i++) {
				com.liferay.portal.model.UserGroup userGroup = (com.liferay.portal.model.UserGroup)userGroups.get(i);

				addUserGroup.add(pk, userGroup.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void clearUserGroups(long pk)
		throws NoSuchGroupException, SystemException {
		try {
			clearUserGroups.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void removeUserGroup(long pk, long userGroupPK)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			removeUserGroup.remove(pk, userGroupPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void removeUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			removeUserGroup.remove(pk, userGroup.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void removeUserGroups(long pk, long[] userGroupPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			for (int i = 0; i < userGroupPKs.length; i++) {
				removeUserGroup.remove(pk, userGroupPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void removeUserGroups(long pk, List userGroups)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			for (int i = 0; i < userGroups.size(); i++) {
				com.liferay.portal.model.UserGroup userGroup = (com.liferay.portal.model.UserGroup)userGroups.get(i);

				removeUserGroup.remove(pk, userGroup.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void setUserGroups(long pk, long[] userGroupPKs)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			clearUserGroups.clear(pk);

			for (int i = 0; i < userGroupPKs.length; i++) {
				addUserGroup.add(pk, userGroupPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public void setUserGroups(long pk, List userGroups)
		throws NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException, SystemException {
		try {
			clearUserGroups.clear(pk);

			for (int i = 0; i < userGroups.size(); i++) {
				com.liferay.portal.model.UserGroup userGroup = (com.liferay.portal.model.UserGroup)userGroups.get(i);

				addUserGroup.add(pk, userGroup.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_UserGroups");
		}
	}

	public List getUsers(long pk) throws NoSuchGroupException, SystemException {
		return getUsers(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getUsers(long pk, int begin, int end)
		throws NoSuchGroupException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchGroupException, SystemException {
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_USERS_GROUPS;
		String finderClassName = "Users_Groups";
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
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_USERS_GROUPS;
		String finderClassName = "Users_Groups";
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
		boolean finderClassNameCacheEnabled = GroupModelImpl.CACHE_ENABLED_USERS_GROUPS;
		String finderClassName = "Users_Groups";
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
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			addUser.add(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void addUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			addUser.add(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void addUsers(long pk, long[] userPKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
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
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void addUsers(long pk, List users)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
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
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void clearUsers(long pk)
		throws NoSuchGroupException, SystemException {
		try {
			clearUsers.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void removeUser(long pk, long userPK)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			removeUser.remove(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void removeUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
			SystemException {
		try {
			removeUser.remove(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void removeUsers(long pk, long[] userPKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
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
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void removeUsers(long pk, List users)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
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
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void setUsers(long pk, long[] userPKs)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
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
			FinderCache.clearCache("Users_Groups");
		}
	}

	public void setUsers(long pk, List users)
		throws NoSuchGroupException, com.liferay.portal.NoSuchUserException, 
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
			FinderCache.clearCache("Users_Groups");
		}
	}

	protected void initDao() {
		containsOrganization = new ContainsOrganization(this);

		addOrganization = new AddOrganization(this);
		clearOrganizations = new ClearOrganizations(this);
		removeOrganization = new RemoveOrganization(this);

		containsPermission = new ContainsPermission(this);

		addPermission = new AddPermission(this);
		clearPermissions = new ClearPermissions(this);
		removePermission = new RemovePermission(this);

		containsRole = new ContainsRole(this);

		addRole = new AddRole(this);
		clearRoles = new ClearRoles(this);
		removeRole = new RemoveRole(this);

		containsUserGroup = new ContainsUserGroup(this);

		addUserGroup = new AddUserGroup(this);
		clearUserGroups = new ClearUserGroups(this);
		removeUserGroup = new RemoveUserGroup(this);

		containsUser = new ContainsUser(this);

		addUser = new AddUser(this);
		clearUsers = new ClearUsers(this);
		removeUser = new RemoveUser(this);
	}

	protected ContainsOrganization containsOrganization;
	protected AddOrganization addOrganization;
	protected ClearOrganizations clearOrganizations;
	protected RemoveOrganization removeOrganization;
	protected ContainsPermission containsPermission;
	protected AddPermission addPermission;
	protected ClearPermissions clearPermissions;
	protected RemovePermission removePermission;
	protected ContainsRole containsRole;
	protected AddRole addRole;
	protected ClearRoles clearRoles;
	protected RemoveRole removeRole;
	protected ContainsUserGroup containsUserGroup;
	protected AddUserGroup addUserGroup;
	protected ClearUserGroups clearUserGroups;
	protected RemoveUserGroup removeUserGroup;
	protected ContainsUser containsUser;
	protected AddUser addUser;
	protected ClearUsers clearUsers;
	protected RemoveUser removeUser;

	protected class ContainsOrganization extends MappingSqlQuery {
		protected ContainsOrganization(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSORGANIZATION);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long groupId, long organizationId) {
			List results = execute(new Object[] {
						new Long(groupId), new Long(organizationId)
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

	protected class AddOrganization extends SqlUpdate {
		protected AddOrganization(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Groups_Orgs (groupId, organizationId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long groupId, long organizationId) {
			if (!_persistenceImpl.containsOrganization.contains(groupId,
						organizationId)) {
				update(new Object[] { new Long(groupId), new Long(
							organizationId) });
			}
		}

		private GroupPersistenceImpl _persistenceImpl;
	}

	protected class ClearOrganizations extends SqlUpdate {
		protected ClearOrganizations(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Orgs WHERE groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long groupId) {
			update(new Object[] { new Long(groupId) });
		}
	}

	protected class RemoveOrganization extends SqlUpdate {
		protected RemoveOrganization(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Orgs WHERE groupId = ? AND organizationId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long groupId, long organizationId) {
			update(new Object[] { new Long(groupId), new Long(organizationId) });
		}
	}

	protected class ContainsPermission extends MappingSqlQuery {
		protected ContainsPermission(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSPERMISSION);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long groupId, long permissionId) {
			List results = execute(new Object[] {
						new Long(groupId), new Long(permissionId)
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

	protected class AddPermission extends SqlUpdate {
		protected AddPermission(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Groups_Permissions (groupId, permissionId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long groupId, long permissionId) {
			if (!_persistenceImpl.containsPermission.contains(groupId,
						permissionId)) {
				update(new Object[] { new Long(groupId), new Long(permissionId) });
			}
		}

		private GroupPersistenceImpl _persistenceImpl;
	}

	protected class ClearPermissions extends SqlUpdate {
		protected ClearPermissions(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Permissions WHERE groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long groupId) {
			update(new Object[] { new Long(groupId) });
		}
	}

	protected class RemovePermission extends SqlUpdate {
		protected RemovePermission(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Permissions WHERE groupId = ? AND permissionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long groupId, long permissionId) {
			update(new Object[] { new Long(groupId), new Long(permissionId) });
		}
	}

	protected class ContainsRole extends MappingSqlQuery {
		protected ContainsRole(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSROLE);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long groupId, long roleId) {
			List results = execute(new Object[] {
						new Long(groupId), new Long(roleId)
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

	protected class AddRole extends SqlUpdate {
		protected AddRole(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Groups_Roles (groupId, roleId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long groupId, long roleId) {
			if (!_persistenceImpl.containsRole.contains(groupId, roleId)) {
				update(new Object[] { new Long(groupId), new Long(roleId) });
			}
		}

		private GroupPersistenceImpl _persistenceImpl;
	}

	protected class ClearRoles extends SqlUpdate {
		protected ClearRoles(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Roles WHERE groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long groupId) {
			update(new Object[] { new Long(groupId) });
		}
	}

	protected class RemoveRole extends SqlUpdate {
		protected RemoveRole(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Roles WHERE groupId = ? AND roleId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long groupId, long roleId) {
			update(new Object[] { new Long(groupId), new Long(roleId) });
		}
	}

	protected class ContainsUserGroup extends MappingSqlQuery {
		protected ContainsUserGroup(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSUSERGROUP);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long groupId, long userGroupId) {
			List results = execute(new Object[] {
						new Long(groupId), new Long(userGroupId)
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

	protected class AddUserGroup extends SqlUpdate {
		protected AddUserGroup(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Groups_UserGroups (groupId, userGroupId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long groupId, long userGroupId) {
			if (!_persistenceImpl.containsUserGroup.contains(groupId,
						userGroupId)) {
				update(new Object[] { new Long(groupId), new Long(userGroupId) });
			}
		}

		private GroupPersistenceImpl _persistenceImpl;
	}

	protected class ClearUserGroups extends SqlUpdate {
		protected ClearUserGroups(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_UserGroups WHERE groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long groupId) {
			update(new Object[] { new Long(groupId) });
		}
	}

	protected class RemoveUserGroup extends SqlUpdate {
		protected RemoveUserGroup(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_UserGroups WHERE groupId = ? AND userGroupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long groupId, long userGroupId) {
			update(new Object[] { new Long(groupId), new Long(userGroupId) });
		}
	}

	protected class ContainsUser extends MappingSqlQuery {
		protected ContainsUser(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSUSER);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long groupId, long userId) {
			List results = execute(new Object[] {
						new Long(groupId), new Long(userId)
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
		protected AddUser(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Users_Groups (groupId, userId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long groupId, long userId) {
			if (!_persistenceImpl.containsUser.contains(groupId, userId)) {
				update(new Object[] { new Long(groupId), new Long(userId) });
			}
		}

		private GroupPersistenceImpl _persistenceImpl;
	}

	protected class ClearUsers extends SqlUpdate {
		protected ClearUsers(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_Groups WHERE groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long groupId) {
			update(new Object[] { new Long(groupId) });
		}
	}

	protected class RemoveUser extends SqlUpdate {
		protected RemoveUser(GroupPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_Groups WHERE groupId = ? AND userId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long groupId, long userId) {
			update(new Object[] { new Long(groupId), new Long(userId) });
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

	private static final String _SQL_GETORGANIZATIONS = "SELECT {Organization_.*} FROM Organization_ INNER JOIN Groups_Orgs ON (Groups_Orgs.organizationId = Organization_.organizationId) WHERE (Groups_Orgs.groupId = ?)";
	private static final String _SQL_GETORGANIZATIONSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Orgs WHERE groupId = ?";
	private static final String _SQL_CONTAINSORGANIZATION = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Orgs WHERE groupId = ? AND organizationId = ?";
	private static final String _SQL_GETPERMISSIONS = "SELECT {Permission_.*} FROM Permission_ INNER JOIN Groups_Permissions ON (Groups_Permissions.permissionId = Permission_.permissionId) WHERE (Groups_Permissions.groupId = ?)";
	private static final String _SQL_GETPERMISSIONSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Permissions WHERE groupId = ?";
	private static final String _SQL_CONTAINSPERMISSION = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Permissions WHERE groupId = ? AND permissionId = ?";
	private static final String _SQL_GETROLES = "SELECT {Role_.*} FROM Role_ INNER JOIN Groups_Roles ON (Groups_Roles.roleId = Role_.roleId) WHERE (Groups_Roles.groupId = ?)";
	private static final String _SQL_GETROLESSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Roles WHERE groupId = ?";
	private static final String _SQL_CONTAINSROLE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Roles WHERE groupId = ? AND roleId = ?";
	private static final String _SQL_GETUSERGROUPS = "SELECT {UserGroup.*} FROM UserGroup INNER JOIN Groups_UserGroups ON (Groups_UserGroups.userGroupId = UserGroup.userGroupId) WHERE (Groups_UserGroups.groupId = ?)";
	private static final String _SQL_GETUSERGROUPSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_UserGroups WHERE groupId = ?";
	private static final String _SQL_CONTAINSUSERGROUP = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_UserGroups WHERE groupId = ? AND userGroupId = ?";
	private static final String _SQL_GETUSERS = "SELECT {User_.*} FROM User_ INNER JOIN Users_Groups ON (Users_Groups.userId = User_.userId) WHERE (Users_Groups.groupId = ?)";
	private static final String _SQL_GETUSERSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_Groups WHERE groupId = ?";
	private static final String _SQL_CONTAINSUSER = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_Groups WHERE groupId = ? AND userId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Group"));
	private static Log _log = LogFactory.getLog(GroupPersistenceImpl.class);
}
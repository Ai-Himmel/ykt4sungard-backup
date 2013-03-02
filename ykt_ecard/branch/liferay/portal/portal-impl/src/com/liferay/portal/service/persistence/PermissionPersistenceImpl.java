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

import com.liferay.portal.NoSuchPermissionException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.impl.PermissionImpl;
import com.liferay.portal.model.impl.PermissionModelImpl;
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
 * <a href="PermissionPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionPersistenceImpl extends BasePersistence
	implements PermissionPersistence {
	public Permission create(long permissionId) {
		Permission permission = new PermissionImpl();

		permission.setNew(true);
		permission.setPrimaryKey(permissionId);

		return permission;
	}

	public Permission remove(long permissionId)
		throws NoSuchPermissionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Permission permission = (Permission)session.get(PermissionImpl.class,
					new Long(permissionId));

			if (permission == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Permission exists with the primary key " +
						permissionId);
				}

				throw new NoSuchPermissionException(
					"No Permission exists with the primary key " +
					permissionId);
			}

			return remove(permission);
		}
		catch (NoSuchPermissionException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Permission remove(Permission permission) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(permission);
		}

		permission = removeImpl(permission);

		if (listener != null) {
			listener.onAfterRemove(permission);
		}

		return permission;
	}

	protected Permission removeImpl(Permission permission)
		throws SystemException {
		try {
			clearGroups.clear(permission.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}

		try {
			clearRoles.clear(permission.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}

		try {
			clearUsers.clear(permission.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(permission);

			session.flush();

			return permission;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Permission.class.getName());
		}
	}

	public Permission update(Permission permission) throws SystemException {
		return update(permission, false);
	}

	public Permission update(Permission permission, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = permission.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(permission);
			}
			else {
				listener.onBeforeUpdate(permission);
			}
		}

		permission = updateImpl(permission, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(permission);
			}
			else {
				listener.onAfterUpdate(permission);
			}
		}

		return permission;
	}

	public Permission updateImpl(
		com.liferay.portal.model.Permission permission, boolean merge)
		throws SystemException {
		FinderCache.clearCache("Groups_Permissions");
		FinderCache.clearCache("Roles_Permissions");
		FinderCache.clearCache("Users_Permissions");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(permission);
			}
			else {
				if (permission.isNew()) {
					session.save(permission);
				}
			}

			session.flush();

			permission.setNew(false);

			return permission;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Permission.class.getName());
		}
	}

	public Permission findByPrimaryKey(long permissionId)
		throws NoSuchPermissionException, SystemException {
		Permission permission = fetchByPrimaryKey(permissionId);

		if (permission == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Permission exists with the primary key " +
					permissionId);
			}

			throw new NoSuchPermissionException(
				"No Permission exists with the primary key " + permissionId);
		}

		return permission;
	}

	public Permission fetchByPrimaryKey(long permissionId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Permission)session.get(PermissionImpl.class,
				new Long(permissionId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByResourceId(long resourceId) throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
		String finderMethodName = "findByResourceId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(resourceId) };

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

				query.append("FROM com.liferay.portal.model.Permission WHERE ");

				query.append("resourceId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, resourceId);

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

	public List findByResourceId(long resourceId, int begin, int end)
		throws SystemException {
		return findByResourceId(resourceId, begin, end, null);
	}

	public List findByResourceId(long resourceId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
		String finderMethodName = "findByResourceId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(resourceId),
				
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

				query.append("FROM com.liferay.portal.model.Permission WHERE ");

				query.append("resourceId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, resourceId);

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

	public Permission findByResourceId_First(long resourceId,
		OrderByComparator obc)
		throws NoSuchPermissionException, SystemException {
		List list = findByResourceId(resourceId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Permission exists with the key {");

			msg.append("resourceId=" + resourceId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPermissionException(msg.toString());
		}
		else {
			return (Permission)list.get(0);
		}
	}

	public Permission findByResourceId_Last(long resourceId,
		OrderByComparator obc)
		throws NoSuchPermissionException, SystemException {
		int count = countByResourceId(resourceId);

		List list = findByResourceId(resourceId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Permission exists with the key {");

			msg.append("resourceId=" + resourceId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPermissionException(msg.toString());
		}
		else {
			return (Permission)list.get(0);
		}
	}

	public Permission[] findByResourceId_PrevAndNext(long permissionId,
		long resourceId, OrderByComparator obc)
		throws NoSuchPermissionException, SystemException {
		Permission permission = findByPrimaryKey(permissionId);

		int count = countByResourceId(resourceId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Permission WHERE ");

			query.append("resourceId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, resourceId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					permission);

			Permission[] array = new PermissionImpl[3];

			array[0] = (Permission)objArray[0];
			array[1] = (Permission)objArray[1];
			array[2] = (Permission)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Permission findByA_R(String actionId, long resourceId)
		throws NoSuchPermissionException, SystemException {
		Permission permission = fetchByA_R(actionId, resourceId);

		if (permission == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Permission exists with the key {");

			msg.append("actionId=" + actionId);

			msg.append(", ");
			msg.append("resourceId=" + resourceId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchPermissionException(msg.toString());
		}

		return permission;
	}

	public Permission fetchByA_R(String actionId, long resourceId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
		String finderMethodName = "fetchByA_R";
		String[] finderParams = new String[] {
				String.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { actionId, new Long(resourceId) };

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

				query.append("FROM com.liferay.portal.model.Permission WHERE ");

				if (actionId == null) {
					query.append("actionId IS NULL");
				}
				else {
					query.append("actionId = ?");
				}

				query.append(" AND ");

				query.append("resourceId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (actionId != null) {
					q.setString(queryPos++, actionId);
				}

				q.setLong(queryPos++, resourceId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Permission)list.get(0);
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
				return (Permission)list.get(0);
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
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
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

				query.append("FROM com.liferay.portal.model.Permission ");

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

	public void removeByResourceId(long resourceId) throws SystemException {
		Iterator itr = findByResourceId(resourceId).iterator();

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			remove(permission);
		}
	}

	public void removeByA_R(String actionId, long resourceId)
		throws NoSuchPermissionException, SystemException {
		Permission permission = findByA_R(actionId, resourceId);

		remove(permission);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Permission)itr.next());
		}
	}

	public int countByResourceId(long resourceId) throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
		String finderMethodName = "countByResourceId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(resourceId) };

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
				query.append("FROM com.liferay.portal.model.Permission WHERE ");

				query.append("resourceId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, resourceId);

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

	public int countByA_R(String actionId, long resourceId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
		String finderMethodName = "countByA_R";
		String[] finderParams = new String[] {
				String.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { actionId, new Long(resourceId) };

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
				query.append("FROM com.liferay.portal.model.Permission WHERE ");

				if (actionId == null) {
					query.append("actionId IS NULL");
				}
				else {
					query.append("actionId = ?");
				}

				query.append(" AND ");

				query.append("resourceId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (actionId != null) {
					q.setString(queryPos++, actionId);
				}

				q.setLong(queryPos++, resourceId);

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
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED;
		String finderClassName = Permission.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Permission");

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

	public List getGroups(long pk)
		throws NoSuchPermissionException, SystemException {
		return getGroups(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getGroups(long pk, int begin, int end)
		throws NoSuchPermissionException, SystemException {
		return getGroups(pk, begin, end, null);
	}

	public List getGroups(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchPermissionException, SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
		String finderClassName = "Groups_Permissions";
		String finderMethodName = "getGroups";
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

				sm.append(_SQL_GETGROUPS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("Group_.name ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("Group_",
					com.liferay.portal.model.impl.GroupImpl.class);

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

	public int getGroupsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
		String finderClassName = "Groups_Permissions";
		String finderMethodName = "getGroupsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETGROUPSSIZE);

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

	public boolean containsGroup(long pk, long groupPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
		String finderClassName = "Groups_Permissions";
		String finderMethodName = "containsGroups";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(groupPK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsGroup.contains(pk,
							groupPK));

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

	public boolean containsGroups(long pk) throws SystemException {
		if (getGroupsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addGroup(long pk, long groupPK)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			addGroup.add(pk, groupPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void addGroup(long pk, com.liferay.portal.model.Group group)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			addGroup.add(pk, group.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void addGroups(long pk, long[] groupPKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			for (int i = 0; i < groupPKs.length; i++) {
				addGroup.add(pk, groupPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void addGroups(long pk, List groups)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			for (int i = 0; i < groups.size(); i++) {
				com.liferay.portal.model.Group group = (com.liferay.portal.model.Group)groups.get(i);

				addGroup.add(pk, group.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void clearGroups(long pk)
		throws NoSuchPermissionException, SystemException {
		try {
			clearGroups.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removeGroup(long pk, long groupPK)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			removeGroup.remove(pk, groupPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			removeGroup.remove(pk, group.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removeGroups(long pk, long[] groupPKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			for (int i = 0; i < groupPKs.length; i++) {
				removeGroup.remove(pk, groupPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void removeGroups(long pk, List groups)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			for (int i = 0; i < groups.size(); i++) {
				com.liferay.portal.model.Group group = (com.liferay.portal.model.Group)groups.get(i);

				removeGroup.remove(pk, group.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void setGroups(long pk, long[] groupPKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			clearGroups.clear(pk);

			for (int i = 0; i < groupPKs.length; i++) {
				addGroup.add(pk, groupPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public void setGroups(long pk, List groups)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			clearGroups.clear(pk);

			for (int i = 0; i < groups.size(); i++) {
				com.liferay.portal.model.Group group = (com.liferay.portal.model.Group)groups.get(i);

				addGroup.add(pk, group.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Permissions");
		}
	}

	public List getRoles(long pk)
		throws NoSuchPermissionException, SystemException {
		return getRoles(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getRoles(long pk, int begin, int end)
		throws NoSuchPermissionException, SystemException {
		return getRoles(pk, begin, end, null);
	}

	public List getRoles(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchPermissionException, SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_ROLES_PERMISSIONS;
		String finderClassName = "Roles_Permissions";
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
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_ROLES_PERMISSIONS;
		String finderClassName = "Roles_Permissions";
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
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_ROLES_PERMISSIONS;
		String finderClassName = "Roles_Permissions";
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
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
		try {
			addRole.add(pk, rolePK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void addRole(long pk, com.liferay.portal.model.Role role)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
		try {
			addRole.add(pk, role.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void addRoles(long pk, long[] rolePKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
		try {
			for (int i = 0; i < rolePKs.length; i++) {
				addRole.add(pk, rolePKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void addRoles(long pk, List roles)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
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
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void clearRoles(long pk)
		throws NoSuchPermissionException, SystemException {
		try {
			clearRoles.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void removeRole(long pk, long rolePK)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
		try {
			removeRole.remove(pk, rolePK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void removeRole(long pk, com.liferay.portal.model.Role role)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
		try {
			removeRole.remove(pk, role.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void removeRoles(long pk, long[] rolePKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
		try {
			for (int i = 0; i < rolePKs.length; i++) {
				removeRole.remove(pk, rolePKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void removeRoles(long pk, List roles)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
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
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void setRoles(long pk, long[] rolePKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
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
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public void setRoles(long pk, List roles)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException, SystemException {
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
			FinderCache.clearCache("Roles_Permissions");
		}
	}

	public List getUsers(long pk)
		throws NoSuchPermissionException, SystemException {
		return getUsers(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getUsers(long pk, int begin, int end)
		throws NoSuchPermissionException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchPermissionException, SystemException {
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_USERS_PERMISSIONS;
		String finderClassName = "Users_Permissions";
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
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_USERS_PERMISSIONS;
		String finderClassName = "Users_Permissions";
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
		boolean finderClassNameCacheEnabled = PermissionModelImpl.CACHE_ENABLED_USERS_PERMISSIONS;
		String finderClassName = "Users_Permissions";
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
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			addUser.add(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void addUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			addUser.add(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void addUsers(long pk, long[] userPKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			for (int i = 0; i < userPKs.length; i++) {
				addUser.add(pk, userPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void addUsers(long pk, List users)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
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
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void clearUsers(long pk)
		throws NoSuchPermissionException, SystemException {
		try {
			clearUsers.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void removeUser(long pk, long userPK)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			removeUser.remove(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void removeUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			removeUser.remove(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void removeUsers(long pk, long[] userPKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			for (int i = 0; i < userPKs.length; i++) {
				removeUser.remove(pk, userPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void removeUsers(long pk, List users)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
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
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void setUsers(long pk, long[] userPKs)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
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
			FinderCache.clearCache("Users_Permissions");
		}
	}

	public void setUsers(long pk, List users)
		throws NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException, SystemException {
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
			FinderCache.clearCache("Users_Permissions");
		}
	}

	protected void initDao() {
		containsGroup = new ContainsGroup(this);

		addGroup = new AddGroup(this);
		clearGroups = new ClearGroups(this);
		removeGroup = new RemoveGroup(this);

		containsRole = new ContainsRole(this);

		addRole = new AddRole(this);
		clearRoles = new ClearRoles(this);
		removeRole = new RemoveRole(this);

		containsUser = new ContainsUser(this);

		addUser = new AddUser(this);
		clearUsers = new ClearUsers(this);
		removeUser = new RemoveUser(this);
	}

	protected ContainsGroup containsGroup;
	protected AddGroup addGroup;
	protected ClearGroups clearGroups;
	protected RemoveGroup removeGroup;
	protected ContainsRole containsRole;
	protected AddRole addRole;
	protected ClearRoles clearRoles;
	protected RemoveRole removeRole;
	protected ContainsUser containsUser;
	protected AddUser addUser;
	protected ClearUsers clearUsers;
	protected RemoveUser removeUser;

	protected class ContainsGroup extends MappingSqlQuery {
		protected ContainsGroup(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSGROUP);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long permissionId, long groupId) {
			List results = execute(new Object[] {
						new Long(permissionId), new Long(groupId)
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

	protected class AddGroup extends SqlUpdate {
		protected AddGroup(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Groups_Permissions (permissionId, groupId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long permissionId, long groupId) {
			if (!_persistenceImpl.containsGroup.contains(permissionId, groupId)) {
				update(new Object[] { new Long(permissionId), new Long(groupId) });
			}
		}

		private PermissionPersistenceImpl _persistenceImpl;
	}

	protected class ClearGroups extends SqlUpdate {
		protected ClearGroups(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Permissions WHERE permissionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long permissionId) {
			update(new Object[] { new Long(permissionId) });
		}
	}

	protected class RemoveGroup extends SqlUpdate {
		protected RemoveGroup(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Permissions WHERE permissionId = ? AND groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long permissionId, long groupId) {
			update(new Object[] { new Long(permissionId), new Long(groupId) });
		}
	}

	protected class ContainsRole extends MappingSqlQuery {
		protected ContainsRole(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSROLE);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long permissionId, long roleId) {
			List results = execute(new Object[] {
						new Long(permissionId), new Long(roleId)
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
		protected AddRole(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Roles_Permissions (permissionId, roleId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long permissionId, long roleId) {
			if (!_persistenceImpl.containsRole.contains(permissionId, roleId)) {
				update(new Object[] { new Long(permissionId), new Long(roleId) });
			}
		}

		private PermissionPersistenceImpl _persistenceImpl;
	}

	protected class ClearRoles extends SqlUpdate {
		protected ClearRoles(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Roles_Permissions WHERE permissionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long permissionId) {
			update(new Object[] { new Long(permissionId) });
		}
	}

	protected class RemoveRole extends SqlUpdate {
		protected RemoveRole(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Roles_Permissions WHERE permissionId = ? AND roleId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long permissionId, long roleId) {
			update(new Object[] { new Long(permissionId), new Long(roleId) });
		}
	}

	protected class ContainsUser extends MappingSqlQuery {
		protected ContainsUser(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSUSER);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long permissionId, long userId) {
			List results = execute(new Object[] {
						new Long(permissionId), new Long(userId)
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
		protected AddUser(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Users_Permissions (permissionId, userId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long permissionId, long userId) {
			if (!_persistenceImpl.containsUser.contains(permissionId, userId)) {
				update(new Object[] { new Long(permissionId), new Long(userId) });
			}
		}

		private PermissionPersistenceImpl _persistenceImpl;
	}

	protected class ClearUsers extends SqlUpdate {
		protected ClearUsers(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_Permissions WHERE permissionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long permissionId) {
			update(new Object[] { new Long(permissionId) });
		}
	}

	protected class RemoveUser extends SqlUpdate {
		protected RemoveUser(PermissionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_Permissions WHERE permissionId = ? AND userId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long permissionId, long userId) {
			update(new Object[] { new Long(permissionId), new Long(userId) });
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

	private static final String _SQL_GETGROUPS = "SELECT {Group_.*} FROM Group_ INNER JOIN Groups_Permissions ON (Groups_Permissions.groupId = Group_.groupId) WHERE (Groups_Permissions.permissionId = ?)";
	private static final String _SQL_GETGROUPSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Permissions WHERE permissionId = ?";
	private static final String _SQL_CONTAINSGROUP = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Permissions WHERE permissionId = ? AND groupId = ?";
	private static final String _SQL_GETROLES = "SELECT {Role_.*} FROM Role_ INNER JOIN Roles_Permissions ON (Roles_Permissions.roleId = Role_.roleId) WHERE (Roles_Permissions.permissionId = ?)";
	private static final String _SQL_GETROLESSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Roles_Permissions WHERE permissionId = ?";
	private static final String _SQL_CONTAINSROLE = "SELECT COUNT(*) AS COUNT_VALUE FROM Roles_Permissions WHERE permissionId = ? AND roleId = ?";
	private static final String _SQL_GETUSERS = "SELECT {User_.*} FROM User_ INNER JOIN Users_Permissions ON (Users_Permissions.userId = User_.userId) WHERE (Users_Permissions.permissionId = ?)";
	private static final String _SQL_GETUSERSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_Permissions WHERE permissionId = ?";
	private static final String _SQL_CONTAINSUSER = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_Permissions WHERE permissionId = ? AND userId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Permission"));
	private static Log _log = LogFactory.getLog(PermissionPersistenceImpl.class);
}
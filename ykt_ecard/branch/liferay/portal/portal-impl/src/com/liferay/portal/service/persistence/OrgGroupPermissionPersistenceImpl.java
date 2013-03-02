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

import com.liferay.portal.NoSuchOrgGroupPermissionException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.OrgGroupPermission;
import com.liferay.portal.model.impl.OrgGroupPermissionImpl;
import com.liferay.portal.model.impl.OrgGroupPermissionModelImpl;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="OrgGroupPermissionPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgGroupPermissionPersistenceImpl extends BasePersistence
	implements OrgGroupPermissionPersistence {
	public OrgGroupPermission create(OrgGroupPermissionPK orgGroupPermissionPK) {
		OrgGroupPermission orgGroupPermission = new OrgGroupPermissionImpl();

		orgGroupPermission.setNew(true);
		orgGroupPermission.setPrimaryKey(orgGroupPermissionPK);

		return orgGroupPermission;
	}

	public OrgGroupPermission remove(OrgGroupPermissionPK orgGroupPermissionPK)
		throws NoSuchOrgGroupPermissionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			OrgGroupPermission orgGroupPermission = (OrgGroupPermission)session.get(OrgGroupPermissionImpl.class,
					orgGroupPermissionPK);

			if (orgGroupPermission == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No OrgGroupPermission exists with the primary key " +
						orgGroupPermissionPK);
				}

				throw new NoSuchOrgGroupPermissionException(
					"No OrgGroupPermission exists with the primary key " +
					orgGroupPermissionPK);
			}

			return remove(orgGroupPermission);
		}
		catch (NoSuchOrgGroupPermissionException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public OrgGroupPermission remove(OrgGroupPermission orgGroupPermission)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(orgGroupPermission);
		}

		orgGroupPermission = removeImpl(orgGroupPermission);

		if (listener != null) {
			listener.onAfterRemove(orgGroupPermission);
		}

		return orgGroupPermission;
	}

	protected OrgGroupPermission removeImpl(
		OrgGroupPermission orgGroupPermission) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(orgGroupPermission);

			session.flush();

			return orgGroupPermission;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(OrgGroupPermission.class.getName());
		}
	}

	public OrgGroupPermission update(OrgGroupPermission orgGroupPermission)
		throws SystemException {
		return update(orgGroupPermission, false);
	}

	public OrgGroupPermission update(OrgGroupPermission orgGroupPermission,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = orgGroupPermission.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(orgGroupPermission);
			}
			else {
				listener.onBeforeUpdate(orgGroupPermission);
			}
		}

		orgGroupPermission = updateImpl(orgGroupPermission, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(orgGroupPermission);
			}
			else {
				listener.onAfterUpdate(orgGroupPermission);
			}
		}

		return orgGroupPermission;
	}

	public OrgGroupPermission updateImpl(
		com.liferay.portal.model.OrgGroupPermission orgGroupPermission,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(orgGroupPermission);
			}
			else {
				if (orgGroupPermission.isNew()) {
					session.save(orgGroupPermission);
				}
			}

			session.flush();

			orgGroupPermission.setNew(false);

			return orgGroupPermission;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(OrgGroupPermission.class.getName());
		}
	}

	public OrgGroupPermission findByPrimaryKey(
		OrgGroupPermissionPK orgGroupPermissionPK)
		throws NoSuchOrgGroupPermissionException, SystemException {
		OrgGroupPermission orgGroupPermission = fetchByPrimaryKey(orgGroupPermissionPK);

		if (orgGroupPermission == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No OrgGroupPermission exists with the primary key " +
					orgGroupPermissionPK);
			}

			throw new NoSuchOrgGroupPermissionException(
				"No OrgGroupPermission exists with the primary key " +
				orgGroupPermissionPK);
		}

		return orgGroupPermission;
	}

	public OrgGroupPermission fetchByPrimaryKey(
		OrgGroupPermissionPK orgGroupPermissionPK) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (OrgGroupPermission)session.get(OrgGroupPermissionImpl.class,
				orgGroupPermissionPK);
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
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
					"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

				query.append("groupId = ?");

				query.append(" ");

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
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
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
					"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
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

	public OrgGroupPermission findByGroupId_First(long groupId,
		OrderByComparator obc)
		throws NoSuchOrgGroupPermissionException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No OrgGroupPermission exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrgGroupPermissionException(msg.toString());
		}
		else {
			return (OrgGroupPermission)list.get(0);
		}
	}

	public OrgGroupPermission findByGroupId_Last(long groupId,
		OrderByComparator obc)
		throws NoSuchOrgGroupPermissionException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No OrgGroupPermission exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrgGroupPermissionException(msg.toString());
		}
		else {
			return (OrgGroupPermission)list.get(0);
		}
	}

	public OrgGroupPermission[] findByGroupId_PrevAndNext(
		OrgGroupPermissionPK orgGroupPermissionPK, long groupId,
		OrderByComparator obc)
		throws NoSuchOrgGroupPermissionException, SystemException {
		OrgGroupPermission orgGroupPermission = findByPrimaryKey(orgGroupPermissionPK);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					orgGroupPermission);

			OrgGroupPermission[] array = new OrgGroupPermissionImpl[3];

			array[0] = (OrgGroupPermission)objArray[0];
			array[1] = (OrgGroupPermission)objArray[1];
			array[2] = (OrgGroupPermission)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByPermissionId(long permissionId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
		String finderMethodName = "findByPermissionId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(permissionId) };

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
					"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

				query.append("permissionId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, permissionId);

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

	public List findByPermissionId(long permissionId, int begin, int end)
		throws SystemException {
		return findByPermissionId(permissionId, begin, end, null);
	}

	public List findByPermissionId(long permissionId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
		String finderMethodName = "findByPermissionId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(permissionId),
				
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
					"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

				query.append("permissionId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, permissionId);

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

	public OrgGroupPermission findByPermissionId_First(long permissionId,
		OrderByComparator obc)
		throws NoSuchOrgGroupPermissionException, SystemException {
		List list = findByPermissionId(permissionId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No OrgGroupPermission exists with the key {");

			msg.append("permissionId=" + permissionId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrgGroupPermissionException(msg.toString());
		}
		else {
			return (OrgGroupPermission)list.get(0);
		}
	}

	public OrgGroupPermission findByPermissionId_Last(long permissionId,
		OrderByComparator obc)
		throws NoSuchOrgGroupPermissionException, SystemException {
		int count = countByPermissionId(permissionId);

		List list = findByPermissionId(permissionId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No OrgGroupPermission exists with the key {");

			msg.append("permissionId=" + permissionId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrgGroupPermissionException(msg.toString());
		}
		else {
			return (OrgGroupPermission)list.get(0);
		}
	}

	public OrgGroupPermission[] findByPermissionId_PrevAndNext(
		OrgGroupPermissionPK orgGroupPermissionPK, long permissionId,
		OrderByComparator obc)
		throws NoSuchOrgGroupPermissionException, SystemException {
		OrgGroupPermission orgGroupPermission = findByPrimaryKey(orgGroupPermissionPK);

		int count = countByPermissionId(permissionId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

			query.append("permissionId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, permissionId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					orgGroupPermission);

			OrgGroupPermission[] array = new OrgGroupPermissionImpl[3];

			array[0] = (OrgGroupPermission)objArray[0];
			array[1] = (OrgGroupPermission)objArray[1];
			array[2] = (OrgGroupPermission)objArray[2];

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
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
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
					"FROM com.liferay.portal.model.OrgGroupPermission ");

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

	public void removeByGroupId(long groupId) throws SystemException {
		Iterator itr = findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			OrgGroupPermission orgGroupPermission = (OrgGroupPermission)itr.next();

			remove(orgGroupPermission);
		}
	}

	public void removeByPermissionId(long permissionId)
		throws SystemException {
		Iterator itr = findByPermissionId(permissionId).iterator();

		while (itr.hasNext()) {
			OrgGroupPermission orgGroupPermission = (OrgGroupPermission)itr.next();

			remove(orgGroupPermission);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((OrgGroupPermission)itr.next());
		}
	}

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
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
					"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

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

	public int countByPermissionId(long permissionId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
		String finderMethodName = "countByPermissionId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(permissionId) };

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
					"FROM com.liferay.portal.model.OrgGroupPermission WHERE ");

				query.append("permissionId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, permissionId);

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
		boolean finderClassNameCacheEnabled = OrgGroupPermissionModelImpl.CACHE_ENABLED;
		String finderClassName = OrgGroupPermission.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.OrgGroupPermission");

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
				"value.object.listener.com.liferay.portal.model.OrgGroupPermission"));
	private static Log _log = LogFactory.getLog(OrgGroupPermissionPersistenceImpl.class);
}
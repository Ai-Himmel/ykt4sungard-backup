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

package com.liferay.portlet.softwarecatalog.service.persistence;

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

import com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException;
import com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion;
import com.liferay.portlet.softwarecatalog.model.impl.SCFrameworkVersionImpl;
import com.liferay.portlet.softwarecatalog.model.impl.SCFrameworkVersionModelImpl;

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
 * <a href="SCFrameworkVersionPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCFrameworkVersionPersistenceImpl extends BasePersistence
	implements SCFrameworkVersionPersistence {
	public SCFrameworkVersion create(long frameworkVersionId) {
		SCFrameworkVersion scFrameworkVersion = new SCFrameworkVersionImpl();

		scFrameworkVersion.setNew(true);
		scFrameworkVersion.setPrimaryKey(frameworkVersionId);

		return scFrameworkVersion;
	}

	public SCFrameworkVersion remove(long frameworkVersionId)
		throws NoSuchFrameworkVersionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			SCFrameworkVersion scFrameworkVersion = (SCFrameworkVersion)session.get(SCFrameworkVersionImpl.class,
					new Long(frameworkVersionId));

			if (scFrameworkVersion == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No SCFrameworkVersion exists with the primary key " +
						frameworkVersionId);
				}

				throw new NoSuchFrameworkVersionException(
					"No SCFrameworkVersion exists with the primary key " +
					frameworkVersionId);
			}

			return remove(scFrameworkVersion);
		}
		catch (NoSuchFrameworkVersionException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public SCFrameworkVersion remove(SCFrameworkVersion scFrameworkVersion)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(scFrameworkVersion);
		}

		scFrameworkVersion = removeImpl(scFrameworkVersion);

		if (listener != null) {
			listener.onAfterRemove(scFrameworkVersion);
		}

		return scFrameworkVersion;
	}

	protected SCFrameworkVersion removeImpl(
		SCFrameworkVersion scFrameworkVersion) throws SystemException {
		try {
			clearSCProductVersions.clear(scFrameworkVersion.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(scFrameworkVersion);

			session.flush();

			return scFrameworkVersion;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(SCFrameworkVersion.class.getName());
		}
	}

	public SCFrameworkVersion update(SCFrameworkVersion scFrameworkVersion)
		throws SystemException {
		return update(scFrameworkVersion, false);
	}

	public SCFrameworkVersion update(SCFrameworkVersion scFrameworkVersion,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = scFrameworkVersion.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(scFrameworkVersion);
			}
			else {
				listener.onBeforeUpdate(scFrameworkVersion);
			}
		}

		scFrameworkVersion = updateImpl(scFrameworkVersion, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(scFrameworkVersion);
			}
			else {
				listener.onAfterUpdate(scFrameworkVersion);
			}
		}

		return scFrameworkVersion;
	}

	public SCFrameworkVersion updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion,
		boolean merge) throws SystemException {
		FinderCache.clearCache("SCFrameworkVersi_SCProductVers");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(scFrameworkVersion);
			}
			else {
				if (scFrameworkVersion.isNew()) {
					session.save(scFrameworkVersion);
				}
			}

			session.flush();

			scFrameworkVersion.setNew(false);

			return scFrameworkVersion;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(SCFrameworkVersion.class.getName());
		}
	}

	public SCFrameworkVersion findByPrimaryKey(long frameworkVersionId)
		throws NoSuchFrameworkVersionException, SystemException {
		SCFrameworkVersion scFrameworkVersion = fetchByPrimaryKey(frameworkVersionId);

		if (scFrameworkVersion == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No SCFrameworkVersion exists with the primary key " +
					frameworkVersionId);
			}

			throw new NoSuchFrameworkVersionException(
				"No SCFrameworkVersion exists with the primary key " +
				frameworkVersionId);
		}

		return scFrameworkVersion;
	}

	public SCFrameworkVersion fetchByPrimaryKey(long frameworkVersionId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (SCFrameworkVersion)session.get(SCFrameworkVersionImpl.class,
				new Long(frameworkVersionId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("priority ASC, ");
				query.append("name ASC");

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
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("priority ASC, ");
					query.append("name ASC");
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

	public SCFrameworkVersion findByGroupId_First(long groupId,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCFrameworkVersion exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFrameworkVersionException(msg.toString());
		}
		else {
			return (SCFrameworkVersion)list.get(0);
		}
	}

	public SCFrameworkVersion findByGroupId_Last(long groupId,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCFrameworkVersion exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFrameworkVersionException(msg.toString());
		}
		else {
			return (SCFrameworkVersion)list.get(0);
		}
	}

	public SCFrameworkVersion[] findByGroupId_PrevAndNext(
		long frameworkVersionId, long groupId, OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		SCFrameworkVersion scFrameworkVersion = findByPrimaryKey(frameworkVersionId);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("priority ASC, ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					scFrameworkVersion);

			SCFrameworkVersion[] array = new SCFrameworkVersionImpl[3];

			array[0] = (SCFrameworkVersion)objArray[0];
			array[1] = (SCFrameworkVersion)objArray[1];
			array[2] = (SCFrameworkVersion)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("priority ASC, ");
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
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("priority ASC, ");
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

	public SCFrameworkVersion findByCompanyId_First(long companyId,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCFrameworkVersion exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFrameworkVersionException(msg.toString());
		}
		else {
			return (SCFrameworkVersion)list.get(0);
		}
	}

	public SCFrameworkVersion findByCompanyId_Last(long companyId,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		int count = countByCompanyId(companyId);

		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCFrameworkVersion exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFrameworkVersionException(msg.toString());
		}
		else {
			return (SCFrameworkVersion)list.get(0);
		}
	}

	public SCFrameworkVersion[] findByCompanyId_PrevAndNext(
		long frameworkVersionId, long companyId, OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		SCFrameworkVersion scFrameworkVersion = findByPrimaryKey(frameworkVersionId);

		int count = countByCompanyId(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

			query.append("companyId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("priority ASC, ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					scFrameworkVersion);

			SCFrameworkVersion[] array = new SCFrameworkVersionImpl[3];

			array[0] = (SCFrameworkVersion)objArray[0];
			array[1] = (SCFrameworkVersion)objArray[1];
			array[2] = (SCFrameworkVersion)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_A(long groupId, boolean active)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
		String finderMethodName = "findByG_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(active)
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("active_ = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("priority ASC, ");
				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, active);

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

	public List findByG_A(long groupId, boolean active, int begin, int end)
		throws SystemException {
		return findByG_A(groupId, active, begin, end, null);
	}

	public List findByG_A(long groupId, boolean active, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
		String finderMethodName = "findByG_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(active),
				
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("active_ = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("priority ASC, ");
					query.append("name ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, active);

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

	public SCFrameworkVersion findByG_A_First(long groupId, boolean active,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		List list = findByG_A(groupId, active, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCFrameworkVersion exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFrameworkVersionException(msg.toString());
		}
		else {
			return (SCFrameworkVersion)list.get(0);
		}
	}

	public SCFrameworkVersion findByG_A_Last(long groupId, boolean active,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		int count = countByG_A(groupId, active);

		List list = findByG_A(groupId, active, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCFrameworkVersion exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFrameworkVersionException(msg.toString());
		}
		else {
			return (SCFrameworkVersion)list.get(0);
		}
	}

	public SCFrameworkVersion[] findByG_A_PrevAndNext(long frameworkVersionId,
		long groupId, boolean active, OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		SCFrameworkVersion scFrameworkVersion = findByPrimaryKey(frameworkVersionId);

		int count = countByG_A(groupId, active);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("active_ = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("priority ASC, ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, active);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					scFrameworkVersion);

			SCFrameworkVersion[] array = new SCFrameworkVersionImpl[3];

			array[0] = (SCFrameworkVersion)objArray[0];
			array[1] = (SCFrameworkVersion)objArray[1];
			array[2] = (SCFrameworkVersion)objArray[2];

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
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("priority ASC, ");
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

	public void removeByGroupId(long groupId) throws SystemException {
		Iterator itr = findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			SCFrameworkVersion scFrameworkVersion = (SCFrameworkVersion)itr.next();

			remove(scFrameworkVersion);
		}
	}

	public void removeByCompanyId(long companyId) throws SystemException {
		Iterator itr = findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			SCFrameworkVersion scFrameworkVersion = (SCFrameworkVersion)itr.next();

			remove(scFrameworkVersion);
		}
	}

	public void removeByG_A(long groupId, boolean active)
		throws SystemException {
		Iterator itr = findByG_A(groupId, active).iterator();

		while (itr.hasNext()) {
			SCFrameworkVersion scFrameworkVersion = (SCFrameworkVersion)itr.next();

			remove(scFrameworkVersion);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((SCFrameworkVersion)itr.next());
		}
	}

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

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

	public int countByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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
				query.append(
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

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

	public int countByG_A(long groupId, boolean active)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
		String finderMethodName = "countByG_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(active)
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("active_ = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, active);

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
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCFrameworkVersion.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion");

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

	public List getSCProductVersions(long pk)
		throws NoSuchFrameworkVersionException, SystemException {
		return getSCProductVersions(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getSCProductVersions(long pk, int begin, int end)
		throws NoSuchFrameworkVersionException, SystemException {
		return getSCProductVersions(pk, begin, end, null);
	}

	public List getSCProductVersions(long pk, int begin, int end,
		OrderByComparator obc)
		throws NoSuchFrameworkVersionException, SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
		String finderClassName = "SCFrameworkVersi_SCProductVers";
		String finderMethodName = "getSCProductVersions";
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

				sm.append(_SQL_GETSCPRODUCTVERSIONS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("SCProductVersion.createDate DESC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("SCProductVersion",
					com.liferay.portlet.softwarecatalog.model.impl.SCProductVersionImpl.class);

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

	public int getSCProductVersionsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
		String finderClassName = "SCFrameworkVersi_SCProductVers";
		String finderMethodName = "getSCProductVersionsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETSCPRODUCTVERSIONSSIZE);

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

	public boolean containsSCProductVersion(long pk, long scProductVersionPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCFrameworkVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
		String finderClassName = "SCFrameworkVersi_SCProductVers";
		String finderMethodName = "containsSCProductVersions";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(pk),
				
				new Long(scProductVersionPK)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsSCProductVersion.contains(
							pk, scProductVersionPK));

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

	public boolean containsSCProductVersions(long pk) throws SystemException {
		if (getSCProductVersionsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addSCProductVersion(long pk, long scProductVersionPK)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			addSCProductVersion.add(pk, scProductVersionPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void addSCProductVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			addSCProductVersion.add(pk, scProductVersion.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void addSCProductVersions(long pk, long[] scProductVersionPKs)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scProductVersionPKs.length; i++) {
				addSCProductVersion.add(pk, scProductVersionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void addSCProductVersions(long pk, List scProductVersions)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scProductVersions.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion =
					(com.liferay.portlet.softwarecatalog.model.SCProductVersion)scProductVersions.get(i);

				addSCProductVersion.add(pk, scProductVersion.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void clearSCProductVersions(long pk)
		throws NoSuchFrameworkVersionException, SystemException {
		try {
			clearSCProductVersions.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCProductVersion(long pk, long scProductVersionPK)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			removeSCProductVersion.remove(pk, scProductVersionPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCProductVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			removeSCProductVersion.remove(pk, scProductVersion.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCProductVersions(long pk, long[] scProductVersionPKs)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scProductVersionPKs.length; i++) {
				removeSCProductVersion.remove(pk, scProductVersionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCProductVersions(long pk, List scProductVersions)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scProductVersions.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion =
					(com.liferay.portlet.softwarecatalog.model.SCProductVersion)scProductVersions.get(i);

				removeSCProductVersion.remove(pk,
					scProductVersion.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void setSCProductVersions(long pk, long[] scProductVersionPKs)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			clearSCProductVersions.clear(pk);

			for (int i = 0; i < scProductVersionPKs.length; i++) {
				addSCProductVersion.add(pk, scProductVersionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void setSCProductVersions(long pk, List scProductVersions)
		throws NoSuchFrameworkVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductVersionException, 
			SystemException {
		try {
			clearSCProductVersions.clear(pk);

			for (int i = 0; i < scProductVersions.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion =
					(com.liferay.portlet.softwarecatalog.model.SCProductVersion)scProductVersions.get(i);

				addSCProductVersion.add(pk, scProductVersion.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	protected void initDao() {
		containsSCProductVersion = new ContainsSCProductVersion(this);

		addSCProductVersion = new AddSCProductVersion(this);
		clearSCProductVersions = new ClearSCProductVersions(this);
		removeSCProductVersion = new RemoveSCProductVersion(this);
	}

	protected ContainsSCProductVersion containsSCProductVersion;
	protected AddSCProductVersion addSCProductVersion;
	protected ClearSCProductVersions clearSCProductVersions;
	protected RemoveSCProductVersion removeSCProductVersion;

	protected class ContainsSCProductVersion extends MappingSqlQuery {
		protected ContainsSCProductVersion(
			SCFrameworkVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSSCPRODUCTVERSION);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long frameworkVersionId,
			long productVersionId) {
			List results = execute(new Object[] {
						new Long(frameworkVersionId), new Long(productVersionId)
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

	protected class AddSCProductVersion extends SqlUpdate {
		protected AddSCProductVersion(
			SCFrameworkVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO SCFrameworkVersi_SCProductVers (frameworkVersionId, productVersionId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long frameworkVersionId, long productVersionId) {
			if (!_persistenceImpl.containsSCProductVersion.contains(
						frameworkVersionId, productVersionId)) {
				update(new Object[] {
						new Long(frameworkVersionId), new Long(productVersionId)
					});
			}
		}

		private SCFrameworkVersionPersistenceImpl _persistenceImpl;
	}

	protected class ClearSCProductVersions extends SqlUpdate {
		protected ClearSCProductVersions(
			SCFrameworkVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM SCFrameworkVersi_SCProductVers WHERE frameworkVersionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long frameworkVersionId) {
			update(new Object[] { new Long(frameworkVersionId) });
		}
	}

	protected class RemoveSCProductVersion extends SqlUpdate {
		protected RemoveSCProductVersion(
			SCFrameworkVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM SCFrameworkVersi_SCProductVers WHERE frameworkVersionId = ? AND productVersionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long frameworkVersionId, long productVersionId) {
			update(new Object[] {
					new Long(frameworkVersionId), new Long(productVersionId)
				});
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

	private static final String _SQL_GETSCPRODUCTVERSIONS = "SELECT {SCProductVersion.*} FROM SCProductVersion INNER JOIN SCFrameworkVersi_SCProductVers ON (SCFrameworkVersi_SCProductVers.productVersionId = SCProductVersion.productVersionId) WHERE (SCFrameworkVersi_SCProductVers.frameworkVersionId = ?)";
	private static final String _SQL_GETSCPRODUCTVERSIONSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM SCFrameworkVersi_SCProductVers WHERE frameworkVersionId = ?";
	private static final String _SQL_CONTAINSSCPRODUCTVERSION = "SELECT COUNT(*) AS COUNT_VALUE FROM SCFrameworkVersi_SCProductVers WHERE frameworkVersionId = ? AND productVersionId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion"));
	private static Log _log = LogFactory.getLog(SCFrameworkVersionPersistenceImpl.class);
}
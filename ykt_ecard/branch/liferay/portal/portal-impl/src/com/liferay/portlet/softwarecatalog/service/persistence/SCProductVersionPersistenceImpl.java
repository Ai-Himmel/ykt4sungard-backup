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

import com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;
import com.liferay.portlet.softwarecatalog.model.SCProductVersion;
import com.liferay.portlet.softwarecatalog.model.impl.SCProductVersionImpl;
import com.liferay.portlet.softwarecatalog.model.impl.SCProductVersionModelImpl;

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
 * <a href="SCProductVersionPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductVersionPersistenceImpl extends BasePersistence
	implements SCProductVersionPersistence {
	public SCProductVersion create(long productVersionId) {
		SCProductVersion scProductVersion = new SCProductVersionImpl();

		scProductVersion.setNew(true);
		scProductVersion.setPrimaryKey(productVersionId);

		return scProductVersion;
	}

	public SCProductVersion remove(long productVersionId)
		throws NoSuchProductVersionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			SCProductVersion scProductVersion = (SCProductVersion)session.get(SCProductVersionImpl.class,
					new Long(productVersionId));

			if (scProductVersion == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No SCProductVersion exists with the primary key " +
						productVersionId);
				}

				throw new NoSuchProductVersionException(
					"No SCProductVersion exists with the primary key " +
					productVersionId);
			}

			return remove(scProductVersion);
		}
		catch (NoSuchProductVersionException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public SCProductVersion remove(SCProductVersion scProductVersion)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(scProductVersion);
		}

		scProductVersion = removeImpl(scProductVersion);

		if (listener != null) {
			listener.onAfterRemove(scProductVersion);
		}

		return scProductVersion;
	}

	protected SCProductVersion removeImpl(SCProductVersion scProductVersion)
		throws SystemException {
		try {
			clearSCFrameworkVersions.clear(scProductVersion.getPrimaryKey());
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

			session.delete(scProductVersion);

			session.flush();

			return scProductVersion;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(SCProductVersion.class.getName());
		}
	}

	public SCProductVersion update(SCProductVersion scProductVersion)
		throws SystemException {
		return update(scProductVersion, false);
	}

	public SCProductVersion update(SCProductVersion scProductVersion,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = scProductVersion.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(scProductVersion);
			}
			else {
				listener.onBeforeUpdate(scProductVersion);
			}
		}

		scProductVersion = updateImpl(scProductVersion, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(scProductVersion);
			}
			else {
				listener.onAfterUpdate(scProductVersion);
			}
		}

		return scProductVersion;
	}

	public SCProductVersion updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCProductVersion scProductVersion,
		boolean merge) throws SystemException {
		FinderCache.clearCache("SCFrameworkVersi_SCProductVers");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(scProductVersion);
			}
			else {
				if (scProductVersion.isNew()) {
					session.save(scProductVersion);
				}
			}

			session.flush();

			scProductVersion.setNew(false);

			return scProductVersion;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(SCProductVersion.class.getName());
		}
	}

	public SCProductVersion findByPrimaryKey(long productVersionId)
		throws NoSuchProductVersionException, SystemException {
		SCProductVersion scProductVersion = fetchByPrimaryKey(productVersionId);

		if (scProductVersion == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No SCProductVersion exists with the primary key " +
					productVersionId);
			}

			throw new NoSuchProductVersionException(
				"No SCProductVersion exists with the primary key " +
				productVersionId);
		}

		return scProductVersion;
	}

	public SCProductVersion fetchByPrimaryKey(long productVersionId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (SCProductVersion)session.get(SCProductVersionImpl.class,
				new Long(productVersionId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByProductEntryId(long productEntryId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
		String finderMethodName = "findByProductEntryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(productEntryId) };

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
					"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion WHERE ");

				query.append("productEntryId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("createDate DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, productEntryId);

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

	public List findByProductEntryId(long productEntryId, int begin, int end)
		throws SystemException {
		return findByProductEntryId(productEntryId, begin, end, null);
	}

	public List findByProductEntryId(long productEntryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
		String finderMethodName = "findByProductEntryId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(productEntryId),
				
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion WHERE ");

				query.append("productEntryId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("createDate DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, productEntryId);

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

	public SCProductVersion findByProductEntryId_First(long productEntryId,
		OrderByComparator obc)
		throws NoSuchProductVersionException, SystemException {
		List list = findByProductEntryId(productEntryId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCProductVersion exists with the key {");

			msg.append("productEntryId=" + productEntryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchProductVersionException(msg.toString());
		}
		else {
			return (SCProductVersion)list.get(0);
		}
	}

	public SCProductVersion findByProductEntryId_Last(long productEntryId,
		OrderByComparator obc)
		throws NoSuchProductVersionException, SystemException {
		int count = countByProductEntryId(productEntryId);

		List list = findByProductEntryId(productEntryId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCProductVersion exists with the key {");

			msg.append("productEntryId=" + productEntryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchProductVersionException(msg.toString());
		}
		else {
			return (SCProductVersion)list.get(0);
		}
	}

	public SCProductVersion[] findByProductEntryId_PrevAndNext(
		long productVersionId, long productEntryId, OrderByComparator obc)
		throws NoSuchProductVersionException, SystemException {
		SCProductVersion scProductVersion = findByPrimaryKey(productVersionId);

		int count = countByProductEntryId(productEntryId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion WHERE ");

			query.append("productEntryId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, productEntryId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					scProductVersion);

			SCProductVersion[] array = new SCProductVersionImpl[3];

			array[0] = (SCProductVersion)objArray[0];
			array[1] = (SCProductVersion)objArray[1];
			array[2] = (SCProductVersion)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public SCProductVersion findByDirectDownloadURL(String directDownloadURL)
		throws NoSuchProductVersionException, SystemException {
		SCProductVersion scProductVersion = fetchByDirectDownloadURL(directDownloadURL);

		if (scProductVersion == null) {
			StringMaker msg = new StringMaker();

			msg.append("No SCProductVersion exists with the key {");

			msg.append("directDownloadURL=" + directDownloadURL);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchProductVersionException(msg.toString());
		}

		return scProductVersion;
	}

	public SCProductVersion fetchByDirectDownloadURL(String directDownloadURL)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
		String finderMethodName = "fetchByDirectDownloadURL";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { directDownloadURL };

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
					"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion WHERE ");

				if (directDownloadURL == null) {
					query.append("directDownloadURL IS NULL");
				}
				else {
					query.append("lower(directDownloadURL) = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("createDate DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (directDownloadURL != null) {
					q.setString(queryPos++, directDownloadURL);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (SCProductVersion)list.get(0);
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
				return (SCProductVersion)list.get(0);
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
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("createDate DESC");
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

	public void removeByProductEntryId(long productEntryId)
		throws SystemException {
		Iterator itr = findByProductEntryId(productEntryId).iterator();

		while (itr.hasNext()) {
			SCProductVersion scProductVersion = (SCProductVersion)itr.next();

			remove(scProductVersion);
		}
	}

	public void removeByDirectDownloadURL(String directDownloadURL)
		throws NoSuchProductVersionException, SystemException {
		SCProductVersion scProductVersion = findByDirectDownloadURL(directDownloadURL);

		remove(scProductVersion);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((SCProductVersion)itr.next());
		}
	}

	public int countByProductEntryId(long productEntryId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
		String finderMethodName = "countByProductEntryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(productEntryId) };

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
					"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion WHERE ");

				query.append("productEntryId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, productEntryId);

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

	public int countByDirectDownloadURL(String directDownloadURL)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
		String finderMethodName = "countByDirectDownloadURL";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { directDownloadURL };

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
					"FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion WHERE ");

				if (directDownloadURL == null) {
					query.append("directDownloadURL IS NULL");
				}
				else {
					query.append("lower(directDownloadURL) = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (directDownloadURL != null) {
					q.setString(queryPos++, directDownloadURL);
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
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED;
		String finderClassName = SCProductVersion.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.softwarecatalog.model.SCProductVersion");

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

	public List getSCFrameworkVersions(long pk)
		throws NoSuchProductVersionException, SystemException {
		return getSCFrameworkVersions(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getSCFrameworkVersions(long pk, int begin, int end)
		throws NoSuchProductVersionException, SystemException {
		return getSCFrameworkVersions(pk, begin, end, null);
	}

	public List getSCFrameworkVersions(long pk, int begin, int end,
		OrderByComparator obc)
		throws NoSuchProductVersionException, SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
		String finderClassName = "SCFrameworkVersi_SCProductVers";
		String finderMethodName = "getSCFrameworkVersions";
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

				sm.append(_SQL_GETSCFRAMEWORKVERSIONS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("SCFrameworkVersion.priority ASC, ");
					sm.append("SCFrameworkVersion.name ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("SCFrameworkVersion",
					com.liferay.portlet.softwarecatalog.model.impl.SCFrameworkVersionImpl.class);

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

	public int getSCFrameworkVersionsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
		String finderClassName = "SCFrameworkVersi_SCProductVers";
		String finderMethodName = "getSCFrameworkVersionsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETSCFRAMEWORKVERSIONSSIZE);

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

	public boolean containsSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCProductVersionModelImpl.CACHE_ENABLED_SCFRAMEWORKVERSI_SCPRODUCTVERS;
		String finderClassName = "SCFrameworkVersi_SCProductVers";
		String finderMethodName = "containsSCFrameworkVersions";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(pk),
				
				new Long(scFrameworkVersionPK)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsSCFrameworkVersion.contains(
							pk, scFrameworkVersionPK));

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

	public boolean containsSCFrameworkVersions(long pk)
		throws SystemException {
		if (getSCFrameworkVersionsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			addSCFrameworkVersion.add(pk, scFrameworkVersionPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void addSCFrameworkVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			addSCFrameworkVersion.add(pk, scFrameworkVersion.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void addSCFrameworkVersions(long pk, long[] scFrameworkVersionPKs)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scFrameworkVersionPKs.length; i++) {
				addSCFrameworkVersion.add(pk, scFrameworkVersionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void addSCFrameworkVersions(long pk, List scFrameworkVersions)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scFrameworkVersions.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion =
					(com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion)scFrameworkVersions.get(i);

				addSCFrameworkVersion.add(pk, scFrameworkVersion.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void clearSCFrameworkVersions(long pk)
		throws NoSuchProductVersionException, SystemException {
		try {
			clearSCFrameworkVersions.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCFrameworkVersion(long pk, long scFrameworkVersionPK)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			removeSCFrameworkVersion.remove(pk, scFrameworkVersionPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCFrameworkVersion(long pk,
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			removeSCFrameworkVersion.remove(pk,
				scFrameworkVersion.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCFrameworkVersions(long pk, long[] scFrameworkVersionPKs)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scFrameworkVersionPKs.length; i++) {
				removeSCFrameworkVersion.remove(pk, scFrameworkVersionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void removeSCFrameworkVersions(long pk, List scFrameworkVersions)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			for (int i = 0; i < scFrameworkVersions.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion =
					(com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion)scFrameworkVersions.get(i);

				removeSCFrameworkVersion.remove(pk,
					scFrameworkVersion.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void setSCFrameworkVersions(long pk, long[] scFrameworkVersionPKs)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			clearSCFrameworkVersions.clear(pk);

			for (int i = 0; i < scFrameworkVersionPKs.length; i++) {
				addSCFrameworkVersion.add(pk, scFrameworkVersionPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCFrameworkVersi_SCProductVers");
		}
	}

	public void setSCFrameworkVersions(long pk, List scFrameworkVersions)
		throws NoSuchProductVersionException, 
			com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException, 
			SystemException {
		try {
			clearSCFrameworkVersions.clear(pk);

			for (int i = 0; i < scFrameworkVersions.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion scFrameworkVersion =
					(com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion)scFrameworkVersions.get(i);

				addSCFrameworkVersion.add(pk, scFrameworkVersion.getPrimaryKey());
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
		containsSCFrameworkVersion = new ContainsSCFrameworkVersion(this);

		addSCFrameworkVersion = new AddSCFrameworkVersion(this);
		clearSCFrameworkVersions = new ClearSCFrameworkVersions(this);
		removeSCFrameworkVersion = new RemoveSCFrameworkVersion(this);
	}

	protected ContainsSCFrameworkVersion containsSCFrameworkVersion;
	protected AddSCFrameworkVersion addSCFrameworkVersion;
	protected ClearSCFrameworkVersions clearSCFrameworkVersions;
	protected RemoveSCFrameworkVersion removeSCFrameworkVersion;

	protected class ContainsSCFrameworkVersion extends MappingSqlQuery {
		protected ContainsSCFrameworkVersion(
			SCProductVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				_SQL_CONTAINSSCFRAMEWORKVERSION);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long productVersionId,
			long frameworkVersionId) {
			List results = execute(new Object[] {
						new Long(productVersionId), new Long(frameworkVersionId)
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

	protected class AddSCFrameworkVersion extends SqlUpdate {
		protected AddSCFrameworkVersion(
			SCProductVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO SCFrameworkVersi_SCProductVers (productVersionId, frameworkVersionId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long productVersionId, long frameworkVersionId) {
			if (!_persistenceImpl.containsSCFrameworkVersion.contains(
						productVersionId, frameworkVersionId)) {
				update(new Object[] {
						new Long(productVersionId), new Long(frameworkVersionId)
					});
			}
		}

		private SCProductVersionPersistenceImpl _persistenceImpl;
	}

	protected class ClearSCFrameworkVersions extends SqlUpdate {
		protected ClearSCFrameworkVersions(
			SCProductVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM SCFrameworkVersi_SCProductVers WHERE productVersionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long productVersionId) {
			update(new Object[] { new Long(productVersionId) });
		}
	}

	protected class RemoveSCFrameworkVersion extends SqlUpdate {
		protected RemoveSCFrameworkVersion(
			SCProductVersionPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM SCFrameworkVersi_SCProductVers WHERE productVersionId = ? AND frameworkVersionId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long productVersionId, long frameworkVersionId) {
			update(new Object[] {
					new Long(productVersionId), new Long(frameworkVersionId)
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

	private static final String _SQL_GETSCFRAMEWORKVERSIONS = "SELECT {SCFrameworkVersion.*} FROM SCFrameworkVersion INNER JOIN SCFrameworkVersi_SCProductVers ON (SCFrameworkVersi_SCProductVers.frameworkVersionId = SCFrameworkVersion.frameworkVersionId) WHERE (SCFrameworkVersi_SCProductVers.productVersionId = ?)";
	private static final String _SQL_GETSCFRAMEWORKVERSIONSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM SCFrameworkVersi_SCProductVers WHERE productVersionId = ?";
	private static final String _SQL_CONTAINSSCFRAMEWORKVERSION = "SELECT COUNT(*) AS COUNT_VALUE FROM SCFrameworkVersi_SCProductVers WHERE productVersionId = ? AND frameworkVersionId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.softwarecatalog.model.SCProductVersion"));
	private static Log _log = LogFactory.getLog(SCProductVersionPersistenceImpl.class);
}
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

import com.liferay.portlet.softwarecatalog.NoSuchLicenseException;
import com.liferay.portlet.softwarecatalog.model.SCLicense;
import com.liferay.portlet.softwarecatalog.model.impl.SCLicenseImpl;
import com.liferay.portlet.softwarecatalog.model.impl.SCLicenseModelImpl;

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
 * <a href="SCLicensePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SCLicensePersistenceImpl extends BasePersistence
	implements SCLicensePersistence {
	public SCLicense create(long licenseId) {
		SCLicense scLicense = new SCLicenseImpl();

		scLicense.setNew(true);
		scLicense.setPrimaryKey(licenseId);

		return scLicense;
	}

	public SCLicense remove(long licenseId)
		throws NoSuchLicenseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			SCLicense scLicense = (SCLicense)session.get(SCLicenseImpl.class,
					new Long(licenseId));

			if (scLicense == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No SCLicense exists with the primary key " +
						licenseId);
				}

				throw new NoSuchLicenseException(
					"No SCLicense exists with the primary key " + licenseId);
			}

			return remove(scLicense);
		}
		catch (NoSuchLicenseException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public SCLicense remove(SCLicense scLicense) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(scLicense);
		}

		scLicense = removeImpl(scLicense);

		if (listener != null) {
			listener.onAfterRemove(scLicense);
		}

		return scLicense;
	}

	protected SCLicense removeImpl(SCLicense scLicense)
		throws SystemException {
		try {
			clearSCProductEntries.clear(scLicense.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(scLicense);

			session.flush();

			return scLicense;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(SCLicense.class.getName());
		}
	}

	public SCLicense update(SCLicense scLicense) throws SystemException {
		return update(scLicense, false);
	}

	public SCLicense update(SCLicense scLicense, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = scLicense.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(scLicense);
			}
			else {
				listener.onBeforeUpdate(scLicense);
			}
		}

		scLicense = updateImpl(scLicense, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(scLicense);
			}
			else {
				listener.onAfterUpdate(scLicense);
			}
		}

		return scLicense;
	}

	public SCLicense updateImpl(
		com.liferay.portlet.softwarecatalog.model.SCLicense scLicense,
		boolean merge) throws SystemException {
		FinderCache.clearCache("SCLicenses_SCProductEntries");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(scLicense);
			}
			else {
				if (scLicense.isNew()) {
					session.save(scLicense);
				}
			}

			session.flush();

			scLicense.setNew(false);

			return scLicense;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(SCLicense.class.getName());
		}
	}

	public SCLicense findByPrimaryKey(long licenseId)
		throws NoSuchLicenseException, SystemException {
		SCLicense scLicense = fetchByPrimaryKey(licenseId);

		if (scLicense == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No SCLicense exists with the primary key " +
					licenseId);
			}

			throw new NoSuchLicenseException(
				"No SCLicense exists with the primary key " + licenseId);
		}

		return scLicense;
	}

	public SCLicense fetchByPrimaryKey(long licenseId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (SCLicense)session.get(SCLicenseImpl.class,
				new Long(licenseId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByActive(boolean active) throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
		String finderMethodName = "findByActive";
		String[] finderParams = new String[] { Boolean.class.getName() };
		Object[] finderArgs = new Object[] { Boolean.valueOf(active) };

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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

				query.append("active_ = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

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

	public List findByActive(boolean active, int begin, int end)
		throws SystemException {
		return findByActive(active, begin, end, null);
	}

	public List findByActive(boolean active, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
		String finderMethodName = "findByActive";
		String[] finderParams = new String[] {
				Boolean.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				Boolean.valueOf(active),
				
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

				query.append("active_ = ?");

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

	public SCLicense findByActive_First(boolean active, OrderByComparator obc)
		throws NoSuchLicenseException, SystemException {
		List list = findByActive(active, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCLicense exists with the key {");

			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLicenseException(msg.toString());
		}
		else {
			return (SCLicense)list.get(0);
		}
	}

	public SCLicense findByActive_Last(boolean active, OrderByComparator obc)
		throws NoSuchLicenseException, SystemException {
		int count = countByActive(active);

		List list = findByActive(active, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCLicense exists with the key {");

			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLicenseException(msg.toString());
		}
		else {
			return (SCLicense)list.get(0);
		}
	}

	public SCLicense[] findByActive_PrevAndNext(long licenseId, boolean active,
		OrderByComparator obc) throws NoSuchLicenseException, SystemException {
		SCLicense scLicense = findByPrimaryKey(licenseId);

		int count = countByActive(active);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

			query.append("active_ = ?");

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

			q.setBoolean(queryPos++, active);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					scLicense);

			SCLicense[] array = new SCLicenseImpl[3];

			array[0] = (SCLicense)objArray[0];
			array[1] = (SCLicense)objArray[1];
			array[2] = (SCLicense)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByA_R(boolean active, boolean recommended)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
		String finderMethodName = "findByA_R";
		String[] finderParams = new String[] {
				Boolean.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				Boolean.valueOf(active), Boolean.valueOf(recommended)
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

				query.append("active_ = ?");

				query.append(" AND ");

				query.append("recommended = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setBoolean(queryPos++, active);

				q.setBoolean(queryPos++, recommended);

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

	public List findByA_R(boolean active, boolean recommended, int begin,
		int end) throws SystemException {
		return findByA_R(active, recommended, begin, end, null);
	}

	public List findByA_R(boolean active, boolean recommended, int begin,
		int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
		String finderMethodName = "findByA_R";
		String[] finderParams = new String[] {
				Boolean.class.getName(), Boolean.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				Boolean.valueOf(active), Boolean.valueOf(recommended),
				
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

				query.append("active_ = ?");

				query.append(" AND ");

				query.append("recommended = ?");

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

				q.setBoolean(queryPos++, active);

				q.setBoolean(queryPos++, recommended);

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

	public SCLicense findByA_R_First(boolean active, boolean recommended,
		OrderByComparator obc) throws NoSuchLicenseException, SystemException {
		List list = findByA_R(active, recommended, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCLicense exists with the key {");

			msg.append("active=" + active);

			msg.append(", ");
			msg.append("recommended=" + recommended);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLicenseException(msg.toString());
		}
		else {
			return (SCLicense)list.get(0);
		}
	}

	public SCLicense findByA_R_Last(boolean active, boolean recommended,
		OrderByComparator obc) throws NoSuchLicenseException, SystemException {
		int count = countByA_R(active, recommended);

		List list = findByA_R(active, recommended, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No SCLicense exists with the key {");

			msg.append("active=" + active);

			msg.append(", ");
			msg.append("recommended=" + recommended);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLicenseException(msg.toString());
		}
		else {
			return (SCLicense)list.get(0);
		}
	}

	public SCLicense[] findByA_R_PrevAndNext(long licenseId, boolean active,
		boolean recommended, OrderByComparator obc)
		throws NoSuchLicenseException, SystemException {
		SCLicense scLicense = findByPrimaryKey(licenseId);

		int count = countByA_R(active, recommended);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

			query.append("active_ = ?");

			query.append(" AND ");

			query.append("recommended = ?");

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

			q.setBoolean(queryPos++, active);

			q.setBoolean(queryPos++, recommended);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					scLicense);

			SCLicense[] array = new SCLicenseImpl[3];

			array[0] = (SCLicense)objArray[0];
			array[1] = (SCLicense)objArray[1];
			array[2] = (SCLicense)objArray[2];

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
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense ");

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

	public void removeByActive(boolean active) throws SystemException {
		Iterator itr = findByActive(active).iterator();

		while (itr.hasNext()) {
			SCLicense scLicense = (SCLicense)itr.next();

			remove(scLicense);
		}
	}

	public void removeByA_R(boolean active, boolean recommended)
		throws SystemException {
		Iterator itr = findByA_R(active, recommended).iterator();

		while (itr.hasNext()) {
			SCLicense scLicense = (SCLicense)itr.next();

			remove(scLicense);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((SCLicense)itr.next());
		}
	}

	public int countByActive(boolean active) throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
		String finderMethodName = "countByActive";
		String[] finderParams = new String[] { Boolean.class.getName() };
		Object[] finderArgs = new Object[] { Boolean.valueOf(active) };

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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

				query.append("active_ = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

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

	public int countByA_R(boolean active, boolean recommended)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
		String finderMethodName = "countByA_R";
		String[] finderParams = new String[] {
				Boolean.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				Boolean.valueOf(active), Boolean.valueOf(recommended)
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
					"FROM com.liferay.portlet.softwarecatalog.model.SCLicense WHERE ");

				query.append("active_ = ?");

				query.append(" AND ");

				query.append("recommended = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setBoolean(queryPos++, active);

				q.setBoolean(queryPos++, recommended);

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
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED;
		String finderClassName = SCLicense.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.softwarecatalog.model.SCLicense");

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

	public List getSCProductEntries(long pk)
		throws NoSuchLicenseException, SystemException {
		return getSCProductEntries(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getSCProductEntries(long pk, int begin, int end)
		throws NoSuchLicenseException, SystemException {
		return getSCProductEntries(pk, begin, end, null);
	}

	public List getSCProductEntries(long pk, int begin, int end,
		OrderByComparator obc) throws NoSuchLicenseException, SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED_SCLICENSES_SCPRODUCTENTRIES;
		String finderClassName = "SCLicenses_SCProductEntries";
		String finderMethodName = "getSCProductEntries";
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

				sm.append(_SQL_GETSCPRODUCTENTRIES);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("SCProductEntry.modifiedDate DESC, ");
					sm.append("SCProductEntry.name DESC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("SCProductEntry",
					com.liferay.portlet.softwarecatalog.model.impl.SCProductEntryImpl.class);

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

	public int getSCProductEntriesSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED_SCLICENSES_SCPRODUCTENTRIES;
		String finderClassName = "SCLicenses_SCProductEntries";
		String finderMethodName = "getSCProductEntriesSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETSCPRODUCTENTRIESSIZE);

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

	public boolean containsSCProductEntry(long pk, long scProductEntryPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = SCLicenseModelImpl.CACHE_ENABLED_SCLICENSES_SCPRODUCTENTRIES;
		String finderClassName = "SCLicenses_SCProductEntries";
		String finderMethodName = "containsSCProductEntries";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(pk),
				
				new Long(scProductEntryPK)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsSCProductEntry.contains(
							pk, scProductEntryPK));

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

	public boolean containsSCProductEntries(long pk) throws SystemException {
		if (getSCProductEntriesSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addSCProductEntry(long pk, long scProductEntryPK)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			addSCProductEntry.add(pk, scProductEntryPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void addSCProductEntry(long pk,
		com.liferay.portlet.softwarecatalog.model.SCProductEntry scProductEntry)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			addSCProductEntry.add(pk, scProductEntry.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void addSCProductEntries(long pk, long[] scProductEntryPKs)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			for (int i = 0; i < scProductEntryPKs.length; i++) {
				addSCProductEntry.add(pk, scProductEntryPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void addSCProductEntries(long pk, List scProductEntries)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			for (int i = 0; i < scProductEntries.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCProductEntry scProductEntry =
					(com.liferay.portlet.softwarecatalog.model.SCProductEntry)scProductEntries.get(i);

				addSCProductEntry.add(pk, scProductEntry.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void clearSCProductEntries(long pk)
		throws NoSuchLicenseException, SystemException {
		try {
			clearSCProductEntries.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void removeSCProductEntry(long pk, long scProductEntryPK)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			removeSCProductEntry.remove(pk, scProductEntryPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void removeSCProductEntry(long pk,
		com.liferay.portlet.softwarecatalog.model.SCProductEntry scProductEntry)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			removeSCProductEntry.remove(pk, scProductEntry.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void removeSCProductEntries(long pk, long[] scProductEntryPKs)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			for (int i = 0; i < scProductEntryPKs.length; i++) {
				removeSCProductEntry.remove(pk, scProductEntryPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void removeSCProductEntries(long pk, List scProductEntries)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			for (int i = 0; i < scProductEntries.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCProductEntry scProductEntry =
					(com.liferay.portlet.softwarecatalog.model.SCProductEntry)scProductEntries.get(i);

				removeSCProductEntry.remove(pk, scProductEntry.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void setSCProductEntries(long pk, long[] scProductEntryPKs)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			clearSCProductEntries.clear(pk);

			for (int i = 0; i < scProductEntryPKs.length; i++) {
				addSCProductEntry.add(pk, scProductEntryPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	public void setSCProductEntries(long pk, List scProductEntries)
		throws NoSuchLicenseException, 
			com.liferay.portlet.softwarecatalog.NoSuchProductEntryException, 
			SystemException {
		try {
			clearSCProductEntries.clear(pk);

			for (int i = 0; i < scProductEntries.size(); i++) {
				com.liferay.portlet.softwarecatalog.model.SCProductEntry scProductEntry =
					(com.liferay.portlet.softwarecatalog.model.SCProductEntry)scProductEntries.get(i);

				addSCProductEntry.add(pk, scProductEntry.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("SCLicenses_SCProductEntries");
		}
	}

	protected void initDao() {
		containsSCProductEntry = new ContainsSCProductEntry(this);

		addSCProductEntry = new AddSCProductEntry(this);
		clearSCProductEntries = new ClearSCProductEntries(this);
		removeSCProductEntry = new RemoveSCProductEntry(this);
	}

	protected ContainsSCProductEntry containsSCProductEntry;
	protected AddSCProductEntry addSCProductEntry;
	protected ClearSCProductEntries clearSCProductEntries;
	protected RemoveSCProductEntry removeSCProductEntry;

	protected class ContainsSCProductEntry extends MappingSqlQuery {
		protected ContainsSCProductEntry(
			SCLicensePersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSSCPRODUCTENTRY);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long licenseId, long productEntryId) {
			List results = execute(new Object[] {
						new Long(licenseId), new Long(productEntryId)
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

	protected class AddSCProductEntry extends SqlUpdate {
		protected AddSCProductEntry(SCLicensePersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO SCLicenses_SCProductEntries (licenseId, productEntryId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long licenseId, long productEntryId) {
			if (!_persistenceImpl.containsSCProductEntry.contains(licenseId,
						productEntryId)) {
				update(new Object[] {
						new Long(licenseId), new Long(productEntryId)
					});
			}
		}

		private SCLicensePersistenceImpl _persistenceImpl;
	}

	protected class ClearSCProductEntries extends SqlUpdate {
		protected ClearSCProductEntries(
			SCLicensePersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM SCLicenses_SCProductEntries WHERE licenseId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long licenseId) {
			update(new Object[] { new Long(licenseId) });
		}
	}

	protected class RemoveSCProductEntry extends SqlUpdate {
		protected RemoveSCProductEntry(SCLicensePersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM SCLicenses_SCProductEntries WHERE licenseId = ? AND productEntryId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long licenseId, long productEntryId) {
			update(new Object[] { new Long(licenseId), new Long(productEntryId) });
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

	private static final String _SQL_GETSCPRODUCTENTRIES = "SELECT {SCProductEntry.*} FROM SCProductEntry INNER JOIN SCLicenses_SCProductEntries ON (SCLicenses_SCProductEntries.productEntryId = SCProductEntry.productEntryId) WHERE (SCLicenses_SCProductEntries.licenseId = ?)";
	private static final String _SQL_GETSCPRODUCTENTRIESSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM SCLicenses_SCProductEntries WHERE licenseId = ?";
	private static final String _SQL_CONTAINSSCPRODUCTENTRY = "SELECT COUNT(*) AS COUNT_VALUE FROM SCLicenses_SCProductEntries WHERE licenseId = ? AND productEntryId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.softwarecatalog.model.SCLicense"));
	private static Log _log = LogFactory.getLog(SCLicensePersistenceImpl.class);
}
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

import com.liferay.portal.NoSuchOrganizationException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.model.impl.OrganizationModelImpl;
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
 * <a href="OrganizationPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrganizationPersistenceImpl extends BasePersistence
	implements OrganizationPersistence {
	public Organization create(long organizationId) {
		Organization organization = new OrganizationImpl();

		organization.setNew(true);
		organization.setPrimaryKey(organizationId);

		return organization;
	}

	public Organization remove(long organizationId)
		throws NoSuchOrganizationException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Organization organization = (Organization)session.get(OrganizationImpl.class,
					new Long(organizationId));

			if (organization == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Organization exists with the primary key " +
						organizationId);
				}

				throw new NoSuchOrganizationException(
					"No Organization exists with the primary key " +
					organizationId);
			}

			return remove(organization);
		}
		catch (NoSuchOrganizationException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Organization remove(Organization organization)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(organization);
		}

		organization = removeImpl(organization);

		if (listener != null) {
			listener.onAfterRemove(organization);
		}

		return organization;
	}

	protected Organization removeImpl(Organization organization)
		throws SystemException {
		try {
			clearGroups.clear(organization.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}

		try {
			clearUsers.clear(organization.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("Users_Orgs");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(organization);

			session.flush();

			return organization;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Organization.class.getName());
		}
	}

	public Organization update(Organization organization)
		throws SystemException {
		return update(organization, false);
	}

	public Organization update(Organization organization, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = organization.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(organization);
			}
			else {
				listener.onBeforeUpdate(organization);
			}
		}

		organization = updateImpl(organization, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(organization);
			}
			else {
				listener.onAfterUpdate(organization);
			}
		}

		return organization;
	}

	public Organization updateImpl(
		com.liferay.portal.model.Organization organization, boolean merge)
		throws SystemException {
		FinderCache.clearCache("Groups_Orgs");
		FinderCache.clearCache("Users_Orgs");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(organization);
			}
			else {
				if (organization.isNew()) {
					session.save(organization);
				}
			}

			session.flush();

			organization.setNew(false);

			return organization;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Organization.class.getName());
		}
	}

	public Organization findByPrimaryKey(long organizationId)
		throws NoSuchOrganizationException, SystemException {
		Organization organization = fetchByPrimaryKey(organizationId);

		if (organization == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Organization exists with the primary key " +
					organizationId);
			}

			throw new NoSuchOrganizationException(
				"No Organization exists with the primary key " +
				organizationId);
		}

		return organization;
	}

	public Organization fetchByPrimaryKey(long organizationId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Organization)session.get(OrganizationImpl.class,
				new Long(organizationId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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
					"FROM com.liferay.portal.model.Organization WHERE ");

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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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
					"FROM com.liferay.portal.model.Organization WHERE ");

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

	public Organization findByCompanyId_First(long companyId,
		OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrganizationException(msg.toString());
		}
		else {
			return (Organization)list.get(0);
		}
	}

	public Organization findByCompanyId_Last(long companyId,
		OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		int count = countByCompanyId(companyId);

		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrganizationException(msg.toString());
		}
		else {
			return (Organization)list.get(0);
		}
	}

	public Organization[] findByCompanyId_PrevAndNext(long organizationId,
		long companyId, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		Organization organization = findByPrimaryKey(organizationId);

		int count = countByCompanyId(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Organization WHERE ");

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
					organization);

			Organization[] array = new OrganizationImpl[3];

			array[0] = (Organization)objArray[0];
			array[1] = (Organization)objArray[1];
			array[2] = (Organization)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByLocations(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
		String finderMethodName = "findByLocations";
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
					"FROM com.liferay.portal.model.Organization WHERE ");

				query.append("companyId = ?");

				query.append(" AND parentOrganizationId != 0 ");

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

	public List findByLocations(long companyId, int begin, int end)
		throws SystemException {
		return findByLocations(companyId, begin, end, null);
	}

	public List findByLocations(long companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
		String finderMethodName = "findByLocations";
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
					"FROM com.liferay.portal.model.Organization WHERE ");

				query.append("companyId = ?");

				query.append(" AND parentOrganizationId != 0 ");

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

	public Organization findByLocations_First(long companyId,
		OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		List list = findByLocations(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrganizationException(msg.toString());
		}
		else {
			return (Organization)list.get(0);
		}
	}

	public Organization findByLocations_Last(long companyId,
		OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		int count = countByLocations(companyId);

		List list = findByLocations(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrganizationException(msg.toString());
		}
		else {
			return (Organization)list.get(0);
		}
	}

	public Organization[] findByLocations_PrevAndNext(long organizationId,
		long companyId, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		Organization organization = findByPrimaryKey(organizationId);

		int count = countByLocations(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Organization WHERE ");

			query.append("companyId = ?");

			query.append(" AND parentOrganizationId != 0 ");

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
					organization);

			Organization[] array = new OrganizationImpl[3];

			array[0] = (Organization)objArray[0];
			array[1] = (Organization)objArray[1];
			array[2] = (Organization)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByC_P(long companyId, long parentOrganizationId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
		String finderMethodName = "findByC_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(parentOrganizationId)
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
					"FROM com.liferay.portal.model.Organization WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("parentOrganizationId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, parentOrganizationId);

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

	public List findByC_P(long companyId, long parentOrganizationId, int begin,
		int end) throws SystemException {
		return findByC_P(companyId, parentOrganizationId, begin, end, null);
	}

	public List findByC_P(long companyId, long parentOrganizationId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
		String finderMethodName = "findByC_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(parentOrganizationId),
				
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
					"FROM com.liferay.portal.model.Organization WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("parentOrganizationId = ?");

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

				q.setLong(queryPos++, parentOrganizationId);

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

	public Organization findByC_P_First(long companyId,
		long parentOrganizationId, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		List list = findByC_P(companyId, parentOrganizationId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("parentOrganizationId=" + parentOrganizationId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrganizationException(msg.toString());
		}
		else {
			return (Organization)list.get(0);
		}
	}

	public Organization findByC_P_Last(long companyId,
		long parentOrganizationId, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		int count = countByC_P(companyId, parentOrganizationId);

		List list = findByC_P(companyId, parentOrganizationId, count - 1,
				count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("parentOrganizationId=" + parentOrganizationId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrganizationException(msg.toString());
		}
		else {
			return (Organization)list.get(0);
		}
	}

	public Organization[] findByC_P_PrevAndNext(long organizationId,
		long companyId, long parentOrganizationId, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		Organization organization = findByPrimaryKey(organizationId);

		int count = countByC_P(companyId, parentOrganizationId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Organization WHERE ");

			query.append("companyId = ?");

			query.append(" AND ");

			query.append("parentOrganizationId = ?");

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

			q.setLong(queryPos++, parentOrganizationId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					organization);

			Organization[] array = new OrganizationImpl[3];

			array[0] = (Organization)objArray[0];
			array[1] = (Organization)objArray[1];
			array[2] = (Organization)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Organization findByC_N(long companyId, String name)
		throws NoSuchOrganizationException, SystemException {
		Organization organization = fetchByC_N(companyId, name);

		if (organization == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Organization exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchOrganizationException(msg.toString());
		}

		return organization;
	}

	public Organization fetchByC_N(long companyId, String name)
		throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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

				query.append(
					"FROM com.liferay.portal.model.Organization WHERE ");

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
					return (Organization)list.get(0);
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
				return (Organization)list.get(0);
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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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

				query.append("FROM com.liferay.portal.model.Organization ");

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
			Organization organization = (Organization)itr.next();

			remove(organization);
		}
	}

	public void removeByLocations(long companyId) throws SystemException {
		Iterator itr = findByLocations(companyId).iterator();

		while (itr.hasNext()) {
			Organization organization = (Organization)itr.next();

			remove(organization);
		}
	}

	public void removeByC_P(long companyId, long parentOrganizationId)
		throws SystemException {
		Iterator itr = findByC_P(companyId, parentOrganizationId).iterator();

		while (itr.hasNext()) {
			Organization organization = (Organization)itr.next();

			remove(organization);
		}
	}

	public void removeByC_N(long companyId, String name)
		throws NoSuchOrganizationException, SystemException {
		Organization organization = findByC_N(companyId, name);

		remove(organization);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Organization)itr.next());
		}
	}

	public int countByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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
					"FROM com.liferay.portal.model.Organization WHERE ");

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

	public int countByLocations(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
		String finderMethodName = "countByLocations";
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
					"FROM com.liferay.portal.model.Organization WHERE ");

				query.append("companyId = ?");

				query.append(" AND parentOrganizationId != 0 ");

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

	public int countByC_P(long companyId, long parentOrganizationId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
		String finderMethodName = "countByC_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId), new Long(parentOrganizationId)
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
					"FROM com.liferay.portal.model.Organization WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				query.append("parentOrganizationId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				q.setLong(queryPos++, parentOrganizationId);

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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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
				query.append(
					"FROM com.liferay.portal.model.Organization WHERE ");

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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED;
		String finderClassName = Organization.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Organization");

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
		throws NoSuchOrganizationException, SystemException {
		return getGroups(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getGroups(long pk, int begin, int end)
		throws NoSuchOrganizationException, SystemException {
		return getGroups(pk, begin, end, null);
	}

	public List getGroups(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED_GROUPS_ORGS;
		String finderClassName = "Groups_Orgs";
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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED_GROUPS_ORGS;
		String finderClassName = "Groups_Orgs";
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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED_GROUPS_ORGS;
		String finderClassName = "Groups_Orgs";
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
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			addGroup.add(pk, groupPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void addGroup(long pk, com.liferay.portal.model.Group group)
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			addGroup.add(pk, group.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void addGroups(long pk, long[] groupPKs)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void addGroups(long pk, List groups)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void clearGroups(long pk)
		throws NoSuchOrganizationException, SystemException {
		try {
			clearGroups.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeGroup(long pk, long groupPK)
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			removeGroup.remove(pk, groupPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchGroupException, SystemException {
		try {
			removeGroup.remove(pk, group.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeGroups(long pk, long[] groupPKs)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void removeGroups(long pk, List groups)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void setGroups(long pk, long[] groupPKs)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public void setGroups(long pk, List groups)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Groups_Orgs");
		}
	}

	public List getUsers(long pk)
		throws NoSuchOrganizationException, SystemException {
		return getUsers(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getUsers(long pk, int begin, int end)
		throws NoSuchOrganizationException, SystemException {
		return getUsers(pk, begin, end, null);
	}

	public List getUsers(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchOrganizationException, SystemException {
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED_USERS_ORGS;
		String finderClassName = "Users_Orgs";
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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED_USERS_ORGS;
		String finderClassName = "Users_Orgs";
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
		boolean finderClassNameCacheEnabled = OrganizationModelImpl.CACHE_ENABLED_USERS_ORGS;
		String finderClassName = "Users_Orgs";
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
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			addUser.add(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void addUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			addUser.add(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void addUsers(long pk, long[] userPKs)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void addUsers(long pk, List users)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void clearUsers(long pk)
		throws NoSuchOrganizationException, SystemException {
		try {
			clearUsers.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void removeUser(long pk, long userPK)
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			removeUser.remove(pk, userPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void removeUser(long pk, com.liferay.portal.model.User user)
		throws NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException, SystemException {
		try {
			removeUser.remove(pk, user.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void removeUsers(long pk, long[] userPKs)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void removeUsers(long pk, List users)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void setUsers(long pk, long[] userPKs)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Users_Orgs");
		}
	}

	public void setUsers(long pk, List users)
		throws NoSuchOrganizationException, 
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
			FinderCache.clearCache("Users_Orgs");
		}
	}

	protected void initDao() {
		containsGroup = new ContainsGroup(this);

		addGroup = new AddGroup(this);
		clearGroups = new ClearGroups(this);
		removeGroup = new RemoveGroup(this);

		containsUser = new ContainsUser(this);

		addUser = new AddUser(this);
		clearUsers = new ClearUsers(this);
		removeUser = new RemoveUser(this);
	}

	protected ContainsGroup containsGroup;
	protected AddGroup addGroup;
	protected ClearGroups clearGroups;
	protected RemoveGroup removeGroup;
	protected ContainsUser containsUser;
	protected AddUser addUser;
	protected ClearUsers clearUsers;
	protected RemoveUser removeUser;

	protected class ContainsGroup extends MappingSqlQuery {
		protected ContainsGroup(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSGROUP);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long organizationId, long groupId) {
			List results = execute(new Object[] {
						new Long(organizationId), new Long(groupId)
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
		protected AddGroup(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Groups_Orgs (organizationId, groupId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long organizationId, long groupId) {
			if (!_persistenceImpl.containsGroup.contains(organizationId, groupId)) {
				update(new Object[] { new Long(organizationId), new Long(
							groupId) });
			}
		}

		private OrganizationPersistenceImpl _persistenceImpl;
	}

	protected class ClearGroups extends SqlUpdate {
		protected ClearGroups(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Orgs WHERE organizationId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long organizationId) {
			update(new Object[] { new Long(organizationId) });
		}
	}

	protected class RemoveGroup extends SqlUpdate {
		protected RemoveGroup(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Groups_Orgs WHERE organizationId = ? AND groupId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long organizationId, long groupId) {
			update(new Object[] { new Long(organizationId), new Long(groupId) });
		}
	}

	protected class ContainsUser extends MappingSqlQuery {
		protected ContainsUser(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSUSER);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long organizationId, long userId) {
			List results = execute(new Object[] {
						new Long(organizationId), new Long(userId)
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
		protected AddUser(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO Users_Orgs (organizationId, userId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long organizationId, long userId) {
			if (!_persistenceImpl.containsUser.contains(organizationId, userId)) {
				update(new Object[] { new Long(organizationId), new Long(userId) });
			}
		}

		private OrganizationPersistenceImpl _persistenceImpl;
	}

	protected class ClearUsers extends SqlUpdate {
		protected ClearUsers(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_Orgs WHERE organizationId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long organizationId) {
			update(new Object[] { new Long(organizationId) });
		}
	}

	protected class RemoveUser extends SqlUpdate {
		protected RemoveUser(OrganizationPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM Users_Orgs WHERE organizationId = ? AND userId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long organizationId, long userId) {
			update(new Object[] { new Long(organizationId), new Long(userId) });
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

	private static final String _SQL_GETGROUPS = "SELECT {Group_.*} FROM Group_ INNER JOIN Groups_Orgs ON (Groups_Orgs.groupId = Group_.groupId) WHERE (Groups_Orgs.organizationId = ?)";
	private static final String _SQL_GETGROUPSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Orgs WHERE organizationId = ?";
	private static final String _SQL_CONTAINSGROUP = "SELECT COUNT(*) AS COUNT_VALUE FROM Groups_Orgs WHERE organizationId = ? AND groupId = ?";
	private static final String _SQL_GETUSERS = "SELECT {User_.*} FROM User_ INNER JOIN Users_Orgs ON (Users_Orgs.userId = User_.userId) WHERE (Users_Orgs.organizationId = ?)";
	private static final String _SQL_GETUSERSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_Orgs WHERE organizationId = ?";
	private static final String _SQL_CONTAINSUSER = "SELECT COUNT(*) AS COUNT_VALUE FROM Users_Orgs WHERE organizationId = ? AND userId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Organization"));
	private static Log _log = LogFactory.getLog(OrganizationPersistenceImpl.class);
}
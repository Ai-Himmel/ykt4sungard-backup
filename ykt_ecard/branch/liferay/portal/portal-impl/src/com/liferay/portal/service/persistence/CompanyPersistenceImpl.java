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

import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.model.impl.CompanyModelImpl;
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
 * <a href="CompanyPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CompanyPersistenceImpl extends BasePersistence
	implements CompanyPersistence {
	public Company create(long companyId) {
		Company company = new CompanyImpl();

		company.setNew(true);
		company.setPrimaryKey(companyId);

		return company;
	}

	public Company remove(long companyId)
		throws NoSuchCompanyException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Company company = (Company)session.get(CompanyImpl.class,
					new Long(companyId));

			if (company == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Company exists with the primary key " +
						companyId);
				}

				throw new NoSuchCompanyException(
					"No Company exists with the primary key " + companyId);
			}

			return remove(company);
		}
		catch (NoSuchCompanyException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Company remove(Company company) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(company);
		}

		company = removeImpl(company);

		if (listener != null) {
			listener.onAfterRemove(company);
		}

		return company;
	}

	protected Company removeImpl(Company company) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(company);

			session.flush();

			return company;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Company.class.getName());
		}
	}

	public Company update(Company company) throws SystemException {
		return update(company, false);
	}

	public Company update(Company company, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = company.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(company);
			}
			else {
				listener.onBeforeUpdate(company);
			}
		}

		company = updateImpl(company, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(company);
			}
			else {
				listener.onAfterUpdate(company);
			}
		}

		return company;
	}

	public Company updateImpl(com.liferay.portal.model.Company company,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(company);
			}
			else {
				if (company.isNew()) {
					session.save(company);
				}
			}

			session.flush();

			company.setNew(false);

			return company;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Company.class.getName());
		}
	}

	public Company findByPrimaryKey(long companyId)
		throws NoSuchCompanyException, SystemException {
		Company company = fetchByPrimaryKey(companyId);

		if (company == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Company exists with the primary key " +
					companyId);
			}

			throw new NoSuchCompanyException(
				"No Company exists with the primary key " + companyId);
		}

		return company;
	}

	public Company fetchByPrimaryKey(long companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Company)session.get(CompanyImpl.class, new Long(companyId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Company findByWebId(String webId)
		throws NoSuchCompanyException, SystemException {
		Company company = fetchByWebId(webId);

		if (company == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Company exists with the key {");

			msg.append("webId=" + webId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchCompanyException(msg.toString());
		}

		return company;
	}

	public Company fetchByWebId(String webId) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "fetchByWebId";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { webId };

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

				query.append("FROM com.liferay.portal.model.Company WHERE ");

				if (webId == null) {
					query.append("webId IS NULL");
				}
				else {
					query.append("webId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (webId != null) {
					q.setString(queryPos++, webId);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Company)list.get(0);
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
				return (Company)list.get(0);
			}
		}
	}

	public Company findByVirtualHost(String virtualHost)
		throws NoSuchCompanyException, SystemException {
		Company company = fetchByVirtualHost(virtualHost);

		if (company == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Company exists with the key {");

			msg.append("virtualHost=" + virtualHost);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchCompanyException(msg.toString());
		}

		return company;
	}

	public Company fetchByVirtualHost(String virtualHost)
		throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "fetchByVirtualHost";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { virtualHost };

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

				query.append("FROM com.liferay.portal.model.Company WHERE ");

				if (virtualHost == null) {
					query.append("virtualHost IS NULL");
				}
				else {
					query.append("virtualHost = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (virtualHost != null) {
					q.setString(queryPos++, virtualHost);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Company)list.get(0);
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
				return (Company)list.get(0);
			}
		}
	}

	public Company findByMx(String mx)
		throws NoSuchCompanyException, SystemException {
		Company company = fetchByMx(mx);

		if (company == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Company exists with the key {");

			msg.append("mx=" + mx);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchCompanyException(msg.toString());
		}

		return company;
	}

	public Company fetchByMx(String mx) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "fetchByMx";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { mx };

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

				query.append("FROM com.liferay.portal.model.Company WHERE ");

				if (mx == null) {
					query.append("mx IS NULL");
				}
				else {
					query.append("mx = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (mx != null) {
					q.setString(queryPos++, mx);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Company)list.get(0);
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
				return (Company)list.get(0);
			}
		}
	}

	public Company findByLogoId(long logoId)
		throws NoSuchCompanyException, SystemException {
		Company company = fetchByLogoId(logoId);

		if (company == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Company exists with the key {");

			msg.append("logoId=" + logoId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchCompanyException(msg.toString());
		}

		return company;
	}

	public Company fetchByLogoId(long logoId) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "fetchByLogoId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(logoId) };

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

				query.append("FROM com.liferay.portal.model.Company WHERE ");

				query.append("logoId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, logoId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Company)list.get(0);
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
				return (Company)list.get(0);
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
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
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

				query.append("FROM com.liferay.portal.model.Company ");

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

	public void removeByWebId(String webId)
		throws NoSuchCompanyException, SystemException {
		Company company = findByWebId(webId);

		remove(company);
	}

	public void removeByVirtualHost(String virtualHost)
		throws NoSuchCompanyException, SystemException {
		Company company = findByVirtualHost(virtualHost);

		remove(company);
	}

	public void removeByMx(String mx)
		throws NoSuchCompanyException, SystemException {
		Company company = findByMx(mx);

		remove(company);
	}

	public void removeByLogoId(long logoId)
		throws NoSuchCompanyException, SystemException {
		Company company = findByLogoId(logoId);

		remove(company);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Company)itr.next());
		}
	}

	public int countByWebId(String webId) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "countByWebId";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { webId };

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
				query.append("FROM com.liferay.portal.model.Company WHERE ");

				if (webId == null) {
					query.append("webId IS NULL");
				}
				else {
					query.append("webId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (webId != null) {
					q.setString(queryPos++, webId);
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

	public int countByVirtualHost(String virtualHost) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "countByVirtualHost";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { virtualHost };

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
				query.append("FROM com.liferay.portal.model.Company WHERE ");

				if (virtualHost == null) {
					query.append("virtualHost IS NULL");
				}
				else {
					query.append("virtualHost = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (virtualHost != null) {
					q.setString(queryPos++, virtualHost);
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

	public int countByMx(String mx) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "countByMx";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { mx };

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
				query.append("FROM com.liferay.portal.model.Company WHERE ");

				if (mx == null) {
					query.append("mx IS NULL");
				}
				else {
					query.append("mx = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (mx != null) {
					q.setString(queryPos++, mx);
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

	public int countByLogoId(long logoId) throws SystemException {
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
		String finderMethodName = "countByLogoId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(logoId) };

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
				query.append("FROM com.liferay.portal.model.Company WHERE ");

				query.append("logoId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, logoId);

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
		boolean finderClassNameCacheEnabled = CompanyModelImpl.CACHE_ENABLED;
		String finderClassName = Company.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Company");

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
				"value.object.listener.com.liferay.portal.model.Company"));
	private static Log _log = LogFactory.getLog(CompanyPersistenceImpl.class);
}
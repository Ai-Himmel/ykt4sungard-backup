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

import com.liferay.portal.NoSuchServiceComponentException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.ServiceComponent;
import com.liferay.portal.model.impl.ServiceComponentImpl;
import com.liferay.portal.model.impl.ServiceComponentModelImpl;
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
 * <a href="ServiceComponentPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ServiceComponentPersistenceImpl extends BasePersistence
	implements ServiceComponentPersistence {
	public ServiceComponent create(long serviceComponentId) {
		ServiceComponent serviceComponent = new ServiceComponentImpl();

		serviceComponent.setNew(true);
		serviceComponent.setPrimaryKey(serviceComponentId);

		return serviceComponent;
	}

	public ServiceComponent remove(long serviceComponentId)
		throws NoSuchServiceComponentException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ServiceComponent serviceComponent = (ServiceComponent)session.get(ServiceComponentImpl.class,
					new Long(serviceComponentId));

			if (serviceComponent == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No ServiceComponent exists with the primary key " +
						serviceComponentId);
				}

				throw new NoSuchServiceComponentException(
					"No ServiceComponent exists with the primary key " +
					serviceComponentId);
			}

			return remove(serviceComponent);
		}
		catch (NoSuchServiceComponentException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ServiceComponent remove(ServiceComponent serviceComponent)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(serviceComponent);
		}

		serviceComponent = removeImpl(serviceComponent);

		if (listener != null) {
			listener.onAfterRemove(serviceComponent);
		}

		return serviceComponent;
	}

	protected ServiceComponent removeImpl(ServiceComponent serviceComponent)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(serviceComponent);

			session.flush();

			return serviceComponent;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ServiceComponent.class.getName());
		}
	}

	public ServiceComponent update(ServiceComponent serviceComponent)
		throws SystemException {
		return update(serviceComponent, false);
	}

	public ServiceComponent update(ServiceComponent serviceComponent,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = serviceComponent.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(serviceComponent);
			}
			else {
				listener.onBeforeUpdate(serviceComponent);
			}
		}

		serviceComponent = updateImpl(serviceComponent, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(serviceComponent);
			}
			else {
				listener.onAfterUpdate(serviceComponent);
			}
		}

		return serviceComponent;
	}

	public ServiceComponent updateImpl(
		com.liferay.portal.model.ServiceComponent serviceComponent,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(serviceComponent);
			}
			else {
				if (serviceComponent.isNew()) {
					session.save(serviceComponent);
				}
			}

			session.flush();

			serviceComponent.setNew(false);

			return serviceComponent;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ServiceComponent.class.getName());
		}
	}

	public ServiceComponent findByPrimaryKey(long serviceComponentId)
		throws NoSuchServiceComponentException, SystemException {
		ServiceComponent serviceComponent = fetchByPrimaryKey(serviceComponentId);

		if (serviceComponent == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ServiceComponent exists with the primary key " +
					serviceComponentId);
			}

			throw new NoSuchServiceComponentException(
				"No ServiceComponent exists with the primary key " +
				serviceComponentId);
		}

		return serviceComponent;
	}

	public ServiceComponent fetchByPrimaryKey(long serviceComponentId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (ServiceComponent)session.get(ServiceComponentImpl.class,
				new Long(serviceComponentId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByBuildNamespace(String buildNamespace)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
		String finderMethodName = "findByBuildNamespace";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { buildNamespace };

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
					"FROM com.liferay.portal.model.ServiceComponent WHERE ");

				if (buildNamespace == null) {
					query.append("buildNamespace IS NULL");
				}
				else {
					query.append("buildNamespace = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("buildNamespace DESC, ");
				query.append("buildNumber DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (buildNamespace != null) {
					q.setString(queryPos++, buildNamespace);
				}

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

	public List findByBuildNamespace(String buildNamespace, int begin, int end)
		throws SystemException {
		return findByBuildNamespace(buildNamespace, begin, end, null);
	}

	public List findByBuildNamespace(String buildNamespace, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
		String finderMethodName = "findByBuildNamespace";
		String[] finderParams = new String[] {
				String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				buildNamespace,
				
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
					"FROM com.liferay.portal.model.ServiceComponent WHERE ");

				if (buildNamespace == null) {
					query.append("buildNamespace IS NULL");
				}
				else {
					query.append("buildNamespace = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("buildNamespace DESC, ");
					query.append("buildNumber DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (buildNamespace != null) {
					q.setString(queryPos++, buildNamespace);
				}

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

	public ServiceComponent findByBuildNamespace_First(String buildNamespace,
		OrderByComparator obc)
		throws NoSuchServiceComponentException, SystemException {
		List list = findByBuildNamespace(buildNamespace, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ServiceComponent exists with the key {");

			msg.append("buildNamespace=" + buildNamespace);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchServiceComponentException(msg.toString());
		}
		else {
			return (ServiceComponent)list.get(0);
		}
	}

	public ServiceComponent findByBuildNamespace_Last(String buildNamespace,
		OrderByComparator obc)
		throws NoSuchServiceComponentException, SystemException {
		int count = countByBuildNamespace(buildNamespace);

		List list = findByBuildNamespace(buildNamespace, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ServiceComponent exists with the key {");

			msg.append("buildNamespace=" + buildNamespace);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchServiceComponentException(msg.toString());
		}
		else {
			return (ServiceComponent)list.get(0);
		}
	}

	public ServiceComponent[] findByBuildNamespace_PrevAndNext(
		long serviceComponentId, String buildNamespace, OrderByComparator obc)
		throws NoSuchServiceComponentException, SystemException {
		ServiceComponent serviceComponent = findByPrimaryKey(serviceComponentId);

		int count = countByBuildNamespace(buildNamespace);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portal.model.ServiceComponent WHERE ");

			if (buildNamespace == null) {
				query.append("buildNamespace IS NULL");
			}
			else {
				query.append("buildNamespace = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("buildNamespace DESC, ");
				query.append("buildNumber DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			if (buildNamespace != null) {
				q.setString(queryPos++, buildNamespace);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					serviceComponent);

			ServiceComponent[] array = new ServiceComponentImpl[3];

			array[0] = (ServiceComponent)objArray[0];
			array[1] = (ServiceComponent)objArray[1];
			array[2] = (ServiceComponent)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ServiceComponent findByBNS_BNU(String buildNamespace,
		long buildNumber)
		throws NoSuchServiceComponentException, SystemException {
		ServiceComponent serviceComponent = fetchByBNS_BNU(buildNamespace,
				buildNumber);

		if (serviceComponent == null) {
			StringMaker msg = new StringMaker();

			msg.append("No ServiceComponent exists with the key {");

			msg.append("buildNamespace=" + buildNamespace);

			msg.append(", ");
			msg.append("buildNumber=" + buildNumber);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchServiceComponentException(msg.toString());
		}

		return serviceComponent;
	}

	public ServiceComponent fetchByBNS_BNU(String buildNamespace,
		long buildNumber) throws SystemException {
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
		String finderMethodName = "fetchByBNS_BNU";
		String[] finderParams = new String[] {
				String.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { buildNamespace, new Long(buildNumber) };

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
					"FROM com.liferay.portal.model.ServiceComponent WHERE ");

				if (buildNamespace == null) {
					query.append("buildNamespace IS NULL");
				}
				else {
					query.append("buildNamespace = ?");
				}

				query.append(" AND ");

				query.append("buildNumber = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("buildNamespace DESC, ");
				query.append("buildNumber DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (buildNamespace != null) {
					q.setString(queryPos++, buildNamespace);
				}

				q.setLong(queryPos++, buildNumber);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (ServiceComponent)list.get(0);
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
				return (ServiceComponent)list.get(0);
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
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
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

				query.append("FROM com.liferay.portal.model.ServiceComponent ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("buildNamespace DESC, ");
					query.append("buildNumber DESC");
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

	public void removeByBuildNamespace(String buildNamespace)
		throws SystemException {
		Iterator itr = findByBuildNamespace(buildNamespace).iterator();

		while (itr.hasNext()) {
			ServiceComponent serviceComponent = (ServiceComponent)itr.next();

			remove(serviceComponent);
		}
	}

	public void removeByBNS_BNU(String buildNamespace, long buildNumber)
		throws NoSuchServiceComponentException, SystemException {
		ServiceComponent serviceComponent = findByBNS_BNU(buildNamespace,
				buildNumber);

		remove(serviceComponent);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((ServiceComponent)itr.next());
		}
	}

	public int countByBuildNamespace(String buildNamespace)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
		String finderMethodName = "countByBuildNamespace";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { buildNamespace };

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
					"FROM com.liferay.portal.model.ServiceComponent WHERE ");

				if (buildNamespace == null) {
					query.append("buildNamespace IS NULL");
				}
				else {
					query.append("buildNamespace = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (buildNamespace != null) {
					q.setString(queryPos++, buildNamespace);
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

	public int countByBNS_BNU(String buildNamespace, long buildNumber)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
		String finderMethodName = "countByBNS_BNU";
		String[] finderParams = new String[] {
				String.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { buildNamespace, new Long(buildNumber) };

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
					"FROM com.liferay.portal.model.ServiceComponent WHERE ");

				if (buildNamespace == null) {
					query.append("buildNamespace IS NULL");
				}
				else {
					query.append("buildNamespace = ?");
				}

				query.append(" AND ");

				query.append("buildNumber = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (buildNamespace != null) {
					q.setString(queryPos++, buildNamespace);
				}

				q.setLong(queryPos++, buildNumber);

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
		boolean finderClassNameCacheEnabled = ServiceComponentModelImpl.CACHE_ENABLED;
		String finderClassName = ServiceComponent.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.ServiceComponent");

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
				"value.object.listener.com.liferay.portal.model.ServiceComponent"));
	private static Log _log = LogFactory.getLog(ServiceComponentPersistenceImpl.class);
}
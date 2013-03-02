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

import com.liferay.portal.NoSuchRegionException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.Region;
import com.liferay.portal.model.impl.RegionImpl;
import com.liferay.portal.model.impl.RegionModelImpl;
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
 * <a href="RegionPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RegionPersistenceImpl extends BasePersistence
	implements RegionPersistence {
	public Region create(long regionId) {
		Region region = new RegionImpl();

		region.setNew(true);
		region.setPrimaryKey(regionId);

		return region;
	}

	public Region remove(long regionId)
		throws NoSuchRegionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Region region = (Region)session.get(RegionImpl.class,
					new Long(regionId));

			if (region == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Region exists with the primary key " +
						regionId);
				}

				throw new NoSuchRegionException(
					"No Region exists with the primary key " + regionId);
			}

			return remove(region);
		}
		catch (NoSuchRegionException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Region remove(Region region) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(region);
		}

		region = removeImpl(region);

		if (listener != null) {
			listener.onAfterRemove(region);
		}

		return region;
	}

	protected Region removeImpl(Region region) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(region);

			session.flush();

			return region;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Region.class.getName());
		}
	}

	public Region update(Region region) throws SystemException {
		return update(region, false);
	}

	public Region update(Region region, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = region.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(region);
			}
			else {
				listener.onBeforeUpdate(region);
			}
		}

		region = updateImpl(region, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(region);
			}
			else {
				listener.onAfterUpdate(region);
			}
		}

		return region;
	}

	public Region updateImpl(com.liferay.portal.model.Region region,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(region);
			}
			else {
				if (region.isNew()) {
					session.save(region);
				}
			}

			session.flush();

			region.setNew(false);

			return region;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Region.class.getName());
		}
	}

	public Region findByPrimaryKey(long regionId)
		throws NoSuchRegionException, SystemException {
		Region region = fetchByPrimaryKey(regionId);

		if (region == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Region exists with the primary key " + regionId);
			}

			throw new NoSuchRegionException(
				"No Region exists with the primary key " + regionId);
		}

		return region;
	}

	public Region fetchByPrimaryKey(long regionId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Region)session.get(RegionImpl.class, new Long(regionId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCountryId(long countryId) throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
		String finderMethodName = "findByCountryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(countryId) };

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

				query.append("FROM com.liferay.portal.model.Region WHERE ");

				query.append("countryId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, countryId);

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

	public List findByCountryId(long countryId, int begin, int end)
		throws SystemException {
		return findByCountryId(countryId, begin, end, null);
	}

	public List findByCountryId(long countryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
		String finderMethodName = "findByCountryId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(countryId),
				
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

				query.append("FROM com.liferay.portal.model.Region WHERE ");

				query.append("countryId = ?");

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

				q.setLong(queryPos++, countryId);

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

	public Region findByCountryId_First(long countryId, OrderByComparator obc)
		throws NoSuchRegionException, SystemException {
		List list = findByCountryId(countryId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Region exists with the key {");

			msg.append("countryId=" + countryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchRegionException(msg.toString());
		}
		else {
			return (Region)list.get(0);
		}
	}

	public Region findByCountryId_Last(long countryId, OrderByComparator obc)
		throws NoSuchRegionException, SystemException {
		int count = countByCountryId(countryId);

		List list = findByCountryId(countryId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Region exists with the key {");

			msg.append("countryId=" + countryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchRegionException(msg.toString());
		}
		else {
			return (Region)list.get(0);
		}
	}

	public Region[] findByCountryId_PrevAndNext(long regionId, long countryId,
		OrderByComparator obc) throws NoSuchRegionException, SystemException {
		Region region = findByPrimaryKey(regionId);

		int count = countByCountryId(countryId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Region WHERE ");

			query.append("countryId = ?");

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

			q.setLong(queryPos++, countryId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, region);

			Region[] array = new RegionImpl[3];

			array[0] = (Region)objArray[0];
			array[1] = (Region)objArray[1];
			array[2] = (Region)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByActive(boolean active) throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
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

				query.append("FROM com.liferay.portal.model.Region WHERE ");

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
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
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

				query.append("FROM com.liferay.portal.model.Region WHERE ");

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

	public Region findByActive_First(boolean active, OrderByComparator obc)
		throws NoSuchRegionException, SystemException {
		List list = findByActive(active, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Region exists with the key {");

			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchRegionException(msg.toString());
		}
		else {
			return (Region)list.get(0);
		}
	}

	public Region findByActive_Last(boolean active, OrderByComparator obc)
		throws NoSuchRegionException, SystemException {
		int count = countByActive(active);

		List list = findByActive(active, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Region exists with the key {");

			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchRegionException(msg.toString());
		}
		else {
			return (Region)list.get(0);
		}
	}

	public Region[] findByActive_PrevAndNext(long regionId, boolean active,
		OrderByComparator obc) throws NoSuchRegionException, SystemException {
		Region region = findByPrimaryKey(regionId);

		int count = countByActive(active);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Region WHERE ");

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

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, region);

			Region[] array = new RegionImpl[3];

			array[0] = (Region)objArray[0];
			array[1] = (Region)objArray[1];
			array[2] = (Region)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByC_A(long countryId, boolean active)
		throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
		String finderMethodName = "findByC_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(countryId), Boolean.valueOf(active)
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

				query.append("FROM com.liferay.portal.model.Region WHERE ");

				query.append("countryId = ?");

				query.append(" AND ");

				query.append("active_ = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, countryId);

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

	public List findByC_A(long countryId, boolean active, int begin, int end)
		throws SystemException {
		return findByC_A(countryId, active, begin, end, null);
	}

	public List findByC_A(long countryId, boolean active, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
		String finderMethodName = "findByC_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(countryId), Boolean.valueOf(active),
				
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

				query.append("FROM com.liferay.portal.model.Region WHERE ");

				query.append("countryId = ?");

				query.append(" AND ");

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

				q.setLong(queryPos++, countryId);

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

	public Region findByC_A_First(long countryId, boolean active,
		OrderByComparator obc) throws NoSuchRegionException, SystemException {
		List list = findByC_A(countryId, active, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Region exists with the key {");

			msg.append("countryId=" + countryId);

			msg.append(", ");
			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchRegionException(msg.toString());
		}
		else {
			return (Region)list.get(0);
		}
	}

	public Region findByC_A_Last(long countryId, boolean active,
		OrderByComparator obc) throws NoSuchRegionException, SystemException {
		int count = countByC_A(countryId, active);

		List list = findByC_A(countryId, active, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Region exists with the key {");

			msg.append("countryId=" + countryId);

			msg.append(", ");
			msg.append("active=" + active);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchRegionException(msg.toString());
		}
		else {
			return (Region)list.get(0);
		}
	}

	public Region[] findByC_A_PrevAndNext(long regionId, long countryId,
		boolean active, OrderByComparator obc)
		throws NoSuchRegionException, SystemException {
		Region region = findByPrimaryKey(regionId);

		int count = countByC_A(countryId, active);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Region WHERE ");

			query.append("countryId = ?");

			query.append(" AND ");

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

			q.setLong(queryPos++, countryId);

			q.setBoolean(queryPos++, active);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, region);

			Region[] array = new RegionImpl[3];

			array[0] = (Region)objArray[0];
			array[1] = (Region)objArray[1];
			array[2] = (Region)objArray[2];

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
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
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

				query.append("FROM com.liferay.portal.model.Region ");

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

	public void removeByCountryId(long countryId) throws SystemException {
		Iterator itr = findByCountryId(countryId).iterator();

		while (itr.hasNext()) {
			Region region = (Region)itr.next();

			remove(region);
		}
	}

	public void removeByActive(boolean active) throws SystemException {
		Iterator itr = findByActive(active).iterator();

		while (itr.hasNext()) {
			Region region = (Region)itr.next();

			remove(region);
		}
	}

	public void removeByC_A(long countryId, boolean active)
		throws SystemException {
		Iterator itr = findByC_A(countryId, active).iterator();

		while (itr.hasNext()) {
			Region region = (Region)itr.next();

			remove(region);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Region)itr.next());
		}
	}

	public int countByCountryId(long countryId) throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
		String finderMethodName = "countByCountryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(countryId) };

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
				query.append("FROM com.liferay.portal.model.Region WHERE ");

				query.append("countryId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, countryId);

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

	public int countByActive(boolean active) throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
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
				query.append("FROM com.liferay.portal.model.Region WHERE ");

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

	public int countByC_A(long countryId, boolean active)
		throws SystemException {
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
		String finderMethodName = "countByC_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(countryId), Boolean.valueOf(active)
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
				query.append("FROM com.liferay.portal.model.Region WHERE ");

				query.append("countryId = ?");

				query.append(" AND ");

				query.append("active_ = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, countryId);

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
		boolean finderClassNameCacheEnabled = RegionModelImpl.CACHE_ENABLED;
		String finderClassName = Region.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Region");

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
				"value.object.listener.com.liferay.portal.model.Region"));
	private static Log _log = LogFactory.getLog(RegionPersistenceImpl.class);
}
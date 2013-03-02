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

import com.liferay.portal.NoSuchListTypeException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ListType;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.impl.ListTypeImpl;
import com.liferay.portal.model.impl.ListTypeModelImpl;
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
 * <a href="ListTypePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ListTypePersistenceImpl extends BasePersistence
	implements ListTypePersistence {
	public ListType create(int listTypeId) {
		ListType listType = new ListTypeImpl();

		listType.setNew(true);
		listType.setPrimaryKey(listTypeId);

		return listType;
	}

	public ListType remove(int listTypeId)
		throws NoSuchListTypeException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ListType listType = (ListType)session.get(ListTypeImpl.class,
					new Integer(listTypeId));

			if (listType == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No ListType exists with the primary key " +
						listTypeId);
				}

				throw new NoSuchListTypeException(
					"No ListType exists with the primary key " + listTypeId);
			}

			return remove(listType);
		}
		catch (NoSuchListTypeException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ListType remove(ListType listType) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(listType);
		}

		listType = removeImpl(listType);

		if (listener != null) {
			listener.onAfterRemove(listType);
		}

		return listType;
	}

	protected ListType removeImpl(ListType listType) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(listType);

			session.flush();

			return listType;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ListType.class.getName());
		}
	}

	public ListType update(ListType listType) throws SystemException {
		return update(listType, false);
	}

	public ListType update(ListType listType, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = listType.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(listType);
			}
			else {
				listener.onBeforeUpdate(listType);
			}
		}

		listType = updateImpl(listType, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(listType);
			}
			else {
				listener.onAfterUpdate(listType);
			}
		}

		return listType;
	}

	public ListType updateImpl(com.liferay.portal.model.ListType listType,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(listType);
			}
			else {
				if (listType.isNew()) {
					session.save(listType);
				}
			}

			session.flush();

			listType.setNew(false);

			return listType;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ListType.class.getName());
		}
	}

	public ListType findByPrimaryKey(int listTypeId)
		throws NoSuchListTypeException, SystemException {
		ListType listType = fetchByPrimaryKey(listTypeId);

		if (listType == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ListType exists with the primary key " +
					listTypeId);
			}

			throw new NoSuchListTypeException(
				"No ListType exists with the primary key " + listTypeId);
		}

		return listType;
	}

	public ListType fetchByPrimaryKey(int listTypeId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (ListType)session.get(ListTypeImpl.class,
				new Integer(listTypeId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByType(String type) throws SystemException {
		boolean finderClassNameCacheEnabled = ListTypeModelImpl.CACHE_ENABLED;
		String finderClassName = ListType.class.getName();
		String finderMethodName = "findByType";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { type };

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

				query.append("FROM com.liferay.portal.model.ListType WHERE ");

				if (type == null) {
					query.append("type_ IS NULL");
				}
				else {
					query.append("type_ = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (type != null) {
					q.setString(queryPos++, type);
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

	public List findByType(String type, int begin, int end)
		throws SystemException {
		return findByType(type, begin, end, null);
	}

	public List findByType(String type, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = ListTypeModelImpl.CACHE_ENABLED;
		String finderClassName = ListType.class.getName();
		String finderMethodName = "findByType";
		String[] finderParams = new String[] {
				String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				type,
				
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

				query.append("FROM com.liferay.portal.model.ListType WHERE ");

				if (type == null) {
					query.append("type_ IS NULL");
				}
				else {
					query.append("type_ = ?");
				}

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

				if (type != null) {
					q.setString(queryPos++, type);
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

	public ListType findByType_First(String type, OrderByComparator obc)
		throws NoSuchListTypeException, SystemException {
		List list = findByType(type, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ListType exists with the key {");

			msg.append("type=" + type);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchListTypeException(msg.toString());
		}
		else {
			return (ListType)list.get(0);
		}
	}

	public ListType findByType_Last(String type, OrderByComparator obc)
		throws NoSuchListTypeException, SystemException {
		int count = countByType(type);

		List list = findByType(type, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ListType exists with the key {");

			msg.append("type=" + type);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchListTypeException(msg.toString());
		}
		else {
			return (ListType)list.get(0);
		}
	}

	public ListType[] findByType_PrevAndNext(int listTypeId, String type,
		OrderByComparator obc) throws NoSuchListTypeException, SystemException {
		ListType listType = findByPrimaryKey(listTypeId);

		int count = countByType(type);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.ListType WHERE ");

			if (type == null) {
				query.append("type_ IS NULL");
			}
			else {
				query.append("type_ = ?");
			}

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

			if (type != null) {
				q.setString(queryPos++, type);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, listType);

			ListType[] array = new ListTypeImpl[3];

			array[0] = (ListType)objArray[0];
			array[1] = (ListType)objArray[1];
			array[2] = (ListType)objArray[2];

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
		boolean finderClassNameCacheEnabled = ListTypeModelImpl.CACHE_ENABLED;
		String finderClassName = ListType.class.getName();
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

				query.append("FROM com.liferay.portal.model.ListType ");

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

	public void removeByType(String type) throws SystemException {
		Iterator itr = findByType(type).iterator();

		while (itr.hasNext()) {
			ListType listType = (ListType)itr.next();

			remove(listType);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((ListType)itr.next());
		}
	}

	public int countByType(String type) throws SystemException {
		boolean finderClassNameCacheEnabled = ListTypeModelImpl.CACHE_ENABLED;
		String finderClassName = ListType.class.getName();
		String finderMethodName = "countByType";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { type };

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
				query.append("FROM com.liferay.portal.model.ListType WHERE ");

				if (type == null) {
					query.append("type_ IS NULL");
				}
				else {
					query.append("type_ = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (type != null) {
					q.setString(queryPos++, type);
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
		boolean finderClassNameCacheEnabled = ListTypeModelImpl.CACHE_ENABLED;
		String finderClassName = ListType.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.ListType");

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
				"value.object.listener.com.liferay.portal.model.ListType"));
	private static Log _log = LogFactory.getLog(ListTypePersistenceImpl.class);
}
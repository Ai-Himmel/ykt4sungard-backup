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

package com.liferay.portlet.shopping.service.persistence;

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

import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.impl.ShoppingItemImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemModelImpl;

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

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingItemPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemPersistenceImpl extends BasePersistence
	implements ShoppingItemPersistence {
	public ShoppingItem create(long itemId) {
		ShoppingItem shoppingItem = new ShoppingItemImpl();

		shoppingItem.setNew(true);
		shoppingItem.setPrimaryKey(itemId);

		return shoppingItem;
	}

	public ShoppingItem remove(long itemId)
		throws NoSuchItemException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingItem shoppingItem = (ShoppingItem)session.get(ShoppingItemImpl.class,
					new Long(itemId));

			if (shoppingItem == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No ShoppingItem exists with the primary key " +
						itemId);
				}

				throw new NoSuchItemException(
					"No ShoppingItem exists with the primary key " + itemId);
			}

			return remove(shoppingItem);
		}
		catch (NoSuchItemException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ShoppingItem remove(ShoppingItem shoppingItem)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(shoppingItem);
		}

		shoppingItem = removeImpl(shoppingItem);

		if (listener != null) {
			listener.onAfterRemove(shoppingItem);
		}

		return shoppingItem;
	}

	protected ShoppingItem removeImpl(ShoppingItem shoppingItem)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(shoppingItem);

			session.flush();

			return shoppingItem;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingItem.class.getName());
		}
	}

	public ShoppingItem update(ShoppingItem shoppingItem)
		throws SystemException {
		return update(shoppingItem, false);
	}

	public ShoppingItem update(ShoppingItem shoppingItem, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = shoppingItem.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingItem);
			}
			else {
				listener.onBeforeUpdate(shoppingItem);
			}
		}

		shoppingItem = updateImpl(shoppingItem, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingItem);
			}
			else {
				listener.onAfterUpdate(shoppingItem);
			}
		}

		return shoppingItem;
	}

	public ShoppingItem updateImpl(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(shoppingItem);
			}
			else {
				if (shoppingItem.isNew()) {
					session.save(shoppingItem);
				}
			}

			session.flush();

			shoppingItem.setNew(false);

			return shoppingItem;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingItem.class.getName());
		}
	}

	public ShoppingItem findByPrimaryKey(long itemId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = fetchByPrimaryKey(itemId);

		if (shoppingItem == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ShoppingItem exists with the primary key " +
					itemId);
			}

			throw new NoSuchItemException(
				"No ShoppingItem exists with the primary key " + itemId);
		}

		return shoppingItem;
	}

	public ShoppingItem fetchByPrimaryKey(long itemId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (ShoppingItem)session.get(ShoppingItemImpl.class,
				new Long(itemId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCategoryId(long categoryId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "findByCategoryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(categoryId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("categoryId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, categoryId);

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

	public List findByCategoryId(long categoryId, int begin, int end)
		throws SystemException {
		return findByCategoryId(categoryId, begin, end, null);
	}

	public List findByCategoryId(long categoryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "findByCategoryId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(categoryId),
				
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("categoryId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("itemId ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, categoryId);

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

	public ShoppingItem findByCategoryId_First(long categoryId,
		OrderByComparator obc) throws NoSuchItemException, SystemException {
		List list = findByCategoryId(categoryId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItem exists with the key {");

			msg.append("categoryId=" + categoryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchItemException(msg.toString());
		}
		else {
			return (ShoppingItem)list.get(0);
		}
	}

	public ShoppingItem findByCategoryId_Last(long categoryId,
		OrderByComparator obc) throws NoSuchItemException, SystemException {
		int count = countByCategoryId(categoryId);

		List list = findByCategoryId(categoryId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItem exists with the key {");

			msg.append("categoryId=" + categoryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchItemException(msg.toString());
		}
		else {
			return (ShoppingItem)list.get(0);
		}
	}

	public ShoppingItem[] findByCategoryId_PrevAndNext(long itemId,
		long categoryId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = findByPrimaryKey(itemId);

		int count = countByCategoryId(categoryId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

			query.append("categoryId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, categoryId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					shoppingItem);

			ShoppingItem[] array = new ShoppingItemImpl[3];

			array[0] = (ShoppingItem)objArray[0];
			array[1] = (ShoppingItem)objArray[1];
			array[2] = (ShoppingItem)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ShoppingItem findBySmallImageId(long smallImageId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = fetchBySmallImageId(smallImageId);

		if (shoppingItem == null) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItem exists with the key {");

			msg.append("smallImageId=" + smallImageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchItemException(msg.toString());
		}

		return shoppingItem;
	}

	public ShoppingItem fetchBySmallImageId(long smallImageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "fetchBySmallImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(smallImageId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("smallImageId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, smallImageId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (ShoppingItem)list.get(0);
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
				return (ShoppingItem)list.get(0);
			}
		}
	}

	public ShoppingItem findByMediumImageId(long mediumImageId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = fetchByMediumImageId(mediumImageId);

		if (shoppingItem == null) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItem exists with the key {");

			msg.append("mediumImageId=" + mediumImageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchItemException(msg.toString());
		}

		return shoppingItem;
	}

	public ShoppingItem fetchByMediumImageId(long mediumImageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "fetchByMediumImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(mediumImageId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("mediumImageId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, mediumImageId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (ShoppingItem)list.get(0);
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
				return (ShoppingItem)list.get(0);
			}
		}
	}

	public ShoppingItem findByLargeImageId(long largeImageId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = fetchByLargeImageId(largeImageId);

		if (shoppingItem == null) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItem exists with the key {");

			msg.append("largeImageId=" + largeImageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchItemException(msg.toString());
		}

		return shoppingItem;
	}

	public ShoppingItem fetchByLargeImageId(long largeImageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "fetchByLargeImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(largeImageId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("largeImageId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, largeImageId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (ShoppingItem)list.get(0);
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
				return (ShoppingItem)list.get(0);
			}
		}
	}

	public ShoppingItem findByC_S(long companyId, String sku)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = fetchByC_S(companyId, sku);

		if (shoppingItem == null) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItem exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("sku=" + sku);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchItemException(msg.toString());
		}

		return shoppingItem;
	}

	public ShoppingItem fetchByC_S(long companyId, String sku)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "fetchByC_S";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), sku };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (sku == null) {
					query.append("sku IS NULL");
				}
				else {
					query.append("sku = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (sku != null) {
					q.setString(queryPos++, sku);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (ShoppingItem)list.get(0);
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
				return (ShoppingItem)list.get(0);
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
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("itemId ASC");
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

	public void removeByCategoryId(long categoryId) throws SystemException {
		Iterator itr = findByCategoryId(categoryId).iterator();

		while (itr.hasNext()) {
			ShoppingItem shoppingItem = (ShoppingItem)itr.next();

			remove(shoppingItem);
		}
	}

	public void removeBySmallImageId(long smallImageId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = findBySmallImageId(smallImageId);

		remove(shoppingItem);
	}

	public void removeByMediumImageId(long mediumImageId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = findByMediumImageId(mediumImageId);

		remove(shoppingItem);
	}

	public void removeByLargeImageId(long largeImageId)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = findByLargeImageId(largeImageId);

		remove(shoppingItem);
	}

	public void removeByC_S(long companyId, String sku)
		throws NoSuchItemException, SystemException {
		ShoppingItem shoppingItem = findByC_S(companyId, sku);

		remove(shoppingItem);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((ShoppingItem)itr.next());
		}
	}

	public int countByCategoryId(long categoryId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "countByCategoryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(categoryId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("categoryId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, categoryId);

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

	public int countBySmallImageId(long smallImageId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "countBySmallImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(smallImageId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("smallImageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, smallImageId);

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

	public int countByMediumImageId(long mediumImageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "countByMediumImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(mediumImageId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("mediumImageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, mediumImageId);

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

	public int countByLargeImageId(long largeImageId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "countByLargeImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(largeImageId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("largeImageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, largeImageId);

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

	public int countByC_S(long companyId, String sku) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
		String finderMethodName = "countByC_S";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), sku };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItem WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (sku == null) {
					query.append("sku IS NULL");
				}
				else {
					query.append("sku = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (sku != null) {
					q.setString(queryPos++, sku);
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
		boolean finderClassNameCacheEnabled = ShoppingItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItem.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.shopping.model.ShoppingItem");

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

	public List getShoppingItemPrices(long pk)
		throws NoSuchItemException, SystemException {
		return getShoppingItemPrices(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getShoppingItemPrices(long pk, int begin, int end)
		throws NoSuchItemException, SystemException {
		return getShoppingItemPrices(pk, begin, end, null);
	}

	public List getShoppingItemPrices(long pk, int begin, int end,
		OrderByComparator obc) throws NoSuchItemException, SystemException {
		boolean finderClassNameCacheEnabled = com.liferay.portlet.shopping.model.impl.ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = com.liferay.portlet.shopping.model.ShoppingItemPrice.class.getName();
		String finderMethodName = "getShoppingItemPrices";
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

				sm.append(_SQL_GETSHOPPINGITEMPRICES);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("ShoppingItemPrice.itemId ASC, ");
					sm.append("ShoppingItemPrice.itemPriceId ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("ShoppingItemPrice",
					com.liferay.portlet.shopping.model.impl.ShoppingItemPriceImpl.class);

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

	public int getShoppingItemPricesSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = com.liferay.portlet.shopping.model.impl.ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = com.liferay.portlet.shopping.model.ShoppingItemPrice.class.getName();
		String finderMethodName = "getShoppingItemPricesSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETSHOPPINGITEMPRICESSIZE);

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

	public boolean containsShoppingItemPrice(long pk, long shoppingItemPricePK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = com.liferay.portlet.shopping.model.impl.ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = com.liferay.portlet.shopping.model.ShoppingItemPrice.class.getName();
		String finderMethodName = "containsShoppingItemPrices";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(pk),
				
				new Long(shoppingItemPricePK)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsShoppingItemPrice.contains(
							pk, shoppingItemPricePK));

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

	public boolean containsShoppingItemPrices(long pk)
		throws SystemException {
		if (getShoppingItemPricesSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	protected void initDao() {
		containsShoppingItemPrice = new ContainsShoppingItemPrice(this);
	}

	protected ContainsShoppingItemPrice containsShoppingItemPrice;

	protected class ContainsShoppingItemPrice extends MappingSqlQuery {
		protected ContainsShoppingItemPrice(
			ShoppingItemPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				_SQL_CONTAINSSHOPPINGITEMPRICE);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long itemId, long itemPriceId) {
			List results = execute(new Object[] {
						new Long(itemId), new Long(itemPriceId)
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

	private static final String _SQL_GETSHOPPINGITEMPRICES = "SELECT {ShoppingItemPrice.*} FROM ShoppingItemPrice INNER JOIN ShoppingItem ON (ShoppingItem.itemId = ShoppingItemPrice.itemId) WHERE (ShoppingItem.itemId = ?)";
	private static final String _SQL_GETSHOPPINGITEMPRICESSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM ShoppingItemPrice WHERE itemId = ?";
	private static final String _SQL_CONTAINSSHOPPINGITEMPRICE = "SELECT COUNT(*) AS COUNT_VALUE FROM ShoppingItemPrice WHERE itemId = ? AND itemPriceId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingItem"));
	private static Log _log = LogFactory.getLog(ShoppingItemPersistenceImpl.class);
}
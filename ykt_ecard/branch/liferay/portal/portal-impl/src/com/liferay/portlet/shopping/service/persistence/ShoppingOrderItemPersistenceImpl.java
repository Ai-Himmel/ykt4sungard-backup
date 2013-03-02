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

import com.liferay.portlet.shopping.NoSuchOrderItemException;
import com.liferay.portlet.shopping.model.ShoppingOrderItem;
import com.liferay.portlet.shopping.model.impl.ShoppingOrderItemImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingOrderItemModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingOrderItemPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingOrderItemPersistenceImpl extends BasePersistence
	implements ShoppingOrderItemPersistence {
	public ShoppingOrderItem create(long orderItemId) {
		ShoppingOrderItem shoppingOrderItem = new ShoppingOrderItemImpl();

		shoppingOrderItem.setNew(true);
		shoppingOrderItem.setPrimaryKey(orderItemId);

		return shoppingOrderItem;
	}

	public ShoppingOrderItem remove(long orderItemId)
		throws NoSuchOrderItemException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingOrderItem shoppingOrderItem = (ShoppingOrderItem)session.get(ShoppingOrderItemImpl.class,
					new Long(orderItemId));

			if (shoppingOrderItem == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No ShoppingOrderItem exists with the primary key " +
						orderItemId);
				}

				throw new NoSuchOrderItemException(
					"No ShoppingOrderItem exists with the primary key " +
					orderItemId);
			}

			return remove(shoppingOrderItem);
		}
		catch (NoSuchOrderItemException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ShoppingOrderItem remove(ShoppingOrderItem shoppingOrderItem)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(shoppingOrderItem);
		}

		shoppingOrderItem = removeImpl(shoppingOrderItem);

		if (listener != null) {
			listener.onAfterRemove(shoppingOrderItem);
		}

		return shoppingOrderItem;
	}

	protected ShoppingOrderItem removeImpl(ShoppingOrderItem shoppingOrderItem)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(shoppingOrderItem);

			session.flush();

			return shoppingOrderItem;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingOrderItem.class.getName());
		}
	}

	public ShoppingOrderItem update(ShoppingOrderItem shoppingOrderItem)
		throws SystemException {
		return update(shoppingOrderItem, false);
	}

	public ShoppingOrderItem update(ShoppingOrderItem shoppingOrderItem,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = shoppingOrderItem.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingOrderItem);
			}
			else {
				listener.onBeforeUpdate(shoppingOrderItem);
			}
		}

		shoppingOrderItem = updateImpl(shoppingOrderItem, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingOrderItem);
			}
			else {
				listener.onAfterUpdate(shoppingOrderItem);
			}
		}

		return shoppingOrderItem;
	}

	public ShoppingOrderItem updateImpl(
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(shoppingOrderItem);
			}
			else {
				if (shoppingOrderItem.isNew()) {
					session.save(shoppingOrderItem);
				}
			}

			session.flush();

			shoppingOrderItem.setNew(false);

			return shoppingOrderItem;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingOrderItem.class.getName());
		}
	}

	public ShoppingOrderItem findByPrimaryKey(long orderItemId)
		throws NoSuchOrderItemException, SystemException {
		ShoppingOrderItem shoppingOrderItem = fetchByPrimaryKey(orderItemId);

		if (shoppingOrderItem == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ShoppingOrderItem exists with the primary key " +
					orderItemId);
			}

			throw new NoSuchOrderItemException(
				"No ShoppingOrderItem exists with the primary key " +
				orderItemId);
		}

		return shoppingOrderItem;
	}

	public ShoppingOrderItem fetchByPrimaryKey(long orderItemId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (ShoppingOrderItem)session.get(ShoppingOrderItemImpl.class,
				new Long(orderItemId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByOrderId(long orderId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingOrderItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingOrderItem.class.getName();
		String finderMethodName = "findByOrderId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(orderId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingOrderItem WHERE ");

				query.append("orderId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC, ");
				query.append("description ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, orderId);

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

	public List findByOrderId(long orderId, int begin, int end)
		throws SystemException {
		return findByOrderId(orderId, begin, end, null);
	}

	public List findByOrderId(long orderId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingOrderItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingOrderItem.class.getName();
		String finderMethodName = "findByOrderId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(orderId),
				
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
					"FROM com.liferay.portlet.shopping.model.ShoppingOrderItem WHERE ");

				query.append("orderId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("name ASC, ");
					query.append("description ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, orderId);

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

	public ShoppingOrderItem findByOrderId_First(long orderId,
		OrderByComparator obc) throws NoSuchOrderItemException, SystemException {
		List list = findByOrderId(orderId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingOrderItem exists with the key {");

			msg.append("orderId=" + orderId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrderItemException(msg.toString());
		}
		else {
			return (ShoppingOrderItem)list.get(0);
		}
	}

	public ShoppingOrderItem findByOrderId_Last(long orderId,
		OrderByComparator obc) throws NoSuchOrderItemException, SystemException {
		int count = countByOrderId(orderId);

		List list = findByOrderId(orderId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingOrderItem exists with the key {");

			msg.append("orderId=" + orderId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchOrderItemException(msg.toString());
		}
		else {
			return (ShoppingOrderItem)list.get(0);
		}
	}

	public ShoppingOrderItem[] findByOrderId_PrevAndNext(long orderItemId,
		long orderId, OrderByComparator obc)
		throws NoSuchOrderItemException, SystemException {
		ShoppingOrderItem shoppingOrderItem = findByPrimaryKey(orderItemId);

		int count = countByOrderId(orderId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.shopping.model.ShoppingOrderItem WHERE ");

			query.append("orderId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("name ASC, ");
				query.append("description ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, orderId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					shoppingOrderItem);

			ShoppingOrderItem[] array = new ShoppingOrderItemImpl[3];

			array[0] = (ShoppingOrderItem)objArray[0];
			array[1] = (ShoppingOrderItem)objArray[1];
			array[2] = (ShoppingOrderItem)objArray[2];

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
		boolean finderClassNameCacheEnabled = ShoppingOrderItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingOrderItem.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingOrderItem ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("name ASC, ");
					query.append("description ASC");
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

	public void removeByOrderId(long orderId) throws SystemException {
		Iterator itr = findByOrderId(orderId).iterator();

		while (itr.hasNext()) {
			ShoppingOrderItem shoppingOrderItem = (ShoppingOrderItem)itr.next();

			remove(shoppingOrderItem);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((ShoppingOrderItem)itr.next());
		}
	}

	public int countByOrderId(long orderId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingOrderItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingOrderItem.class.getName();
		String finderMethodName = "countByOrderId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(orderId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingOrderItem WHERE ");

				query.append("orderId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, orderId);

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
		boolean finderClassNameCacheEnabled = ShoppingOrderItemModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingOrderItem.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.shopping.model.ShoppingOrderItem");

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
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingOrderItem"));
	private static Log _log = LogFactory.getLog(ShoppingOrderItemPersistenceImpl.class);
}
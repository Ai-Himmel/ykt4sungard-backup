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

import com.liferay.portlet.shopping.NoSuchItemPriceException;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.model.impl.ShoppingItemPriceImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemPriceModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingItemPricePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemPricePersistenceImpl extends BasePersistence
	implements ShoppingItemPricePersistence {
	public ShoppingItemPrice create(long itemPriceId) {
		ShoppingItemPrice shoppingItemPrice = new ShoppingItemPriceImpl();

		shoppingItemPrice.setNew(true);
		shoppingItemPrice.setPrimaryKey(itemPriceId);

		return shoppingItemPrice;
	}

	public ShoppingItemPrice remove(long itemPriceId)
		throws NoSuchItemPriceException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingItemPrice shoppingItemPrice = (ShoppingItemPrice)session.get(ShoppingItemPriceImpl.class,
					new Long(itemPriceId));

			if (shoppingItemPrice == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No ShoppingItemPrice exists with the primary key " +
						itemPriceId);
				}

				throw new NoSuchItemPriceException(
					"No ShoppingItemPrice exists with the primary key " +
					itemPriceId);
			}

			return remove(shoppingItemPrice);
		}
		catch (NoSuchItemPriceException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ShoppingItemPrice remove(ShoppingItemPrice shoppingItemPrice)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(shoppingItemPrice);
		}

		shoppingItemPrice = removeImpl(shoppingItemPrice);

		if (listener != null) {
			listener.onAfterRemove(shoppingItemPrice);
		}

		return shoppingItemPrice;
	}

	protected ShoppingItemPrice removeImpl(ShoppingItemPrice shoppingItemPrice)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(shoppingItemPrice);

			session.flush();

			return shoppingItemPrice;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingItemPrice.class.getName());
		}
	}

	public ShoppingItemPrice update(ShoppingItemPrice shoppingItemPrice)
		throws SystemException {
		return update(shoppingItemPrice, false);
	}

	public ShoppingItemPrice update(ShoppingItemPrice shoppingItemPrice,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = shoppingItemPrice.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingItemPrice);
			}
			else {
				listener.onBeforeUpdate(shoppingItemPrice);
			}
		}

		shoppingItemPrice = updateImpl(shoppingItemPrice, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingItemPrice);
			}
			else {
				listener.onAfterUpdate(shoppingItemPrice);
			}
		}

		return shoppingItemPrice;
	}

	public ShoppingItemPrice updateImpl(
		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(shoppingItemPrice);
			}
			else {
				if (shoppingItemPrice.isNew()) {
					session.save(shoppingItemPrice);
				}
			}

			session.flush();

			shoppingItemPrice.setNew(false);

			return shoppingItemPrice;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingItemPrice.class.getName());
		}
	}

	public ShoppingItemPrice findByPrimaryKey(long itemPriceId)
		throws NoSuchItemPriceException, SystemException {
		ShoppingItemPrice shoppingItemPrice = fetchByPrimaryKey(itemPriceId);

		if (shoppingItemPrice == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ShoppingItemPrice exists with the primary key " +
					itemPriceId);
			}

			throw new NoSuchItemPriceException(
				"No ShoppingItemPrice exists with the primary key " +
				itemPriceId);
		}

		return shoppingItemPrice;
	}

	public ShoppingItemPrice fetchByPrimaryKey(long itemPriceId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (ShoppingItemPrice)session.get(ShoppingItemPriceImpl.class,
				new Long(itemPriceId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByItemId(long itemId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemPrice.class.getName();
		String finderMethodName = "findByItemId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(itemId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemPrice WHERE ");

				query.append("itemId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC, ");
				query.append("itemPriceId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, itemId);

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

	public List findByItemId(long itemId, int begin, int end)
		throws SystemException {
		return findByItemId(itemId, begin, end, null);
	}

	public List findByItemId(long itemId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemPrice.class.getName();
		String finderMethodName = "findByItemId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(itemId),
				
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemPrice WHERE ");

				query.append("itemId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("itemId ASC, ");
					query.append("itemPriceId ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, itemId);

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

	public ShoppingItemPrice findByItemId_First(long itemId,
		OrderByComparator obc) throws NoSuchItemPriceException, SystemException {
		List list = findByItemId(itemId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItemPrice exists with the key {");

			msg.append("itemId=" + itemId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchItemPriceException(msg.toString());
		}
		else {
			return (ShoppingItemPrice)list.get(0);
		}
	}

	public ShoppingItemPrice findByItemId_Last(long itemId,
		OrderByComparator obc) throws NoSuchItemPriceException, SystemException {
		int count = countByItemId(itemId);

		List list = findByItemId(itemId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItemPrice exists with the key {");

			msg.append("itemId=" + itemId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchItemPriceException(msg.toString());
		}
		else {
			return (ShoppingItemPrice)list.get(0);
		}
	}

	public ShoppingItemPrice[] findByItemId_PrevAndNext(long itemPriceId,
		long itemId, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		ShoppingItemPrice shoppingItemPrice = findByPrimaryKey(itemPriceId);

		int count = countByItemId(itemId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.shopping.model.ShoppingItemPrice WHERE ");

			query.append("itemId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("itemId ASC, ");
				query.append("itemPriceId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, itemId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					shoppingItemPrice);

			ShoppingItemPrice[] array = new ShoppingItemPriceImpl[3];

			array[0] = (ShoppingItemPrice)objArray[0];
			array[1] = (ShoppingItemPrice)objArray[1];
			array[2] = (ShoppingItemPrice)objArray[2];

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
		boolean finderClassNameCacheEnabled = ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemPrice.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemPrice ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("itemId ASC, ");
					query.append("itemPriceId ASC");
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

	public void removeByItemId(long itemId) throws SystemException {
		Iterator itr = findByItemId(itemId).iterator();

		while (itr.hasNext()) {
			ShoppingItemPrice shoppingItemPrice = (ShoppingItemPrice)itr.next();

			remove(shoppingItemPrice);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((ShoppingItemPrice)itr.next());
		}
	}

	public int countByItemId(long itemId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemPrice.class.getName();
		String finderMethodName = "countByItemId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(itemId) };

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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemPrice WHERE ");

				query.append("itemId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, itemId);

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
		boolean finderClassNameCacheEnabled = ShoppingItemPriceModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemPrice.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.shopping.model.ShoppingItemPrice");

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
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingItemPrice"));
	private static Log _log = LogFactory.getLog(ShoppingItemPricePersistenceImpl.class);
}
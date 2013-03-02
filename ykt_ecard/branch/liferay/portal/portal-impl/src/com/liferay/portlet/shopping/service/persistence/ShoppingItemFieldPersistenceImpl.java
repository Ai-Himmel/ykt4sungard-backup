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

import com.liferay.portlet.shopping.NoSuchItemFieldException;
import com.liferay.portlet.shopping.model.ShoppingItemField;
import com.liferay.portlet.shopping.model.impl.ShoppingItemFieldImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemFieldModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingItemFieldPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemFieldPersistenceImpl extends BasePersistence
	implements ShoppingItemFieldPersistence {
	public ShoppingItemField create(long itemFieldId) {
		ShoppingItemField shoppingItemField = new ShoppingItemFieldImpl();

		shoppingItemField.setNew(true);
		shoppingItemField.setPrimaryKey(itemFieldId);

		return shoppingItemField;
	}

	public ShoppingItemField remove(long itemFieldId)
		throws NoSuchItemFieldException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingItemField shoppingItemField = (ShoppingItemField)session.get(ShoppingItemFieldImpl.class,
					new Long(itemFieldId));

			if (shoppingItemField == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No ShoppingItemField exists with the primary key " +
						itemFieldId);
				}

				throw new NoSuchItemFieldException(
					"No ShoppingItemField exists with the primary key " +
					itemFieldId);
			}

			return remove(shoppingItemField);
		}
		catch (NoSuchItemFieldException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ShoppingItemField remove(ShoppingItemField shoppingItemField)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(shoppingItemField);
		}

		shoppingItemField = removeImpl(shoppingItemField);

		if (listener != null) {
			listener.onAfterRemove(shoppingItemField);
		}

		return shoppingItemField;
	}

	protected ShoppingItemField removeImpl(ShoppingItemField shoppingItemField)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(shoppingItemField);

			session.flush();

			return shoppingItemField;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingItemField.class.getName());
		}
	}

	public ShoppingItemField update(ShoppingItemField shoppingItemField)
		throws SystemException {
		return update(shoppingItemField, false);
	}

	public ShoppingItemField update(ShoppingItemField shoppingItemField,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = shoppingItemField.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingItemField);
			}
			else {
				listener.onBeforeUpdate(shoppingItemField);
			}
		}

		shoppingItemField = updateImpl(shoppingItemField, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingItemField);
			}
			else {
				listener.onAfterUpdate(shoppingItemField);
			}
		}

		return shoppingItemField;
	}

	public ShoppingItemField updateImpl(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(shoppingItemField);
			}
			else {
				if (shoppingItemField.isNew()) {
					session.save(shoppingItemField);
				}
			}

			session.flush();

			shoppingItemField.setNew(false);

			return shoppingItemField;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(ShoppingItemField.class.getName());
		}
	}

	public ShoppingItemField findByPrimaryKey(long itemFieldId)
		throws NoSuchItemFieldException, SystemException {
		ShoppingItemField shoppingItemField = fetchByPrimaryKey(itemFieldId);

		if (shoppingItemField == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ShoppingItemField exists with the primary key " +
					itemFieldId);
			}

			throw new NoSuchItemFieldException(
				"No ShoppingItemField exists with the primary key " +
				itemFieldId);
		}

		return shoppingItemField;
	}

	public ShoppingItemField fetchByPrimaryKey(long itemFieldId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (ShoppingItemField)session.get(ShoppingItemFieldImpl.class,
				new Long(itemFieldId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByItemId(long itemId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemFieldModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemField.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemField WHERE ");

				query.append("itemId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("itemId ASC, ");
				query.append("name ASC");

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
		boolean finderClassNameCacheEnabled = ShoppingItemFieldModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemField.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemField WHERE ");

				query.append("itemId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("itemId ASC, ");
					query.append("name ASC");
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

	public ShoppingItemField findByItemId_First(long itemId,
		OrderByComparator obc) throws NoSuchItemFieldException, SystemException {
		List list = findByItemId(itemId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItemField exists with the key {");

			msg.append("itemId=" + itemId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchItemFieldException(msg.toString());
		}
		else {
			return (ShoppingItemField)list.get(0);
		}
	}

	public ShoppingItemField findByItemId_Last(long itemId,
		OrderByComparator obc) throws NoSuchItemFieldException, SystemException {
		int count = countByItemId(itemId);

		List list = findByItemId(itemId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No ShoppingItemField exists with the key {");

			msg.append("itemId=" + itemId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchItemFieldException(msg.toString());
		}
		else {
			return (ShoppingItemField)list.get(0);
		}
	}

	public ShoppingItemField[] findByItemId_PrevAndNext(long itemFieldId,
		long itemId, OrderByComparator obc)
		throws NoSuchItemFieldException, SystemException {
		ShoppingItemField shoppingItemField = findByPrimaryKey(itemFieldId);

		int count = countByItemId(itemId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.shopping.model.ShoppingItemField WHERE ");

			query.append("itemId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("itemId ASC, ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, itemId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					shoppingItemField);

			ShoppingItemField[] array = new ShoppingItemFieldImpl[3];

			array[0] = (ShoppingItemField)objArray[0];
			array[1] = (ShoppingItemField)objArray[1];
			array[2] = (ShoppingItemField)objArray[2];

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
		boolean finderClassNameCacheEnabled = ShoppingItemFieldModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemField.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemField ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("itemId ASC, ");
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

	public void removeByItemId(long itemId) throws SystemException {
		Iterator itr = findByItemId(itemId).iterator();

		while (itr.hasNext()) {
			ShoppingItemField shoppingItemField = (ShoppingItemField)itr.next();

			remove(shoppingItemField);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((ShoppingItemField)itr.next());
		}
	}

	public int countByItemId(long itemId) throws SystemException {
		boolean finderClassNameCacheEnabled = ShoppingItemFieldModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemField.class.getName();
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
					"FROM com.liferay.portlet.shopping.model.ShoppingItemField WHERE ");

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
		boolean finderClassNameCacheEnabled = ShoppingItemFieldModelImpl.CACHE_ENABLED;
		String finderClassName = ShoppingItemField.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.shopping.model.ShoppingItemField");

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
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingItemField"));
	private static Log _log = LogFactory.getLog(ShoppingItemFieldPersistenceImpl.class);
}
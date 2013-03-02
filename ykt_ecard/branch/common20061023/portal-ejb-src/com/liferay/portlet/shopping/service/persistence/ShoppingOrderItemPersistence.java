/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.shopping.NoSuchOrderItemException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingOrderItemPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderItemPersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingOrderItem create(
		ShoppingOrderItemPK shoppingOrderItemPK) {
		return new com.liferay.portlet.shopping.model.ShoppingOrderItem(shoppingOrderItemPK);
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem remove(
		ShoppingOrderItemPK shoppingOrderItemPK)
		throws NoSuchOrderItemException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)session.get(ShoppingOrderItemHBM.class,
					shoppingOrderItemPK);

			if (shoppingOrderItemHBM == null) {
				_log.warn(
					"No ShoppingOrderItem exists with the primary key of " +
					shoppingOrderItemPK.toString());
				throw new NoSuchOrderItemException(shoppingOrderItemPK.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem =
				ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM);
			session.delete(shoppingOrderItemHBM);
			session.flush();
			ShoppingOrderItemPool.remove(shoppingOrderItemPK);

			return shoppingOrderItem;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem update(
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingOrderItem.isNew() || shoppingOrderItem.isModified()) {
				session = openSession();

				if (shoppingOrderItem.isNew()) {
					ShoppingOrderItemHBM shoppingOrderItemHBM = new ShoppingOrderItemHBM(shoppingOrderItem.getOrderId(),
							shoppingOrderItem.getItemId(),
							shoppingOrderItem.getSku(),
							shoppingOrderItem.getName(),
							shoppingOrderItem.getDescription(),
							shoppingOrderItem.getProperties(),
							shoppingOrderItem.getSupplierUserId(),
							shoppingOrderItem.getPrice(),
							shoppingOrderItem.getQuantity(),
							shoppingOrderItem.getShippedDate());
					session.save(shoppingOrderItemHBM);
					session.flush();
				}
				else {
					ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)session.get(ShoppingOrderItemHBM.class,
							shoppingOrderItem.getPrimaryKey());

					if (shoppingOrderItemHBM != null) {
						shoppingOrderItemHBM.setSku(shoppingOrderItem.getSku());
						shoppingOrderItemHBM.setName(shoppingOrderItem.getName());
						shoppingOrderItemHBM.setDescription(shoppingOrderItem.getDescription());
						shoppingOrderItemHBM.setProperties(shoppingOrderItem.getProperties());
						shoppingOrderItemHBM.setSupplierUserId(shoppingOrderItem.getSupplierUserId());
						shoppingOrderItemHBM.setPrice(shoppingOrderItem.getPrice());
						shoppingOrderItemHBM.setQuantity(shoppingOrderItem.getQuantity());
						shoppingOrderItemHBM.setShippedDate(shoppingOrderItem.getShippedDate());
						session.flush();
					}
					else {
						shoppingOrderItemHBM = new ShoppingOrderItemHBM(shoppingOrderItem.getOrderId(),
								shoppingOrderItem.getItemId(),
								shoppingOrderItem.getSku(),
								shoppingOrderItem.getName(),
								shoppingOrderItem.getDescription(),
								shoppingOrderItem.getProperties(),
								shoppingOrderItem.getSupplierUserId(),
								shoppingOrderItem.getPrice(),
								shoppingOrderItem.getQuantity(),
								shoppingOrderItem.getShippedDate());
						session.save(shoppingOrderItemHBM);
						session.flush();
					}
				}

				shoppingOrderItem.setNew(false);
				shoppingOrderItem.setModified(false);
				shoppingOrderItem.protect();
				ShoppingOrderItemPool.put(shoppingOrderItem.getPrimaryKey(),
					shoppingOrderItem);
			}

			return shoppingOrderItem;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem findByPrimaryKey(
		ShoppingOrderItemPK shoppingOrderItemPK)
		throws NoSuchOrderItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem = ShoppingOrderItemPool.get(shoppingOrderItemPK);
		Session session = null;

		try {
			if (shoppingOrderItem == null) {
				session = openSession();

				ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)session.get(ShoppingOrderItemHBM.class,
						shoppingOrderItemPK);

				if (shoppingOrderItemHBM == null) {
					_log.warn(
						"No ShoppingOrderItem exists with the primary key of " +
						shoppingOrderItemPK.toString());
					throw new NoSuchOrderItemException(shoppingOrderItemPK.toString());
				}

				shoppingOrderItem = ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM);
			}

			return shoppingOrderItem;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByOrderId(String orderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("orderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("supplierUserId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("description ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, orderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
				list.add(ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByOrderId(String orderId, int begin, int end)
		throws SystemException {
		return findByOrderId(orderId, begin, end, null);
	}

	public List findByOrderId(String orderId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("orderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("supplierUserId ASC").append(", ");
				query.append("name ASC").append(", ");
				query.append("description ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, orderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
					list.add(ShoppingOrderItemHBMUtil.model(
							shoppingOrderItemHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)sr.get(0);
						list.add(ShoppingOrderItemHBMUtil.model(
								shoppingOrderItemHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem findByOrderId_First(
		String orderId, OrderByComparator obc)
		throws NoSuchOrderItemException, SystemException {
		List list = findByOrderId(orderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrderItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem findByOrderId_Last(
		String orderId, OrderByComparator obc)
		throws NoSuchOrderItemException, SystemException {
		int count = countByOrderId(orderId);
		List list = findByOrderId(orderId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrderItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem[] findByOrderId_PrevAndNext(
		ShoppingOrderItemPK shoppingOrderItemPK, String orderId,
		OrderByComparator obc) throws NoSuchOrderItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem = findByPrimaryKey(shoppingOrderItemPK);
		int count = countByOrderId(orderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("orderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("supplierUserId ASC").append(", ");
				query.append("name ASC").append(", ");
				query.append("description ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, orderId);

			com.liferay.portlet.shopping.model.ShoppingOrderItem[] array = new com.liferay.portlet.shopping.model.ShoppingOrderItem[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)sr.get(0);

					if (shoppingOrderItemHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingOrderItem curShoppingOrderItem =
						ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM);
					int value = obc.compare(shoppingOrderItem,
							curShoppingOrderItem);

					if (value == 0) {
						if (!shoppingOrderItem.equals(curShoppingOrderItem)) {
							break;
						}

						array[1] = curShoppingOrderItem;

						if (sr.previous()) {
							array[0] = ShoppingOrderItemHBMUtil.model((ShoppingOrderItemHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingOrderItemHBMUtil.model((ShoppingOrderItemHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("supplierUserId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("description ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
				list.add(ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByItemId(String itemId, int begin, int end)
		throws SystemException {
		return findByItemId(itemId, begin, end, null);
	}

	public List findByItemId(String itemId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("supplierUserId ASC").append(", ");
				query.append("name ASC").append(", ");
				query.append("description ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
					list.add(ShoppingOrderItemHBMUtil.model(
							shoppingOrderItemHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)sr.get(0);
						list.add(ShoppingOrderItemHBMUtil.model(
								shoppingOrderItemHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem findByItemId_First(
		String itemId, OrderByComparator obc)
		throws NoSuchOrderItemException, SystemException {
		List list = findByItemId(itemId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrderItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem findByItemId_Last(
		String itemId, OrderByComparator obc)
		throws NoSuchOrderItemException, SystemException {
		int count = countByItemId(itemId);
		List list = findByItemId(itemId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrderItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrderItem[] findByItemId_PrevAndNext(
		ShoppingOrderItemPK shoppingOrderItemPK, String itemId,
		OrderByComparator obc) throws NoSuchOrderItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem = findByPrimaryKey(shoppingOrderItemPK);
		int count = countByItemId(itemId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("supplierUserId ASC").append(", ");
				query.append("name ASC").append(", ");
				query.append("description ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			com.liferay.portlet.shopping.model.ShoppingOrderItem[] array = new com.liferay.portlet.shopping.model.ShoppingOrderItem[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)sr.get(0);

					if (shoppingOrderItemHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingOrderItem curShoppingOrderItem =
						ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM);
					int value = obc.compare(shoppingOrderItem,
							curShoppingOrderItem);

					if (value == 0) {
						if (!shoppingOrderItem.equals(curShoppingOrderItem)) {
							break;
						}

						array[1] = curShoppingOrderItem;

						if (sr.previous()) {
							array[0] = ShoppingOrderItemHBMUtil.model((ShoppingOrderItemHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingOrderItemHBMUtil.model((ShoppingOrderItemHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM ");
			query.append("ORDER BY ");
			query.append("supplierUserId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("description ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
				list.add(ShoppingOrderItemHBMUtil.model(shoppingOrderItemHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByOrderId(String orderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("orderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("supplierUserId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("description ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, orderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
				ShoppingOrderItemPool.remove((ShoppingOrderItemPK)shoppingOrderItemHBM.getPrimaryKey());
				session.delete(shoppingOrderItemHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("supplierUserId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("description ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingOrderItemHBM shoppingOrderItemHBM = (ShoppingOrderItemHBM)itr.next();
				ShoppingOrderItemPool.remove((ShoppingOrderItemPK)shoppingOrderItemHBM.getPrimaryKey());
				session.delete(shoppingOrderItemHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByOrderId(String orderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("orderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, orderId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingOrderItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	private static final Log _log = LogFactory.getLog(ShoppingOrderItemPersistence.class);
}
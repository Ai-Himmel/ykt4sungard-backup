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

import com.liferay.portlet.shopping.NoSuchItemPriceException;

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
 * <a href="ShoppingItemPricePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemPricePersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingItemPrice create(
		String itemPriceId) {
		return new com.liferay.portlet.shopping.model.ShoppingItemPrice(itemPriceId);
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice remove(
		String itemPriceId) throws NoSuchItemPriceException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)session.get(ShoppingItemPriceHBM.class,
					itemPriceId);

			if (shoppingItemPriceHBM == null) {
				_log.warn(
					"No ShoppingItemPrice exists with the primary key of " +
					itemPriceId.toString());
				throw new NoSuchItemPriceException(itemPriceId.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice =
				ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM);
			session.delete(shoppingItemPriceHBM);
			session.flush();
			ShoppingItemPricePool.remove(itemPriceId);

			return shoppingItemPrice;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice update(
		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingItemPrice.isNew() || shoppingItemPrice.isModified()) {
				session = openSession();

				if (shoppingItemPrice.isNew()) {
					ShoppingItemPriceHBM shoppingItemPriceHBM = new ShoppingItemPriceHBM(shoppingItemPrice.getItemPriceId(),
							shoppingItemPrice.getItemId(),
							shoppingItemPrice.getMinQuantity(),
							shoppingItemPrice.getMaxQuantity(),
							shoppingItemPrice.getPrice(),
							shoppingItemPrice.getDiscount(),
							shoppingItemPrice.getTaxable(),
							shoppingItemPrice.getShipping(),
							shoppingItemPrice.getUseShippingFormula(),
							shoppingItemPrice.getStatus());
					session.save(shoppingItemPriceHBM);
					session.flush();
				}
				else {
					ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)session.get(ShoppingItemPriceHBM.class,
							shoppingItemPrice.getPrimaryKey());

					if (shoppingItemPriceHBM != null) {
						shoppingItemPriceHBM.setItemId(shoppingItemPrice.getItemId());
						shoppingItemPriceHBM.setMinQuantity(shoppingItemPrice.getMinQuantity());
						shoppingItemPriceHBM.setMaxQuantity(shoppingItemPrice.getMaxQuantity());
						shoppingItemPriceHBM.setPrice(shoppingItemPrice.getPrice());
						shoppingItemPriceHBM.setDiscount(shoppingItemPrice.getDiscount());
						shoppingItemPriceHBM.setTaxable(shoppingItemPrice.getTaxable());
						shoppingItemPriceHBM.setShipping(shoppingItemPrice.getShipping());
						shoppingItemPriceHBM.setUseShippingFormula(shoppingItemPrice.getUseShippingFormula());
						shoppingItemPriceHBM.setStatus(shoppingItemPrice.getStatus());
						session.flush();
					}
					else {
						shoppingItemPriceHBM = new ShoppingItemPriceHBM(shoppingItemPrice.getItemPriceId(),
								shoppingItemPrice.getItemId(),
								shoppingItemPrice.getMinQuantity(),
								shoppingItemPrice.getMaxQuantity(),
								shoppingItemPrice.getPrice(),
								shoppingItemPrice.getDiscount(),
								shoppingItemPrice.getTaxable(),
								shoppingItemPrice.getShipping(),
								shoppingItemPrice.getUseShippingFormula(),
								shoppingItemPrice.getStatus());
						session.save(shoppingItemPriceHBM);
						session.flush();
					}
				}

				shoppingItemPrice.setNew(false);
				shoppingItemPrice.setModified(false);
				shoppingItemPrice.protect();
				ShoppingItemPricePool.put(shoppingItemPrice.getPrimaryKey(),
					shoppingItemPrice);
			}

			return shoppingItemPrice;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice findByPrimaryKey(
		String itemPriceId) throws NoSuchItemPriceException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice = ShoppingItemPricePool.get(itemPriceId);
		Session session = null;

		try {
			if (shoppingItemPrice == null) {
				session = openSession();

				ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)session.get(ShoppingItemPriceHBM.class,
						itemPriceId);

				if (shoppingItemPriceHBM == null) {
					_log.warn(
						"No ShoppingItemPrice exists with the primary key of " +
						itemPriceId.toString());
					throw new NoSuchItemPriceException(itemPriceId.toString());
				}

				shoppingItemPrice = ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM);
			}

			return shoppingItemPrice;
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
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("itemPriceId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
				list.add(ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM));
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
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC").append(", ");
				query.append("itemPriceId ASC");
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
					ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
					list.add(ShoppingItemPriceHBMUtil.model(
							shoppingItemPriceHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)sr.get(0);
						list.add(ShoppingItemPriceHBMUtil.model(
								shoppingItemPriceHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingItemPrice findByItemId_First(
		String itemId, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		List list = findByItemId(itemId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchItemPriceException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItemPrice)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice findByItemId_Last(
		String itemId, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		int count = countByItemId(itemId);
		List list = findByItemId(itemId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchItemPriceException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItemPrice)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice[] findByItemId_PrevAndNext(
		String itemPriceId, String itemId, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice = findByPrimaryKey(itemPriceId);
		int count = countByItemId(itemId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC").append(", ");
				query.append("itemPriceId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			com.liferay.portlet.shopping.model.ShoppingItemPrice[] array = new com.liferay.portlet.shopping.model.ShoppingItemPrice[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)sr.get(0);

					if (shoppingItemPriceHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingItemPrice curShoppingItemPrice =
						ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM);
					int value = obc.compare(shoppingItemPrice,
							curShoppingItemPrice);

					if (value == 0) {
						if (!shoppingItemPrice.equals(curShoppingItemPrice)) {
							break;
						}

						array[1] = curShoppingItemPrice;

						if (sr.previous()) {
							array[0] = ShoppingItemPriceHBMUtil.model((ShoppingItemPriceHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingItemPriceHBMUtil.model((ShoppingItemPriceHBM)sr.get(
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

	public List findByI_S(String itemId, int status) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("itemPriceId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
				list.add(ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM));
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

	public List findByI_S(String itemId, int status, int begin, int end)
		throws SystemException {
		return findByI_S(itemId, status, begin, end, null);
	}

	public List findByI_S(String itemId, int status, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC").append(", ");
				query.append("itemPriceId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);
			q.setInteger(queryPos++, status);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
					list.add(ShoppingItemPriceHBMUtil.model(
							shoppingItemPriceHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)sr.get(0);
						list.add(ShoppingItemPriceHBMUtil.model(
								shoppingItemPriceHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingItemPrice findByI_S_First(
		String itemId, int status, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		List list = findByI_S(itemId, status, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchItemPriceException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItemPrice)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice findByI_S_Last(
		String itemId, int status, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		int count = countByI_S(itemId, status);
		List list = findByI_S(itemId, status, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchItemPriceException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItemPrice)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemPrice[] findByI_S_PrevAndNext(
		String itemPriceId, String itemId, int status, OrderByComparator obc)
		throws NoSuchItemPriceException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice = findByPrimaryKey(itemPriceId);
		int count = countByI_S(itemId, status);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC").append(", ");
				query.append("itemPriceId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);
			q.setInteger(queryPos++, status);

			com.liferay.portlet.shopping.model.ShoppingItemPrice[] array = new com.liferay.portlet.shopping.model.ShoppingItemPrice[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)sr.get(0);

					if (shoppingItemPriceHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingItemPrice curShoppingItemPrice =
						ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM);
					int value = obc.compare(shoppingItemPrice,
							curShoppingItemPrice);

					if (value == 0) {
						if (!shoppingItemPrice.equals(curShoppingItemPrice)) {
							break;
						}

						array[1] = curShoppingItemPrice;

						if (sr.previous()) {
							array[0] = ShoppingItemPriceHBMUtil.model((ShoppingItemPriceHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingItemPriceHBMUtil.model((ShoppingItemPriceHBM)sr.get(
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
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("itemPriceId ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
				list.add(ShoppingItemPriceHBMUtil.model(shoppingItemPriceHBM));
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

	public void removeByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("itemPriceId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
				ShoppingItemPricePool.remove((String)shoppingItemPriceHBM.getPrimaryKey());
				session.delete(shoppingItemPriceHBM);
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

	public void removeByI_S(String itemId, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("itemPriceId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemPriceHBM shoppingItemPriceHBM = (ShoppingItemPriceHBM)itr.next();
				ShoppingItemPricePool.remove((String)shoppingItemPriceHBM.getPrimaryKey());
				session.delete(shoppingItemPriceHBM);
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

	public int countByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
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

	public int countByI_S(String itemId, int status) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItemPrice IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceHBM WHERE ");
			query.append("itemId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);
			q.setInteger(queryPos++, status);

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

	private static final Log _log = LogFactory.getLog(ShoppingItemPricePersistence.class);
}
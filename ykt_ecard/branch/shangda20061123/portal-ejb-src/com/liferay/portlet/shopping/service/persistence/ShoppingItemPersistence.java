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

import com.liferay.portlet.shopping.NoSuchItemException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingItemPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemPersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingItem create(String itemId) {
		return new com.liferay.portlet.shopping.model.ShoppingItem(itemId);
	}

	public com.liferay.portlet.shopping.model.ShoppingItem remove(String itemId)
		throws NoSuchItemException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)session.get(ShoppingItemHBM.class,
					itemId);

			if (shoppingItemHBM == null) {
				_log.warn("No ShoppingItem exists with the primary key of " +
					itemId.toString());
				throw new NoSuchItemException(itemId.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingItem shoppingItem = ShoppingItemHBMUtil.model(shoppingItemHBM);
			session.delete(shoppingItemHBM);
			session.flush();
			ShoppingItemPool.remove(itemId);

			return shoppingItem;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem update(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingItem.isNew() || shoppingItem.isModified()) {
				session = openSession();

				if (shoppingItem.isNew()) {
					ShoppingItemHBM shoppingItemHBM = new ShoppingItemHBM(shoppingItem.getItemId(),
							shoppingItem.getCompanyId(),
							shoppingItem.getCreateDate(),
							shoppingItem.getModifiedDate(),
							shoppingItem.getCategoryId(),
							shoppingItem.getSku(), shoppingItem.getName(),
							shoppingItem.getDescription(),
							shoppingItem.getProperties(),
							shoppingItem.getSupplierUserId(),
							shoppingItem.getFields(),
							shoppingItem.getFieldsQuantities(),
							shoppingItem.getMinQuantity(),
							shoppingItem.getMaxQuantity(),
							shoppingItem.getPrice(),
							shoppingItem.getDiscount(),
							shoppingItem.getTaxable(),
							shoppingItem.getShipping(),
							shoppingItem.getUseShippingFormula(),
							shoppingItem.getRequiresShipping(),
							shoppingItem.getStockQuantity(),
							shoppingItem.getFeatured(), shoppingItem.getSale(),
							shoppingItem.getSmallImage(),
							shoppingItem.getSmallImageURL(),
							shoppingItem.getMediumImage(),
							shoppingItem.getMediumImageURL(),
							shoppingItem.getLargeImage(),
							shoppingItem.getLargeImageURL());
					session.save(shoppingItemHBM);
					session.flush();
				}
				else {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)session.get(ShoppingItemHBM.class,
							shoppingItem.getPrimaryKey());

					if (shoppingItemHBM != null) {
						shoppingItemHBM.setCompanyId(shoppingItem.getCompanyId());
						shoppingItemHBM.setCreateDate(shoppingItem.getCreateDate());
						shoppingItemHBM.setModifiedDate(shoppingItem.getModifiedDate());
						shoppingItemHBM.setCategoryId(shoppingItem.getCategoryId());
						shoppingItemHBM.setSku(shoppingItem.getSku());
						shoppingItemHBM.setName(shoppingItem.getName());
						shoppingItemHBM.setDescription(shoppingItem.getDescription());
						shoppingItemHBM.setProperties(shoppingItem.getProperties());
						shoppingItemHBM.setSupplierUserId(shoppingItem.getSupplierUserId());
						shoppingItemHBM.setFields(shoppingItem.getFields());
						shoppingItemHBM.setFieldsQuantities(shoppingItem.getFieldsQuantities());
						shoppingItemHBM.setMinQuantity(shoppingItem.getMinQuantity());
						shoppingItemHBM.setMaxQuantity(shoppingItem.getMaxQuantity());
						shoppingItemHBM.setPrice(shoppingItem.getPrice());
						shoppingItemHBM.setDiscount(shoppingItem.getDiscount());
						shoppingItemHBM.setTaxable(shoppingItem.getTaxable());
						shoppingItemHBM.setShipping(shoppingItem.getShipping());
						shoppingItemHBM.setUseShippingFormula(shoppingItem.getUseShippingFormula());
						shoppingItemHBM.setRequiresShipping(shoppingItem.getRequiresShipping());
						shoppingItemHBM.setStockQuantity(shoppingItem.getStockQuantity());
						shoppingItemHBM.setFeatured(shoppingItem.getFeatured());
						shoppingItemHBM.setSale(shoppingItem.getSale());
						shoppingItemHBM.setSmallImage(shoppingItem.getSmallImage());
						shoppingItemHBM.setSmallImageURL(shoppingItem.getSmallImageURL());
						shoppingItemHBM.setMediumImage(shoppingItem.getMediumImage());
						shoppingItemHBM.setMediumImageURL(shoppingItem.getMediumImageURL());
						shoppingItemHBM.setLargeImage(shoppingItem.getLargeImage());
						shoppingItemHBM.setLargeImageURL(shoppingItem.getLargeImageURL());
						session.flush();
					}
					else {
						shoppingItemHBM = new ShoppingItemHBM(shoppingItem.getItemId(),
								shoppingItem.getCompanyId(),
								shoppingItem.getCreateDate(),
								shoppingItem.getModifiedDate(),
								shoppingItem.getCategoryId(),
								shoppingItem.getSku(), shoppingItem.getName(),
								shoppingItem.getDescription(),
								shoppingItem.getProperties(),
								shoppingItem.getSupplierUserId(),
								shoppingItem.getFields(),
								shoppingItem.getFieldsQuantities(),
								shoppingItem.getMinQuantity(),
								shoppingItem.getMaxQuantity(),
								shoppingItem.getPrice(),
								shoppingItem.getDiscount(),
								shoppingItem.getTaxable(),
								shoppingItem.getShipping(),
								shoppingItem.getUseShippingFormula(),
								shoppingItem.getRequiresShipping(),
								shoppingItem.getStockQuantity(),
								shoppingItem.getFeatured(),
								shoppingItem.getSale(),
								shoppingItem.getSmallImage(),
								shoppingItem.getSmallImageURL(),
								shoppingItem.getMediumImage(),
								shoppingItem.getMediumImageURL(),
								shoppingItem.getLargeImage(),
								shoppingItem.getLargeImageURL());
						session.save(shoppingItemHBM);
						session.flush();
					}
				}

				shoppingItem.setNew(false);
				shoppingItem.setModified(false);
				shoppingItem.protect();
				ShoppingItemPool.put(shoppingItem.getPrimaryKey(), shoppingItem);
			}

			return shoppingItem;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem findByPrimaryKey(
		String itemId) throws NoSuchItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem = ShoppingItemPool.get(itemId);
		Session session = null;

		try {
			if (shoppingItem == null) {
				session = openSession();

				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)session.get(ShoppingItemHBM.class,
						itemId);

				if (shoppingItemHBM == null) {
					_log.warn("No ShoppingItem exists with the primary key of " +
						itemId.toString());
					throw new NoSuchItemException(itemId.toString());
				}

				shoppingItem = ShoppingItemHBMUtil.model(shoppingItemHBM);
			}

			return shoppingItem;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
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

	public List findByCompanyId(String companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(String companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
					list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)sr.get(0);
						list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingItem findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem[] findByCompanyId_PrevAndNext(
		String itemId, String companyId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem = findByPrimaryKey(itemId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.shopping.model.ShoppingItem[] array = new com.liferay.portlet.shopping.model.ShoppingItem[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)sr.get(0);

					if (shoppingItemHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingItem curShoppingItem =
						ShoppingItemHBMUtil.model(shoppingItemHBM);
					int value = obc.compare(shoppingItem, curShoppingItem);

					if (value == 0) {
						if (!shoppingItem.equals(curShoppingItem)) {
							break;
						}

						array[1] = curShoppingItem;

						if (sr.previous()) {
							array[0] = ShoppingItemHBMUtil.model((ShoppingItemHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingItemHBMUtil.model((ShoppingItemHBM)sr.get(
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

	public List findBySupplierUserId(String supplierUserId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("supplierUserId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, supplierUserId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
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

	public List findBySupplierUserId(String supplierUserId, int begin, int end)
		throws SystemException {
		return findBySupplierUserId(supplierUserId, begin, end, null);
	}

	public List findBySupplierUserId(String supplierUserId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("supplierUserId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, supplierUserId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
					list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)sr.get(0);
						list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingItem findBySupplierUserId_First(
		String supplierUserId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		List list = findBySupplierUserId(supplierUserId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem findBySupplierUserId_Last(
		String supplierUserId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		int count = countBySupplierUserId(supplierUserId);
		List list = findBySupplierUserId(supplierUserId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem[] findBySupplierUserId_PrevAndNext(
		String itemId, String supplierUserId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem = findByPrimaryKey(itemId);
		int count = countBySupplierUserId(supplierUserId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("supplierUserId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, supplierUserId);

			com.liferay.portlet.shopping.model.ShoppingItem[] array = new com.liferay.portlet.shopping.model.ShoppingItem[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)sr.get(0);

					if (shoppingItemHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingItem curShoppingItem =
						ShoppingItemHBMUtil.model(shoppingItemHBM);
					int value = obc.compare(shoppingItem, curShoppingItem);

					if (value == 0) {
						if (!shoppingItem.equals(curShoppingItem)) {
							break;
						}

						array[1] = curShoppingItem;

						if (sr.previous()) {
							array[0] = ShoppingItemHBMUtil.model((ShoppingItemHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingItemHBMUtil.model((ShoppingItemHBM)sr.get(
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

	public List findByC_C(String companyId, String categoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, categoryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
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

	public List findByC_C(String companyId, String categoryId, int begin,
		int end) throws SystemException {
		return findByC_C(companyId, categoryId, begin, end, null);
	}

	public List findByC_C(String companyId, String categoryId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, categoryId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
					list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)sr.get(0);
						list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingItem findByC_C_First(
		String companyId, String categoryId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		List list = findByC_C(companyId, categoryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem findByC_C_Last(
		String companyId, String categoryId, OrderByComparator obc)
		throws NoSuchItemException, SystemException {
		int count = countByC_C(companyId, categoryId);
		List list = findByC_C(companyId, categoryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchItemException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItem)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItem[] findByC_C_PrevAndNext(
		String itemId, String companyId, String categoryId,
		OrderByComparator obc) throws NoSuchItemException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem = findByPrimaryKey(itemId);
		int count = countByC_C(companyId, categoryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, categoryId);

			com.liferay.portlet.shopping.model.ShoppingItem[] array = new com.liferay.portlet.shopping.model.ShoppingItem[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)sr.get(0);

					if (shoppingItemHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingItem curShoppingItem =
						ShoppingItemHBMUtil.model(shoppingItemHBM);
					int value = obc.compare(shoppingItem, curShoppingItem);

					if (value == 0) {
						if (!shoppingItem.equals(curShoppingItem)) {
							break;
						}

						array[1] = curShoppingItem;

						if (sr.previous()) {
							array[0] = ShoppingItemHBMUtil.model((ShoppingItemHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingItemHBMUtil.model((ShoppingItemHBM)sr.get(
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

	public com.liferay.portlet.shopping.model.ShoppingItem findByC_S(
		String companyId, String sku)
		throws NoSuchItemException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sku = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, sku);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchItemException();
			}

			ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();

			return ShoppingItemHBMUtil.model(shoppingItemHBM);
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
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				list.add(ShoppingItemHBMUtil.model(shoppingItemHBM));
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

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				ShoppingItemPool.remove((String)shoppingItemHBM.getPrimaryKey());
				session.delete(shoppingItemHBM);
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

	public void removeBySupplierUserId(String supplierUserId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("supplierUserId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, supplierUserId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				ShoppingItemPool.remove((String)shoppingItemHBM.getPrimaryKey());
				session.delete(shoppingItemHBM);
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

	public void removeByC_C(String companyId, String categoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, categoryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				ShoppingItemPool.remove((String)shoppingItemHBM.getPrimaryKey());
				session.delete(shoppingItemHBM);
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

	public void removeByC_S(String companyId, String sku)
		throws NoSuchItemException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sku = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, sku);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemHBM shoppingItemHBM = (ShoppingItemHBM)itr.next();
				ShoppingItemPool.remove((String)shoppingItemHBM.getPrimaryKey());
				session.delete(shoppingItemHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchItemException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

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

	public int countBySupplierUserId(String supplierUserId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("supplierUserId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, supplierUserId);

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

	public int countByC_C(String companyId, String categoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("categoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, categoryId);

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

	public int countByC_S(String companyId, String sku)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItem IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sku = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, sku);

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

	private static final Log _log = LogFactory.getLog(ShoppingItemPersistence.class);
}
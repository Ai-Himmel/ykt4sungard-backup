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

import com.liferay.portlet.shopping.NoSuchCouponException;

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
 * <a href="ShoppingCouponPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCouponPersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingCoupon create(
		String couponId) {
		return new com.liferay.portlet.shopping.model.ShoppingCoupon(couponId);
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon remove(
		String couponId) throws NoSuchCouponException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)session.get(ShoppingCouponHBM.class,
					couponId);

			if (shoppingCouponHBM == null) {
				_log.warn("No ShoppingCoupon exists with the primary key of " +
					couponId.toString());
				throw new NoSuchCouponException(couponId.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingCoupon shoppingCoupon = ShoppingCouponHBMUtil.model(shoppingCouponHBM);
			session.delete(shoppingCouponHBM);
			session.flush();
			ShoppingCouponPool.remove(couponId);

			return shoppingCoupon;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon update(
		com.liferay.portlet.shopping.model.ShoppingCoupon shoppingCoupon)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingCoupon.isNew() || shoppingCoupon.isModified()) {
				session = openSession();

				if (shoppingCoupon.isNew()) {
					ShoppingCouponHBM shoppingCouponHBM = new ShoppingCouponHBM(shoppingCoupon.getCouponId(),
							shoppingCoupon.getCompanyId(),
							shoppingCoupon.getCreateDate(),
							shoppingCoupon.getModifiedDate(),
							shoppingCoupon.getName(),
							shoppingCoupon.getDescription(),
							shoppingCoupon.getStartDate(),
							shoppingCoupon.getEndDate(),
							shoppingCoupon.getActive(),
							shoppingCoupon.getLimitCategories(),
							shoppingCoupon.getLimitSkus(),
							shoppingCoupon.getMinOrder(),
							shoppingCoupon.getDiscount(),
							shoppingCoupon.getDiscountType());
					session.save(shoppingCouponHBM);
					session.flush();
				}
				else {
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)session.get(ShoppingCouponHBM.class,
							shoppingCoupon.getPrimaryKey());

					if (shoppingCouponHBM != null) {
						shoppingCouponHBM.setCompanyId(shoppingCoupon.getCompanyId());
						shoppingCouponHBM.setCreateDate(shoppingCoupon.getCreateDate());
						shoppingCouponHBM.setModifiedDate(shoppingCoupon.getModifiedDate());
						shoppingCouponHBM.setName(shoppingCoupon.getName());
						shoppingCouponHBM.setDescription(shoppingCoupon.getDescription());
						shoppingCouponHBM.setStartDate(shoppingCoupon.getStartDate());
						shoppingCouponHBM.setEndDate(shoppingCoupon.getEndDate());
						shoppingCouponHBM.setActive(shoppingCoupon.getActive());
						shoppingCouponHBM.setLimitCategories(shoppingCoupon.getLimitCategories());
						shoppingCouponHBM.setLimitSkus(shoppingCoupon.getLimitSkus());
						shoppingCouponHBM.setMinOrder(shoppingCoupon.getMinOrder());
						shoppingCouponHBM.setDiscount(shoppingCoupon.getDiscount());
						shoppingCouponHBM.setDiscountType(shoppingCoupon.getDiscountType());
						session.flush();
					}
					else {
						shoppingCouponHBM = new ShoppingCouponHBM(shoppingCoupon.getCouponId(),
								shoppingCoupon.getCompanyId(),
								shoppingCoupon.getCreateDate(),
								shoppingCoupon.getModifiedDate(),
								shoppingCoupon.getName(),
								shoppingCoupon.getDescription(),
								shoppingCoupon.getStartDate(),
								shoppingCoupon.getEndDate(),
								shoppingCoupon.getActive(),
								shoppingCoupon.getLimitCategories(),
								shoppingCoupon.getLimitSkus(),
								shoppingCoupon.getMinOrder(),
								shoppingCoupon.getDiscount(),
								shoppingCoupon.getDiscountType());
						session.save(shoppingCouponHBM);
						session.flush();
					}
				}

				shoppingCoupon.setNew(false);
				shoppingCoupon.setModified(false);
				shoppingCoupon.protect();
				ShoppingCouponPool.put(shoppingCoupon.getPrimaryKey(),
					shoppingCoupon);
			}

			return shoppingCoupon;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByPrimaryKey(
		String couponId) throws NoSuchCouponException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCoupon shoppingCoupon = ShoppingCouponPool.get(couponId);
		Session session = null;

		try {
			if (shoppingCoupon == null) {
				session = openSession();

				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)session.get(ShoppingCouponHBM.class,
						couponId);

				if (shoppingCouponHBM == null) {
					_log.warn(
						"No ShoppingCoupon exists with the primary key of " +
						couponId.toString());
					throw new NoSuchCouponException(couponId.toString());
				}

				shoppingCoupon = ShoppingCouponHBMUtil.model(shoppingCouponHBM);
			}

			return shoppingCoupon;
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
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
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
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
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
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
					list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)sr.get(0);
						list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchCouponException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCouponException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCoupon)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchCouponException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCouponException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCoupon)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon[] findByCompanyId_PrevAndNext(
		String couponId, String companyId, OrderByComparator obc)
		throws NoSuchCouponException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCoupon shoppingCoupon = findByPrimaryKey(couponId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.shopping.model.ShoppingCoupon[] array = new com.liferay.portlet.shopping.model.ShoppingCoupon[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)sr.get(0);

					if (shoppingCouponHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingCoupon curShoppingCoupon =
						ShoppingCouponHBMUtil.model(shoppingCouponHBM);
					int value = obc.compare(shoppingCoupon, curShoppingCoupon);

					if (value == 0) {
						if (!shoppingCoupon.equals(curShoppingCoupon)) {
							break;
						}

						array[1] = curShoppingCoupon;

						if (sr.previous()) {
							array[0] = ShoppingCouponHBMUtil.model((ShoppingCouponHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingCouponHBMUtil.model((ShoppingCouponHBM)sr.get(
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

	public List findByC_A(String companyId, boolean active)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
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

	public List findByC_A(String companyId, boolean active, int begin, int end)
		throws SystemException {
		return findByC_A(companyId, active, begin, end, null);
	}

	public List findByC_A(String companyId, boolean active, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
					list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)sr.get(0);
						list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByC_A_First(
		String companyId, boolean active, OrderByComparator obc)
		throws NoSuchCouponException, SystemException {
		List list = findByC_A(companyId, active, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCouponException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCoupon)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByC_A_Last(
		String companyId, boolean active, OrderByComparator obc)
		throws NoSuchCouponException, SystemException {
		int count = countByC_A(companyId, active);
		List list = findByC_A(companyId, active, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCouponException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCoupon)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon[] findByC_A_PrevAndNext(
		String couponId, String companyId, boolean active, OrderByComparator obc)
		throws NoSuchCouponException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCoupon shoppingCoupon = findByPrimaryKey(couponId);
		int count = countByC_A(companyId, active);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);

			com.liferay.portlet.shopping.model.ShoppingCoupon[] array = new com.liferay.portlet.shopping.model.ShoppingCoupon[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)sr.get(0);

					if (shoppingCouponHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingCoupon curShoppingCoupon =
						ShoppingCouponHBMUtil.model(shoppingCouponHBM);
					int value = obc.compare(shoppingCoupon, curShoppingCoupon);

					if (value == 0) {
						if (!shoppingCoupon.equals(curShoppingCoupon)) {
							break;
						}

						array[1] = curShoppingCoupon;

						if (sr.previous()) {
							array[0] = ShoppingCouponHBMUtil.model((ShoppingCouponHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingCouponHBMUtil.model((ShoppingCouponHBM)sr.get(
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

	public List findByC_A_D(String companyId, boolean active,
		String discountType) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" AND ");
			query.append("discountType = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);
			q.setString(queryPos++, discountType);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
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

	public List findByC_A_D(String companyId, boolean active,
		String discountType, int begin, int end) throws SystemException {
		return findByC_A_D(companyId, active, discountType, begin, end, null);
	}

	public List findByC_A_D(String companyId, boolean active,
		String discountType, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" AND ");
			query.append("discountType = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);
			q.setString(queryPos++, discountType);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
					list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)sr.get(0);
						list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByC_A_D_First(
		String companyId, boolean active, String discountType,
		OrderByComparator obc) throws NoSuchCouponException, SystemException {
		List list = findByC_A_D(companyId, active, discountType, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCouponException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCoupon)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon findByC_A_D_Last(
		String companyId, boolean active, String discountType,
		OrderByComparator obc) throws NoSuchCouponException, SystemException {
		int count = countByC_A_D(companyId, active, discountType);
		List list = findByC_A_D(companyId, active, discountType, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchCouponException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCoupon)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCoupon[] findByC_A_D_PrevAndNext(
		String couponId, String companyId, boolean active, String discountType,
		OrderByComparator obc) throws NoSuchCouponException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCoupon shoppingCoupon = findByPrimaryKey(couponId);
		int count = countByC_A_D(companyId, active, discountType);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" AND ");
			query.append("discountType = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);
			q.setString(queryPos++, discountType);

			com.liferay.portlet.shopping.model.ShoppingCoupon[] array = new com.liferay.portlet.shopping.model.ShoppingCoupon[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)sr.get(0);

					if (shoppingCouponHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingCoupon curShoppingCoupon =
						ShoppingCouponHBMUtil.model(shoppingCouponHBM);
					int value = obc.compare(shoppingCoupon, curShoppingCoupon);

					if (value == 0) {
						if (!shoppingCoupon.equals(curShoppingCoupon)) {
							break;
						}

						array[1] = curShoppingCoupon;

						if (sr.previous()) {
							array[0] = ShoppingCouponHBMUtil.model((ShoppingCouponHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingCouponHBMUtil.model((ShoppingCouponHBM)sr.get(
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
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				list.add(ShoppingCouponHBMUtil.model(shoppingCouponHBM));
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
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				ShoppingCouponPool.remove((String)shoppingCouponHBM.getPrimaryKey());
				session.delete(shoppingCouponHBM);
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

	public void removeByC_A(String companyId, boolean active)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				ShoppingCouponPool.remove((String)shoppingCouponHBM.getPrimaryKey());
				session.delete(shoppingCouponHBM);
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

	public void removeByC_A_D(String companyId, boolean active,
		String discountType) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" AND ");
			query.append("discountType = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);
			q.setString(queryPos++, discountType);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingCouponHBM shoppingCouponHBM = (ShoppingCouponHBM)itr.next();
				ShoppingCouponPool.remove((String)shoppingCouponHBM.getPrimaryKey());
				session.delete(shoppingCouponHBM);
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

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
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

	public int countByC_A(String companyId, boolean active)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);

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

	public int countByC_A_D(String companyId, boolean active,
		String discountType) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingCoupon IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCouponHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("active_ = ?");
			query.append(" AND ");
			query.append("discountType = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, active);
			q.setString(queryPos++, discountType);

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

	private static final Log _log = LogFactory.getLog(ShoppingCouponPersistence.class);
}
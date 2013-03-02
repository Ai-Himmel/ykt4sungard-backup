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

import com.liferay.portlet.shopping.NoSuchOrderException;

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
 * <a href="ShoppingOrderPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderPersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingOrder create(
		String orderId) {
		return new com.liferay.portlet.shopping.model.ShoppingOrder(orderId);
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder remove(
		String orderId) throws NoSuchOrderException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)session.get(ShoppingOrderHBM.class,
					orderId);

			if (shoppingOrderHBM == null) {
				_log.warn("No ShoppingOrder exists with the primary key of " +
					orderId.toString());
				throw new NoSuchOrderException(orderId.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = ShoppingOrderHBMUtil.model(shoppingOrderHBM);
			session.delete(shoppingOrderHBM);
			session.flush();
			ShoppingOrderPool.remove(orderId);

			return shoppingOrder;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder update(
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingOrder.isNew() || shoppingOrder.isModified()) {
				session = openSession();

				if (shoppingOrder.isNew()) {
					ShoppingOrderHBM shoppingOrderHBM = new ShoppingOrderHBM(shoppingOrder.getOrderId(),
							shoppingOrder.getCompanyId(),
							shoppingOrder.getUserId(),
							shoppingOrder.getCreateDate(),
							shoppingOrder.getModifiedDate(),
							shoppingOrder.getTax(),
							shoppingOrder.getShipping(),
							shoppingOrder.getAltShipping(),
							shoppingOrder.getRequiresShipping(),
							shoppingOrder.getInsure(),
							shoppingOrder.getInsurance(),
							shoppingOrder.getCouponIds(),
							shoppingOrder.getCouponDiscount(),
							shoppingOrder.getBillingFirstName(),
							shoppingOrder.getBillingLastName(),
							shoppingOrder.getBillingEmailAddress(),
							shoppingOrder.getBillingCompany(),
							shoppingOrder.getBillingStreet(),
							shoppingOrder.getBillingCity(),
							shoppingOrder.getBillingState(),
							shoppingOrder.getBillingZip(),
							shoppingOrder.getBillingCountry(),
							shoppingOrder.getBillingPhone(),
							shoppingOrder.getShipToBilling(),
							shoppingOrder.getShippingFirstName(),
							shoppingOrder.getShippingLastName(),
							shoppingOrder.getShippingEmailAddress(),
							shoppingOrder.getShippingCompany(),
							shoppingOrder.getShippingStreet(),
							shoppingOrder.getShippingCity(),
							shoppingOrder.getShippingState(),
							shoppingOrder.getShippingZip(),
							shoppingOrder.getShippingCountry(),
							shoppingOrder.getShippingPhone(),
							shoppingOrder.getCcName(),
							shoppingOrder.getCcType(),
							shoppingOrder.getCcNumber(),
							shoppingOrder.getCcExpMonth(),
							shoppingOrder.getCcExpYear(),
							shoppingOrder.getCcVerNumber(),
							shoppingOrder.getComments(),
							shoppingOrder.getPpTxnId(),
							shoppingOrder.getPpPaymentStatus(),
							shoppingOrder.getPpPaymentGross(),
							shoppingOrder.getPpReceiverEmail(),
							shoppingOrder.getPpPayerEmail(),
							shoppingOrder.getSendOrderEmail(),
							shoppingOrder.getSendShippingEmail());
					session.save(shoppingOrderHBM);
					session.flush();
				}
				else {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)session.get(ShoppingOrderHBM.class,
							shoppingOrder.getPrimaryKey());

					if (shoppingOrderHBM != null) {
						shoppingOrderHBM.setCompanyId(shoppingOrder.getCompanyId());
						shoppingOrderHBM.setUserId(shoppingOrder.getUserId());
						shoppingOrderHBM.setCreateDate(shoppingOrder.getCreateDate());
						shoppingOrderHBM.setModifiedDate(shoppingOrder.getModifiedDate());
						shoppingOrderHBM.setTax(shoppingOrder.getTax());
						shoppingOrderHBM.setShipping(shoppingOrder.getShipping());
						shoppingOrderHBM.setAltShipping(shoppingOrder.getAltShipping());
						shoppingOrderHBM.setRequiresShipping(shoppingOrder.getRequiresShipping());
						shoppingOrderHBM.setInsure(shoppingOrder.getInsure());
						shoppingOrderHBM.setInsurance(shoppingOrder.getInsurance());
						shoppingOrderHBM.setCouponIds(shoppingOrder.getCouponIds());
						shoppingOrderHBM.setCouponDiscount(shoppingOrder.getCouponDiscount());
						shoppingOrderHBM.setBillingFirstName(shoppingOrder.getBillingFirstName());
						shoppingOrderHBM.setBillingLastName(shoppingOrder.getBillingLastName());
						shoppingOrderHBM.setBillingEmailAddress(shoppingOrder.getBillingEmailAddress());
						shoppingOrderHBM.setBillingCompany(shoppingOrder.getBillingCompany());
						shoppingOrderHBM.setBillingStreet(shoppingOrder.getBillingStreet());
						shoppingOrderHBM.setBillingCity(shoppingOrder.getBillingCity());
						shoppingOrderHBM.setBillingState(shoppingOrder.getBillingState());
						shoppingOrderHBM.setBillingZip(shoppingOrder.getBillingZip());
						shoppingOrderHBM.setBillingCountry(shoppingOrder.getBillingCountry());
						shoppingOrderHBM.setBillingPhone(shoppingOrder.getBillingPhone());
						shoppingOrderHBM.setShipToBilling(shoppingOrder.getShipToBilling());
						shoppingOrderHBM.setShippingFirstName(shoppingOrder.getShippingFirstName());
						shoppingOrderHBM.setShippingLastName(shoppingOrder.getShippingLastName());
						shoppingOrderHBM.setShippingEmailAddress(shoppingOrder.getShippingEmailAddress());
						shoppingOrderHBM.setShippingCompany(shoppingOrder.getShippingCompany());
						shoppingOrderHBM.setShippingStreet(shoppingOrder.getShippingStreet());
						shoppingOrderHBM.setShippingCity(shoppingOrder.getShippingCity());
						shoppingOrderHBM.setShippingState(shoppingOrder.getShippingState());
						shoppingOrderHBM.setShippingZip(shoppingOrder.getShippingZip());
						shoppingOrderHBM.setShippingCountry(shoppingOrder.getShippingCountry());
						shoppingOrderHBM.setShippingPhone(shoppingOrder.getShippingPhone());
						shoppingOrderHBM.setCcName(shoppingOrder.getCcName());
						shoppingOrderHBM.setCcType(shoppingOrder.getCcType());
						shoppingOrderHBM.setCcNumber(shoppingOrder.getCcNumber());
						shoppingOrderHBM.setCcExpMonth(shoppingOrder.getCcExpMonth());
						shoppingOrderHBM.setCcExpYear(shoppingOrder.getCcExpYear());
						shoppingOrderHBM.setCcVerNumber(shoppingOrder.getCcVerNumber());
						shoppingOrderHBM.setComments(shoppingOrder.getComments());
						shoppingOrderHBM.setPpTxnId(shoppingOrder.getPpTxnId());
						shoppingOrderHBM.setPpPaymentStatus(shoppingOrder.getPpPaymentStatus());
						shoppingOrderHBM.setPpPaymentGross(shoppingOrder.getPpPaymentGross());
						shoppingOrderHBM.setPpReceiverEmail(shoppingOrder.getPpReceiverEmail());
						shoppingOrderHBM.setPpPayerEmail(shoppingOrder.getPpPayerEmail());
						shoppingOrderHBM.setSendOrderEmail(shoppingOrder.getSendOrderEmail());
						shoppingOrderHBM.setSendShippingEmail(shoppingOrder.getSendShippingEmail());
						session.flush();
					}
					else {
						shoppingOrderHBM = new ShoppingOrderHBM(shoppingOrder.getOrderId(),
								shoppingOrder.getCompanyId(),
								shoppingOrder.getUserId(),
								shoppingOrder.getCreateDate(),
								shoppingOrder.getModifiedDate(),
								shoppingOrder.getTax(),
								shoppingOrder.getShipping(),
								shoppingOrder.getAltShipping(),
								shoppingOrder.getRequiresShipping(),
								shoppingOrder.getInsure(),
								shoppingOrder.getInsurance(),
								shoppingOrder.getCouponIds(),
								shoppingOrder.getCouponDiscount(),
								shoppingOrder.getBillingFirstName(),
								shoppingOrder.getBillingLastName(),
								shoppingOrder.getBillingEmailAddress(),
								shoppingOrder.getBillingCompany(),
								shoppingOrder.getBillingStreet(),
								shoppingOrder.getBillingCity(),
								shoppingOrder.getBillingState(),
								shoppingOrder.getBillingZip(),
								shoppingOrder.getBillingCountry(),
								shoppingOrder.getBillingPhone(),
								shoppingOrder.getShipToBilling(),
								shoppingOrder.getShippingFirstName(),
								shoppingOrder.getShippingLastName(),
								shoppingOrder.getShippingEmailAddress(),
								shoppingOrder.getShippingCompany(),
								shoppingOrder.getShippingStreet(),
								shoppingOrder.getShippingCity(),
								shoppingOrder.getShippingState(),
								shoppingOrder.getShippingZip(),
								shoppingOrder.getShippingCountry(),
								shoppingOrder.getShippingPhone(),
								shoppingOrder.getCcName(),
								shoppingOrder.getCcType(),
								shoppingOrder.getCcNumber(),
								shoppingOrder.getCcExpMonth(),
								shoppingOrder.getCcExpYear(),
								shoppingOrder.getCcVerNumber(),
								shoppingOrder.getComments(),
								shoppingOrder.getPpTxnId(),
								shoppingOrder.getPpPaymentStatus(),
								shoppingOrder.getPpPaymentGross(),
								shoppingOrder.getPpReceiverEmail(),
								shoppingOrder.getPpPayerEmail(),
								shoppingOrder.getSendOrderEmail(),
								shoppingOrder.getSendShippingEmail());
						session.save(shoppingOrderHBM);
						session.flush();
					}
				}

				shoppingOrder.setNew(false);
				shoppingOrder.setModified(false);
				shoppingOrder.protect();
				ShoppingOrderPool.put(shoppingOrder.getPrimaryKey(),
					shoppingOrder);
			}

			return shoppingOrder;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder findByPrimaryKey(
		String orderId) throws NoSuchOrderException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = ShoppingOrderPool.get(orderId);
		Session session = null;

		try {
			if (shoppingOrder == null) {
				session = openSession();

				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)session.get(ShoppingOrderHBM.class,
						orderId);

				if (shoppingOrderHBM == null) {
					_log.warn(
						"No ShoppingOrder exists with the primary key of " +
						orderId.toString());
					throw new NoSuchOrderException(orderId.toString());
				}

				shoppingOrder = ShoppingOrderHBMUtil.model(shoppingOrderHBM);
			}

			return shoppingOrder;
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
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
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
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
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
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
					list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);
						list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingOrder findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder[] findByCompanyId_PrevAndNext(
		String orderId, String companyId, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = findByPrimaryKey(orderId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.shopping.model.ShoppingOrder[] array = new com.liferay.portlet.shopping.model.ShoppingOrder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);

					if (shoppingOrderHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingOrder curShoppingOrder =
						ShoppingOrderHBMUtil.model(shoppingOrderHBM);
					int value = obc.compare(shoppingOrder, curShoppingOrder);

					if (value == 0) {
						if (!shoppingOrder.equals(curShoppingOrder)) {
							break;
						}

						array[1] = curShoppingOrder;

						if (sr.previous()) {
							array[0] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
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

	public List findByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
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

	public List findByUserId(String userId, int begin, int end)
		throws SystemException {
		return findByUserId(userId, begin, end, null);
	}

	public List findByUserId(String userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
					list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);
						list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingOrder findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder[] findByUserId_PrevAndNext(
		String orderId, String userId, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = findByPrimaryKey(orderId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.shopping.model.ShoppingOrder[] array = new com.liferay.portlet.shopping.model.ShoppingOrder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);

					if (shoppingOrderHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingOrder curShoppingOrder =
						ShoppingOrderHBMUtil.model(shoppingOrderHBM);
					int value = obc.compare(shoppingOrder, curShoppingOrder);

					if (value == 0) {
						if (!shoppingOrder.equals(curShoppingOrder)) {
							break;
						}

						array[1] = curShoppingOrder;

						if (sr.previous()) {
							array[0] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
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

	public List findByC_PPPS(String companyId, String ppPaymentStatus)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, ppPaymentStatus);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
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

	public List findByC_PPPS(String companyId, String ppPaymentStatus,
		int begin, int end) throws SystemException {
		return findByC_PPPS(companyId, ppPaymentStatus, begin, end, null);
	}

	public List findByC_PPPS(String companyId, String ppPaymentStatus,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, ppPaymentStatus);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
					list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);
						list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingOrder findByC_PPPS_First(
		String companyId, String ppPaymentStatus, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		List list = findByC_PPPS(companyId, ppPaymentStatus, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder findByC_PPPS_Last(
		String companyId, String ppPaymentStatus, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		int count = countByC_PPPS(companyId, ppPaymentStatus);
		List list = findByC_PPPS(companyId, ppPaymentStatus, count - 1, count,
				obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder[] findByC_PPPS_PrevAndNext(
		String orderId, String companyId, String ppPaymentStatus,
		OrderByComparator obc) throws NoSuchOrderException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = findByPrimaryKey(orderId);
		int count = countByC_PPPS(companyId, ppPaymentStatus);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, ppPaymentStatus);

			com.liferay.portlet.shopping.model.ShoppingOrder[] array = new com.liferay.portlet.shopping.model.ShoppingOrder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);

					if (shoppingOrderHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingOrder curShoppingOrder =
						ShoppingOrderHBMUtil.model(shoppingOrderHBM);
					int value = obc.compare(shoppingOrder, curShoppingOrder);

					if (value == 0) {
						if (!shoppingOrder.equals(curShoppingOrder)) {
							break;
						}

						array[1] = curShoppingOrder;

						if (sr.previous()) {
							array[0] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
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

	public List findByU_PPPS(String userId, String ppPaymentStatus)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, ppPaymentStatus);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
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

	public List findByU_PPPS(String userId, String ppPaymentStatus, int begin,
		int end) throws SystemException {
		return findByU_PPPS(userId, ppPaymentStatus, begin, end, null);
	}

	public List findByU_PPPS(String userId, String ppPaymentStatus, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, ppPaymentStatus);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
					list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);
						list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingOrder findByU_PPPS_First(
		String userId, String ppPaymentStatus, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		List list = findByU_PPPS(userId, ppPaymentStatus, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder findByU_PPPS_Last(
		String userId, String ppPaymentStatus, OrderByComparator obc)
		throws NoSuchOrderException, SystemException {
		int count = countByU_PPPS(userId, ppPaymentStatus);
		List list = findByU_PPPS(userId, ppPaymentStatus, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchOrderException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingOrder)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingOrder[] findByU_PPPS_PrevAndNext(
		String orderId, String userId, String ppPaymentStatus,
		OrderByComparator obc) throws NoSuchOrderException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = findByPrimaryKey(orderId);
		int count = countByU_PPPS(userId, ppPaymentStatus);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, ppPaymentStatus);

			com.liferay.portlet.shopping.model.ShoppingOrder[] array = new com.liferay.portlet.shopping.model.ShoppingOrder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)sr.get(0);

					if (shoppingOrderHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingOrder curShoppingOrder =
						ShoppingOrderHBMUtil.model(shoppingOrderHBM);
					int value = obc.compare(shoppingOrder, curShoppingOrder);

					if (value == 0) {
						if (!shoppingOrder.equals(curShoppingOrder)) {
							break;
						}

						array[1] = curShoppingOrder;

						if (sr.previous()) {
							array[0] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingOrderHBMUtil.model((ShoppingOrderHBM)sr.get(
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
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				list.add(ShoppingOrderHBMUtil.model(shoppingOrderHBM));
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
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				ShoppingOrderPool.remove((String)shoppingOrderHBM.getPrimaryKey());
				session.delete(shoppingOrderHBM);
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

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				ShoppingOrderPool.remove((String)shoppingOrderHBM.getPrimaryKey());
				session.delete(shoppingOrderHBM);
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

	public void removeByC_PPPS(String companyId, String ppPaymentStatus)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, ppPaymentStatus);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				ShoppingOrderPool.remove((String)shoppingOrderHBM.getPrimaryKey());
				session.delete(shoppingOrderHBM);
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

	public void removeByU_PPPS(String userId, String ppPaymentStatus)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, ppPaymentStatus);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingOrderHBM shoppingOrderHBM = (ShoppingOrderHBM)itr.next();
				ShoppingOrderPool.remove((String)shoppingOrderHBM.getPrimaryKey());
				session.delete(shoppingOrderHBM);
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
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");

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

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ppPaymentStatus != 'LIFERAY_STATUS_LATEST' ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

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

	public int countByC_PPPS(String companyId, String ppPaymentStatus)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, ppPaymentStatus);

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

	public int countByU_PPPS(String userId, String ppPaymentStatus)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingOrder IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingOrderHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("ppPaymentStatus = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setString(queryPos++, ppPaymentStatus);

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

	private static final Log _log = LogFactory.getLog(ShoppingOrderPersistence.class);
}
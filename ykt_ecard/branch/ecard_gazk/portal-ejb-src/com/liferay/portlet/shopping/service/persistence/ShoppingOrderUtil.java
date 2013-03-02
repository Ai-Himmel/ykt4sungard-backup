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

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ShoppingOrderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.shopping.model.ShoppingOrder"),
			"com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingOrder"));

	public static com.liferay.portlet.shopping.model.ShoppingOrder create(
		java.lang.String orderId) {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(orderId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder remove(
		java.lang.String orderId)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(orderId));
		}

		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = persistence.remove(orderId);

		if (listener != null) {
			listener.onAfterRemove(shoppingOrder);
		}

		return shoppingOrder;
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder update(
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = shoppingOrder.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingOrder);
			}
			else {
				listener.onBeforeUpdate(shoppingOrder);
			}
		}

		shoppingOrder = persistence.update(shoppingOrder);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(shoppingOrder);
			}
			else {
				listener.onAfterUpdate(shoppingOrder);
			}
		}

		return shoppingOrder;
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByPrimaryKey(
		java.lang.String orderId)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(orderId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder[] findByCompanyId_PrevAndNext(
		java.lang.String orderId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(orderId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder[] findByUserId_PrevAndNext(
		java.lang.String orderId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(orderId, userId, obc);
	}

	public static java.util.List findByC_PPPS(java.lang.String companyId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_PPPS(companyId, ppPaymentStatus);
	}

	public static java.util.List findByC_PPPS(java.lang.String companyId,
		java.lang.String ppPaymentStatus, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_PPPS(companyId, ppPaymentStatus, begin, end);
	}

	public static java.util.List findByC_PPPS(java.lang.String companyId,
		java.lang.String ppPaymentStatus, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_PPPS(companyId, ppPaymentStatus, begin, end,
			obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByC_PPPS_First(
		java.lang.String companyId, java.lang.String ppPaymentStatus,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_PPPS_First(companyId, ppPaymentStatus, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByC_PPPS_Last(
		java.lang.String companyId, java.lang.String ppPaymentStatus,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_PPPS_Last(companyId, ppPaymentStatus, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder[] findByC_PPPS_PrevAndNext(
		java.lang.String orderId, java.lang.String companyId,
		java.lang.String ppPaymentStatus,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_PPPS_PrevAndNext(orderId, companyId,
			ppPaymentStatus, obc);
	}

	public static java.util.List findByU_PPPS(java.lang.String userId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_PPPS(userId, ppPaymentStatus);
	}

	public static java.util.List findByU_PPPS(java.lang.String userId,
		java.lang.String ppPaymentStatus, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_PPPS(userId, ppPaymentStatus, begin, end);
	}

	public static java.util.List findByU_PPPS(java.lang.String userId,
		java.lang.String ppPaymentStatus, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_PPPS(userId, ppPaymentStatus, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByU_PPPS_First(
		java.lang.String userId, java.lang.String ppPaymentStatus,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_PPPS_First(userId, ppPaymentStatus, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByU_PPPS_Last(
		java.lang.String userId, java.lang.String ppPaymentStatus,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_PPPS_Last(userId, ppPaymentStatus, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder[] findByU_PPPS_PrevAndNext(
		java.lang.String orderId, java.lang.String userId,
		java.lang.String ppPaymentStatus,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchOrderException, 
			com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_PPPS_PrevAndNext(orderId, userId,
			ppPaymentStatus, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByC_PPPS(java.lang.String companyId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_PPPS(companyId, ppPaymentStatus);
	}

	public static void removeByU_PPPS(java.lang.String userId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_PPPS(userId, ppPaymentStatus);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByC_PPPS(java.lang.String companyId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_PPPS(companyId, ppPaymentStatus);
	}

	public static int countByU_PPPS(java.lang.String userId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		ShoppingOrderPersistence persistence = (ShoppingOrderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_PPPS(userId, ppPaymentStatus);
	}

	private static final Log _log = LogFactory.getLog(ShoppingOrderUtil.class);
}
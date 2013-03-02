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
 * <a href="ShoppingItemUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.shopping.model.ShoppingItem"),
			"com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingItem"));

	public static com.liferay.portlet.shopping.model.ShoppingItem create(
		java.lang.String itemId) {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(itemId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem remove(
		java.lang.String itemId)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(itemId));
		}

		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem = persistence.remove(itemId);

		if (listener != null) {
			listener.onAfterRemove(shoppingItem);
		}

		return shoppingItem;
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem update(
		com.liferay.portlet.shopping.model.ShoppingItem shoppingItem)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = shoppingItem.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingItem);
			}
			else {
				listener.onBeforeUpdate(shoppingItem);
			}
		}

		shoppingItem = persistence.update(shoppingItem);

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

	public static com.liferay.portlet.shopping.model.ShoppingItem findByPrimaryKey(
		java.lang.String itemId)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(itemId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem[] findByCompanyId_PrevAndNext(
		java.lang.String itemId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(itemId, companyId, obc);
	}

	public static java.util.List findBySupplierUserId(
		java.lang.String supplierUserId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findBySupplierUserId(supplierUserId);
	}

	public static java.util.List findBySupplierUserId(
		java.lang.String supplierUserId, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findBySupplierUserId(supplierUserId, begin, end);
	}

	public static java.util.List findBySupplierUserId(
		java.lang.String supplierUserId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findBySupplierUserId(supplierUserId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findBySupplierUserId_First(
		java.lang.String supplierUserId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findBySupplierUserId_First(supplierUserId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findBySupplierUserId_Last(
		java.lang.String supplierUserId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findBySupplierUserId_Last(supplierUserId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem[] findBySupplierUserId_PrevAndNext(
		java.lang.String itemId, java.lang.String supplierUserId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findBySupplierUserId_PrevAndNext(itemId,
			supplierUserId, obc);
	}

	public static java.util.List findByC_C(java.lang.String companyId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, categoryId);
	}

	public static java.util.List findByC_C(java.lang.String companyId,
		java.lang.String categoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, categoryId, begin, end);
	}

	public static java.util.List findByC_C(java.lang.String companyId,
		java.lang.String categoryId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, categoryId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findByC_C_First(
		java.lang.String companyId, java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_First(companyId, categoryId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findByC_C_Last(
		java.lang.String companyId, java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_Last(companyId, categoryId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem[] findByC_C_PrevAndNext(
		java.lang.String itemId, java.lang.String companyId,
		java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_PrevAndNext(itemId, companyId, categoryId,
			obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem findByC_S(
		java.lang.String companyId, java.lang.String sku)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, sku);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeBySupplierUserId(java.lang.String supplierUserId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeBySupplierUserId(supplierUserId);
	}

	public static void removeByC_C(java.lang.String companyId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_C(companyId, categoryId);
	}

	public static void removeByC_S(java.lang.String companyId,
		java.lang.String sku)
		throws com.liferay.portlet.shopping.NoSuchItemException, 
			com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_S(companyId, sku);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countBySupplierUserId(java.lang.String supplierUserId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countBySupplierUserId(supplierUserId);
	}

	public static int countByC_C(java.lang.String companyId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_C(companyId, categoryId);
	}

	public static int countByC_S(java.lang.String companyId,
		java.lang.String sku) throws com.liferay.portal.SystemException {
		ShoppingItemPersistence persistence = (ShoppingItemPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_S(companyId, sku);
	}

	private static final Log _log = LogFactory.getLog(ShoppingItemUtil.class);
}
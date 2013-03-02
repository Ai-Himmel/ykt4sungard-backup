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
 * <a href="ShoppingItemPriceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemPriceUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.shopping.model.ShoppingItemPrice"),
			"com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.shopping.model.ShoppingItemPrice"));

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice create(
		java.lang.String itemPriceId) {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(itemPriceId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice remove(
		java.lang.String itemPriceId)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(itemPriceId));
		}

		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice = persistence.remove(itemPriceId);

		if (listener != null) {
			listener.onAfterRemove(shoppingItemPrice);
		}

		return shoppingItemPrice;
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice update(
		com.liferay.portlet.shopping.model.ShoppingItemPrice shoppingItemPrice)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = shoppingItemPrice.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(shoppingItemPrice);
			}
			else {
				listener.onBeforeUpdate(shoppingItemPrice);
			}
		}

		shoppingItemPrice = persistence.update(shoppingItemPrice);

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

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice findByPrimaryKey(
		java.lang.String itemPriceId)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(itemPriceId);
	}

	public static java.util.List findByItemId(java.lang.String itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId(itemId);
	}

	public static java.util.List findByItemId(java.lang.String itemId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId(itemId, begin, end);
	}

	public static java.util.List findByItemId(java.lang.String itemId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId(itemId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice findByItemId_First(
		java.lang.String itemId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId_First(itemId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice findByItemId_Last(
		java.lang.String itemId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId_Last(itemId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice[] findByItemId_PrevAndNext(
		java.lang.String itemPriceId, java.lang.String itemId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByItemId_PrevAndNext(itemPriceId, itemId, obc);
	}

	public static java.util.List findByI_S(java.lang.String itemId, int status)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByI_S(itemId, status);
	}

	public static java.util.List findByI_S(java.lang.String itemId, int status,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByI_S(itemId, status, begin, end);
	}

	public static java.util.List findByI_S(java.lang.String itemId, int status,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByI_S(itemId, status, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice findByI_S_First(
		java.lang.String itemId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByI_S_First(itemId, status, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice findByI_S_Last(
		java.lang.String itemId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByI_S_Last(itemId, status, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice[] findByI_S_PrevAndNext(
		java.lang.String itemPriceId, java.lang.String itemId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.shopping.NoSuchItemPriceException, 
			com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByI_S_PrevAndNext(itemPriceId, itemId, status,
			obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByItemId(java.lang.String itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByItemId(itemId);
	}

	public static void removeByI_S(java.lang.String itemId, int status)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByI_S(itemId, status);
	}

	public static int countByItemId(java.lang.String itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByItemId(itemId);
	}

	public static int countByI_S(java.lang.String itemId, int status)
		throws com.liferay.portal.SystemException {
		ShoppingItemPricePersistence persistence = (ShoppingItemPricePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByI_S(itemId, status);
	}

	private static final Log _log = LogFactory.getLog(ShoppingItemPriceUtil.class);
}
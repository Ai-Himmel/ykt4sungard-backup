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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.shopping.CartMinQuantityException;
import com.liferay.portlet.shopping.CouponActiveException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.NoSuchCartException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingCart;
import com.liferay.portlet.shopping.model.ShoppingCartItem;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.impl.ShoppingCartItemImpl;
import com.liferay.portlet.shopping.service.base.ShoppingCartLocalServiceBaseImpl;
import com.liferay.portlet.shopping.util.ShoppingUtil;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * <a href="ShoppingCartLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCartLocalServiceImpl
	extends ShoppingCartLocalServiceBaseImpl {

	public void deleteGroupCarts(long groupId) throws SystemException {
		shoppingCartPersistence.removeByGroupId(groupId);
	}

	public void deleteUserCarts(long userId) throws SystemException {
		shoppingCartPersistence.removeByUserId(userId);
	}

	public ShoppingCart getCart(long userId, long groupId)
		throws PortalException, SystemException {

		return shoppingCartPersistence.findByG_U(groupId, userId);
	}

	public Map getItems(long groupId, String itemIds)
		throws SystemException {

		Map items = new TreeMap();

		String[] itemIdsArray = StringUtil.split(itemIds);

		for (int i = 0; i < itemIdsArray.length; i++) {
			try {
				long itemId = ShoppingUtil.getItemId(itemIdsArray[i]);
				String fields = ShoppingUtil.getItemFields(itemIdsArray[i]);

				ShoppingItem item = shoppingItemPersistence.findByPrimaryKey(
					itemId);

				ShoppingCategory category = item.getCategory();

				if (category.getGroupId() == groupId) {
					ShoppingCartItem cartItem =
						new ShoppingCartItemImpl(item, fields);

					Integer count = (Integer)items.get(cartItem);

					if (count == null) {
						count = new Integer(1);
					}
					else {
						count = new Integer(count.intValue() + 1);
					}

					items.put(cartItem, count);
				}
			}
			catch (NoSuchItemException nsie) {
			}
		}

		return items;
	}

	public ShoppingCart updateCart(
			long userId, long groupId, String itemIds, String couponCodes,
			int altShipping, boolean insure)
		throws PortalException, SystemException {

		List badItemIds = new ArrayList();

		Map items = getItems(groupId, itemIds);

		boolean minQtyMultiple = GetterUtil.getBoolean(PropsUtil.get(
			PropsUtil.SHOPPING_CART_MIN_QTY_MULTIPLE));

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			int minQuantity = ShoppingUtil.getMinQuantity(item);

			if (minQuantity <= 0) {
				continue;
			}

			if (minQtyMultiple) {
				if ((count.intValue() % minQuantity) > 0) {
					badItemIds.add(new Long(item.getItemId()));
				}
			}
			else {
				if (count.intValue() < minQuantity) {
					badItemIds.add(new Long(item.getItemId()));
				}
			}
		}

		if (badItemIds.size() > 0) {
			throw new CartMinQuantityException(
				StringUtil.merge((Long[])badItemIds.toArray(new Long[0])));
		}

		String[] couponCodesArray = StringUtil.split(couponCodes);

		for (int i = 0; i < couponCodesArray.length; i++) {
			try {
				ShoppingCoupon coupon = shoppingCouponPersistence.findByCode(
					couponCodesArray[i]);

				if (coupon.getGroupId() != groupId) {
					throw new NoSuchCouponException(couponCodesArray[i]);
				}
				else if (!coupon.isActive()) {
					throw new CouponActiveException(couponCodesArray[i]);
				}
				else if (!coupon.hasValidStartDate()) {
					throw new CouponStartDateException(couponCodesArray[i]);
				}
				else if (!coupon.hasValidEndDate()) {
					throw new CouponEndDateException(couponCodesArray[i]);
				}
			}
			catch (NoSuchCouponException nsce) {
				throw new NoSuchCouponException(couponCodesArray[i]);
			}

			// Temporarily disable stacking of coupon codes

			break;
		}

		User user = userPersistence.findByPrimaryKey(userId);
		Date now = new Date();

		ShoppingCart cart = null;

		if (user.isDefaultUser()) {
			cart = shoppingCartPersistence.create(0);

			cart.setGroupId(groupId);
			cart.setCompanyId(user.getCompanyId());
			cart.setUserId(userId);
			cart.setUserName(user.getFullName());
			cart.setCreateDate(now);
		}
		else {
			try {
				cart = shoppingCartPersistence.findByG_U(groupId, userId);
			}
			catch (NoSuchCartException nsce) {
				long cartId = counterLocalService.increment();

				cart = shoppingCartPersistence.create(cartId);

				cart.setGroupId(groupId);
				cart.setCompanyId(user.getCompanyId());
				cart.setUserId(userId);
				cart.setUserName(user.getFullName());
				cart.setCreateDate(now);
			}
		}

		cart.setModifiedDate(now);
		cart.setItemIds(checkItemIds(groupId, itemIds));
		cart.setCouponCodes(couponCodes);
		cart.setAltShipping(altShipping);
		cart.setInsure(insure);

		if (!user.isDefaultUser()) {
			shoppingCartPersistence.update(cart);
		}

		return cart;
	}

	protected String checkItemIds(long groupId, String itemIds) {
		String[] itemIdsArray = StringUtil.split(itemIds);

		for (int i = 0; i < itemIdsArray.length; i++) {
			long itemId = ShoppingUtil.getItemId(itemIdsArray[i]);

			ShoppingItem item = null;

			try {
				item = shoppingItemPersistence.findByPrimaryKey(itemId);

				ShoppingCategory category = item.getCategory();

				if (category.getGroupId() != groupId) {
					item = null;
				}
			}
			catch (Exception e) {
			}

			if (item == null) {
				itemIds = StringUtil.remove(itemIds, itemIdsArray[i]);
			}
		}

		return itemIds;
	}

}
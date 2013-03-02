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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.shopping.CartMinQuantityException;
import com.liferay.portlet.shopping.CouponActiveException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.NoSuchCartException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingCart;
import com.liferay.portlet.shopping.model.ShoppingCartItem;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.persistence.ShoppingCartUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCartLocalServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCartService;
import com.liferay.portlet.shopping.util.ShoppingUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * <a href="ShoppingCartServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class ShoppingCartServiceImpl
	extends PrincipalBean implements ShoppingCartService {

	// Business methods

	public void deleteCart(String cartId)
		throws PortalException, SystemException {

		if (!hasAdmin(cartId)) {
			throw new PrincipalException();
		}

		ShoppingCartLocalServiceUtil.deleteCart(cartId);
	}

	public ShoppingCart emptyCart(String sessionId, String companyId)
		throws PortalException, SystemException {

		try {
			return _emptyUserCart(getUserId());
		}
		catch (PrincipalException pe) {
			return _emptySessionCart(sessionId, companyId);
		}
	}

	public ShoppingCart getCart(String sessionId, String companyId)
		throws PortalException, SystemException {

		try {
			return _getUserCart(sessionId, getUserId());
		}
		catch (PrincipalException pe) {
			return _getSessionCart(sessionId, companyId);
		}
	}

	public Map getItems(String companyId, String itemIds)
		throws SystemException {

		Map items = new TreeMap();

		String[] itemIdsArray = StringUtil.split(itemIds);

		for (int i = 0; i < itemIdsArray.length; i++) {
			try {
				String itemId = ShoppingUtil.getItemId(itemIdsArray[i]);
				String fields = ShoppingUtil.getItemFields(itemIdsArray[i]);

				ShoppingItem item =
					ShoppingItemUtil.findByPrimaryKey(itemId);

				if (item.getCompanyId().equals(companyId)) {
					ShoppingCartItem cartItem =
						new ShoppingCartItem(item, fields);

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
			String sessionId, String companyId, String itemIds,
			String couponIds, int altShipping, boolean insure)
		throws PortalException, SystemException {

		List badItemIds = new ArrayList();

		Map items = getItems(companyId, itemIds);

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			int minQuantity = ShoppingUtil.getMinQuantity(item);

			if (minQuantity > 0) {
				if (count.intValue() % minQuantity > 0) {
					badItemIds.add(item.getItemId());
				}
			}
		}

		if (badItemIds.size() > 0) {
			throw new CartMinQuantityException(
				StringUtil.merge((String[])badItemIds.toArray(new String[0])));
		}

		String[] couponIdsArray = StringUtil.split(couponIds);

		for (int i = 0; i < couponIdsArray.length; i++) {
			try {
				ShoppingCoupon coupon =
					ShoppingCouponUtil.findByPrimaryKey(couponIdsArray[i]);

				if (!coupon.getCompanyId().equals(companyId)) {
					throw new NoSuchCouponException(couponIdsArray[i]);
				}
				else if (!coupon.isActive()) {
					throw new CouponActiveException(couponIdsArray[i]);
				}
				else if (!coupon.hasValidStartDate()) {
					throw new CouponStartDateException(couponIdsArray[i]);
				}
				else if (!coupon.hasValidEndDate()) {
					throw new CouponEndDateException(couponIdsArray[i]);
				}
			}
			catch (NoSuchCouponException nsce) {
				throw new NoSuchCouponException(couponIdsArray[i]);
			}

			// Temporarily disable stacking of coupon codes

			break;
		}

		try {
			return _updateUserCart(
				getUserId(), itemIds, couponIds, altShipping, insure);
		}
		catch (PrincipalException pe) {
			return _updateSessionCart(
				sessionId, companyId, itemIds, couponIds, altShipping, insure);
		}
	}

	// Permission methods

	public boolean hasAdmin(String cartId)
		throws PortalException, SystemException {

		ShoppingCart cart = ShoppingCartUtil.findByPrimaryKey(cartId);

		if ((cart.getUserId().equals(getUserId())) ||
			(getUser().getCompanyId().equals(cart.getCompanyId()) &&
			 RoleServiceUtil.hasRole(getUserId(), Role.SHOPPING_ADMIN))) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private String _checkItemIds(String companyId, String itemIds) {
		String[] itemIdsArray = StringUtil.split(itemIds);

		for (int i = 0; i < itemIdsArray.length; i++) {
			String itemId = ShoppingUtil.getItemId(itemIdsArray[i]);

			ShoppingItem item = null;

			try {
				item = ShoppingItemUtil.findByPrimaryKey(itemId);

				if (!item.getCompanyId().equals(companyId)) {
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

	private Map _getCartsPool() {
		String scpId = ShoppingCartServiceImpl.class.getName();

		Map cartsPool = (Map)SimpleCachePool.get(scpId);

		if (cartsPool == null) {
			cartsPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, cartsPool);
		}

		return cartsPool;
	}

	private ShoppingCart _getSessionCart(String sessionId, String companyId) {
		Map cartsPool = _getCartsPool();

		ShoppingCart cart = (ShoppingCart)cartsPool.get(sessionId);

		if (cart == null) {
			cart = _emptySessionCart(sessionId, companyId);
		}

		return cart;
	}

	private ShoppingCart _getUserCart(String sessionId, String userId)
		throws PortalException, SystemException {

		Map cartsPool = _getCartsPool();

		ShoppingCart cart = (ShoppingCart)cartsPool.remove(sessionId);

		if (cart != null && cart.getItemsSize() > 0) {
			cart = _updateUserCart(
				userId, cart.getItemIds(), cart.getCouponIds(),
				cart.getAltShipping(), cart.isInsure());
		}
		else {
			try {
				cart = ShoppingCartUtil.findByPrimaryKey(userId);
			}
			catch (NoSuchCartException nsce) {
				cart = _emptyUserCart(userId);
			}
		}

		return cart;
	}

	private ShoppingCart _emptySessionCart(String sessionId, String companyId) {
		Map cartsPool = _getCartsPool();

		cartsPool.remove(sessionId);

		return _updateSessionCart(
			sessionId, companyId, StringPool.BLANK, StringPool.BLANK, 0, false);
	}

	private ShoppingCart _emptyUserCart(String userId)
		throws PortalException, SystemException {

		return _updateUserCart(
			userId, StringPool.BLANK, StringPool.BLANK, 0, false);
	}

	private ShoppingCart _updateSessionCart(
		String sessionId, String companyId, String itemIds, String couponIds,
		int altShipping, boolean insure) {

		Map cartsPool = _getCartsPool();

		ShoppingCart cart = (ShoppingCart)cartsPool.get(sessionId);

		Date now = new Date();

		if (cart == null) {
			cart = ShoppingCartUtil.create(sessionId);

			cart.setCompanyId(companyId);
			cart.setCreateDate(now);
			cart.setModifiedDate(now);

			cartsPool.put(sessionId, cart);
		}

		cart.setModifiedDate(now);
		cart.setItemIds(_checkItemIds(companyId, itemIds));
		cart.setCouponIds(couponIds);
		cart.setAltShipping(altShipping);
		cart.setInsure(insure);

		return cart;
	}

	private ShoppingCart _updateUserCart(
			String userId, String itemIds, String couponIds, int altShipping,
			boolean insure)
		throws PortalException, SystemException {

		User user = getUser();

		String cartId = user.getUserId();

		ShoppingCart cart = null;

		Date now = new Date();

		try {
			cart = ShoppingCartUtil.findByPrimaryKey(cartId);
		}
		catch (NoSuchCartException nsce) {
			cart = ShoppingCartUtil.create(cartId);

			cart.setCompanyId(user.getCompanyId());
			cart.setUserId(user.getUserId());
			cart.setCreateDate(now);
		}

		cart.setModifiedDate(now);
		cart.setItemIds(_checkItemIds(user.getCompanyId(), itemIds));
		cart.setCouponIds(couponIds);
		cart.setAltShipping(altShipping);
		cart.setInsure(insure);

		ShoppingCartUtil.update(cart);

		return cart;
	}

}
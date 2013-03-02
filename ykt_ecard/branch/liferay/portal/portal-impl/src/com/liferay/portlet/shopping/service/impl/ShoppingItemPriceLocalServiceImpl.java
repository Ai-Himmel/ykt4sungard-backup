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
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.model.impl.ShoppingItemPriceImpl;
import com.liferay.portlet.shopping.service.base.ShoppingItemPriceLocalServiceBaseImpl;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="ShoppingItemPriceLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemPriceLocalServiceImpl
	extends ShoppingItemPriceLocalServiceBaseImpl {

	public List getItemPrices(long itemId)
		throws PortalException, SystemException {

		ShoppingItem item = shoppingItemPersistence.findByPrimaryKey(itemId);

		List itemPrices = shoppingItemPricePersistence.findByItemId(itemId);

		if (itemPrices.size() == 0) {
			itemPrices = new ArrayList();

			ShoppingItemPrice itemPrice = shoppingItemPricePersistence.create(
				0);

			itemPrice.setItemId(itemId);
			itemPrice.setMinQuantity(item.getMinQuantity());
			itemPrice.setMaxQuantity(item.getMaxQuantity());
			itemPrice.setPrice(item.getPrice());
			itemPrice.setDiscount(item.getDiscount());
			itemPrice.setTaxable(item.isTaxable());
			itemPrice.setShipping(item.getShipping());
			itemPrice.setUseShippingFormula(item.isUseShippingFormula());
			itemPrice.setStatus(ShoppingItemPriceImpl.STATUS_ACTIVE_DEFAULT);

			itemPrices.add(itemPrice);
		}

		return itemPrices;
	}

}
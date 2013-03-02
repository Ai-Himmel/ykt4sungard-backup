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
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemPriceService;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="ShoppingItemPriceServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class ShoppingItemPriceServiceImpl
	extends PrincipalBean implements ShoppingItemPriceService {

	// Business methods

	public List getItemPrices(String itemId)
		throws PortalException, SystemException {

		ShoppingItem item = ShoppingItemUtil.findByPrimaryKey(itemId);

		List itemPrices = ShoppingItemPriceUtil.findByItemId(itemId);

		if (itemPrices.size() == 0) {
			itemPrices = new ArrayList();

			itemPrices.add(new ShoppingItemPrice(
				null, itemId, item.getMinQuantity(), item.getMaxQuantity(),
				item.getPrice(), item.getDiscount(), item.getTaxable(),
				item.getShipping(), item.isUseShippingFormula(),
				ShoppingItemPrice.STATUS_ACTIVE_DEFAULT));
		}

		return itemPrices;
	}

}
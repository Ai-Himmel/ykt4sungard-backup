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

package com.liferay.portlet.shopping.model.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingItemPriceLocalServiceUtil;
import com.liferay.portlet.shopping.util.comparator.ItemNameComparator;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ShoppingItemImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemImpl
	extends ShoppingItemModelImpl implements ShoppingItem {

	public ShoppingItemImpl() {
	}

	public ShoppingCategory getCategory() {
		ShoppingCategory category = null;

		try {
			category = ShoppingCategoryLocalServiceUtil.getCategory(
				getCategoryId());
		}
		catch (Exception e) {
			category = new ShoppingCategoryImpl();

			_log.error(e);
		}

		return category;
	}

	public void setFieldsQuantities(String fieldsQuantities) {
		_fieldsQuantitiesArray = StringUtil.split(fieldsQuantities);

		super.setFieldsQuantities(fieldsQuantities);
	}

	public String[] getFieldsQuantitiesArray() {
		return _fieldsQuantitiesArray;
	}

	public void setFieldsQuantitiesArray(String[] fieldsQuantitiesArray) {
		_fieldsQuantitiesArray = fieldsQuantitiesArray;

		super.setFieldsQuantities(StringUtil.merge(fieldsQuantitiesArray));
	}

	public int compareTo(Object obj) {
		return new ItemNameComparator(true).compare(this, obj);
	}

	public List getItemPrices()
		throws PortalException, SystemException {

		return ShoppingItemPriceLocalServiceUtil.getItemPrices(getItemId());
	}

	private static Log _log = LogFactory.getLog(ShoppingItemImpl.class);

	private String[] _fieldsQuantitiesArray;

}
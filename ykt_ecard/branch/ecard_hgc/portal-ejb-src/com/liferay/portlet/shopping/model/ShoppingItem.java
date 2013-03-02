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

package com.liferay.portlet.shopping.model;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.shopping.service.spring.ShoppingItemPriceServiceUtil;
import com.liferay.portlet.shopping.util.ItemNameComparator;
import com.liferay.util.StringUtil;

import java.util.Date;
import java.util.List;

/**
 * <a href="ShoppingItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.21 $
 *
 */
public class ShoppingItem extends ShoppingItemModel {

	public ShoppingItem() {
		super();
	}

	public ShoppingItem(String itemId) {
		super(itemId);
	}

	public ShoppingItem(String itemId, String companyId, Date createDate,
						Date modifiedDate, String categoryId, String sku,
						String name, String description, String properties,
						String supplierUserId, boolean fields,
						String fieldsQuantities, int minQuantity,
						int maxQuantity, double price, double discount,
						boolean taxable, double shipping,
						boolean useShippingFormula, boolean requiresShipping,
						int stockQuantity, boolean featured, boolean sale,
						boolean smallImage, String smallImageURL,
						boolean mediumImage, String mediumImageURL,
						boolean largeImage, String largeImageURL) {

		super(itemId, companyId, createDate, modifiedDate, categoryId, sku,
			  name, description, properties, supplierUserId, fields,
			  fieldsQuantities, minQuantity, maxQuantity, price, discount,
			  taxable, shipping, useShippingFormula, requiresShipping,
			  stockQuantity, featured, sale, smallImage, smallImageURL,
			  mediumImage, mediumImageURL, largeImage, largeImageURL);

		setFieldsQuantities(fieldsQuantities);
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

	public String getSmallImageId() {
		return getCompanyId() + ".shopping.item." + getItemId() + ".small";
	}

	public String getMediumImageId() {
		return getCompanyId() + ".shopping.item." + getItemId() + ".medium";
	}

	public String getLargeImageId() {
		return getCompanyId() + ".shopping.item." + getItemId() + ".large";
	}

	public int compareTo(Object obj) {
		return new ItemNameComparator(true).compare(this, obj);
	}

	public List getItemPrices()
		throws PortalException, SystemException {

		return ShoppingItemPriceServiceUtil.getItemPrices(getItemId());
	}

	private String[] _fieldsQuantitiesArray;

}
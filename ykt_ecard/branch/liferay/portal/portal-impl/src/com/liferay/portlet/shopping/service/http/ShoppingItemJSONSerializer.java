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

package com.liferay.portlet.shopping.service.http;

import com.liferay.portlet.shopping.model.ShoppingItem;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="ShoppingItemJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.shopping.service.http.ShoppingItemServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.http.ShoppingItemServiceJSON
 *
 */
public class ShoppingItemJSONSerializer {
	public static JSONObject toJSONObject(ShoppingItem model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "itemId", model.getItemId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "userId", model.getUserId());
		JSONUtil.put(jsonObj, "userName", model.getUserName());
		JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
		JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
		JSONUtil.put(jsonObj, "categoryId", model.getCategoryId());
		JSONUtil.put(jsonObj, "sku", model.getSku());
		JSONUtil.put(jsonObj, "name", model.getName());
		JSONUtil.put(jsonObj, "description", model.getDescription());
		JSONUtil.put(jsonObj, "properties", model.getProperties());
		JSONUtil.put(jsonObj, "fields", model.getFields());
		JSONUtil.put(jsonObj, "fieldsQuantities", model.getFieldsQuantities());
		JSONUtil.put(jsonObj, "minQuantity", model.getMinQuantity());
		JSONUtil.put(jsonObj, "maxQuantity", model.getMaxQuantity());
		JSONUtil.put(jsonObj, "price", model.getPrice());
		JSONUtil.put(jsonObj, "discount", model.getDiscount());
		JSONUtil.put(jsonObj, "taxable", model.getTaxable());
		JSONUtil.put(jsonObj, "shipping", model.getShipping());
		JSONUtil.put(jsonObj, "useShippingFormula",
			model.getUseShippingFormula());
		JSONUtil.put(jsonObj, "requiresShipping", model.getRequiresShipping());
		JSONUtil.put(jsonObj, "stockQuantity", model.getStockQuantity());
		JSONUtil.put(jsonObj, "featured", model.getFeatured());
		JSONUtil.put(jsonObj, "sale", model.getSale());
		JSONUtil.put(jsonObj, "smallImage", model.getSmallImage());
		JSONUtil.put(jsonObj, "smallImageId", model.getSmallImageId());
		JSONUtil.put(jsonObj, "smallImageURL", model.getSmallImageURL());
		JSONUtil.put(jsonObj, "mediumImage", model.getMediumImage());
		JSONUtil.put(jsonObj, "mediumImageId", model.getMediumImageId());
		JSONUtil.put(jsonObj, "mediumImageURL", model.getMediumImageURL());
		JSONUtil.put(jsonObj, "largeImage", model.getLargeImage());
		JSONUtil.put(jsonObj, "largeImageId", model.getLargeImageId());
		JSONUtil.put(jsonObj, "largeImageURL", model.getLargeImageURL());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			ShoppingItem model = (ShoppingItem)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}
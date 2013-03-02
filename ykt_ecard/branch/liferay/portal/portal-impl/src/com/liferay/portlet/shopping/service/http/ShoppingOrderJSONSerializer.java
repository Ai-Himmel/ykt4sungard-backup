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

import com.liferay.portlet.shopping.model.ShoppingOrder;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="ShoppingOrderJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.shopping.service.http.ShoppingOrderServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.http.ShoppingOrderServiceJSON
 *
 */
public class ShoppingOrderJSONSerializer {
	public static JSONObject toJSONObject(ShoppingOrder model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "orderId", model.getOrderId());
		JSONUtil.put(jsonObj, "groupId", model.getGroupId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "userId", model.getUserId());
		JSONUtil.put(jsonObj, "userName", model.getUserName());
		JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
		JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
		JSONUtil.put(jsonObj, "number", model.getNumber());
		JSONUtil.put(jsonObj, "tax", model.getTax());
		JSONUtil.put(jsonObj, "shipping", model.getShipping());
		JSONUtil.put(jsonObj, "altShipping", model.getAltShipping());
		JSONUtil.put(jsonObj, "requiresShipping", model.getRequiresShipping());
		JSONUtil.put(jsonObj, "insure", model.getInsure());
		JSONUtil.put(jsonObj, "insurance", model.getInsurance());
		JSONUtil.put(jsonObj, "couponCodes", model.getCouponCodes());
		JSONUtil.put(jsonObj, "couponDiscount", model.getCouponDiscount());
		JSONUtil.put(jsonObj, "billingFirstName", model.getBillingFirstName());
		JSONUtil.put(jsonObj, "billingLastName", model.getBillingLastName());
		JSONUtil.put(jsonObj, "billingEmailAddress",
			model.getBillingEmailAddress());
		JSONUtil.put(jsonObj, "billingCompany", model.getBillingCompany());
		JSONUtil.put(jsonObj, "billingStreet", model.getBillingStreet());
		JSONUtil.put(jsonObj, "billingCity", model.getBillingCity());
		JSONUtil.put(jsonObj, "billingState", model.getBillingState());
		JSONUtil.put(jsonObj, "billingZip", model.getBillingZip());
		JSONUtil.put(jsonObj, "billingCountry", model.getBillingCountry());
		JSONUtil.put(jsonObj, "billingPhone", model.getBillingPhone());
		JSONUtil.put(jsonObj, "shipToBilling", model.getShipToBilling());
		JSONUtil.put(jsonObj, "shippingFirstName", model.getShippingFirstName());
		JSONUtil.put(jsonObj, "shippingLastName", model.getShippingLastName());
		JSONUtil.put(jsonObj, "shippingEmailAddress",
			model.getShippingEmailAddress());
		JSONUtil.put(jsonObj, "shippingCompany", model.getShippingCompany());
		JSONUtil.put(jsonObj, "shippingStreet", model.getShippingStreet());
		JSONUtil.put(jsonObj, "shippingCity", model.getShippingCity());
		JSONUtil.put(jsonObj, "shippingState", model.getShippingState());
		JSONUtil.put(jsonObj, "shippingZip", model.getShippingZip());
		JSONUtil.put(jsonObj, "shippingCountry", model.getShippingCountry());
		JSONUtil.put(jsonObj, "shippingPhone", model.getShippingPhone());
		JSONUtil.put(jsonObj, "ccName", model.getCcName());
		JSONUtil.put(jsonObj, "ccType", model.getCcType());
		JSONUtil.put(jsonObj, "ccNumber", model.getCcNumber());
		JSONUtil.put(jsonObj, "ccExpMonth", model.getCcExpMonth());
		JSONUtil.put(jsonObj, "ccExpYear", model.getCcExpYear());
		JSONUtil.put(jsonObj, "ccVerNumber", model.getCcVerNumber());
		JSONUtil.put(jsonObj, "comments", model.getComments());
		JSONUtil.put(jsonObj, "ppTxnId", model.getPpTxnId());
		JSONUtil.put(jsonObj, "ppPaymentStatus", model.getPpPaymentStatus());
		JSONUtil.put(jsonObj, "ppPaymentGross", model.getPpPaymentGross());
		JSONUtil.put(jsonObj, "ppReceiverEmail", model.getPpReceiverEmail());
		JSONUtil.put(jsonObj, "ppPayerEmail", model.getPpPayerEmail());
		JSONUtil.put(jsonObj, "sendOrderEmail", model.getSendOrderEmail());
		JSONUtil.put(jsonObj, "sendShippingEmail", model.getSendShippingEmail());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			ShoppingOrder model = (ShoppingOrder)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}
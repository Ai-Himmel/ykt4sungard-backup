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

/**
 * <a href="ShoppingOrderHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderHBMUtil {
	public static com.liferay.portlet.shopping.model.ShoppingOrder model(
		ShoppingOrderHBM shoppingOrderHBM) {
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder = ShoppingOrderPool.get(shoppingOrderHBM.getPrimaryKey());

		if (shoppingOrder == null) {
			shoppingOrder = new com.liferay.portlet.shopping.model.ShoppingOrder(shoppingOrderHBM.getOrderId(),
					shoppingOrderHBM.getCompanyId(),
					shoppingOrderHBM.getUserId(),
					shoppingOrderHBM.getCreateDate(),
					shoppingOrderHBM.getModifiedDate(),
					shoppingOrderHBM.getTax(), shoppingOrderHBM.getShipping(),
					shoppingOrderHBM.getAltShipping(),
					shoppingOrderHBM.getRequiresShipping(),
					shoppingOrderHBM.getInsure(),
					shoppingOrderHBM.getInsurance(),
					shoppingOrderHBM.getCouponIds(),
					shoppingOrderHBM.getCouponDiscount(),
					shoppingOrderHBM.getBillingFirstName(),
					shoppingOrderHBM.getBillingLastName(),
					shoppingOrderHBM.getBillingEmailAddress(),
					shoppingOrderHBM.getBillingCompany(),
					shoppingOrderHBM.getBillingStreet(),
					shoppingOrderHBM.getBillingCity(),
					shoppingOrderHBM.getBillingState(),
					shoppingOrderHBM.getBillingZip(),
					shoppingOrderHBM.getBillingCountry(),
					shoppingOrderHBM.getBillingPhone(),
					shoppingOrderHBM.getShipToBilling(),
					shoppingOrderHBM.getShippingFirstName(),
					shoppingOrderHBM.getShippingLastName(),
					shoppingOrderHBM.getShippingEmailAddress(),
					shoppingOrderHBM.getShippingCompany(),
					shoppingOrderHBM.getShippingStreet(),
					shoppingOrderHBM.getShippingCity(),
					shoppingOrderHBM.getShippingState(),
					shoppingOrderHBM.getShippingZip(),
					shoppingOrderHBM.getShippingCountry(),
					shoppingOrderHBM.getShippingPhone(),
					shoppingOrderHBM.getCcName(), shoppingOrderHBM.getCcType(),
					shoppingOrderHBM.getCcNumber(),
					shoppingOrderHBM.getCcExpMonth(),
					shoppingOrderHBM.getCcExpYear(),
					shoppingOrderHBM.getCcVerNumber(),
					shoppingOrderHBM.getComments(),
					shoppingOrderHBM.getPpTxnId(),
					shoppingOrderHBM.getPpPaymentStatus(),
					shoppingOrderHBM.getPpPaymentGross(),
					shoppingOrderHBM.getPpReceiverEmail(),
					shoppingOrderHBM.getPpPayerEmail(),
					shoppingOrderHBM.getSendOrderEmail(),
					shoppingOrderHBM.getSendShippingEmail());
			ShoppingOrderPool.put(shoppingOrder.getPrimaryKey(), shoppingOrder);
		}

		return shoppingOrder;
	}
}
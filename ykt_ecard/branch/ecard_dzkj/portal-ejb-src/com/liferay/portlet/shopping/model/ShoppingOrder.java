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

import java.util.Date;

/**
 * <a href="ShoppingOrder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.19 $
 *
 */
public class ShoppingOrder extends ShoppingOrderModel {

	public static final String[] STATUSES = {
		"checkout", "completed", "denied", "pending", "refunded"
	};

	public static final String STATUS_LATEST = "LIFERAY_STATUS_LATEST";

	public static final String STATUS_CHECKOUT = "LIFERAY_STATUS_CHECKOUT";

	public static final String STATUS_COMPLETED = "Completed";

	public static final String STATUS_DENIED = "Denied";

	public static final String STATUS_PENDING = "Pending";

	public static final String STATUS_REFUNDED = "Refunded";

	public ShoppingOrder() {
		super();
	}

	public ShoppingOrder(String orderId) {
		super(orderId);
	}

	public ShoppingOrder(String orderId, String companyId, String userId,
						 Date createDate, Date modifiedDate, double tax,
						 double shipping, String altShipping,
						 boolean requiresShipping, boolean insure,
						 double insurance, String couponIds,
						 double couponDiscount, String billingFirstName,
						 String billingLastName, String billingEmailAddress,
						 String billingCompany, String billingStreet,
						 String billingCity, String billingState,
						 String billingZip, String billingCountry,
						 String billingPhone, boolean shipToBilling,
						 String shippingFirstName, String shippingLastName,
						 String shippingEmailAddress, String shippingCompany,
						 String shippingStreet, String shippingCity,
						 String shippingState, String shippingZip,
						 String shippingCountry, String shippingPhone,
						 String ccName, String ccType, String ccNumber,
						 int ccExpMonth, int ccExpYear, String ccVerNumber,
						 String comments, String ppTxnId,
						 String ppPaymentStatus, double ppPaymentGross,
						 String ppReceiverEmail, String ppPayerEmail,
						 boolean sendOrderEmail, boolean sendShippingEmail) {

		super(orderId, companyId, userId, createDate, modifiedDate, tax,
			  shipping, altShipping, requiresShipping, insure, insurance,
			  couponIds, couponDiscount, billingFirstName, billingLastName,
			  billingEmailAddress, billingCompany, billingStreet, billingCity,
			  billingState, billingZip, billingCountry, billingPhone,
			  shipToBilling, shippingFirstName, shippingLastName,
			  shippingEmailAddress, shippingCompany, shippingStreet,
			  shippingCity, shippingState, shippingZip, shippingCountry,
			  shippingPhone, ccName, ccType, ccNumber, ccExpMonth, ccExpYear,
			  ccVerNumber, comments, ppTxnId, ppPaymentStatus, ppPaymentGross,
			  ppReceiverEmail, ppPayerEmail, sendOrderEmail, sendShippingEmail);
	}

}
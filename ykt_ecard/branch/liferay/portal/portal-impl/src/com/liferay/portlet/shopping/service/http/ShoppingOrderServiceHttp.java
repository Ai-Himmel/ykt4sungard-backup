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

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.DoubleWrapper;
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.http.TunnelUtil;

import com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil;

/**
 * <a href="ShoppingOrderServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it requires an
 * additional <code>com.liferay.portal.security.auth.HttpPrincipal</code>
 * parameter.
 * </p>
 *
 * <p>
 * The benefits of using the HTTP utility is that it is fast and allows for
 * tunneling without the cost of serializing to text. The drawback is that it
 * only works with Java.
 * </p>
 *
 * <p>
 * Set the property <code>tunnel.servlet.hosts.allowed</code> in
 * portal.properties to configure security.
 * </p>
 *
 * <p>
 * The HTTP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.security.auth.HttpPrincipal
 * @see com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil
 * @see com.liferay.portlet.shopping.service.http.ShoppingOrderServiceSoap
 *
 */
public class ShoppingOrderServiceHttp {
	public static void completeOrder(HttpPrincipal httpPrincipal, long plid,
		java.lang.String number, java.lang.String ppTxnId,
		java.lang.String ppPaymentStatus, double ppPaymentGross,
		java.lang.String ppReceiverEmail, java.lang.String ppPayerEmail)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = number;

			if (number == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = ppTxnId;

			if (ppTxnId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new DoubleWrapper(ppPaymentGross);

			Object paramObj5 = ppReceiverEmail;

			if (ppReceiverEmail == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = ppPayerEmail;

			if (ppPayerEmail == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"completeOrder",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6
					});

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deleteOrder(HttpPrincipal httpPrincipal, long plid,
		long orderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new LongWrapper(orderId);

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"deleteOrder", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder getOrder(
		HttpPrincipal httpPrincipal, long plid, long orderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new LongWrapper(orderId);

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrder", new Object[] { paramObj0, paramObj1 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void sendEmail(HttpPrincipal httpPrincipal, long plid,
		long orderId, java.lang.String emailType)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new LongWrapper(orderId);

			Object paramObj2 = emailType;

			if (emailType == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"sendEmail",
					new Object[] { paramObj0, paramObj1, paramObj2 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateOrder(
		HttpPrincipal httpPrincipal, long plid, long orderId,
		java.lang.String billingFirstName, java.lang.String billingLastName,
		java.lang.String billingEmailAddress, java.lang.String billingCompany,
		java.lang.String billingStreet, java.lang.String billingCity,
		java.lang.String billingState, java.lang.String billingZip,
		java.lang.String billingCountry, java.lang.String billingPhone,
		boolean shipToBilling, java.lang.String shippingFirstName,
		java.lang.String shippingLastName,
		java.lang.String shippingEmailAddress,
		java.lang.String shippingCompany, java.lang.String shippingStreet,
		java.lang.String shippingCity, java.lang.String shippingState,
		java.lang.String shippingZip, java.lang.String shippingCountry,
		java.lang.String shippingPhone, java.lang.String ccName,
		java.lang.String ccType, java.lang.String ccNumber, int ccExpMonth,
		int ccExpYear, java.lang.String ccVerNumber, java.lang.String comments)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new LongWrapper(orderId);

			Object paramObj2 = billingFirstName;

			if (billingFirstName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = billingLastName;

			if (billingLastName == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = billingEmailAddress;

			if (billingEmailAddress == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = billingCompany;

			if (billingCompany == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = billingStreet;

			if (billingStreet == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = billingCity;

			if (billingCity == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = billingState;

			if (billingState == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = billingZip;

			if (billingZip == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = billingCountry;

			if (billingCountry == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = billingPhone;

			if (billingPhone == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = new BooleanWrapper(shipToBilling);

			Object paramObj13 = shippingFirstName;

			if (shippingFirstName == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = shippingLastName;

			if (shippingLastName == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = shippingEmailAddress;

			if (shippingEmailAddress == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = shippingCompany;

			if (shippingCompany == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = shippingStreet;

			if (shippingStreet == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = shippingCity;

			if (shippingCity == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = shippingState;

			if (shippingState == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = shippingZip;

			if (shippingZip == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = shippingCountry;

			if (shippingCountry == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = shippingPhone;

			if (shippingPhone == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = ccName;

			if (ccName == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = ccType;

			if (ccType == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = ccNumber;

			if (ccNumber == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			Object paramObj26 = new IntegerWrapper(ccExpMonth);

			Object paramObj27 = new IntegerWrapper(ccExpYear);

			Object paramObj28 = ccVerNumber;

			if (ccVerNumber == null) {
				paramObj28 = new NullWrapper("java.lang.String");
			}

			Object paramObj29 = comments;

			if (comments == null) {
				paramObj29 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"updateOrder",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26, paramObj27, paramObj28, paramObj29
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateOrder(
		HttpPrincipal httpPrincipal, long plid, long orderId,
		java.lang.String ppTxnId, java.lang.String ppPaymentStatus,
		double ppPaymentGross, java.lang.String ppReceiverEmail,
		java.lang.String ppPayerEmail)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(plid);

			Object paramObj1 = new LongWrapper(orderId);

			Object paramObj2 = ppTxnId;

			if (ppTxnId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new DoubleWrapper(ppPaymentGross);

			Object paramObj5 = ppReceiverEmail;

			if (ppReceiverEmail == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = ppPayerEmail;

			if (ppPayerEmail == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"updateOrder",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(ShoppingOrderServiceHttp.class);
}
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

package com.liferay.portlet.shopping.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.shopping.service.spring.ShoppingOrderServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.DoubleWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ShoppingOrderServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderServiceHttp {
	public static void addNote(HttpPrincipal httpPrincipal,
		java.lang.String orderId, java.lang.String noteContent)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = noteContent;

			if (noteContent == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"addNote", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void completeOrder(HttpPrincipal httpPrincipal,
		java.lang.String orderId, java.lang.String ppTxnId,
		java.lang.String ppPaymentStatus, double ppPaymentGross,
		java.lang.String ppReceiverEmail, java.lang.String ppPayerEmail)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = ppTxnId;

			if (ppTxnId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new DoubleWrapper(ppPaymentGross);
			Object paramObj4 = ppReceiverEmail;

			if (ppReceiverEmail == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = ppPayerEmail;

			if (ppPayerEmail == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"completeOrder",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void deleteNote(HttpPrincipal httpPrincipal,
		java.lang.String orderId, java.lang.String noteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = noteId;

			if (noteId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"deleteNote", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void deleteOrder(HttpPrincipal httpPrincipal,
		java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"deleteOrder", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void deleteOrder(HttpPrincipal httpPrincipal,
		com.liferay.portlet.shopping.model.ShoppingOrder order)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = order;

			if (order == null) {
				paramObj0 = new NullWrapper(
						"com.liferay.portlet.shopping.model.ShoppingOrder");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"deleteOrder", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder getLatestOrder(
		HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getLatestOrder", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getNotes(HttpPrincipal httpPrincipal,
		java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getNotes", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder getOrder(
		HttpPrincipal httpPrincipal, java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrder", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getOrders(HttpPrincipal httpPrincipal,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrders", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getOrders(HttpPrincipal httpPrincipal,
		java.lang.String ppPaymentStatus, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = new IntegerWrapper(begin);
			Object paramObj2 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrders",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getOrders(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String ppPaymentStatus)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrders", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getOrders(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String ppPaymentStatus,
		int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = new IntegerWrapper(begin);
			Object paramObj3 = new IntegerWrapper(end);
			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrders",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static int getOrdersSize(HttpPrincipal httpPrincipal,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrdersSize", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static int getOrdersSize(HttpPrincipal httpPrincipal,
		java.lang.String companyId, java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = companyId;

			if (companyId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"getOrdersSize", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder saveLatestOrder(
		HttpPrincipal httpPrincipal,
		com.liferay.portlet.shopping.model.ShoppingCart cart)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = cart;

			if (cart == null) {
				paramObj0 = new NullWrapper(
						"com.liferay.portlet.shopping.model.ShoppingCart");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"saveLatestOrder", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void sendOrderEmail(HttpPrincipal httpPrincipal,
		java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"sendOrderEmail", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void sendShippingEmail(HttpPrincipal httpPrincipal,
		java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"sendShippingEmail", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateLatestOrder(
		HttpPrincipal httpPrincipal, java.lang.String billingFirstName,
		java.lang.String billingLastName, java.lang.String billingEmailAddress,
		java.lang.String billingCompany, java.lang.String billingStreet,
		java.lang.String billingCity, java.lang.String billingState,
		java.lang.String billingZip, java.lang.String billingCountry,
		java.lang.String billingPhone, boolean shipToBilling,
		java.lang.String shippingFirstName, java.lang.String shippingLastName,
		java.lang.String shippingEmailAddress,
		java.lang.String shippingCompany, java.lang.String shippingStreet,
		java.lang.String shippingCity, java.lang.String shippingState,
		java.lang.String shippingZip, java.lang.String shippingCountry,
		java.lang.String shippingPhone, java.lang.String ccName,
		java.lang.String ccType, java.lang.String ccNumber, int ccExpMonth,
		int ccExpYear, java.lang.String ccVerNumber, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = billingFirstName;

			if (billingFirstName == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = billingLastName;

			if (billingLastName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = billingEmailAddress;

			if (billingEmailAddress == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = billingCompany;

			if (billingCompany == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = billingStreet;

			if (billingStreet == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = billingCity;

			if (billingCity == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = billingState;

			if (billingState == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = billingZip;

			if (billingZip == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = billingCountry;

			if (billingCountry == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = billingPhone;

			if (billingPhone == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = new BooleanWrapper(shipToBilling);
			Object paramObj11 = shippingFirstName;

			if (shippingFirstName == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = shippingLastName;

			if (shippingLastName == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = shippingEmailAddress;

			if (shippingEmailAddress == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = shippingCompany;

			if (shippingCompany == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = shippingStreet;

			if (shippingStreet == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = shippingCity;

			if (shippingCity == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = shippingState;

			if (shippingState == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = shippingZip;

			if (shippingZip == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = shippingCountry;

			if (shippingCountry == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = shippingPhone;

			if (shippingPhone == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = ccName;

			if (ccName == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = ccType;

			if (ccType == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = ccNumber;

			if (ccNumber == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = new IntegerWrapper(ccExpMonth);
			Object paramObj25 = new IntegerWrapper(ccExpYear);
			Object paramObj26 = ccVerNumber;

			if (ccVerNumber == null) {
				paramObj26 = new NullWrapper("java.lang.String");
			}

			Object paramObj27 = comments;

			if (comments == null) {
				paramObj27 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"updateLatestOrder",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26, paramObj27
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateOrder(
		HttpPrincipal httpPrincipal, java.lang.String orderId,
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
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = billingFirstName;

			if (billingFirstName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = billingLastName;

			if (billingLastName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = billingEmailAddress;

			if (billingEmailAddress == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = billingCompany;

			if (billingCompany == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = billingStreet;

			if (billingStreet == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = billingCity;

			if (billingCity == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = billingState;

			if (billingState == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = billingZip;

			if (billingZip == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = billingCountry;

			if (billingCountry == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = billingPhone;

			if (billingPhone == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = new BooleanWrapper(shipToBilling);
			Object paramObj12 = shippingFirstName;

			if (shippingFirstName == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = shippingLastName;

			if (shippingLastName == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = shippingEmailAddress;

			if (shippingEmailAddress == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = shippingCompany;

			if (shippingCompany == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = shippingStreet;

			if (shippingStreet == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = shippingCity;

			if (shippingCity == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = shippingState;

			if (shippingState == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = shippingZip;

			if (shippingZip == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = shippingCountry;

			if (shippingCountry == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = shippingPhone;

			if (shippingPhone == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = ccName;

			if (ccName == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = ccType;

			if (ccType == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = ccNumber;

			if (ccNumber == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = new IntegerWrapper(ccExpMonth);
			Object paramObj26 = new IntegerWrapper(ccExpYear);
			Object paramObj27 = ccVerNumber;

			if (ccVerNumber == null) {
				paramObj27 = new NullWrapper("java.lang.String");
			}

			Object paramObj28 = comments;

			if (comments == null) {
				paramObj28 = new NullWrapper("java.lang.String");
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
						paramObj26, paramObj27, paramObj28
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateOrder(
		HttpPrincipal httpPrincipal, java.lang.String orderId,
		java.lang.String ppTxnId, java.lang.String ppPaymentStatus,
		double ppPaymentGross, java.lang.String ppReceiverEmail,
		java.lang.String ppPayerEmail)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = ppTxnId;

			if (ppTxnId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = ppPaymentStatus;

			if (ppPaymentStatus == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new DoubleWrapper(ppPaymentGross);
			Object paramObj4 = ppReceiverEmail;

			if (ppReceiverEmail == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = ppPayerEmail;

			if (ppPayerEmail == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"updateOrder",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.shopping.model.ShoppingOrder)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static boolean hasAdmin(HttpPrincipal httpPrincipal,
		java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = orderId;

			if (orderId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ShoppingOrderServiceUtil.class.getName(),
					"hasAdmin", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	private static final Log _log = LogFactory.getLog(ShoppingOrderServiceHttp.class);
}
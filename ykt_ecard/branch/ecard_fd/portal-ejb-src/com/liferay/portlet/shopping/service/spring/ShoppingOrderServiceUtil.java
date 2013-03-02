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

package com.liferay.portlet.shopping.service.spring;

/**
 * <a href="ShoppingOrderServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderServiceUtil {
	public static final String PORTLET_ID = "34";

	public static void addNote(java.lang.String orderId,
		java.lang.String noteContent)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.addNote(orderId, noteContent);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void completeOrder(java.lang.String orderId,
		java.lang.String ppTxnId, java.lang.String ppPaymentStatus,
		double ppPaymentGross, java.lang.String ppReceiverEmail,
		java.lang.String ppPayerEmail)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.completeOrder(orderId, ppTxnId,
				ppPaymentStatus, ppPaymentGross, ppReceiverEmail, ppPayerEmail);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteNote(java.lang.String orderId,
		java.lang.String noteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.deleteNote(orderId, noteId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteOrder(java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.deleteOrder(orderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteOrder(
		com.liferay.portlet.shopping.model.ShoppingOrder order)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.deleteOrder(order);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder getLatestOrder()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getLatestOrder();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getNotes(java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getNotes(orderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder getOrder(
		java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrder(orderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getOrders(java.lang.String ppPaymentStatus)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrders(ppPaymentStatus);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getOrders(java.lang.String ppPaymentStatus,
		int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrders(ppPaymentStatus, begin, end);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getOrders(java.lang.String companyId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrders(companyId, ppPaymentStatus);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getOrders(java.lang.String companyId,
		java.lang.String ppPaymentStatus, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrders(companyId, ppPaymentStatus,
				begin, end);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getOrdersSize(java.lang.String ppPaymentStatus)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrdersSize(ppPaymentStatus);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getOrdersSize(java.lang.String companyId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.getOrdersSize(companyId, ppPaymentStatus);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder saveLatestOrder(
		com.liferay.portlet.shopping.model.ShoppingCart cart)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.saveLatestOrder(cart);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void sendOrderEmail(java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.sendOrderEmail(orderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void sendShippingEmail(java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();
			shoppingOrderService.sendShippingEmail(orderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateLatestOrder(
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
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.updateLatestOrder(billingFirstName,
				billingLastName, billingEmailAddress, billingCompany,
				billingStreet, billingCity, billingState, billingZip,
				billingCountry, billingPhone, shipToBilling, shippingFirstName,
				shippingLastName, shippingEmailAddress, shippingCompany,
				shippingStreet, shippingCity, shippingState, shippingZip,
				shippingCountry, shippingPhone, ccName, ccType, ccNumber,
				ccExpMonth, ccExpYear, ccVerNumber, comments);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateOrder(
		java.lang.String orderId, java.lang.String billingFirstName,
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
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.updateOrder(orderId, billingFirstName,
				billingLastName, billingEmailAddress, billingCompany,
				billingStreet, billingCity, billingState, billingZip,
				billingCountry, billingPhone, shipToBilling, shippingFirstName,
				shippingLastName, shippingEmailAddress, shippingCompany,
				shippingStreet, shippingCity, shippingState, shippingZip,
				shippingCountry, shippingPhone, ccName, ccType, ccNumber,
				ccExpMonth, ccExpYear, ccVerNumber, comments);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateOrder(
		java.lang.String orderId, java.lang.String ppTxnId,
		java.lang.String ppPaymentStatus, double ppPaymentGross,
		java.lang.String ppReceiverEmail, java.lang.String ppPayerEmail)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.updateOrder(orderId, ppTxnId,
				ppPaymentStatus, ppPaymentGross, ppReceiverEmail, ppPayerEmail);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin(java.lang.String orderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingOrderService shoppingOrderService = ShoppingOrderServiceFactory.getService();

			return shoppingOrderService.hasAdmin(orderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}
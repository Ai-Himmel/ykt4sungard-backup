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

import com.liferay.portlet.shopping.service.spring.ShoppingOrderServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingOrderServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderServiceSoap {
	public static void addNote(java.lang.String orderId,
		java.lang.String noteContent) throws RemoteException {
		try {
			ShoppingOrderServiceUtil.addNote(orderId, noteContent);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void completeOrder(java.lang.String orderId,
		java.lang.String ppTxnId, java.lang.String ppPaymentStatus,
		double ppPaymentGross, java.lang.String ppReceiverEmail,
		java.lang.String ppPayerEmail) throws RemoteException {
		try {
			ShoppingOrderServiceUtil.completeOrder(orderId, ppTxnId,
				ppPaymentStatus, ppPaymentGross, ppReceiverEmail, ppPayerEmail);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteNote(java.lang.String orderId,
		java.lang.String noteId) throws RemoteException {
		try {
			ShoppingOrderServiceUtil.deleteNote(orderId, noteId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteOrder(java.lang.String orderId)
		throws RemoteException {
		try {
			ShoppingOrderServiceUtil.deleteOrder(orderId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteOrder(
		com.liferay.portlet.shopping.model.ShoppingOrder order)
		throws RemoteException {
		try {
			ShoppingOrderServiceUtil.deleteOrder(order);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel getLatestOrder()
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.getLatestOrder();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel[] getNotes(
		java.lang.String orderId) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingOrderServiceUtil.getNotes(orderId);

			return (com.liferay.portlet.shopping.model.ShoppingOrder[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingOrder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel getOrder(
		java.lang.String orderId) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.getOrder(orderId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel[] getOrders(
		java.lang.String ppPaymentStatus) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingOrderServiceUtil.getOrders(ppPaymentStatus);

			return (com.liferay.portlet.shopping.model.ShoppingOrder[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingOrder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel[] getOrders(
		java.lang.String ppPaymentStatus, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingOrderServiceUtil.getOrders(ppPaymentStatus,
					begin, end);

			return (com.liferay.portlet.shopping.model.ShoppingOrder[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingOrder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel[] getOrders(
		java.lang.String companyId, java.lang.String ppPaymentStatus)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingOrderServiceUtil.getOrders(companyId,
					ppPaymentStatus);

			return (com.liferay.portlet.shopping.model.ShoppingOrder[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingOrder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel[] getOrders(
		java.lang.String companyId, java.lang.String ppPaymentStatus,
		int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingOrderServiceUtil.getOrders(companyId,
					ppPaymentStatus, begin, end);

			return (com.liferay.portlet.shopping.model.ShoppingOrder[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingOrder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getOrdersSize(java.lang.String ppPaymentStatus)
		throws RemoteException {
		try {
			int returnValue = ShoppingOrderServiceUtil.getOrdersSize(ppPaymentStatus);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getOrdersSize(java.lang.String companyId,
		java.lang.String ppPaymentStatus) throws RemoteException {
		try {
			int returnValue = ShoppingOrderServiceUtil.getOrdersSize(companyId,
					ppPaymentStatus);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel saveLatestOrder(
		com.liferay.portlet.shopping.model.ShoppingCart cart)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.saveLatestOrder(cart);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void sendOrderEmail(java.lang.String orderId)
		throws RemoteException {
		try {
			ShoppingOrderServiceUtil.sendOrderEmail(orderId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void sendShippingEmail(java.lang.String orderId)
		throws RemoteException {
		try {
			ShoppingOrderServiceUtil.sendShippingEmail(orderId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel updateLatestOrder(
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
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.updateLatestOrder(billingFirstName,
					billingLastName, billingEmailAddress, billingCompany,
					billingStreet, billingCity, billingState, billingZip,
					billingCountry, billingPhone, shipToBilling,
					shippingFirstName, shippingLastName, shippingEmailAddress,
					shippingCompany, shippingStreet, shippingCity,
					shippingState, shippingZip, shippingCountry, shippingPhone,
					ccName, ccType, ccNumber, ccExpMonth, ccExpYear,
					ccVerNumber, comments);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel updateOrder(
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
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.updateOrder(orderId,
					billingFirstName, billingLastName, billingEmailAddress,
					billingCompany, billingStreet, billingCity, billingState,
					billingZip, billingCountry, billingPhone, shipToBilling,
					shippingFirstName, shippingLastName, shippingEmailAddress,
					shippingCompany, shippingStreet, shippingCity,
					shippingState, shippingZip, shippingCountry, shippingPhone,
					ccName, ccType, ccNumber, ccExpMonth, ccExpYear,
					ccVerNumber, comments);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderModel updateOrder(
		java.lang.String orderId, java.lang.String ppTxnId,
		java.lang.String ppPaymentStatus, double ppPaymentGross,
		java.lang.String ppReceiverEmail, java.lang.String ppPayerEmail)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.updateOrder(orderId,
					ppTxnId, ppPaymentStatus, ppPaymentGross, ppReceiverEmail,
					ppPayerEmail);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String orderId)
		throws RemoteException {
		try {
			boolean returnValue = ShoppingOrderServiceUtil.hasAdmin(orderId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}
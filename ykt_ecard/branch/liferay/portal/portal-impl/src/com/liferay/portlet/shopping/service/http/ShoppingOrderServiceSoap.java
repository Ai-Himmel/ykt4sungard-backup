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

import com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingOrderServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.shopping.model.ShoppingOrderSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.shopping.model.ShoppingOrder</code>,
 * that is translated to a <code>com.liferay.portlet.shopping.model.ShoppingOrderSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil
 * @see com.liferay.portlet.shopping.service.http.ShoppingOrderServiceHttp
 * @see com.liferay.portlet.shopping.service.model.ShoppingOrderSoap
 *
 */
public class ShoppingOrderServiceSoap {
	public static void completeOrder(long plid, java.lang.String number,
		java.lang.String ppTxnId, java.lang.String ppPaymentStatus,
		double ppPaymentGross, java.lang.String ppReceiverEmail,
		java.lang.String ppPayerEmail) throws RemoteException {
		try {
			ShoppingOrderServiceUtil.completeOrder(plid, number, ppTxnId,
				ppPaymentStatus, ppPaymentGross, ppReceiverEmail, ppPayerEmail);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteOrder(long plid, long orderId)
		throws RemoteException {
		try {
			ShoppingOrderServiceUtil.deleteOrder(plid, orderId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderSoap getOrder(
		long plid, long orderId) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.getOrder(plid,
					orderId);

			return com.liferay.portlet.shopping.model.ShoppingOrderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void sendEmail(long plid, long orderId,
		java.lang.String emailType) throws RemoteException {
		try {
			ShoppingOrderServiceUtil.sendEmail(plid, orderId, emailType);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderSoap updateOrder(
		long plid, long orderId, java.lang.String billingFirstName,
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
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.updateOrder(plid,
					orderId, billingFirstName, billingLastName,
					billingEmailAddress, billingCompany, billingStreet,
					billingCity, billingState, billingZip, billingCountry,
					billingPhone, shipToBilling, shippingFirstName,
					shippingLastName, shippingEmailAddress, shippingCompany,
					shippingStreet, shippingCity, shippingState, shippingZip,
					shippingCountry, shippingPhone, ccName, ccType, ccNumber,
					ccExpMonth, ccExpYear, ccVerNumber, comments);

			return com.liferay.portlet.shopping.model.ShoppingOrderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderSoap updateOrder(
		long plid, long orderId, java.lang.String ppTxnId,
		java.lang.String ppPaymentStatus, double ppPaymentGross,
		java.lang.String ppReceiverEmail, java.lang.String ppPayerEmail)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingOrder returnValue = ShoppingOrderServiceUtil.updateOrder(plid,
					orderId, ppTxnId, ppPaymentStatus, ppPaymentGross,
					ppReceiverEmail, ppPayerEmail);

			return com.liferay.portlet.shopping.model.ShoppingOrderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(ShoppingOrderServiceSoap.class);
}
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

import com.liferay.portlet.shopping.service.spring.ShoppingCartServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingCartServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCartServiceSoap {
	public static void deleteCart(java.lang.String cartId)
		throws RemoteException {
		try {
			ShoppingCartServiceUtil.deleteCart(cartId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCartModel emptyCart(
		java.lang.String sessionId, java.lang.String companyId)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCart returnValue = ShoppingCartServiceUtil.emptyCart(sessionId,
					companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCartModel getCart(
		java.lang.String sessionId, java.lang.String companyId)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCart returnValue = ShoppingCartServiceUtil.getCart(sessionId,
					companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.util.Map getItems(java.lang.String companyId,
		java.lang.String itemIds) throws RemoteException {
		try {
			java.util.Map returnValue = ShoppingCartServiceUtil.getItems(companyId,
					itemIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCartModel updateCart(
		java.lang.String sessionId, java.lang.String companyId,
		java.lang.String itemIds, java.lang.String couponIds, int altShipping,
		boolean insure) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCart returnValue = ShoppingCartServiceUtil.updateCart(sessionId,
					companyId, itemIds, couponIds, altShipping, insure);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String cartId)
		throws RemoteException {
		try {
			boolean returnValue = ShoppingCartServiceUtil.hasAdmin(cartId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}
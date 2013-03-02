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
 * <a href="ShoppingCartServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCartServiceUtil {
	public static final String PORTLET_ID = "34";

	public static void deleteCart(java.lang.String cartId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCartService shoppingCartService = ShoppingCartServiceFactory.getService();
			shoppingCartService.deleteCart(cartId);
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

	public static com.liferay.portlet.shopping.model.ShoppingCart emptyCart(
		java.lang.String sessionId, java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCartService shoppingCartService = ShoppingCartServiceFactory.getService();

			return shoppingCartService.emptyCart(sessionId, companyId);
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

	public static com.liferay.portlet.shopping.model.ShoppingCart getCart(
		java.lang.String sessionId, java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCartService shoppingCartService = ShoppingCartServiceFactory.getService();

			return shoppingCartService.getCart(sessionId, companyId);
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

	public static java.util.Map getItems(java.lang.String companyId,
		java.lang.String itemIds) throws com.liferay.portal.SystemException {
		try {
			ShoppingCartService shoppingCartService = ShoppingCartServiceFactory.getService();

			return shoppingCartService.getItems(companyId, itemIds);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCart updateCart(
		java.lang.String sessionId, java.lang.String companyId,
		java.lang.String itemIds, java.lang.String couponIds, int altShipping,
		boolean insure)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCartService shoppingCartService = ShoppingCartServiceFactory.getService();

			return shoppingCartService.updateCart(sessionId, companyId,
				itemIds, couponIds, altShipping, insure);
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

	public static boolean hasAdmin(java.lang.String cartId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCartService shoppingCartService = ShoppingCartServiceFactory.getService();

			return shoppingCartService.hasAdmin(cartId);
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
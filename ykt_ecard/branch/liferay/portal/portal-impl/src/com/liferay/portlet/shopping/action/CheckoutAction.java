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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.shopping.BillingCityException;
import com.liferay.portlet.shopping.BillingCountryException;
import com.liferay.portlet.shopping.BillingEmailAddressException;
import com.liferay.portlet.shopping.BillingFirstNameException;
import com.liferay.portlet.shopping.BillingLastNameException;
import com.liferay.portlet.shopping.BillingPhoneException;
import com.liferay.portlet.shopping.BillingStateException;
import com.liferay.portlet.shopping.BillingStreetException;
import com.liferay.portlet.shopping.BillingZipException;
import com.liferay.portlet.shopping.CCExpirationException;
import com.liferay.portlet.shopping.CCNameException;
import com.liferay.portlet.shopping.CCNumberException;
import com.liferay.portlet.shopping.CCTypeException;
import com.liferay.portlet.shopping.ShippingCityException;
import com.liferay.portlet.shopping.ShippingCountryException;
import com.liferay.portlet.shopping.ShippingEmailAddressException;
import com.liferay.portlet.shopping.ShippingFirstNameException;
import com.liferay.portlet.shopping.ShippingLastNameException;
import com.liferay.portlet.shopping.ShippingPhoneException;
import com.liferay.portlet.shopping.ShippingStateException;
import com.liferay.portlet.shopping.ShippingStreetException;
import com.liferay.portlet.shopping.ShippingZipException;
import com.liferay.portlet.shopping.model.ShoppingCart;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.service.ShoppingOrderLocalServiceUtil;
import com.liferay.portlet.shopping.util.ShoppingPreferences;
import com.liferay.portlet.shopping.util.ShoppingUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="CheckoutAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CheckoutAction extends CartAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		if (redirectToLogin(req, res)) {
			return;
		}

		String cmd = ParamUtil.getString(req, Constants.CMD);

		getLatestOrder(req);

		if (cmd.equals(Constants.SAVE)) {
			updateCart(req);
			updateLatestOrder(req);
			saveLatestOrder(req);
			forwardCheckout(req, res);
		}
		else if (cmd.equals(Constants.UPDATE)) {
			try {
				updateLatestOrder(req);

				setForward(req, "portlet.shopping.checkout_second");
			}
			catch (Exception e) {
				if (e instanceof BillingCityException ||
					e instanceof BillingCountryException ||
					e instanceof BillingEmailAddressException ||
					e instanceof BillingFirstNameException ||
					e instanceof BillingLastNameException ||
					e instanceof BillingPhoneException ||
					e instanceof BillingStateException ||
					e instanceof BillingStreetException ||
					e instanceof BillingZipException ||
					e instanceof CCExpirationException ||
					e instanceof CCNameException ||
					e instanceof CCNumberException ||
					e instanceof CCTypeException ||
					e instanceof ShippingCityException ||
					e instanceof ShippingCountryException ||
					e instanceof ShippingEmailAddressException ||
					e instanceof ShippingFirstNameException ||
					e instanceof ShippingLastNameException ||
					e instanceof ShippingPhoneException ||
					e instanceof ShippingStateException ||
					e instanceof ShippingStreetException ||
					e instanceof ShippingZipException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.checkout_first");
				}
				else if (e instanceof PrincipalException) {
					setForward(req, "portlet.shopping.error");
				}
				else {
					throw e;
				}
			}
		}
		else if (cmd.equals(Constants.VIEW)) {
			setForward(req, "portlet.shopping.checkout_third");
		}
		else {
			setForward(req, "portlet.shopping.checkout_first");
		}
	}

	protected void getLatestOrder(ActionRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		ShoppingOrder order = ShoppingOrderLocalServiceUtil.getLatestOrder(
			themeDisplay.getUserId(), themeDisplay.getPortletGroupId());

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

	protected void forwardCheckout(ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		ShoppingCart cart = ShoppingUtil.getCart(req);

		ShoppingOrder order =
			(ShoppingOrder)req.getAttribute(WebKeys.SHOPPING_ORDER);

		ShoppingPreferences prefs = ShoppingPreferences.getInstance(
			themeDisplay.getCompanyId(), themeDisplay.getPortletGroupId());

		String returnURL = ShoppingUtil.getPayPalReturnURL(
			((ActionResponseImpl)res).createActionURL(), order);
		String notifyURL = ShoppingUtil.getPayPalNotifyURL(themeDisplay);

		if (prefs.usePayPal()) {
			double total = ShoppingUtil.calculateTotal(
				cart.getItems(), order.getBillingState(), cart.getCoupon(),
				cart.getAltShipping(), cart.isInsure());

			String redirectURL = ShoppingUtil.getPayPalRedirectURL(
				prefs, order, total, returnURL, notifyURL);

			res.sendRedirect(redirectURL);
		}
		else {
			ShoppingOrderLocalServiceUtil.sendEmail(order, "confirmation");

			res.sendRedirect(returnURL);
		}
	}

	protected void saveLatestOrder(ActionRequest req) throws Exception {
		ShoppingCart cart = ShoppingUtil.getCart(req);

		ShoppingOrder order =
			ShoppingOrderLocalServiceUtil.saveLatestOrder(cart);

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

	protected void updateLatestOrder(ActionRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		String billingFirstName = ParamUtil.getString(req, "billingFirstName");
		String billingLastName = ParamUtil.getString(req, "billingLastName");
		String billingEmailAddress = ParamUtil.getString(
			req, "billingEmailAddress");
		String billingCompany = ParamUtil.getString(req, "billingCompany");
		String billingStreet = ParamUtil.getString(req, "billingStreet");
		String billingCity = ParamUtil.getString(req, "billingCity");

		String billingStateSel = ParamUtil.getString(req, "billingStateSel");
		String billingState = billingStateSel;
		if (Validator.isNull(billingStateSel)) {
			billingState = ParamUtil.getString(req, "billingState");
		}

		String billingZip = ParamUtil.getString(req, "billingZip");
		String billingCountry = ParamUtil.getString(req, "billingCountry");
		String billingPhone = ParamUtil.getString(req, "billingPhone");

		boolean shipToBilling = ParamUtil.getBoolean(req, "shipToBilling");
		String shippingFirstName = ParamUtil.getString(
			req, "shippingFirstName");
		String shippingLastName = ParamUtil.getString(req, "shippingLastName");
		String shippingEmailAddress = ParamUtil.getString(
			req, "shippingEmailAddress");
		String shippingCompany = ParamUtil.getString(req, "shippingCompany");
		String shippingStreet = ParamUtil.getString(req, "shippingStreet");
		String shippingCity = ParamUtil.getString(req, "shippingCity");

		String shippingStateSel = ParamUtil.getString(req, "shippingStateSel");
		String shippingState = shippingStateSel;
		if (Validator.isNull(shippingStateSel)) {
			shippingState = ParamUtil.getString(req, "shippingState");
		}

		String shippingZip = ParamUtil.getString(req, "shippingZip");
		String shippingCountry = ParamUtil.getString(req, "shippingCountry");
		String shippingPhone = ParamUtil.getString(req, "shippingPhone");

		String ccName = ParamUtil.getString(req, "ccName");
		String ccType = ParamUtil.getString(req, "ccType");
		String ccNumber = ParamUtil.getString(req, "ccNumber");
		int ccExpMonth = ParamUtil.getInteger(req, "ccExpMonth");
		int ccExpYear = ParamUtil.getInteger(req, "ccExpYear");
		String ccVerNumber = ParamUtil.getString(req, "ccVerNumber");

		String comments = ParamUtil.getString(req, "comments");

		ShoppingOrder order = ShoppingOrderLocalServiceUtil.updateLatestOrder(
			themeDisplay.getUserId(), themeDisplay.getPortletGroupId(),
			billingFirstName, billingLastName, billingEmailAddress,
			billingCompany, billingStreet, billingCity, billingState,
			billingZip, billingCountry, billingPhone, shipToBilling,
			shippingFirstName, shippingLastName, shippingEmailAddress,
			shippingCompany, shippingStreet, shippingCity, shippingState,
			shippingZip, shippingCountry, shippingPhone, ccName, ccType,
			ccNumber, ccExpMonth, ccExpYear, ccVerNumber, comments);

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

}
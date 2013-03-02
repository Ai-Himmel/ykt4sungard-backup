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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Company;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.admin.model.ShoppingConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
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
import com.liferay.portlet.shopping.service.spring.ShoppingCartServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderLocalServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderServiceUtil;
import com.liferay.portlet.shopping.util.ShoppingUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletSession;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="CheckoutAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.19 $
 *
 */
public class CheckoutAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		if (redirectToLogin(req, res)) {
			return;
		}

		String cmd = req.getParameter(Constants.CMD);

		try {
			_editLatestOrder(req);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			setForward(req, Constants.COMMON_ERROR);
		}

		if (cmd != null && cmd.equals(Constants.SAVE)) {
			try {
				ActionUtil.updateCart(req, res);

				_updateLatestOrder(req);

				_saveLatestOrder(req);

				_forwardCheckout(req, res);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else if (cmd != null && cmd.equals(Constants.UPDATE)) {
			try {
				_updateLatestOrder(req);

				setForward(req, "portlet.shopping.checkout_second");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof BillingCityException ||
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

					setForward(req,
						"portlet.shopping.checkout_first");
				}
				else if (e != null &&
						 e instanceof PrincipalException) {

					setForward(req, "portlet.shopping.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.VIEW)) {
			setForward(req, "portlet.shopping.checkout_third");
		}
		else {
			setForward(req, "portlet.shopping.checkout_first");
		}
	}

	private void _editLatestOrder(ActionRequest req) throws Exception {
		ShoppingOrder order = ShoppingOrderServiceUtil.getLatestOrder();

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

	private void _forwardCheckout(ActionRequest req, ActionResponse res)
		throws Exception {

		PortletSession ses = req.getPortletSession();

		PortletContext portletCtx = ses.getPortletContext();

		Company company = PortalUtil.getCompany(req);

		ShoppingCart cart = ShoppingCartServiceUtil.getCart(
			ses.getId(), company.getCompanyId());

		ShoppingOrder order =
			(ShoppingOrder)req.getAttribute(WebKeys.SHOPPING_ORDER);

		ShoppingConfig shoppingConfig =
			AdminConfigServiceUtil.getShoppingConfig(company.getCompanyId());

		String mainPath = (String)portletCtx.getAttribute(WebKeys.MAIN_PATH);

		String returnURL = ShoppingUtil.getPayPalReturnURL(
			((ActionResponseImpl)res).createActionURL(), order);
		String notifyURL = ShoppingUtil.getPayPalNotifyURL(company, mainPath);

		if (shoppingConfig.usePayPal()) {
			double total = ShoppingUtil.calculateTotal(
				cart.getItems(), order.getBillingState(), cart.getCoupon(),
				cart.getAltShipping(), cart.isInsure());

			String redirectURL = ShoppingUtil.getPayPalRedirectURL(
				shoppingConfig, order, total, returnURL, notifyURL);

			// Send redirect

			res.sendRedirect(redirectURL);
		}
		else {
			ShoppingOrderLocalServiceUtil.sendOrderEmail(order);

			// Send redirect

			res.sendRedirect(returnURL);
		}
	}

	private void _saveLatestOrder(ActionRequest req) throws Exception {
		ShoppingCart cart = ShoppingCartServiceUtil.getCart(
			req.getPortletSession().getId(), PortalUtil.getCompanyId(req));

		ShoppingOrder order =
			ShoppingOrderServiceUtil.saveLatestOrder(cart);

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

	private void _updateLatestOrder(ActionRequest req) throws Exception {
		String billingFirstName = ParamUtil.getString(
			req, "order_b_first_name");
		String billingLastName = ParamUtil.getString(req, "order_b_last_name");
		String billingEmailAddress = ParamUtil.getString(
			req, "order_b_email_address");
		String billingCompany = ParamUtil.getString(req, "order_b_company");
		String billingStreet = ParamUtil.getString(req, "order_b_street");
		String billingCity = ParamUtil.getString(req, "order_b_city");

		String billingStateSel = ParamUtil.getString(req, "order_b_state_sel");
		String billingState = billingStateSel;
		if (Validator.isNull(billingStateSel)) {
			billingState = ParamUtil.getString(req, "order_b_state");
		}

		String billingZip = ParamUtil.getString(req, "order_b_zip");
		String billingCountry = ParamUtil.getString(req, "order_b_country");
		String billingPhone = ParamUtil.getString(req, "order_b_phone");

		boolean shipToBilling = ParamUtil.get(req, "order_s_t_b", false);
		String shippingFirstName = ParamUtil.getString(
			req, "order_s_first_name");
		String shippingLastName = ParamUtil.getString(req, "order_s_last_name");
		String shippingEmailAddress = ParamUtil.getString(
			req, "order_s_email_address");
		String shippingCompany = ParamUtil.getString(req, "order_s_company");
		String shippingStreet = ParamUtil.getString(req, "order_s_street");
		String shippingCity = ParamUtil.getString(req, "order_s_city");

		String shippingStateSel = ParamUtil.getString(req, "order_s_state_sel");
		String shippingState = shippingStateSel;
		if (Validator.isNull(shippingStateSel)) {
			shippingState = ParamUtil.getString(req, "order_s_state");
		}

		String shippingZip = ParamUtil.getString(req, "order_s_zip");
		String shippingCountry = ParamUtil.getString(req, "order_s_country");
		String shippingPhone = ParamUtil.getString(req, "order_s_phone");

		String ccName = ParamUtil.getString(req, "order_cc_name");
		String ccType = ParamUtil.getString(req, "order_cc_type");
		String ccNumber = ParamUtil.getString(req, "order_cc_number");
		int ccExpMonth = ParamUtil.getInteger(req, "order_cc_exp_month");
		int ccExpYear = ParamUtil.getInteger(req, "order_cc_exp_year");
		String ccVerNumber = ParamUtil.getString(req, "order_cc_ver_number");

		String comments = ParamUtil.getString(req, "order_comments");

		ShoppingOrder order = ShoppingOrderServiceUtil.updateLatestOrder(
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
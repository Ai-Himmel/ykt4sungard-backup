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

import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.shopping.util.ShoppingPreferences;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="ConfigurationActionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ConfigurationActionImpl implements ConfigurationAction {

	public void processAction(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		ShoppingPreferences prefs = ShoppingPreferences.getInstance(
			themeDisplay.getCompanyId(), themeDisplay.getPortletGroupId());

		String tabs2 = ParamUtil.getString(req, "tabs2");
		String tabs3 = ParamUtil.getString(req, "tabs3");

		if (tabs2.equals("payment-settings")) {
			updatePayment(req, prefs);
		}
		else if (tabs2.equals("shipping-calculation")) {
			updateShippingCalculation(req, prefs);
		}
		else if (tabs2.equals("insurance-calculation")) {
			updateInsuranceCalculation(req, prefs);
		}
		else if (tabs2.equals("emails")) {
			if (tabs3.equals("email-from")) {
				updateEmailFrom(req, prefs);
			}
			else if (tabs3.equals("confirmation-email")) {
				updateEmailOrderConfirmation(req, prefs);
			}
			else if (tabs3.equals("shipping-email")) {
				updateEmailOrderShipping(req, prefs);
			}
		}

		if (SessionErrors.isEmpty(req)) {
			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/shopping/configuration.jsp";
	}

	protected void updateEmailFrom(ActionRequest req, ShoppingPreferences prefs)
		throws Exception {

		String emailFromName = ParamUtil.getString(req, "emailFromName");
		String emailFromAddress = ParamUtil.getString(req, "emailFromAddress");

		if (Validator.isNull(emailFromName)) {
			SessionErrors.add(req, "emailFromName");
		}
		else if (!Validator.isEmailAddress(emailFromAddress)) {
			SessionErrors.add(req, "emailFromAddress");
		}
		else {
			prefs.setEmailFromName(emailFromName);
			prefs.setEmailFromAddress(emailFromAddress);
		}
	}

	protected void updateEmailOrderConfirmation(
			ActionRequest req, ShoppingPreferences prefs)
		throws Exception {

		boolean emailOrderConfirmationEnabled = ParamUtil.getBoolean(
			req, "emailOrderConfirmationEnabled");
		String emailOrderConfirmationSubject = ParamUtil.getString(
			req, "emailOrderConfirmationSubject");
		String emailOrderConfirmationBody = ParamUtil.getString(
			req, "emailOrderConfirmationBody");

		if (Validator.isNull(emailOrderConfirmationSubject)) {
			SessionErrors.add(req, "emailOrderConfirmationSubject");
		}
		else if (Validator.isNull(emailOrderConfirmationBody)) {
			SessionErrors.add(req, "emailOrderConfirmationBody");
		}
		else {
			prefs.setEmailOrderConfirmationEnabled(
				emailOrderConfirmationEnabled);
			prefs.setEmailOrderConfirmationSubject(
				emailOrderConfirmationSubject);
			prefs.setEmailOrderConfirmationBody(emailOrderConfirmationBody);
		}
	}

	protected void updateEmailOrderShipping(
			ActionRequest req, ShoppingPreferences prefs)
		throws Exception {

		boolean emailOrderShippingEnabled = ParamUtil.getBoolean(
			req, "emailOrderShippingEnabled");
		String emailOrderShippingSubject = ParamUtil.getString(
			req, "emailOrderShippingSubject");
		String emailOrderShippingBody = ParamUtil.getString(
			req, "emailOrderShippingBody");

		if (Validator.isNull(emailOrderShippingSubject)) {
			SessionErrors.add(req, "emailOrderShippingSubject");
		}
		else if (Validator.isNull(emailOrderShippingBody)) {
			SessionErrors.add(req, "emailOrderShippingBody");
		}
		else {
			prefs.setEmailOrderShippingEnabled(emailOrderShippingEnabled);
			prefs.setEmailOrderShippingSubject(emailOrderShippingSubject);
			prefs.setEmailOrderShippingBody(emailOrderShippingBody);
		}
	}

	protected void updateInsuranceCalculation(
			ActionRequest req, ShoppingPreferences prefs)
		throws Exception {

		String insuranceFormula = ParamUtil.getString(req, "insuranceFormula");

		String[] insurance = new String[5];

		for (int i = 0; i < insurance.length; i++) {
			insurance[i] = String.valueOf(
				ParamUtil.getDouble(req, "insurance" + i));
		}

		prefs.setInsuranceFormula(insuranceFormula);
		prefs.setInsurance(insurance);
	}

	protected void updatePayment(ActionRequest req, ShoppingPreferences prefs)
		throws Exception {

		String payPalEmailAddress = ParamUtil.getString(
			req, "payPalEmailAddress");
		String[] ccTypes = StringUtil.split(
			ParamUtil.getString(req, "ccTypes"));
		String currencyId = ParamUtil.getString(req, "currencyId");
		String taxState = ParamUtil.getString(req, "taxState");
		double taxRate = ParamUtil.getDouble(req, "taxRate") / 100;
		double minOrder = ParamUtil.getDouble(req, "minOrder");

		prefs.setPayPalEmailAddress(payPalEmailAddress);
		prefs.setCcTypes(ccTypes);
		prefs.setCurrencyId(currencyId);
		prefs.setTaxState(taxState);
		prefs.setTaxRate(taxRate);
		prefs.setMinOrder(minOrder);
	}

	protected void updateShippingCalculation(
			ActionRequest req, ShoppingPreferences prefs)
		throws Exception {

		String shippingFormula = ParamUtil.getString(req, "shippingFormula");

		String[] shipping = new String[5];

		for (int i = 0; i < shipping.length; i++) {
			shipping[i] = String.valueOf(
				ParamUtil.getDouble(req, "shipping" + i));
		}

		prefs.setShippingFormula(shippingFormula);
		prefs.setShipping(shipping);
	}

}
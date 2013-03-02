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
import com.liferay.portal.service.spring.PropertiesServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.admin.model.EmailConfig;
import com.liferay.portlet.admin.model.ShoppingConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.util.Properties;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="UpdateShoppingConfigAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class UpdateShoppingConfigAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			String cmd = ParamUtil.get(req, Constants.CMD, "payment");

			ShoppingConfig shoppingConfig =
				AdminConfigServiceUtil.getShoppingConfig(
					PortalUtil.getCompanyId(req));

			if (cmd.equals("payment")) {
				_updatePayment(req, shoppingConfig);
			}
			else if (cmd.equals("display")) {
				_updateDisplay(req, shoppingConfig);
			}
			else if (cmd.equals("shipping_calculation")) {
				_updateShippingCalculation(req, shoppingConfig);
			}
			else if (cmd.equals("insurance_calculation")) {
				_updateInsuranceCalculation(req, shoppingConfig);
			}
			else if (cmd.equals("order_email")) {
				_updateOrderEmail(req, shoppingConfig);
			}
			else if (cmd.equals("shipping_email")) {
				_updateShippingEmail(req, shoppingConfig);
			}

			// Update config

			AdminConfigServiceUtil.updateShoppingConfig(shoppingConfig);

			// Session messages

			SessionMessages.add(
				req, UpdateShoppingConfigAction.class.getName());

			// Send redirect

			res.sendRedirect(ParamUtil.getString(req, "redirect"));
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.shopping.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
	}

	private void _updateDisplay(
			ActionRequest req, ShoppingConfig shoppingConfig)
		throws Exception {

		String[] displayPropertyKeys = new String[] {
			PropsUtil.SHOPPING_CART_MIN_QTY_MULTIPLE,
			PropsUtil.SHOPPING_CATEGORY_FORWARD_TO_CART,
			PropsUtil.SHOPPING_CATEGORY_SHOW_ITEM_DESCRIPTION,
			PropsUtil.SHOPPING_CATEGORY_SHOW_ITEM_PROPERTIES,
			PropsUtil.SHOPPING_CATEGORY_SHOW_ITEM_PRICES,
			PropsUtil.SHOPPING_CATEGORY_SHOW_SPECIAL_ITEMS,
			PropsUtil.SHOPPING_CATEGORY_SHOW_SPECIAL_ITEM_DESCRIPTION,
			PropsUtil.SHOPPING_ITEM_SHOW_AVAILABILITY
		};

		String companyId = PortalUtil.getCompanyId(req);

		Properties propertiesObj =
			PropertiesServiceUtil.getPortalProperties(companyId);

		for (int i = 0; i < displayPropertyKeys.length; i++) {
			boolean displayPropertyBoolean = ParamUtil.getBoolean(
				req, displayPropertyKeys[i]);

			propertiesObj.setProperty(
				displayPropertyKeys[i],
				Boolean.toString(displayPropertyBoolean));

		}

		PropertiesServiceUtil.updatePortalProperties(companyId, propertiesObj);
	}

	private void _updateInsuranceCalculation(
			ActionRequest req, ShoppingConfig shoppingConfig)
		throws Exception {

		String insuranceFormula = ParamUtil.get(
			req, "config_i", ShoppingConfig.DEFAULT_INSURANCE_FORMULA);

		String[] insurance = new String[5];
		for (int i = 0; i < insurance.length; i++) {
			insurance[i] = Double.toString(
				ParamUtil.get(req, "config_i_" + i, 0.0));
		}

		shoppingConfig.setInsuranceFormula(insuranceFormula);
		shoppingConfig.setInsurance(insurance);
	}

	private void _updateOrderEmail(
			ActionRequest req, ShoppingConfig shoppingConfig)
		throws Exception {

		boolean orderEmailSend = ParamUtil.get(req, "config_oe_send", true);
		String orderEmailSubject = ParamUtil.getString(
			req, "config_oe_subject");
		String orderEmailBody = ParamUtil.getString(req, "config_oe_body");

		EmailConfig emailConfig = new EmailConfig(
			orderEmailSend, orderEmailSubject, orderEmailBody);

		shoppingConfig.setOrderEmail(emailConfig);
	}

	private void _updatePayment(
			ActionRequest req, ShoppingConfig shoppingConfig)
		throws Exception {

		String payPalEmailAddress = ParamUtil.getString(req, "config_pp_e_a");
		String[] ccTypes = StringUtil.split(
			ParamUtil.getString(req, "config_cc_types"));
		String currencyId = ParamUtil.getString(req, "config_c_id");
		String taxState = ParamUtil.getString(req, "config_t_s");
		double taxRate = ParamUtil.get(req, "config_t_r", 0.0) / 100;
		double minOrder = ParamUtil.get(req, "config_m_o", 0.0);

		shoppingConfig.setPayPalEmailAddress(payPalEmailAddress);
		shoppingConfig.setCcTypes(ccTypes);
		shoppingConfig.setCurrencyId(currencyId);
		shoppingConfig.setTaxState(taxState);
		shoppingConfig.setTaxRate(taxRate);
		shoppingConfig.setMinOrder(minOrder);
	}

	private void _updateShippingCalculation(
			ActionRequest req, ShoppingConfig shoppingConfig)
		throws Exception {

		String shippingFormula = ParamUtil.get(
			req, "config_s", ShoppingConfig.DEFAULT_SHIPPING_FORMULA);

		String[] shipping = new String[5];
		for (int i = 0; i < shipping.length; i++) {
			shipping[i] = Double.toString(
				ParamUtil.get(req, "config_s_" + i, 0.0));
		}

		String[][] alternativeShipping = new String[2][10];
		for (int i = 0; i < 10; i++) {
			String altShippingName = ParamUtil.getString(
				req, "config_alt_s_name_" + i);
			String altShippingDelta = Double.toString(
				ParamUtil.getDouble(req, "config_alt_s_delta_" + i));

			if (Validator.isNull(altShippingName) ||
				Validator.isNull(altShippingDelta)) {

				altShippingName = StringPool.BLANK;
				altShippingDelta = StringPool.BLANK;
			}

			alternativeShipping[0][i] = altShippingName;
			alternativeShipping[1][i] = altShippingDelta;
		}

		shoppingConfig.setShippingFormula(shippingFormula);
		shoppingConfig.setShipping(shipping);
		shoppingConfig.setAlternativeShipping(alternativeShipping);
	}

	private void _updateShippingEmail(
			ActionRequest req, ShoppingConfig shoppingConfig)
		throws Exception {

		boolean shippingEmailSend = ParamUtil.get(req, "config_se_send", true);
		String shippingEmailSubject = ParamUtil.getString(
			req, "config_se_subject");
		String shippingEmailBody = ParamUtil.getString(req, "config_se_body");

		EmailConfig emailConfig = new EmailConfig(
			shippingEmailSend, shippingEmailSubject, shippingEmailBody);

		shoppingConfig.setShippingEmail(emailConfig);
	}

}
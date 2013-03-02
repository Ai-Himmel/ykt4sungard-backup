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

package com.liferay.portlet.shopping.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.service.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;

import java.io.IOException;

import java.util.Currency;
import java.util.Locale;
import java.util.Set;
import java.util.TreeSet;

import javax.portlet.PortletPreferences;
import javax.portlet.ReadOnlyException;
import javax.portlet.ValidatorException;

/**
 * <a href="ShoppingPreferences.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingPreferences {

	public static final String[] CC_TYPES =
		new String[] {"visa", "mastercard", "discover", "amex"};

	public static final String[] CURRENCY_IDS;

	static {
		String[] ids = null;

		try {
			Set set = new TreeSet();

			Locale[] locales = Locale.getAvailableLocales();

			for (int i = 0; i < locales.length; i++) {
				Locale locale = locales[i];

				if (locale.getCountry().length() == 2) {
					Currency currency = Currency.getInstance(locale);

					String currencyId = currency.getCurrencyCode();

					set.add(currencyId);
				}
			}

			ids = (String[])set.toArray(new String[0]);
		}
		catch (Exception e) {
			ids = new String[] {"USD", "CAD", "EUR", "GBP", "JPY"};
		}
		finally {
			CURRENCY_IDS = ids;
		}
	}

	public static final double[] SHIPPING_RANGE = {
		0.01, 9.99, 10.00, 49.99, 50.00, 99.99, 100.00, 199.99, 200.00,
		Double.POSITIVE_INFINITY
	};

	public static final double[] INSURANCE_RANGE = {
		0.01, 9.99, 10.00, 49.99, 50.00, 99.99, 100.00, 199.99, 200.00,
		Double.POSITIVE_INFINITY
	};

	public static ShoppingPreferences getInstance(long companyId, long groupId)
		throws PortalException, SystemException {

		return new ShoppingPreferences(companyId, groupId);
	}

	public String getPayPalEmailAddress() {
		return _prefs.getValue("paypal-email-address", StringPool.BLANK);
	}

	public void setPayPalEmailAddress(String payPalEmailAddress)
		throws ReadOnlyException {

		_prefs.setValue("paypal-email-address", payPalEmailAddress);
	}

	public boolean usePayPal() {
		return Validator.isNotNull(getPayPalEmailAddress());
	}

	public String getCurrencyId() {
		return _prefs.getValue("currency-id", "USD");
	}

	public void setCurrencyId(String currencyId) throws ReadOnlyException {
		_prefs.setValue("currency-id", currencyId);
	}

	public String[] getCcTypes() {
		return StringUtil.split(_prefs.getValue(
			"cc-types", StringUtil.merge(CC_TYPES)));
	}

	public void setCcTypes(String[] ccTypes) throws ReadOnlyException {
		_prefs.setValue("cc-types", StringUtil.merge(ccTypes));
	}

	public String getTaxState() {
		return _prefs.getValue("tax-state", "CA");
	}

	public void setTaxState(String taxState) throws ReadOnlyException {
		_prefs.setValue("tax-state", taxState);
	}

	public double getTaxRate() {
		return GetterUtil.getDouble(_prefs.getValue(
			"tax-rate", StringPool.BLANK));
	}

	public void setTaxRate(double taxRate) throws ReadOnlyException {
		_prefs.setValue("tax-rate", String.valueOf(taxRate));
	}

	public String getShippingFormula() {
		return _prefs.getValue("shipping-formula", "flat");
	}

	public void setShippingFormula(String shippingFormula)
		throws ReadOnlyException {

		_prefs.setValue("shipping-formula", shippingFormula);
	}

	public String[] getShipping() {
		String value = _prefs.getValue("shipping", null);

		if (value == null) {
			return new String[5];
		}
		else {
			return StringUtil.split(value);
		}
	}

	public void setShipping(String[] shipping) throws ReadOnlyException {
		_prefs.setValue("shipping", StringUtil.merge(shipping));
	}

	public String[][] getAlternativeShipping() {
		String value = _prefs.getValue("alternative-shipping", null);

		if (value == null) {
			return new String[0][0];
		}
		else {
			String[] array =
				StringUtil.split("alternative-shipping", "[$_ARRAY_$]");

			String[][] alternativeShipping = new String[array.length][0];

			for (int i = 0; i < array.length; i++) {
				alternativeShipping[i] = StringUtil.split(array[i]);
			}

			return alternativeShipping;
		}
	}

	public void setAlternativeShipping(String[][] alternativeShipping)
		throws ReadOnlyException {

		StringMaker sm = new StringMaker();

		for (int i = 0; i < alternativeShipping.length; i++) {
			sm.append(StringUtil.merge(alternativeShipping[i]));

			if ((i + 1) < alternativeShipping.length) {
				sm.append("[$_ARRAY_$]");
			}
		}

		_prefs.setValue("alternative-shipping", sm.toString());
	}

	public boolean useAlternativeShipping() {
		String[][] alternativeShipping = getAlternativeShipping();

		try {
			for (int i = 0; i < 10; i++) {
				if (Validator.isNotNull(alternativeShipping[0][i]) &&
					Validator.isNotNull(alternativeShipping[1][i])) {

					return true;
				}
			}
		}
		catch (Exception e) {
		}

		return false;
	}

	public String getAlternativeShippingName(int altShipping) {
		String altShippingName = StringPool.BLANK;

		try {
			altShippingName = getAlternativeShipping()[0][altShipping];
		}
		catch (Exception e) {
		}

		return altShippingName;
	}

	public String getInsuranceFormula() {
		return _prefs.getValue("insurance-formula", "flat");
	}

	public void setInsuranceFormula(String insuranceFormula)
		throws ReadOnlyException {

		_prefs.setValue("insurance-formula", insuranceFormula);
	}

	public String[] getInsurance() {
		String value = _prefs.getValue("insurance", null);

		if (value == null) {
			return new String[5];
		}
		else {
			return StringUtil.split(value);
		}
	}

	public void setInsurance(String[] insurance) throws ReadOnlyException {
		_prefs.setValue("insurance", StringUtil.merge(insurance));
	}

	public double getMinOrder() {
		return GetterUtil.getDouble(_prefs.getValue(
			"min-order", StringPool.BLANK));
	}

	public void setMinOrder(double minOrder) throws ReadOnlyException {
		_prefs.setValue("min-order", String.valueOf(minOrder));
	}

	public String getEmailFromAddress() {
		String emailFromAddress = PropsUtil.get(
			PropsUtil.SHOPPING_EMAIL_FROM_ADDRESS);

		return _prefs.getValue("email-from-address", emailFromAddress);
	}

	public void setEmailFromAddress(String emailFromAddress)
		throws ReadOnlyException {

		_prefs.setValue("email-from-address", emailFromAddress);
	}

	public String getEmailFromName() {
		String emailFromName = PropsUtil.get(
			PropsUtil.SHOPPING_EMAIL_FROM_NAME);

		return _prefs.getValue("email-from-name", emailFromName);
	}

	public void setEmailFromName(String emailFromName)
		throws ReadOnlyException {

		_prefs.setValue("email-from-name", emailFromName);
	}

	public boolean getEmailOrderConfirmationEnabled() {
		String emailOrderConfirmationEnabled = _prefs.getValue(
			"email-order-confirmation-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailOrderConfirmationEnabled)) {
			return GetterUtil.getBoolean(emailOrderConfirmationEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.SHOPPING_EMAIL_ORDER_CONFIRMATION_ENABLED));
		}
	}

	public void setEmailOrderConfirmationEnabled(
			boolean emailOrderConfirmationEnabled)
		throws ReadOnlyException {

		_prefs.setValue(
			"email-order-confirmation-enabled",
			String.valueOf(emailOrderConfirmationEnabled));
	}

	public String getEmailOrderConfirmationBody() throws IOException {
		String emailOrderConfirmationBody = _prefs.getValue(
			"email-order-confirmation-body", StringPool.BLANK);

		if (Validator.isNotNull(emailOrderConfirmationBody)) {
			return emailOrderConfirmationBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.SHOPPING_EMAIL_ORDER_CONFIRMATION_BODY));
		}
	}

	public void setEmailOrderConfirmationBody(String emailOrderConfirmationBody)
		throws ReadOnlyException {

		_prefs.setValue(
			"email-order-confirmation-body", emailOrderConfirmationBody);
	}

	public String getEmailOrderConfirmationSubject() throws IOException {
		String emailOrderConfirmationSubject = _prefs.getValue(
			"email-order-confirmation-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailOrderConfirmationSubject)) {
			return emailOrderConfirmationSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.SHOPPING_EMAIL_ORDER_CONFIRMATION_SUBJECT));
		}
	}

	public void setEmailOrderConfirmationSubject(
			String emailOrderConfirmationSubject)
		throws ReadOnlyException {

		_prefs.setValue(
			"email-order-confirmation-subject", emailOrderConfirmationSubject);
	}

	public boolean getEmailOrderShippingEnabled() {
		String emailOrderShippingEnabled = _prefs.getValue(
			"email-order-shipping-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailOrderShippingEnabled)) {
			return GetterUtil.getBoolean(emailOrderShippingEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.SHOPPING_EMAIL_ORDER_SHIPPING_ENABLED));
		}
	}

	public void setEmailOrderShippingEnabled(boolean emailOrderShippingEnabled)
		throws ReadOnlyException {

		_prefs.setValue(
			"email-order-shipping-enabled",
			String.valueOf(emailOrderShippingEnabled));
	}

	public String getEmailOrderShippingBody() throws IOException {
		String emailOrderShippingBody = _prefs.getValue(
			"email-order-shipping-body", StringPool.BLANK);

		if (Validator.isNotNull(emailOrderShippingBody)) {
			return emailOrderShippingBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.SHOPPING_EMAIL_ORDER_SHIPPING_BODY));
		}
	}

	public void setEmailOrderShippingBody(String emailOrderShippingBody)
		throws ReadOnlyException {

		_prefs.setValue("email-order-shipping-body", emailOrderShippingBody);
	}

	public String getEmailOrderShippingSubject() throws IOException {
		String emailOrderShippingSubject = _prefs.getValue(
			"email-order-shipping-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailOrderShippingSubject)) {
			return emailOrderShippingSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.SHOPPING_EMAIL_ORDER_SHIPPING_SUBJECT));
		}
	}

	public void setEmailOrderShippingSubject(String emailOrderShippingSubject)
		throws ReadOnlyException {

		_prefs.setValue(
			"email-order-shipping-subject", emailOrderShippingSubject);
	}

	public void store() throws IOException, ValidatorException {
		_prefs.store();
	}

	protected ShoppingPreferences(long companyId, long groupId)
		throws PortalException, SystemException {

		long ownerId = groupId;
		int ownerType = PortletKeys.PREFS_OWNER_TYPE_GROUP;
		long plid = PortletKeys.PREFS_PLID_SHARED;
		String portletId = PortletKeys.SHOPPING;

		_prefs = PortletPreferencesLocalServiceUtil.getPreferences(
			companyId, ownerId, ownerType, plid, portletId);
	}

	private PortletPreferences _prefs;

}
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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.CompanyLocalServiceUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portlet.admin.model.EmailConfig;
import com.liferay.portlet.admin.model.ShoppingConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.portlet.shopping.model.ShoppingCartItem;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemField;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.model.ShoppingOrderItem;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemFieldServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderItemServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderLocalService;
import com.liferay.portlet.shopping.util.ShoppingUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.mail.MailMessage;

import java.io.IOException;

import java.text.NumberFormat;

import java.util.ArrayList;
import java.util.Currency;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import javax.mail.internet.InternetAddress;

/**
 * <a href="ShoppingOrderLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class ShoppingOrderLocalServiceImpl
	implements ShoppingOrderLocalService {

	// Business methods

	public void completeOrder(
			String orderId, String ppTxnId, String ppPaymentStatus,
			double ppPaymentGross, String ppReceiverEmail, String ppPayerEmail,
			boolean updateInventory)
		throws PortalException, SystemException {

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		order.setModifiedDate(new Date());
		order.setPpTxnId(ppTxnId);
		order.setPpPaymentStatus(ppPaymentStatus);
		order.setPpPaymentGross(ppPaymentGross);
		order.setPpReceiverEmail(ppReceiverEmail);
		order.setPpPayerEmail(ppPayerEmail);

		ShoppingOrderUtil.update(order);

		// Update inventory

		if (updateInventory &&
			ppPaymentStatus.equals(ShoppingOrder.STATUS_COMPLETED)) {

			List orderItems =
				ShoppingOrderItemServiceUtil.getOrderItems(order.getOrderId());

			for (int i = 0; i < orderItems.size(); i++) {
				ShoppingOrderItem orderItem =
					(ShoppingOrderItem)orderItems.get(i);

				ShoppingItem item = ShoppingItemServiceUtil.getItemById(
					ShoppingUtil.getItemId(orderItem.getItemId()));

				if (!item.isFields()) {
					int quantity =
						item.getStockQuantity() - orderItem.getQuantity();

					item.setStockQuantity(quantity);
				}
				else {
					ShoppingItemField[] itemFields = (ShoppingItemField[])
						ShoppingItemFieldServiceUtil.getItemFields(
						item.getItemId()).toArray(new ShoppingItemField[0]);

					String[] fieldsArray = ShoppingCartItem.getFieldsArray(
						ShoppingUtil.getItemFields(orderItem.getItemId()));

					int rowPos = ShoppingUtil.getFieldsQuantitiesPos(
						item, itemFields, fieldsArray);

					String[] fieldsQuantities = item.getFieldsQuantitiesArray();

					try {
						int quantity =
							GetterUtil.getInteger(fieldsQuantities[rowPos]) -
							orderItem.getQuantity();

						fieldsQuantities[rowPos] = Integer.toString(quantity);

						item.setFieldsQuantitiesArray(fieldsQuantities);
					}
					catch (Exception e) {
					}
				}

				ShoppingItemUtil.update(item);
			}
		}

		// Send order email

		ShoppingConfig shoppingConfig =
			AdminConfigServiceUtil.getShoppingConfig(order.getCompanyId());

		if (shoppingConfig.usePayPal()) {
			sendOrderEmail(order);
		}
	}

	public void sendOrderEmail(ShoppingOrder order)
		throws PortalException, SystemException {

		sendOrderEmail(order, false);
	}

	public void sendOrderEmail(ShoppingOrder order, boolean override)
		throws PortalException, SystemException {

		ShoppingConfig shoppingConfig =
			AdminConfigServiceUtil.getShoppingConfig(order.getCompanyId());

		EmailConfig orderEmail = shoppingConfig.getOrderEmail();

		if (override || (order.isSendOrderEmail() && orderEmail.isSend())) {
			List orderItems =
				ShoppingOrderItemServiceUtil.getOrderItems(order.getOrderId());

			Set supplierUserIds = ShoppingUtil.getSupplierUserIds(orderItems);

			Iterator itr = supplierUserIds.iterator();

			while (itr.hasNext()) {
				String supplierUserId = (String)itr.next();

				_sendEmail(
					order, orderItems, supplierUserId, shoppingConfig,
					orderEmail);
			}

			_sendEmail(order, orderItems, null, shoppingConfig, orderEmail);

			order.setModifiedDate(new Date());
			order.setSendOrderEmail(false);

			ShoppingOrderUtil.update(order);
		}
	}

	public void sendShippingEmail(ShoppingOrder order)
		throws PortalException, SystemException {

		sendShippingEmail(order, false);
	}

	public void sendShippingEmail(ShoppingOrder order, boolean override)
		throws PortalException, SystemException {

		ShoppingConfig shoppingConfig =
			AdminConfigServiceUtil.getShoppingConfig(order.getCompanyId());

		EmailConfig shippingEmail = shoppingConfig.getShippingEmail();

		if (override ||
			(order.isSendShippingEmail() && shippingEmail.isSend())) {

			List orderItems =
				ShoppingOrderItemServiceUtil.getOrderItems(order.getOrderId());

			Set supplierUserIds = ShoppingUtil.getSupplierUserIds(orderItems);

			Iterator itr = supplierUserIds.iterator();

			while (itr.hasNext()) {
				String supplierUserId = (String)itr.next();

				_sendEmail(
					order, orderItems, supplierUserId, shoppingConfig,
					shippingEmail);
			}

			_sendEmail(order, orderItems, null, shoppingConfig, shippingEmail);

			order.setModifiedDate(new Date());
			order.setSendShippingEmail(false);

			ShoppingOrderUtil.update(order);
		}
	}

	// Private methods

	private void _sendEmail(
			ShoppingOrder order, List orderItems, String supplierUserId,
			ShoppingConfig shoppingConfig, EmailConfig email)
		throws PortalException, SystemException {

		Company company =
			CompanyLocalServiceUtil.getCompany(order.getCompanyId());

		User user = UserLocalServiceUtil.getUserById(order.getUserId());

		Currency currency =
			Currency.getInstance(shoppingConfig.getCurrencyId());

		NumberFormat doubleFormat =
			NumberFormat.getNumberInstance(user.getLocale());
		doubleFormat.setMaximumFractionDigits(2);
		doubleFormat.setMinimumFractionDigits(2);

		String orderNumber = order.getOrderId();

		String orderSummary =
			LanguageUtil.get(user, "billing-address").toUpperCase() + ":\n" +
			order.getBillingFirstName() + " " + order.getBillingLastName() +
				"\n" +
			order.getBillingEmailAddress() + "\n" +
			order.getBillingStreet() + "\n" +
			order.getBillingCity() + "\n" +
			order.getBillingState() + "\n" +
			order.getBillingZip() + "\n" +
			order.getBillingCountry() + "\n" +
			order.getBillingPhone() + "\n" +
			"\n" +
			LanguageUtil.get(user, "shipping-address").toUpperCase() + ":\n" +
			order.getShippingFirstName() + " " +
				order.getShippingLastName() + "\n" +
			order.getShippingEmailAddress() + "\n" +
			order.getShippingStreet() + "\n" +
			order.getShippingCity() + "\n" +
			order.getShippingState() + "\n" +
			order.getShippingZip() + "\n" +
			order.getShippingCountry() + "\n" +
			order.getShippingPhone() + "\n" +
			"\n";

		User supplier = null;
		if (supplierUserId != null) {
			supplier = UserLocalServiceUtil.getUserById(supplierUserId);
		}

		List orderSupplierItems = new ArrayList();

		for (int i = 0; i < orderItems.size(); i++) {
			ShoppingOrderItem orderItem =
				(ShoppingOrderItem)orderItems.get(i);

			if ((supplierUserId == null) ||
				(supplierUserId.equals(
					orderItem.getSupplierUserId()))) {

				orderSupplierItems.add(orderItem);
			}
		}

		for (int i = 0; i < orderSupplierItems.size(); i++) {
			ShoppingOrderItem orderItem =
				(ShoppingOrderItem)orderSupplierItems.get(i);

			ShoppingItem item = ShoppingItemServiceUtil.getItemById(
				ShoppingUtil.getItemId(orderItem.getItemId()));
			int quantity = orderItem.getQuantity();

			String skuText = LanguageUtil.get(user, "sku");
			String itemNameText = LanguageUtil.get(user, "item-name");
			String itemDescriptionText = LanguageUtil.get(
				user, "item-description");
			String quantityText = LanguageUtil.get(user, "quantity");
			String priceText = LanguageUtil.get(user, "price");
			String itemTotalText = LanguageUtil.get(user, "item-total");

			orderSummary +=
				skuText + ": " + item.getSku() + "\n" +
				itemNameText + ": " + item.getName() + "\n" +
				itemDescriptionText + ": " + item.getDescription() + "\n" +
				quantityText + ": " + quantity + "\n" +
				priceText + ": " + currency.getSymbol() +
					doubleFormat.format(orderItem.getPrice()) + "\n" +
				itemTotalText + currency.getSymbol() +
					doubleFormat.format(orderItem.getPrice() * quantity) +
					"\n";

			if (Validator.isNotNull(orderItem.getSupplierUserId())) {
				User orderItemSupplier = UserLocalServiceUtil.getUserById(
					orderItem.getSupplierUserId());

				orderSummary += " [" + orderItemSupplier.getFullName() + "]\n";
			}

			orderSummary += "\n";
		}

		String totalText = LanguageUtil.get(user, "total");

		double total = 0.0;

		if (supplierUserId == null) {
			total = ShoppingUtil.calculateTotal(order);
		}
		else {
			total = ShoppingUtil.calculateActualSubtotal(orderSupplierItems);
		}

		orderSummary +=
			totalText + ": " + currency.getSymbol() +
			doubleFormat.format(total) + "\n";

		String subject = email.getSubject();
		subject = StringUtil.replace(
			subject,
			new String[] {"[$ADMIN_EMAIL_ADDRESS$]", "[$ADMIN_NAME$]",
						  "[$COMPANY_NAME$]",
						  "[$ORDER_NUMBER$]", "[$ORDER_SUMMARY$]",
						  "[$PORTAL_URL$]",
						  "[$USER_EMAIL_ADDRESS$]", "[$USER_NAME$]"},
			new String[] {company.getEmailAddress(), company.getAdminName(),
						  company.getName(),
						  orderNumber, orderSummary,
						  company.getPortalURL(),
						  user.getEmailAddress(), user.getFullName()});

		if (supplier != null) {
			subject += " [" + supplier.getFullName() + "]";
		}

		String body = email.getBody();
		body = StringUtil.replace(
			body,
			new String[] {"[$ADMIN_EMAIL_ADDRESS$]", "[$ADMIN_NAME$]",
						  "[$COMPANY_NAME$]",
						  "[$ORDER_NUMBER$]", "[$ORDER_SUMMARY$]",
						  "[$PORTAL_URL$]",
						  "[$USER_EMAIL_ADDRESS$]", "[$USER_NAME$]"},
			new String[] {company.getEmailAddress(), company.getAdminName(),
						  company.getName(),
						  orderNumber, orderSummary,
						  company.getPortalURL(),
						  user.getEmailAddress(), user.getFullName()});

		try {
			InternetAddress from = new InternetAddress(
				company.getEmailAddress(), company.getAdminName());

			InternetAddress[] to = new InternetAddress[1];
			if (supplier == null) {
				to[0] = new InternetAddress(
					user.getEmailAddress(), user.getFullName());
			}
			else {
				to[0] = new InternetAddress(
					supplier.getEmailAddress(), supplier.getFullName());
			}

			InternetAddress[] cc = null;

			Role shoppingAdminRole = RoleLocalServiceUtil.getRoleByName(
				company.getCompanyId(), Role.SHOPPING_ADMIN);

			List users = RoleLocalServiceUtil.getUsers(
				shoppingAdminRole.getRoleId());

			InternetAddress[] bcc = new InternetAddress[users.size()];

			for (int i = 0; i < users.size(); i++) {
				User shoppingAdminUser = (User)users.get(i);

				bcc[i] = new InternetAddress(
					shoppingAdminUser.getEmailAddress(),
					shoppingAdminUser.getFullName());
			}

			MailServiceUtil.sendEmail(new MailMessage(
				from, to, cc, bcc, subject, body));
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

}
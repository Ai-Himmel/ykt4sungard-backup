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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Note;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.NoteLocalServiceUtil;
import com.liferay.portal.service.spring.RoleServiceUtil;
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
import com.liferay.portlet.shopping.CartMinOrderException;
import com.liferay.portlet.shopping.NoSuchOrderException;
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
import com.liferay.portlet.shopping.model.ShoppingCartItem;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.model.ShoppingOrderItem;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPK;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCategoryServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderLocalServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderService;
import com.liferay.portlet.shopping.util.OrderDateComparator;
import com.liferay.portlet.shopping.util.ShoppingUtil;
import com.liferay.util.CreditCard;
import com.liferay.util.PwdGenerator;
import com.liferay.util.Validator;
import com.liferay.util.cal.CalendarUtil;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 * <a href="ShoppingOrderServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class ShoppingOrderServiceImpl
	extends PrincipalBean implements ShoppingOrderService {

	// Business methods

	public void addNote(String orderId, String noteContent)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		NoteLocalServiceUtil.addNote(
			getUserId(), ShoppingOrder.class.getName(), orderId, noteContent);
	}

	public void completeOrder(
			String orderId, String ppTxnId, String ppPaymentStatus,
			double ppPaymentGross, String ppReceiverEmail, String ppPayerEmail)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		ShoppingOrderLocalServiceUtil.completeOrder(
			orderId, ppTxnId, ppPaymentStatus, ppPaymentGross, ppReceiverEmail,
			ppPayerEmail, false);
	}

	public void deleteNote(String orderId, String noteId)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		Note note = NoteLocalServiceUtil.getNote(noteId);

		if (note.getClassPK().equals(orderId)) {
			NoteLocalServiceUtil.deleteNote(noteId);
		}
	}

	public void deleteOrder(String orderId)
		throws PortalException, SystemException {

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		deleteOrder(order);
	}

	public void deleteOrder(ShoppingOrder order)
		throws PortalException, SystemException {

		String orderId = order.getPrimaryKey();

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		// Remove order notes

		NoteLocalServiceUtil.deleteNotes(
			order.getCompanyId(), ShoppingOrder.class.getName(), orderId);

		// Remove order items

		ShoppingOrderItemUtil.removeByOrderId(orderId);

		// Remove order

		ShoppingOrderUtil.remove(orderId);
	}

	public ShoppingOrder getLatestOrder()
		throws PortalException, SystemException {

		User user = getUser();

		List orders = ShoppingOrderUtil.findByU_PPPS(
			getUserId(), ShoppingOrder.STATUS_LATEST);

		ShoppingOrder order = null;

		if (orders.size() == 0) {
			List pastOrders = ShoppingOrderUtil.findByU_PPPS(
				getUserId(), ShoppingOrder.STATUS_CHECKOUT);

			if (pastOrders.size() > 0) {
				ShoppingOrder pastOrder =
					(ShoppingOrder)pastOrders.iterator().next();

				order = (ShoppingOrder)pastOrder.clone();
			}

			String orderId = _getOrderId();

			if (order == null) {
				order = ShoppingOrderUtil.create(orderId);
			}
			else {
				order.setOrderId(orderId);
			}

			Date now = new Date();

			order.setCompanyId(user.getCompanyId());
			order.setUserId(user.getUserId());
			order.setCreateDate(now);
			order.setModifiedDate(now);
			order.setPpPaymentStatus(ShoppingOrder.STATUS_LATEST);
			order.setSendOrderEmail(true);
			order.setSendShippingEmail(true);

			ShoppingOrderUtil.update(order);
		}
		else {
			order = (ShoppingOrder)orders.iterator().next();
		}

		return order;
	}

	public List getNotes(String orderId)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		return NoteLocalServiceUtil.getNotes(
			getUser().getCompanyId(), ShoppingOrder.class.getName(), orderId);
	}

	public ShoppingOrder getOrder(String orderId)
		throws PortalException, SystemException {

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		if (!order.getUserId().equals(getUserId()) && !hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		return order;
	}

	public List getOrders(String ppPaymentStatus)
		throws PortalException, SystemException {

		List list = null;

		if (Validator.isNull(ppPaymentStatus)) {
			list = ShoppingOrderUtil.findByUserId(getUserId());
		}
		else {
			list = ShoppingOrderUtil.findByU_PPPS(
				getUserId(), ShoppingUtil.getPpPaymentStatus(ppPaymentStatus));
		}

		return list;
	}

	public List getOrders(String ppPaymentStatus, int begin, int end)
		throws PortalException, SystemException {

		List list = null;

		if (Validator.isNull(ppPaymentStatus)) {
			list = ShoppingOrderUtil.findByUserId(
				getUserId(), begin, end, new OrderDateComparator(false));
		}
		else {
			list = ShoppingOrderUtil.findByU_PPPS(
				getUserId(), ShoppingUtil.getPpPaymentStatus(ppPaymentStatus),
				begin, end, new OrderDateComparator(false));
		}

		return list;
	}

	public List getOrders(String companyId, String ppPaymentStatus)
		throws PortalException, SystemException {

		if (!ShoppingCategoryServiceUtil.hasAdmin() ||
			!getUser().getCompanyId().equals(companyId)) {

			throw new PrincipalException();
		}

		List list = null;

		if (Validator.isNull(ppPaymentStatus)) {
			list = ShoppingOrderUtil.findByCompanyId(companyId);
		}
		else {
			list = ShoppingOrderUtil.findByC_PPPS(
				companyId, ShoppingUtil.getPpPaymentStatus(ppPaymentStatus));
		}

		return list;
	}

	public List getOrders(
			String companyId, String ppPaymentStatus, int begin, int end)
		throws PortalException, SystemException {

		if (!ShoppingCategoryServiceUtil.hasAdmin() ||
			!getUser().getCompanyId().equals(companyId)) {

			throw new PrincipalException();
		}

		List list = null;

		if (Validator.isNull(ppPaymentStatus)) {
			list = ShoppingOrderUtil.findByCompanyId(
				companyId, begin, end, new OrderDateComparator(false));
		}
		else {
			list = ShoppingOrderUtil.findByC_PPPS(
				companyId, ShoppingUtil.getPpPaymentStatus(ppPaymentStatus),
				begin, end, new OrderDateComparator(false));
		}

		return list;
	}

	public int getOrdersSize(String ppPaymentStatus)
		throws PortalException, SystemException {

		int count = 0;

		if (Validator.isNull(ppPaymentStatus)) {
			count = ShoppingOrderUtil.countByUserId(getUserId());
		}
		else {
			count = ShoppingOrderUtil.countByU_PPPS(
				getUserId(), ShoppingUtil.getPpPaymentStatus(ppPaymentStatus));
		}

		return count;
	}

	public int getOrdersSize(String companyId, String ppPaymentStatus)
		throws SystemException {

		int count = 0;

		if (Validator.isNull(ppPaymentStatus)) {
			count = ShoppingOrderUtil.countByCompanyId(companyId);
		}
		else {
			count = ShoppingOrderUtil.countByC_PPPS(
				companyId, ShoppingUtil.getPpPaymentStatus(ppPaymentStatus));
		}

		return count;
	}

	public ShoppingOrder saveLatestOrder(ShoppingCart cart)
		throws PortalException, SystemException {

		Map items = cart.getItems();

		ShoppingOrder order = getLatestOrder();

		ShoppingConfig shoppingConfig =
			AdminConfigServiceUtil.getShoppingConfig(order.getCompanyId());

		if (!ShoppingUtil.meetsMinOrder(shoppingConfig, items)) {
			throw new CartMinOrderException();
		}

		Date now = new Date();

		order.setCreateDate(now);
		order.setModifiedDate(now);
		order.setPpPaymentStatus(ShoppingOrder.STATUS_CHECKOUT);

		ShoppingOrderUtil.update(order);

		boolean requiresShipping = false;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			if (item.isRequiresShipping()) {
				requiresShipping = true;
			}

			ShoppingOrderItemPK orderItemPK = new ShoppingOrderItemPK(
				order.getOrderId(), cartItem.getCartItemId());

			ShoppingOrderItem orderItem =
				ShoppingOrderItemUtil.create(orderItemPK);

			orderItem.setSku(item.getSku());
			orderItem.setName(item.getName());
			orderItem.setDescription(item.getDescription());
			orderItem.setProperties(item.getProperties());
			orderItem.setSupplierUserId(item.getSupplierUserId());
			orderItem.setPrice(
				ShoppingUtil.calculateActualPrice(item, count.intValue()) /
					count.intValue());
			orderItem.setQuantity(count.intValue());

			ShoppingOrderItemUtil.update(orderItem);
		}

		order.setModifiedDate(new Date());
		order.setTax(
			ShoppingUtil.calculateTax(items, order.getBillingState()));
		order.setShipping(
			ShoppingUtil.calculateAlternativeShipping(
				items, cart.getAltShipping()));
		order.setAltShipping(
			shoppingConfig.getAlternativeShippingName(cart.getAltShipping()));
		order.setRequiresShipping(requiresShipping);
		order.setInsure(cart.isInsure());
		order.setInsurance(ShoppingUtil.calculateInsurance(items));
		order.setCouponIds(cart.getCouponIds());
		order.setCouponDiscount(
			ShoppingUtil.calculateCouponDiscount(
				items, order.getBillingState(), cart.getCoupon()));
		order.setSendOrderEmail(true);
		order.setSendShippingEmail(true);

		ShoppingOrderUtil.update(order);

		return order;
	}

	public void sendOrderEmail(String orderId)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		ShoppingOrderLocalServiceUtil.sendOrderEmail(order, true);
	}

	public void sendShippingEmail(String orderId)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		ShoppingOrderLocalServiceUtil.sendShippingEmail(order, true);
	}

	public ShoppingOrder updateLatestOrder(
			String billingFirstName, String billingLastName,
			String billingEmailAddress, String billingCompany,
			String billingStreet, String billingCity, String billingState,
			String billingZip, String billingCountry, String billingPhone,
			boolean shipToBilling, String shippingFirstName,
			String shippingLastName, String shippingEmailAddress,
			String shippingCompany, String shippingStreet, String shippingCity,
			String shippingState, String shippingZip, String shippingCountry,
			String shippingPhone, String ccName, String ccType, String ccNumber,
			int ccExpMonth, int ccExpYear, String ccVerNumber, String comments)
		throws PortalException, SystemException {

		return updateOrder(
			getLatestOrder().getOrderId(), billingFirstName, billingLastName,
			billingEmailAddress, billingCompany, billingStreet, billingCity,
			billingState, billingZip, billingCountry, billingPhone,
			shipToBilling, shippingFirstName, shippingLastName,
			shippingEmailAddress, shippingCompany, shippingStreet, shippingCity,
			shippingState, shippingZip, shippingCountry, shippingPhone,
			ccName, ccType, ccNumber, ccExpMonth, ccExpYear, ccVerNumber,
			comments);
	}

	public ShoppingOrder updateOrder(
			String orderId, String billingFirstName, String billingLastName,
			String billingEmailAddress, String billingCompany,
			String billingStreet, String billingCity, String billingState,
			String billingZip, String billingCountry, String billingPhone,
			boolean shipToBilling, String shippingFirstName,
			String shippingLastName, String shippingEmailAddress,
			String shippingCompany, String shippingStreet, String shippingCity,
			String shippingState, String shippingZip, String shippingCountry,
			String shippingPhone, String ccName, String ccType, String ccNumber,
			int ccExpMonth, int ccExpYear, String ccVerNumber, String comments)
		throws PortalException, SystemException {

		User user = getUser();

		ShoppingConfig shoppingConfig =
			AdminConfigServiceUtil.getShoppingConfig(user.getCompanyId());

		_validate(
			shoppingConfig, billingFirstName, billingLastName,
			billingEmailAddress, billingStreet, billingCity, billingState,
			billingZip, billingCountry, billingPhone, shipToBilling,
			shippingFirstName, shippingLastName, shippingEmailAddress,
			shippingStreet, shippingCity, shippingState, shippingZip,
			shippingCountry, shippingPhone, ccName, ccType, ccNumber,
			ccExpMonth, ccExpYear, ccVerNumber);

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		if (!order.getUserId().equals(getUserId()) && !hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		order.setModifiedDate(new Date());

		order.setBillingFirstName(billingFirstName);
		order.setBillingLastName(billingLastName);
		order.setBillingEmailAddress(billingEmailAddress);
		order.setBillingCompany(billingCompany);
		order.setBillingStreet(billingStreet);
		order.setBillingCity(billingCity);
		order.setBillingState(billingState);
		order.setBillingZip(billingZip);
		order.setBillingCountry(billingCountry);
		order.setBillingPhone(billingPhone);
		order.setShipToBilling(shipToBilling);

		if (shipToBilling) {
			order.setShippingFirstName(billingFirstName);
			order.setShippingLastName(billingLastName);
			order.setShippingEmailAddress(billingEmailAddress);
			order.setShippingCompany(billingCompany);
			order.setShippingStreet(billingStreet);
			order.setShippingCity(billingCity);
			order.setShippingState(billingState);
			order.setShippingZip(billingZip);
			order.setShippingCountry(billingCountry);
			order.setShippingPhone(billingPhone);
		}
		else {
			order.setShippingFirstName(shippingFirstName);
			order.setShippingLastName(shippingLastName);
			order.setShippingEmailAddress(shippingEmailAddress);
			order.setShippingCompany(shippingCompany);
			order.setShippingStreet(shippingStreet);
			order.setShippingCity(shippingCity);
			order.setShippingState(shippingState);
			order.setShippingZip(shippingZip);
			order.setShippingCountry(shippingCountry);
			order.setShippingPhone(shippingPhone);
		}

		order.setCcName(ccName);
		order.setCcType(ccType);
		order.setCcNumber(ccNumber);
		order.setCcExpMonth(ccExpMonth);
		order.setCcExpYear(ccExpYear);
		order.setCcVerNumber(ccVerNumber);

		order.setComments(comments);

		ShoppingOrderUtil.update(order);

		return order;
	}

	public ShoppingOrder updateOrder(
			String orderId, String ppTxnId, String ppPaymentStatus,
			double ppPaymentGross, String ppReceiverEmail, String ppPayerEmail)
		throws PortalException, SystemException {

		if (!hasAdmin(orderId)) {
			throw new PrincipalException();
		}

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		order.setModifiedDate(new Date());
		order.setPpTxnId(ppTxnId);
		order.setPpPaymentStatus(ppPaymentStatus);
		order.setPpPaymentGross(ppPaymentGross);
		order.setPpReceiverEmail(ppReceiverEmail);
		order.setPpPayerEmail(ppPayerEmail);

		ShoppingOrderUtil.update(order);

		return order;
	}

	// Permission methods

	public boolean hasAdmin(String orderId)
		throws PortalException, SystemException {

		ShoppingOrder order = ShoppingOrderUtil.findByPrimaryKey(orderId);

		if (getUser().getCompanyId().equals(order.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.SHOPPING_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private String _getOrderId() throws SystemException {
		String orderId =
			PwdGenerator.getPassword(PwdGenerator.KEY1 + PwdGenerator.KEY2, 12);

		try {
			ShoppingOrderUtil.findByPrimaryKey(orderId);

			return _getOrderId();
		}
		catch (NoSuchOrderException nsoe) {
			return orderId;
		}
	}

	private void _validate(
			ShoppingConfig shoppingConfig, String billingFirstName,
			String billingLastName, String billingEmailAddress,
			String billingStreet, String billingCity, String billingState,
			String billingZip, String billingCountry, String billingPhone,
			boolean shipToBilling, String shippingFirstName,
			String shippingLastName, String shippingEmailAddress,
			String shippingStreet, String shippingCity, String shippingState,
			String shippingZip, String shippingCountry, String shippingPhone,
			String ccName, String ccType, String ccNumber, int ccExpMonth,
			int ccExpYear, String ccVerNumber)
		throws PortalException {

		if (Validator.isNull(billingFirstName)) {
			throw new BillingFirstNameException();
		}
		else if (Validator.isNull(billingLastName)) {
			throw new BillingLastNameException();
		}
		else if (!Validator.isEmailAddress(billingEmailAddress)) {
			throw new BillingEmailAddressException();
		}
		else if (Validator.isNull(billingStreet)) {
			throw new BillingStreetException();
		}
		else if (Validator.isNull(billingCity)) {
			throw new BillingCityException();
		}
		else if (Validator.isNull(billingState)) {
			throw new BillingStateException();
		}
		else if (Validator.isNull(billingZip)) {
			throw new BillingZipException();
		}
		else if (Validator.isNull(billingCountry)) {
			throw new BillingCountryException();
		}
		else if (Validator.isNull(billingPhone)) {
			throw new BillingPhoneException();
		}

		if (!shipToBilling) {
			if (Validator.isNull(shippingFirstName)) {
				throw new ShippingFirstNameException();
			}
			else if (Validator.isNull(shippingLastName)) {
				throw new ShippingLastNameException();
			}
			else if (!Validator.isEmailAddress(shippingEmailAddress)) {
				throw new ShippingEmailAddressException();
			}
			else if (Validator.isNull(shippingStreet)) {
				throw new ShippingStreetException();
			}
			else if (Validator.isNull(shippingCity)) {
				throw new ShippingCityException();
			}
			else if (Validator.isNull(shippingState)) {
				throw new ShippingStateException();
			}
			else if (Validator.isNull(shippingZip)) {
				throw new ShippingZipException();
			}
			else if (Validator.isNull(shippingCountry)) {
				throw new ShippingCountryException();
			}
			else if (Validator.isNull(shippingPhone)) {
				throw new ShippingPhoneException();
			}
		}

		if (!shoppingConfig.usePayPal() &&
			(shoppingConfig.getCcTypes().length > 0)) {

			if (Validator.isNull(ccName)) {
				throw new CCNameException();
			}
			else if (Validator.isNull(ccType)) {
				throw new CCTypeException();
			}
			else if (!CreditCard.isValid(ccNumber, ccType)) {
				throw new CCNumberException();
			}
			else if (!CalendarUtil.isFuture(ccExpMonth, ccExpYear)) {
				throw new CCExpirationException();
			}
		}
	}

}
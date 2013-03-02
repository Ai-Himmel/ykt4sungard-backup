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

package com.liferay.portlet.shopping.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.mail.service.MailService;
import com.liferay.mail.service.MailServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.service.CompanyLocalService;
import com.liferay.portal.service.CompanyLocalServiceFactory;
import com.liferay.portal.service.CompanyService;
import com.liferay.portal.service.CompanyServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.persistence.CompanyPersistence;
import com.liferay.portal.service.persistence.CompanyUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.messageboards.service.MBMessageLocalService;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBMessageService;
import com.liferay.portlet.messageboards.service.MBMessageServiceFactory;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinder;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.model.impl.ShoppingOrderImpl;
import com.liferay.portlet.shopping.service.ShoppingCartLocalService;
import com.liferay.portlet.shopping.service.ShoppingCartLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalService;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCategoryService;
import com.liferay.portlet.shopping.service.ShoppingCategoryServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCouponLocalService;
import com.liferay.portlet.shopping.service.ShoppingCouponLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingCouponService;
import com.liferay.portlet.shopping.service.ShoppingCouponServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingItemFieldLocalService;
import com.liferay.portlet.shopping.service.ShoppingItemFieldLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingItemLocalService;
import com.liferay.portlet.shopping.service.ShoppingItemLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingItemPriceLocalService;
import com.liferay.portlet.shopping.service.ShoppingItemPriceLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingItemService;
import com.liferay.portlet.shopping.service.ShoppingItemServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingOrderItemLocalService;
import com.liferay.portlet.shopping.service.ShoppingOrderItemLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingOrderLocalService;
import com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingCartUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinderUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemFinderUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinderUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence;
import com.liferay.portlet.shopping.service.persistence.ShoppingOrderUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="ShoppingOrderLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class ShoppingOrderLocalServiceBaseImpl
	implements ShoppingOrderLocalService, InitializingBean {
	public ShoppingOrder addShoppingOrder(ShoppingOrder model)
		throws SystemException {
		ShoppingOrder shoppingOrder = new ShoppingOrderImpl();

		shoppingOrder.setNew(true);

		shoppingOrder.setOrderId(model.getOrderId());
		shoppingOrder.setGroupId(model.getGroupId());
		shoppingOrder.setCompanyId(model.getCompanyId());
		shoppingOrder.setUserId(model.getUserId());
		shoppingOrder.setUserName(model.getUserName());
		shoppingOrder.setCreateDate(model.getCreateDate());
		shoppingOrder.setModifiedDate(model.getModifiedDate());
		shoppingOrder.setNumber(model.getNumber());
		shoppingOrder.setTax(model.getTax());
		shoppingOrder.setShipping(model.getShipping());
		shoppingOrder.setAltShipping(model.getAltShipping());
		shoppingOrder.setRequiresShipping(model.getRequiresShipping());
		shoppingOrder.setInsure(model.getInsure());
		shoppingOrder.setInsurance(model.getInsurance());
		shoppingOrder.setCouponCodes(model.getCouponCodes());
		shoppingOrder.setCouponDiscount(model.getCouponDiscount());
		shoppingOrder.setBillingFirstName(model.getBillingFirstName());
		shoppingOrder.setBillingLastName(model.getBillingLastName());
		shoppingOrder.setBillingEmailAddress(model.getBillingEmailAddress());
		shoppingOrder.setBillingCompany(model.getBillingCompany());
		shoppingOrder.setBillingStreet(model.getBillingStreet());
		shoppingOrder.setBillingCity(model.getBillingCity());
		shoppingOrder.setBillingState(model.getBillingState());
		shoppingOrder.setBillingZip(model.getBillingZip());
		shoppingOrder.setBillingCountry(model.getBillingCountry());
		shoppingOrder.setBillingPhone(model.getBillingPhone());
		shoppingOrder.setShipToBilling(model.getShipToBilling());
		shoppingOrder.setShippingFirstName(model.getShippingFirstName());
		shoppingOrder.setShippingLastName(model.getShippingLastName());
		shoppingOrder.setShippingEmailAddress(model.getShippingEmailAddress());
		shoppingOrder.setShippingCompany(model.getShippingCompany());
		shoppingOrder.setShippingStreet(model.getShippingStreet());
		shoppingOrder.setShippingCity(model.getShippingCity());
		shoppingOrder.setShippingState(model.getShippingState());
		shoppingOrder.setShippingZip(model.getShippingZip());
		shoppingOrder.setShippingCountry(model.getShippingCountry());
		shoppingOrder.setShippingPhone(model.getShippingPhone());
		shoppingOrder.setCcName(model.getCcName());
		shoppingOrder.setCcType(model.getCcType());
		shoppingOrder.setCcNumber(model.getCcNumber());
		shoppingOrder.setCcExpMonth(model.getCcExpMonth());
		shoppingOrder.setCcExpYear(model.getCcExpYear());
		shoppingOrder.setCcVerNumber(model.getCcVerNumber());
		shoppingOrder.setComments(model.getComments());
		shoppingOrder.setPpTxnId(model.getPpTxnId());
		shoppingOrder.setPpPaymentStatus(model.getPpPaymentStatus());
		shoppingOrder.setPpPaymentGross(model.getPpPaymentGross());
		shoppingOrder.setPpReceiverEmail(model.getPpReceiverEmail());
		shoppingOrder.setPpPayerEmail(model.getPpPayerEmail());
		shoppingOrder.setSendOrderEmail(model.getSendOrderEmail());
		shoppingOrder.setSendShippingEmail(model.getSendShippingEmail());

		return shoppingOrderPersistence.update(shoppingOrder);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return shoppingOrderPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return shoppingOrderPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public ShoppingOrder updateShoppingOrder(ShoppingOrder model)
		throws SystemException {
		ShoppingOrder shoppingOrder = new ShoppingOrderImpl();

		shoppingOrder.setNew(false);

		shoppingOrder.setOrderId(model.getOrderId());
		shoppingOrder.setGroupId(model.getGroupId());
		shoppingOrder.setCompanyId(model.getCompanyId());
		shoppingOrder.setUserId(model.getUserId());
		shoppingOrder.setUserName(model.getUserName());
		shoppingOrder.setCreateDate(model.getCreateDate());
		shoppingOrder.setModifiedDate(model.getModifiedDate());
		shoppingOrder.setNumber(model.getNumber());
		shoppingOrder.setTax(model.getTax());
		shoppingOrder.setShipping(model.getShipping());
		shoppingOrder.setAltShipping(model.getAltShipping());
		shoppingOrder.setRequiresShipping(model.getRequiresShipping());
		shoppingOrder.setInsure(model.getInsure());
		shoppingOrder.setInsurance(model.getInsurance());
		shoppingOrder.setCouponCodes(model.getCouponCodes());
		shoppingOrder.setCouponDiscount(model.getCouponDiscount());
		shoppingOrder.setBillingFirstName(model.getBillingFirstName());
		shoppingOrder.setBillingLastName(model.getBillingLastName());
		shoppingOrder.setBillingEmailAddress(model.getBillingEmailAddress());
		shoppingOrder.setBillingCompany(model.getBillingCompany());
		shoppingOrder.setBillingStreet(model.getBillingStreet());
		shoppingOrder.setBillingCity(model.getBillingCity());
		shoppingOrder.setBillingState(model.getBillingState());
		shoppingOrder.setBillingZip(model.getBillingZip());
		shoppingOrder.setBillingCountry(model.getBillingCountry());
		shoppingOrder.setBillingPhone(model.getBillingPhone());
		shoppingOrder.setShipToBilling(model.getShipToBilling());
		shoppingOrder.setShippingFirstName(model.getShippingFirstName());
		shoppingOrder.setShippingLastName(model.getShippingLastName());
		shoppingOrder.setShippingEmailAddress(model.getShippingEmailAddress());
		shoppingOrder.setShippingCompany(model.getShippingCompany());
		shoppingOrder.setShippingStreet(model.getShippingStreet());
		shoppingOrder.setShippingCity(model.getShippingCity());
		shoppingOrder.setShippingState(model.getShippingState());
		shoppingOrder.setShippingZip(model.getShippingZip());
		shoppingOrder.setShippingCountry(model.getShippingCountry());
		shoppingOrder.setShippingPhone(model.getShippingPhone());
		shoppingOrder.setCcName(model.getCcName());
		shoppingOrder.setCcType(model.getCcType());
		shoppingOrder.setCcNumber(model.getCcNumber());
		shoppingOrder.setCcExpMonth(model.getCcExpMonth());
		shoppingOrder.setCcExpYear(model.getCcExpYear());
		shoppingOrder.setCcVerNumber(model.getCcVerNumber());
		shoppingOrder.setComments(model.getComments());
		shoppingOrder.setPpTxnId(model.getPpTxnId());
		shoppingOrder.setPpPaymentStatus(model.getPpPaymentStatus());
		shoppingOrder.setPpPaymentGross(model.getPpPaymentGross());
		shoppingOrder.setPpReceiverEmail(model.getPpReceiverEmail());
		shoppingOrder.setPpPayerEmail(model.getPpPayerEmail());
		shoppingOrder.setSendOrderEmail(model.getSendOrderEmail());
		shoppingOrder.setSendShippingEmail(model.getSendShippingEmail());

		return shoppingOrderPersistence.update(shoppingOrder);
	}

	public ShoppingCartLocalService getShoppingCartLocalService() {
		return shoppingCartLocalService;
	}

	public void setShoppingCartLocalService(
		ShoppingCartLocalService shoppingCartLocalService) {
		this.shoppingCartLocalService = shoppingCartLocalService;
	}

	public ShoppingCartPersistence getShoppingCartPersistence() {
		return shoppingCartPersistence;
	}

	public void setShoppingCartPersistence(
		ShoppingCartPersistence shoppingCartPersistence) {
		this.shoppingCartPersistence = shoppingCartPersistence;
	}

	public ShoppingCategoryLocalService getShoppingCategoryLocalService() {
		return shoppingCategoryLocalService;
	}

	public void setShoppingCategoryLocalService(
		ShoppingCategoryLocalService shoppingCategoryLocalService) {
		this.shoppingCategoryLocalService = shoppingCategoryLocalService;
	}

	public ShoppingCategoryService getShoppingCategoryService() {
		return shoppingCategoryService;
	}

	public void setShoppingCategoryService(
		ShoppingCategoryService shoppingCategoryService) {
		this.shoppingCategoryService = shoppingCategoryService;
	}

	public ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		return shoppingCategoryPersistence;
	}

	public void setShoppingCategoryPersistence(
		ShoppingCategoryPersistence shoppingCategoryPersistence) {
		this.shoppingCategoryPersistence = shoppingCategoryPersistence;
	}

	public ShoppingCouponLocalService getShoppingCouponLocalService() {
		return shoppingCouponLocalService;
	}

	public void setShoppingCouponLocalService(
		ShoppingCouponLocalService shoppingCouponLocalService) {
		this.shoppingCouponLocalService = shoppingCouponLocalService;
	}

	public ShoppingCouponService getShoppingCouponService() {
		return shoppingCouponService;
	}

	public void setShoppingCouponService(
		ShoppingCouponService shoppingCouponService) {
		this.shoppingCouponService = shoppingCouponService;
	}

	public ShoppingCouponPersistence getShoppingCouponPersistence() {
		return shoppingCouponPersistence;
	}

	public void setShoppingCouponPersistence(
		ShoppingCouponPersistence shoppingCouponPersistence) {
		this.shoppingCouponPersistence = shoppingCouponPersistence;
	}

	public ShoppingCouponFinder getShoppingCouponFinder() {
		return shoppingCouponFinder;
	}

	public void setShoppingCouponFinder(
		ShoppingCouponFinder shoppingCouponFinder) {
		this.shoppingCouponFinder = shoppingCouponFinder;
	}

	public ShoppingItemLocalService getShoppingItemLocalService() {
		return shoppingItemLocalService;
	}

	public void setShoppingItemLocalService(
		ShoppingItemLocalService shoppingItemLocalService) {
		this.shoppingItemLocalService = shoppingItemLocalService;
	}

	public ShoppingItemService getShoppingItemService() {
		return shoppingItemService;
	}

	public void setShoppingItemService(ShoppingItemService shoppingItemService) {
		this.shoppingItemService = shoppingItemService;
	}

	public ShoppingItemPersistence getShoppingItemPersistence() {
		return shoppingItemPersistence;
	}

	public void setShoppingItemPersistence(
		ShoppingItemPersistence shoppingItemPersistence) {
		this.shoppingItemPersistence = shoppingItemPersistence;
	}

	public ShoppingItemFinder getShoppingItemFinder() {
		return shoppingItemFinder;
	}

	public void setShoppingItemFinder(ShoppingItemFinder shoppingItemFinder) {
		this.shoppingItemFinder = shoppingItemFinder;
	}

	public ShoppingItemFieldLocalService getShoppingItemFieldLocalService() {
		return shoppingItemFieldLocalService;
	}

	public void setShoppingItemFieldLocalService(
		ShoppingItemFieldLocalService shoppingItemFieldLocalService) {
		this.shoppingItemFieldLocalService = shoppingItemFieldLocalService;
	}

	public ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		return shoppingItemFieldPersistence;
	}

	public void setShoppingItemFieldPersistence(
		ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		this.shoppingItemFieldPersistence = shoppingItemFieldPersistence;
	}

	public ShoppingItemPriceLocalService getShoppingItemPriceLocalService() {
		return shoppingItemPriceLocalService;
	}

	public void setShoppingItemPriceLocalService(
		ShoppingItemPriceLocalService shoppingItemPriceLocalService) {
		this.shoppingItemPriceLocalService = shoppingItemPriceLocalService;
	}

	public ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		return shoppingItemPricePersistence;
	}

	public void setShoppingItemPricePersistence(
		ShoppingItemPricePersistence shoppingItemPricePersistence) {
		this.shoppingItemPricePersistence = shoppingItemPricePersistence;
	}

	public ShoppingOrderPersistence getShoppingOrderPersistence() {
		return shoppingOrderPersistence;
	}

	public void setShoppingOrderPersistence(
		ShoppingOrderPersistence shoppingOrderPersistence) {
		this.shoppingOrderPersistence = shoppingOrderPersistence;
	}

	public ShoppingOrderFinder getShoppingOrderFinder() {
		return shoppingOrderFinder;
	}

	public void setShoppingOrderFinder(ShoppingOrderFinder shoppingOrderFinder) {
		this.shoppingOrderFinder = shoppingOrderFinder;
	}

	public ShoppingOrderItemLocalService getShoppingOrderItemLocalService() {
		return shoppingOrderItemLocalService;
	}

	public void setShoppingOrderItemLocalService(
		ShoppingOrderItemLocalService shoppingOrderItemLocalService) {
		this.shoppingOrderItemLocalService = shoppingOrderItemLocalService;
	}

	public ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		return shoppingOrderItemPersistence;
	}

	public void setShoppingOrderItemPersistence(
		ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		this.shoppingOrderItemPersistence = shoppingOrderItemPersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public MailService getMailService() {
		return mailService;
	}

	public void setMailService(MailService mailService) {
		this.mailService = mailService;
	}

	public CompanyLocalService getCompanyLocalService() {
		return companyLocalService;
	}

	public void setCompanyLocalService(CompanyLocalService companyLocalService) {
		this.companyLocalService = companyLocalService;
	}

	public CompanyService getCompanyService() {
		return companyService;
	}

	public void setCompanyService(CompanyService companyService) {
		this.companyService = companyService;
	}

	public CompanyPersistence getCompanyPersistence() {
		return companyPersistence;
	}

	public void setCompanyPersistence(CompanyPersistence companyPersistence) {
		this.companyPersistence = companyPersistence;
	}

	public UserLocalService getUserLocalService() {
		return userLocalService;
	}

	public void setUserLocalService(UserLocalService userLocalService) {
		this.userLocalService = userLocalService;
	}

	public UserService getUserService() {
		return userService;
	}

	public void setUserService(UserService userService) {
		this.userService = userService;
	}

	public UserPersistence getUserPersistence() {
		return userPersistence;
	}

	public void setUserPersistence(UserPersistence userPersistence) {
		this.userPersistence = userPersistence;
	}

	public UserFinder getUserFinder() {
		return userFinder;
	}

	public void setUserFinder(UserFinder userFinder) {
		this.userFinder = userFinder;
	}

	public MBMessageLocalService getMBMessageLocalService() {
		return mbMessageLocalService;
	}

	public void setMBMessageLocalService(
		MBMessageLocalService mbMessageLocalService) {
		this.mbMessageLocalService = mbMessageLocalService;
	}

	public MBMessageService getMBMessageService() {
		return mbMessageService;
	}

	public void setMBMessageService(MBMessageService mbMessageService) {
		this.mbMessageService = mbMessageService;
	}

	public MBMessagePersistence getMBMessagePersistence() {
		return mbMessagePersistence;
	}

	public void setMBMessagePersistence(
		MBMessagePersistence mbMessagePersistence) {
		this.mbMessagePersistence = mbMessagePersistence;
	}

	public MBMessageFinder getMBMessageFinder() {
		return mbMessageFinder;
	}

	public void setMBMessageFinder(MBMessageFinder mbMessageFinder) {
		this.mbMessageFinder = mbMessageFinder;
	}

	public void afterPropertiesSet() {
		if (shoppingCartLocalService == null) {
			shoppingCartLocalService = ShoppingCartLocalServiceFactory.getImpl();
		}

		if (shoppingCartPersistence == null) {
			shoppingCartPersistence = ShoppingCartUtil.getPersistence();
		}

		if (shoppingCategoryLocalService == null) {
			shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getImpl();
		}

		if (shoppingCategoryService == null) {
			shoppingCategoryService = ShoppingCategoryServiceFactory.getImpl();
		}

		if (shoppingCategoryPersistence == null) {
			shoppingCategoryPersistence = ShoppingCategoryUtil.getPersistence();
		}

		if (shoppingCouponLocalService == null) {
			shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getImpl();
		}

		if (shoppingCouponService == null) {
			shoppingCouponService = ShoppingCouponServiceFactory.getImpl();
		}

		if (shoppingCouponPersistence == null) {
			shoppingCouponPersistence = ShoppingCouponUtil.getPersistence();
		}

		if (shoppingCouponFinder == null) {
			shoppingCouponFinder = ShoppingCouponFinderUtil.getFinder();
		}

		if (shoppingItemLocalService == null) {
			shoppingItemLocalService = ShoppingItemLocalServiceFactory.getImpl();
		}

		if (shoppingItemService == null) {
			shoppingItemService = ShoppingItemServiceFactory.getImpl();
		}

		if (shoppingItemPersistence == null) {
			shoppingItemPersistence = ShoppingItemUtil.getPersistence();
		}

		if (shoppingItemFinder == null) {
			shoppingItemFinder = ShoppingItemFinderUtil.getFinder();
		}

		if (shoppingItemFieldLocalService == null) {
			shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getImpl();
		}

		if (shoppingItemFieldPersistence == null) {
			shoppingItemFieldPersistence = ShoppingItemFieldUtil.getPersistence();
		}

		if (shoppingItemPriceLocalService == null) {
			shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getImpl();
		}

		if (shoppingItemPricePersistence == null) {
			shoppingItemPricePersistence = ShoppingItemPriceUtil.getPersistence();
		}

		if (shoppingOrderPersistence == null) {
			shoppingOrderPersistence = ShoppingOrderUtil.getPersistence();
		}

		if (shoppingOrderFinder == null) {
			shoppingOrderFinder = ShoppingOrderFinderUtil.getFinder();
		}

		if (shoppingOrderItemLocalService == null) {
			shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getImpl();
		}

		if (shoppingOrderItemPersistence == null) {
			shoppingOrderItemPersistence = ShoppingOrderItemUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (mailService == null) {
			mailService = MailServiceFactory.getImpl();
		}

		if (companyLocalService == null) {
			companyLocalService = CompanyLocalServiceFactory.getImpl();
		}

		if (companyService == null) {
			companyService = CompanyServiceFactory.getImpl();
		}

		if (companyPersistence == null) {
			companyPersistence = CompanyUtil.getPersistence();
		}

		if (userLocalService == null) {
			userLocalService = UserLocalServiceFactory.getImpl();
		}

		if (userService == null) {
			userService = UserServiceFactory.getImpl();
		}

		if (userPersistence == null) {
			userPersistence = UserUtil.getPersistence();
		}

		if (userFinder == null) {
			userFinder = UserFinderUtil.getFinder();
		}

		if (mbMessageLocalService == null) {
			mbMessageLocalService = MBMessageLocalServiceFactory.getImpl();
		}

		if (mbMessageService == null) {
			mbMessageService = MBMessageServiceFactory.getImpl();
		}

		if (mbMessagePersistence == null) {
			mbMessagePersistence = MBMessageUtil.getPersistence();
		}

		if (mbMessageFinder == null) {
			mbMessageFinder = MBMessageFinderUtil.getFinder();
		}
	}

	protected ShoppingCartLocalService shoppingCartLocalService;
	protected ShoppingCartPersistence shoppingCartPersistence;
	protected ShoppingCategoryLocalService shoppingCategoryLocalService;
	protected ShoppingCategoryService shoppingCategoryService;
	protected ShoppingCategoryPersistence shoppingCategoryPersistence;
	protected ShoppingCouponLocalService shoppingCouponLocalService;
	protected ShoppingCouponService shoppingCouponService;
	protected ShoppingCouponPersistence shoppingCouponPersistence;
	protected ShoppingCouponFinder shoppingCouponFinder;
	protected ShoppingItemLocalService shoppingItemLocalService;
	protected ShoppingItemService shoppingItemService;
	protected ShoppingItemPersistence shoppingItemPersistence;
	protected ShoppingItemFinder shoppingItemFinder;
	protected ShoppingItemFieldLocalService shoppingItemFieldLocalService;
	protected ShoppingItemFieldPersistence shoppingItemFieldPersistence;
	protected ShoppingItemPriceLocalService shoppingItemPriceLocalService;
	protected ShoppingItemPricePersistence shoppingItemPricePersistence;
	protected ShoppingOrderPersistence shoppingOrderPersistence;
	protected ShoppingOrderFinder shoppingOrderFinder;
	protected ShoppingOrderItemLocalService shoppingOrderItemLocalService;
	protected ShoppingOrderItemPersistence shoppingOrderItemPersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected MailService mailService;
	protected CompanyLocalService companyLocalService;
	protected CompanyService companyService;
	protected CompanyPersistence companyPersistence;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
	protected MBMessageLocalService mbMessageLocalService;
	protected MBMessageService mbMessageService;
	protected MBMessagePersistence mbMessagePersistence;
	protected MBMessageFinder mbMessageFinder;
}
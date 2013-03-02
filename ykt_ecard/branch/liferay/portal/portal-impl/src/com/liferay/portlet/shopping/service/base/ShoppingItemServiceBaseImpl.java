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

import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

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
import com.liferay.portlet.shopping.service.ShoppingOrderItemLocalService;
import com.liferay.portlet.shopping.service.ShoppingOrderItemLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingOrderLocalService;
import com.liferay.portlet.shopping.service.ShoppingOrderLocalServiceFactory;
import com.liferay.portlet.shopping.service.ShoppingOrderService;
import com.liferay.portlet.shopping.service.ShoppingOrderServiceFactory;
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

/**
 * <a href="ShoppingItemServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class ShoppingItemServiceBaseImpl extends PrincipalBean
	implements ShoppingItemService, InitializingBean {
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

	public ShoppingOrderLocalService getShoppingOrderLocalService() {
		return shoppingOrderLocalService;
	}

	public void setShoppingOrderLocalService(
		ShoppingOrderLocalService shoppingOrderLocalService) {
		this.shoppingOrderLocalService = shoppingOrderLocalService;
	}

	public ShoppingOrderService getShoppingOrderService() {
		return shoppingOrderService;
	}

	public void setShoppingOrderService(
		ShoppingOrderService shoppingOrderService) {
		this.shoppingOrderService = shoppingOrderService;
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

	public ResourceLocalService getResourceLocalService() {
		return resourceLocalService;
	}

	public void setResourceLocalService(
		ResourceLocalService resourceLocalService) {
		this.resourceLocalService = resourceLocalService;
	}

	public ResourceService getResourceService() {
		return resourceService;
	}

	public void setResourceService(ResourceService resourceService) {
		this.resourceService = resourceService;
	}

	public ResourcePersistence getResourcePersistence() {
		return resourcePersistence;
	}

	public void setResourcePersistence(ResourcePersistence resourcePersistence) {
		this.resourcePersistence = resourcePersistence;
	}

	public ResourceFinder getResourceFinder() {
		return resourceFinder;
	}

	public void setResourceFinder(ResourceFinder resourceFinder) {
		this.resourceFinder = resourceFinder;
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

		if (shoppingOrderLocalService == null) {
			shoppingOrderLocalService = ShoppingOrderLocalServiceFactory.getImpl();
		}

		if (shoppingOrderService == null) {
			shoppingOrderService = ShoppingOrderServiceFactory.getImpl();
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

		if (resourceLocalService == null) {
			resourceLocalService = ResourceLocalServiceFactory.getImpl();
		}

		if (resourceService == null) {
			resourceService = ResourceServiceFactory.getImpl();
		}

		if (resourcePersistence == null) {
			resourcePersistence = ResourceUtil.getPersistence();
		}

		if (resourceFinder == null) {
			resourceFinder = ResourceFinderUtil.getFinder();
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
	protected ShoppingItemPersistence shoppingItemPersistence;
	protected ShoppingItemFinder shoppingItemFinder;
	protected ShoppingItemFieldLocalService shoppingItemFieldLocalService;
	protected ShoppingItemFieldPersistence shoppingItemFieldPersistence;
	protected ShoppingItemPriceLocalService shoppingItemPriceLocalService;
	protected ShoppingItemPricePersistence shoppingItemPricePersistence;
	protected ShoppingOrderLocalService shoppingOrderLocalService;
	protected ShoppingOrderService shoppingOrderService;
	protected ShoppingOrderPersistence shoppingOrderPersistence;
	protected ShoppingOrderFinder shoppingOrderFinder;
	protected ShoppingOrderItemLocalService shoppingOrderItemLocalService;
	protected ShoppingOrderItemPersistence shoppingOrderItemPersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
}
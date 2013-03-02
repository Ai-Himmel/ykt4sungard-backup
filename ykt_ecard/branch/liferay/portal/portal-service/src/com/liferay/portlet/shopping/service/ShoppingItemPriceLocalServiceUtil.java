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

package com.liferay.portlet.shopping.service;


/**
 * <a href="ShoppingItemPriceLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingItemPriceLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingItemPriceLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingItemPriceLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingItemPriceLocalServiceFactory
 *
 */
public class ShoppingItemPriceLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingItemPrice addShoppingItemPrice(
		com.liferay.portlet.shopping.model.ShoppingItemPrice model)
		throws com.liferay.portal.SystemException {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.addShoppingItemPrice(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemPrice updateShoppingItemPrice(
		com.liferay.portlet.shopping.model.ShoppingItemPrice model)
		throws com.liferay.portal.SystemException {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.updateShoppingItemPrice(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static void afterPropertiesSet() {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		shoppingItemPriceLocalService.afterPropertiesSet();
	}

	public static java.util.List getItemPrices(long itemId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemPriceLocalService shoppingItemPriceLocalService = ShoppingItemPriceLocalServiceFactory.getService();

		return shoppingItemPriceLocalService.getItemPrices(itemId);
	}
}
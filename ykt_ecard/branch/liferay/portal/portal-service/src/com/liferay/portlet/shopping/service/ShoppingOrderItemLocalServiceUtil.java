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
 * <a href="ShoppingOrderItemLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingOrderItemLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingOrderItemLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingOrderItemLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingOrderItemLocalServiceFactory
 *
 */
public class ShoppingOrderItemLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingOrderItem addShoppingOrderItem(
		com.liferay.portlet.shopping.model.ShoppingOrderItem model)
		throws com.liferay.portal.SystemException {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.addShoppingOrderItem(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem updateShoppingOrderItem(
		com.liferay.portlet.shopping.model.ShoppingOrderItem model)
		throws com.liferay.portal.SystemException {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.updateShoppingOrderItem(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static void afterPropertiesSet() {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		shoppingOrderItemLocalService.afterPropertiesSet();
	}

	public static java.util.List getOrderItems(long orderId)
		throws com.liferay.portal.SystemException {
		ShoppingOrderItemLocalService shoppingOrderItemLocalService = ShoppingOrderItemLocalServiceFactory.getService();

		return shoppingOrderItemLocalService.getOrderItems(orderId);
	}
}
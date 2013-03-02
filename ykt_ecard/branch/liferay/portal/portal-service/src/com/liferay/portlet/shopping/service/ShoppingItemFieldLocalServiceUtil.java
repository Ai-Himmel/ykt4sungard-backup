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
 * <a href="ShoppingItemFieldLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingItemFieldLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingItemFieldLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingItemFieldLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingItemFieldLocalServiceFactory
 *
 */
public class ShoppingItemFieldLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingItemField addShoppingItemField(
		com.liferay.portlet.shopping.model.ShoppingItemField model)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.addShoppingItemField(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField updateShoppingItemField(
		com.liferay.portlet.shopping.model.ShoppingItemField model)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.updateShoppingItemField(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static void afterPropertiesSet() {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		shoppingItemFieldLocalService.afterPropertiesSet();
	}

	public static java.util.List getItemFields(long itemId)
		throws com.liferay.portal.SystemException {
		ShoppingItemFieldLocalService shoppingItemFieldLocalService = ShoppingItemFieldLocalServiceFactory.getService();

		return shoppingItemFieldLocalService.getItemFields(itemId);
	}
}
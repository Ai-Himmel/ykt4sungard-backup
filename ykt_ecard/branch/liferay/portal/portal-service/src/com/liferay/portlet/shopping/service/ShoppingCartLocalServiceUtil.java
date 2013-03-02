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
 * <a href="ShoppingCartLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingCartLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingCartLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingCartLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingCartLocalServiceFactory
 *
 */
public class ShoppingCartLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingCart addShoppingCart(
		com.liferay.portlet.shopping.model.ShoppingCart model)
		throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.addShoppingCart(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCart updateShoppingCart(
		com.liferay.portlet.shopping.model.ShoppingCart model)
		throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.updateShoppingCart(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.afterPropertiesSet();
	}

	public static void deleteGroupCarts(long groupId)
		throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.deleteGroupCarts(groupId);
	}

	public static void deleteUserCarts(long userId)
		throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		shoppingCartLocalService.deleteUserCarts(userId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCart getCart(
		long userId, long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getCart(userId, groupId);
	}

	public static java.util.Map getItems(long groupId, java.lang.String itemIds)
		throws com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.getItems(groupId, itemIds);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCart updateCart(
		long userId, long groupId, java.lang.String itemIds,
		java.lang.String couponCodes, int altShipping, boolean insure)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCartLocalService shoppingCartLocalService = ShoppingCartLocalServiceFactory.getService();

		return shoppingCartLocalService.updateCart(userId, groupId, itemIds,
			couponCodes, altShipping, insure);
	}
}
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
 * <a href="ShoppingCouponLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingCouponLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingCouponLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingCouponLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingCouponLocalServiceFactory
 *
 */
public class ShoppingCouponLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingCoupon addShoppingCoupon(
		com.liferay.portlet.shopping.model.ShoppingCoupon model)
		throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.addShoppingCoupon(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon updateShoppingCoupon(
		com.liferay.portlet.shopping.model.ShoppingCoupon model)
		throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.updateShoppingCoupon(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon addCoupon(
		long userId, long plid, java.lang.String code, boolean autoCode,
		java.lang.String name, java.lang.String description,
		int startDateMonth, int startDateDay, int startDateYear,
		int startDateHour, int startDateMinute, int endDateMonth,
		int endDateDay, int endDateYear, int endDateHour, int endDateMinute,
		boolean neverExpire, boolean active, java.lang.String limitCategories,
		java.lang.String limitSkus, double minOrder, double discount,
		java.lang.String discountType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.addCoupon(userId, plid, code,
			autoCode, name, description, startDateMonth, startDateDay,
			startDateYear, startDateHour, startDateMinute, endDateMonth,
			endDateDay, endDateYear, endDateHour, endDateMinute, neverExpire,
			active, limitCategories, limitSkus, minOrder, discount, discountType);
	}

	public static void deleteCoupon(long couponId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.deleteCoupon(couponId);
	}

	public static void deleteCoupons(long groupId)
		throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		shoppingCouponLocalService.deleteCoupons(groupId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon getCoupon(
		long couponId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getCoupon(couponId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon getCoupon(
		java.lang.String code)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.getCoupon(code);
	}

	public static java.util.List search(long plid, long companyId,
		java.lang.String code, boolean active, java.lang.String discountType,
		boolean andOperator, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.search(plid, companyId, code, active,
			discountType, andOperator, begin, end);
	}

	public static int searchCount(long groupId, long companyId,
		java.lang.String code, boolean active, java.lang.String discountType,
		boolean andOperator) throws com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.searchCount(groupId, companyId, code,
			active, discountType, andOperator);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon updateCoupon(
		long userId, long couponId, java.lang.String name,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int endDateHour,
		int endDateMinute, boolean neverExpire, boolean active,
		java.lang.String limitCategories, java.lang.String limitSkus,
		double minOrder, double discount, java.lang.String discountType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCouponLocalService shoppingCouponLocalService = ShoppingCouponLocalServiceFactory.getService();

		return shoppingCouponLocalService.updateCoupon(userId, couponId, name,
			description, startDateMonth, startDateDay, startDateYear,
			startDateHour, startDateMinute, endDateMonth, endDateDay,
			endDateYear, endDateHour, endDateMinute, neverExpire, active,
			limitCategories, limitSkus, minOrder, discount, discountType);
	}
}
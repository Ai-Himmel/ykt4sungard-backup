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
 * <a href="ShoppingCategoryLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingCategoryLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingCategoryLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceFactory
 *
 */
public class ShoppingCategoryLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingCategory addShoppingCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory model)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.addShoppingCategory(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory updateShoppingCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory model)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.updateShoppingCategory(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.addCategory(userId, plid,
			parentCategoryId, name, description, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.addCategory(userId, plid,
			parentCategoryId, name, description, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.addCategory(userId, plid,
			parentCategoryId, name, description, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions);
	}

	public static void addCategoryResources(long categoryId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.addCategoryResources(categoryId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addCategoryResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.addCategoryResources(category,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addCategoryResources(long categoryId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.addCategoryResources(categoryId,
			communityPermissions, guestPermissions);
	}

	public static void addCategoryResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.addCategoryResources(category,
			communityPermissions, guestPermissions);
	}

	public static void deleteCategories(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.deleteCategories(groupId);
	}

	public static void deleteCategory(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.deleteCategory(categoryId);
	}

	public static void deleteCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.deleteCategory(category);
	}

	public static java.util.List getCategories(long groupId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getCategories(groupId);
	}

	public static java.util.List getCategories(long groupId,
		long parentCategoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getCategories(groupId,
			parentCategoryId, begin, end);
	}

	public static int getCategoriesCount(long groupId, long parentCategoryId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getCategoriesCount(groupId,
			parentCategoryId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory getCategory(
		long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getCategory(categoryId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory getParentCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getParentCategory(category);
	}

	public static java.util.List getParentCategories(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getParentCategories(categoryId);
	}

	public static java.util.List getParentCategories(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.getParentCategories(category);
	}

	public static void getSubcategoryIds(java.util.List categoryIds,
		long groupId, long categoryId)
		throws com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		shoppingCategoryLocalService.getSubcategoryIds(categoryIds, groupId,
			categoryId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingCategory updateCategory(
		long categoryId, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean mergeWithParentCategory)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingCategoryLocalService shoppingCategoryLocalService = ShoppingCategoryLocalServiceFactory.getService();

		return shoppingCategoryLocalService.updateCategory(categoryId,
			parentCategoryId, name, description, mergeWithParentCategory);
	}
}
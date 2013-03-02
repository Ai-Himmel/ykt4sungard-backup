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
 * <a href="ShoppingItemLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.shopping.service.ShoppingItemLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.shopping.service.ShoppingItemLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingItemLocalService
 * @see com.liferay.portlet.shopping.service.ShoppingItemLocalServiceFactory
 *
 */
public class ShoppingItemLocalServiceUtil {
	public static com.liferay.portlet.shopping.model.ShoppingItem addShoppingItem(
		com.liferay.portlet.shopping.model.ShoppingItem model)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.addShoppingItem(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem updateShoppingItem(
		com.liferay.portlet.shopping.model.ShoppingItem model)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.updateShoppingItem(model);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingCartPersistence();
	}

	public static void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingCartPersistence(shoppingCartPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingCategoryPersistence();
	}

	public static void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingCategoryPersistence(shoppingCategoryPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingCouponPersistence();
	}

	public static void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingCouponPersistence(shoppingCouponPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingCouponFinder();
	}

	public static void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingCouponFinder(shoppingCouponFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingItemPersistence();
	}

	public static void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingItemPersistence(shoppingItemPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingItemFinder();
	}

	public static void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingItemFinder(shoppingItemFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingItemFieldPersistence();
	}

	public static void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingItemFieldPersistence(shoppingItemFieldPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingItemPricePersistence();
	}

	public static void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingItemPricePersistence(shoppingItemPricePersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingOrderPersistence();
	}

	public static void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingOrderPersistence(shoppingOrderPersistence);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingOrderFinder();
	}

	public static void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingOrderFinder(shoppingOrderFinder);
	}

	public static com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getShoppingOrderItemPersistence();
	}

	public static void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setShoppingOrderItemPersistence(shoppingOrderItemPersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.afterPropertiesSet();
	}

	public static void addBookItems(long userId, long categoryId,
		java.lang.String[] isbns)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.addBookItems(userId, categoryId, isbns);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem addItem(
		long userId, long categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.addItem(userId, categoryId, sku, name,
			description, properties, fieldsQuantities, requiresShipping,
			stockQuantity, featured, sale, smallImage, smallImageURL,
			smallFile, mediumImage, mediumImageURL, mediumFile, largeImage,
			largeImageURL, largeFile, itemFields, itemPrices,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem addItem(
		long userId, long categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.addItem(userId, categoryId, sku, name,
			description, properties, fieldsQuantities, requiresShipping,
			stockQuantity, featured, sale, smallImage, smallImageURL,
			smallFile, mediumImage, mediumImageURL, mediumFile, largeImage,
			largeImageURL, largeFile, itemFields, itemPrices,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem addItem(
		long userId, long categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.addItem(userId, categoryId, sku, name,
			description, properties, fieldsQuantities, requiresShipping,
			stockQuantity, featured, sale, smallImage, smallImageURL,
			smallFile, mediumImage, mediumImageURL, mediumFile, largeImage,
			largeImageURL, largeFile, itemFields, itemPrices,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static void addItemResources(long itemId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.addItemResources(itemId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addItemResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		com.liferay.portlet.shopping.model.ShoppingItem item,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.addItemResources(category, item,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addItemResources(long itemId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.addItemResources(itemId, communityPermissions,
			guestPermissions);
	}

	public static void addItemResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		com.liferay.portlet.shopping.model.ShoppingItem item,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.addItemResources(category, item,
			communityPermissions, guestPermissions);
	}

	public static void deleteItem(long itemId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.deleteItem(itemId);
	}

	public static void deleteItem(
		com.liferay.portlet.shopping.model.ShoppingItem item)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.deleteItem(item);
	}

	public static void deleteItems(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		shoppingItemLocalService.deleteItems(categoryId);
	}

	public static int getCategoriesItemsCount(java.util.List categoryIds)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getCategoriesItemsCount(categoryIds);
	}

	public static java.util.List getFeaturedItems(long groupId,
		long categoryId, int numOfItems)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getFeaturedItems(groupId, categoryId,
			numOfItems);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItem(
		long itemId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItem(itemId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItem(
		long companyId, java.lang.String sku)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItem(companyId, sku);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItemByLargeImageId(
		long largeImageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItemByLargeImageId(largeImageId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItemByMediumImageId(
		long mediumImageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItemByMediumImageId(mediumImageId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItemBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItemBySmallImageId(smallImageId);
	}

	public static java.util.List getItems(long categoryId)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItems(categoryId);
	}

	public static java.util.List getItems(long categoryId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItems(categoryId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem[] getItemsPrevAndNext(
		long itemId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItemsPrevAndNext(itemId, obc);
	}

	public static int getItemsCount(long categoryId)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getItemsCount(categoryId);
	}

	public static java.util.List getSaleItems(long groupId, long categoryId,
		int numOfItems) throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.getSaleItems(groupId, categoryId,
			numOfItems);
	}

	public static java.util.List search(long groupId, long[] categoryIds,
		java.lang.String keywords, int begin, int end)
		throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.search(groupId, categoryIds, keywords,
			begin, end);
	}

	public static int searchCount(long groupId, long[] categoryIds,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.searchCount(groupId, categoryIds,
			keywords);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem updateItem(
		long userId, long itemId, long categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		ShoppingItemLocalService shoppingItemLocalService = ShoppingItemLocalServiceFactory.getService();

		return shoppingItemLocalService.updateItem(userId, itemId, categoryId,
			sku, name, description, properties, fieldsQuantities,
			requiresShipping, stockQuantity, featured, sale, smallImage,
			smallImageURL, smallFile, mediumImage, mediumImageURL, mediumFile,
			largeImage, largeImageURL, largeFile, itemFields, itemPrices);
	}
}
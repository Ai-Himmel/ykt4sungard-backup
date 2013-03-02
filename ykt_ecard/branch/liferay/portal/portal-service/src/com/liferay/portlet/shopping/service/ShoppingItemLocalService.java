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
 * <a href="ShoppingItemLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.shopping.service.impl.ShoppingItemLocalServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingItemLocalServiceFactory
 * @see com.liferay.portlet.shopping.service.ShoppingItemLocalServiceUtil
 *
 */
public interface ShoppingItemLocalService {
	public com.liferay.portlet.shopping.model.ShoppingItem addShoppingItem(
		com.liferay.portlet.shopping.model.ShoppingItem model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem updateShoppingItem(
		com.liferay.portlet.shopping.model.ShoppingItem model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence getShoppingCartPersistence();

	public void setShoppingCartPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCartPersistence shoppingCartPersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence getShoppingCategoryPersistence();

	public void setShoppingCategoryPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCategoryPersistence shoppingCategoryPersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence getShoppingCouponPersistence();

	public void setShoppingCouponPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponPersistence shoppingCouponPersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder getShoppingCouponFinder();

	public void setShoppingCouponFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingCouponFinder shoppingCouponFinder);

	public com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence getShoppingItemPersistence();

	public void setShoppingItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPersistence shoppingItemPersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder getShoppingItemFinder();

	public void setShoppingItemFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFinder shoppingItemFinder);

	public com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence getShoppingItemFieldPersistence();

	public void setShoppingItemFieldPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldPersistence shoppingItemFieldPersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence getShoppingItemPricePersistence();

	public void setShoppingItemPricePersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingItemPricePersistence shoppingItemPricePersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence getShoppingOrderPersistence();

	public void setShoppingOrderPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderPersistence shoppingOrderPersistence);

	public com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder getShoppingOrderFinder();

	public void setShoppingOrderFinder(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderFinder shoppingOrderFinder);

	public com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence getShoppingOrderItemPersistence();

	public void setShoppingOrderItemPersistence(
		com.liferay.portlet.shopping.service.persistence.ShoppingOrderItemPersistence shoppingOrderItemPersistence);

	public com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence();

	public void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence);

	public com.liferay.portal.service.persistence.ResourceFinder getResourceFinder();

	public void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder);

	public com.liferay.portal.service.persistence.UserPersistence getUserPersistence();

	public void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence);

	public com.liferay.portal.service.persistence.UserFinder getUserFinder();

	public void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder);

	public void afterPropertiesSet();

	public void addBookItems(long userId, long categoryId,
		java.lang.String[] isbns)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem addItem(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem addItem(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem addItem(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addItemResources(long itemId, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addItemResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		com.liferay.portlet.shopping.model.ShoppingItem item,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addItemResources(long itemId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addItemResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		com.liferay.portlet.shopping.model.ShoppingItem item,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteItem(long itemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteItem(com.liferay.portlet.shopping.model.ShoppingItem item)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteItems(long categoryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public int getCategoriesItemsCount(java.util.List categoryIds)
		throws com.liferay.portal.SystemException;

	public java.util.List getFeaturedItems(long groupId, long categoryId,
		int numOfItems) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem getItem(long itemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem getItem(
		long companyId, java.lang.String sku)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem getItemByLargeImageId(
		long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem getItemByMediumImageId(
		long mediumImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingItem getItemBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getItems(long categoryId)
		throws com.liferay.portal.SystemException;

	public java.util.List getItems(long categoryId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem[] getItemsPrevAndNext(
		long itemId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public int getItemsCount(long categoryId)
		throws com.liferay.portal.SystemException;

	public java.util.List getSaleItems(long groupId, long categoryId,
		int numOfItems) throws com.liferay.portal.SystemException;

	public java.util.List search(long groupId, long[] categoryIds,
		java.lang.String keywords, int begin, int end)
		throws com.liferay.portal.SystemException;

	public int searchCount(long groupId, long[] categoryIds,
		java.lang.String keywords) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingItem updateItem(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}
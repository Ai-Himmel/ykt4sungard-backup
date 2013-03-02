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
 * <a href="ShoppingCategoryLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.shopping.service.impl.ShoppingCategoryLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceFactory
 * @see com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceUtil
 *
 */
public interface ShoppingCategoryLocalService {
	public com.liferay.portlet.shopping.model.ShoppingCategory addShoppingCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingCategory updateShoppingCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory model)
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

	public com.liferay.portlet.shopping.model.ShoppingCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addCategoryResources(long categoryId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addCategoryResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addCategoryResources(long categoryId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addCategoryResources(
		com.liferay.portlet.shopping.model.ShoppingCategory category,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteCategories(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteCategory(long categoryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getCategories(long groupId)
		throws com.liferay.portal.SystemException;

	public java.util.List getCategories(long groupId, long parentCategoryId,
		int begin, int end) throws com.liferay.portal.SystemException;

	public int getCategoriesCount(long groupId, long parentCategoryId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingCategory getCategory(
		long categoryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.shopping.model.ShoppingCategory getParentCategory(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getParentCategories(long categoryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getParentCategories(
		com.liferay.portlet.shopping.model.ShoppingCategory category)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void getSubcategoryIds(java.util.List categoryIds, long groupId,
		long categoryId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.shopping.model.ShoppingCategory updateCategory(
		long categoryId, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean mergeWithParentCategory)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}
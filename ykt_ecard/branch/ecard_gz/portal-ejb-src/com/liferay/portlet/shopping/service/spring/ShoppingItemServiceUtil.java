/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.shopping.service.spring;

/**
 * <a href="ShoppingItemServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemServiceUtil {
	public static final String PORTLET_ID = "34";

	public static void addBookItems(java.lang.String categoryId,
		java.lang.String[] isbnArray)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();
			shoppingItemService.addBookItems(categoryId, isbnArray);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem addItem(
		java.lang.String categoryId, java.lang.String sku,
		java.lang.String name, java.lang.String description,
		java.lang.String properties, java.lang.String supplierUserId,
		java.lang.String fieldsQuantities, boolean requiresShipping,
		int stockQuantity, boolean featured, java.lang.Boolean sale,
		boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, boolean mediumImage,
		java.lang.String mediumImageURL, java.io.File mediumFile,
		boolean largeImage, java.lang.String largeImageURL,
		java.io.File largeFile, java.util.List itemFields,
		java.util.List itemPrices)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.addItem(categoryId, sku, name,
				description, properties, supplierUserId, fieldsQuantities,
				requiresShipping, stockQuantity, featured, sale, smallImage,
				smallImageURL, smallFile, mediumImage, mediumImageURL,
				mediumFile, largeImage, largeImageURL, largeFile, itemFields,
				itemPrices);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteItem(java.lang.String itemId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();
			shoppingItemService.deleteItem(itemId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteItem(
		com.liferay.portlet.shopping.model.ShoppingItem item)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();
			shoppingItemService.deleteItem(item);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getFeaturedItems(java.lang.String companyId,
		java.lang.String categoryId, int numOfItems)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getFeaturedItems(companyId, categoryId,
				numOfItems);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItemById(
		java.lang.String itemId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItemById(itemId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem getItemBySKU(
		java.lang.String companyId, java.lang.String sku)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItemBySKU(companyId, sku);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getItems(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItems(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getItems(java.lang.String companyId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItems(companyId, categoryId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getItems(java.lang.String companyId,
		java.lang.String categoryId, int begin, int end,
		javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItems(companyId, categoryId, begin,
				end, prefs);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem[] getItemsPrevAndNext(
		java.lang.String itemId, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItemsPrevAndNext(itemId, prefs);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getItemsSize(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItemsSize(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getItemsSize(java.lang.String companyId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getItemsSize(companyId, categoryId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getSaleItems(java.lang.String companyId,
		java.lang.String categoryId, int numOfItems)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.getSaleItems(companyId, categoryId,
				numOfItems);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List search(java.lang.String companyId,
		java.lang.String[] categoryIds, java.lang.String keywords, int begin,
		int end) throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.search(companyId, categoryIds, keywords,
				begin, end);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int searchSize(java.lang.String companyId,
		java.lang.String[] categoryIds, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.searchSize(companyId, categoryIds,
				keywords);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingItem updateItem(
		java.lang.String itemId, java.lang.String categoryId,
		java.lang.String sku, java.lang.String name,
		java.lang.String description, java.lang.String properties,
		java.lang.String supplierUserId, java.lang.String fieldsQuantities,
		boolean requiresShipping, int stockQuantity, boolean featured,
		java.lang.Boolean sale, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean mediumImage, java.lang.String mediumImageURL,
		java.io.File mediumFile, boolean largeImage,
		java.lang.String largeImageURL, java.io.File largeFile,
		java.util.List itemFields, java.util.List itemPrices)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.updateItem(itemId, categoryId, sku,
				name, description, properties, supplierUserId,
				fieldsQuantities, requiresShipping, stockQuantity, featured,
				sale, smallImage, smallImageURL, smallFile, mediumImage,
				mediumImageURL, mediumFile, largeImage, largeImageURL,
				largeFile, itemFields, itemPrices);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin(java.lang.String itemId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingItemService shoppingItemService = ShoppingItemServiceFactory.getService();

			return shoppingItemService.hasAdmin(itemId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}
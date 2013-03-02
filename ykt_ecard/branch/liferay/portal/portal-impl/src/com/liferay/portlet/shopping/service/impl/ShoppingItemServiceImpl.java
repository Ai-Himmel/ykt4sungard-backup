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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.base.ShoppingItemServiceBaseImpl;
import com.liferay.portlet.shopping.service.permission.ShoppingCategoryPermission;
import com.liferay.portlet.shopping.service.permission.ShoppingItemPermission;

import java.io.File;

import java.util.List;

/**
 * <a href="ShoppingItemServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemServiceImpl extends ShoppingItemServiceBaseImpl {

	public void addBookItems(long categoryId, String[] isbns)
		throws PortalException, SystemException {

		ShoppingCategoryPermission.check(
			getPermissionChecker(), categoryId, ActionKeys.ADD_ITEM);

		shoppingItemLocalService.addBookItems(getUserId(), categoryId, isbns);
	}

	public ShoppingItem addItem(
			long categoryId, String sku, String name, String description,
			String properties, String fieldsQuantities,
			boolean requiresShipping, int stockQuantity, boolean featured,
			Boolean sale, boolean smallImage, String smallImageURL,
			File smallFile, boolean mediumImage, String mediumImageURL,
			File mediumFile, boolean largeImage, String largeImageURL,
			File largeFile, List itemFields, List itemPrices,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		ShoppingCategoryPermission.check(
			getPermissionChecker(), categoryId, ActionKeys.ADD_ITEM);

		return shoppingItemLocalService.addItem(
			getUserId(), categoryId, sku, name, description, properties,
			fieldsQuantities, requiresShipping, stockQuantity, featured, sale,
			smallImage, smallImageURL, smallFile, mediumImage, mediumImageURL,
			mediumFile, largeImage, largeImageURL, largeFile, itemFields,
			itemPrices, addCommunityPermissions, addGuestPermissions);
	}

	public ShoppingItem addItem(
			long categoryId, String sku, String name, String description,
			String properties, String fieldsQuantities,
			boolean requiresShipping, int stockQuantity, boolean featured,
			Boolean sale, boolean smallImage, String smallImageURL,
			File smallFile, boolean mediumImage, String mediumImageURL,
			File mediumFile, boolean largeImage, String largeImageURL,
			File largeFile, List itemFields, List itemPrices,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		ShoppingCategoryPermission.check(
			getPermissionChecker(), categoryId, ActionKeys.ADD_ITEM);

		return shoppingItemLocalService.addItem(
			getUserId(), categoryId, sku, name, description, properties,
			fieldsQuantities, requiresShipping, stockQuantity, featured, sale,
			smallImage, smallImageURL, smallFile, mediumImage, mediumImageURL,
			mediumFile, largeImage, largeImageURL, largeFile, itemFields,
			itemPrices, communityPermissions, guestPermissions);
	}

	public void deleteItem(long itemId)
		throws PortalException, SystemException {

		ShoppingItemPermission.check(
			getPermissionChecker(), itemId, ActionKeys.DELETE);

		shoppingItemLocalService.deleteItem(itemId);
	}

	public ShoppingItem getItem(long itemId)
		throws PortalException, SystemException {

		ShoppingItemPermission.check(
			getPermissionChecker(), itemId, ActionKeys.VIEW);

		return shoppingItemLocalService.getItem(itemId);
	}

	public ShoppingItem updateItem(
			long itemId, long categoryId, String sku, String name,
			String description, String properties, String fieldsQuantities,
			boolean requiresShipping, int stockQuantity, boolean featured,
			Boolean sale, boolean smallImage, String smallImageURL,
			File smallFile, boolean mediumImage, String mediumImageURL,
			File mediumFile, boolean largeImage, String largeImageURL,
			File largeFile, List itemFields, List itemPrices)
		throws PortalException, SystemException {

		ShoppingItemPermission.check(
			getPermissionChecker(), itemId, ActionKeys.UPDATE);

		return shoppingItemLocalService.updateItem(
			getUserId(), itemId, categoryId, sku, name, description, properties,
			fieldsQuantities, requiresShipping, stockQuantity, featured, sale,
			smallImage, smallImageURL, smallFile, mediumImage, mediumImageURL,
			mediumFile, largeImage, largeImageURL, largeFile, itemFields,
			itemPrices);
	}

}
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

package com.liferay.portlet.shopping.service.permission;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.impl.ShoppingCategoryImpl;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceUtil;

/**
 * <a href="ShoppingCategoryPermission.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCategoryPermission {

	public static void check(
			PermissionChecker permissionChecker, long plid, long categoryId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, plid, categoryId, actionId)) {
			throw new PrincipalException();
		}
	}

	public static void check(
			PermissionChecker permissionChecker, long categoryId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, categoryId, actionId)) {
			throw new PrincipalException();
		}
	}

	public static void check(
			PermissionChecker permissionChecker, ShoppingCategory category,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, category, actionId)) {
			throw new PrincipalException();
		}
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long plid, long categoryId,
			String actionId)
		throws PortalException, SystemException {

		if (categoryId == ShoppingCategoryImpl.DEFAULT_PARENT_CATEGORY_ID) {
			return PortletPermissionUtil.contains(
				permissionChecker, plid, PortletKeys.SHOPPING, actionId);
		}
		else {
			return contains(permissionChecker, categoryId, actionId);
		}
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long categoryId,
			String actionId)
		throws PortalException, SystemException {

		ShoppingCategory category =
			ShoppingCategoryLocalServiceUtil.getCategory(categoryId);

		return contains(permissionChecker, category, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, ShoppingCategory category,
			String actionId)
		throws PortalException, SystemException {

		if (actionId.equals(ActionKeys.ADD_CATEGORY)) {
			actionId = ActionKeys.ADD_SUBCATEGORY;
		}

		long categoryId = category.getCategoryId();

		while (categoryId != ShoppingCategoryImpl.DEFAULT_PARENT_CATEGORY_ID) {
			category = ShoppingCategoryLocalServiceUtil.getCategory(categoryId);

			categoryId = category.getParentCategoryId();

			if (permissionChecker.hasPermission(
					category.getGroupId(), ShoppingCategory.class.getName(),
					category.getCategoryId(), actionId)) {

				return true;
			}

			if (actionId.equals(ActionKeys.VIEW)) {
				break;
			}
		}

		return false;
	}

}
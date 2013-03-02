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

package com.liferay.portal.service.permission;

import com.liferay.portal.NoSuchResourceException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.ResourceLocalServiceUtil;

/**
 * <a href="LayoutPermissionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutPermissionImpl implements LayoutPermission {

	public void check(
			PermissionChecker permissionChecker, long plid, String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, plid, actionId)) {
			throw new PrincipalException();
		}
	}

	public void check(
			PermissionChecker permissionChecker, long groupId,
			boolean privateLayout, long layoutId, String actionId)
		throws PortalException, SystemException {

		if (!contains(
				permissionChecker, groupId, privateLayout, layoutId,
				actionId)) {

			throw new PrincipalException();
		}
	}

	public void check(
			PermissionChecker permissionChecker, Layout layout, String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, layout, actionId)) {
			throw new PrincipalException();
		}
	}

	public boolean contains(
			PermissionChecker permissionChecker, long plid, String actionId)
		throws PortalException, SystemException {

		Layout layout = LayoutLocalServiceUtil.getLayout(plid);

		return contains(permissionChecker, layout, actionId);
	}

	public boolean contains(
			PermissionChecker permissionChecker, long groupId,
			boolean privateLayout, long layoutId, String actionId)
		throws PortalException, SystemException {

		if (layoutId == LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {
			if (GroupPermissionUtil.contains(
					permissionChecker, groupId, ActionKeys.MANAGE_LAYOUTS)) {

				return true;
			}
			else {
				return false;
			}
		}
		else {
			Layout layout = LayoutLocalServiceUtil.getLayout(
				groupId, privateLayout, layoutId);

			return contains(permissionChecker, layout, actionId);
		}
	}

	public boolean contains(
			PermissionChecker permissionChecker, Layout layout, String actionId)
		throws PortalException, SystemException {

		if (GroupPermissionUtil.contains(
				permissionChecker, layout.getGroupId(),
				ActionKeys.MANAGE_LAYOUTS)) {

			return true;
		}

		try {
			ResourceLocalServiceUtil.getResource(
				layout.getCompanyId(), Layout.class.getName(),
				ResourceImpl.SCOPE_INDIVIDUAL,
				String.valueOf(layout.getPlid()));
		}
		catch (NoSuchResourceException nsre) {
			boolean addCommunityPermission = true;
			boolean addGuestPermission = true;

			if (layout.isPrivateLayout()) {
				addGuestPermission = false;
			}

			ResourceLocalServiceUtil.addResources(
				layout.getCompanyId(), layout.getGroupId(), 0,
				Layout.class.getName(), layout.getPlid(), false,
				addCommunityPermission, addGuestPermission);
		}

		return permissionChecker.hasPermission(
			layout.getGroupId(), Layout.class.getName(), layout.getPlid(),
			actionId);
	}

}
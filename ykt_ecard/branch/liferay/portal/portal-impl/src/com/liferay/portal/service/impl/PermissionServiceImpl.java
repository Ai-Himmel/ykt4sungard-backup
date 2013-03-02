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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.security.permission.PermissionCheckerBag;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.PermissionServiceBaseImpl;
import com.liferay.portal.service.permission.GroupPermissionUtil;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.service.permission.UserPermissionUtil;

/**
 * <a href="PermissionServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionServiceImpl extends PermissionServiceBaseImpl {

	public void checkPermission(long groupId, String name, String primKey)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, name, primKey);
	}

	public boolean hasGroupPermission(
			long groupId, String actionId, long resourceId)
		throws PortalException, SystemException {

		return permissionLocalService.hasGroupPermission(
			groupId, actionId, resourceId);
	}

	public boolean hasUserPermission(
			long userId, String actionId, long resourceId)
		throws PortalException, SystemException {

		return permissionLocalService.hasUserPermission(
			userId, actionId, resourceId);
	}

	public boolean hasUserPermissions(
			long userId, long groupId, String actionId, long[] resourceIds,
			PermissionCheckerBag permissionCheckerBag)
		throws PortalException, SystemException {

		return permissionLocalService.hasUserPermissions(
			userId, groupId, actionId, resourceIds, permissionCheckerBag);
	}

	public void setGroupPermissions(
			long groupId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, resourceId);

		permissionLocalService.setGroupPermissions(
			groupId, actionIds, resourceId);
	}

	public void setGroupPermissions(
			String className, String classPK, long groupId,
			String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, resourceId);

		permissionLocalService.setGroupPermissions(
			className, classPK, groupId, actionIds, resourceId);
	}

	public void setOrgGroupPermissions(
			long organizationId, long groupId, String[] actionIds,
			long resourceId)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, resourceId);

		permissionLocalService.setOrgGroupPermissions(
			organizationId, groupId, actionIds, resourceId);
	}

	public void setRolePermission(
			long roleId, long groupId, String name, int scope, String primKey,
			String actionId)
		throws PortalException, SystemException {

		checkPermission(
			getPermissionChecker(), groupId, Role.class.getName(), roleId);

		permissionLocalService.setRolePermission(
			roleId, getUser().getCompanyId(), name, scope, primKey, actionId);
	}

	public void setRolePermissions(
			long roleId, long groupId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, resourceId);

		permissionLocalService.setRolePermissions(
			roleId, actionIds, resourceId);
	}

	public void setUserPermissions(
			long userId, long groupId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, resourceId);

		permissionLocalService.setUserPermissions(
			userId, actionIds, resourceId);
	}

	public void unsetRolePermission(
			long roleId, long groupId, long permissionId)
		throws SystemException, PortalException {

		checkPermission(
			getPermissionChecker(), groupId, Role.class.getName(), roleId);

		permissionLocalService.unsetRolePermission(roleId, permissionId);
	}

	public void unsetRolePermission(
			long roleId, long groupId, String name, int scope, String primKey,
			String actionId)
		throws PortalException, SystemException {

		checkPermission(
			getPermissionChecker(), groupId, Role.class.getName(), roleId);

		permissionLocalService.unsetRolePermission(
			roleId, getUser().getCompanyId(), name, scope, primKey, actionId);
	}

	public void unsetRolePermissions(
			long roleId, long groupId, String name, int scope, String actionId)
		throws PortalException, SystemException {

		checkPermission(
			getPermissionChecker(), groupId, Role.class.getName(), roleId);

		permissionLocalService.unsetRolePermissions(
			roleId, getUser().getCompanyId(), name, scope, actionId);
	}

	public void unsetUserPermissions(
			long userId, long groupId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		checkPermission(getPermissionChecker(), groupId, resourceId);

		permissionLocalService.unsetUserPermissions(
			userId, actionIds, resourceId);
	}

	protected void checkPermission(
			PermissionChecker permissionChecker, long groupId,
			long resourceId)
		throws PortalException, SystemException {

		Resource resource = resourcePersistence.findByPrimaryKey(resourceId);

		checkPermission(
			permissionChecker, groupId, resource.getName(),
			resource.getPrimKey().toString());
	}

	protected void checkPermission(
			PermissionChecker permissionChecker, long groupId, String name,
			long primKey)
		throws PortalException, SystemException {

		checkPermission(
			permissionChecker, groupId, name, String.valueOf(primKey));
	}

	protected void checkPermission(
			PermissionChecker permissionChecker, long groupId, String name,
			String primKey)
		throws PortalException, SystemException {

		if (name.equals(Group.class.getName())) {
			GroupPermissionUtil.check(
				permissionChecker, GetterUtil.getLong(primKey),
				ActionKeys.PERMISSIONS);
		}
		else if (name.equals(Layout.class.getName())) {
			long plid = GetterUtil.getLong(primKey);

			Layout layout = layoutPersistence.findByPrimaryKey(plid);

			GroupPermissionUtil.check(
				permissionChecker, layout.getGroupId(),
				ActionKeys.MANAGE_LAYOUTS);
		}
		else if (name.equals(User.class.getName())) {
			long userId = GetterUtil.getLong(primKey);

			User user = userPersistence.findByPrimaryKey(userId);

			UserPermissionUtil.check(
				permissionChecker, userId, user.getOrganizationIds(),
				ActionKeys.PERMISSIONS);
		}
		else if ((primKey != null) &&
				 (primKey.indexOf(PortletImpl.LAYOUT_SEPARATOR) != -1)) {

			int pos = primKey.indexOf(PortletImpl.LAYOUT_SEPARATOR);

			long plid = GetterUtil.getLong(primKey.substring(0, pos));

			String portletId = primKey.substring(
				pos + PortletImpl.LAYOUT_SEPARATOR.length() , primKey.length());

			if (!PortletPermissionUtil.contains(
					permissionChecker, plid, portletId,
					ActionKeys.CONFIGURATION)) {

				throw new PrincipalException();
			}
		}
		else if (!permissionChecker.hasPermission(
					groupId, name, primKey, ActionKeys.PERMISSIONS) &&
				 !permissionChecker.hasPermission(
					groupId, name, primKey, ActionKeys.DEFINE_PERMISSIONS)) {

			throw new PrincipalException();
		}
	}

}
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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.OrganizationLocalServiceUtil;

import java.util.List;

/**
 * <a href="GroupPermissionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupPermissionImpl implements GroupPermission {

	public void check(
			PermissionChecker permissionChecker, long groupId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, groupId, actionId)) {
			throw new PrincipalException();
		}
	}

	public boolean contains(
			PermissionChecker permissionChecker, long groupId, String actionId)
		throws PortalException, SystemException {

		if (actionId.equals(ActionKeys.MANAGE_LAYOUTS)) {
			Group group = GroupLocalServiceUtil.getGroup(groupId);

			if (group.isOrganization()) {
				long organizationId = group.getClassPK();

				return OrganizationPermissionUtil.contains(
					permissionChecker, organizationId, actionId);
			}
			else if (group.isUser()) {

				// An individual user would never reach this block because he
				// would be an administrator of his own layouts. However, a user
				// who manages a set of organizations may be modifying pages of
				// a user he manages.

				long userId = group.getClassPK();

				List organizations =
					OrganizationLocalServiceUtil.getUserOrganizations(
						userId);

				for (int i = 0; i < organizations.size(); i++) {
					Organization organization =
						(Organization)organizations.get(i);

					if (OrganizationPermissionUtil.contains(
							permissionChecker, organization.getOrganizationId(),
							ActionKeys.MANAGE_USERS)) {

						return true;
					}
				}
			}
		}

		// Group id must be set so that users can modify their personal pages

		return permissionChecker.hasPermission(
			groupId, Group.class.getName(), groupId, actionId);
	}

}
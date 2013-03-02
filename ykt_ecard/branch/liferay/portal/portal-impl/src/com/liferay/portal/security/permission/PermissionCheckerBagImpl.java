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

package com.liferay.portal.security.permission;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.security.permission.PermissionCheckerBag;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.service.OrganizationLocalServiceUtil;
import com.liferay.portal.service.UserGroupRoleLocalServiceUtil;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * <a href="PermissionCheckerBagImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionCheckerBagImpl implements PermissionCheckerBag {

	public PermissionCheckerBagImpl() {
	}

	public PermissionCheckerBagImpl(
		long userId, List userGroups, List userOrgs, List userOrgGroups,
		List userUserGroupGroups, List groups, List roles) {

		_userId = userId;
		_userGroups = userGroups;
		_userOrgs = userOrgs;
		_userOrgGroups = userOrgGroups;
		_userUserGroupGroups = userUserGroupGroups;
		_groups = groups;
		_roles = roles;
	}

	public List getUserGroups() {
		return _userGroups;
	}

	public List getUserOrgs() {
		return _userOrgs;
	}

	public List getUserOrgGroups() {
		return _userOrgGroups;
	}

	public List getUserUserGroupGroups() {
		return _userUserGroupGroups;
	}

	public List getGroups() {
		return _groups;
	}

	public List getRoles() {
		return _roles;
	}

	public boolean isCommunityAdmin(
			PermissionChecker permissionChecker, Object groupObj)
		throws Exception {

		Group group = (Group)groupObj;

		String key = String.valueOf(group.getGroupId());

		Boolean value = (Boolean)_communityAdmins.get(key);

		if (value == null) {
			value = Boolean.valueOf(
				isCommunityAdminImpl(permissionChecker, group));

			_communityAdmins.put(key, value);
		}

		return value.booleanValue();
	}

	public boolean isCommunityOwner(
			PermissionChecker permissionChecker, Object groupObj)
		throws Exception {

		Group group = (Group)groupObj;

		String key = String.valueOf(group.getGroupId());

		Boolean value = (Boolean)_communityOwners.get(key);

		if (value == null) {
			value = Boolean.valueOf(
				isCommunityOwnerImpl(permissionChecker, group));

			_communityOwners.put(key, value);
		}

		return value.booleanValue();
	}

	protected boolean isCommunityAdminImpl(
			PermissionChecker permissionChecker, Group group)
		throws PortalException, SystemException {

		if (group.isCommunity()) {
			if (UserGroupRoleLocalServiceUtil.hasUserGroupRole(
					_userId, group.getGroupId(),
					RoleImpl.COMMUNITY_ADMINISTRATOR) ||
				UserGroupRoleLocalServiceUtil.hasUserGroupRole(
					_userId, group.getGroupId(), RoleImpl.COMMUNITY_OWNER)) {

				return true;
			}
		}
		else if (group.isOrganization()) {
			long organizationId = group.getClassPK();

			while (organizationId !=
						OrganizationImpl.DEFAULT_PARENT_ORGANIZATION_ID) {

				Organization organization =
					OrganizationLocalServiceUtil.getOrganization(
						organizationId);

				Group organizationGroup = organization.getGroup();

				long organizationGroupId = organizationGroup.getGroupId();

				if (UserGroupRoleLocalServiceUtil.hasUserGroupRole(
						_userId, organizationGroupId,
						RoleImpl.ORGANIZATION_ADMINISTRATOR) ||
					UserGroupRoleLocalServiceUtil.hasUserGroupRole(
						_userId, organizationGroupId,
						RoleImpl.ORGANIZATION_OWNER)) {

					return true;
				}

				organizationId = organization.getParentOrganizationId();
			}
		}
		else if (group.isUser()) {
			long userId = group.getClassPK();

			if (userId == _userId) {
				return true;
			}
		}

		return false;
	}

	protected boolean isCommunityOwnerImpl(
			PermissionChecker permissionChecker, Group group)
		throws PortalException, SystemException {

		if (group.isCommunity()) {
			if (UserGroupRoleLocalServiceUtil.hasUserGroupRole(
					_userId, group.getGroupId(), RoleImpl.COMMUNITY_OWNER)) {

				return true;
			}
		}
		else if (group.isOrganization()) {
			long organizationId = group.getClassPK();

			while (organizationId !=
						OrganizationImpl.DEFAULT_PARENT_ORGANIZATION_ID) {

				Organization organization =
					OrganizationLocalServiceUtil.getOrganization(
						organizationId);

				Group organizationGroup = organization.getGroup();

				long organizationGroupId = organizationGroup.getGroupId();

				if (UserGroupRoleLocalServiceUtil.hasUserGroupRole(
						_userId, organizationGroupId,
						RoleImpl.ORGANIZATION_OWNER)) {

					return true;
				}

				organizationId = organization.getParentOrganizationId();
			}
		}
		else if (group.isUser()) {
			long userId = group.getClassPK();

			if (userId == _userId) {
				return true;
			}
		}

		return false;
	}

	private long _userId;
	private List _userGroups;
	private List _userOrgs;
	private List _userOrgGroups;
	private List _userUserGroupGroups;
	private List _groups;
	private List _roles;
	private Map _communityAdmins = new HashMap();
	private Map _communityOwners = new HashMap();

}
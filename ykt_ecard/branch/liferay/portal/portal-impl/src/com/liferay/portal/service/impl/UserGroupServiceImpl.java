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
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.service.base.UserGroupServiceBaseImpl;
import com.liferay.portal.service.permission.GroupPermissionUtil;
import com.liferay.portal.service.permission.PortalPermissionUtil;
import com.liferay.portal.service.permission.UserGroupPermissionUtil;

import java.util.List;

/**
 * <a href="UserGroupServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class UserGroupServiceImpl extends UserGroupServiceBaseImpl {

	public void addGroupUserGroups(long groupId, long[] userGroupIds)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);

		userGroupLocalService.addGroupUserGroups(groupId, userGroupIds);
	}

	public UserGroup addUserGroup(String name, String description)
		throws PortalException, SystemException {

		PortalPermissionUtil.check(
			getPermissionChecker(), ActionKeys.ADD_USER_GROUP);

		User user = getUser();

		return userGroupLocalService.addUserGroup(
			user.getUserId(), user.getCompanyId(), name, description);
	}

	public void deleteUserGroup(long userGroupId)
		throws PortalException, SystemException {

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.DELETE);

		userGroupLocalService.deleteUserGroup(userGroupId);
	}

	public UserGroup getUserGroup(long userGroupId)
		throws PortalException, SystemException {

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.VIEW);

		return userGroupLocalService.getUserGroup(userGroupId);
	}

	public UserGroup getUserGroup(String name)
		throws PortalException, SystemException {

		UserGroup userGroup = userGroupLocalService.getUserGroup(
			getUser().getCompanyId(), name);

		long userGroupId = userGroup.getUserGroupId();

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.VIEW);

		return userGroup;
	}

	public List getUserUserGroups(long userId)
		throws PortalException, SystemException {

		return userGroupLocalService.getUserUserGroups(userId);
	}

	public void unsetGroupUserGroups(long groupId, long[] userGroupIds)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);

		userGroupLocalService.unsetGroupUserGroups(groupId, userGroupIds);
	}

	public UserGroup updateUserGroup(
			long userGroupId, String name, String description)
		throws PortalException, SystemException {

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.UPDATE);

		return userGroupLocalService.updateUserGroup(
			getUser().getCompanyId(), userGroupId, name, description);
	}

}
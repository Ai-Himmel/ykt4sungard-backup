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
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.kernel.security.permission.PermissionChecker;

/**
 * <a href="GroupPermissionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupPermissionUtil {

	public static void check(
			PermissionChecker permissionChecker, long groupId, String actionId)
		throws PortalException, SystemException {

		getGroupPermission().check(permissionChecker, groupId, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long groupId, String actionId)
		throws PortalException, SystemException {

		return getGroupPermission().contains(
			permissionChecker, groupId, actionId);
	}

	public static GroupPermission getGroupPermission() {
		return _getUtil()._groupPermission;
	}

	public void setGroupPermission(GroupPermission groupPermission) {
		_groupPermission = groupPermission;
	}

	private static GroupPermissionUtil _getUtil() {
		if (_util == null) {
			_util = (GroupPermissionUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = GroupPermissionUtil.class.getName();

	private static GroupPermissionUtil _util;

	private GroupPermission _groupPermission;

}
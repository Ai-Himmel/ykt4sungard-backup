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
import com.liferay.portal.model.Portlet;

/**
 * <a href="PortletPermissionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPermissionUtil {

	public static void check(
			PermissionChecker permissionChecker, String portletId,
			String actionId)
		throws PortalException, SystemException {

		getPortletPermission().check(permissionChecker, portletId, actionId);
	}

	public static void check(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId)
		throws PortalException, SystemException {

		getPortletPermission().check(
			permissionChecker, plid, portletId, actionId);
	}

	public static void check(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId, boolean strict)
		throws PortalException, SystemException {

		getPortletPermission().check(
			permissionChecker, plid, portletId, actionId, strict);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, String portletId,
			String actionId)
		throws PortalException, SystemException {

		return getPortletPermission().contains(
			permissionChecker, portletId, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId)
		throws PortalException, SystemException {

		return getPortletPermission().contains(
			permissionChecker, plid, portletId, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId, boolean strict)
		throws PortalException, SystemException {

		return getPortletPermission().contains(
			permissionChecker, plid, portletId, actionId, strict);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long plid, Portlet portlet,
			String actionId)
		throws PortalException, SystemException {

		return getPortletPermission().contains(
			permissionChecker, plid, portlet, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long plid, Portlet portlet,
			String actionId, boolean strict)
		throws PortalException, SystemException {

		return getPortletPermission().contains(
			permissionChecker, plid, portlet, actionId, strict);
	}

	public static PortletPermission getPortletPermission() {
		return _getUtil()._portletPermission;
	}

	public static String getPrimaryKey(long plid, String portletId) {
		return getPortletPermission().getPrimaryKey(plid, portletId);
	}

	public static boolean hasLayoutManagerPermission(
		String portletId, String actionId) {

		return getPortletPermission().hasLayoutManagerPermission(
			portletId, actionId);
	}

	public void setPortletPermission(PortletPermission portletPermission) {
		_portletPermission = portletPermission;
	}

	private static PortletPermissionUtil _getUtil() {
		if (_util == null) {
			_util = (PortletPermissionUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PortletPermissionUtil.class.getName();

	private static PortletPermissionUtil _util;

	private PortletPermission _portletPermission;

}
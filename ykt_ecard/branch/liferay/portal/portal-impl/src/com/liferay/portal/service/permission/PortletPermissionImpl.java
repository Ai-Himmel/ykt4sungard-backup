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
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.security.permission.ResourceActionsUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletPermissionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPermissionImpl implements PortletPermission {

	public static final boolean DEFAULT_STRICT = false;

	public void check(
			PermissionChecker permissionChecker, String portletId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, portletId, actionId)) {
			throw new PrincipalException();
		}
	}

	public void check(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId)
		throws PortalException, SystemException {

		check(permissionChecker, plid, portletId, actionId, DEFAULT_STRICT);
	}

	public void check(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId, boolean strict)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, plid, portletId, actionId, strict)) {
			throw new PrincipalException();
		}
	}

	public boolean contains(
			PermissionChecker permissionChecker, String portletId,
			String actionId)
		throws PortalException, SystemException {

		return contains(permissionChecker, 0, portletId, actionId);
	}

	public boolean contains(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId)
		throws PortalException, SystemException {

		return contains(
			permissionChecker, plid, portletId, actionId, DEFAULT_STRICT);
	}

	public boolean contains(
			PermissionChecker permissionChecker, long plid, String portletId,
			String actionId, boolean strict)
		throws PortalException, SystemException {

		long groupId = 0;
		String name = null;
		String primKey = null;

		if (plid > 0) {
			Layout layout = LayoutLocalServiceUtil.getLayout(plid);

			groupId = layout.getGroupId();
			name = PortletImpl.getRootPortletId(portletId);
			primKey = getPrimaryKey(plid, portletId);

			if (!strict) {
				if (LayoutPermissionUtil.contains(
						permissionChecker, groupId, layout.isPrivateLayout(),
						layout.getLayoutId(), ActionKeys.UPDATE) &&
					hasLayoutManagerPermission(portletId, actionId)) {

					return true;
				}
			}
		}
		else {
			name = portletId;
			primKey = portletId;
		}

		return permissionChecker.hasPermission(
			groupId, name, primKey, actionId);
	}

	public boolean contains(
			PermissionChecker permissionChecker, long plid, Portlet portlet,
			String actionId)
		throws PortalException, SystemException {

		return contains(
			permissionChecker, plid, portlet, actionId, DEFAULT_STRICT);
	}

	public boolean contains(
			PermissionChecker permissionChecker, long plid, Portlet portlet,
			String actionId, boolean strict)
		throws PortalException, SystemException {

		boolean value = contains(
			permissionChecker, plid, portlet.getPortletId(), actionId, strict);

		if (value) {
			return true;
		}
		else {
			if (portlet.isSystem() && actionId.equals(ActionKeys.VIEW)) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	public String getPrimaryKey(long plid, String portletId) {
		StringMaker sm = new StringMaker();

		sm.append(plid);
		sm.append(PortletImpl.LAYOUT_SEPARATOR);
		sm.append(portletId);

		return sm.toString();
	}

	public boolean hasLayoutManagerPermission(
		String portletId, String actionId) {

		try {
			return hasLayoutManagerPermissionImpl(portletId, actionId);
		}
		catch (Exception e) {
			_log.error(e, e);

			return false;
		}
	}

	protected boolean hasLayoutManagerPermissionImpl(
			String portletId, String actionId)
		throws SystemException {

		portletId = PortletImpl.getRootPortletId(portletId);

		List layoutManagerActions =
			ResourceActionsUtil.getPortletResourceLayoutManagerActions(
				portletId);

		return layoutManagerActions.contains(actionId);
	}

	private static Log _log = LogFactory.getLog(PortletPermissionImpl.class);

}
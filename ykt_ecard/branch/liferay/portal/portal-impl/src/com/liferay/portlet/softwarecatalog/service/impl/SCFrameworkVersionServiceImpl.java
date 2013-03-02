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

package com.liferay.portlet.softwarecatalog.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion;
import com.liferay.portlet.softwarecatalog.service.base.SCFrameworkVersionServiceBaseImpl;
import com.liferay.portlet.softwarecatalog.service.permission.SCFrameworkVersionPermission;

import java.util.List;

/**
 * <a href="SCFrameworkVersionServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 *
 */
public class SCFrameworkVersionServiceImpl
	extends SCFrameworkVersionServiceBaseImpl {

	public SCFrameworkVersion addFrameworkVersion(
			long plid, String name, String url, boolean active, int priority,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SOFTWARE_CATALOG,
			ActionKeys.ADD_FRAMEWORK_VERSION);

		return scFrameworkVersionLocalService.addFrameworkVersion(
			getUserId(), plid, name, url, active, priority,
			addCommunityPermissions, addGuestPermissions);
	}

	public SCFrameworkVersion addFrameworkVersion(
			long plid, String name, String url, boolean active, int priority,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SOFTWARE_CATALOG,
			ActionKeys.ADD_FRAMEWORK_VERSION);

		return scFrameworkVersionLocalService.addFrameworkVersion(
			getUserId(), plid, name, url, active, priority,
			communityPermissions, guestPermissions);
	}

	public void deleteFrameworkVersion(long frameworkVersionId)
		throws PortalException, SystemException {

		SCFrameworkVersionPermission.check(
			getPermissionChecker(), frameworkVersionId, ActionKeys.DELETE);

		scFrameworkVersionLocalService.deleteFrameworkVersion(
			frameworkVersionId);
	}

	public SCFrameworkVersion getFrameworkVersion(long frameworkVersionId)
		throws PortalException, SystemException {

		return scFrameworkVersionLocalService.getFrameworkVersion(
			frameworkVersionId);
	}

	public List getFrameworkVersions(long groupId, boolean active)
		throws SystemException {

		return scFrameworkVersionLocalService.getFrameworkVersions(
			groupId, active);
	}

	public List getFrameworkVersions(
			long groupId, boolean active, int begin, int end)
		throws SystemException {

		return scFrameworkVersionLocalService.getFrameworkVersions(
			groupId, active, begin, end);
	}

	public SCFrameworkVersion updateFrameworkVersion(
			long frameworkVersionId, String name, String url, boolean active,
			int priority)
		throws PortalException, SystemException {

		SCFrameworkVersionPermission.check(
			getPermissionChecker(), frameworkVersionId, ActionKeys.UPDATE);

		return scFrameworkVersionLocalService.updateFrameworkVersion(
			frameworkVersionId, name, url, active, priority);
	}

}
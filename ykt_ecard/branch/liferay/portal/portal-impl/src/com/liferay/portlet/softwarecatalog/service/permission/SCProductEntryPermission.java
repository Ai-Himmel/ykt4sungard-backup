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

package com.liferay.portlet.softwarecatalog.service.permission;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portlet.softwarecatalog.model.SCProductEntry;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceUtil;

/**
 * <a href="SCProductEntryPermission.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductEntryPermission {

	public static void check(
			PermissionChecker permissionChecker, long productEntryId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, productEntryId, actionId)) {
			throw new PrincipalException();
		}
	}

	public static void check(
			PermissionChecker permissionChecker, SCProductEntry productEntry,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, productEntry, actionId)) {
			throw new PrincipalException();
		}
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long productEntryId,
			String actionId)
		throws PortalException, SystemException {

		SCProductEntry productEntry =
			SCProductEntryLocalServiceUtil.getProductEntry(productEntryId);

		return contains(permissionChecker, productEntry, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, SCProductEntry productEntry,
			String actionId)
		throws PortalException, SystemException {

		return permissionChecker.hasPermission(
			productEntry.getGroupId(), SCProductEntry.class.getName(),
			productEntry.getProductEntryId(), actionId);
	}

}
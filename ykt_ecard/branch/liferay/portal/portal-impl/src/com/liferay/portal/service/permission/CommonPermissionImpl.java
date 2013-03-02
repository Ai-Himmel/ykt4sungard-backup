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
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;

/**
 * <a href="CommonPermissionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class CommonPermissionImpl implements CommonPermission {

	public void check(
			PermissionChecker permissionChecker, long classNameId,
			long classPK, String actionId)
		throws PortalException, SystemException {

		String className = PortalUtil.getClassName(classNameId);

		check(permissionChecker, className, classPK, actionId);
	}

	public void check(
			PermissionChecker permissionChecker, String className,
			long classPK, String actionId)
		throws PortalException, SystemException {

		if (className.equals(Account.class.getName())) {
		}
		else if (className.equals(Contact.class.getName())) {
			User user = UserLocalServiceUtil.getUserByContactId(classPK);

			UserPermissionUtil.check(
				permissionChecker, user.getUserId(), user.getOrganizationIds(),
				actionId);
		}
		else if (className.equals(Organization.class.getName())) {
			OrganizationPermissionUtil.check(
				permissionChecker, classPK, actionId);
		}
		else {
			throw new PrincipalException();
		}
	}

}
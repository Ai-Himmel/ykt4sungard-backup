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

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.security.auth.PrincipalException;

/**
 * <a href="PasswordPolicyPermissionUtil.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PasswordPolicyPermissionUtil {

	public static void check(
			PermissionChecker permissionChecker, long passwordPolicyId,
			String actionId)
		throws PrincipalException {

		getPasswordPolicyPermission().check(
			permissionChecker, passwordPolicyId, actionId);
	}

	public static boolean contains(
		PermissionChecker permissionChecker, long passwordPolicyId,
		String actionId) {

		return getPasswordPolicyPermission().contains(
			permissionChecker, passwordPolicyId, actionId);
	}

	public static PasswordPolicyPermission getPasswordPolicyPermission() {
		return _getUtil()._passwordPolicyPermission;
	}

	public void setPasswordPolicyPermission(
		PasswordPolicyPermission passwordPolicyPermission) {

		_passwordPolicyPermission = passwordPolicyPermission;
	}

	private static PasswordPolicyPermissionUtil _getUtil() {
		if (_util == null) {
			_util = (PasswordPolicyPermissionUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL =
		PasswordPolicyPermissionUtil.class.getName();

	private static PasswordPolicyPermissionUtil _util;

	private PasswordPolicyPermission _passwordPolicyPermission;

}
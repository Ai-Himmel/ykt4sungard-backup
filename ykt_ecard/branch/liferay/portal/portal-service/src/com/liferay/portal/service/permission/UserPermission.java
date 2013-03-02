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

import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.security.auth.PrincipalException;

/**
 * <a href="UserPermission.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public interface UserPermission {

	public void check(
			PermissionChecker permissionChecker, long userId, String actionId)
		throws PrincipalException;

	/**
	 * @deprecated
	 */
	public void check(
			PermissionChecker permissionChecker, long userId,
			long organizationId, long locationId, String actionId)
		throws PrincipalException;

	public void check(
			PermissionChecker permissionChecker, long userId,
			long[] organizationIds, String actionId)
		throws PrincipalException;

	public boolean contains(
		PermissionChecker permissionChecker, long userId, String actionId);

	/**
	 * @deprecated
	 */
	public boolean contains(
		PermissionChecker permissionChecker, long userId, long organizationId,
		long locationId, String actionId);

	public boolean contains(
		PermissionChecker permissionChecker, long userId,
		long[] organizationIds, String actionId);

}
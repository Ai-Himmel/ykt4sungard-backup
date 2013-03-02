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

package com.liferay.portal.service.persistence;

/**
 * <a href="PermissionUserFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface PermissionUserFinder {
	public int countByOrgGroupPermissions(long companyId,
		java.lang.String name, java.lang.String primKey,
		java.lang.String actionId) throws com.liferay.portal.SystemException;

	public int countByPermissionAndRole(long companyId, long groupId,
		java.lang.String name, java.lang.String primKey,
		java.lang.String actionId, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String emailAddress, boolean andOperator)
		throws com.liferay.portal.SystemException;

	public int countByUserAndOrgGroupPermission(long companyId,
		java.lang.String name, java.lang.String primKey,
		java.lang.String actionId, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String emailAddress, boolean andOperator)
		throws com.liferay.portal.SystemException;

	public java.util.List findByPermissionAndRole(long companyId, long groupId,
		java.lang.String name, java.lang.String primKey,
		java.lang.String actionId, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String emailAddress, boolean andOperator, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUserAndOrgGroupPermission(long companyId,
		java.lang.String name, java.lang.String primKey,
		java.lang.String actionId, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String emailAddress, boolean andOperator, int begin, int end)
		throws com.liferay.portal.SystemException;
}
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
 * <a href="PermissionFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface PermissionFinder {
	public boolean containsPermissions_2(java.util.List permissions,
		long userId, java.util.List groups, long groupId)
		throws com.liferay.portal.SystemException;

	public boolean containsPermissions_4(java.util.List permissions,
		long userId, java.util.List groups, java.util.List roles)
		throws com.liferay.portal.SystemException;

	public int countByGroupsPermissions(java.util.List permissions,
		java.util.List groups) throws com.liferay.portal.SystemException;

	public int countByGroupsRoles(java.util.List permissions,
		java.util.List groups) throws com.liferay.portal.SystemException;

	public int countByRolesPermissions(java.util.List permissions,
		java.util.List roles) throws com.liferay.portal.SystemException;

	public int countByUserGroupRole(java.util.List permissions, long userId,
		long groupId) throws com.liferay.portal.SystemException;

	public int countByUsersPermissions(java.util.List permissions, long userId)
		throws com.liferay.portal.SystemException;

	public int countByUsersRoles(java.util.List permissions, long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByA_R(java.lang.String actionId,
		long[] resourceIds) throws com.liferay.portal.SystemException;

	public java.util.List findByG_R(long groupId, long resourceId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByR_R(long roleId, long resourceId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByU_R(long userId, long resourceId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByO_G_R(long organizationId, long groupId,
		long resourceId) throws com.liferay.portal.SystemException;

	public java.util.List findByU_A_R(long userId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByG_C_N_S_P(long groupId, long companyId,
		java.lang.String name, int scope, java.lang.String primKey)
		throws com.liferay.portal.SystemException;

	public java.util.List findByU_C_N_S_P(long userId, long companyId,
		java.lang.String name, int scope, java.lang.String primKey)
		throws com.liferay.portal.SystemException;
}
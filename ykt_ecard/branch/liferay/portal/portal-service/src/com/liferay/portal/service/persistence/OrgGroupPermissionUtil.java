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
 * <a href="OrgGroupPermissionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgGroupPermissionUtil {
	public static com.liferay.portal.model.OrgGroupPermission create(
		com.liferay.portal.service.persistence.OrgGroupPermissionPK orgGroupPermissionPK) {
		return getPersistence().create(orgGroupPermissionPK);
	}

	public static com.liferay.portal.model.OrgGroupPermission remove(
		com.liferay.portal.service.persistence.OrgGroupPermissionPK orgGroupPermissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().remove(orgGroupPermissionPK);
	}

	public static com.liferay.portal.model.OrgGroupPermission remove(
		com.liferay.portal.model.OrgGroupPermission orgGroupPermission)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(orgGroupPermission);
	}

	public static com.liferay.portal.model.OrgGroupPermission update(
		com.liferay.portal.model.OrgGroupPermission orgGroupPermission)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(orgGroupPermission);
	}

	public static com.liferay.portal.model.OrgGroupPermission update(
		com.liferay.portal.model.OrgGroupPermission orgGroupPermission,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(orgGroupPermission, merge);
	}

	public static com.liferay.portal.model.OrgGroupPermission updateImpl(
		com.liferay.portal.model.OrgGroupPermission orgGroupPermission,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(orgGroupPermission, merge);
	}

	public static com.liferay.portal.model.OrgGroupPermission findByPrimaryKey(
		com.liferay.portal.service.persistence.OrgGroupPermissionPK orgGroupPermissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByPrimaryKey(orgGroupPermissionPK);
	}

	public static com.liferay.portal.model.OrgGroupPermission fetchByPrimaryKey(
		com.liferay.portal.service.persistence.OrgGroupPermissionPK orgGroupPermissionPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(orgGroupPermissionPK);
	}

	public static java.util.List findByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portal.model.OrgGroupPermission findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portal.model.OrgGroupPermission findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portal.model.OrgGroupPermission[] findByGroupId_PrevAndNext(
		com.liferay.portal.service.persistence.OrgGroupPermissionPK orgGroupPermissionPK,
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByGroupId_PrevAndNext(orgGroupPermissionPK,
			groupId, obc);
	}

	public static java.util.List findByPermissionId(long permissionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByPermissionId(permissionId);
	}

	public static java.util.List findByPermissionId(long permissionId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByPermissionId(permissionId, begin, end);
	}

	public static java.util.List findByPermissionId(long permissionId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByPermissionId(permissionId, begin, end, obc);
	}

	public static com.liferay.portal.model.OrgGroupPermission findByPermissionId_First(
		long permissionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByPermissionId_First(permissionId, obc);
	}

	public static com.liferay.portal.model.OrgGroupPermission findByPermissionId_Last(
		long permissionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByPermissionId_Last(permissionId, obc);
	}

	public static com.liferay.portal.model.OrgGroupPermission[] findByPermissionId_PrevAndNext(
		com.liferay.portal.service.persistence.OrgGroupPermissionPK orgGroupPermissionPK,
		long permissionId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrgGroupPermissionException {
		return getPersistence().findByPermissionId_PrevAndNext(orgGroupPermissionPK,
			permissionId, obc);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByPermissionId(long permissionId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByPermissionId(permissionId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByPermissionId(long permissionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByPermissionId(permissionId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static OrgGroupPermissionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(OrgGroupPermissionPersistence persistence) {
		_persistence = persistence;
	}

	private static OrgGroupPermissionUtil _getUtil() {
		if (_util == null) {
			_util = (OrgGroupPermissionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = OrgGroupPermissionUtil.class.getName();
	private static OrgGroupPermissionUtil _util;
	private OrgGroupPermissionPersistence _persistence;
}
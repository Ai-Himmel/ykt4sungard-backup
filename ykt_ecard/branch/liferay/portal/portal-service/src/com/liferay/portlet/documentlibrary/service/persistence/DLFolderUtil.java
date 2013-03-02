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

package com.liferay.portlet.documentlibrary.service.persistence;

/**
 * <a href="DLFolderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFolderUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFolder create(
		long folderId) {
		return getPersistence().create(folderId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder remove(
		long folderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().remove(folderId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder remove(
		com.liferay.portlet.documentlibrary.model.DLFolder dlFolder)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(dlFolder);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder update(
		com.liferay.portlet.documentlibrary.model.DLFolder dlFolder)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFolder);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder update(
		com.liferay.portlet.documentlibrary.model.DLFolder dlFolder,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFolder, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFolder dlFolder,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(dlFolder, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByPrimaryKey(
		long folderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByPrimaryKey(folderId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder fetchByPrimaryKey(
		long folderId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(folderId);
	}

	public static java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder[] findByUuid_PrevAndNext(
		long folderId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByUuid_PrevAndNext(folderId, uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder fetchByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByUUID_G(uuid, groupId);
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

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder[] findByGroupId_PrevAndNext(
		long folderId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByGroupId_PrevAndNext(folderId, groupId, obc);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder[] findByCompanyId_PrevAndNext(
		long folderId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByCompanyId_PrevAndNext(folderId,
			companyId, obc);
	}

	public static java.util.List findByG_P(long groupId, long parentFolderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, parentFolderId);
	}

	public static java.util.List findByG_P(long groupId, long parentFolderId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, parentFolderId, begin, end);
	}

	public static java.util.List findByG_P(long groupId, long parentFolderId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, parentFolderId, begin, end,
			obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByG_P_First(
		long groupId, long parentFolderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByG_P_First(groupId, parentFolderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByG_P_Last(
		long groupId, long parentFolderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByG_P_Last(groupId, parentFolderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder[] findByG_P_PrevAndNext(
		long folderId, long groupId, long parentFolderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByG_P_PrevAndNext(folderId, groupId,
			parentFolderId, obc);
	}

	public static java.util.List findByP_N(long parentFolderId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		return getPersistence().findByP_N(parentFolderId, name);
	}

	public static java.util.List findByP_N(long parentFolderId,
		java.lang.String name, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByP_N(parentFolderId, name, begin, end);
	}

	public static java.util.List findByP_N(long parentFolderId,
		java.lang.String name, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByP_N(parentFolderId, name, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByP_N_First(
		long parentFolderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByP_N_First(parentFolderId, name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByP_N_Last(
		long parentFolderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByP_N_Last(parentFolderId, name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder[] findByP_N_PrevAndNext(
		long folderId, long parentFolderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByP_N_PrevAndNext(folderId, parentFolderId,
			name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder findByG_P_N(
		long groupId, long parentFolderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		return getPersistence().findByG_P_N(groupId, parentFolderId, name);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolder fetchByG_P_N(
		long groupId, long parentFolderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_P_N(groupId, parentFolderId, name);
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

	public static void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUuid(uuid);
	}

	public static void removeByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByG_P(long groupId, long parentFolderId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P(groupId, parentFolderId);
	}

	public static void removeByP_N(long parentFolderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByP_N(parentFolderId, name);
	}

	public static void removeByG_P_N(long groupId, long parentFolderId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFolderException {
		getPersistence().removeByG_P_N(groupId, parentFolderId, name);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUUID_G(uuid, groupId);
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByG_P(long groupId, long parentFolderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P(groupId, parentFolderId);
	}

	public static int countByP_N(long parentFolderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByP_N(parentFolderId, name);
	}

	public static int countByG_P_N(long groupId, long parentFolderId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_N(groupId, parentFolderId, name);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static DLFolderPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DLFolderPersistence persistence) {
		_persistence = persistence;
	}

	private static DLFolderUtil _getUtil() {
		if (_util == null) {
			_util = (DLFolderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DLFolderUtil.class.getName();
	private static DLFolderUtil _util;
	private DLFolderPersistence _persistence;
}
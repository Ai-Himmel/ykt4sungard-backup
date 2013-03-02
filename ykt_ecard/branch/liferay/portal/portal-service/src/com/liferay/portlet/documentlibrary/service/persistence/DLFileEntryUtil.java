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
 * <a href="DLFileEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileEntryUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileEntry create(
		long fileEntryId) {
		return getPersistence().create(fileEntryId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry remove(
		long fileEntryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().remove(fileEntryId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry remove(
		com.liferay.portlet.documentlibrary.model.DLFileEntry dlFileEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(dlFileEntry);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry update(
		com.liferay.portlet.documentlibrary.model.DLFileEntry dlFileEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileEntry);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry update(
		com.liferay.portlet.documentlibrary.model.DLFileEntry dlFileEntry,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileEntry, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFileEntry dlFileEntry,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(dlFileEntry, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByPrimaryKey(
		long fileEntryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByPrimaryKey(fileEntryId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry fetchByPrimaryKey(
		long fileEntryId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(fileEntryId);
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

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry[] findByUuid_PrevAndNext(
		long fileEntryId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByUuid_PrevAndNext(fileEntryId, uuid, obc);
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

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry[] findByCompanyId_PrevAndNext(
		long fileEntryId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByCompanyId_PrevAndNext(fileEntryId,
			companyId, obc);
	}

	public static java.util.List findByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByFolderId(folderId);
	}

	public static java.util.List findByFolderId(long folderId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByFolderId(folderId, begin, end);
	}

	public static java.util.List findByFolderId(long folderId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByFolderId(folderId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByFolderId_First(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByFolderId_First(folderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByFolderId_Last(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByFolderId_Last(folderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry[] findByFolderId_PrevAndNext(
		long fileEntryId, long folderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByFolderId_PrevAndNext(fileEntryId,
			folderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByF_N(
		long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByF_N(folderId, name);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry fetchByF_N(
		long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByF_N(folderId, name);
	}

	public static java.util.List findByF_T(long folderId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByF_T(folderId, title);
	}

	public static java.util.List findByF_T(long folderId,
		java.lang.String title, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByF_T(folderId, title, begin, end);
	}

	public static java.util.List findByF_T(long folderId,
		java.lang.String title, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByF_T(folderId, title, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByF_T_First(
		long folderId, java.lang.String title,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByF_T_First(folderId, title, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry findByF_T_Last(
		long folderId, java.lang.String title,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByF_T_Last(folderId, title, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry[] findByF_T_PrevAndNext(
		long fileEntryId, long folderId, java.lang.String title,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		return getPersistence().findByF_T_PrevAndNext(fileEntryId, folderId,
			title, obc);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByFolderId(folderId);
	}

	public static void removeByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileEntryException {
		getPersistence().removeByF_N(folderId, name);
	}

	public static void removeByF_T(long folderId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByF_T(folderId, title);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByFolderId(folderId);
	}

	public static int countByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByF_N(folderId, name);
	}

	public static int countByF_T(long folderId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByF_T(folderId, title);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static DLFileEntryPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DLFileEntryPersistence persistence) {
		_persistence = persistence;
	}

	private static DLFileEntryUtil _getUtil() {
		if (_util == null) {
			_util = (DLFileEntryUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DLFileEntryUtil.class.getName();
	private static DLFileEntryUtil _util;
	private DLFileEntryPersistence _persistence;
}
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
 * <a href="DLFileShortcutUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileShortcutUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut create(
		long fileShortcutId) {
		return getPersistence().create(fileShortcutId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut remove(
		long fileShortcutId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().remove(fileShortcutId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut remove(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut dlFileShortcut)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(dlFileShortcut);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut update(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut dlFileShortcut)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileShortcut);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut update(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut dlFileShortcut,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileShortcut, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut dlFileShortcut,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(dlFileShortcut, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByPrimaryKey(
		long fileShortcutId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByPrimaryKey(fileShortcutId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut fetchByPrimaryKey(
		long fileShortcutId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(fileShortcutId);
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

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut[] findByUuid_PrevAndNext(
		long fileShortcutId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByUuid_PrevAndNext(fileShortcutId, uuid, obc);
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

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByFolderId_First(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByFolderId_First(folderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByFolderId_Last(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByFolderId_Last(folderId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut[] findByFolderId_PrevAndNext(
		long fileShortcutId, long folderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByFolderId_PrevAndNext(fileShortcutId,
			folderId, obc);
	}

	public static java.util.List findByTF_TN(long toFolderId,
		java.lang.String toName) throws com.liferay.portal.SystemException {
		return getPersistence().findByTF_TN(toFolderId, toName);
	}

	public static java.util.List findByTF_TN(long toFolderId,
		java.lang.String toName, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByTF_TN(toFolderId, toName, begin, end);
	}

	public static java.util.List findByTF_TN(long toFolderId,
		java.lang.String toName, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByTF_TN(toFolderId, toName, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByTF_TN_First(
		long toFolderId, java.lang.String toName,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByTF_TN_First(toFolderId, toName, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut findByTF_TN_Last(
		long toFolderId, java.lang.String toName,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByTF_TN_Last(toFolderId, toName, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut[] findByTF_TN_PrevAndNext(
		long fileShortcutId, long toFolderId, java.lang.String toName,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileShortcutException {
		return getPersistence().findByTF_TN_PrevAndNext(fileShortcutId,
			toFolderId, toName, obc);
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

	public static void removeByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByFolderId(folderId);
	}

	public static void removeByTF_TN(long toFolderId, java.lang.String toName)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByTF_TN(toFolderId, toName);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByFolderId(folderId);
	}

	public static int countByTF_TN(long toFolderId, java.lang.String toName)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByTF_TN(toFolderId, toName);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static DLFileShortcutPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DLFileShortcutPersistence persistence) {
		_persistence = persistence;
	}

	private static DLFileShortcutUtil _getUtil() {
		if (_util == null) {
			_util = (DLFileShortcutUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DLFileShortcutUtil.class.getName();
	private static DLFileShortcutUtil _util;
	private DLFileShortcutPersistence _persistence;
}
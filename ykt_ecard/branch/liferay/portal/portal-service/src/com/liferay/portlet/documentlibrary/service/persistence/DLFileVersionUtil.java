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
 * <a href="DLFileVersionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileVersionUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileVersion create(
		long fileVersionId) {
		return getPersistence().create(fileVersionId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion remove(
		long fileVersionId)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		return getPersistence().remove(fileVersionId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion remove(
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(dlFileVersion);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion update(
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileVersion);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion update(
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileVersion, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(dlFileVersion, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion findByPrimaryKey(
		long fileVersionId)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByPrimaryKey(fileVersionId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion fetchByPrimaryKey(
		long fileVersionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(fileVersionId);
	}

	public static java.util.List findByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByF_N(folderId, name);
	}

	public static java.util.List findByF_N(long folderId,
		java.lang.String name, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByF_N(folderId, name, begin, end);
	}

	public static java.util.List findByF_N(long folderId,
		java.lang.String name, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByF_N(folderId, name, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion findByF_N_First(
		long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByF_N_First(folderId, name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion findByF_N_Last(
		long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByF_N_Last(folderId, name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion[] findByF_N_PrevAndNext(
		long fileVersionId, long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByF_N_PrevAndNext(fileVersionId, folderId,
			name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion findByF_N_V(
		long folderId, java.lang.String name, double version)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		return getPersistence().findByF_N_V(folderId, name, version);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileVersion fetchByF_N_V(
		long folderId, java.lang.String name, double version)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByF_N_V(folderId, name, version);
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

	public static void removeByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByF_N(folderId, name);
	}

	public static void removeByF_N_V(long folderId, java.lang.String name,
		double version)
		throws com.liferay.portlet.documentlibrary.NoSuchFileVersionException, 
			com.liferay.portal.SystemException {
		getPersistence().removeByF_N_V(folderId, name, version);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByF_N(folderId, name);
	}

	public static int countByF_N_V(long folderId, java.lang.String name,
		double version) throws com.liferay.portal.SystemException {
		return getPersistence().countByF_N_V(folderId, name, version);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static DLFileVersionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DLFileVersionPersistence persistence) {
		_persistence = persistence;
	}

	private static DLFileVersionUtil _getUtil() {
		if (_util == null) {
			_util = (DLFileVersionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DLFileVersionUtil.class.getName();
	private static DLFileVersionUtil _util;
	private DLFileVersionPersistence _persistence;
}
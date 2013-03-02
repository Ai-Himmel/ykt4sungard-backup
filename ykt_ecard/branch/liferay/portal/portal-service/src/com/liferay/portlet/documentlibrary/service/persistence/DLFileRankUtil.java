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
 * <a href="DLFileRankUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileRankUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileRank create(
		long fileRankId) {
		return getPersistence().create(fileRankId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank remove(
		long fileRankId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().remove(fileRankId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank remove(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(dlFileRank);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank update(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileRank);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank update(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(dlFileRank, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(dlFileRank, merge);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByPrimaryKey(
		long fileRankId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByPrimaryKey(fileRankId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank fetchByPrimaryKey(
		long fileRankId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(fileRankId);
	}

	public static java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId);
	}

	public static java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank[] findByUserId_PrevAndNext(
		long fileRankId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByUserId_PrevAndNext(fileRankId, userId, obc);
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

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByF_N_First(
		long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByF_N_First(folderId, name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByF_N_Last(
		long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByF_N_Last(folderId, name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank[] findByF_N_PrevAndNext(
		long fileRankId, long folderId, java.lang.String name,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByF_N_PrevAndNext(fileRankId, folderId,
			name, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByC_U_F_N(
		long companyId, long userId, long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		return getPersistence().findByC_U_F_N(companyId, userId, folderId, name);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank fetchByC_U_F_N(
		long companyId, long userId, long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_U_F_N(companyId, userId, folderId, name);
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

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByF_N(folderId, name);
	}

	public static void removeByC_U_F_N(long companyId, long userId,
		long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.documentlibrary.NoSuchFileRankException {
		getPersistence().removeByC_U_F_N(companyId, userId, folderId, name);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countByF_N(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByF_N(folderId, name);
	}

	public static int countByC_U_F_N(long companyId, long userId,
		long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_U_F_N(companyId, userId, folderId, name);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static DLFileRankPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DLFileRankPersistence persistence) {
		_persistence = persistence;
	}

	private static DLFileRankUtil _getUtil() {
		if (_util == null) {
			_util = (DLFileRankUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DLFileRankUtil.class.getName();
	private static DLFileRankUtil _util;
	private DLFileRankPersistence _persistence;
}
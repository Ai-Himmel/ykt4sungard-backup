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
 * <a href="LayoutUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutUtil {
	public static com.liferay.portal.model.Layout create(long plid) {
		return getPersistence().create(plid);
	}

	public static com.liferay.portal.model.Layout remove(long plid)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().remove(plid);
	}

	public static com.liferay.portal.model.Layout remove(
		com.liferay.portal.model.Layout layout)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(layout);
	}

	public static com.liferay.portal.model.Layout update(
		com.liferay.portal.model.Layout layout)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(layout);
	}

	public static com.liferay.portal.model.Layout update(
		com.liferay.portal.model.Layout layout, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(layout, merge);
	}

	public static com.liferay.portal.model.Layout updateImpl(
		com.liferay.portal.model.Layout layout, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(layout, merge);
	}

	public static com.liferay.portal.model.Layout findByPrimaryKey(long plid)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByPrimaryKey(plid);
	}

	public static com.liferay.portal.model.Layout fetchByPrimaryKey(long plid)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(plid);
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

	public static com.liferay.portal.model.Layout findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portal.model.Layout findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portal.model.Layout[] findByGroupId_PrevAndNext(
		long plid, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByGroupId_PrevAndNext(plid, groupId, obc);
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

	public static com.liferay.portal.model.Layout findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Layout findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Layout[] findByCompanyId_PrevAndNext(
		long plid, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByCompanyId_PrevAndNext(plid, companyId, obc);
	}

	public static com.liferay.portal.model.Layout findByDLFolderId(
		long dlFolderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByDLFolderId(dlFolderId);
	}

	public static com.liferay.portal.model.Layout fetchByDLFolderId(
		long dlFolderId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByDLFolderId(dlFolderId);
	}

	public static com.liferay.portal.model.Layout findByIconImageId(
		long iconImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByIconImageId(iconImageId);
	}

	public static com.liferay.portal.model.Layout fetchByIconImageId(
		long iconImageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByIconImageId(iconImageId);
	}

	public static java.util.List findByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, privateLayout);
	}

	public static java.util.List findByG_P(long groupId, boolean privateLayout,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, privateLayout, begin, end);
	}

	public static java.util.List findByG_P(long groupId, boolean privateLayout,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P(groupId, privateLayout, begin, end,
			obc);
	}

	public static com.liferay.portal.model.Layout findByG_P_First(
		long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_First(groupId, privateLayout, obc);
	}

	public static com.liferay.portal.model.Layout findByG_P_Last(long groupId,
		boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_Last(groupId, privateLayout, obc);
	}

	public static com.liferay.portal.model.Layout[] findByG_P_PrevAndNext(
		long plid, long groupId, boolean privateLayout,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_PrevAndNext(plid, groupId,
			privateLayout, obc);
	}

	public static com.liferay.portal.model.Layout findByG_P_L(long groupId,
		boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_L(groupId, privateLayout, layoutId);
	}

	public static com.liferay.portal.model.Layout fetchByG_P_L(long groupId,
		boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_P_L(groupId, privateLayout, layoutId);
	}

	public static java.util.List findByG_P_P(long groupId,
		boolean privateLayout, long parentLayoutId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_P(groupId, privateLayout,
			parentLayoutId);
	}

	public static java.util.List findByG_P_P(long groupId,
		boolean privateLayout, long parentLayoutId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_P(groupId, privateLayout,
			parentLayoutId, begin, end);
	}

	public static java.util.List findByG_P_P(long groupId,
		boolean privateLayout, long parentLayoutId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_P_P(groupId, privateLayout,
			parentLayoutId, begin, end, obc);
	}

	public static com.liferay.portal.model.Layout findByG_P_P_First(
		long groupId, boolean privateLayout, long parentLayoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_P_First(groupId, privateLayout,
			parentLayoutId, obc);
	}

	public static com.liferay.portal.model.Layout findByG_P_P_Last(
		long groupId, boolean privateLayout, long parentLayoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_P_Last(groupId, privateLayout,
			parentLayoutId, obc);
	}

	public static com.liferay.portal.model.Layout[] findByG_P_P_PrevAndNext(
		long plid, long groupId, boolean privateLayout, long parentLayoutId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_P_PrevAndNext(plid, groupId,
			privateLayout, parentLayoutId, obc);
	}

	public static com.liferay.portal.model.Layout findByG_P_F(long groupId,
		boolean privateLayout, java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		return getPersistence().findByG_P_F(groupId, privateLayout, friendlyURL);
	}

	public static com.liferay.portal.model.Layout fetchByG_P_F(long groupId,
		boolean privateLayout, java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_P_F(groupId, privateLayout, friendlyURL);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByDLFolderId(long dlFolderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		getPersistence().removeByDLFolderId(dlFolderId);
	}

	public static void removeByIconImageId(long iconImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		getPersistence().removeByIconImageId(iconImageId);
	}

	public static void removeByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P(groupId, privateLayout);
	}

	public static void removeByG_P_L(long groupId, boolean privateLayout,
		long layoutId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		getPersistence().removeByG_P_L(groupId, privateLayout, layoutId);
	}

	public static void removeByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId) throws com.liferay.portal.SystemException {
		getPersistence().removeByG_P_P(groupId, privateLayout, parentLayoutId);
	}

	public static void removeByG_P_F(long groupId, boolean privateLayout,
		java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchLayoutException {
		getPersistence().removeByG_P_F(groupId, privateLayout, friendlyURL);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByDLFolderId(long dlFolderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByDLFolderId(dlFolderId);
	}

	public static int countByIconImageId(long iconImageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByIconImageId(iconImageId);
	}

	public static int countByG_P(long groupId, boolean privateLayout)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P(groupId, privateLayout);
	}

	public static int countByG_P_L(long groupId, boolean privateLayout,
		long layoutId) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_L(groupId, privateLayout, layoutId);
	}

	public static int countByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_P(groupId, privateLayout,
			parentLayoutId);
	}

	public static int countByG_P_F(long groupId, boolean privateLayout,
		java.lang.String friendlyURL) throws com.liferay.portal.SystemException {
		return getPersistence().countByG_P_F(groupId, privateLayout, friendlyURL);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static LayoutPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(LayoutPersistence persistence) {
		_persistence = persistence;
	}

	private static LayoutUtil _getUtil() {
		if (_util == null) {
			_util = (LayoutUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = LayoutUtil.class.getName();
	private static LayoutUtil _util;
	private LayoutPersistence _persistence;
}
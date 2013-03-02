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
 * <a href="ActivityTrackerUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActivityTrackerUtil {
	public static com.liferay.portal.model.ActivityTracker create(
		long activityTrackerId) {
		return getPersistence().create(activityTrackerId);
	}

	public static com.liferay.portal.model.ActivityTracker remove(
		long activityTrackerId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().remove(activityTrackerId);
	}

	public static com.liferay.portal.model.ActivityTracker remove(
		com.liferay.portal.model.ActivityTracker activityTracker)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(activityTracker);
	}

	public static com.liferay.portal.model.ActivityTracker update(
		com.liferay.portal.model.ActivityTracker activityTracker)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(activityTracker);
	}

	public static com.liferay.portal.model.ActivityTracker update(
		com.liferay.portal.model.ActivityTracker activityTracker, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(activityTracker, merge);
	}

	public static com.liferay.portal.model.ActivityTracker updateImpl(
		com.liferay.portal.model.ActivityTracker activityTracker, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(activityTracker, merge);
	}

	public static com.liferay.portal.model.ActivityTracker findByPrimaryKey(
		long activityTrackerId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByPrimaryKey(activityTrackerId);
	}

	public static com.liferay.portal.model.ActivityTracker fetchByPrimaryKey(
		long activityTrackerId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(activityTrackerId);
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

	public static com.liferay.portal.model.ActivityTracker findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker[] findByGroupId_PrevAndNext(
		long activityTrackerId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByGroupId_PrevAndNext(activityTrackerId,
			groupId, obc);
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

	public static com.liferay.portal.model.ActivityTracker findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker[] findByCompanyId_PrevAndNext(
		long activityTrackerId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByCompanyId_PrevAndNext(activityTrackerId,
			companyId, obc);
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

	public static com.liferay.portal.model.ActivityTracker findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker[] findByUserId_PrevAndNext(
		long activityTrackerId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByUserId_PrevAndNext(activityTrackerId,
			userId, obc);
	}

	public static java.util.List findByReceiverUserId(long receiverUserId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByReceiverUserId(receiverUserId);
	}

	public static java.util.List findByReceiverUserId(long receiverUserId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByReceiverUserId(receiverUserId, begin, end);
	}

	public static java.util.List findByReceiverUserId(long receiverUserId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByReceiverUserId(receiverUserId, begin,
			end, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByReceiverUserId_First(
		long receiverUserId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByReceiverUserId_First(receiverUserId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByReceiverUserId_Last(
		long receiverUserId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByReceiverUserId_Last(receiverUserId, obc);
	}

	public static com.liferay.portal.model.ActivityTracker[] findByReceiverUserId_PrevAndNext(
		long activityTrackerId, long receiverUserId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByReceiverUserId_PrevAndNext(activityTrackerId,
			receiverUserId, obc);
	}

	public static java.util.List findByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(classNameId, classPK);
	}

	public static java.util.List findByC_C(long classNameId, long classPK,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(classNameId, classPK, begin, end);
	}

	public static java.util.List findByC_C(long classNameId, long classPK,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(classNameId, classPK, begin, end, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByC_C_First(
		long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByC_C_First(classNameId, classPK, obc);
	}

	public static com.liferay.portal.model.ActivityTracker findByC_C_Last(
		long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByC_C_Last(classNameId, classPK, obc);
	}

	public static com.liferay.portal.model.ActivityTracker[] findByC_C_PrevAndNext(
		long activityTrackerId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchActivityTrackerException {
		return getPersistence().findByC_C_PrevAndNext(activityTrackerId,
			classNameId, classPK, obc);
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

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeByReceiverUserId(long receiverUserId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByReceiverUserId(receiverUserId);
	}

	public static void removeByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C(classNameId, classPK);
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

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countByReceiverUserId(long receiverUserId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByReceiverUserId(receiverUserId);
	}

	public static int countByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C(classNameId, classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static ActivityTrackerPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ActivityTrackerPersistence persistence) {
		_persistence = persistence;
	}

	private static ActivityTrackerUtil _getUtil() {
		if (_util == null) {
			_util = (ActivityTrackerUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ActivityTrackerUtil.class.getName();
	private static ActivityTrackerUtil _util;
	private ActivityTrackerPersistence _persistence;
}
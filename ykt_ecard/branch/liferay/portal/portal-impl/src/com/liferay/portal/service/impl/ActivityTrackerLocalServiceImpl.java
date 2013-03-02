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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.ActivityTracker;
import com.liferay.portal.model.User;
import com.liferay.portal.service.base.ActivityTrackerLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;

import java.util.Date;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ActivityTrackerLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActivityTrackerLocalServiceImpl
	extends ActivityTrackerLocalServiceBaseImpl {

	public ActivityTracker addActivityTracker(
			long userId, long groupId, String className, long classPK,
			String activity, String extraData, long receiverUserId)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);

		String receiverUserName = StringPool.BLANK;

		if (receiverUserId > 0) {
			try {
				User receiverUser = userPersistence.findByPrimaryKey(
					receiverUserId);

				receiverUserName = receiverUser.getFullName();
			}
			catch (NoSuchUserException nsue) {
				if (_log.isWarnEnabled()) {
					_log.warn(nsue);
				}
			}
		}

		long activityTrackerId = counterLocalService.increment(
			ActivityTracker.class.getName());

		ActivityTracker activityTracker = activityTrackerPersistence.create(
			activityTrackerId);

		activityTracker.setGroupId(groupId);
		activityTracker.setCompanyId(user.getCompanyId());
		activityTracker.setUserId(user.getUserId());
		activityTracker.setUserName(user.getFullName());
		activityTracker.setCreateDate(new Date());
		activityTracker.setClassNameId(classNameId);
		activityTracker.setClassPK(classPK);
		activityTracker.setActivity(activity);
		activityTracker.setExtraData(extraData);
		activityTracker.setReceiverUserId(receiverUserId);
		activityTracker.setReceiverUserName(receiverUserName);

		activityTrackerPersistence.update(activityTracker);

		return activityTracker;
	}

	public void deleteActivityTrackers(String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		activityTrackerPersistence.removeByC_C(classNameId, classPK);
	}

	public List getCompanyActivityTrackers(long companyId, int begin, int end)
		throws SystemException {

		return activityTrackerPersistence.findByCompanyId(
			companyId, begin, end);
	}

	public int getCompanyActivityTrackersCount(long companyId)
		throws SystemException {

		return activityTrackerPersistence.countByCompanyId(companyId);
	}

	public List getGroupActivityTrackers(long groupId, int begin, int end)
		throws SystemException {

		return activityTrackerPersistence.findByGroupId(groupId, begin, end);
	}

	public int getGroupActivityTrackersCount(long groupId)
		throws SystemException {

		return activityTrackerPersistence.countByGroupId(groupId);
	}

	public List getUserActivityTrackers(long userId, int begin, int end)
		throws SystemException {

		return activityTrackerFinder.findByU_R(userId, userId, begin, end);
	}

	public int getUserActivityTrackersCount(long userId)
		throws SystemException {

		return activityTrackerFinder.countByU_R(userId, userId);
	}

	private static Log _log =
		LogFactory.getLog(ActivityTrackerLocalServiceImpl.class);

}
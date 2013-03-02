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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.model.UserTrackerPath;
import com.liferay.portal.service.base.UserTrackerLocalServiceBaseImpl;
import com.liferay.portal.util.PropsValues;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="UserTrackerLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserTrackerLocalServiceImpl
	extends UserTrackerLocalServiceBaseImpl {

	public UserTracker addUserTracker(
			long companyId, long userId, Date modifiedDate, String sessionId,
			String remoteAddr, String remoteHost, String userAgent,
			List userTrackerPaths)
		throws SystemException {

		if (PropsValues.SESSION_TRACKER_PERSISTENCE_ENABLED) {
			long userTrackerId = counterLocalService.increment(
				UserTracker.class.getName());

			UserTracker userTracker =
				userTrackerPersistence.create(userTrackerId);

			userTracker.setCompanyId(companyId);
			userTracker.setUserId(userId);
			userTracker.setModifiedDate(modifiedDate);
			userTracker.setSessionId(sessionId);
			userTracker.setRemoteAddr(remoteAddr);
			userTracker.setRemoteHost(remoteHost);
			userTracker.setUserAgent(userAgent);

			userTrackerPersistence.update(userTracker);

			Iterator itr = userTrackerPaths.iterator();

			while (itr.hasNext()) {
				UserTrackerPath userTrackerPath = (UserTrackerPath)itr.next();

				long pathId = counterLocalService.increment(
					UserTrackerPath.class.getName());

				userTrackerPath.setUserTrackerPathId(pathId);
				userTrackerPath.setUserTrackerId(userTrackerId);

				userTrackerPathPersistence.update(userTrackerPath);
			}

			return userTracker;
		}
		else {
			return null;
		}
	}

	public void deleteUserTracker(long userTrackerId)
		throws PortalException, SystemException {

		// Paths

		userTrackerPathPersistence.removeByUserTrackerId(userTrackerId);

		// User tracker

		userTrackerPersistence.remove(userTrackerId);
	}

	public List getUserTrackers(long companyId, int begin, int end)
		throws SystemException {

		return userTrackerPersistence.findByCompanyId(companyId, begin, end);
	}

}
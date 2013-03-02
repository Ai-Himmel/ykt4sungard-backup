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

package com.liferay.portlet.messageboards.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.messageboards.model.MBStatsUser;
import com.liferay.portlet.messageboards.service.base.MBStatsUserLocalServiceBaseImpl;

import java.util.Date;
import java.util.List;

/**
 * <a href="MBStatsUserLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBStatsUserLocalServiceImpl
	extends MBStatsUserLocalServiceBaseImpl {

	public void deleteStatsUserByGroupId(long groupId)
		throws SystemException {

		mbStatsUserPersistence.removeByGroupId(groupId);
	}

	public void deleteStatsUserByUserId(long userId) throws SystemException {
		mbStatsUserPersistence.removeByUserId(userId);
	}

	public MBStatsUser getStatsUser(long groupId, long userId)
		throws PortalException, SystemException {

		MBStatsUser statsUser = mbStatsUserPersistence.fetchByG_U(
			groupId, userId);

		if (statsUser == null) {
			long statsUserId = counterLocalService.increment();

			statsUser = mbStatsUserPersistence.create(statsUserId);

			statsUser.setGroupId(groupId);
			statsUser.setUserId(userId);

			mbStatsUserPersistence.update(statsUser);
		}

		return statsUser;
	}

	public List getStatsUsers(long groupId, int begin, int end)
		throws SystemException {

		return mbStatsUserPersistence.findByG_M(groupId, 0, begin, end);
	}

	public int getStatsUsersCount(long groupId) throws SystemException {
		return mbStatsUserPersistence.countByG_M(groupId, 0);
	}

	public void updateStatsUser(long groupId, long userId)
		throws PortalException, SystemException {

		MBStatsUser statsUser = getStatsUser(groupId, userId);

		statsUser.setMessageCount(statsUser.getMessageCount() + 1);
		statsUser.setLastPostDate(new Date());

		mbStatsUserPersistence.update(statsUser);
	}

}
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

package com.liferay.portal.util;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.UserTrackerLocalServiceUtil;
import com.liferay.portal.service.persistence.UserTrackerUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LiveUsers.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class LiveUsers {

	public static void deleteGroup(long groupId) {
		_instance._deleteGroup(groupId);
	}

	public static Set getGroupUsers(long groupId) {
		return _instance._getGroupUsers(_instance._getLiveUsers(), groupId);
	}

	public static int getGroupUsersCount(long groupId) {
		return getGroupUsers(groupId).size();
	}

	public static Map getSessionUsers() {
		return _instance._getSessionUsers(_instance._getLiveUsers());
	}

	public static int getSessionUsersCount() {
		return getSessionUsers().size();
	}

	public static UserTracker getUserTracker(String sesId) {
		return _instance._getUserTracker(sesId);
	}

	public static void joinGroup(long userId, long groupId) {
		_instance._joinGroup(userId, groupId);
	}

	public static void joinGroup(long[] userIds, long groupId) {
		_instance._joinGroup(userIds, groupId);
	}

	public static void leaveGroup(long userId, long groupId) {
		_instance._leaveGroup(userId, groupId);
	}

	public static void leaveGroup(long[] userIds, long groupId) {
		_instance._leaveGroup(userIds, groupId);
	}

	public static void signIn(HttpServletRequest req) throws SystemException {
		_instance._signIn(req);
	}

	public static void signOut(String sesId, long userId)
		throws SystemException {

		_instance._signOut(sesId, userId);
	}

	private LiveUsers() {
	}

	private void _addUserTracker(long userId, UserTracker userTracker) {
		List userTrackers = _getUserTrackers(userId);

		if (userTrackers != null) {
			userTrackers.add(userTracker);
		}
		else {
			userTrackers = new ArrayList();

			userTrackers.add(userTracker);

			Map userTrackersMap = _getUserTrackersMap();

			userTrackersMap.put(new Long(userId), userTrackers);
		}
	}

	private void _deleteGroup(long groupId) {
		Map liveUsers = _getLiveUsers();

		liveUsers.remove(new Long(groupId));
	}

	private Set _getGroupUsers(Map liveUsers, long groupId) {
		Long groupIdObj = new Long(groupId);

		Set groupUsers = (Set)liveUsers.get(groupIdObj);

		if (groupUsers == null) {
			groupUsers = CollectionFactory.getSyncHashSet();

			liveUsers.put(groupIdObj, groupUsers);
		}

		return groupUsers;
	}

	private Map _getLiveUsers() {
		String companyIdString = String.valueOf(
			CompanyThreadLocal.getCompanyId());

		Map liveUsers = (Map)WebAppPool.get(
			companyIdString, WebKeys.LIVE_USERS);

		if (liveUsers == null) {
			liveUsers = CollectionFactory.getSyncHashMap();

			WebAppPool.put(companyIdString, WebKeys.LIVE_USERS, liveUsers);
		}

		return liveUsers;
	}

	private Map _getSessionUsers(Map liveUsers) {
		Long groupIdObj = new Long(0);

		Map sessionUsers = (Map)liveUsers.get(groupIdObj);

		if (sessionUsers == null) {
			sessionUsers = CollectionFactory.getSyncHashMap();

			liveUsers.put(groupIdObj, sessionUsers);
		}

		return sessionUsers;
	}

	private UserTracker _getUserTracker(String sesId) {
		Map liveUsers = _getLiveUsers();

		Map sessionUsers = _getSessionUsers(liveUsers);

		return (UserTracker)sessionUsers.get(sesId);
	}

	private List _getUserTrackers(long userId) {
		Map userTrackersMap = _getUserTrackersMap();

		return (List)userTrackersMap.get(new Long(userId));
	}

	private Map _getUserTrackersMap() {
		Map liveUsers = _getLiveUsers();

		Long groupIdObj = new Long(-1);

		Map userTrackersMap = (Map)liveUsers.get(groupIdObj);

		if (userTrackersMap == null) {
			userTrackersMap = CollectionFactory.getSyncHashMap();

			liveUsers.put(groupIdObj, userTrackersMap);
		}

		return userTrackersMap;
	}

	private void _joinGroup(long userId, long groupId) {
		Map liveUsers = _getLiveUsers();

		Set groupUsers = _getGroupUsers(liveUsers, groupId);

		if (_getUserTrackers(userId) != null) {
			groupUsers.add(new Long(userId));
		}
	}

	private void _joinGroup(long[] userIds, long groupId) {
		Map liveUsers = _getLiveUsers();

		Set groupUsers = _getGroupUsers(liveUsers, groupId);

		for (int i = 0; i < userIds.length; i++) {
			long userId = userIds[i];

			if (_getUserTrackers(userId) != null) {
				groupUsers.add(new Long(userId));
			}
		}
	}

	private void _leaveGroup(long userId, long groupId) {
		Map liveUsers = _getLiveUsers();

		Set groupUsers = _getGroupUsers(liveUsers, groupId);

		groupUsers.remove(new Long(userId));
	}

	private void _leaveGroup(long[] userIds, long groupId) {
		Map liveUsers = _getLiveUsers();

		Set groupUsers = _getGroupUsers(liveUsers, groupId);

		for (int i = 0; i < userIds.length; i++) {
			long userId = userIds[i];

			groupUsers.remove(new Long(userId));
		}
	}

	private void _removeUserTracker(long userId, UserTracker userTracker) {
		List userTrackers = _getUserTrackers(userId);

		if (userTrackers != null) {
			Iterator itr = userTrackers.iterator();

			while (itr.hasNext()) {
				UserTracker curUserTracker = (UserTracker)itr.next();

				if (userTracker.equals(curUserTracker)) {
					itr.remove();
				}
			}

			if (userTrackers.size() == 0) {
				Map userTrackersMap = _getUserTrackersMap();

				userTrackersMap.remove(new Long(userId));
			}
		}
	}

	private void _signIn(HttpServletRequest req) throws SystemException {
		HttpSession ses = req.getSession();

		long companyId = CompanyThreadLocal.getCompanyId();
		long userId = GetterUtil.getLong(req.getRemoteUser());

		Map liveUsers = _updateGroupStatus(userId, true);

		Map sessionUsers = _getSessionUsers(liveUsers);

		List userTrackers = _getUserTrackers(userId);

		if (!PropsValues.AUTH_SIMULTANEOUS_LOGINS) {
			if (userTrackers != null) {
				for (int i = 0; i < userTrackers.size(); i++) {
					UserTracker userTracker = (UserTracker)userTrackers.get(i);

					// Disable old login

					userTracker.getHttpSession().setAttribute(
						WebKeys.STALE_SESSION, Boolean.TRUE);
				}
			}
		}

		UserTracker userTracker = (UserTracker)sessionUsers.get(ses.getId());

		if ((userTracker == null) &&
			(PropsValues.SESSION_TRACKER_MEMORY_ENABLED)) {

			userTracker = UserTrackerUtil.create(0);

			userTracker.setCompanyId(companyId);
			userTracker.setUserId(userId);
			userTracker.setModifiedDate(new Date());
			userTracker.setHttpSession(ses);
			userTracker.setRemoteAddr(req.getRemoteAddr());
			userTracker.setRemoteHost(req.getRemoteHost());
			userTracker.setUserAgent(req.getHeader(HttpHeaders.USER_AGENT));

			sessionUsers.put(ses.getId(), userTracker);

			_addUserTracker(userId, userTracker);
		}
	}

	private void _signOut(String sesId, long userId) throws SystemException {
		List userTrackers = _getUserTrackers(userId);

		Map liveUsers = null;

		if ((userTrackers == null) || (userTrackers.size() <= 1)) {
			liveUsers = _updateGroupStatus(userId, false);
		}

		if (liveUsers == null) {
			liveUsers = _getLiveUsers();
		}

		Map sessionUsers = _getSessionUsers(liveUsers);

		UserTracker userTracker = (UserTracker)sessionUsers.remove(sesId);

		if (userTracker != null) {
			try {
				UserTrackerLocalServiceUtil.addUserTracker(
					userTracker.getCompanyId(), userTracker.getUserId(),
					userTracker.getModifiedDate(), sesId,
					userTracker.getRemoteAddr(), userTracker.getRemoteHost(),
					userTracker.getUserAgent(), userTracker.getPaths());
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e.getMessage());
				}
			}

			_removeUserTracker(userId, userTracker);
		}
	}

	private Map _updateGroupStatus(long userId, boolean signedIn)
		throws SystemException {

		Long userIdObj = new Long(userId);

		long companyId = CompanyThreadLocal.getCompanyId();

		Map liveUsers = _getLiveUsers();

		LinkedHashMap groupParams = new LinkedHashMap();

		groupParams.put("usersGroups", userIdObj);

		List communities = GroupLocalServiceUtil.search(
			companyId, null, null, groupParams, QueryUtil.ALL_POS,
			QueryUtil.ALL_POS);

		for (int i = 0; i < communities.size(); i++) {
			Group community = (Group)communities.get(i);

			Set groupUsers = _getGroupUsers(liveUsers, community.getGroupId());

			if (signedIn) {
				groupUsers.add(userIdObj);
			}
			else {
				groupUsers.remove(userIdObj);
			}
		}

		return liveUsers;
	}

	private static Log _log = LogFactory.getLog(LiveUsers.class);

	private static LiveUsers _instance = new LiveUsers();

}
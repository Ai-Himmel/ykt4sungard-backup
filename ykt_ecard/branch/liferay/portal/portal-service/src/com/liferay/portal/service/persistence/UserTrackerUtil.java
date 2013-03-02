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
 * <a href="UserTrackerUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserTrackerUtil {
	public static com.liferay.portal.model.UserTracker create(
		long userTrackerId) {
		return getPersistence().create(userTrackerId);
	}

	public static com.liferay.portal.model.UserTracker remove(
		long userTrackerId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().remove(userTrackerId);
	}

	public static com.liferay.portal.model.UserTracker remove(
		com.liferay.portal.model.UserTracker userTracker)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(userTracker);
	}

	public static com.liferay.portal.model.UserTracker update(
		com.liferay.portal.model.UserTracker userTracker)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(userTracker);
	}

	public static com.liferay.portal.model.UserTracker update(
		com.liferay.portal.model.UserTracker userTracker, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(userTracker, merge);
	}

	public static com.liferay.portal.model.UserTracker updateImpl(
		com.liferay.portal.model.UserTracker userTracker, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(userTracker, merge);
	}

	public static com.liferay.portal.model.UserTracker findByPrimaryKey(
		long userTrackerId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByPrimaryKey(userTrackerId);
	}

	public static com.liferay.portal.model.UserTracker fetchByPrimaryKey(
		long userTrackerId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(userTrackerId);
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

	public static com.liferay.portal.model.UserTracker findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.UserTracker findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.UserTracker[] findByCompanyId_PrevAndNext(
		long userTrackerId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByCompanyId_PrevAndNext(userTrackerId,
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

	public static com.liferay.portal.model.UserTracker findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.UserTracker findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.UserTracker[] findByUserId_PrevAndNext(
		long userTrackerId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findByUserId_PrevAndNext(userTrackerId, userId,
			obc);
	}

	public static java.util.List findBySessionId(java.lang.String sessionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySessionId(sessionId);
	}

	public static java.util.List findBySessionId(java.lang.String sessionId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findBySessionId(sessionId, begin, end);
	}

	public static java.util.List findBySessionId(java.lang.String sessionId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySessionId(sessionId, begin, end, obc);
	}

	public static com.liferay.portal.model.UserTracker findBySessionId_First(
		java.lang.String sessionId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findBySessionId_First(sessionId, obc);
	}

	public static com.liferay.portal.model.UserTracker findBySessionId_Last(
		java.lang.String sessionId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findBySessionId_Last(sessionId, obc);
	}

	public static com.liferay.portal.model.UserTracker[] findBySessionId_PrevAndNext(
		long userTrackerId, java.lang.String sessionId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserTrackerException {
		return getPersistence().findBySessionId_PrevAndNext(userTrackerId,
			sessionId, obc);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeBySessionId(java.lang.String sessionId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeBySessionId(sessionId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countBySessionId(java.lang.String sessionId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countBySessionId(sessionId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static UserTrackerPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(UserTrackerPersistence persistence) {
		_persistence = persistence;
	}

	private static UserTrackerUtil _getUtil() {
		if (_util == null) {
			_util = (UserTrackerUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = UserTrackerUtil.class.getName();
	private static UserTrackerUtil _util;
	private UserTrackerPersistence _persistence;
}
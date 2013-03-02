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
 * <a href="PasswordTrackerUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PasswordTrackerUtil {
	public static com.liferay.portal.model.PasswordTracker create(
		long passwordTrackerId) {
		return getPersistence().create(passwordTrackerId);
	}

	public static com.liferay.portal.model.PasswordTracker remove(
		long passwordTrackerId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordTrackerException {
		return getPersistence().remove(passwordTrackerId);
	}

	public static com.liferay.portal.model.PasswordTracker remove(
		com.liferay.portal.model.PasswordTracker passwordTracker)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(passwordTracker);
	}

	public static com.liferay.portal.model.PasswordTracker update(
		com.liferay.portal.model.PasswordTracker passwordTracker)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(passwordTracker);
	}

	public static com.liferay.portal.model.PasswordTracker update(
		com.liferay.portal.model.PasswordTracker passwordTracker, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(passwordTracker, merge);
	}

	public static com.liferay.portal.model.PasswordTracker updateImpl(
		com.liferay.portal.model.PasswordTracker passwordTracker, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(passwordTracker, merge);
	}

	public static com.liferay.portal.model.PasswordTracker findByPrimaryKey(
		long passwordTrackerId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordTrackerException {
		return getPersistence().findByPrimaryKey(passwordTrackerId);
	}

	public static com.liferay.portal.model.PasswordTracker fetchByPrimaryKey(
		long passwordTrackerId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(passwordTrackerId);
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

	public static com.liferay.portal.model.PasswordTracker findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordTrackerException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.PasswordTracker findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordTrackerException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.PasswordTracker[] findByUserId_PrevAndNext(
		long passwordTrackerId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPasswordTrackerException {
		return getPersistence().findByUserId_PrevAndNext(passwordTrackerId,
			userId, obc);
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

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PasswordTrackerPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PasswordTrackerPersistence persistence) {
		_persistence = persistence;
	}

	private static PasswordTrackerUtil _getUtil() {
		if (_util == null) {
			_util = (PasswordTrackerUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PasswordTrackerUtil.class.getName();
	private static PasswordTrackerUtil _util;
	private PasswordTrackerPersistence _persistence;
}
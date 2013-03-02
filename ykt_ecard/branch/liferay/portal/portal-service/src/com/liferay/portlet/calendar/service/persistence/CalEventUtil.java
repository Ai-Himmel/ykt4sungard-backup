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

package com.liferay.portlet.calendar.service.persistence;

/**
 * <a href="CalEventUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalEventUtil {
	public static com.liferay.portlet.calendar.model.CalEvent create(
		long eventId) {
		return getPersistence().create(eventId);
	}

	public static com.liferay.portlet.calendar.model.CalEvent remove(
		long eventId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().remove(eventId);
	}

	public static com.liferay.portlet.calendar.model.CalEvent remove(
		com.liferay.portlet.calendar.model.CalEvent calEvent)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(calEvent);
	}

	public static com.liferay.portlet.calendar.model.CalEvent update(
		com.liferay.portlet.calendar.model.CalEvent calEvent)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(calEvent);
	}

	public static com.liferay.portlet.calendar.model.CalEvent update(
		com.liferay.portlet.calendar.model.CalEvent calEvent, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(calEvent, merge);
	}

	public static com.liferay.portlet.calendar.model.CalEvent updateImpl(
		com.liferay.portlet.calendar.model.CalEvent calEvent, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(calEvent, merge);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByPrimaryKey(
		long eventId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByPrimaryKey(eventId);
	}

	public static com.liferay.portlet.calendar.model.CalEvent fetchByPrimaryKey(
		long eventId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(eventId);
	}

	public static java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByUuid_PrevAndNext(
		long eventId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByUuid_PrevAndNext(eventId, uuid, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.calendar.model.CalEvent fetchByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByUUID_G(uuid, groupId);
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

	public static com.liferay.portlet.calendar.model.CalEvent findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByGroupId_PrevAndNext(
		long eventId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByGroupId_PrevAndNext(eventId, groupId, obc);
	}

	public static java.util.List findByG_T(long groupId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_T(groupId, type);
	}

	public static java.util.List findByG_T(long groupId, java.lang.String type,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_T(groupId, type, begin, end);
	}

	public static java.util.List findByG_T(long groupId, java.lang.String type,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_T(groupId, type, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_T_First(
		long groupId, java.lang.String type,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByG_T_First(groupId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_T_Last(
		long groupId, java.lang.String type,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByG_T_Last(groupId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_T_PrevAndNext(
		long eventId, long groupId, java.lang.String type,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByG_T_PrevAndNext(eventId, groupId, type,
			obc);
	}

	public static java.util.List findByG_R(long groupId, boolean repeating)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_R(groupId, repeating);
	}

	public static java.util.List findByG_R(long groupId, boolean repeating,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_R(groupId, repeating, begin, end);
	}

	public static java.util.List findByG_R(long groupId, boolean repeating,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_R(groupId, repeating, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_R_First(
		long groupId, boolean repeating,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByG_R_First(groupId, repeating, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_R_Last(
		long groupId, boolean repeating,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByG_R_Last(groupId, repeating, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_R_PrevAndNext(
		long eventId, long groupId, boolean repeating,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		return getPersistence().findByG_R_PrevAndNext(eventId, groupId,
			repeating, obc);
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

	public static void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUuid(uuid);
	}

	public static void removeByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.calendar.NoSuchEventException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByG_T(long groupId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_T(groupId, type);
	}

	public static void removeByG_R(long groupId, boolean repeating)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_R(groupId, repeating);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUUID_G(uuid, groupId);
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByG_T(long groupId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_T(groupId, type);
	}

	public static int countByG_R(long groupId, boolean repeating)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_R(groupId, repeating);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static CalEventPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CalEventPersistence persistence) {
		_persistence = persistence;
	}

	private static CalEventUtil _getUtil() {
		if (_util == null) {
			_util = (CalEventUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CalEventUtil.class.getName();
	private static CalEventUtil _util;
	private CalEventPersistence _persistence;
}
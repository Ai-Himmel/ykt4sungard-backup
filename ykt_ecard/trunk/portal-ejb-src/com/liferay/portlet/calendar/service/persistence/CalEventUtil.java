/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CalEventUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.calendar.model.CalEvent"),
			"com.liferay.portlet.calendar.service.persistence.CalEventPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.calendar.model.CalEvent"));

	public static com.liferay.portlet.calendar.model.CalEvent create(
		java.lang.String eventId) {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(eventId);
	}

	public static com.liferay.portlet.calendar.model.CalEvent remove(
		java.lang.String eventId)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(eventId));
		}

		com.liferay.portlet.calendar.model.CalEvent calEvent = persistence.remove(eventId);

		if (listener != null) {
			listener.onAfterRemove(calEvent);
		}

		return calEvent;
	}

	public static com.liferay.portlet.calendar.model.CalEvent update(
		com.liferay.portlet.calendar.model.CalEvent calEvent)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = calEvent.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(calEvent);
			}
			else {
				listener.onBeforeUpdate(calEvent);
			}
		}

		calEvent = persistence.update(calEvent);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(calEvent);
			}
			else {
				listener.onAfterUpdate(calEvent);
			}
		}

		return calEvent;
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByPrimaryKey(
		java.lang.String eventId)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(eventId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByGroupId_PrevAndNext(
		java.lang.String eventId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(eventId, groupId, obc);
	}

	public static java.util.List findByC_T(java.lang.String companyId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_T(companyId, type);
	}

	public static java.util.List findByC_T(java.lang.String companyId,
		java.lang.String type, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_T(companyId, type, begin, end);
	}

	public static java.util.List findByC_T(java.lang.String companyId,
		java.lang.String type, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_T(companyId, type, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByC_T_First(
		java.lang.String companyId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_T_First(companyId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByC_T_Last(
		java.lang.String companyId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_T_Last(companyId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByC_T_PrevAndNext(
		java.lang.String eventId, java.lang.String companyId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_T_PrevAndNext(eventId, companyId, type, obc);
	}

	public static java.util.List findByC_U_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_T(companyId, userId, type);
	}

	public static java.util.List findByC_U_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String type, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_T(companyId, userId, type, begin, end);
	}

	public static java.util.List findByC_U_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String type, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_T(companyId, userId, type, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByC_U_T_First(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_T_First(companyId, userId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByC_U_T_Last(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_T_Last(companyId, userId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByC_U_T_PrevAndNext(
		java.lang.String eventId, java.lang.String companyId,
		java.lang.String userId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_T_PrevAndNext(eventId, companyId, userId,
			type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByC_U_D_T(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String description, java.lang.String type)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U_D_T(companyId, userId, description, type);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId, begin, end);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_U_First(
		java.lang.String groupId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_First(groupId, userId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_U_Last(
		java.lang.String groupId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_Last(groupId, userId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_U_PrevAndNext(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_PrevAndNext(eventId, groupId, userId, obc);
	}

	public static java.util.List findByG_T(java.lang.String groupId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_T(groupId, type);
	}

	public static java.util.List findByG_T(java.lang.String groupId,
		java.lang.String type, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_T(groupId, type, begin, end);
	}

	public static java.util.List findByG_T(java.lang.String groupId,
		java.lang.String type, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_T(groupId, type, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_T_First(
		java.lang.String groupId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_T_First(groupId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_T_Last(
		java.lang.String groupId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_T_Last(groupId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_T_PrevAndNext(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_T_PrevAndNext(eventId, groupId, type, obc);
	}

	public static java.util.List findByG_U_T(java.lang.String groupId,
		java.lang.String userId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_T(groupId, userId, type);
	}

	public static java.util.List findByG_U_T(java.lang.String groupId,
		java.lang.String userId, java.lang.String type, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_T(groupId, userId, type, begin, end);
	}

	public static java.util.List findByG_U_T(java.lang.String groupId,
		java.lang.String userId, java.lang.String type, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_T(groupId, userId, type, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_U_T_First(
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_T_First(groupId, userId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_U_T_Last(
		java.lang.String groupId, java.lang.String userId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_T_Last(groupId, userId, type, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_U_T_PrevAndNext(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String userId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_T_PrevAndNext(eventId, groupId, userId,
			type, obc);
	}

	public static java.util.List findByG_C_R(java.lang.String groupId,
		java.lang.String companyId, boolean repeating)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_R(groupId, companyId, repeating);
	}

	public static java.util.List findByG_C_R(java.lang.String groupId,
		java.lang.String companyId, boolean repeating, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_R(groupId, companyId, repeating, begin, end);
	}

	public static java.util.List findByG_C_R(java.lang.String groupId,
		java.lang.String companyId, boolean repeating, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_R(groupId, companyId, repeating, begin,
			end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_C_R_First(
		java.lang.String groupId, java.lang.String companyId,
		boolean repeating, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_R_First(groupId, companyId, repeating, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_C_R_Last(
		java.lang.String groupId, java.lang.String companyId,
		boolean repeating, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_R_Last(groupId, companyId, repeating, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_C_R_PrevAndNext(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String companyId, boolean repeating,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_R_PrevAndNext(eventId, groupId, companyId,
			repeating, obc);
	}

	public static java.util.List findByG_U_R(java.lang.String groupId,
		java.lang.String userId, boolean repeating)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_R(groupId, userId, repeating);
	}

	public static java.util.List findByG_U_R(java.lang.String groupId,
		java.lang.String userId, boolean repeating, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_R(groupId, userId, repeating, begin, end);
	}

	public static java.util.List findByG_U_R(java.lang.String groupId,
		java.lang.String userId, boolean repeating, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_R(groupId, userId, repeating, begin, end,
			obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_U_R_First(
		java.lang.String groupId, java.lang.String userId, boolean repeating,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_R_First(groupId, userId, repeating, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent findByG_U_R_Last(
		java.lang.String groupId, java.lang.String userId, boolean repeating,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_R_Last(groupId, userId, repeating, obc);
	}

	public static com.liferay.portlet.calendar.model.CalEvent[] findByG_U_R_PrevAndNext(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String userId, boolean repeating,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_R_PrevAndNext(eventId, groupId, userId,
			repeating, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByC_T(java.lang.String companyId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_T(companyId, type);
	}

	public static void removeByC_U_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_U_T(companyId, userId, type);
	}

	public static void removeByC_U_D_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String description,
		java.lang.String type)
		throws com.liferay.portlet.calendar.NoSuchEventException, 
			com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_U_D_T(companyId, userId, description, type);
	}

	public static void removeByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U(groupId, userId);
	}

	public static void removeByG_T(java.lang.String groupId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_T(groupId, type);
	}

	public static void removeByG_U_T(java.lang.String groupId,
		java.lang.String userId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U_T(groupId, userId, type);
	}

	public static void removeByG_C_R(java.lang.String groupId,
		java.lang.String companyId, boolean repeating)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_C_R(groupId, companyId, repeating);
	}

	public static void removeByG_U_R(java.lang.String groupId,
		java.lang.String userId, boolean repeating)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U_R(groupId, userId, repeating);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByC_T(java.lang.String companyId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_T(companyId, type);
	}

	public static int countByC_U_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_U_T(companyId, userId, type);
	}

	public static int countByC_U_D_T(java.lang.String companyId,
		java.lang.String userId, java.lang.String description,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_U_D_T(companyId, userId, description, type);
	}

	public static int countByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U(groupId, userId);
	}

	public static int countByG_T(java.lang.String groupId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_T(groupId, type);
	}

	public static int countByG_U_T(java.lang.String groupId,
		java.lang.String userId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U_T(groupId, userId, type);
	}

	public static int countByG_C_R(java.lang.String groupId,
		java.lang.String companyId, boolean repeating)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_C_R(groupId, companyId, repeating);
	}

	public static int countByG_U_R(java.lang.String groupId,
		java.lang.String userId, boolean repeating)
		throws com.liferay.portal.SystemException {
		CalEventPersistence persistence = (CalEventPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U_R(groupId, userId, repeating);
	}

	private static final Log _log = LogFactory.getLog(CalEventUtil.class);
}
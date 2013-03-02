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
 * <a href="CalTaskUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalTaskUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.calendar.model.CalTask"),
			"com.liferay.portlet.calendar.service.persistence.CalTaskPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.calendar.model.CalTask"));

	public static com.liferay.portlet.calendar.model.CalTask create(
		java.lang.String taskId) {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(taskId);
	}

	public static com.liferay.portlet.calendar.model.CalTask remove(
		java.lang.String taskId)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(taskId));
		}

		com.liferay.portlet.calendar.model.CalTask calTask = persistence.remove(taskId);

		if (listener != null) {
			listener.onAfterRemove(calTask);
		}

		return calTask;
	}

	public static com.liferay.portlet.calendar.model.CalTask update(
		com.liferay.portlet.calendar.model.CalTask calTask)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = calTask.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(calTask);
			}
			else {
				listener.onBeforeUpdate(calTask);
			}
		}

		calTask = persistence.update(calTask);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(calTask);
			}
			else {
				listener.onAfterUpdate(calTask);
			}
		}

		return calTask;
	}

	public static com.liferay.portlet.calendar.model.CalTask findByPrimaryKey(
		java.lang.String taskId)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(taskId);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask[] findByUserId_PrevAndNext(
		java.lang.String taskId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(taskId, userId, obc);
	}

	public static java.util.List findByU_P(java.lang.String userId, int priority)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P(userId, priority);
	}

	public static java.util.List findByU_P(java.lang.String userId,
		int priority, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P(userId, priority, begin, end);
	}

	public static java.util.List findByU_P(java.lang.String userId,
		int priority, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P(userId, priority, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByU_P_First(
		java.lang.String userId, int priority,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_First(userId, priority, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByU_P_Last(
		java.lang.String userId, int priority,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_Last(userId, priority, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask[] findByU_P_PrevAndNext(
		java.lang.String taskId, java.lang.String userId, int priority,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_PrevAndNext(taskId, userId, priority, obc);
	}

	public static java.util.List findByU_S(java.lang.String userId, int status)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, status);
	}

	public static java.util.List findByU_S(java.lang.String userId, int status,
		int begin, int end) throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, status, begin, end);
	}

	public static java.util.List findByU_S(java.lang.String userId, int status,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, status, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByU_S_First(
		java.lang.String userId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_First(userId, status, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByU_S_Last(
		java.lang.String userId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_Last(userId, status, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask[] findByU_S_PrevAndNext(
		java.lang.String taskId, java.lang.String userId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_PrevAndNext(taskId, userId, status, obc);
	}

	public static java.util.List findByU_P_S(java.lang.String userId,
		int priority, int status) throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_S(userId, priority, status);
	}

	public static java.util.List findByU_P_S(java.lang.String userId,
		int priority, int status, int begin, int end)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_S(userId, priority, status, begin, end);
	}

	public static java.util.List findByU_P_S(java.lang.String userId,
		int priority, int status, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_S(userId, priority, status, begin, end, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByU_P_S_First(
		java.lang.String userId, int priority, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_S_First(userId, priority, status, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask findByU_P_S_Last(
		java.lang.String userId, int priority, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_S_Last(userId, priority, status, obc);
	}

	public static com.liferay.portlet.calendar.model.CalTask[] findByU_P_S_PrevAndNext(
		java.lang.String taskId, java.lang.String userId, int priority,
		int status, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.calendar.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_S_PrevAndNext(taskId, userId, priority,
			status, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByU_P(java.lang.String userId, int priority)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_P(userId, priority);
	}

	public static void removeByU_S(java.lang.String userId, int status)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_S(userId, status);
	}

	public static void removeByU_P_S(java.lang.String userId, int priority,
		int status) throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_P_S(userId, priority, status);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByU_P(java.lang.String userId, int priority)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_P(userId, priority);
	}

	public static int countByU_S(java.lang.String userId, int status)
		throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_S(userId, status);
	}

	public static int countByU_P_S(java.lang.String userId, int priority,
		int status) throws com.liferay.portal.SystemException {
		CalTaskPersistence persistence = (CalTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_P_S(userId, priority, status);
	}

	private static final Log _log = LogFactory.getLog(CalTaskUtil.class);
}
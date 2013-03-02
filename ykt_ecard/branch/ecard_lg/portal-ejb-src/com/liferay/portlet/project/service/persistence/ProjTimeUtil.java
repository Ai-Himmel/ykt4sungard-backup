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

package com.liferay.portlet.project.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ProjTimeUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTimeUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.project.model.ProjTime"),
			"com.liferay.portlet.project.service.persistence.ProjTimePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.project.model.ProjTime"));

	public static com.liferay.portlet.project.model.ProjTime create(
		java.lang.String timeId) {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(timeId);
	}

	public static com.liferay.portlet.project.model.ProjTime remove(
		java.lang.String timeId)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(timeId));
		}

		com.liferay.portlet.project.model.ProjTime projTime = persistence.remove(timeId);

		if (listener != null) {
			listener.onAfterRemove(projTime);
		}

		return projTime;
	}

	public static com.liferay.portlet.project.model.ProjTime update(
		com.liferay.portlet.project.model.ProjTime projTime)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = projTime.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(projTime);
			}
			else {
				listener.onBeforeUpdate(projTime);
			}
		}

		projTime = persistence.update(projTime);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(projTime);
			}
			else {
				listener.onAfterUpdate(projTime);
			}
		}

		return projTime;
	}

	public static com.liferay.portlet.project.model.ProjTime findByPrimaryKey(
		java.lang.String timeId)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(timeId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime[] findByCompanyId_PrevAndNext(
		java.lang.String timeId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(timeId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime[] findByUserId_PrevAndNext(
		java.lang.String timeId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(timeId, userId, obc);
	}

	public static java.util.List findByProjectId(java.lang.String projectId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId(projectId);
	}

	public static java.util.List findByProjectId(java.lang.String projectId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId(projectId, begin, end);
	}

	public static java.util.List findByProjectId(java.lang.String projectId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId(projectId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByProjectId_First(
		java.lang.String projectId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId_First(projectId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByProjectId_Last(
		java.lang.String projectId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId_Last(projectId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime[] findByProjectId_PrevAndNext(
		java.lang.String timeId, java.lang.String projectId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId_PrevAndNext(timeId, projectId, obc);
	}

	public static java.util.List findByTaskId(java.lang.String taskId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTaskId(taskId);
	}

	public static java.util.List findByTaskId(java.lang.String taskId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTaskId(taskId, begin, end);
	}

	public static java.util.List findByTaskId(java.lang.String taskId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTaskId(taskId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByTaskId_First(
		java.lang.String taskId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTaskId_First(taskId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime findByTaskId_Last(
		java.lang.String taskId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTaskId_Last(taskId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTime[] findByTaskId_PrevAndNext(
		java.lang.String timeId, java.lang.String taskId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTimeException, 
			com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByTaskId_PrevAndNext(timeId, taskId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByProjectId(java.lang.String projectId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByProjectId(projectId);
	}

	public static void removeByTaskId(java.lang.String taskId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByTaskId(taskId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByProjectId(java.lang.String projectId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByProjectId(projectId);
	}

	public static int countByTaskId(java.lang.String taskId)
		throws com.liferay.portal.SystemException {
		ProjTimePersistence persistence = (ProjTimePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByTaskId(taskId);
	}

	private static final Log _log = LogFactory.getLog(ProjTimeUtil.class);
}
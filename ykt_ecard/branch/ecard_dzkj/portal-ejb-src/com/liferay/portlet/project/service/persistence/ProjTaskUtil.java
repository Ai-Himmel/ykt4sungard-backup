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
 * <a href="ProjTaskUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTaskUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.project.model.ProjTask"),
			"com.liferay.portlet.project.service.persistence.ProjTaskPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.project.model.ProjTask"));

	public static com.liferay.portlet.project.model.ProjTask create(
		java.lang.String taskId) {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(taskId);
	}

	public static com.liferay.portlet.project.model.ProjTask remove(
		java.lang.String taskId)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
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

		com.liferay.portlet.project.model.ProjTask projTask = persistence.remove(taskId);

		if (listener != null) {
			listener.onAfterRemove(projTask);
		}

		return projTask;
	}

	public static com.liferay.portlet.project.model.ProjTask update(
		com.liferay.portlet.project.model.ProjTask projTask)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = projTask.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(projTask);
			}
			else {
				listener.onBeforeUpdate(projTask);
			}
		}

		projTask = persistence.update(projTask);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(projTask);
			}
			else {
				listener.onAfterUpdate(projTask);
			}
		}

		return projTask;
	}

	public static java.util.List getUsers(java.lang.String pk)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end, obc);
	}

	public static int getUsersSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsersSize(pk);
	}

	public static void setUsers(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, pks);
	}

	public static void setUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, users);
	}

	public static boolean addUser(java.lang.String pk, java.lang.String userPK)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, userPK);
	}

	public static boolean addUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, user);
	}

	public static boolean addUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, userPKs);
	}

	public static boolean addUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, users);
	}

	public static void clearUsers(java.lang.String pk)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearUsers(pk);
	}

	public static boolean containsUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, userPK);
	}

	public static boolean containsUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, user);
	}

	public static boolean removeUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, userPK);
	}

	public static boolean removeUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, user);
	}

	public static boolean removeUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, userPKs);
	}

	public static boolean removeUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, users);
	}

	public static com.liferay.portlet.project.model.ProjTask findByPrimaryKey(
		java.lang.String taskId)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(taskId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask[] findByCompanyId_PrevAndNext(
		java.lang.String taskId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(taskId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask[] findByUserId_PrevAndNext(
		java.lang.String taskId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(taskId, userId, obc);
	}

	public static java.util.List findByProjectId(java.lang.String projectId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId(projectId);
	}

	public static java.util.List findByProjectId(java.lang.String projectId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId(projectId, begin, end);
	}

	public static java.util.List findByProjectId(java.lang.String projectId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId(projectId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByProjectId_First(
		java.lang.String projectId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId_First(projectId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByProjectId_Last(
		java.lang.String projectId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId_Last(projectId, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask[] findByProjectId_PrevAndNext(
		java.lang.String taskId, java.lang.String projectId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByProjectId_PrevAndNext(taskId, projectId, obc);
	}

	public static java.util.List findByC_S(java.lang.String companyId,
		int status) throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, status);
	}

	public static java.util.List findByC_S(java.lang.String companyId,
		int status, int begin, int end)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, status, begin, end);
	}

	public static java.util.List findByC_S(java.lang.String companyId,
		int status, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S(companyId, status, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByC_S_First(
		java.lang.String companyId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S_First(companyId, status, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByC_S_Last(
		java.lang.String companyId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S_Last(companyId, status, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask[] findByC_S_PrevAndNext(
		java.lang.String taskId, java.lang.String companyId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_S_PrevAndNext(taskId, companyId, status, obc);
	}

	public static java.util.List findByU_S(java.lang.String userId, int status)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, status);
	}

	public static java.util.List findByU_S(java.lang.String userId, int status,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, status, begin, end);
	}

	public static java.util.List findByU_S(java.lang.String userId, int status,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, status, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByU_S_First(
		java.lang.String userId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_First(userId, status, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask findByU_S_Last(
		java.lang.String userId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_Last(userId, status, obc);
	}

	public static com.liferay.portlet.project.model.ProjTask[] findByU_S_PrevAndNext(
		java.lang.String taskId, java.lang.String userId, int status,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_PrevAndNext(taskId, userId, status, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByProjectId(java.lang.String projectId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByProjectId(projectId);
	}

	public static void removeByC_S(java.lang.String companyId, int status)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_S(companyId, status);
	}

	public static void removeByU_S(java.lang.String userId, int status)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_S(userId, status);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByProjectId(java.lang.String projectId)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByProjectId(projectId);
	}

	public static int countByC_S(java.lang.String companyId, int status)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_S(companyId, status);
	}

	public static int countByU_S(java.lang.String userId, int status)
		throws com.liferay.portal.SystemException {
		ProjTaskPersistence persistence = (ProjTaskPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_S(userId, status);
	}

	private static final Log _log = LogFactory.getLog(ProjTaskUtil.class);
}
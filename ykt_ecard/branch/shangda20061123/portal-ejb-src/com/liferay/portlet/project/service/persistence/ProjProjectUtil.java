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
 * <a href="ProjProjectUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjProjectUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.project.model.ProjProject"),
			"com.liferay.portlet.project.service.persistence.ProjProjectPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.project.model.ProjProject"));

	public static com.liferay.portlet.project.model.ProjProject create(
		java.lang.String projectId) {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(projectId);
	}

	public static com.liferay.portlet.project.model.ProjProject remove(
		java.lang.String projectId)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(projectId));
		}

		com.liferay.portlet.project.model.ProjProject projProject = persistence.remove(projectId);

		if (listener != null) {
			listener.onAfterRemove(projProject);
		}

		return projProject;
	}

	public static com.liferay.portlet.project.model.ProjProject update(
		com.liferay.portlet.project.model.ProjProject projProject)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = projProject.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(projProject);
			}
			else {
				listener.onBeforeUpdate(projProject);
			}
		}

		projProject = persistence.update(projProject);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(projProject);
			}
			else {
				listener.onAfterUpdate(projProject);
			}
		}

		return projProject;
	}

	public static java.util.List getUsers(java.lang.String pk)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end, obc);
	}

	public static int getUsersSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsersSize(pk);
	}

	public static void setUsers(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, pks);
	}

	public static void setUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, users);
	}

	public static boolean addUser(java.lang.String pk, java.lang.String userPK)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, userPK);
	}

	public static boolean addUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, user);
	}

	public static boolean addUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, userPKs);
	}

	public static boolean addUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, users);
	}

	public static void clearUsers(java.lang.String pk)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearUsers(pk);
	}

	public static boolean containsUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, userPK);
	}

	public static boolean containsUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, user);
	}

	public static boolean removeUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, userPK);
	}

	public static boolean removeUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, user);
	}

	public static boolean removeUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, userPKs);
	}

	public static boolean removeUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, users);
	}

	public static com.liferay.portlet.project.model.ProjProject findByPrimaryKey(
		java.lang.String projectId)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(projectId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject[] findByCompanyId_PrevAndNext(
		java.lang.String projectId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(projectId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject[] findByUserId_PrevAndNext(
		java.lang.String projectId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(projectId, userId, obc);
	}

	public static java.util.List findByFirmId(java.lang.String firmId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByFirmId(firmId);
	}

	public static java.util.List findByFirmId(java.lang.String firmId,
		int begin, int end) throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByFirmId(firmId, begin, end);
	}

	public static java.util.List findByFirmId(java.lang.String firmId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByFirmId(firmId, begin, end, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByFirmId_First(
		java.lang.String firmId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByFirmId_First(firmId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByFirmId_Last(
		java.lang.String firmId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByFirmId_Last(firmId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject[] findByFirmId_PrevAndNext(
		java.lang.String projectId, java.lang.String firmId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByFirmId_PrevAndNext(projectId, firmId, obc);
	}

	public static com.liferay.portlet.project.model.ProjProject findByC_C(
		java.lang.String companyId, java.lang.String code)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, code);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByFirmId(java.lang.String firmId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByFirmId(firmId);
	}

	public static void removeByC_C(java.lang.String companyId,
		java.lang.String code)
		throws com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_C(companyId, code);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByFirmId(java.lang.String firmId)
		throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByFirmId(firmId);
	}

	public static int countByC_C(java.lang.String companyId,
		java.lang.String code) throws com.liferay.portal.SystemException {
		ProjProjectPersistence persistence = (ProjProjectPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_C(companyId, code);
	}

	private static final Log _log = LogFactory.getLog(ProjProjectUtil.class);
}
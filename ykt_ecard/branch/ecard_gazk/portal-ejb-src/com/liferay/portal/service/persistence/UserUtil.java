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

package com.liferay.portal.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UserUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.User"),
			"com.liferay.portal.service.persistence.UserPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.User"));

	public static com.liferay.portal.model.User create(java.lang.String userId) {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(userId);
	}

	public static com.liferay.portal.model.User remove(java.lang.String userId)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(userId));
		}

		com.liferay.portal.model.User user = persistence.remove(userId);

		if (listener != null) {
			listener.onAfterRemove(user);
		}

		return user;
	}

	public static com.liferay.portal.model.User update(
		com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = user.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(user);
			}
			else {
				listener.onBeforeUpdate(user);
			}
		}

		user = persistence.update(user);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(user);
			}
			else {
				listener.onAfterUpdate(user);
			}
		}

		return user;
	}

	public static java.util.List getGroups(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroups(pk);
	}

	public static java.util.List getGroups(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroups(pk, begin, end);
	}

	public static java.util.List getGroups(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroups(pk, begin, end, obc);
	}

	public static int getGroupsSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroupsSize(pk);
	}

	public static void setGroups(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setGroups(pk, pks);
	}

	public static void setGroups(java.lang.String pk, java.util.List groups)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setGroups(pk, groups);
	}

	public static boolean addGroup(java.lang.String pk, java.lang.String groupPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroup(pk, groupPK);
	}

	public static boolean addGroup(java.lang.String pk,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroup(pk, group);
	}

	public static boolean addGroups(java.lang.String pk,
		java.lang.String[] groupPKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroups(pk, groupPKs);
	}

	public static boolean addGroups(java.lang.String pk, java.util.List groups)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroups(pk, groups);
	}

	public static void clearGroups(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearGroups(pk);
	}

	public static boolean containsGroup(java.lang.String pk,
		java.lang.String groupPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsGroup(pk, groupPK);
	}

	public static boolean containsGroup(java.lang.String pk,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsGroup(pk, group);
	}

	public static boolean removeGroup(java.lang.String pk,
		java.lang.String groupPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroup(pk, groupPK);
	}

	public static boolean removeGroup(java.lang.String pk,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroup(pk, group);
	}

	public static boolean removeGroups(java.lang.String pk,
		java.lang.String[] groupPKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroups(pk, groupPKs);
	}

	public static boolean removeGroups(java.lang.String pk,
		java.util.List groups)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroups(pk, groups);
	}

	public static java.util.List getRoles(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRoles(pk);
	}

	public static java.util.List getRoles(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRoles(pk, begin, end);
	}

	public static java.util.List getRoles(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRoles(pk, begin, end, obc);
	}

	public static int getRolesSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRolesSize(pk);
	}

	public static void setRoles(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setRoles(pk, pks);
	}

	public static void setRoles(java.lang.String pk, java.util.List roles)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setRoles(pk, roles);
	}

	public static boolean addRole(java.lang.String pk, java.lang.String rolePK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRole(pk, rolePK);
	}

	public static boolean addRole(java.lang.String pk,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRole(pk, role);
	}

	public static boolean addRoles(java.lang.String pk,
		java.lang.String[] rolePKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRoles(pk, rolePKs);
	}

	public static boolean addRoles(java.lang.String pk, java.util.List roles)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRoles(pk, roles);
	}

	public static void clearRoles(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearRoles(pk);
	}

	public static boolean containsRole(java.lang.String pk,
		java.lang.String rolePK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsRole(pk, rolePK);
	}

	public static boolean containsRole(java.lang.String pk,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsRole(pk, role);
	}

	public static boolean removeRole(java.lang.String pk,
		java.lang.String rolePK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRole(pk, rolePK);
	}

	public static boolean removeRole(java.lang.String pk,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRole(pk, role);
	}

	public static boolean removeRoles(java.lang.String pk,
		java.lang.String[] rolePKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRoles(pk, rolePKs);
	}

	public static boolean removeRoles(java.lang.String pk, java.util.List roles)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRoles(pk, roles);
	}

	public static java.util.List getProjProjects(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjProjects(pk);
	}

	public static java.util.List getProjProjects(java.lang.String pk,
		int begin, int end)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjProjects(pk, begin, end);
	}

	public static java.util.List getProjProjects(java.lang.String pk,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjProjects(pk, begin, end, obc);
	}

	public static int getProjProjectsSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjProjectsSize(pk);
	}

	public static void setProjProjects(java.lang.String pk,
		java.lang.String[] pks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setProjProjects(pk, pks);
	}

	public static void setProjProjects(java.lang.String pk,
		java.util.List projProjects)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setProjProjects(pk, projProjects);
	}

	public static boolean addProjProject(java.lang.String pk,
		java.lang.String projProjectPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjProject(pk, projProjectPK);
	}

	public static boolean addProjProject(java.lang.String pk,
		com.liferay.portlet.project.model.ProjProject projProject)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjProject(pk, projProject);
	}

	public static boolean addProjProjects(java.lang.String pk,
		java.lang.String[] projProjectPKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjProjects(pk, projProjectPKs);
	}

	public static boolean addProjProjects(java.lang.String pk,
		java.util.List projProjects)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjProjects(pk, projProjects);
	}

	public static void clearProjProjects(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearProjProjects(pk);
	}

	public static boolean containsProjProject(java.lang.String pk,
		java.lang.String projProjectPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsProjProject(pk, projProjectPK);
	}

	public static boolean containsProjProject(java.lang.String pk,
		com.liferay.portlet.project.model.ProjProject projProject)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsProjProject(pk, projProject);
	}

	public static boolean removeProjProject(java.lang.String pk,
		java.lang.String projProjectPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjProject(pk, projProjectPK);
	}

	public static boolean removeProjProject(java.lang.String pk,
		com.liferay.portlet.project.model.ProjProject projProject)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjProject(pk, projProject);
	}

	public static boolean removeProjProjects(java.lang.String pk,
		java.lang.String[] projProjectPKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjProjects(pk, projProjectPKs);
	}

	public static boolean removeProjProjects(java.lang.String pk,
		java.util.List projProjects)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchProjectException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjProjects(pk, projProjects);
	}

	public static java.util.List getProjTasks(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjTasks(pk);
	}

	public static java.util.List getProjTasks(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjTasks(pk, begin, end);
	}

	public static java.util.List getProjTasks(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjTasks(pk, begin, end, obc);
	}

	public static int getProjTasksSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getProjTasksSize(pk);
	}

	public static void setProjTasks(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setProjTasks(pk, pks);
	}

	public static void setProjTasks(java.lang.String pk,
		java.util.List projTasks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.setProjTasks(pk, projTasks);
	}

	public static boolean addProjTask(java.lang.String pk,
		java.lang.String projTaskPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjTask(pk, projTaskPK);
	}

	public static boolean addProjTask(java.lang.String pk,
		com.liferay.portlet.project.model.ProjTask projTask)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjTask(pk, projTask);
	}

	public static boolean addProjTasks(java.lang.String pk,
		java.lang.String[] projTaskPKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjTasks(pk, projTaskPKs);
	}

	public static boolean addProjTasks(java.lang.String pk,
		java.util.List projTasks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addProjTasks(pk, projTasks);
	}

	public static void clearProjTasks(java.lang.String pk)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearProjTasks(pk);
	}

	public static boolean containsProjTask(java.lang.String pk,
		java.lang.String projTaskPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsProjTask(pk, projTaskPK);
	}

	public static boolean containsProjTask(java.lang.String pk,
		com.liferay.portlet.project.model.ProjTask projTask)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsProjTask(pk, projTask);
	}

	public static boolean removeProjTask(java.lang.String pk,
		java.lang.String projTaskPK)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjTask(pk, projTaskPK);
	}

	public static boolean removeProjTask(java.lang.String pk,
		com.liferay.portlet.project.model.ProjTask projTask)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjTask(pk, projTask);
	}

	public static boolean removeProjTasks(java.lang.String pk,
		java.lang.String[] projTaskPKs)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjTasks(pk, projTaskPKs);
	}

	public static boolean removeProjTasks(java.lang.String pk,
		java.util.List projTasks)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portlet.project.NoSuchTaskException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeProjTasks(pk, projTasks);
	}

	public static com.liferay.portal.model.User findByPrimaryKey(
		java.lang.String userId)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(userId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.User findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.User findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.User[] findByCompanyId_PrevAndNext(
		java.lang.String userId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(userId, companyId, obc);
	}

	public static com.liferay.portal.model.User findByC_U(
		java.lang.String companyId, java.lang.String userId)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_U(companyId, userId);
	}

	public static java.util.List findByC_P(java.lang.String companyId,
		java.lang.String password) throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P(companyId, password);
	}

	public static java.util.List findByC_P(java.lang.String companyId,
		java.lang.String password, int begin, int end)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P(companyId, password, begin, end);
	}

	public static java.util.List findByC_P(java.lang.String companyId,
		java.lang.String password, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P(companyId, password, begin, end, obc);
	}

	public static com.liferay.portal.model.User findByC_P_First(
		java.lang.String companyId, java.lang.String password,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P_First(companyId, password, obc);
	}

	public static com.liferay.portal.model.User findByC_P_Last(
		java.lang.String companyId, java.lang.String password,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P_Last(companyId, password, obc);
	}

	public static com.liferay.portal.model.User[] findByC_P_PrevAndNext(
		java.lang.String userId, java.lang.String companyId,
		java.lang.String password,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_P_PrevAndNext(userId, companyId, password,
			obc);
	}

	public static com.liferay.portal.model.User findByC_EA(
		java.lang.String companyId, java.lang.String emailAddress)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_EA(companyId, emailAddress);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByC_U(java.lang.String companyId,
		java.lang.String userId)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_U(companyId, userId);
	}

	public static void removeByC_P(java.lang.String companyId,
		java.lang.String password) throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_P(companyId, password);
	}

	public static void removeByC_EA(java.lang.String companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_EA(companyId, emailAddress);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByC_U(java.lang.String companyId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_U(companyId, userId);
	}

	public static int countByC_P(java.lang.String companyId,
		java.lang.String password) throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_P(companyId, password);
	}

	public static int countByC_EA(java.lang.String companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException {
		UserPersistence persistence = (UserPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_EA(companyId, emailAddress);
	}

	private static final Log _log = LogFactory.getLog(UserUtil.class);
}
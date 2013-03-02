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
 * <a href="RoleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class RoleUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.Role"),
			"com.liferay.portal.service.persistence.RolePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Role"));

	public static com.liferay.portal.model.Role create(java.lang.String roleId) {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(roleId);
	}

	public static com.liferay.portal.model.Role remove(java.lang.String roleId)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(roleId));
		}

		com.liferay.portal.model.Role role = persistence.remove(roleId);

		if (listener != null) {
			listener.onAfterRemove(role);
		}

		return role;
	}

	public static com.liferay.portal.model.Role update(
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = role.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(role);
			}
			else {
				listener.onBeforeUpdate(role);
			}
		}

		role = persistence.update(role);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(role);
			}
			else {
				listener.onAfterUpdate(role);
			}
		}

		return role;
	}

	public static java.util.List getGroups(java.lang.String pk)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroups(pk);
	}

	public static java.util.List getGroups(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroups(pk, begin, end);
	}

	public static java.util.List getGroups(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroups(pk, begin, end, obc);
	}

	public static int getGroupsSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getGroupsSize(pk);
	}

	public static void setGroups(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.setGroups(pk, pks);
	}

	public static void setGroups(java.lang.String pk, java.util.List groups)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.setGroups(pk, groups);
	}

	public static boolean addGroup(java.lang.String pk, java.lang.String groupPK)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroup(pk, groupPK);
	}

	public static boolean addGroup(java.lang.String pk,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroup(pk, group);
	}

	public static boolean addGroups(java.lang.String pk,
		java.lang.String[] groupPKs)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroups(pk, groupPKs);
	}

	public static boolean addGroups(java.lang.String pk, java.util.List groups)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addGroups(pk, groups);
	}

	public static void clearGroups(java.lang.String pk)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.clearGroups(pk);
	}

	public static boolean containsGroup(java.lang.String pk,
		java.lang.String groupPK)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsGroup(pk, groupPK);
	}

	public static boolean containsGroup(java.lang.String pk,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsGroup(pk, group);
	}

	public static boolean removeGroup(java.lang.String pk,
		java.lang.String groupPK)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroup(pk, groupPK);
	}

	public static boolean removeGroup(java.lang.String pk,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroup(pk, group);
	}

	public static boolean removeGroups(java.lang.String pk,
		java.lang.String[] groupPKs)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroups(pk, groupPKs);
	}

	public static boolean removeGroups(java.lang.String pk,
		java.util.List groups)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeGroups(pk, groups);
	}

	public static java.util.List getUsers(java.lang.String pk)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end, obc);
	}

	public static int getUsersSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsersSize(pk);
	}

	public static void setUsers(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, pks);
	}

	public static void setUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, users);
	}

	public static boolean addUser(java.lang.String pk, java.lang.String userPK)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, userPK);
	}

	public static boolean addUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, user);
	}

	public static boolean addUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, userPKs);
	}

	public static boolean addUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, users);
	}

	public static void clearUsers(java.lang.String pk)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.clearUsers(pk);
	}

	public static boolean containsUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, userPK);
	}

	public static boolean containsUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, user);
	}

	public static boolean removeUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, userPK);
	}

	public static boolean removeUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, user);
	}

	public static boolean removeUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, userPKs);
	}

	public static boolean removeUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, users);
	}

	public static com.liferay.portal.model.Role findByPrimaryKey(
		java.lang.String roleId)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(roleId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Role findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Role findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Role[] findByCompanyId_PrevAndNext(
		java.lang.String roleId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(roleId, companyId, obc);
	}

	public static com.liferay.portal.model.Role findByC_N(
		java.lang.String companyId, java.lang.String name)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_N(companyId, name);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByC_N(java.lang.String companyId,
		java.lang.String name)
		throws com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_N(companyId, name);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByC_N(java.lang.String companyId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		RolePersistence persistence = (RolePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_N(companyId, name);
	}

	private static final Log _log = LogFactory.getLog(RoleUtil.class);
}
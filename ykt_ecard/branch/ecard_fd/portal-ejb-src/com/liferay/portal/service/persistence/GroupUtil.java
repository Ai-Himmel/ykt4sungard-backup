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
 * <a href="GroupUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class GroupUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.Group"),
			"com.liferay.portal.service.persistence.GroupPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Group"));

	public static com.liferay.portal.model.Group create(
		java.lang.String groupId) {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(groupId);
	}

	public static com.liferay.portal.model.Group remove(
		java.lang.String groupId)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(groupId));
		}

		com.liferay.portal.model.Group group = persistence.remove(groupId);

		if (listener != null) {
			listener.onAfterRemove(group);
		}

		return group;
	}

	public static com.liferay.portal.model.Group update(
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = group.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(group);
			}
			else {
				listener.onBeforeUpdate(group);
			}
		}

		group = persistence.update(group);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(group);
			}
			else {
				listener.onAfterUpdate(group);
			}
		}

		return group;
	}

	public static java.util.List getRoles(java.lang.String pk)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRoles(pk);
	}

	public static java.util.List getRoles(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRoles(pk, begin, end);
	}

	public static java.util.List getRoles(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRoles(pk, begin, end, obc);
	}

	public static int getRolesSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getRolesSize(pk);
	}

	public static void setRoles(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.setRoles(pk, pks);
	}

	public static void setRoles(java.lang.String pk, java.util.List roles)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.setRoles(pk, roles);
	}

	public static boolean addRole(java.lang.String pk, java.lang.String rolePK)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRole(pk, rolePK);
	}

	public static boolean addRole(java.lang.String pk,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRole(pk, role);
	}

	public static boolean addRoles(java.lang.String pk,
		java.lang.String[] rolePKs)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRoles(pk, rolePKs);
	}

	public static boolean addRoles(java.lang.String pk, java.util.List roles)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addRoles(pk, roles);
	}

	public static void clearRoles(java.lang.String pk)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearRoles(pk);
	}

	public static boolean containsRole(java.lang.String pk,
		java.lang.String rolePK)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsRole(pk, rolePK);
	}

	public static boolean containsRole(java.lang.String pk,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsRole(pk, role);
	}

	public static boolean removeRole(java.lang.String pk,
		java.lang.String rolePK)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRole(pk, rolePK);
	}

	public static boolean removeRole(java.lang.String pk,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRole(pk, role);
	}

	public static boolean removeRoles(java.lang.String pk,
		java.lang.String[] rolePKs)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRoles(pk, rolePKs);
	}

	public static boolean removeRoles(java.lang.String pk, java.util.List roles)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeRoles(pk, roles);
	}

	public static java.util.List getUsers(java.lang.String pk)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(java.lang.String pk, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsers(pk, begin, end, obc);
	}

	public static int getUsersSize(java.lang.String pk)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.getUsersSize(pk);
	}

	public static void setUsers(java.lang.String pk, java.lang.String[] pks)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, pks);
	}

	public static void setUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.setUsers(pk, users);
	}

	public static boolean addUser(java.lang.String pk, java.lang.String userPK)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, userPK);
	}

	public static boolean addUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUser(pk, user);
	}

	public static boolean addUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, userPKs);
	}

	public static boolean addUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.addUsers(pk, users);
	}

	public static void clearUsers(java.lang.String pk)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.clearUsers(pk);
	}

	public static boolean containsUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, userPK);
	}

	public static boolean containsUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.containsUser(pk, user);
	}

	public static boolean removeUser(java.lang.String pk,
		java.lang.String userPK)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, userPK);
	}

	public static boolean removeUser(java.lang.String pk,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUser(pk, user);
	}

	public static boolean removeUsers(java.lang.String pk,
		java.lang.String[] userPKs)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, userPKs);
	}

	public static boolean removeUsers(java.lang.String pk, java.util.List users)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.removeUsers(pk, users);
	}

	public static com.liferay.portal.model.Group findByPrimaryKey(
		java.lang.String groupId)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(groupId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Group findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Group findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Group[] findByCompanyId_PrevAndNext(
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(groupId, companyId, obc);
	}

	public static com.liferay.portal.model.Group findByC_N(
		java.lang.String companyId, java.lang.String name)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_N(companyId, name);
	}

	public static com.liferay.portal.model.Group findByC_F(
		java.lang.String companyId, java.lang.String friendlyURL)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F(companyId, friendlyURL);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByC_N(java.lang.String companyId,
		java.lang.String name)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_N(companyId, name);
	}

	public static void removeByC_F(java.lang.String companyId,
		java.lang.String friendlyURL)
		throws com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_F(companyId, friendlyURL);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByC_N(java.lang.String companyId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_N(companyId, name);
	}

	public static int countByC_F(java.lang.String companyId,
		java.lang.String friendlyURL) throws com.liferay.portal.SystemException {
		GroupPersistence persistence = (GroupPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_F(companyId, friendlyURL);
	}

	private static final Log _log = LogFactory.getLog(GroupUtil.class);
}
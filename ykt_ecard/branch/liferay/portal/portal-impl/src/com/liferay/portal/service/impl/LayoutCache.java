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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchResourceException;
import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.service.OrganizationLocalServiceUtil;
import com.liferay.portal.service.ResourceLocalServiceUtil;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.service.UserGroupLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * <a href="LayoutCache.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class LayoutCache  {

	protected long getEntityGroupId(
			long companyId, String entityName, String name)
		throws PortalException, SystemException {

		long entityGroupId = 0;

		Long entityGroupIdObj = (Long)entityGroupIdMap.get(entityName);

		if (entityGroupIdObj == null) {
			if (entityName.equals("user-group")) {
				List userGroups = UserGroupLocalServiceUtil.search(
					companyId, name, null, null, 0, 1, null);

				if (userGroups.size() > 0) {
					UserGroup userGroup = (UserGroup)userGroups.get(0);

					Group group = userGroup.getGroup();

					entityGroupId = group.getGroupId();
				}
			}
			else if (entityName.equals("organization") ||
					 entityName.equals("location")) {

				List organizations = null;

				if (entityName.equals("organization")) {
					organizations = OrganizationLocalServiceUtil.search(
						companyId, OrganizationImpl.ANY_PARENT_ORGANIZATION_ID,
					    name, OrganizationImpl.TYPE_REGULAR, null, null, null,
						null, null, null, true, 0, 1);
				}
				else if (entityName.equals("location")) {
					organizations = OrganizationLocalServiceUtil.search(
						companyId, OrganizationImpl.ANY_PARENT_ORGANIZATION_ID,
					    name, OrganizationImpl.TYPE_LOCATION, null, null, null,
						null, null, null, true, 0, 1);
				}

				if (organizations.size() > 0) {
					Organization organization =
						(Organization)organizations.get(0);

					Group group = organization.getGroup();

					entityGroupId = group.getGroupId();
				}
			}

			entityGroupIdMap.put(entityName, entityGroupIdObj);
		}
		else {
			entityGroupId = entityGroupIdObj.longValue();
		}

		return entityGroupId;
	}

	protected Map getEntityMap(long companyId, String entityName)
		throws PortalException, SystemException {

		Map entityMap = (Map)entityMapMap.get(entityName);

		if (entityMap == null) {
			entityMap = new HashMap();

			if (entityName.equals("user-group")) {
				List userGroups = UserGroupLocalServiceUtil.search(
					companyId, null, null, null, QueryUtil.ALL_POS,
					QueryUtil.ALL_POS, null);

				for (int i = 0; i < userGroups.size(); i++) {
					UserGroup userGroup = (UserGroup)userGroups.get(i);

					Group group = userGroup.getGroup();

					entityMap.put(
						userGroup.getName(), new Long(group.getGroupId()));
				}
			}
			else if (entityName.equals("organization") ||
					 entityName.equals("location")) {

				List organizations = null;

				if (entityName.equals("organization")) {
					organizations = OrganizationLocalServiceUtil.search(
						companyId, OrganizationImpl.ANY_PARENT_ORGANIZATION_ID,
					    null, OrganizationImpl.TYPE_REGULAR, null, null, null,
						QueryUtil.ALL_POS, QueryUtil.ALL_POS);
				}
				else if (entityName.equals("location")) {
					organizations = OrganizationLocalServiceUtil.search(
						companyId, OrganizationImpl.ANY_PARENT_ORGANIZATION_ID,
					    null, OrganizationImpl.TYPE_LOCATION, null, null, null,
						QueryUtil.ALL_POS, QueryUtil.ALL_POS);
				}

				for (int i = 0; i < organizations.size(); i++) {
					Organization organization =
						(Organization)organizations.get(i);

					Group group = organization.getGroup();

					entityMap.put(
						organization.getName(), new Long(group.getGroupId()));
				}
			}

			entityMapMap.put(entityName, entityMap);
		}

		return entityMap;
	}

	protected List getGroupRoles(long groupId)
		throws PortalException, SystemException {

		Long groupIdObj = new Long(groupId);

		List roles = (List)groupRolesMap.get(groupIdObj);

		if (roles == null) {
			roles = RoleLocalServiceUtil.getGroupRoles(groupId);

			groupRolesMap.put(groupIdObj, roles);
		}

		return roles;
	}

	protected List getGroupUsers(long groupId)
		throws PortalException, SystemException {

		List users = (List)groupUsersMap.get(new Long(groupId));

		if (users == null) {
			users = UserLocalServiceUtil.getGroupUsers(groupId);

			groupUsersMap.put(new Long(groupId), users);
		}

		return users;
	}

	protected Resource getResource(
			long companyId, long groupId, String resourceName, int scope,
			String resourcePrimKey, boolean portletActions)
		throws PortalException, SystemException {

		StringMaker sm = new StringMaker();

		sm.append(resourceName);
		sm.append(StringPool.PIPE);
		sm.append(scope);
		sm.append(StringPool.PIPE);
		sm.append(resourcePrimKey);

		String key = sm.toString();

		Resource resource = (Resource)resourcesMap.get(key);

		if (resource == null) {
			try {
				resource = ResourceLocalServiceUtil.getResource(
					companyId, resourceName, scope, resourcePrimKey);
			}
			catch (NoSuchResourceException nsre) {
				ResourceLocalServiceUtil.addResources(
					companyId, groupId, 0, resourceName, resourcePrimKey,
					portletActions, true, true);

				resource = ResourceLocalServiceUtil.getResource(
					companyId, resourceName, scope, resourcePrimKey);
			}

			resourcesMap.put(key, resource);
		}

		return resource;
	}

	protected Role getRole(long companyId, String roleName)
		throws PortalException, SystemException {

		Role role = (Role)rolesMap.get(roleName);

		if (role == null) {
			try {
				role = RoleLocalServiceUtil.getRole(companyId, roleName);

				rolesMap.put(roleName, role);
			}
			catch (NoSuchRoleException nsre) {
			}
		}

		return role;
	}

	protected User getUser(long companyId, long groupId, String emailAddress)
		throws PortalException, SystemException {

		List users = (List)usersMap.get(emailAddress);

		if (users == null) {
			LinkedHashMap params = new LinkedHashMap();

			params.put("usersGroups", new Long(groupId));

			users = UserLocalServiceUtil.search(
				companyId, null, null, null, null, emailAddress, Boolean.TRUE,
				params, true, 0, 1, null);

			usersMap.put(emailAddress, users);
		}

		if (users.size() == 0) {
			return null;
		}
		else {
			return (User)users.get(0);
		}
	}

	protected List getUserRoles(long userId)
		throws PortalException, SystemException {

		Long userIdObj = new Long(userId);

		List userRoles = (List)userRolesMap.get(userIdObj);

		if (userRoles == null) {
			userRoles = RoleLocalServiceUtil.getUserRoles(userId);

			userRolesMap.put(userIdObj, userRoles);
		}

		return userRoles;
	}

	protected Map entityGroupIdMap = CollectionFactory.getHashMap();
    protected Map entityMapMap = CollectionFactory.getHashMap();
    protected Map groupRolesMap = CollectionFactory.getHashMap();
    protected Map groupUsersMap = CollectionFactory.getHashMap();
    protected Map resourcesMap = CollectionFactory.getHashMap();
    protected Map rolesMap = CollectionFactory.getHashMap();
    protected Map userRolesMap = CollectionFactory.getHashMap();
    protected Map usersMap = CollectionFactory.getHashMap();

}
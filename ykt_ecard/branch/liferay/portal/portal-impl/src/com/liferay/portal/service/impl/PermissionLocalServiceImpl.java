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

import com.liferay.portal.NoSuchPermissionException;
import com.liferay.portal.NoSuchResourceException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.PermissionCheckerBag;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.OrgGroupPermission;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.security.permission.PermissionCacheUtil;
import com.liferay.portal.security.permission.PermissionCheckerImpl;
import com.liferay.portal.security.permission.ResourceActionsUtil;
import com.liferay.portal.service.base.PermissionLocalServiceBaseImpl;
import com.liferay.portal.service.persistence.OrgGroupPermissionPK;
import com.liferay.portal.util.comparator.PermissionComparator;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PermissionLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionLocalServiceImpl extends PermissionLocalServiceBaseImpl {

	public Permission addPermission(
			long companyId, String actionId, long resourceId)
		throws PortalException, SystemException {

		Permission permission = permissionPersistence.fetchByA_R(
			actionId, resourceId);

		if (permission == null) {
			long permissionId = counterLocalService.increment(
				Permission.class.getName());

			permission = permissionPersistence.create(permissionId);

			permission.setCompanyId(companyId);
			permission.setActionId(actionId);
			permission.setResourceId(resourceId);

			permissionPersistence.update(permission);
		}

		return permission;
	}

	public List addPermissions(
			long companyId, String name, long resourceId,
			boolean portletActions)
		throws PortalException, SystemException {

		List permissions = new ArrayList();

		List actions = null;

		if (portletActions) {
			actions =
				ResourceActionsUtil.getPortletResourceActions(companyId, name);
		}
		else {
			actions = ResourceActionsUtil.getModelResourceActions(name);
		}

		for (int i = 0; i < actions.size(); i++) {
			String actionId = (String)actions.get(i);

			Permission permission =
				addPermission(companyId, actionId, resourceId);

			permissions.add(permission);
		}

		return permissions;
	}

	public void addUserPermissions(
			long userId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		List permissions = permissionFinder.findByU_R(userId, resourceId);

		permissions = getPermissions(
			user.getCompanyId(), actionIds, resourceId);

		userPersistence.addPermissions(userId, permissions);

		PermissionCacheUtil.clearCache();
	}

	public List getActions(List permissions) throws SystemException {
		List actions = new ArrayList();

		Iterator itr = permissions.iterator();

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			actions.add(permission.getActionId());
		}

		return actions;
	}

	public List getGroupPermissions(long groupId, long resourceId)
		throws SystemException {

		return permissionFinder.findByG_R(groupId, resourceId);
	}

	public List getGroupPermissions(
			long groupId, long companyId, String name, int scope,
			String primKey)
		throws SystemException {

		return permissionFinder.findByG_C_N_S_P(
			groupId, companyId, name, scope, primKey);
	}

	public List getOrgGroupPermissions(
			long organizationId, long groupId, long resourceId)
		throws SystemException {

		return permissionFinder.findByO_G_R(
			organizationId, groupId, resourceId);
	}

	public long getLatestPermissionId()
		throws PortalException, SystemException {

		List list = permissionPersistence.findAll(
			0, 1, new PermissionComparator());

		if (list.size() == 0) {
			return 0;
		}
		else {
			Permission permission = (Permission)list.get(0);

			return permission.getPermissionId();
		}
	}

	public List getPermissions(
			long companyId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		List permissions = new ArrayList();

		for (int i = 0; i < actionIds.length; i++) {
			Permission permission =
				addPermission(companyId, actionIds[i], resourceId);

			permissions.add(permission);
		}

		return permissions;
	}

	public List getRolePermissions(long roleId)
		throws PortalException, SystemException {

		return rolePersistence.getPermissions(roleId);
	}

	public List getRolePermissions(long roleId, long resourceId)
		throws SystemException {

		return permissionFinder.findByR_R(roleId, resourceId);
	}

	public List getUserPermissions(long userId, long resourceId)
		throws SystemException {

		return permissionFinder.findByU_R(userId, resourceId);
	}

	public List getUserPermissions(
			long userId, long companyId, String name, int scope, String primKey)
		throws SystemException {

		return permissionFinder.findByU_C_N_S_P(
			userId, companyId, name, scope, primKey);
	}

	public boolean hasGroupPermission(
			long groupId, String actionId, long resourceId)
		throws PortalException, SystemException {

		Permission permission = null;

		try {
			permission = permissionPersistence.findByA_R(actionId, resourceId);
		}
		catch (NoSuchPermissionException nspe) {

			// Return false if there is no permission based on the given action
			// id and resource id

			return false;
		}

		return groupPersistence.containsPermission(
			groupId, permission.getPermissionId());
	}

	public boolean hasRolePermission(
			long roleId, long companyId, String name, int scope,
			String actionId)
		throws PortalException, SystemException {

		ResourceCode resourceCode = resourceCodeLocalService.getResourceCode(
			companyId, name, scope);

		Iterator itr = resourcePersistence.findByCodeId(
			resourceCode.getCodeId()).iterator();

		while (itr.hasNext()) {
			Resource resource = (Resource)itr.next();

			try {
				Permission permission = permissionPersistence.findByA_R(
					actionId, resource.getResourceId());

				if (rolePersistence.containsPermission(
						roleId, permission.getPermissionId())) {

					return true;
				}
			}
			catch (NoSuchPermissionException nspe) {
			}
		}

		return false;
	}

	public boolean hasRolePermission(
			long roleId, long companyId, String name, int scope, String primKey,
			String actionId)
		throws PortalException, SystemException {

		try {
			ResourceCode resourceCode =
				resourceCodeLocalService.getResourceCode(
					companyId, name, scope);

			Resource resource = resourcePersistence.findByC_P(
				resourceCode.getCodeId(), primKey);

			Permission permission = permissionPersistence.findByA_R(
				actionId, resource.getResourceId());

			return rolePersistence.containsPermission(
				roleId, permission.getPermissionId());
		}
		catch (NoSuchPermissionException nspe) {
		}
		catch (NoSuchResourceException nsre) {
		}

		return false;
	}

	public boolean hasUserPermission(
			long userId, String actionId, long resourceId)
		throws PortalException, SystemException {

		Permission permission = null;

		try {
			permission = permissionPersistence.findByA_R(actionId, resourceId);
		}
		catch (NoSuchPermissionException nspe) {

			// Return false if there is no permission based on the given action
			// id and resource id

			return false;
		}

		return userPersistence.containsPermission(
			userId, permission.getPermissionId());
	}

	public boolean hasUserPermissions(
			long userId, long groupId, String actionId, long[] resourceIds,
			PermissionCheckerBag permissionCheckerBag)
		throws PortalException, SystemException {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		int block = 1;

		// Return false if there is no resources

		if ((Validator.isNull(actionId)) || (resourceIds == null) ||
			(resourceIds.length == 0)) {

			return false;
		}

		List permissions = permissionFinder.findByA_R(actionId, resourceIds);

		// Return false if there are no permissions

		if (permissions.size() == 0) {
			return false;
		}

		// Record logs with the first resource id

		long resourceId = resourceIds[0];

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		//List userGroups = permissionCheckerBag.getUserGroups();
		//List userOrgs = permissionCheckerBag.getUserOrgs();
		//List userOrgGroups = permissionCheckerBag.getUserOrgGroups();
		//List userUserGroupGroups =
		//	permissionCheckerBag.getUserUserGroupGroups();
		List groups = permissionCheckerBag.getGroups();
		List roles = permissionCheckerBag.getRoles();

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Check the organization and community intersection table. Break out of
		// this method if the user has one of the permissions set at the
		// intersection because that takes priority.

		//if (checkOrgGroupPermission(userOrgs, userGroups, permissions)) {
		//	return true;
		//}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		if (PermissionCheckerImpl.USER_CHECK_ALGORITHM == 1) {
			return hasUserPermissions_1(
				userId, actionId, resourceId, permissions, groups, groupId,
				stopWatch, block);
		}
		else if (PermissionCheckerImpl.USER_CHECK_ALGORITHM == 2) {
			return hasUserPermissions_2(
				userId, actionId, resourceId, permissions, groups, groupId,
				stopWatch, block);
		}
		else if (PermissionCheckerImpl.USER_CHECK_ALGORITHM == 3) {
			return hasUserPermissions_3(
				userId, actionId, resourceId, permissions, groups, roles,
				stopWatch, block);
		}
		else if (PermissionCheckerImpl.USER_CHECK_ALGORITHM == 4) {
			return hasUserPermissions_4(
				userId, actionId, resourceId, permissions, groups, roles,
				stopWatch, block);
		}

		return false;
	}

	public void setGroupPermissions(
			long groupId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		Group group = groupPersistence.findByPrimaryKey(groupId);

		Iterator itr = permissionFinder.findByG_R(
			groupId, resourceId).iterator();

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			groupPersistence.removePermission(groupId, permission);
		}

		List permissions = getPermissions(
			group.getCompanyId(), actionIds, resourceId);

		groupPersistence.addPermissions(groupId, permissions);

		PermissionCacheUtil.clearCache();
	}

	public void setGroupPermissions(
			String className, String classPK, long groupId,
			String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		long associatedGroupId = 0;

		if (className.equals(Organization.class.getName())) {
			long organizationId = GetterUtil.getLong(classPK);

			Organization organization =
				organizationPersistence.findByPrimaryKey(organizationId);

			orgGroupPermissionFinder.removeByO_G_R(
				organizationId, groupId, resourceId);

			associatedGroupId = organization.getGroup().getGroupId();
		}
		else if (className.equals(UserGroup.class.getName())) {
			long userGroupId = GetterUtil.getLong(classPK);

			UserGroup userGroup = userGroupPersistence.findByPrimaryKey(
				userGroupId);

			associatedGroupId = userGroup.getGroup().getGroupId();
		}

		setGroupPermissions(associatedGroupId, actionIds, resourceId);
	}

	public void setOrgGroupPermissions(
			long organizationId, long groupId, String[] actionIds,
			long resourceId)
		throws PortalException, SystemException {

		Organization organization =
			organizationPersistence.findByPrimaryKey(organizationId);

		long orgGroupId = organization.getGroup().getGroupId();

		Iterator itr = permissionPersistence.findByResourceId(
			resourceId).iterator();

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			groupPersistence.removePermission(orgGroupId, permission);
		}

		itr = getPermissions(
			organization.getCompanyId(), actionIds, resourceId).iterator();

		orgGroupPermissionFinder.removeByO_G_R(
			organizationId, groupId, resourceId);

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			OrgGroupPermissionPK pk = new OrgGroupPermissionPK(
				organizationId, groupId, permission.getPermissionId());

			OrgGroupPermission orgGroupPermission =
				orgGroupPermissionPersistence.create(pk);

			orgGroupPermissionPersistence.update(orgGroupPermission);
		}

		PermissionCacheUtil.clearCache();
	}

	public void setRolePermission(
			long roleId, long companyId, String name, int scope, String primKey,
			String actionId)
		throws PortalException, SystemException {

		if (scope == ResourceImpl.SCOPE_COMPANY) {

			// Remove group permission

			unsetRolePermissions(
				roleId, companyId, name, ResourceImpl.SCOPE_GROUP, actionId);
		}
		else if (scope == ResourceImpl.SCOPE_GROUP) {

			// Remove company permission

			unsetRolePermissions(
				roleId, companyId, name, ResourceImpl.SCOPE_COMPANY, actionId);
		}
		else if (scope == ResourceImpl.SCOPE_INDIVIDUAL) {
			throw new NoSuchPermissionException();
		}

		Resource resource = resourceLocalService.addResource(
			companyId, name, scope, primKey);

		Permission permission = null;

		try {
			permission = permissionPersistence.findByA_R(
				actionId, resource.getResourceId());
		}
		catch (NoSuchPermissionException nspe) {
			long permissionId = counterLocalService.increment(
				Permission.class.getName());

			permission = permissionPersistence.create(permissionId);

			permission.setCompanyId(companyId);
			permission.setActionId(actionId);
			permission.setResourceId(resource.getResourceId());

			permissionPersistence.update(permission);
		}

		rolePersistence.addPermission(roleId, permission);

		PermissionCacheUtil.clearCache();
	}

	public void setRolePermissions(
			long roleId, long companyId, String name, int scope, String primKey,
			String[] actionIds)
		throws PortalException, SystemException {

		for (int i = 0; i < actionIds.length; i++) {
			String actionId = actionIds[i];

			setRolePermission(
				roleId, companyId, name, scope, primKey, actionId);
		}
	}

	public void setRolePermissions(
			long roleId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		Role role = rolePersistence.findByPrimaryKey(roleId);

		List permissions = permissionFinder.findByR_R(roleId, resourceId);

		rolePersistence.removePermissions(roleId, permissions);

		permissions = getPermissions(
			role.getCompanyId(), actionIds, resourceId);

		rolePersistence.addPermissions(roleId, permissions);

		PermissionCacheUtil.clearCache();
	}

	public void setUserPermissions(
			long userId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		List permissions = permissionFinder.findByU_R(userId, resourceId);

		userPersistence.removePermissions(userId, permissions);

		permissions = getPermissions(
			user.getCompanyId(), actionIds, resourceId);

		userPersistence.addPermissions(userId, permissions);

		PermissionCacheUtil.clearCache();
	}

	public void unsetRolePermission(long roleId, long permissionId)
		throws SystemException, PortalException {

		try {
			Permission permission = permissionPersistence.findByPrimaryKey(
				permissionId);

			rolePersistence.removePermission(roleId, permission);
		}
		catch (NoSuchPermissionException nspe) {
		}

		PermissionCacheUtil.clearCache();
	}

	public void unsetRolePermission(
			long roleId, long companyId, String name, int scope, String primKey,
			String actionId)
		throws PortalException, SystemException {

		try {
			ResourceCode resourceCode =
				resourceCodeLocalService.getResourceCode(
					companyId, name, scope);

			Resource resource = resourcePersistence.findByC_P(
				resourceCode.getCodeId(), primKey);

			Permission permission = permissionPersistence.findByA_R(
				actionId, resource.getResourceId());

			rolePersistence.removePermission(roleId, permission);
		}
		catch (NoSuchPermissionException nspe) {
		}
		catch (NoSuchResourceException nsre) {
		}

		PermissionCacheUtil.clearCache();
	}

	public void unsetRolePermissions(
			long roleId, long companyId, String name, int scope,
			String actionId)
		throws PortalException, SystemException {

		ResourceCode resourceCode = resourceCodeLocalService.getResourceCode(
			companyId, name, scope);

		Iterator itr = resourcePersistence.findByCodeId(
			resourceCode.getCodeId()).iterator();

		while (itr.hasNext()) {
			Resource resource = (Resource)itr.next();

			try {
				Permission permission = permissionPersistence.findByA_R(
					actionId, resource.getResourceId());

				rolePersistence.removePermission(roleId, permission);
			}
			catch (NoSuchPermissionException nspe) {
			}
		}

		PermissionCacheUtil.clearCache();
	}

	public void unsetUserPermissions(
			long userId, String[] actionIds, long resourceId)
		throws PortalException, SystemException {

		List permissions = permissionFinder.findByU_A_R(
			userId, actionIds, resourceId);

		userPersistence.removePermissions(userId, permissions);

		PermissionCacheUtil.clearCache();
	}

	protected boolean checkOrgGroupPermission(
			List organizations, List groups, List permissions)
		throws PortalException, SystemException {

		for (int i = 0; i < permissions.size(); i++) {
			Permission permission = (Permission)permissions.get(i);

			if (checkOrgGroupPermission(organizations, groups, permission)) {
				return true;
			}
		}

		return false;
	}

	protected boolean checkOrgGroupPermission(
			List organizations, List groups, Permission permission)
		throws PortalException, SystemException {

		// Do not check for an OrgGroupPermission intersection unless there is
		// at least one organization and one group to check

		if ((organizations.size() == 0) || (groups.size() == 0)) {
			return false;
		}

		// Do not check unless the OrgGroupPermission intersection contains at
		// least one permission

		List orgGroupPermissions =
			orgGroupPermissionPersistence.findByPermissionId(
				permission.getPermissionId());

		if (orgGroupPermissions.size() == 0) {
			return false;
		}

		Iterator itr = orgGroupPermissions.iterator();

		while (itr.hasNext()) {
			OrgGroupPermission orgGroupPermission =
				(OrgGroupPermission)itr.next();

			if (orgGroupPermission.containsOrganization(organizations) &&
				orgGroupPermission.containsGroup(groups)) {

				return true;
			}
		}

		// Throw an exception so that we do not continue checking permissions.
		// The user has a specific permission given in the OrgGroupPermission
		// intersection that prohibits him from going further.

		throw new NoSuchPermissionException(
			"User has a permission in OrgGroupPermission that does not match");
	}

	protected boolean hasUserPermissions_1(
			long userId, String actionId, long resourceId, List permissions,
			List groups, long groupId, StopWatch stopWatch, int block)
		throws PortalException, SystemException {

		// Is the user connected to one of the permissions via group or
		// organization roles?

		if (groups.size() > 0) {
			if (permissionFinder.countByGroupsRoles(permissions, groups) > 0) {
				return true;
			}
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Is the user associated with groups or organizations that are directly
		// connected to one of the permissions?

		if (groups.size() > 0) {
			if (permissionFinder.countByGroupsPermissions(
					permissions, groups) > 0) {

				return true;
			}
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Is the user connected to one of the permissions via user roles?

		if (permissionFinder.countByUsersRoles(permissions, userId) > 0) {
			return true;
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Is the user connected to one of the permissions via user group roles?

		if (permissionFinder.countByUserGroupRole(
				permissions, userId, groupId) > 0) {

			return true;
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Is the user directly connected to one of the permissions?

		if (permissionFinder.countByUsersPermissions(permissions, userId) > 0) {
			return true;
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		return false;
	}

	protected boolean hasUserPermissions_2(
			long userId, String actionId, long resourceId, List permissions,
			List groups, long groupId, StopWatch stopWatch, int block)
		throws PortalException, SystemException {

		// Call countByGroupsRoles, countByGroupsPermissions, countByUsersRoles,
		// countByUserGroupRole, and countByUsersPermissions in one method

		if (permissionFinder.containsPermissions_2(
				permissions, userId, groups, groupId)) {

			return true;
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		return false;
	}

	protected boolean hasUserPermissions_3(
			long userId, String actionId, long resourceId, List permissions,
			List groups, List roles, StopWatch stopWatch, int block)
		throws PortalException, SystemException {

		// Is the user associated with groups or organizations that are directly
		// connected to one of the permissions?

		if (groups.size() > 0) {
			if (permissionFinder.countByGroupsPermissions(
					permissions, groups) > 0) {

				return true;
			}
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Is the user associated with a role that is directly connected to one
		// of the permissions?

		if (roles.size() > 0) {
			if (permissionFinder.countByRolesPermissions(
					permissions, roles) > 0) {

				return true;
			}
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		// Is the user directly connected to one of the permissions?

		if (permissionFinder.countByUsersPermissions(permissions, userId) > 0) {
			return true;
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		return false;
	}

	protected boolean hasUserPermissions_4(
			long userId, String actionId, long resourceId, List permissions,
			List groups, List roles, StopWatch stopWatch, int block)
		throws PortalException, SystemException {

		// Call countByGroupsPermissions, countByRolesPermissions, and
		// countByUsersPermissions in one method

		if (permissionFinder.containsPermissions_4(
				permissions, userId, groups, roles)) {

			return true;
		}

		logHasUserPermissions(userId, actionId, resourceId, stopWatch, block++);

		return false;
	}

	protected void logHasUserPermissions(
		long userId, String actionId, long resourceId, StopWatch stopWatch,
		int block) {

		if (!_log.isDebugEnabled()) {
			return;
		}

		_log.debug(
			"Checking user permissions block " + block + " for " + userId +
				" " + actionId + " " + resourceId + " takes " +
					stopWatch.getTime() + " ms");
	}

	private static Log _log =
		LogFactory.getLog(PermissionLocalServiceImpl.class);

}
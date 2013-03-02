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
import com.liferay.portal.PortalException;
import com.liferay.portal.ResourceActionsException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.PermissionsListFilter;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.security.permission.PermissionsListFilterFactory;
import com.liferay.portal.security.permission.ResourceActionsUtil;
import com.liferay.portal.service.base.ResourceLocalServiceBaseImpl;
import com.liferay.portal.util.comparator.ResourceComparator;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ResourceLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Wilson S. Man
 *
 */
public class ResourceLocalServiceImpl extends ResourceLocalServiceBaseImpl {

	public void addModelResources(
			long companyId, long groupId, long userId, String name,
			long primKey, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		addModelResources(
			companyId, groupId, userId, name, String.valueOf(primKey),
			communityPermissions, guestPermissions);
	}

	public void addModelResources(
			long companyId, long groupId, long userId, String name,
			String primKey, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		validate(companyId, name, false);

		// Company

		addResource(
			companyId, name, ResourceImpl.SCOPE_COMPANY,
			String.valueOf(companyId));

		// Guest

		Group guestGroup = groupLocalService.getGroup(
			companyId, GroupImpl.GUEST);

		addResource(
			companyId, name, ResourceImpl.SCOPE_GROUP,
			String.valueOf(guestGroup.getGroupId()));

		// Group

		if ((groupId > 0) && (guestGroup.getGroupId() != groupId)) {
			addResource(
				companyId, name, ResourceImpl.SCOPE_GROUP,
				String.valueOf(groupId));
		}

		if (primKey != null) {

			// Individual

			Resource resource = addResource(
				companyId, name, ResourceImpl.SCOPE_INDIVIDUAL, primKey);

			// Permissions

			List permissionsList = permissionLocalService.addPermissions(
				companyId, name, resource.getResourceId(), false);

			// User permissions

			PermissionsListFilter permissionsListFilter =
				PermissionsListFilterFactory.getInstance();

			long defaultUserId = userLocalService.getDefaultUserId(companyId);

			if ((userId > 0) && (userId != defaultUserId)) {
				List userPermissionsList =
					permissionsListFilter.filterUserPermissions(
						companyId, groupId, userId, name, primKey, false,
						permissionsList);

				userPersistence.addPermissions(userId, userPermissionsList);
			}

			// Community permissions

			if (groupId > 0) {
				groupPersistence.findByPrimaryKey(groupId);

				if (communityPermissions == null) {
					communityPermissions = new String[0];
				}

				List communityPermissionsList =
					permissionLocalService.getPermissions(
						companyId, communityPermissions,
						resource.getResourceId());

				communityPermissionsList =
					permissionsListFilter.filterCommunityPermissions(
						companyId, groupId, userId, name, primKey, false,
						communityPermissionsList);

				groupPersistence.addPermissions(
					groupId, communityPermissionsList);
			}

			// Guest permissions

			if (guestPermissions == null) {
				guestPermissions = new String[0];
			}

			List guestPermissionsList =
				permissionLocalService.getPermissions(
					companyId, guestPermissions, resource.getResourceId());

			guestPermissionsList = permissionsListFilter.filterGuestPermissions(
				companyId, groupId, userId, name, primKey, false,
				guestPermissionsList);

			userPersistence.addPermissions(defaultUserId, guestPermissionsList);
		}
	}

	public Resource addResource(
			long companyId, String name, int scope, String primKey)
		throws PortalException, SystemException {

		ResourceCode resourceCode = resourceCodeLocalService.getResourceCode(
			companyId, name, scope);

		Resource resource = resourcePersistence.fetchByC_P(
			resourceCode.getCodeId(), primKey);

		if (resource == null) {
			long resourceId = counterLocalService.increment(
				Resource.class.getName());

			resource = resourcePersistence.create(resourceId);

			resource.setCodeId(resourceCode.getCodeId());
			resource.setPrimKey(primKey);

			resourcePersistence.update(resource);
		}

		return resource;
	}

	public void addResources(
			long companyId, long groupId, String name, boolean portletActions)
		throws PortalException, SystemException {

		addResources(
			companyId, groupId, 0, name, null, portletActions, false, false);
	}

	public void addResources(
			long companyId, long groupId, long userId, String name,
			long primKey, boolean portletActions,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		addResources(
			companyId, groupId, userId, name, String.valueOf(primKey),
			portletActions, addCommunityPermissions, addGuestPermissions);
	}

	public void addResources(
			long companyId, long groupId, long userId, String name,
			String primKey, boolean portletActions,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		validate(companyId, name, portletActions);

		logAddResources(name, primKey, stopWatch, 1);

		// Company

		addResource(
			companyId, name, ResourceImpl.SCOPE_COMPANY,
			String.valueOf(companyId));

		logAddResources(name, primKey, stopWatch, 2);

		if (groupId > 0) {
			addResource(
				companyId, name, ResourceImpl.SCOPE_GROUP,
				String.valueOf(groupId));
		}

		logAddResources(name, primKey, stopWatch, 3);

		if (primKey != null) {

			// Individual

			Resource resource = addResource(
				companyId, name, ResourceImpl.SCOPE_INDIVIDUAL, primKey);

			logAddResources(name, primKey, stopWatch, 4);

			// Permissions

			List permissionsList = permissionLocalService.addPermissions(
				companyId, name, resource.getResourceId(), portletActions);

			logAddResources(name, primKey, stopWatch, 5);

			// User permissions

			PermissionsListFilter permissionsListFilter =
				PermissionsListFilterFactory.getInstance();

			long defaultUserId = userLocalService.getDefaultUserId(companyId);

			if ((userId > 0) && (userId != defaultUserId)) {
				List userPermissionsList =
					permissionsListFilter.filterUserPermissions(
						companyId, groupId, userId, name, primKey,
						portletActions, permissionsList);

				userPersistence.addPermissions(userId, userPermissionsList);
			}

			logAddResources(name, primKey, stopWatch, 6);

			// Community permissions

			if ((groupId > 0) && addCommunityPermissions) {
				addCommunityPermissions(
					companyId, groupId, userId, name, resource, portletActions);
			}

			logAddResources(name, primKey, stopWatch, 7);

			// Guest permissions

			if (addGuestPermissions) {

				// Don't add guest permissions when you've already added
				// community permissions and the given community is the guest
				// community.

				addGuestPermissions(
					companyId, groupId, userId, name, resource, portletActions);
			}

			logAddResources(name, primKey, stopWatch, 9);
		}
	}

	public void deleteResource(long resourceId)
		throws PortalException, SystemException {

		try {
			Resource resource = resourcePersistence.findByPrimaryKey(
				resourceId);

			deleteResource(resource);
		}
		catch (NoSuchResourceException nsre) {
			_log.warn(nsre);
		}
	}

	public void deleteResource(Resource resource)
		throws PortalException, SystemException {

		// Permissions

		Iterator itr = permissionPersistence.findByResourceId(
			resource.getResourceId()).iterator();

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			orgGroupPermissionPersistence.removeByPermissionId(
				permission.getPermissionId());
		}

		permissionPersistence.removeByResourceId(resource.getResourceId());

		// Resource

		resourcePersistence.remove(resource.getResourceId());
	}

	public void deleteResource(
			long companyId, String name, int scope, long primKey)
		throws PortalException, SystemException {

		deleteResource(companyId, name, scope, String.valueOf(primKey));
	}

	public void deleteResource(
			long companyId, String name, int scope, String primKey)
		throws PortalException, SystemException {

		try {
			Resource resource = getResource(companyId, name, scope, primKey);

			deleteResource(resource.getResourceId());
		}
		catch (NoSuchResourceException nsre) {
			_log.warn(nsre);
		}
	}

	public void deleteResources(String name)
		throws PortalException, SystemException {

		Iterator itr = resourceFinder.findByName(name).iterator();

		while (itr.hasNext()) {
			Resource resource = (Resource)itr.next();

			deleteResource(resource);
		}
	}

	public long getLatestResourceId()
		throws PortalException, SystemException {

		List list = resourcePersistence.findAll(0, 1, new ResourceComparator());

		if (list.size() == 0) {
			return 0;
		}
		else {
			Resource resource = (Resource)list.get(0);

			return resource.getResourceId();
		}
	}

	public Resource getResource(long resourceId)
		throws PortalException, SystemException {

		return resourcePersistence.findByPrimaryKey(resourceId);
	}

	public List getResources() throws SystemException {
		return resourcePersistence.findAll();
	}

	public Resource getResource(
			long companyId, String name, int scope, String primKey)
		throws PortalException, SystemException {

		ResourceCode resourceCode = resourceCodeLocalService.getResourceCode(
			companyId, name, scope);

		return resourcePersistence.findByC_P(resourceCode.getCodeId(), primKey);
	}

	protected void addCommunityPermissions(
			long companyId, long groupId, long userId, String name,
			Resource resource, boolean portletActions)
		throws PortalException, SystemException {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		Group group = groupPersistence.findByPrimaryKey(groupId);

		long resourceId = resource.getResourceId();
		String primKey = resource.getPrimKey();

		logAddCommunityPermissions(groupId, name, resourceId, stopWatch, 1);

		List actions = null;

		if (portletActions) {
			actions =
				ResourceActionsUtil.getPortletResourceCommunityDefaultActions(
					name);
		}
		else {
			actions =
				ResourceActionsUtil.getModelResourceCommunityDefaultActions(
					name);
		}

		logAddCommunityPermissions(groupId, name, resourceId, stopWatch, 2);

		String[] actionIds = (String[])actions.toArray(new String[0]);

		List communityPermissionsList = permissionLocalService.getPermissions(
			group.getCompanyId(), actionIds, resourceId);

		logAddCommunityPermissions(groupId, name, resourceId, stopWatch, 3);

		PermissionsListFilter permissionsListFilter =
			PermissionsListFilterFactory.getInstance();

		communityPermissionsList =
			permissionsListFilter.filterCommunityPermissions(
				companyId, groupId, userId, name, primKey, portletActions,
				communityPermissionsList);

		logAddCommunityPermissions(groupId, name, resourceId, stopWatch, 4);

		groupPersistence.addPermissions(groupId, communityPermissionsList);

		logAddCommunityPermissions(groupId, name, resourceId, stopWatch, 5);
	}

	protected void addGuestPermissions(
			long companyId, long groupId, long userId, String name,
			Resource resource, boolean portletActions)
		throws PortalException, SystemException {

		long defaultUserId = userLocalService.getDefaultUserId(companyId);

		List actions = null;

		if (portletActions) {
			actions =
				ResourceActionsUtil.getPortletResourceGuestDefaultActions(name);
		}
		else {
			actions =
				ResourceActionsUtil.getModelResourceGuestDefaultActions(name);
		}

		String[] actionIds = (String[])actions.toArray(new String[0]);

		List guestPermissionsList = permissionLocalService.getPermissions(
			companyId, actionIds, resource.getResourceId());

		PermissionsListFilter permissionsListFilter =
			PermissionsListFilterFactory.getInstance();

		guestPermissionsList =
			permissionsListFilter.filterGuestPermissions(
				companyId, groupId, userId, name, resource.getPrimKey(),
				portletActions, guestPermissionsList);

		userPersistence.addPermissions(defaultUserId, guestPermissionsList);
	}

	protected void logAddCommunityPermissions(
		long groupId, String name, long resourceId, StopWatch stopWatch,
		int block) {

		if (!_log.isDebugEnabled()) {
			return;
		}

		_log.debug(
			"Adding community permissions block " + block + " for " + groupId +
				" " + name + " " + resourceId + " takes " +
					stopWatch.getTime() + " ms");
	}

	protected void logAddResources(
		String name, String primKey, StopWatch stopWatch, int block) {

		if (!_log.isDebugEnabled()) {
			return;
		}

		_log.debug(
			"Adding resources block " + block + " for " + name + " " + primKey +
				" takes " + stopWatch.getTime() + " ms");
	}

	protected void validate(
			long companyId, String name, boolean portletActions)
		throws PortalException, SystemException {

		List actions = null;

		if (portletActions) {
			actions =
				ResourceActionsUtil.getPortletResourceActions(companyId, name);
		}
		else {
			actions = ResourceActionsUtil.getModelResourceActions(name);
		}

		if (actions.size() == 0) {
			throw new ResourceActionsException(
				"There are no actions associated with the resource " + name);
		}
	}

	private static Log _log = LogFactory.getLog(ResourceLocalServiceImpl.class);

}
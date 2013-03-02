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

package com.liferay.portal.security.permission;

import com.liferay.portal.NoSuchResourceException;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.security.permission.PermissionCheckerBag;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Resource;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.OrganizationLocalServiceUtil;
import com.liferay.portal.service.PermissionLocalServiceUtil;
import com.liferay.portal.service.ResourceLocalServiceUtil;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.service.UserGroupLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.admin.util.OmniadminUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.UniqueList;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletRequest;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PermissionCheckerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionCheckerImpl implements PermissionChecker, Serializable {

	public static final int USER_CHECK_ALGORITHM = GetterUtil.getInteger(
		PropsUtil.get(PropsUtil.PERMISSIONS_USER_CHECK_ALGORITHM));

	public PermissionCheckerImpl() {
	}

	public void init(User user, boolean checkGuest) {
		this.user = user;

		if (user.isDefaultUser()) {
			this.defaultUserId = user.getUserId();
			this.signedIn = false;
		}
		else {
			try {
				this.defaultUserId = UserLocalServiceUtil.getDefaultUserId(
					user.getCompanyId());
			}
			catch (Exception e) {
				_log.error(e, e);
			}

			this.signedIn = true;
		}

		this.checkGuest = checkGuest;
	}

	public void recycle() {
		user = null;
		defaultUserId = 0;
		signedIn = false;
		checkGuest = false;
		omniadmin = null;
		companyAdmins.clear();
		bags.clear();
		resetValues();
	}

	public void setValues(PortletRequest req) {

		// This method is called in com.liferay.portlet.StrutsPortlet to allow
		// developers to hook in additiona parameters from the portlet request.
		// Don't overwrite this method unless you're using Liferay in a 2 tier
		// environment and don't expect to make remote calls. Remote calls to
		// service beans will not have any values set from the portlet request.

	}

	public void resetValues() {
	}

	public User getUser() {
		return user;
	}

	public void setUser(User user) {
		this.user = user;
	}

	public long getUserId() {
		return user.getUserId();
	}

	public boolean isSignedIn() {
		return signedIn;
	}

	public void setSignedIn(boolean signedIn) {
		this.signedIn = signedIn;
	}

	public boolean isCheckGuest() {
		return checkGuest;
	}

	public void setCheckGuest(boolean checkGuest) {
		this.checkGuest = checkGuest;
	}

	public boolean hasPermission(
		long groupId, String name, long primKey, String actionId) {

		return hasPermission(groupId, name, String.valueOf(primKey), actionId);
	}

	public boolean hasPermission(
		long groupId, String name, String primKey, String actionId) {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		Group group = null;

		// If the current group is staging, the live group should be checked for
		// permissions instead

		try {
			if (groupId > 0) {
				group = GroupLocalServiceUtil.getGroup(groupId);

				if (group.isStagingGroup()) {
					if (primKey.equals(String.valueOf(groupId))) {
						primKey = String.valueOf(group.getLiveGroupId());
					}

					groupId = group.getLiveGroupId();
					group = group.getLiveGroup();
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		PermissionCheckerBag bag = getBag(groupId);

		if (signedIn && (bag == null)) {
			try {

				// If we are checking permissions on an object that belongs to a
				// community, then it's only necessary to check the group that
				// represents the community and not all the groups that the user
				// belongs to. This is so because an object cannot belong to
				// more than one community.

				List userGroups = new ArrayList();
				//List userGroups = UserUtil.getGroups(userId);

				if (groupId > 0) {
					if (GroupLocalServiceUtil.hasUserGroup(
							user.getUserId(), groupId)) {

						userGroups.add(group);
					}
				}

				List userOrgs =	getUserOrgs(user.getUserId());

				List userOrgGroups =
					GroupLocalServiceUtil.getOrganizationsGroups(userOrgs);

				List userUserGroups =
					UserGroupLocalServiceUtil.getUserUserGroups(
						user.getUserId());

				List userUserGroupGroups =
					GroupLocalServiceUtil.getUserGroupsGroups(userUserGroups);

				List groups = new ArrayList(
					userGroups.size() + userOrgGroups.size() +
						userUserGroupGroups.size());

				groups.addAll(userGroups);
				groups.addAll(userOrgGroups);
				groups.addAll(userUserGroupGroups);

				List roles = null;

				if ((USER_CHECK_ALGORITHM == 3) ||
					(USER_CHECK_ALGORITHM == 4)) {

					roles = RoleLocalServiceUtil.getUserRelatedRoles(
						user.getUserId(), groups);

					List userGroupRoles =
						RoleLocalServiceUtil.getUserGroupRoles(
							user.getUserId(), groupId);

					roles.addAll(userGroupRoles);
				}
				else {
					roles = new ArrayList();
				}

				if (_log.isDebugEnabled()) {
					_log.debug(
						"Creating bag for " + groupId + " " + name + " " +
							primKey + " " + actionId + " takes " +
								stopWatch.getTime() + " ms");
				}

				bag = new PermissionCheckerBagImpl(
					user.getUserId(), userGroups, userOrgs, userOrgGroups,
					userUserGroupGroups, groups, roles);

				putBag(groupId, bag);
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}

		Boolean value = PermissionCacheUtil.hasPermission(
			user.getUserId(), groupId, name, primKey, actionId);

		if (value == null) {
			value = Boolean.valueOf(
				hasPermissionImpl(groupId, name, primKey, actionId));

			PermissionCacheUtil.putPermission(
				user.getUserId(), groupId, name, primKey, actionId, value);

			if (_log.isDebugEnabled()) {
				_log.debug(
					"Checking permission for " + groupId + " " + name + " " +
						primKey + " " + actionId + " takes " +
							stopWatch.getTime() + " ms");
			}
		}

		return value.booleanValue();
	}

	public boolean hasUserPermission(
		long groupId, String name, String primKey, String actionId,
		boolean checkAdmin) {

		try {
			return hasUserPermissionImpl(
				groupId, name, primKey, actionId, checkAdmin);
		}
		catch (Exception e) {
			_log.error(e, e);

			return false;
		}
	}

	public boolean isOmniadmin() {
		if (omniadmin == null) {
			omniadmin = Boolean.valueOf(OmniadminUtil.isOmniadmin(getUserId()));
		}

		return omniadmin.booleanValue();
	}

	public boolean isCompanyAdmin(long companyId) {
		try {
			return isCompanyAdminImpl(companyId);
		}
		catch (Exception e) {
			_log.error(e, e);

			return false;
		}
	}

	public boolean isCommunityAdmin(long groupId) {
		try {
			return isCommunityAdminImpl(groupId);
		}
		catch (Exception e) {
			_log.error(e, e);

			return false;
		}
	}

	public boolean isCommunityOwner(long groupId) {
		try {
			return isCommunityOwnerImpl(groupId);
		}
		catch (Exception e) {
			_log.error(e, e);

			return false;
		}
	}

	protected PermissionCheckerBag getBag(long groupId) {
		return (PermissionCheckerBag)bags.get(new Long(groupId));
	}

	protected long[] getResourceIds(
			long companyId, long groupId, String name, String primKey,
			String actionId)
		throws Exception {

		// Individual

		long[] resourceIds = new long[4];

		try {
			Resource resource = ResourceLocalServiceUtil.getResource(
				companyId, name, ResourceImpl.SCOPE_INDIVIDUAL, primKey);

			resourceIds[0] = resource.getResourceId();
		}
		catch (NoSuchResourceException nsre) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Resource " + companyId + " " + name + " " +
						ResourceImpl.SCOPE_INDIVIDUAL + " " + primKey +
							" does not exist");
			}
		}

		// Group

		try {
			if (groupId > 0) {
				Resource resource = ResourceLocalServiceUtil.getResource(
					companyId, name, ResourceImpl.SCOPE_GROUP,
					String.valueOf(groupId));

				resourceIds[1] = resource.getResourceId();
			}
		}
		catch (NoSuchResourceException nsre) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Resource " + companyId + " " + name + " " +
						ResourceImpl.SCOPE_GROUP + " " + groupId +
							" does not exist");
			}
		}

		// Group template

		try {
			if (groupId > 0) {
				Resource resource = ResourceLocalServiceUtil.getResource(
					companyId, name, ResourceImpl.SCOPE_GROUP_TEMPLATE,
					String.valueOf(GroupImpl.DEFAULT_PARENT_GROUP_ID));

				resourceIds[2] = resource.getResourceId();
			}
		}
		catch (NoSuchResourceException nsre) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Resource " + companyId + " " + name + " " +
						ResourceImpl.SCOPE_GROUP_TEMPLATE + " " +
							GroupImpl.DEFAULT_PARENT_GROUP_ID +
								" does not exist");
			}
		}

		// Company

		try {
			Resource resource = ResourceLocalServiceUtil.getResource(
				companyId, name, ResourceImpl.SCOPE_COMPANY,
				String.valueOf(companyId));

			resourceIds[3] = resource.getResourceId();
		}
		catch (NoSuchResourceException nsre) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Resource " + companyId + " " + name + " " +
						ResourceImpl.SCOPE_COMPANY + " " + companyId +
							" does not exist");
			}
		}

		return resourceIds;
	}

	protected List getUserOrgs(long userId) throws Exception {
		List userOrgs = OrganizationLocalServiceUtil.getUserOrganizations(
			userId);

		if (userOrgs.size() == 0) {
			return userOrgs;
		}

		List organizations = new UniqueList();

		Iterator itr = userOrgs.iterator();

		while (itr.hasNext()){
			Organization organization = (Organization)itr.next();

			if (!organizations.contains(organization)) {
				organizations.add(organization);

				List ancestorOrganizations = OrganizationLocalServiceUtil.
					getParentOrganizations(organization.getOrganizationId());

				organizations.addAll(ancestorOrganizations);
			}
		}

		return organizations;
	}

	protected boolean hasGuestPermission(
			String name, String primKey, String actionId)
		throws Exception {

		if (name.indexOf(StringPool.PERIOD) != -1) {

			// Check unsupported model actions

			List actions = ResourceActionsUtil.
				getModelResourceGuestUnsupportedActions(name);

			if (actions.contains(actionId)) {
				return false;
			}
		}
		else {

			// Check unsupported portlet actions

			List actions = ResourceActionsUtil.
				getPortletResourceGuestUnsupportedActions(name);

			if (actions.contains(actionId)) {
				return false;
			}
		}

		long companyId = user.getCompanyId();

		long[] resourceIds = getResourceIds(
			companyId, 0, name, primKey, actionId);

		PermissionCheckerBag bag = getBag(GUEST_GROUP_BAG_ID);

		if (bag == null) {
			Group guestGroup = GroupLocalServiceUtil.getGroup(
				companyId, GroupImpl.GUEST);

			List roles = RoleLocalServiceUtil.getGroupRoles(
				guestGroup.getGroupId());

			bag = new PermissionCheckerBagImpl(
				defaultUserId, new ArrayList(), new ArrayList(),
				new ArrayList(), new ArrayList(), new ArrayList(), roles);

			putBag(GUEST_GROUP_BAG_ID, bag);
		}

		try {
			return PermissionLocalServiceUtil.hasUserPermissions(
				defaultUserId, 0, actionId, resourceIds, bag);
		}
		catch (Exception e) {
			return false;
		}
	}

	protected boolean hasPermissionImpl(
		long groupId, String name, String primKey, String actionId) {

		try {
			if (!signedIn) {
				return hasGuestPermission(name, primKey, actionId);
			}
			else {
				boolean value = false;

				if (checkGuest) {
					value = hasGuestPermission(name, primKey, actionId);
				}

				if (!value) {
					value = hasUserPermission(
						groupId, name, primKey, actionId, true);
				}

				return value;
			}
		}
		catch (Exception e) {
			_log.error(e, e);

			return false;
		}
	}

	public boolean hasUserPermissionImpl(
			long groupId, String name, String primKey, String actionId,
			boolean checkAdmin)
		throws Exception {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		long companyId = user.getCompanyId();

		boolean hasLayoutManagerPermission = true;

		// Check if the layout manager has permission to do this action for the
		// current portlet

		if ((Validator.isNotNull(name)) && (Validator.isNotNull(primKey)) &&
			(primKey.indexOf(PortletImpl.LAYOUT_SEPARATOR) != -1)) {

			hasLayoutManagerPermission =
				PortletPermissionUtil.hasLayoutManagerPermission(
					name, actionId);
		}

		if (checkAdmin &&
			(isCompanyAdminImpl(companyId) ||
				(isCommunityAdminImpl(groupId) &&
					hasLayoutManagerPermission))) {

			return true;
		}

		logHasUserPermission(groupId, name, primKey, actionId, stopWatch, 1);

		long[] resourceIds = getResourceIds(
			companyId, groupId, name, primKey, actionId);

		logHasUserPermission(groupId, name, primKey, actionId, stopWatch, 2);

		// Check if user has access to perform the action on the given
		// resource scopes. The resources are scoped to check first for an
		// individual class, then for the group that the class may belong
		// to, and then for the company that the class belongs to.

		PermissionCheckerBag bag = getBag(groupId);

		boolean value = PermissionLocalServiceUtil.hasUserPermissions(
			user.getUserId(), groupId, actionId, resourceIds, bag);

		logHasUserPermission(groupId, name, primKey, actionId, stopWatch, 3);

		return value;
	}

	protected boolean isCompanyAdminImpl(long companyId) throws Exception {
		if (isOmniadmin()) {
			return true;
		}

		String key = String.valueOf(companyId);

		Boolean value = (Boolean)companyAdmins.get(key);

		if (value == null) {
			boolean hasAdminRole = RoleLocalServiceUtil.hasUserRole(
				user.getUserId(), companyId, RoleImpl.ADMINISTRATOR, true);

			value = Boolean.valueOf(hasAdminRole);

			companyAdmins.put(key, value);
		}

		return value.booleanValue();
	}

	protected boolean isCommunityAdminImpl(long groupId) throws Exception {
		if (isOmniadmin()) {
			return true;
		}

		if (groupId <= 0) {
			return false;
		}

		Group group = GroupLocalServiceUtil.getGroup(groupId);

		if (isCompanyAdmin(group.getCompanyId())) {
			return true;
		}

		PermissionCheckerBag bag = getBag(groupId);

		if (bag == null) {
			_log.error("Bag should never be null");
		}

		if (bag.isCommunityAdmin(this, group)) {
			return true;
		}
		else {
			return false;
		}
	}

	protected boolean isCommunityOwnerImpl(long groupId) throws Exception {
		if (isOmniadmin()) {
			return true;
		}

		if (groupId <= 0) {
			return false;
		}

		Group group = GroupLocalServiceUtil.getGroup(groupId);

		if (isCompanyAdmin(group.getCompanyId())) {
			return true;
		}

		PermissionCheckerBag bag = getBag(groupId);

		if (bag == null) {
			_log.error("Bag should never be null");
		}

		if (bag.isCommunityOwner(this, group)) {
			return true;
		}
		else {
			return false;
		}
	}

	protected void logHasUserPermission(
		long groupId, String name, String primKey, String actionId,
		StopWatch stopWatch, int block) {

		if (!_log.isDebugEnabled()) {
			return;
		}

		_log.debug(
			"Checking user permission block " + block + " for " + groupId +
				" " + name + " " + primKey + " " + actionId + " takes " +
					stopWatch.getTime() + " ms");
	}

	protected void putBag(long groupId, PermissionCheckerBag bag) {
		bags.put(new Long(groupId), bag);
	}

	protected static final int GUEST_GROUP_BAG_ID = -101;

	protected static final String RESULTS_SEPARATOR = "_RESULTS_SEPARATOR_";

	protected User user;
	protected long defaultUserId;
	protected boolean signedIn;
	protected boolean checkGuest;
	protected Boolean omniadmin;
	protected Map companyAdmins = new HashMap();
	protected Map bags = CollectionFactory.getHashMap();

	private static Log _log = LogFactory.getLog(PermissionCheckerImpl.class);

}
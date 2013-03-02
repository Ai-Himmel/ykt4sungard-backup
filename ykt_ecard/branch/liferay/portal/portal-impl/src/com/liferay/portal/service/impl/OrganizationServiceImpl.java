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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.model.Organization;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.OrganizationServiceBaseImpl;
import com.liferay.portal.service.permission.GroupPermissionUtil;
import com.liferay.portal.service.permission.OrganizationPermissionUtil;
import com.liferay.portal.service.permission.PasswordPolicyPermissionUtil;
import com.liferay.portal.service.permission.PortalPermissionUtil;

import java.util.List;

/**
 * <a href="OrganizationServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class OrganizationServiceImpl extends OrganizationServiceBaseImpl {

	public void addGroupOrganizations(long groupId, long[] organizationIds)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);

		organizationLocalService.addGroupOrganizations(
			groupId, organizationIds);
	}

	public void addPasswordPolicyOrganizations(
			long passwordPolicyId, long[] organizationIds)
		throws PortalException, SystemException {

		PasswordPolicyPermissionUtil.check(
			getPermissionChecker(), passwordPolicyId, ActionKeys.UPDATE);

		organizationLocalService.addPasswordPolicyOrganizations(
			passwordPolicyId, organizationIds);
	}

	public Organization addOrganization(
			long parentOrganizationId, String name, int type,
			boolean recursable, long regionId, long countryId, int statusId,
			String comments)
		throws PortalException, SystemException {

		if (!OrganizationPermissionUtil.contains(
				getPermissionChecker(), parentOrganizationId,
				ActionKeys.MANAGE_SUBORGANIZATIONS) &&
			!PortalPermissionUtil.contains(
				getPermissionChecker(), ActionKeys.ADD_ORGANIZATION)) {

			throw new PrincipalException(
				"User " + getUserId() + " does not have permissions to add " +
					"an organization with parent " + parentOrganizationId);
		}

		return organizationLocalService.addOrganization(
			getUserId(), parentOrganizationId, name, type, recursable,
			regionId, countryId, statusId, comments);
	}

	public void deleteOrganization(long organizationId)
		throws PortalException, SystemException {

		checkPermission(organizationId, ActionKeys.DELETE);

		organizationLocalService.deleteOrganization(organizationId);
	}

	public Organization getOrganization(long organizationId)
		throws PortalException, SystemException {

		checkPermission(organizationId, ActionKeys.VIEW);

		return organizationLocalService.getOrganization(organizationId);
	}

	public long getOrganizationId(long companyId, String name)
		throws PortalException, SystemException {

		return organizationLocalService.getOrganizationId(companyId, name);
	}

	public List getUserOrganizations(long userId)
		throws PortalException, SystemException {

		return organizationLocalService.getUserOrganizations(userId);
	}

	public void setGroupOrganizations(long groupId, long[] organizationIds)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);

		organizationLocalService.setGroupOrganizations(
			groupId, organizationIds);
	}

	public void unsetGroupOrganizations(long groupId, long[] organizationIds)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);

		organizationLocalService.unsetGroupOrganizations(
			groupId, organizationIds);
	}

	public void unsetPasswordPolicyOrganizations(
			long passwordPolicyId, long[] organizationIds)
		throws PortalException, SystemException {

		PasswordPolicyPermissionUtil.check(
			getPermissionChecker(), passwordPolicyId, ActionKeys.UPDATE);

		organizationLocalService.unsetPasswordPolicyOrganizations(
			passwordPolicyId, organizationIds);
	}

	public Organization updateOrganization(
			long organizationId, long parentOrganizationId, String name,
			int type, boolean recursable, long regionId, long countryId,
			int statusId, String comments)
		throws PortalException, SystemException {

		checkPermission(organizationId, ActionKeys.UPDATE);

		return organizationLocalService.updateOrganization(
			getUser().getCompanyId(), organizationId, parentOrganizationId,
			name, type, recursable, regionId, countryId, statusId, comments);
	}

	protected void checkPermission(long organizationId, String actionId)
		throws PortalException, SystemException {

		OrganizationPermissionUtil.check(
			getPermissionChecker(), organizationId, actionId);
	}

}
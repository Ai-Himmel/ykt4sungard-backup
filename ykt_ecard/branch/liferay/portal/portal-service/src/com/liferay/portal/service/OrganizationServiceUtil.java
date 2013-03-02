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

package com.liferay.portal.service;


/**
 * <a href="OrganizationServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.OrganizationService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.OrganizationServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.OrganizationService
 * @see com.liferay.portal.service.OrganizationServiceFactory
 *
 */
public class OrganizationServiceUtil {
	public static void addGroupOrganizations(long groupId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		organizationService.addGroupOrganizations(groupId, organizationIds);
	}

	public static void addPasswordPolicyOrganizations(long passwordPolicyId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		organizationService.addPasswordPolicyOrganizations(passwordPolicyId,
			organizationIds);
	}

	public static com.liferay.portal.model.Organization addOrganization(
		long parentOrganizationId, java.lang.String name, int type,
		boolean recursable, long regionId, long countryId, int statusId,
		java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		return organizationService.addOrganization(parentOrganizationId, name,
			type, recursable, regionId, countryId, statusId, comments);
	}

	public static void deleteOrganization(long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		organizationService.deleteOrganization(organizationId);
	}

	public static com.liferay.portal.model.Organization getOrganization(
		long organizationId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		return organizationService.getOrganization(organizationId);
	}

	public static long getOrganizationId(long companyId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		return organizationService.getOrganizationId(companyId, name);
	}

	public static java.util.List getUserOrganizations(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		return organizationService.getUserOrganizations(userId);
	}

	public static void setGroupOrganizations(long groupId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		organizationService.setGroupOrganizations(groupId, organizationIds);
	}

	public static void unsetGroupOrganizations(long groupId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		organizationService.unsetGroupOrganizations(groupId, organizationIds);
	}

	public static void unsetPasswordPolicyOrganizations(long passwordPolicyId,
		long[] organizationIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		organizationService.unsetPasswordPolicyOrganizations(passwordPolicyId,
			organizationIds);
	}

	public static com.liferay.portal.model.Organization updateOrganization(
		long organizationId, long parentOrganizationId, java.lang.String name,
		int type, boolean recursable, long regionId, long countryId,
		int statusId, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		OrganizationService organizationService = OrganizationServiceFactory.getService();

		return organizationService.updateOrganization(organizationId,
			parentOrganizationId, name, type, recursable, regionId, countryId,
			statusId, comments);
	}
}
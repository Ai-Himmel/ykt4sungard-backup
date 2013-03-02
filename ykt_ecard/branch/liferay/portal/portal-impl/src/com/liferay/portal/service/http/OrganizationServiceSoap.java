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

package com.liferay.portal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.service.OrganizationServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="OrganizationServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portal.service.OrganizationServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portal.model.OrganizationSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.Organization</code>,
 * that is translated to a <code>com.liferay.portal.model.OrganizationSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.OrganizationServiceUtil
 * @see com.liferay.portal.service.http.OrganizationServiceHttp
 * @see com.liferay.portal.service.model.OrganizationSoap
 *
 */
public class OrganizationServiceSoap {
	public static void addGroupOrganizations(long groupId,
		long[] organizationIds) throws RemoteException {
		try {
			OrganizationServiceUtil.addGroupOrganizations(groupId,
				organizationIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addPasswordPolicyOrganizations(long passwordPolicyId,
		long[] organizationIds) throws RemoteException {
		try {
			OrganizationServiceUtil.addPasswordPolicyOrganizations(passwordPolicyId,
				organizationIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.OrganizationSoap addOrganization(
		long parentOrganizationId, java.lang.String name, int type,
		boolean recursable, long regionId, long countryId, int statusId,
		java.lang.String comments) throws RemoteException {
		try {
			com.liferay.portal.model.Organization returnValue = OrganizationServiceUtil.addOrganization(parentOrganizationId,
					name, type, recursable, regionId, countryId, statusId,
					comments);

			return com.liferay.portal.model.OrganizationSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteOrganization(long organizationId)
		throws RemoteException {
		try {
			OrganizationServiceUtil.deleteOrganization(organizationId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.OrganizationSoap getOrganization(
		long organizationId) throws RemoteException {
		try {
			com.liferay.portal.model.Organization returnValue = OrganizationServiceUtil.getOrganization(organizationId);

			return com.liferay.portal.model.OrganizationSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static long getOrganizationId(long companyId, java.lang.String name)
		throws RemoteException {
		try {
			long returnValue = OrganizationServiceUtil.getOrganizationId(companyId,
					name);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.OrganizationSoap[] getUserOrganizations(
		long userId) throws RemoteException {
		try {
			java.util.List returnValue = OrganizationServiceUtil.getUserOrganizations(userId);

			return com.liferay.portal.model.OrganizationSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void setGroupOrganizations(long groupId,
		long[] organizationIds) throws RemoteException {
		try {
			OrganizationServiceUtil.setGroupOrganizations(groupId,
				organizationIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetGroupOrganizations(long groupId,
		long[] organizationIds) throws RemoteException {
		try {
			OrganizationServiceUtil.unsetGroupOrganizations(groupId,
				organizationIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetPasswordPolicyOrganizations(long passwordPolicyId,
		long[] organizationIds) throws RemoteException {
		try {
			OrganizationServiceUtil.unsetPasswordPolicyOrganizations(passwordPolicyId,
				organizationIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.OrganizationSoap updateOrganization(
		long organizationId, long parentOrganizationId, java.lang.String name,
		int type, boolean recursable, long regionId, long countryId,
		int statusId, java.lang.String comments) throws RemoteException {
		try {
			com.liferay.portal.model.Organization returnValue = OrganizationServiceUtil.updateOrganization(organizationId,
					parentOrganizationId, name, type, recursable, regionId,
					countryId, statusId, comments);

			return com.liferay.portal.model.OrganizationSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(OrganizationServiceSoap.class);
}
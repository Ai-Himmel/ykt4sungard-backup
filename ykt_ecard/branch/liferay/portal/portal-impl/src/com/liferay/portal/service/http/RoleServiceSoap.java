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
import com.liferay.portal.service.RoleServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="RoleServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portal.service.RoleServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portal.model.RoleSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.Role</code>,
 * that is translated to a <code>com.liferay.portal.model.RoleSoap</code>.
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
 * @see com.liferay.portal.service.RoleServiceUtil
 * @see com.liferay.portal.service.http.RoleServiceHttp
 * @see com.liferay.portal.service.model.RoleSoap
 *
 */
public class RoleServiceSoap {
	public static com.liferay.portal.model.RoleSoap addRole(
		java.lang.String name, java.lang.String description, int type)
		throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.addRole(name,
					description, type);

			return com.liferay.portal.model.RoleSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addUserRoles(long userId, long[] roleIds)
		throws RemoteException {
		try {
			RoleServiceUtil.addUserRoles(userId, roleIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteRole(long roleId) throws RemoteException {
		try {
			RoleServiceUtil.deleteRole(roleId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap getGroupRole(
		long companyId, long groupId) throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.getGroupRole(companyId,
					groupId);

			return com.liferay.portal.model.RoleSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap[] getGroupRoles(
		long groupId) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getGroupRoles(groupId);

			return com.liferay.portal.model.RoleSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap getRole(long roleId)
		throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.getRole(roleId);

			return com.liferay.portal.model.RoleSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap getRole(long companyId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.getRole(companyId,
					name);

			return com.liferay.portal.model.RoleSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap[] getUserGroupRoles(
		long userId, long groupId) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getUserGroupRoles(userId,
					groupId);

			return com.liferay.portal.model.RoleSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap[] getUserRelatedRoles(
		long userId, java.util.List groups) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getUserRelatedRoles(userId,
					groups);

			return com.liferay.portal.model.RoleSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap[] getUserRoles(long userId)
		throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getUserRoles(userId);

			return com.liferay.portal.model.RoleSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasUserRole(long userId, long companyId,
		java.lang.String name, boolean inherited) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.hasUserRole(userId,
					companyId, name, inherited);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasUserRoles(long userId, long companyId,
		java.lang.String[] names, boolean inherited) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.hasUserRoles(userId,
					companyId, names, inherited);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetUserRoles(long userId, long[] roleIds)
		throws RemoteException {
		try {
			RoleServiceUtil.unsetUserRoles(userId, roleIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleSoap updateRole(long roleId,
		java.lang.String name, java.lang.String description)
		throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.updateRole(roleId,
					name, description);

			return com.liferay.portal.model.RoleSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(RoleServiceSoap.class);
}
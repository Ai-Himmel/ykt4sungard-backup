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
import com.liferay.portal.service.GroupServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="GroupServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portal.service.GroupServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portal.model.GroupSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.Group</code>,
 * that is translated to a <code>com.liferay.portal.model.GroupSoap</code>.
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
 * @see com.liferay.portal.service.GroupServiceUtil
 * @see com.liferay.portal.service.http.GroupServiceHttp
 * @see com.liferay.portal.service.model.GroupSoap
 *
 */
public class GroupServiceSoap {
	public static com.liferay.portal.model.GroupSoap addGroup(
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.addGroup(name,
					description, type, friendlyURL, active);

			return com.liferay.portal.model.GroupSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap addGroup(
		long liveGroupId, java.lang.String name, java.lang.String description,
		int type, java.lang.String friendlyURL, boolean active)
		throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.addGroup(liveGroupId,
					name, description, type, friendlyURL, active);

			return com.liferay.portal.model.GroupSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addRoleGroups(long roleId, long[] groupIds)
		throws RemoteException {
		try {
			GroupServiceUtil.addRoleGroups(roleId, groupIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteGroup(long groupId) throws RemoteException {
		try {
			GroupServiceUtil.deleteGroup(groupId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap getGroup(long groupId)
		throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.getGroup(groupId);

			return com.liferay.portal.model.GroupSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap getGroup(long companyId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.getGroup(companyId,
					name);

			return com.liferay.portal.model.GroupSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap[] getOrganizationsGroups(
		java.util.List organizations) throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getOrganizationsGroups(organizations);

			return com.liferay.portal.model.GroupSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap[] getUserGroupsGroups(
		java.util.List userGroups) throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.getUserGroupsGroups(userGroups);

			return com.liferay.portal.model.GroupSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasUserGroup(long userId, long groupId)
		throws RemoteException {
		try {
			boolean returnValue = GroupServiceUtil.hasUserGroup(userId, groupId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap[] search(long companyId,
		java.lang.String name, java.lang.String description,
		java.lang.String[] params, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = GroupServiceUtil.search(companyId,
					name, description, params, begin, end);

			return com.liferay.portal.model.GroupSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.lang.String[] params)
		throws RemoteException {
		try {
			int returnValue = GroupServiceUtil.searchCount(companyId, name,
					description, params);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void setRoleGroups(long roleId, long[] groupIds)
		throws RemoteException {
		try {
			GroupServiceUtil.setRoleGroups(roleId, groupIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetRoleGroups(long roleId, long[] groupIds)
		throws RemoteException {
		try {
			GroupServiceUtil.unsetRoleGroups(roleId, groupIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap updateGroup(long groupId,
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.updateGroup(groupId,
					name, description, type, friendlyURL, active);

			return com.liferay.portal.model.GroupSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.GroupSoap updateGroup(long groupId,
		java.lang.String typeSettings) throws RemoteException {
		try {
			com.liferay.portal.model.Group returnValue = GroupServiceUtil.updateGroup(groupId,
					typeSettings);

			return com.liferay.portal.model.GroupSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(GroupServiceSoap.class);
}
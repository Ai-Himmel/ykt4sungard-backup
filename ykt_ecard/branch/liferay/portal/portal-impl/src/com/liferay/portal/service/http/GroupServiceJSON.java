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

import com.liferay.portal.service.GroupServiceUtil;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="GroupServiceJSON.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a JSON utility for the
 * <code>com.liferay.portal.service.GroupServiceUtil</code>
 * service utility. The static methods of this class calls the same methods of
 * the service utility. However, the signatures are different because it is
 * difficult for JSON to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to a <code>org.json.JSONArray</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.Group</code>,
 * that is translated to a <code>org.json.JSONObject</code>. Methods that JSON
 * cannot safely use are skipped. The logic for the translation is encapsulated
 * in <code>com.liferay.portal.service.http.GroupJSONSerializer</code>.
 * </p>
 *
 * <p>
 * This allows you to call the the backend services directly from JavaScript.
 * See <code>portal-web/docroot/html/portlet/tags_admin/unpacked.js</code> for a
 * reference of how that portlet uses the generated JavaScript in
 * <code>portal-web/docroot/html/js/service.js</code> to call the backend
 * services directly from JavaScript.
 * </p>
 *
 * <p>
 * The JSON utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.GroupServiceUtil
 * @see com.liferay.portal.service.http.GroupJSONSerializer
 *
 */
public class GroupServiceJSON {
	public static JSONObject addGroup(java.lang.String name,
		java.lang.String description, int type, java.lang.String friendlyURL,
		boolean active)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portal.model.Group returnValue = GroupServiceUtil.addGroup(name,
				description, type, friendlyURL, active);

		return GroupJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject addGroup(long liveGroupId, java.lang.String name,
		java.lang.String description, int type, java.lang.String friendlyURL,
		boolean active)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portal.model.Group returnValue = GroupServiceUtil.addGroup(liveGroupId,
				name, description, type, friendlyURL, active);

		return GroupJSONSerializer.toJSONObject(returnValue);
	}

	public static void addRoleGroups(long roleId, long[] groupIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		GroupServiceUtil.addRoleGroups(roleId, groupIds);
	}

	public static void deleteGroup(long groupId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		GroupServiceUtil.deleteGroup(groupId);
	}

	public static JSONObject getGroup(long groupId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portal.model.Group returnValue = GroupServiceUtil.getGroup(groupId);

		return GroupJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject getGroup(long companyId, java.lang.String name)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portal.model.Group returnValue = GroupServiceUtil.getGroup(companyId,
				name);

		return GroupJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONArray getOrganizationsGroups(java.util.List organizations)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.util.List returnValue = GroupServiceUtil.getOrganizationsGroups(organizations);

		return GroupJSONSerializer.toJSONArray(returnValue);
	}

	public static JSONArray getUserGroupsGroups(java.util.List userGroups)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.util.List returnValue = GroupServiceUtil.getUserGroupsGroups(userGroups);

		return GroupJSONSerializer.toJSONArray(returnValue);
	}

	public static boolean hasUserGroup(long userId, long groupId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		boolean returnValue = GroupServiceUtil.hasUserGroup(userId, groupId);

		return returnValue;
	}

	public static JSONArray search(long companyId, java.lang.String name,
		java.lang.String description, java.lang.String[] params, int begin,
		int end)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		java.util.List returnValue = GroupServiceUtil.search(companyId, name,
				description, params, begin, end);

		return GroupJSONSerializer.toJSONArray(returnValue);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.lang.String[] params)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		int returnValue = GroupServiceUtil.searchCount(companyId, name,
				description, params);

		return returnValue;
	}

	public static void setRoleGroups(long roleId, long[] groupIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		GroupServiceUtil.setRoleGroups(roleId, groupIds);
	}

	public static void unsetRoleGroups(long roleId, long[] groupIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		GroupServiceUtil.unsetRoleGroups(roleId, groupIds);
	}

	public static JSONObject updateGroup(long groupId, java.lang.String name,
		java.lang.String description, int type, java.lang.String friendlyURL,
		boolean active)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portal.model.Group returnValue = GroupServiceUtil.updateGroup(groupId,
				name, description, type, friendlyURL, active);

		return GroupJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject updateGroup(long groupId,
		java.lang.String typeSettings)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portal.model.Group returnValue = GroupServiceUtil.updateGroup(groupId,
				typeSettings);

		return GroupJSONSerializer.toJSONObject(returnValue);
	}
}
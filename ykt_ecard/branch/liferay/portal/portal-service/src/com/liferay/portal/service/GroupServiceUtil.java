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
 * <a href="GroupServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.GroupService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.GroupServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.GroupService
 * @see com.liferay.portal.service.GroupServiceFactory
 *
 */
public class GroupServiceUtil {
	public static com.liferay.portal.model.Group addGroup(
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.addGroup(name, description, type, friendlyURL,
			active);
	}

	public static com.liferay.portal.model.Group addGroup(long liveGroupId,
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.addGroup(liveGroupId, name, description, type,
			friendlyURL, active);
	}

	public static void addRoleGroups(long roleId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		groupService.addRoleGroups(roleId, groupIds);
	}

	public static void deleteGroup(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		groupService.deleteGroup(groupId);
	}

	public static com.liferay.portal.model.Group getGroup(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.getGroup(groupId);
	}

	public static com.liferay.portal.model.Group getGroup(long companyId,
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.getGroup(companyId, name);
	}

	public static java.util.List getOrganizationsGroups(
		java.util.List organizations)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.getOrganizationsGroups(organizations);
	}

	public static java.util.List getUserGroupsGroups(java.util.List userGroups)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.getUserGroupsGroups(userGroups);
	}

	public static boolean hasUserGroup(long userId, long groupId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.hasUserGroup(userId, groupId);
	}

	public static java.util.List search(long companyId, java.lang.String name,
		java.lang.String description, java.lang.String[] params, int begin,
		int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.search(companyId, name, description, params, begin,
			end);
	}

	public static int searchCount(long companyId, java.lang.String name,
		java.lang.String description, java.lang.String[] params)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.searchCount(companyId, name, description, params);
	}

	public static void setRoleGroups(long roleId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		groupService.setRoleGroups(roleId, groupIds);
	}

	public static void unsetRoleGroups(long roleId, long[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		groupService.unsetRoleGroups(roleId, groupIds);
	}

	public static com.liferay.portal.model.Group updateGroup(long groupId,
		java.lang.String name, java.lang.String description, int type,
		java.lang.String friendlyURL, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.updateGroup(groupId, name, description, type,
			friendlyURL, active);
	}

	public static com.liferay.portal.model.Group updateGroup(long groupId,
		java.lang.String typeSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		GroupService groupService = GroupServiceFactory.getService();

		return groupService.updateGroup(groupId, typeSettings);
	}
}
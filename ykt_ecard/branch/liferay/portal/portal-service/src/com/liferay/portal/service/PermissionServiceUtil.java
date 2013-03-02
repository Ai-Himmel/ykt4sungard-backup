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
 * <a href="PermissionServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.PermissionService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.PermissionServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PermissionService
 * @see com.liferay.portal.service.PermissionServiceFactory
 *
 */
public class PermissionServiceUtil {
	public static void checkPermission(long groupId, java.lang.String name,
		java.lang.String primKey)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.checkPermission(groupId, name, primKey);
	}

	public static boolean hasGroupPermission(long groupId,
		java.lang.String actionId, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		return permissionService.hasGroupPermission(groupId, actionId,
			resourceId);
	}

	public static boolean hasUserPermission(long userId,
		java.lang.String actionId, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		return permissionService.hasUserPermission(userId, actionId, resourceId);
	}

	public static boolean hasUserPermissions(long userId, long groupId,
		java.lang.String actionId, long[] resourceIds,
		com.liferay.portal.kernel.security.permission.PermissionCheckerBag permissionCheckerBag)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		return permissionService.hasUserPermissions(userId, groupId, actionId,
			resourceIds, permissionCheckerBag);
	}

	public static void setGroupPermissions(long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.setGroupPermissions(groupId, actionIds, resourceId);
	}

	public static void setGroupPermissions(java.lang.String className,
		java.lang.String classPK, long groupId, java.lang.String[] actionIds,
		long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.setGroupPermissions(className, classPK, groupId,
			actionIds, resourceId);
	}

	public static void setOrgGroupPermissions(long organizationId,
		long groupId, java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.setOrgGroupPermissions(organizationId, groupId,
			actionIds, resourceId);
	}

	public static void setRolePermission(long roleId, long groupId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.setRolePermission(roleId, groupId, name, scope,
			primKey, actionId);
	}

	public static void setRolePermissions(long roleId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.setRolePermissions(roleId, groupId, actionIds,
			resourceId);
	}

	public static void setUserPermissions(long userId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.setUserPermissions(userId, groupId, actionIds,
			resourceId);
	}

	public static void unsetRolePermission(long roleId, long groupId,
		long permissionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.unsetRolePermission(roleId, groupId, permissionId);
	}

	public static void unsetRolePermission(long roleId, long groupId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.unsetRolePermission(roleId, groupId, name, scope,
			primKey, actionId);
	}

	public static void unsetRolePermissions(long roleId, long groupId,
		java.lang.String name, int scope, java.lang.String actionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.unsetRolePermissions(roleId, groupId, name, scope,
			actionId);
	}

	public static void unsetUserPermissions(long userId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		PermissionService permissionService = PermissionServiceFactory.getService();

		permissionService.unsetUserPermissions(userId, groupId, actionIds,
			resourceId);
	}
}
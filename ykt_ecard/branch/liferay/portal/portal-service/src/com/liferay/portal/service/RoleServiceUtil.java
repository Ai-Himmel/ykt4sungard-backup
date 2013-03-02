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
 * <a href="RoleServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.RoleService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.RoleServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.RoleService
 * @see com.liferay.portal.service.RoleServiceFactory
 *
 */
public class RoleServiceUtil {
	public static com.liferay.portal.model.Role addRole(java.lang.String name,
		java.lang.String description, int type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.addRole(name, description, type);
	}

	public static void addUserRoles(long userId, long[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		roleService.addUserRoles(userId, roleIds);
	}

	public static void deleteRole(long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		roleService.deleteRole(roleId);
	}

	public static com.liferay.portal.model.Role getGroupRole(long companyId,
		long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getGroupRole(companyId, groupId);
	}

	public static java.util.List getGroupRoles(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getGroupRoles(groupId);
	}

	public static com.liferay.portal.model.Role getRole(long roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getRole(roleId);
	}

	public static com.liferay.portal.model.Role getRole(long companyId,
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getRole(companyId, name);
	}

	public static java.util.List getUserGroupRoles(long userId, long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getUserGroupRoles(userId, groupId);
	}

	public static java.util.List getUserRelatedRoles(long userId,
		java.util.List groups)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getUserRelatedRoles(userId, groups);
	}

	public static java.util.List getUserRoles(long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.getUserRoles(userId);
	}

	public static boolean hasUserRole(long userId, long companyId,
		java.lang.String name, boolean inherited)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.hasUserRole(userId, companyId, name, inherited);
	}

	public static boolean hasUserRoles(long userId, long companyId,
		java.lang.String[] names, boolean inherited)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.hasUserRoles(userId, companyId, names, inherited);
	}

	public static void unsetUserRoles(long userId, long[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		roleService.unsetUserRoles(userId, roleIds);
	}

	public static com.liferay.portal.model.Role updateRole(long roleId,
		java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RoleService roleService = RoleServiceFactory.getService();

		return roleService.updateRole(roleId, name, description);
	}
}
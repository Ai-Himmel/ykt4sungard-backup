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
 * <a href="PermissionService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portal.service.impl.PermissionServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a remote service. Methods of this service are expected to have security checks based on the propagated JAAS credentials because this service can be accessed remotely.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.PermissionServiceFactory
 * @see com.liferay.portal.service.PermissionServiceUtil
 *
 */
public interface PermissionService {
	public void checkPermission(long groupId, java.lang.String name,
		java.lang.String primKey)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public boolean hasGroupPermission(long groupId, java.lang.String actionId,
		long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public boolean hasUserPermission(long userId, java.lang.String actionId,
		long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public boolean hasUserPermissions(long userId, long groupId,
		java.lang.String actionId, long[] resourceIds,
		com.liferay.portal.kernel.security.permission.PermissionCheckerBag permissionCheckerBag)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setGroupPermissions(long groupId, java.lang.String[] actionIds,
		long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setGroupPermissions(java.lang.String className,
		java.lang.String classPK, long groupId, java.lang.String[] actionIds,
		long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setOrgGroupPermissions(long organizationId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setRolePermission(long roleId, long groupId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setRolePermissions(long roleId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setUserPermissions(long userId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetRolePermission(long roleId, long groupId, long permissionId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetRolePermission(long roleId, long groupId,
		java.lang.String name, int scope, java.lang.String primKey,
		java.lang.String actionId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetRolePermissions(long roleId, long groupId,
		java.lang.String name, int scope, java.lang.String actionId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetUserPermissions(long userId, long groupId,
		java.lang.String[] actionIds, long resourceId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}
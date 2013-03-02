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

package com.liferay.portlet.softwarecatalog.service;


/**
 * <a href="SCFrameworkVersionServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionService
 * @see com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionServiceFactory
 *
 */
public class SCFrameworkVersionServiceUtil {
	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion addFrameworkVersion(
		long plid, java.lang.String name, java.lang.String url, boolean active,
		int priority, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		return scFrameworkVersionService.addFrameworkVersion(plid, name, url,
			active, priority, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion addFrameworkVersion(
		long plid, java.lang.String name, java.lang.String url, boolean active,
		int priority, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		return scFrameworkVersionService.addFrameworkVersion(plid, name, url,
			active, priority, communityPermissions, guestPermissions);
	}

	public static void deleteFrameworkVersion(long frameworkVersionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		scFrameworkVersionService.deleteFrameworkVersion(frameworkVersionId);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion getFrameworkVersion(
		long frameworkVersionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		return scFrameworkVersionService.getFrameworkVersion(frameworkVersionId);
	}

	public static java.util.List getFrameworkVersions(long groupId,
		boolean active)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		return scFrameworkVersionService.getFrameworkVersions(groupId, active);
	}

	public static java.util.List getFrameworkVersions(long groupId,
		boolean active, int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		return scFrameworkVersionService.getFrameworkVersions(groupId, active,
			begin, end);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion updateFrameworkVersion(
		long frameworkVersionId, java.lang.String name, java.lang.String url,
		boolean active, int priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		SCFrameworkVersionService scFrameworkVersionService = SCFrameworkVersionServiceFactory.getService();

		return scFrameworkVersionService.updateFrameworkVersion(frameworkVersionId,
			name, url, active, priority);
	}
}
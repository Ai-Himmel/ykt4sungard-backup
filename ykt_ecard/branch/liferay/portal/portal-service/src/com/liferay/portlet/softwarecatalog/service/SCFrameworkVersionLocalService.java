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
 * <a href="SCFrameworkVersionLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.softwarecatalog.service.impl.SCFrameworkVersionLocalServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalServiceFactory
 * @see com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalServiceUtil
 *
 */
public interface SCFrameworkVersionLocalService {
	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion addSCFrameworkVersion(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion updateSCFrameworkVersion(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.softwarecatalog.service.persistence.SCLicensePersistence getSCLicensePersistence();

	public void setSCLicensePersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCLicensePersistence scLicensePersistence);

	public com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence getSCFrameworkVersionPersistence();

	public void setSCFrameworkVersionPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence scFrameworkVersionPersistence);

	public com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence getSCProductEntryPersistence();

	public void setSCProductEntryPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence scProductEntryPersistence);

	public com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotPersistence getSCProductScreenshotPersistence();

	public void setSCProductScreenshotPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotPersistence scProductScreenshotPersistence);

	public com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionPersistence getSCProductVersionPersistence();

	public void setSCProductVersionPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionPersistence scProductVersionPersistence);

	public com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence();

	public void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence);

	public com.liferay.portal.service.persistence.ResourceFinder getResourceFinder();

	public void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder);

	public com.liferay.portal.service.persistence.UserPersistence getUserPersistence();

	public void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence);

	public com.liferay.portal.service.persistence.UserFinder getUserFinder();

	public void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder);

	public void afterPropertiesSet();

	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion addFrameworkVersion(
		long userId, long plid, java.lang.String name, java.lang.String url,
		boolean active, int priority, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion addFrameworkVersion(
		long userId, long plid, java.lang.String name, java.lang.String url,
		boolean active, int priority, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion addFrameworkVersion(
		long userId, long plid, java.lang.String name, java.lang.String url,
		boolean active, int priority,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFrameworkVersionResources(long frameworkVersionId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFrameworkVersionResources(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion frameworkVersion,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFrameworkVersionResources(long frameworkVersionId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFrameworkVersionResources(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion frameworkVersion,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFrameworkVersion(long frameworkVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFrameworkVersion(
		com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion frameworkVersion)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFrameworkVersions(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion getFrameworkVersion(
		long frameworkVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getFrameworkVersions(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getFrameworkVersions(long groupId, boolean active)
		throws com.liferay.portal.SystemException;

	public java.util.List getFrameworkVersions(long groupId, boolean active,
		int begin, int end) throws com.liferay.portal.SystemException;

	public int getFrameworkVersionsCount(long groupId)
		throws com.liferay.portal.SystemException;

	public int getFrameworkVersionsCount(long groupId, boolean active)
		throws com.liferay.portal.SystemException;

	public java.util.List getProductVersionFrameworkVersions(
		long productVersionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion updateFrameworkVersion(
		long frameworkVersionId, java.lang.String name, java.lang.String url,
		boolean active, int priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}
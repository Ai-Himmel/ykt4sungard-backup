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
 * <a href="SCProductEntryLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalService
 * @see com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceFactory
 *
 */
public class SCProductEntryLocalServiceUtil {
	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry addSCProductEntry(
		com.liferay.portlet.softwarecatalog.model.SCProductEntry model)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.addSCProductEntry(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry updateSCProductEntry(
		com.liferay.portlet.softwarecatalog.model.SCProductEntry model)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.updateSCProductEntry(model);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCLicensePersistence getSCLicensePersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getSCLicensePersistence();
	}

	public static void setSCLicensePersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCLicensePersistence scLicensePersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setSCLicensePersistence(scLicensePersistence);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence getSCFrameworkVersionPersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getSCFrameworkVersionPersistence();
	}

	public static void setSCFrameworkVersionPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence scFrameworkVersionPersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setSCFrameworkVersionPersistence(scFrameworkVersionPersistence);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence getSCProductEntryPersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getSCProductEntryPersistence();
	}

	public static void setSCProductEntryPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence scProductEntryPersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setSCProductEntryPersistence(scProductEntryPersistence);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotPersistence getSCProductScreenshotPersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getSCProductScreenshotPersistence();
	}

	public static void setSCProductScreenshotPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotPersistence scProductScreenshotPersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setSCProductScreenshotPersistence(scProductScreenshotPersistence);
	}

	public static com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionPersistence getSCProductVersionPersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getSCProductVersionPersistence();
	}

	public static void setSCProductVersionPersistence(
		com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionPersistence scProductVersionPersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setSCProductVersionPersistence(scProductVersionPersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static void afterPropertiesSet() {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry addProductEntry(
		long userId, long plid, java.lang.String name, java.lang.String type,
		java.lang.String tags, java.lang.String shortDescription,
		java.lang.String longDescription, java.lang.String pageURL,
		java.lang.String author, java.lang.String repoGroupId,
		java.lang.String repoArtifactId, long[] licenseIds,
		java.util.List thumbnails, java.util.List fullImages,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.addProductEntry(userId, plid, name,
			type, tags, shortDescription, longDescription, pageURL, author,
			repoGroupId, repoArtifactId, licenseIds, thumbnails, fullImages,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry addProductEntry(
		long userId, long plid, java.lang.String name, java.lang.String type,
		java.lang.String tags, java.lang.String shortDescription,
		java.lang.String longDescription, java.lang.String pageURL,
		java.lang.String author, java.lang.String repoGroupId,
		java.lang.String repoArtifactId, long[] licenseIds,
		java.util.List thumbnails, java.util.List fullImages,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.addProductEntry(userId, plid, name,
			type, tags, shortDescription, longDescription, pageURL, author,
			repoGroupId, repoArtifactId, licenseIds, thumbnails, fullImages,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry addProductEntry(
		long userId, long plid, java.lang.String name, java.lang.String type,
		java.lang.String tags, java.lang.String shortDescription,
		java.lang.String longDescription, java.lang.String pageURL,
		java.lang.String author, java.lang.String repoGroupId,
		java.lang.String repoArtifactId, long[] licenseIds,
		java.util.List thumbnails, java.util.List fullImages,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.addProductEntry(userId, plid, name,
			type, tags, shortDescription, longDescription, pageURL, author,
			repoGroupId, repoArtifactId, licenseIds, thumbnails, fullImages,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static void addProductEntryResources(long productEntryId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.addProductEntryResources(productEntryId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addProductEntryResources(
		com.liferay.portlet.softwarecatalog.model.SCProductEntry productEntry,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.addProductEntryResources(productEntry,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addProductEntryResources(long productEntryId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.addProductEntryResources(productEntryId,
			communityPermissions, guestPermissions);
	}

	public static void addProductEntryResources(
		com.liferay.portlet.softwarecatalog.model.SCProductEntry productEntry,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.addProductEntryResources(productEntry,
			communityPermissions, guestPermissions);
	}

	public static void deleteProductEntries(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.deleteProductEntries(groupId);
	}

	public static void deleteProductEntry(long productEntryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.deleteProductEntry(productEntryId);
	}

	public static void deleteProductEntry(
		com.liferay.portlet.softwarecatalog.model.SCProductEntry productEntry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.deleteProductEntry(productEntry);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry getProductEntry(
		long productEntryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntry(productEntryId);
	}

	public static java.util.List getProductEntries(long groupId, int begin,
		int end) throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntries(groupId, begin, end);
	}

	public static java.util.List getProductEntries(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntries(groupId, begin,
			end, obc);
	}

	public static java.util.List getProductEntries(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntries(groupId, userId,
			begin, end);
	}

	public static java.util.List getProductEntries(long groupId, long userId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntries(groupId, userId,
			begin, end, obc);
	}

	public static int getProductEntriesCount(long groupId)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntriesCount(groupId);
	}

	public static int getProductEntriesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getProductEntriesCount(groupId, userId);
	}

	public static java.lang.String getRepositoryXML(long groupId,
		java.lang.String baseImageURL, java.util.Date oldestDate,
		int maxNumOfVersions, java.util.Properties repoSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getRepositoryXML(groupId,
			baseImageURL, oldestDate, maxNumOfVersions, repoSettings);
	}

	public static java.lang.String getRepositoryXML(long groupId,
		java.lang.String version, java.lang.String baseImageURL,
		java.util.Date oldestDate, int maxNumOfVersions,
		java.util.Properties repoSettings)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.getRepositoryXML(groupId, version,
			baseImageURL, oldestDate, maxNumOfVersions, repoSettings);
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		scProductEntryLocalService.reIndex(ids);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, java.lang.String keywords, java.lang.String type)
		throws com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.search(companyId, groupId, keywords,
			type);
	}

	public static com.liferay.portlet.softwarecatalog.model.SCProductEntry updateProductEntry(
		long productEntryId, java.lang.String name, java.lang.String type,
		java.lang.String tags, java.lang.String shortDescription,
		java.lang.String longDescription, java.lang.String pageURL,
		java.lang.String author, java.lang.String repoGroupId,
		java.lang.String repoArtifactId, long[] licenseIds,
		java.util.List thumbnails, java.util.List fullImages)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		SCProductEntryLocalService scProductEntryLocalService = SCProductEntryLocalServiceFactory.getService();

		return scProductEntryLocalService.updateProductEntry(productEntryId,
			name, type, tags, shortDescription, longDescription, pageURL,
			author, repoGroupId, repoArtifactId, licenseIds, thumbnails,
			fullImages);
	}
}
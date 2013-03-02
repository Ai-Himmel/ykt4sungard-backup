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

package com.liferay.portlet.blogs.service;


/**
 * <a href="BlogsEntryLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.blogs.service.BlogsEntryLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.blogs.service.BlogsEntryLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.blogs.service.BlogsEntryLocalService
 * @see com.liferay.portlet.blogs.service.BlogsEntryLocalServiceFactory
 *
 */
public class BlogsEntryLocalServiceUtil {
	public static com.liferay.portlet.blogs.model.BlogsEntry addBlogsEntry(
		com.liferay.portlet.blogs.model.BlogsEntry model)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.addBlogsEntry(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry updateBlogsEntry(
		com.liferay.portlet.blogs.model.BlogsEntry model)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.updateBlogsEntry(model);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getBlogsEntryPersistence();
	}

	public static void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setBlogsEntryPersistence(blogsEntryPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getBlogsEntryFinder();
	}

	public static void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setBlogsEntryFinder(blogsEntryFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getBlogsStatsUserPersistence();
	}

	public static void setBlogsStatsUserPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence blogsStatsUserPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setBlogsStatsUserPersistence(blogsStatsUserPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder getBlogsStatsUserFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getBlogsStatsUserFinder();
	}

	public static void setBlogsStatsUserFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder blogsStatsUserFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setBlogsStatsUserFinder(blogsStatsUserFinder);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.OrganizationPersistence getOrganizationPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getOrganizationPersistence();
	}

	public static void setOrganizationPersistence(
		com.liferay.portal.service.persistence.OrganizationPersistence organizationPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setOrganizationPersistence(organizationPersistence);
	}

	public static com.liferay.portal.service.persistence.OrganizationFinder getOrganizationFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getOrganizationFinder();
	}

	public static void setOrganizationFinder(
		com.liferay.portal.service.persistence.OrganizationFinder organizationFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setOrganizationFinder(organizationFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static void afterPropertiesSet() {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		long userId, long plid, java.lang.String title,
		java.lang.String content, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.addEntry(userId, plid, title, content,
			displayDateMonth, displayDateDay, displayDateYear, displayDateHour,
			displayDateMinute, tagsEntries, addCommunityPermissions,
			addGuestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		java.lang.String uuid, long userId, long plid, java.lang.String title,
		java.lang.String content, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.addEntry(uuid, userId, plid, title,
			content, displayDateMonth, displayDateDay, displayDateYear,
			displayDateHour, displayDateMinute, tagsEntries,
			addCommunityPermissions, addGuestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		long userId, long plid, java.lang.String title,
		java.lang.String content, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.addEntry(userId, plid, title, content,
			displayDateMonth, displayDateDay, displayDateYear, displayDateHour,
			displayDateMinute, tagsEntries, communityPermissions,
			guestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		java.lang.String uuid, long userId, long plid, java.lang.String title,
		java.lang.String content, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		java.lang.String[] tagsEntries,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.addEntry(uuid, userId, plid, title,
			content, displayDateMonth, displayDateDay, displayDateYear,
			displayDateHour, displayDateMinute, tagsEntries,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions, themeDisplay);
	}

	public static void addEntryResources(long entryId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.addEntryResources(entryId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addEntryResources(
		com.liferay.portlet.blogs.model.BlogsEntry entry,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.addEntryResources(entry,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addEntryResources(long entryId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.addEntryResources(entryId, communityPermissions,
			guestPermissions);
	}

	public static void addEntryResources(
		com.liferay.portlet.blogs.model.BlogsEntry entry,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.addEntryResources(entry, communityPermissions,
			guestPermissions);
	}

	public static void deleteEntries(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.deleteEntries(groupId);
	}

	public static void deleteEntry(long entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.deleteEntry(entryId);
	}

	public static void deleteEntry(
		com.liferay.portlet.blogs.model.BlogsEntry entry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.deleteEntry(entry);
	}

	public static java.util.List getCompanyEntries(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getCompanyEntries(companyId, begin, end);
	}

	public static java.util.List getCompanyEntries(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getCompanyEntries(companyId, begin, end,
			obc);
	}

	public static int getCompanyEntriesCount(long companyId)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getCompanyEntriesCount(companyId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry getEntry(
		long entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getEntry(entryId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry getEntry(
		long groupId, java.lang.String urlTitle)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getEntry(groupId, urlTitle);
	}

	public static java.util.List getGroupEntries(long groupId, int begin,
		int end) throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupEntries(groupId, begin, end);
	}

	public static java.util.List getGroupEntries(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupEntries(groupId, begin, end, obc);
	}

	public static int getGroupEntriesCount(long groupId)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupEntriesCount(groupId);
	}

	public static java.util.List getGroupUserEntries(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupUserEntries(groupId, userId,
			begin, end);
	}

	public static int getGroupUserEntriesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getGroupUserEntriesCount(groupId, userId);
	}

	public static java.util.List getNoAssetEntries()
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getNoAssetEntries();
	}

	public static java.util.List getOrganizationEntries(long organizationId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getOrganizationEntries(organizationId,
			begin, end);
	}

	public static int getOrganizationEntriesCount(long organizationId)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getOrganizationEntriesCount(organizationId);
	}

	public static java.lang.String getUrlTitle(long entryId,
		java.lang.String title) {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.getUrlTitle(entryId, title);
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.reIndex(ids);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, long userId, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.search(companyId, groupId, userId,
			keywords);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry updateEntry(
		long userId, long entryId, java.lang.String title,
		java.lang.String content, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		java.lang.String[] tagsEntries,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		return blogsEntryLocalService.updateEntry(userId, entryId, title,
			content, displayDateMonth, displayDateDay, displayDateYear,
			displayDateHour, displayDateMinute, tagsEntries, themeDisplay);
	}

	public static void updateTagsAsset(long userId,
		com.liferay.portlet.blogs.model.BlogsEntry entry,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsEntryLocalService blogsEntryLocalService = BlogsEntryLocalServiceFactory.getService();

		blogsEntryLocalService.updateTagsAsset(userId, entry, tagsEntries);
	}
}
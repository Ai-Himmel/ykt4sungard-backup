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

package com.liferay.portlet.journal.service;


/**
 * <a href="JournalContentSearchLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalContentSearchLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalContentSearchLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalContentSearchLocalService
 * @see com.liferay.portlet.journal.service.JournalContentSearchLocalServiceFactory
 *
 */
public class JournalContentSearchLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalContentSearch addJournalContentSearch(
		com.liferay.portlet.journal.model.JournalContentSearch model)
		throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.addJournalContentSearch(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch updateJournalContentSearch(
		com.liferay.portlet.journal.model.JournalContentSearch model)
		throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.updateJournalContentSearch(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getLayoutPersistence();
	}

	public static void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setLayoutPersistence(layoutPersistence);
	}

	public static com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getLayoutFinder();
	}

	public static void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setLayoutFinder(layoutFinder);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static void afterPropertiesSet() {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.afterPropertiesSet();
	}

	public static void checkContentSearches(long companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.checkContentSearches(companyId);
	}

	public static void deleteArticleContentSearch(long groupId,
		boolean privateLayout, long layoutId, java.lang.String portletId,
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.deleteArticleContentSearch(groupId,
			privateLayout, layoutId, portletId, articleId);
	}

	public static void deleteArticleContentSearches(long groupId,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.deleteArticleContentSearches(groupId,
			articleId);
	}

	public static void deleteLayoutContentSearches(long groupId,
		boolean privateLayout, long layoutId)
		throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.deleteLayoutContentSearches(groupId,
			privateLayout, layoutId);
	}

	public static void deleteOwnerContentSearches(long groupId,
		boolean privateLayout) throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		journalContentSearchLocalService.deleteOwnerContentSearches(groupId,
			privateLayout);
	}

	public static java.util.List getArticleContentSearches()
		throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getArticleContentSearches();
	}

	public static java.util.List getArticleContentSearches(long groupId,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getArticleContentSearches(groupId,
			articleId);
	}

	public static java.util.List getLayoutIds(long groupId,
		boolean privateLayout, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getLayoutIds(groupId,
			privateLayout, articleId);
	}

	public static int getLayoutIdsCount(long groupId, boolean privateLayout,
		java.lang.String articleId) throws com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.getLayoutIdsCount(groupId,
			privateLayout, articleId);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch updateContentSearch(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId, java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.updateContentSearch(groupId,
			privateLayout, layoutId, portletId, articleId);
	}

	public static com.liferay.portlet.journal.model.JournalContentSearch updateContentSearch(
		long groupId, boolean privateLayout, long layoutId,
		java.lang.String portletId, java.lang.String articleId, boolean purge)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.updateContentSearch(groupId,
			privateLayout, layoutId, portletId, articleId, purge);
	}

	public static java.util.List updateContentSearch(long groupId,
		boolean privateLayout, long layoutId, java.lang.String portletId,
		java.lang.String[] articleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalContentSearchLocalService journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getService();

		return journalContentSearchLocalService.updateContentSearch(groupId,
			privateLayout, layoutId, portletId, articleIds);
	}
}
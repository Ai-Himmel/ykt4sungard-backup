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
 * <a href="JournalArticleResourceLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalArticleResourceLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalArticleResourceLocalService
 * @see com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceFactory
 *
 */
public class JournalArticleResourceLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalArticleResource addJournalArticleResource(
		com.liferay.portlet.journal.model.JournalArticleResource model)
		throws com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.addJournalArticleResource(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.journal.model.JournalArticleResource updateJournalArticleResource(
		com.liferay.portlet.journal.model.JournalArticleResource model)
		throws com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.updateJournalArticleResource(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static void afterPropertiesSet() {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.afterPropertiesSet();
	}

	public static void deleteArticleResource(long groupId,
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		journalArticleResourceLocalService.deleteArticleResource(groupId,
			articleId);
	}

	public static com.liferay.portlet.journal.model.JournalArticleResource getArticleResource(
		long articleResourceId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getArticleResource(articleResourceId);
	}

	public static long getArticleResourcePrimKey(long groupId,
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getArticleResourcePrimKey(groupId,
			articleId);
	}

	public static java.util.List getArticleResources(long groupId)
		throws com.liferay.portal.SystemException {
		JournalArticleResourceLocalService journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getService();

		return journalArticleResourceLocalService.getArticleResources(groupId);
	}
}
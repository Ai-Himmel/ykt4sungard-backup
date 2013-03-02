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
 * <a href="JournalArticleImageLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalArticleImageLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalArticleImageLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalArticleImageLocalService
 * @see com.liferay.portlet.journal.service.JournalArticleImageLocalServiceFactory
 *
 */
public class JournalArticleImageLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalArticleImage addJournalArticleImage(
		com.liferay.portlet.journal.model.JournalArticleImage model)
		throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.addJournalArticleImage(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage updateJournalArticleImage(
		com.liferay.portlet.journal.model.JournalArticleImage model)
		throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.updateJournalArticleImage(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static void afterPropertiesSet() {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.afterPropertiesSet();
	}

	public static void addArticleImageId(long articleImageId, long groupId,
		java.lang.String articleId, double version, java.lang.String elName,
		java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.addArticleImageId(articleImageId,
			groupId, articleId, version, elName, languageId);
	}

	public static void deleteArticleImage(long articleImageId)
		throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.deleteArticleImage(articleImageId);
	}

	public static void deleteArticleImage(long groupId,
		java.lang.String articleId, double version, java.lang.String elName,
		java.lang.String languageId) throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.deleteArticleImage(groupId, articleId,
			version, elName, languageId);
	}

	public static void deleteImages(long groupId, java.lang.String articleId,
		double version) throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		journalArticleImageLocalService.deleteImages(groupId, articleId, version);
	}

	public static com.liferay.portlet.journal.model.JournalArticleImage getArticleImage(
		long articleImageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getArticleImage(articleImageId);
	}

	public static long getArticleImageId(long groupId,
		java.lang.String articleId, double version, java.lang.String elName,
		java.lang.String languageId) throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getArticleImageId(groupId,
			articleId, version, elName, languageId);
	}

	public static long getArticleImageId(long groupId,
		java.lang.String articleId, double version, java.lang.String elName,
		java.lang.String languageId, boolean tempImage)
		throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getArticleImageId(groupId,
			articleId, version, elName, languageId, tempImage);
	}

	public static java.util.List getArticleImages(long groupId)
		throws com.liferay.portal.SystemException {
		JournalArticleImageLocalService journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getService();

		return journalArticleImageLocalService.getArticleImages(groupId);
	}
}
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
 * <a href="JournalArticleResourceLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.journal.service.impl.JournalArticleResourceLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceFactory
 * @see com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceUtil
 *
 */
public interface JournalArticleResourceLocalService {
	public com.liferay.portlet.journal.model.JournalArticleResource addJournalArticleResource(
		com.liferay.portlet.journal.model.JournalArticleResource model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticleResource updateJournalArticleResource(
		com.liferay.portlet.journal.model.JournalArticleResource model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence();

	public void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder();

	public void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder);

	public com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence();

	public void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence();

	public void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence();

	public void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence);

	public com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence();

	public void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence);

	public com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder();

	public void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder);

	public com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence();

	public void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder();

	public void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder);

	public com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence();

	public void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder();

	public void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder);

	public void afterPropertiesSet();

	public void deleteArticleResource(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleResource getArticleResource(
		long articleResourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public long getArticleResourcePrimKey(long groupId,
		java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getArticleResources(long groupId)
		throws com.liferay.portal.SystemException;
}
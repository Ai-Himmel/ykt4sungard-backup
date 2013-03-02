/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.journal.service.spring;

/**
 * <a href="JournalArticleService.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public interface JournalArticleService {
	public com.liferay.portlet.journal.model.JournalArticle addArticle(
		java.lang.String articleId, boolean autoArticleId,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String title, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayMonth, int displayDay,
		int displayYear, int expMonth, int expDay, int expYear,
		boolean neverExpires, java.lang.String articleURL, java.util.Map images)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.journal.model.JournalArticle approveArticle(
		java.lang.String articleId, java.lang.String articleURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public void checkArticles()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public void deleteArticle(java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.journal.model.JournalArticle getArticle(
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.journal.model.JournalArticle getArticle(
		java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.lang.String getArticleContent(java.lang.String articleId,
		java.lang.String languageId, java.lang.String rootPath)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.lang.String getArticleContent(java.lang.String articleId,
		double version, java.lang.String languageId, java.lang.String rootPath)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByCompany(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByCompany(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByCompany(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved, int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByCompany(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public int getArticlesByCompanySize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByStructure(java.lang.String structureId,
		int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public int getArticlesByStructureSize(java.lang.String structureId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByTemplate(java.lang.String templateId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByTemplate(java.lang.String templateId,
		int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public int getArticlesByTemplateSize(java.lang.String templateId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getArticlesByUser(java.lang.String portletId,
		java.lang.String groupId, java.lang.String type, boolean approved,
		int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public int getArticlesByUserSize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String type, boolean approved)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		java.lang.String articleId, java.lang.Boolean approved)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public double getLatestVersion(java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean isLatestVersion(java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.util.lucene.Hits search(java.lang.String companyId,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String title, java.lang.String content, java.lang.String type)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.journal.model.JournalArticle updateArticle(
		java.lang.String articleId, boolean incrementVersion,
		java.lang.String title, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayMonth, int displayDay,
		int displayYear, int expMonth, int expDay, int expYear,
		boolean neverExpires, java.lang.String articleURL, java.util.Map images)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasAdmin()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasAdmin(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK pk)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasDesigner()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasEditor()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasWriter()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;
}
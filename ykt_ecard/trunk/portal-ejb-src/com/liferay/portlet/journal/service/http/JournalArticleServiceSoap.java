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

package com.liferay.portlet.journal.service.http;

import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="JournalArticleServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalArticleServiceSoap {
	public static com.liferay.portlet.journal.model.JournalArticleModel addArticle(
		java.lang.String articleId, boolean autoArticleId,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String title, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayMonth, int displayDay,
		int displayYear, int expMonth, int expDay, int expYear,
		boolean neverExpires, java.lang.String articleURL, java.util.Map images)
		throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.addArticle(articleId,
					autoArticleId, portletId, groupId, title, content, type,
					structureId, templateId, displayMonth, displayDay,
					displayYear, expMonth, expDay, expYear, neverExpires,
					articleURL, images);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel approveArticle(
		java.lang.String articleId, java.lang.String articleURL)
		throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.approveArticle(articleId,
					articleURL);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void checkArticles() throws RemoteException {
		try {
			JournalArticleServiceUtil.checkArticles();
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteArticle(java.lang.String articleId, double version)
		throws RemoteException {
		try {
			JournalArticleServiceUtil.deleteArticle(articleId, version);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel getArticle(
		java.lang.String articleId) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.getArticle(articleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel getArticle(
		java.lang.String articleId, double version) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.getArticle(articleId,
					version);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getArticleContent(
		java.lang.String articleId, java.lang.String languageId,
		java.lang.String rootPath) throws RemoteException {
		try {
			java.lang.String returnValue = JournalArticleServiceUtil.getArticleContent(articleId,
					languageId, rootPath);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getArticleContent(
		java.lang.String articleId, double version,
		java.lang.String languageId, java.lang.String rootPath)
		throws RemoteException {
		try {
			java.lang.String returnValue = JournalArticleServiceUtil.getArticleContent(articleId,
					version, languageId, rootPath);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByCompany(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByCompany(portletId,
					groupId, companyId);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByCompany(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByCompany(portletId,
					groupId, companyId, type, approved);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByCompany(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved,
		int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByCompany(portletId,
					groupId, companyId, type, approved, begin, end);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByCompany(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String type, boolean approved,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByCompany(portletId,
					groupId, companyId, type, approved, begin, end, obc);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getArticlesByCompanySize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String type, boolean approved) throws RemoteException {
		try {
			int returnValue = JournalArticleServiceUtil.getArticlesByCompanySize(portletId,
					groupId, companyId, type, approved);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByStructure(
		java.lang.String structureId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByStructure(structureId,
					begin, end);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getArticlesByStructureSize(java.lang.String structureId)
		throws RemoteException {
		try {
			int returnValue = JournalArticleServiceUtil.getArticlesByStructureSize(structureId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByTemplate(
		java.lang.String templateId) throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByTemplate(templateId);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByTemplate(
		java.lang.String templateId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByTemplate(templateId,
					begin, end);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getArticlesByTemplateSize(java.lang.String templateId)
		throws RemoteException {
		try {
			int returnValue = JournalArticleServiceUtil.getArticlesByTemplateSize(templateId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel[] getArticlesByUser(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String type, boolean approved, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = JournalArticleServiceUtil.getArticlesByUser(portletId,
					groupId, type, approved, begin, end);

			return (com.liferay.portlet.journal.model.JournalArticle[])returnValue.toArray(new com.liferay.portlet.journal.model.JournalArticle[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getArticlesByUserSize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String type, boolean approved)
		throws RemoteException {
		try {
			int returnValue = JournalArticleServiceUtil.getArticlesByUserSize(portletId,
					groupId, type, approved);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel getLatestArticle(
		java.lang.String articleId) throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.getLatestArticle(articleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel getLatestArticle(
		java.lang.String articleId, java.lang.Boolean approved)
		throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.getLatestArticle(articleId,
					approved);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static double getLatestVersion(java.lang.String articleId)
		throws RemoteException {
		try {
			double returnValue = JournalArticleServiceUtil.getLatestVersion(articleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean isLatestVersion(java.lang.String articleId,
		double version) throws RemoteException {
		try {
			boolean returnValue = JournalArticleServiceUtil.isLatestVersion(articleId,
					version);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void reIndex(java.lang.String[] ids)
		throws RemoteException {
		try {
			JournalArticleServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String title,
		java.lang.String content, java.lang.String type)
		throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = JournalArticleServiceUtil.search(companyId,
					portletId, groupId, title, content, type);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.journal.model.JournalArticleModel updateArticle(
		java.lang.String articleId, boolean incrementVersion,
		java.lang.String title, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayMonth, int displayDay,
		int displayYear, int expMonth, int expDay, int expYear,
		boolean neverExpires, java.lang.String articleURL, java.util.Map images)
		throws RemoteException {
		try {
			com.liferay.portlet.journal.model.JournalArticle returnValue = JournalArticleServiceUtil.updateArticle(articleId,
					incrementVersion, title, content, type, structureId,
					templateId, displayMonth, displayDay, displayYear,
					expMonth, expDay, expYear, neverExpires, articleURL, images);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin() throws RemoteException {
		try {
			boolean returnValue = JournalArticleServiceUtil.hasAdmin();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(
		com.liferay.portlet.journal.service.persistence.JournalArticlePK pk)
		throws RemoteException {
		try {
			boolean returnValue = JournalArticleServiceUtil.hasAdmin(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasDesigner() throws RemoteException {
		try {
			boolean returnValue = JournalArticleServiceUtil.hasDesigner();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasEditor() throws RemoteException {
		try {
			boolean returnValue = JournalArticleServiceUtil.hasEditor();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWriter() throws RemoteException {
		try {
			boolean returnValue = JournalArticleServiceUtil.hasWriter();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}
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

package com.liferay.portal.verify;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.service.ResourceLocalServiceUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalStructureLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.tags.NoSuchAssetException;
import com.liferay.portlet.tags.service.TagsAssetLocalServiceUtil;
import com.liferay.util.Html;
import com.liferay.util.dao.DataAccess;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="VerifyJournal.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class VerifyJournal extends VerifyProcess {

	public void verify() throws VerifyException {
		_log.info("Verifying integrity");

		try {
			verifyJournal();
		}
		catch (Exception e) {
			throw new VerifyException(e);
		}
	}

	protected void verifyJournal() throws Exception {

		// Structures

		List structures = JournalStructureLocalServiceUtil.getStructures();

		for (int i = 0; i  < structures.size(); i++) {
			JournalStructure structure = (JournalStructure)structures.get(i);

			ResourceLocalServiceUtil.addResources(
				structure.getCompanyId(), 0, 0,
				JournalStructure.class.getName(), structure.getId(), false,
				true, true);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Permissions verified for Journal structures");
		}

		// Templates

		List templates = JournalTemplateLocalServiceUtil.getTemplates();

		for (int i = 0; i < templates.size(); i++) {
			JournalTemplate template = (JournalTemplate)templates.get(i);

			ResourceLocalServiceUtil.addResources(
				template.getCompanyId(), 0, 0,
				JournalTemplate.class.getName(), template.getId(), false, true,
				true);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Permissions verified for Journal templates");
		}

		// Articles

		List articles = JournalArticleLocalServiceUtil.getArticles();

		for (int i = 0; i < articles.size(); i++) {
			JournalArticle article = (JournalArticle)articles.get(i);

			long groupId = article.getGroupId();
			String articleId = article.getArticleId();
			double version = article.getVersion();

			if (article.getResourcePrimKey() <= 0) {
				article =
					JournalArticleLocalServiceUtil.checkArticleResourcePrimKey(
						groupId, articleId, version);
			}

			ResourceLocalServiceUtil.addResources(
				article.getCompanyId(), 0, 0, JournalArticle.class.getName(),
				article.getResourcePrimKey(), false, true, true);

			try {
				TagsAssetLocalServiceUtil.getAsset(
					JournalArticle.class.getName(),
					article.getResourcePrimKey());
			}
			catch (NoSuchAssetException nsae) {
				try {
					JournalArticleLocalServiceUtil.updateTagsAsset(
						article.getUserId(), article, new String[0]);
				}
				catch (Exception e) {
					if (_log.isWarnEnabled()) {
						_log.warn(
							"Unable to update tags asset for article " +
								article.getId() + ": " + e.getMessage());
					}
				}
			}

			String content = GetterUtil.getString(article.getContent());

			String newContent = Html.replaceMsWordCharacters(content);

			if (!content.equals(newContent)) {
				JournalArticleLocalServiceUtil.updateContent(
					groupId, articleId, version, newContent);
			}

			JournalArticleLocalServiceUtil.checkStructure(
				groupId, articleId, version);

			//verifyStaleJournalArticle(article);
		}

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Permissions and Tags assets verified for Journal articles");
		}
	}

	protected void verifyStaleJournalArticle(JournalArticle article)
		throws Exception {

		long groupId = article.getGroupId();
		String articleId = article.getArticleId();
		double version = article.getVersion();

		if (article.getStructureId().equals("BASIC-RSS-ITEM")) {
			return;
		}

		long count = getPortletPreferencesCount(articleId);

		if (count == 0) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Article {groupId=" + groupId + ", articleId=" +
						articleId + ", version=" + version +
							"} is not used on any layouts");
			}
		}
	}

	protected long getPortletPreferencesCount(String articleId)
		throws Exception {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(_GET_PORTLET_PREFERENCES_COUNT);

			ps.setString(
				1, "%<name>article-id</name><value>" + articleId + "</value>%");

			rs = ps.executeQuery();

			while (rs.next()) {
				long count = rs.getLong("count_value");

				return count;
			}
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return 0;
	}

	private static final String _GET_PORTLET_PREFERENCES_COUNT =
		"select count(*) as count_value from PortletPreferences where " +
			"ownerId = 0 and ownerType = 3 and portletId like " +
				"'56_INSTANCE_%' and preferences like ?";

	private static Log _log = LogFactory.getLog(VerifyJournal.class);

}
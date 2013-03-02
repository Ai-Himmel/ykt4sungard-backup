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

package com.liferay.portlet.journal.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.admin.model.JournalConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.portlet.journal.ArticleContentException;
import com.liferay.portlet.journal.ArticleDisplayDateException;
import com.liferay.portlet.journal.ArticleExpirationDateException;
import com.liferay.portlet.journal.ArticleIdException;
import com.liferay.portlet.journal.ArticleTitleException;
import com.liferay.portlet.journal.DuplicateArticleIdException;
import com.liferay.portlet.journal.NoSuchArticleException;
import com.liferay.portlet.journal.NoSuchStructureException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalStructureServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditArticleAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.38 $
 *
 */
public class EditArticleAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			ActionUtil.getArticle(req);
		}
		catch (Exception e) {
			if (e != null &&
				//e instanceof NoSuchArticleException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.journal.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			if (cmd.equals(Constants.ADD)) {
				req.removeAttribute(WebKeys.JOURNAL_ARTICLE);
			}

			try {
				_updateArticle(config, req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchArticleException ||
					e instanceof NoSuchStructureException ||
					e instanceof NoSuchTemplateException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else if (e != null &&
						 e instanceof ArticleContentException ||
						 e instanceof ArticleDisplayDateException ||
						 e instanceof ArticleExpirationDateException ||
						 e instanceof ArticleIdException ||
						 e instanceof ArticleTitleException ||
						 e instanceof DuplicateArticleIdException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.edit_article_content");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteArticle(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchArticleException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals("approve")) {
			try {
				//_updateArticle(config, req, res);

				_approveArticle(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchArticleException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else if (e != null &&
						 e instanceof ArticleContentException ||
						 e instanceof ArticleDisplayDateException ||
						 e instanceof ArticleExpirationDateException ||
						 e instanceof ArticleTitleException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.edit_article");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			JournalArticle article =
				(JournalArticle)req.getAttribute(WebKeys.JOURNAL_ARTICLE);

			String structureId = req.getParameter("structure_id");
			String templateBased = req.getParameter("article_template_based");

			JournalConfig journalConfig =
				AdminConfigServiceUtil.getJournalConfig(
					PortalUtil.getCompanyId(req), config.getPortletName());

			if (!journalConfig.isAllowSimpleArticles()) {
				templateBased = "1";
			}

			if ((article != null) || (Validator.isNotNull(structureId))) {
				setForward(req, "portlet.journal.edit_article_content");
			}
			else if (Validator.isNotNull(templateBased)) {
				if (GetterUtil.getBoolean(templateBased)) {
					setForward(req, "portlet.journal.edit_article_structure");
				}
				else {
					setForward(req, "portlet.journal.edit_article_content");
				}
			}
			else {
				setForward(req, "portlet.journal.edit_article");
			}
		}
	}

	private void _approveArticle(ActionRequest req, ActionResponse res)
		throws Exception {

		String articleId = ParamUtil.getString(req, "article_id");

		String articleURL = ParamUtil.getString(req, "article_url");

		JournalArticleServiceUtil.approveArticle(articleId, articleURL);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteArticle(ActionRequest req, ActionResponse res)
		throws Exception {

		String articleId = ParamUtil.getString(req, "article_id");
		double version = ParamUtil.get(
			req, "article_version", JournalArticle.DEFAULT_VERSION);

		JournalArticleServiceUtil.deleteArticle(articleId, version);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private Map _getImages(UploadPortletRequest uploadReq) throws Exception {
		Map images = new HashMap();

		String imagePrefix = "structure_image_";

		Enumeration enu = uploadReq.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith(imagePrefix)) {
				File file = uploadReq.getFile(name);
				byte[] bytes = FileUtil.getBytes(file);

				if (bytes != null && bytes.length > 0) {
					name = name.substring(imagePrefix.length(), name.length());

					images.put(name, bytes);
				}
			}
		}

		return images;
	}

	private void _updateArticle(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		String articleId = ParamUtil.getString(req, "article_id");
		boolean autoArticleId = ParamUtil.get(req, "auto_article_id", false);

		double version = ParamUtil.getDouble(req, "article_version");
		boolean incrementVersion = ParamUtil.get(
			req, "article_increment_version", false);

		String title = ParamUtil.getString(req, "article_title");
		String content = ParamUtil.getString(req, "article_content");

		String type = ParamUtil.getString(req, "article_type");
		String structureId = ParamUtil.getString(req, "structure_id");
		String templateId = ParamUtil.getString(req, "template_id");

		int displayMonth = ParamUtil.getInteger(req, "article_display_month");
		int displayDay = ParamUtil.getInteger(req, "article_display_day");
		int displayYear = ParamUtil.getInteger(req, "article_display_year");

		int expMonth = ParamUtil.getInteger(req, "article_exp_month");
		int expDay = ParamUtil.getInteger(req, "article_exp_day");
		int expYear = ParamUtil.getInteger(req, "article_exp_year");

		boolean neverExpires = ParamUtil.get(
			req, "article_never_expires", false);

		String articleURL = ParamUtil.getString(req, "article_url");

		Map images = _getImages(PortalUtil.getUploadPortletRequest(req));

		JournalArticle article = null;

		if (cmd.equals(Constants.ADD)) {

			// Add article

			article = JournalArticleServiceUtil.addArticle(
				articleId, autoArticleId, config.getPortletName(),
				PortalUtil.getPortletGroupId(req), title, content, type,
				structureId, templateId, displayMonth, displayDay, displayYear,
				expMonth, expDay, expYear, neverExpires, articleURL, images);
		}
		else {

			// Merge current content with new content

			if (Validator.isNotNull(structureId)) {
				JournalArticle curArticle =
					JournalArticleServiceUtil.getArticle(articleId, version);

				JournalStructure structure =
					JournalStructureServiceUtil.getStructure(structureId);

				content = JournalUtil.mergeLocaleContent(
					curArticle.getContent(), content, structure.getXsd());
			}

			// Update article

			article = JournalArticleServiceUtil.updateArticle(
				articleId, incrementVersion, title, content, type, structureId,
				templateId, displayMonth, displayDay, displayYear, expMonth,
				expDay, expYear, neverExpires, articleURL, images);
		}

		// Session messages

		SessionMessages.add(req, "article_saved");

		// Recent articles

		JournalUtil.addRecentArticle(req, article);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}
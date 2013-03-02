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

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.NoSuchArticleException;
import com.liferay.portlet.journal.NoSuchStructureException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalStructureServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalTemplateServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lucene.Hits;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="SearchAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class SearchAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (cmd.equals("search_articles")) {
			try {
				_searchArticles(config, req);

				return mapping.findForward(
					"portlet.journal.search_articles_results");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else if (cmd.equals("search_structures")) {
			try {
				_searchStructures(config, req);

				return mapping.findForward(
					"portlet.journal.search_structures_results");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else if (cmd.equals("search_templates")) {
			try {
				_searchTemplates(config, req);

				return mapping.findForward(
					"portlet.journal.search_templates_results");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else {
			return mapping.findForward("portlet.journal.search");
		}
	}

	private void _searchArticles(PortletConfig config, RenderRequest req)
		throws Exception {

		String articleId = ParamUtil.getString(req, "article_id");
		String url = ParamUtil.getString(req, "article_url");
		String title = ParamUtil.getString(req, "article_title");
		String content = ParamUtil.getString(req, "article_content");
		String type = ParamUtil.getString(req, "article_type");

		if (Validator.isNotNull(articleId)) {
			try {
				JournalArticle article =
					JournalArticleServiceUtil.getArticle(articleId);

				req.setAttribute(WebKeys.JOURNAL_SEARCH_RESULTS, article);
			}
			catch (NoSuchArticleException nsae) {
				SessionErrors.add(req, nsae.getClass().getName(), articleId);
			}
		}
		else if (Validator.isNotNull(url)) {
			JournalArticle article = null;

			int pos = url.indexOf("?");

			if (pos != -1) {
				String query = url.substring(pos + 1, url.length());

				String[] queryParams =
					StringUtil.split(query, StringPool.AMPERSAND);

				for (int i = 0; i < queryParams.length; i++) {
					String[] nameValuePair = StringUtil.split(
						queryParams[i], StringPool.EQUAL);
					String name = nameValuePair[0];
					String value = nameValuePair[1];

					if (name.endsWith("article_id")) {
						try {
							article =
								JournalArticleServiceUtil.getArticle(value);
						}
						catch (NoSuchArticleException nsae) {
						}

						break;
					}
				}
			}
			else if (url.endsWith(".html")) {
				int x = url.lastIndexOf("/");
				int y = url.lastIndexOf(".");

				articleId = url.substring(x + 1, y);

				try {
					article = JournalArticleServiceUtil.getArticle(articleId);
				}
				catch (NoSuchArticleException nsae) {
				}
			}
			else {
				int x = url.lastIndexOf("/");

				articleId = url.substring(x + 1, url.length());

				try {
					article = JournalArticleServiceUtil.getArticle(articleId);
				}
				catch (NoSuchArticleException nsae) {
				}
			}

			if (article != null) {
				req.setAttribute(WebKeys.JOURNAL_SEARCH_RESULTS, article);
			}
			else {
				SessionErrors.add(
					req, NoSuchArticleException.class.getName(), url);
			}
		}
		else {
			Hits hits = JournalArticleServiceUtil.search(
				PortalUtil.getCompanyId(req), config.getPortletName(),
				PortalUtil.getPortletGroupId(req), title, content, type);

			req.setAttribute(WebKeys.JOURNAL_SEARCH_RESULTS, hits);
		}
	}

	private void _searchStructures(PortletConfig config, RenderRequest req)
		throws Exception {

		String structureId = ParamUtil.getString(req, "structure_id");
		String name = ParamUtil.getString(req, "structure_name");
		String title = ParamUtil.getString(req, "structure_desc");

		if (Validator.isNotNull(structureId)) {
			try {
				JournalStructure structure =
					JournalStructureServiceUtil.getStructure(structureId);

				req.setAttribute(WebKeys.JOURNAL_SEARCH_RESULTS, structure);
			}
			catch (NoSuchStructureException nsse) {
				SessionErrors.add(req, nsse.getClass().getName(), structureId);
			}
		}
	}

	private void _searchTemplates(PortletConfig config, RenderRequest req)
		throws Exception {

		String templateId = ParamUtil.getString(req, "template_id");
		String name = ParamUtil.getString(req, "template_name");
		String title = ParamUtil.getString(req, "template_desc");

		if (Validator.isNotNull(templateId)) {
			try {
				JournalTemplate template =
					JournalTemplateServiceUtil.getTemplate(templateId);

				req.setAttribute(WebKeys.JOURNAL_SEARCH_RESULTS, template);
			}
			catch (NoSuchTemplateException nsse) {
				SessionErrors.add(req, nsse.getClass().getName(), templateId);
			}
		}
	}

}
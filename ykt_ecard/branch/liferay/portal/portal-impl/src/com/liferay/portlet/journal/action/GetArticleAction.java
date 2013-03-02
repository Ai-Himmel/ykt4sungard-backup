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

package com.liferay.portlet.journal.action;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.model.impl.JournalTemplateImpl;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.StringReader;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.DocumentFactory;
import org.dom4j.Element;
import org.dom4j.ProcessingInstruction;
import org.dom4j.io.SAXReader;

/**
 * <a href="GetArticleAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class GetArticleAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			long groupId = ParamUtil.getLong(req, "groupId");
			String articleId =  ParamUtil.getString(req, "articleId");

			String languageId = LanguageUtil.getLanguageId(req);

			JournalArticle article =
				JournalArticleLocalServiceUtil.getLatestArticle(
					groupId, articleId, Boolean.TRUE);

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			Map tokens = JournalUtil.getTokens(groupId, themeDisplay);

			String xml = article.getContentByLocale(languageId);

			String contentType = ContentTypes.TEXT_HTML_UTF8;

			Document doc = null;

			Element root = null;

			if (article.isTemplateDriven()) {
				SAXReader reader = new SAXReader();

				doc = reader.read(new StringReader(xml));

				root = doc.getRootElement();

				addProcessingInstructions(doc, themeDisplay, article);

				JournalUtil.addAllReservedEls(root, tokens, article);

				xml = JournalUtil.formatXML(doc);

				contentType = ContentTypes.TEXT_XML_UTF8;
			}

			String fileName = null;
			byte[] byteArray = xml.getBytes();

			ServletResponseUtil.sendFile(res, fileName, byteArray, contentType);

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

	protected void addProcessingInstructions(
		Document doc, ThemeDisplay themeDisplay, JournalArticle article) {

		// Add style sheets in the reverse order that they appear in the
		// document

		// Theme CSS

		String url =
			themeDisplay.getPathThemeCss() + "/main.css?companyId=" +
				themeDisplay.getCompanyId() + "&themeId=" +
					themeDisplay.getThemeId() + "&colorSchemeId=" +
						themeDisplay.getColorSchemeId();

		Map arguments = new LinkedHashMap();

		arguments.put("type", "text/css");
		arguments.put("href", url);
		arguments.put("title", "theme css");

		addStyleSheet(doc, url, arguments);

		// CSS cached

		url =
			themeDisplay.getPathMain() + "/portal/css_cached?themeId=" +
				themeDisplay.getThemeId() + "&colorSchemeId=" +
					themeDisplay.getColorSchemeId();

		arguments.clear();

		arguments.put("type", "text/css");
		arguments.put("href", url);
		arguments.put("title", "cached css");
		arguments.put("alternate", "yes");

		addStyleSheet(doc, url, arguments);

		// XSL template

		String templateId = article.getTemplateId();

		if (Validator.isNotNull(templateId)) {
			JournalTemplate template = null;

			try {
				template = JournalTemplateLocalServiceUtil.getTemplate(
					article.getGroupId(), templateId);

				if (Validator.equals(
						template.getLangType(),
						JournalTemplateImpl.LANG_TYPE_XSL)) {

					url =
						themeDisplay.getPathMain() +
							"/journal/get_template?groupId=" +
								article.getGroupId() + "&templateId=" +
									templateId;

					arguments.clear();

					arguments.put("type", "text/xsl");
					arguments.put("href", url);
					arguments.put("title", "xsl");

					addStyleSheet(doc, url, arguments);
				}
			}
			catch (Exception e) {
			}
		}
	}

	protected void addStyleSheet(Document doc, String url, Map arguments) {
		List content = doc.content();

		ProcessingInstruction pi =
			DocumentFactory.getInstance().createProcessingInstruction(
				"xml-stylesheet", arguments);

		content.add(0, pi);
	}

}
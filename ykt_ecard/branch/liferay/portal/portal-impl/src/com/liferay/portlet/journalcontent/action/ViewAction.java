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

package com.liferay.portlet.journalcontent.action;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.model.JournalArticleDisplay;
import com.liferay.portlet.journalcontent.util.JournalContentUtil;
import com.liferay.util.portlet.PortletRequestUtil;

import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ViewAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class ViewAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		PortletPreferences prefs = req.getPreferences();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long groupId = ParamUtil.getLong(req, "groupId");

		if (groupId < 1) {
			groupId = GetterUtil.getLong(
				prefs.getValue("group-id", StringPool.BLANK));
		}

		String articleId = ParamUtil.getString(req, "articleId");
		String templateId = ParamUtil.getString(req, "templateId");

		if (Validator.isNull(articleId)) {
			articleId = GetterUtil.getString(
				prefs.getValue("article-id", StringPool.BLANK));
			templateId = GetterUtil.getString(
				prefs.getValue("template-id", StringPool.BLANK));
		}

		String languageId = LanguageUtil.getLanguageId(req);

		int page = ParamUtil.getInteger(req, "page", 1);

		String xmlRequest = PortletRequestUtil.toXML(req, res);

		JournalArticleDisplay articleDisplay = null;

		if ((groupId > 0) && Validator.isNotNull(articleId)) {
			articleDisplay = JournalContentUtil.getDisplay(
				groupId, articleId, templateId, languageId, themeDisplay,
				page, xmlRequest);
		}

		if (articleDisplay != null) {
			req.setAttribute(WebKeys.JOURNAL_ARTICLE_DISPLAY, articleDisplay);
		}
		else {
			req.removeAttribute(WebKeys.JOURNAL_ARTICLE_DISPLAY);

			// Don't decorate this portlet if there is no content. This will
			// prevent end users from seeing empty portlets from expired
			// articles. Administrators can still see the portlet and either
			// remove the portlet or select a new article.

			req.setAttribute(WebKeys.PORTLET_DECORATE, Boolean.FALSE);
		}

		return mapping.findForward("portlet.journal_content.view");
	}

}
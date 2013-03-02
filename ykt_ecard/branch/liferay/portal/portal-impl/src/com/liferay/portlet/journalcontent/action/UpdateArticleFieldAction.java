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
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalArticleServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.StringReader;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

/**
 * <a href="UpdateArticleFieldAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpdateArticleFieldAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			updateArticleField(req, res);

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

	protected void updateArticleField(
			HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		long groupId = ParamUtil.getLong(req, "groupId");
		String articleId = ParamUtil.getString(req, "articleId");
		double version = ParamUtil.getDouble(req, "version");

		String containerId = ParamUtil.getString(req, "containerId");

		if (Validator.isNotNull(containerId)) {
			int x = containerId.indexOf("_");
			int y = containerId.lastIndexOf("_");

			if ((x != -1) && (y != -1)) {
				groupId = GetterUtil.getLong(containerId.substring(0, x));
				articleId = containerId.substring(x + 1, y);
				version = GetterUtil.getDouble(
					containerId.substring(y, containerId.length()));
			}
		}

		String languageId = LanguageUtil.getLanguageId(req);

		String fieldName = ParamUtil.getString(req, "fieldName");
		String fieldData = ParamUtil.getString(req, "fieldData");

		if (fieldName.startsWith("journal-content-field-name-")) {
			fieldName = fieldName.substring(27, fieldName.length());
		}

		JournalArticle article = JournalArticleLocalServiceUtil.getArticle(
			groupId, articleId, version);

		String content = article.getContent();

		SAXReader reader = new SAXReader();

		Document doc = reader.read(new StringReader(content));

		if (_log.isDebugEnabled()) {
			_log.debug("Before\n" + content);
		}

		String path =
			"/root/dynamic-element[@name='" + fieldName +
				"']/dynamic-content[@language-id='" + languageId + "']";

		Node node = doc.selectSingleNode(path);

		if (node == null) {
			path =
				"/root/dynamic-element[@name='" + fieldName +
					"']/dynamic-content";

			node = doc.selectSingleNode(path);
		}

		node.setText(fieldData);

		content = JournalUtil.formatXML(doc);

		if (_log.isDebugEnabled()) {
			_log.debug("After\n" + content);
		}

		JournalArticleServiceUtil.updateContent(
			groupId, articleId, version, content);

		ServletResponseUtil.write(res, fieldData);
	}

	private static Log _log = LogFactory.getLog(UpdateArticleFieldAction.class);

}
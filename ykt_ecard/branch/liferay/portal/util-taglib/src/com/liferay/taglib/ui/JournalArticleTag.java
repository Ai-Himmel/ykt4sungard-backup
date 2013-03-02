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

package com.liferay.taglib.ui;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.taglib.util.IncludeTag;

import javax.servlet.ServletRequest;

/**
 * <a href="JournalArticleTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class JournalArticleTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute(
			"liferay-ui:journal-article:classPK", String.valueOf(_classPK));
		req.setAttribute("liferay-ui:journal-article:languageId", _languageId);
		req.setAttribute(
			"liferay-ui:journal-article:articlePage",
			String.valueOf(_articlePage));
		req.setAttribute("liferay-ui:journal-article:xmlRequest", _xmlRequest);
		req.setAttribute(
			"liferay-ui:journal-article:showTitle", String.valueOf(_showTitle));
		req.setAttribute(
			"liferay-ui:journal-article:showAvailableLocales",
			String.valueOf(_showAvailableLocales));

		return EVAL_BODY_BUFFERED;
	}

	public void setClassPK(long classPK) {
		_classPK = classPK;
	}

	public void setLanguageId(String languageId) {
		_languageId = languageId;
	}

	public void setArticlePage(int articlePage) {
		_articlePage = articlePage;
	}

	public void setXmlRequest(String xmlRequest) {
		_xmlRequest = xmlRequest;
	}

	public void setShowTitle(boolean showTitle) {
		_showTitle = showTitle;
	}

	public void setShowAvailableLocales(boolean showAvailableLocales) {
		_showAvailableLocales = showAvailableLocales;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE =
		"/html/taglib/ui/journal_article/page.jsp";

	private long _classPK;
	private String _languageId;
	private int _articlePage = 1;
	private String _xmlRequest = StringPool.BLANK;
	private boolean _showTitle;
	private boolean _showAvailableLocales;

}
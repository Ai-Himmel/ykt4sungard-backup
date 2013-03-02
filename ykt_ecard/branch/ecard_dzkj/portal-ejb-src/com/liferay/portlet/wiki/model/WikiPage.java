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

package com.liferay.portlet.wiki.model;

import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPagePK;

import java.util.Date;

/**
 * <a href="WikiPage.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.13 $
 *
 */
public class WikiPage extends WikiPageModel {

	public static final String FRONT_PAGE =
		PropsUtil.get(PropsUtil.WIKI_FRONT_PAGE_NAME);

	public static final double DEFAULT_VERSION = 1.0;

	public static final String CLASSIC_WIKI_FORMAT = "classic_wiki";

	public static final String HTML_FORMAT = "html";

	public static final String PLAIN_TEXT_FORMAT = "plain_text";

	public static final String DEFAULT_FORMAT = CLASSIC_WIKI_FORMAT;

	public static final String[] FORMATS = new String[] {
		CLASSIC_WIKI_FORMAT, HTML_FORMAT, PLAIN_TEXT_FORMAT
	};

	public WikiPage() {
		super();
	}

	public WikiPage(WikiPagePK pk) {
		super(pk);
	}

	public WikiPage(String nodeId, String title, double version,
					String companyId, String userId, String userName,
					Date createDate, String content, String format,
					boolean head) {

		super(nodeId, title, version, companyId, userId, userName, createDate,
			  content, format, head);
	}

}
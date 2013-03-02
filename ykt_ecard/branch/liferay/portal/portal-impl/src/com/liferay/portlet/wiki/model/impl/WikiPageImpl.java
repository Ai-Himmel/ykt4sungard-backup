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

package com.liferay.portlet.wiki.model.impl;

import com.liferay.portal.SystemException;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.WikiNodeLocalServiceUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="WikiPageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageImpl extends WikiPageModelImpl implements WikiPage {

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

	public WikiPageImpl() {
	}

	public String getUserUuid() throws SystemException {
		return PortalUtil.getUserValue(getUserId(), "uuid", _userUuid);
	}

	public void setUserUuid(String userUuid) {
		_userUuid = userUuid;
	}

	public WikiNode getNode() {
		WikiNode node = null;

		try {
			node = WikiNodeLocalServiceUtil.getNode(getNodeId());
		}
		catch (Exception e) {
			node = new WikiNodeImpl();

			_log.error(e);
		}

		return node;
	}

	private static Log _log = LogFactory.getLog(WikiPageImpl.class);

	private String _userUuid;

}
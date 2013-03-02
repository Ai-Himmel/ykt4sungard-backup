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

package com.liferay.portlet.journal.model.impl;

import com.liferay.portal.SystemException;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.journal.model.JournalStructure;

/**
 * <a href="JournalStructureImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalStructureImpl
	extends JournalStructureModelImpl implements JournalStructure {

	public static final String RESERVED = "reserved";

	public static final String RESERVED_ARTICLE_ID = "reserved-article-id";

	public static final String RESERVED_ARTICLE_VERSION =
		"reserved-article-version";

	public static final String RESERVED_ARTICLE_TITLE =
		"reserved-article-title";

	public static final String RESERVED_ARTICLE_DESCRIPTION =
		"reserved-article-description";

	public static final String RESERVED_ARTICLE_TYPE =
		"reserved-article-type";

	public static final String RESERVED_ARTICLE_CREATE_DATE =
		"reserved-article-create-date";

	public static final String RESERVED_ARTICLE_MODIFIED_DATE =
		"reserved-article-modified-date";

	public static final String RESERVED_ARTICLE_DISPLAY_DATE =
		"reserved-article-display-date";

	public static final String RESERVED_ARTICLE_SMALL_IMAGE_URL =
		"reserved-article-small-image-url";

	public static final String RESERVED_ARTICLE_AUTHOR_ID =
		"reserved-article-author-id";

	public static final String RESERVED_ARTICLE_AUTHOR_NAME =
		"reserved-article-author-name";

	public static final String RESERVED_ARTICLE_AUTHOR_EMAIL_ADDRESS =
		"reserved-article-author-email-address";

	public static final String RESERVED_ARTICLE_AUTHOR_COMMENTS =
		"reserved-article-author-comments";

	public static final String RESERVED_ARTICLE_AUTHOR_ORGANIZATION =
		"reserved-article-author-organization";

	public static final String RESERVED_ARTICLE_AUTHOR_LOCATION =
		"reserved-article-author-location";

	public static final String RESERVED_ARTICLE_AUTHOR_JOB_TITLE =
		"reserved-article-author-job-title";

	public JournalStructureImpl() {
	}

	public String getUserUuid() throws SystemException {
		return PortalUtil.getUserValue(getUserId(), "uuid", _userUuid);
	}

	public void setUserUuid(String userUuid) {
		_userUuid = userUuid;
	}

	private String _userUuid;

}
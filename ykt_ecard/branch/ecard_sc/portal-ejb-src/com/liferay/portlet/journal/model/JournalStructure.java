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

package com.liferay.portlet.journal.model;

import java.util.Date;

/**
 * <a href="JournalStructure.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class JournalStructure extends JournalStructureModel {

	public static final String RESERVED = "reserved";

	public static final String RESERVED_ARTICLE_ID = "reserved-article-id";

	public static final String RESERVED_ARTICLE_VERSION =
		"reserved-article-version";

	public static final String RESERVED_ARTICLE_TITLE =
		"reserved-article-title";

	public static final String RESERVED_ARTICLE_CREATE_DATE =
		"reserved-article-create-date";

	public static final String RESERVED_ARTICLE_MODIFIED_DATE =
		"reserved-article-modified-date";

	public static final String RESERVED_ARTICLE_DISPLAY_DATE =
		"reserved-article-display-date";

	public JournalStructure() {
		super();
	}

	public JournalStructure(String structureId) {
		super(structureId);
	}

	public JournalStructure(String structureId, String portletId,
							String groupId, String companyId, String userId,
							String userName, Date createDate, Date modifiedDate,
							String name, String description, String xsd) {

		super(structureId, portletId, groupId, companyId, userId, userName,
			  createDate, modifiedDate, name, description, xsd);
	}

}
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

package com.liferay.portlet.blogs.service.persistence;

import java.util.Date;

/**
 * <a href="BlogsUserHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsUserHBM {
	protected BlogsUserHBM() {
	}

	protected BlogsUserHBM(String userId) {
		_userId = userId;
	}

	protected BlogsUserHBM(String userId, String companyId, String entryId,
		Date lastPostDate) {
		_userId = userId;
		_companyId = companyId;
		_entryId = entryId;
		_lastPostDate = lastPostDate;
	}

	public String getPrimaryKey() {
		return _userId;
	}

	protected void setPrimaryKey(String pk) {
		_userId = pk;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getEntryId() {
		return _entryId;
	}

	protected void setEntryId(String entryId) {
		_entryId = entryId;
	}

	protected Date getLastPostDate() {
		return _lastPostDate;
	}

	protected void setLastPostDate(Date lastPostDate) {
		_lastPostDate = lastPostDate;
	}

	private String _userId;
	private String _companyId;
	private String _entryId;
	private Date _lastPostDate;
}
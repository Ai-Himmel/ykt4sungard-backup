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
 * <a href="BlogsCommentsHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsCommentsHBM {
	protected BlogsCommentsHBM() {
	}

	protected BlogsCommentsHBM(String commentsId) {
		_commentsId = commentsId;
	}

	protected BlogsCommentsHBM(String commentsId, String companyId,
		String userId, String userName, Date createDate, Date modifiedDate,
		String entryId, String content) {
		_commentsId = commentsId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_entryId = entryId;
		_content = content;
	}

	public String getPrimaryKey() {
		return _commentsId;
	}

	protected void setPrimaryKey(String pk) {
		_commentsId = pk;
	}

	protected String getCommentsId() {
		return _commentsId;
	}

	protected void setCommentsId(String commentsId) {
		_commentsId = commentsId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getUserName() {
		return _userName;
	}

	protected void setUserName(String userName) {
		_userName = userName;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getEntryId() {
		return _entryId;
	}

	protected void setEntryId(String entryId) {
		_entryId = entryId;
	}

	protected String getContent() {
		return _content;
	}

	protected void setContent(String content) {
		_content = content;
	}

	private String _commentsId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _entryId;
	private String _content;
}
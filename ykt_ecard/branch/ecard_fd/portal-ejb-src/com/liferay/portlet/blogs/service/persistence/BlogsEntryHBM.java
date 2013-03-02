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
 * <a href="BlogsEntryHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryHBM {
	protected BlogsEntryHBM() {
	}

	protected BlogsEntryHBM(String entryId) {
		_entryId = entryId;
	}

	protected BlogsEntryHBM(String entryId, String companyId, String userId,
		Date createDate, Date modifiedDate, String categoryId, String title,
		String content, Date displayDate, boolean sharing, boolean commentable,
		int propsCount, int commentsCount) {
		_entryId = entryId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_categoryId = categoryId;
		_title = title;
		_content = content;
		_displayDate = displayDate;
		_sharing = sharing;
		_commentable = commentable;
		_propsCount = propsCount;
		_commentsCount = commentsCount;
	}

	public String getPrimaryKey() {
		return _entryId;
	}

	protected void setPrimaryKey(String pk) {
		_entryId = pk;
	}

	protected String getEntryId() {
		return _entryId;
	}

	protected void setEntryId(String entryId) {
		_entryId = entryId;
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

	protected String getCategoryId() {
		return _categoryId;
	}

	protected void setCategoryId(String categoryId) {
		_categoryId = categoryId;
	}

	protected String getTitle() {
		return _title;
	}

	protected void setTitle(String title) {
		_title = title;
	}

	protected String getContent() {
		return _content;
	}

	protected void setContent(String content) {
		_content = content;
	}

	protected Date getDisplayDate() {
		return _displayDate;
	}

	protected void setDisplayDate(Date displayDate) {
		_displayDate = displayDate;
	}

	protected boolean getSharing() {
		return _sharing;
	}

	protected void setSharing(boolean sharing) {
		_sharing = sharing;
	}

	protected boolean getCommentable() {
		return _commentable;
	}

	protected void setCommentable(boolean commentable) {
		_commentable = commentable;
	}

	protected int getPropsCount() {
		return _propsCount;
	}

	protected void setPropsCount(int propsCount) {
		_propsCount = propsCount;
	}

	protected int getCommentsCount() {
		return _commentsCount;
	}

	protected void setCommentsCount(int commentsCount) {
		_commentsCount = commentsCount;
	}

	private String _entryId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _categoryId;
	private String _title;
	private String _content;
	private Date _displayDate;
	private boolean _sharing;
	private boolean _commentable;
	private int _propsCount;
	private int _commentsCount;
}
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

package com.liferay.portlet.blogs.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="BlogsCommentsModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.17 $
 *
 */
public class BlogsCommentsModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.blogs.model.BlogsComments"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.blogs.model.BlogsComments"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_COMMENTSID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments.commentsId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ENTRYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments.entryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CONTENT = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsComments.content"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.blogs.model.BlogsCommentsModel"));

	public BlogsCommentsModel() {
	}

	public BlogsCommentsModel(String commentsId) {
		_commentsId = commentsId;
		setNew(true);
	}

	public BlogsCommentsModel(String commentsId, String companyId,
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

	public String getCommentsId() {
		return _commentsId;
	}

	public void setCommentsId(String commentsId) {
		if (((commentsId == null) && (_commentsId != null)) ||
				((commentsId != null) && (_commentsId == null)) ||
				((commentsId != null) && (_commentsId != null) &&
				!commentsId.equals(_commentsId))) {
			if (!XSS_ALLOW_COMMENTSID) {
				commentsId = Xss.strip(commentsId);
			}

			_commentsId = commentsId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
		}
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			if (!XSS_ALLOW_USERNAME) {
				userName = Xss.strip(userName);
			}

			_userName = userName;
			setModified(true);
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
			setModified(true);
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
			setModified(true);
		}
	}

	public String getEntryId() {
		return _entryId;
	}

	public void setEntryId(String entryId) {
		if (((entryId == null) && (_entryId != null)) ||
				((entryId != null) && (_entryId == null)) ||
				((entryId != null) && (_entryId != null) &&
				!entryId.equals(_entryId))) {
			if (!XSS_ALLOW_ENTRYID) {
				entryId = Xss.strip(entryId);
			}

			_entryId = entryId;
			setModified(true);
		}
	}

	public String getContent() {
		return _content;
	}

	public void setContent(String content) {
		if (((content == null) && (_content != null)) ||
				((content != null) && (_content == null)) ||
				((content != null) && (_content != null) &&
				!content.equals(_content))) {
			if (!XSS_ALLOW_CONTENT) {
				content = Xss.strip(content);
			}

			_content = content;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new BlogsComments(getCommentsId(), getCompanyId(), getUserId(),
			getUserName(), getCreateDate(), getModifiedDate(), getEntryId(),
			getContent());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		BlogsComments blogsComments = (BlogsComments)obj;
		int value = 0;
		value = getCommentsId().compareTo(blogsComments.getCommentsId());

		if (value != 0) {
			return value;
		}

		value = getCreateDate().compareTo(blogsComments.getCreateDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		BlogsComments blogsComments = null;

		try {
			blogsComments = (BlogsComments)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = blogsComments.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
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
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
 * <a href="BlogsUserModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class BlogsUserModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.blogs.model.BlogsUser"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.blogs.model.BlogsUser"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsUser"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsUser.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsUser.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ENTRYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsUser.entryId"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.blogs.model.BlogsUserModel"));

	public BlogsUserModel() {
	}

	public BlogsUserModel(String userId) {
		_userId = userId;
		setNew(true);
	}

	public BlogsUserModel(String userId, String companyId, String entryId,
		Date lastPostDate) {
		_userId = userId;
		_companyId = companyId;
		_entryId = entryId;
		_lastPostDate = lastPostDate;
	}

	public String getPrimaryKey() {
		return _userId;
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

	public Date getLastPostDate() {
		return _lastPostDate;
	}

	public void setLastPostDate(Date lastPostDate) {
		if (((lastPostDate == null) && (_lastPostDate != null)) ||
				((lastPostDate != null) && (_lastPostDate == null)) ||
				((lastPostDate != null) && (_lastPostDate != null) &&
				!lastPostDate.equals(_lastPostDate))) {
			_lastPostDate = lastPostDate;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new BlogsUser(getUserId(), getCompanyId(), getEntryId(),
			getLastPostDate());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		BlogsUser blogsUser = (BlogsUser)obj;
		int value = 0;
		value = getLastPostDate().compareTo(blogsUser.getLastPostDate());
		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		BlogsUser blogsUser = null;

		try {
			blogsUser = (BlogsUser)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = blogsUser.getPrimaryKey();

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

	private String _userId;
	private String _companyId;
	private String _entryId;
	private Date _lastPostDate;
}
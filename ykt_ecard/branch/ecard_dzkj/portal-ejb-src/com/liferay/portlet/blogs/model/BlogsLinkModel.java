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
 * <a href="BlogsLinkModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class BlogsLinkModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.blogs.model.BlogsLink"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.blogs.model.BlogsLink"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsLink"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_LINKID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsLink.linkId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsLink.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsLink.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsLink.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_URL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsLink.url"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.blogs.model.BlogsLinkModel"));

	public BlogsLinkModel() {
	}

	public BlogsLinkModel(String linkId) {
		_linkId = linkId;
		setNew(true);
	}

	public BlogsLinkModel(String linkId, String companyId, String userId,
		Date createDate, Date modifiedDate, String name, String url) {
		_linkId = linkId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_name = name;
		_url = url;
	}

	public String getPrimaryKey() {
		return _linkId;
	}

	public String getLinkId() {
		return _linkId;
	}

	public void setLinkId(String linkId) {
		if (((linkId == null) && (_linkId != null)) ||
				((linkId != null) && (_linkId == null)) ||
				((linkId != null) && (_linkId != null) &&
				!linkId.equals(_linkId))) {
			if (!XSS_ALLOW_LINKID) {
				linkId = Xss.strip(linkId);
			}

			_linkId = linkId;
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

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			if (!XSS_ALLOW_NAME) {
				name = Xss.strip(name);
			}

			_name = name;
			setModified(true);
		}
	}

	public String getUrl() {
		return _url;
	}

	public void setUrl(String url) {
		if (((url == null) && (_url != null)) ||
				((url != null) && (_url == null)) ||
				((url != null) && (_url != null) && !url.equals(_url))) {
			if (!XSS_ALLOW_URL) {
				url = Xss.strip(url);
			}

			_url = url;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new BlogsLink(getLinkId(), getCompanyId(), getUserId(),
			getCreateDate(), getModifiedDate(), getName(), getUrl());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		BlogsLink blogsLink = (BlogsLink)obj;
		int value = 0;
		value = getName().toLowerCase().compareTo(blogsLink.getName()
														   .toLowerCase());

		if (value != 0) {
			return value;
		}

		value = getUrl().toLowerCase().compareTo(blogsLink.getUrl().toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		BlogsLink blogsLink = null;

		try {
			blogsLink = (BlogsLink)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = blogsLink.getPrimaryKey();

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

	private String _linkId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _name;
	private String _url;
}
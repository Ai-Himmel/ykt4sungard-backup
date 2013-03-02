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

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.wiki.service.persistence.WikiPagePK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="WikiPageModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.55 $
 *
 */
public class WikiPageModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.wiki.model.WikiPage"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.wiki.model.WikiPage"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage"), XSS_ALLOW);
	public static boolean XSS_ALLOW_NODEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.nodeId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TITLE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.title"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CONTENT = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.content"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FORMAT = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.wiki.model.WikiPage.format"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.wiki.model.WikiPageModel"));

	public WikiPageModel() {
	}

	public WikiPageModel(WikiPagePK pk) {
		_nodeId = pk.nodeId;
		_title = pk.title;
		_version = pk.version;
		setNew(true);
	}

	public WikiPageModel(String nodeId, String title, double version,
		String companyId, String userId, String userName, Date createDate,
		String content, String format, boolean head) {
		_nodeId = nodeId;
		_title = title;
		_version = version;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_content = content;
		_format = format;
		_head = head;
	}

	public WikiPagePK getPrimaryKey() {
		return new WikiPagePK(_nodeId, _title, _version);
	}

	public String getNodeId() {
		return _nodeId;
	}

	public void setNodeId(String nodeId) {
		if (((nodeId == null) && (_nodeId != null)) ||
				((nodeId != null) && (_nodeId == null)) ||
				((nodeId != null) && (_nodeId != null) &&
				!nodeId.equals(_nodeId))) {
			if (!XSS_ALLOW_NODEID) {
				nodeId = Xss.strip(nodeId);
			}

			_nodeId = nodeId;
			setModified(true);
		}
	}

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			if (!XSS_ALLOW_TITLE) {
				title = Xss.strip(title);
			}

			_title = title;
			setModified(true);
		}
	}

	public double getVersion() {
		return _version;
	}

	public void setVersion(double version) {
		if (version != _version) {
			_version = version;
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

	public String getFormat() {
		return _format;
	}

	public void setFormat(String format) {
		if (((format == null) && (_format != null)) ||
				((format != null) && (_format == null)) ||
				((format != null) && (_format != null) &&
				!format.equals(_format))) {
			if (!XSS_ALLOW_FORMAT) {
				format = Xss.strip(format);
			}

			_format = format;
			setModified(true);
		}
	}

	public boolean getHead() {
		return _head;
	}

	public boolean isHead() {
		return _head;
	}

	public void setHead(boolean head) {
		if (head != _head) {
			_head = head;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new WikiPage(getNodeId(), getTitle(), getVersion(),
			getCompanyId(), getUserId(), getUserName(), getCreateDate(),
			getContent(), getFormat(), getHead());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		WikiPage wikiPage = (WikiPage)obj;
		int value = 0;
		value = getNodeId().compareTo(wikiPage.getNodeId());

		if (value != 0) {
			return value;
		}

		value = getTitle().toLowerCase().compareTo(wikiPage.getTitle()
														   .toLowerCase());

		if (value != 0) {
			return value;
		}

		if (getVersion() < wikiPage.getVersion()) {
			value = -1;
		}
		else if (getVersion() > wikiPage.getVersion()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		WikiPage wikiPage = null;

		try {
			wikiPage = (WikiPage)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		WikiPagePK pk = wikiPage.getPrimaryKey();

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

	private String _nodeId;
	private String _title;
	private double _version;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private String _content;
	private String _format;
	private boolean _head;
}
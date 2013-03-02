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

package com.liferay.portlet.bookmarks.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="BookmarksEntryModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.78 $
 *
 */
public class BookmarksEntryModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.bookmarks.model.BookmarksEntry"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.bookmarks.model.BookmarksEntry"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ENTRYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.entryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_GROUPID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.groupId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FOLDERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.folderId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_URL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.url"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMMENTS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.bookmarks.model.BookmarksEntry.comments"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.bookmarks.model.BookmarksEntryModel"));

	public BookmarksEntryModel() {
	}

	public BookmarksEntryModel(String entryId) {
		_entryId = entryId;
		setNew(true);
	}

	public BookmarksEntryModel(String entryId, String groupId,
		String companyId, String userId, Date createDate, Date modifiedDate,
		String folderId, String name, String url, String comments, int visits) {
		_entryId = entryId;
		_groupId = groupId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_folderId = folderId;
		_name = name;
		_url = url;
		_comments = comments;
		_visits = visits;
	}

	public String getPrimaryKey() {
		return _entryId;
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

	public String getGroupId() {
		return _groupId;
	}

	public void setGroupId(String groupId) {
		if (((groupId == null) && (_groupId != null)) ||
				((groupId != null) && (_groupId == null)) ||
				((groupId != null) && (_groupId != null) &&
				!groupId.equals(_groupId))) {
			if (!XSS_ALLOW_GROUPID) {
				groupId = Xss.strip(groupId);
			}

			_groupId = groupId;
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

	public String getFolderId() {
		return _folderId;
	}

	public void setFolderId(String folderId) {
		if (((folderId == null) && (_folderId != null)) ||
				((folderId != null) && (_folderId == null)) ||
				((folderId != null) && (_folderId != null) &&
				!folderId.equals(_folderId))) {
			if (!XSS_ALLOW_FOLDERID) {
				folderId = Xss.strip(folderId);
			}

			_folderId = folderId;
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

	public String getComments() {
		return _comments;
	}

	public void setComments(String comments) {
		if (((comments == null) && (_comments != null)) ||
				((comments != null) && (_comments == null)) ||
				((comments != null) && (_comments != null) &&
				!comments.equals(_comments))) {
			if (!XSS_ALLOW_COMMENTS) {
				comments = Xss.strip(comments);
			}

			_comments = comments;
			setModified(true);
		}
	}

	public int getVisits() {
		return _visits;
	}

	public void setVisits(int visits) {
		if (visits != _visits) {
			_visits = visits;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new BookmarksEntry(getEntryId(), getGroupId(), getCompanyId(),
			getUserId(), getCreateDate(), getModifiedDate(), getFolderId(),
			getName(), getUrl(), getComments(), getVisits());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		BookmarksEntry bookmarksEntry = (BookmarksEntry)obj;
		int value = 0;
		value = getFolderId().compareTo(bookmarksEntry.getFolderId());

		if (value != 0) {
			return value;
		}

		value = getName().toLowerCase().compareTo(bookmarksEntry.getName()
																.toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		BookmarksEntry bookmarksEntry = null;

		try {
			bookmarksEntry = (BookmarksEntry)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = bookmarksEntry.getPrimaryKey();

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

	private String _entryId;
	private String _groupId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _folderId;
	private String _name;
	private String _url;
	private String _comments;
	private int _visits;
}
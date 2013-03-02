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

package com.liferay.portlet.network.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="NetworkAddressModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.60 $
 *
 */
public class NetworkAddressModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.network.model.NetworkAddress"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.network.model.NetworkAddress"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ADDRESSID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.addressId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_URL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.url"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMMENTS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.comments"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CONTENT = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.content"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NOTIFYBY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.network.model.NetworkAddress.notifyBy"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.network.model.NetworkAddressModel"));

	public NetworkAddressModel() {
	}

	public NetworkAddressModel(String addressId) {
		_addressId = addressId;
		setNew(true);
	}

	public NetworkAddressModel(String addressId, String userId,
		Date createDate, Date modifiedDate, String name, String url,
		String comments, String content, int status, Date lastUpdated,
		String notifyBy, long interval, boolean active) {
		_addressId = addressId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_name = name;
		_url = url;
		_comments = comments;
		_content = content;
		_status = status;
		_lastUpdated = lastUpdated;
		_notifyBy = notifyBy;
		_interval = interval;
		_active = active;
	}

	public String getPrimaryKey() {
		return _addressId;
	}

	public String getAddressId() {
		return _addressId;
	}

	public void setAddressId(String addressId) {
		if (((addressId == null) && (_addressId != null)) ||
				((addressId != null) && (_addressId == null)) ||
				((addressId != null) && (_addressId != null) &&
				!addressId.equals(_addressId))) {
			if (!XSS_ALLOW_ADDRESSID) {
				addressId = Xss.strip(addressId);
			}

			_addressId = addressId;
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

	public int getStatus() {
		return _status;
	}

	public void setStatus(int status) {
		if (status != _status) {
			_status = status;
			setModified(true);
		}
	}

	public Date getLastUpdated() {
		return _lastUpdated;
	}

	public void setLastUpdated(Date lastUpdated) {
		if (((lastUpdated == null) && (_lastUpdated != null)) ||
				((lastUpdated != null) && (_lastUpdated == null)) ||
				((lastUpdated != null) && (_lastUpdated != null) &&
				!lastUpdated.equals(_lastUpdated))) {
			_lastUpdated = lastUpdated;
			setModified(true);
		}
	}

	public String getNotifyBy() {
		return _notifyBy;
	}

	public void setNotifyBy(String notifyBy) {
		if (((notifyBy == null) && (_notifyBy != null)) ||
				((notifyBy != null) && (_notifyBy == null)) ||
				((notifyBy != null) && (_notifyBy != null) &&
				!notifyBy.equals(_notifyBy))) {
			if (!XSS_ALLOW_NOTIFYBY) {
				notifyBy = Xss.strip(notifyBy);
			}

			_notifyBy = notifyBy;
			setModified(true);
		}
	}

	public long getInterval() {
		return _interval;
	}

	public void setInterval(long interval) {
		if (interval != _interval) {
			_interval = interval;
			setModified(true);
		}
	}

	public boolean getActive() {
		return _active;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		if (active != _active) {
			_active = active;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new NetworkAddress(getAddressId(), getUserId(), getCreateDate(),
			getModifiedDate(), getName(), getUrl(), getComments(),
			getContent(), getStatus(), getLastUpdated(), getNotifyBy(),
			getInterval(), getActive());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		NetworkAddress networkAddress = (NetworkAddress)obj;
		int value = 0;
		value = getName().toLowerCase().compareTo(networkAddress.getName()
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

		NetworkAddress networkAddress = null;

		try {
			networkAddress = (NetworkAddress)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = networkAddress.getPrimaryKey();

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

	private String _addressId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _name;
	private String _url;
	private String _comments;
	private String _content;
	private int _status;
	private Date _lastUpdated;
	private String _notifyBy;
	private long _interval;
	private boolean _active;
}
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

/**
 * <a href="BlogsRefererModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.17 $
 *
 */
public class BlogsRefererModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.blogs.model.BlogsReferer"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.blogs.model.BlogsReferer"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsReferer"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_REFERERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsReferer.refererId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ENTRYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsReferer.entryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_URL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsReferer.url"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.blogs.model.BlogsReferer.type"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.blogs.model.BlogsRefererModel"));

	public BlogsRefererModel() {
	}

	public BlogsRefererModel(String refererId) {
		_refererId = refererId;
		setNew(true);
	}

	public BlogsRefererModel(String refererId, String entryId, String url,
		String type, int quantity) {
		_refererId = refererId;
		_entryId = entryId;
		_url = url;
		_type = type;
		_quantity = quantity;
	}

	public String getPrimaryKey() {
		return _refererId;
	}

	public String getRefererId() {
		return _refererId;
	}

	public void setRefererId(String refererId) {
		if (((refererId == null) && (_refererId != null)) ||
				((refererId != null) && (_refererId == null)) ||
				((refererId != null) && (_refererId != null) &&
				!refererId.equals(_refererId))) {
			if (!XSS_ALLOW_REFERERID) {
				refererId = Xss.strip(refererId);
			}

			_refererId = refererId;
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

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			if (!XSS_ALLOW_TYPE) {
				type = Xss.strip(type);
			}

			_type = type;
			setModified(true);
		}
	}

	public int getQuantity() {
		return _quantity;
	}

	public void setQuantity(int quantity) {
		if (quantity != _quantity) {
			_quantity = quantity;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new BlogsReferer(getRefererId(), getEntryId(), getUrl(),
			getType(), getQuantity());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		BlogsReferer blogsReferer = (BlogsReferer)obj;
		int value = 0;
		value = getEntryId().compareTo(blogsReferer.getEntryId());

		if (value != 0) {
			return value;
		}

		value = getType().compareTo(blogsReferer.getType());

		if (value != 0) {
			return value;
		}

		if (getQuantity() < blogsReferer.getQuantity()) {
			value = -1;
		}
		else if (getQuantity() > blogsReferer.getQuantity()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		value = getUrl().compareTo(blogsReferer.getUrl());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		BlogsReferer blogsReferer = null;

		try {
			blogsReferer = (BlogsReferer)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = blogsReferer.getPrimaryKey();

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

	private String _refererId;
	private String _entryId;
	private String _url;
	private String _type;
	private int _quantity;
}
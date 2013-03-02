/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portlet.wiki.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.wiki.model.WikiPage;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="WikiPageModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>WikiPage</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.wiki.service.model.WikiPage
 * @see com.liferay.portlet.wiki.service.model.WikiPageModel
 * @see com.liferay.portlet.wiki.service.model.impl.WikiPageImpl
 *
 */
public class WikiPageModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "WikiPage";
	public static final Object[][] TABLE_COLUMNS = {
			{ "uuid_", new Integer(Types.VARCHAR) },
			

			{ "pageId", new Integer(Types.BIGINT) },
			

			{ "resourcePrimKey", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "nodeId", new Integer(Types.BIGINT) },
			

			{ "title", new Integer(Types.VARCHAR) },
			

			{ "version", new Integer(Types.DOUBLE) },
			

			{ "content", new Integer(Types.CLOB) },
			

			{ "format", new Integer(Types.VARCHAR) },
			

			{ "head", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table WikiPage (uuid_ VARCHAR(75) null,pageId LONG not null primary key,resourcePrimKey LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,nodeId LONG,title VARCHAR(75) null,version DOUBLE,content TEXT null,format VARCHAR(75) null,head BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table WikiPage";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.wiki.model.WikiPage"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.wiki.model.WikiPage"));

	public WikiPageModelImpl() {
	}

	public long getPrimaryKey() {
		return _pageId;
	}

	public void setPrimaryKey(long pk) {
		setPageId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_pageId);
	}

	public String getUuid() {
		return GetterUtil.getString(_uuid);
	}

	public void setUuid(String uuid) {
		if ((uuid != null) && (uuid != _uuid)) {
			_uuid = uuid;
		}
	}

	public long getPageId() {
		return _pageId;
	}

	public void setPageId(long pageId) {
		if (pageId != _pageId) {
			_pageId = pageId;
		}
	}

	public long getResourcePrimKey() {
		return _resourcePrimKey;
	}

	public void setResourcePrimKey(long resourcePrimKey) {
		if (resourcePrimKey != _resourcePrimKey) {
			_resourcePrimKey = resourcePrimKey;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
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
		}
	}

	public long getNodeId() {
		return _nodeId;
	}

	public void setNodeId(long nodeId) {
		if (nodeId != _nodeId) {
			_nodeId = nodeId;
		}
	}

	public String getTitle() {
		return GetterUtil.getString(_title);
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			_title = title;
		}
	}

	public double getVersion() {
		return _version;
	}

	public void setVersion(double version) {
		if (version != _version) {
			_version = version;
		}
	}

	public String getContent() {
		return GetterUtil.getString(_content);
	}

	public void setContent(String content) {
		if (((content == null) && (_content != null)) ||
				((content != null) && (_content == null)) ||
				((content != null) && (_content != null) &&
				!content.equals(_content))) {
			_content = content;
		}
	}

	public String getFormat() {
		return GetterUtil.getString(_format);
	}

	public void setFormat(String format) {
		if (((format == null) && (_format != null)) ||
				((format != null) && (_format == null)) ||
				((format != null) && (_format != null) &&
				!format.equals(_format))) {
			_format = format;
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
		}
	}

	public WikiPage toEscapedModel() {
		if (isEscapedModel()) {
			return (WikiPage)this;
		}
		else {
			WikiPage model = new WikiPageImpl();

			model.setEscapedModel(true);

			model.setUuid(Html.escape(getUuid()));
			model.setPageId(getPageId());
			model.setResourcePrimKey(getResourcePrimKey());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setNodeId(getNodeId());
			model.setTitle(Html.escape(getTitle()));
			model.setVersion(getVersion());
			model.setContent(Html.escape(getContent()));
			model.setFormat(Html.escape(getFormat()));
			model.setHead(getHead());

			model = (WikiPage)Proxy.newProxyInstance(WikiPage.class.getClassLoader(),
					new Class[] { WikiPage.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		WikiPageImpl clone = new WikiPageImpl();

		clone.setUuid(getUuid());
		clone.setPageId(getPageId());
		clone.setResourcePrimKey(getResourcePrimKey());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setNodeId(getNodeId());
		clone.setTitle(getTitle());
		clone.setVersion(getVersion());
		clone.setContent(getContent());
		clone.setFormat(getFormat());
		clone.setHead(getHead());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		WikiPageImpl wikiPage = (WikiPageImpl)obj;

		int value = 0;

		if (getNodeId() < wikiPage.getNodeId()) {
			value = -1;
		}
		else if (getNodeId() > wikiPage.getNodeId()) {
			value = 1;
		}
		else {
			value = 0;
		}

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

		WikiPageImpl wikiPage = null;

		try {
			wikiPage = (WikiPageImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = wikiPage.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private String _uuid;
	private long _pageId;
	private long _resourcePrimKey;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private long _nodeId;
	private String _title;
	private double _version;
	private String _content;
	private String _format;
	private boolean _head;
}
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

import com.liferay.portlet.wiki.model.WikiPageResource;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="WikiPageResourceModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>WikiPageResource</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.wiki.service.model.WikiPageResource
 * @see com.liferay.portlet.wiki.service.model.WikiPageResourceModel
 * @see com.liferay.portlet.wiki.service.model.impl.WikiPageResourceImpl
 *
 */
public class WikiPageResourceModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "WikiPageResource";
	public static final Object[][] TABLE_COLUMNS = {
			{ "resourcePrimKey", new Integer(Types.BIGINT) },
			

			{ "nodeId", new Integer(Types.BIGINT) },
			

			{ "title", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table WikiPageResource (resourcePrimKey LONG not null primary key,nodeId LONG,title VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table WikiPageResource";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.wiki.model.WikiPageResource"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.wiki.model.WikiPageResource"));

	public WikiPageResourceModelImpl() {
	}

	public long getPrimaryKey() {
		return _resourcePrimKey;
	}

	public void setPrimaryKey(long pk) {
		setResourcePrimKey(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_resourcePrimKey);
	}

	public long getResourcePrimKey() {
		return _resourcePrimKey;
	}

	public void setResourcePrimKey(long resourcePrimKey) {
		if (resourcePrimKey != _resourcePrimKey) {
			_resourcePrimKey = resourcePrimKey;
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

	public WikiPageResource toEscapedModel() {
		if (isEscapedModel()) {
			return (WikiPageResource)this;
		}
		else {
			WikiPageResource model = new WikiPageResourceImpl();

			model.setEscapedModel(true);

			model.setResourcePrimKey(getResourcePrimKey());
			model.setNodeId(getNodeId());
			model.setTitle(Html.escape(getTitle()));

			model = (WikiPageResource)Proxy.newProxyInstance(WikiPageResource.class.getClassLoader(),
					new Class[] { WikiPageResource.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		WikiPageResourceImpl clone = new WikiPageResourceImpl();

		clone.setResourcePrimKey(getResourcePrimKey());
		clone.setNodeId(getNodeId());
		clone.setTitle(getTitle());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		WikiPageResourceImpl wikiPageResource = (WikiPageResourceImpl)obj;

		long pk = wikiPageResource.getPrimaryKey();

		if (getPrimaryKey() < pk) {
			return -1;
		}
		else if (getPrimaryKey() > pk) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		WikiPageResourceImpl wikiPageResource = null;

		try {
			wikiPageResource = (WikiPageResourceImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = wikiPageResource.getPrimaryKey();

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

	private long _resourcePrimKey;
	private long _nodeId;
	private String _title;
}
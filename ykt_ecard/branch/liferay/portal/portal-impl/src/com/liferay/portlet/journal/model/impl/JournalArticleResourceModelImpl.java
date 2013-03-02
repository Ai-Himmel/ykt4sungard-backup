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

package com.liferay.portlet.journal.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.journal.model.JournalArticleResource;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="JournalArticleResourceModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>JournalArticleResource</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.model.JournalArticleResource
 * @see com.liferay.portlet.journal.service.model.JournalArticleResourceModel
 * @see com.liferay.portlet.journal.service.model.impl.JournalArticleResourceImpl
 *
 */
public class JournalArticleResourceModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "JournalArticleResource";
	public static final Object[][] TABLE_COLUMNS = {
			{ "resourcePrimKey", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "articleId", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table JournalArticleResource (resourcePrimKey LONG not null primary key,groupId LONG,articleId VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table JournalArticleResource";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.journal.model.JournalArticleResource"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.journal.model.JournalArticleResource"));

	public JournalArticleResourceModelImpl() {
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

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public String getArticleId() {
		return GetterUtil.getString(_articleId);
	}

	public void setArticleId(String articleId) {
		if (((articleId == null) && (_articleId != null)) ||
				((articleId != null) && (_articleId == null)) ||
				((articleId != null) && (_articleId != null) &&
				!articleId.equals(_articleId))) {
			_articleId = articleId;
		}
	}

	public JournalArticleResource toEscapedModel() {
		if (isEscapedModel()) {
			return (JournalArticleResource)this;
		}
		else {
			JournalArticleResource model = new JournalArticleResourceImpl();

			model.setEscapedModel(true);

			model.setResourcePrimKey(getResourcePrimKey());
			model.setGroupId(getGroupId());
			model.setArticleId(Html.escape(getArticleId()));

			model = (JournalArticleResource)Proxy.newProxyInstance(JournalArticleResource.class.getClassLoader(),
					new Class[] { JournalArticleResource.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		JournalArticleResourceImpl clone = new JournalArticleResourceImpl();

		clone.setResourcePrimKey(getResourcePrimKey());
		clone.setGroupId(getGroupId());
		clone.setArticleId(getArticleId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		JournalArticleResourceImpl journalArticleResource = (JournalArticleResourceImpl)obj;

		long pk = journalArticleResource.getPrimaryKey();

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

		JournalArticleResourceImpl journalArticleResource = null;

		try {
			journalArticleResource = (JournalArticleResourceImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = journalArticleResource.getPrimaryKey();

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
	private long _groupId;
	private String _articleId;
}
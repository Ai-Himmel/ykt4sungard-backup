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

import com.liferay.portlet.journal.model.JournalContentSearch;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="JournalContentSearchModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>JournalContentSearch</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.model.JournalContentSearch
 * @see com.liferay.portlet.journal.service.model.JournalContentSearchModel
 * @see com.liferay.portlet.journal.service.model.impl.JournalContentSearchImpl
 *
 */
public class JournalContentSearchModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "JournalContentSearch";
	public static final Object[][] TABLE_COLUMNS = {
			{ "contentSearchId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "privateLayout", new Integer(Types.BOOLEAN) },
			

			{ "layoutId", new Integer(Types.BIGINT) },
			

			{ "portletId", new Integer(Types.VARCHAR) },
			

			{ "articleId", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table JournalContentSearch (contentSearchId LONG not null primary key,groupId LONG,companyId LONG,privateLayout BOOLEAN,layoutId LONG,portletId VARCHAR(200) null,articleId VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table JournalContentSearch";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.journal.model.JournalContentSearch"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.journal.model.JournalContentSearch"));

	public JournalContentSearchModelImpl() {
	}

	public long getPrimaryKey() {
		return _contentSearchId;
	}

	public void setPrimaryKey(long pk) {
		setContentSearchId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_contentSearchId);
	}

	public long getContentSearchId() {
		return _contentSearchId;
	}

	public void setContentSearchId(long contentSearchId) {
		if (contentSearchId != _contentSearchId) {
			_contentSearchId = contentSearchId;
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

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public boolean getPrivateLayout() {
		return _privateLayout;
	}

	public boolean isPrivateLayout() {
		return _privateLayout;
	}

	public void setPrivateLayout(boolean privateLayout) {
		if (privateLayout != _privateLayout) {
			_privateLayout = privateLayout;
		}
	}

	public long getLayoutId() {
		return _layoutId;
	}

	public void setLayoutId(long layoutId) {
		if (layoutId != _layoutId) {
			_layoutId = layoutId;
		}
	}

	public String getPortletId() {
		return GetterUtil.getString(_portletId);
	}

	public void setPortletId(String portletId) {
		if (((portletId == null) && (_portletId != null)) ||
				((portletId != null) && (_portletId == null)) ||
				((portletId != null) && (_portletId != null) &&
				!portletId.equals(_portletId))) {
			_portletId = portletId;
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

	public JournalContentSearch toEscapedModel() {
		if (isEscapedModel()) {
			return (JournalContentSearch)this;
		}
		else {
			JournalContentSearch model = new JournalContentSearchImpl();

			model.setEscapedModel(true);

			model.setContentSearchId(getContentSearchId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setPrivateLayout(getPrivateLayout());
			model.setLayoutId(getLayoutId());
			model.setPortletId(Html.escape(getPortletId()));
			model.setArticleId(Html.escape(getArticleId()));

			model = (JournalContentSearch)Proxy.newProxyInstance(JournalContentSearch.class.getClassLoader(),
					new Class[] { JournalContentSearch.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		JournalContentSearchImpl clone = new JournalContentSearchImpl();

		clone.setContentSearchId(getContentSearchId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setPrivateLayout(getPrivateLayout());
		clone.setLayoutId(getLayoutId());
		clone.setPortletId(getPortletId());
		clone.setArticleId(getArticleId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		JournalContentSearchImpl journalContentSearch = (JournalContentSearchImpl)obj;

		long pk = journalContentSearch.getPrimaryKey();

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

		JournalContentSearchImpl journalContentSearch = null;

		try {
			journalContentSearch = (JournalContentSearchImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = journalContentSearch.getPrimaryKey();

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

	private long _contentSearchId;
	private long _groupId;
	private long _companyId;
	private boolean _privateLayout;
	private long _layoutId;
	private String _portletId;
	private String _articleId;
}
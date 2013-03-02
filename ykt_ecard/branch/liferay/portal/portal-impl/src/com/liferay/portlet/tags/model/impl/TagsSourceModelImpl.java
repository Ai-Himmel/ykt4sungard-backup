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

package com.liferay.portlet.tags.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.tags.model.TagsSource;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="TagsSourceModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>TagsSource</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.model.TagsSource
 * @see com.liferay.portlet.tags.service.model.TagsSourceModel
 * @see com.liferay.portlet.tags.service.model.impl.TagsSourceImpl
 *
 */
public class TagsSourceModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "TagsSource";
	public static final Object[][] TABLE_COLUMNS = {
			{ "sourceId", new Integer(Types.BIGINT) },
			

			{ "parentSourceId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "acronym", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table TagsSource (sourceId LONG not null primary key,parentSourceId LONG,name VARCHAR(75) null,acronym VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table TagsSource";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.tags.model.TagsSource"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.tags.model.TagsSource"));

	public TagsSourceModelImpl() {
	}

	public long getPrimaryKey() {
		return _sourceId;
	}

	public void setPrimaryKey(long pk) {
		setSourceId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_sourceId);
	}

	public long getSourceId() {
		return _sourceId;
	}

	public void setSourceId(long sourceId) {
		if (sourceId != _sourceId) {
			_sourceId = sourceId;
		}
	}

	public long getParentSourceId() {
		return _parentSourceId;
	}

	public void setParentSourceId(long parentSourceId) {
		if (parentSourceId != _parentSourceId) {
			_parentSourceId = parentSourceId;
		}
	}

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
		}
	}

	public String getAcronym() {
		return GetterUtil.getString(_acronym);
	}

	public void setAcronym(String acronym) {
		if (((acronym == null) && (_acronym != null)) ||
				((acronym != null) && (_acronym == null)) ||
				((acronym != null) && (_acronym != null) &&
				!acronym.equals(_acronym))) {
			_acronym = acronym;
		}
	}

	public TagsSource toEscapedModel() {
		if (isEscapedModel()) {
			return (TagsSource)this;
		}
		else {
			TagsSource model = new TagsSourceImpl();

			model.setEscapedModel(true);

			model.setSourceId(getSourceId());
			model.setParentSourceId(getParentSourceId());
			model.setName(Html.escape(getName()));
			model.setAcronym(Html.escape(getAcronym()));

			model = (TagsSource)Proxy.newProxyInstance(TagsSource.class.getClassLoader(),
					new Class[] { TagsSource.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		TagsSourceImpl clone = new TagsSourceImpl();

		clone.setSourceId(getSourceId());
		clone.setParentSourceId(getParentSourceId());
		clone.setName(getName());
		clone.setAcronym(getAcronym());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		TagsSourceImpl tagsSource = (TagsSourceImpl)obj;

		long pk = tagsSource.getPrimaryKey();

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

		TagsSourceImpl tagsSource = null;

		try {
			tagsSource = (TagsSourceImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = tagsSource.getPrimaryKey();

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

	private long _sourceId;
	private long _parentSourceId;
	private String _name;
	private String _acronym;
}
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

import com.liferay.portlet.tags.model.TagsProperty;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="TagsPropertyModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>TagsProperty</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.model.TagsProperty
 * @see com.liferay.portlet.tags.service.model.TagsPropertyModel
 * @see com.liferay.portlet.tags.service.model.impl.TagsPropertyImpl
 *
 */
public class TagsPropertyModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "TagsProperty";
	public static final Object[][] TABLE_COLUMNS = {
			{ "propertyId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "entryId", new Integer(Types.BIGINT) },
			

			{ "key_", new Integer(Types.VARCHAR) },
			

			{ "value", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table TagsProperty (propertyId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,entryId LONG,key_ VARCHAR(75) null,value VARCHAR(300) null)";
	public static final String TABLE_SQL_DROP = "drop table TagsProperty";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.tags.model.TagsProperty"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.tags.model.TagsProperty"));

	public TagsPropertyModelImpl() {
	}

	public long getPrimaryKey() {
		return _propertyId;
	}

	public void setPrimaryKey(long pk) {
		setPropertyId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_propertyId);
	}

	public long getPropertyId() {
		return _propertyId;
	}

	public void setPropertyId(long propertyId) {
		if (propertyId != _propertyId) {
			_propertyId = propertyId;
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

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public long getEntryId() {
		return _entryId;
	}

	public void setEntryId(long entryId) {
		if (entryId != _entryId) {
			_entryId = entryId;
		}
	}

	public String getKey() {
		return GetterUtil.getString(_key);
	}

	public void setKey(String key) {
		if (((key == null) && (_key != null)) ||
				((key != null) && (_key == null)) ||
				((key != null) && (_key != null) && !key.equals(_key))) {
			_key = key;
		}
	}

	public String getValue() {
		return GetterUtil.getString(_value);
	}

	public void setValue(String value) {
		if (((value == null) && (_value != null)) ||
				((value != null) && (_value == null)) ||
				((value != null) && (_value != null) && !value.equals(_value))) {
			_value = value;
		}
	}

	public TagsProperty toEscapedModel() {
		if (isEscapedModel()) {
			return (TagsProperty)this;
		}
		else {
			TagsProperty model = new TagsPropertyImpl();

			model.setEscapedModel(true);

			model.setPropertyId(getPropertyId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setEntryId(getEntryId());
			model.setKey(Html.escape(getKey()));
			model.setValue(Html.escape(getValue()));

			model = (TagsProperty)Proxy.newProxyInstance(TagsProperty.class.getClassLoader(),
					new Class[] { TagsProperty.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		TagsPropertyImpl clone = new TagsPropertyImpl();

		clone.setPropertyId(getPropertyId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setEntryId(getEntryId());
		clone.setKey(getKey());
		clone.setValue(getValue());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		TagsPropertyImpl tagsProperty = (TagsPropertyImpl)obj;

		int value = 0;

		value = getKey().compareTo(tagsProperty.getKey());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		TagsPropertyImpl tagsProperty = null;

		try {
			tagsProperty = (TagsPropertyImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = tagsProperty.getPrimaryKey();

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

	private long _propertyId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _entryId;
	private String _key;
	private String _value;
}
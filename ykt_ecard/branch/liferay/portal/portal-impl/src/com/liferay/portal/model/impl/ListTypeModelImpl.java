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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.ListType;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="ListTypeModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ListType</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.ListType
 * @see com.liferay.portal.service.model.ListTypeModel
 * @see com.liferay.portal.service.model.impl.ListTypeImpl
 *
 */
public class ListTypeModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ListType";
	public static final Object[][] TABLE_COLUMNS = {
			{ "listTypeId", new Integer(Types.INTEGER) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "type_", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table ListType (listTypeId INTEGER not null primary key,name VARCHAR(75) null,type_ VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table ListType";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.ListType"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.ListType"));

	public ListTypeModelImpl() {
	}

	public int getPrimaryKey() {
		return _listTypeId;
	}

	public void setPrimaryKey(int pk) {
		setListTypeId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Integer(_listTypeId);
	}

	public int getListTypeId() {
		return _listTypeId;
	}

	public void setListTypeId(int listTypeId) {
		if (listTypeId != _listTypeId) {
			_listTypeId = listTypeId;
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

	public String getType() {
		return GetterUtil.getString(_type);
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			_type = type;
		}
	}

	public ListType toEscapedModel() {
		if (isEscapedModel()) {
			return (ListType)this;
		}
		else {
			ListType model = new ListTypeImpl();

			model.setEscapedModel(true);

			model.setListTypeId(getListTypeId());
			model.setName(Html.escape(getName()));
			model.setType(Html.escape(getType()));

			model = (ListType)Proxy.newProxyInstance(ListType.class.getClassLoader(),
					new Class[] { ListType.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ListTypeImpl clone = new ListTypeImpl();

		clone.setListTypeId(getListTypeId());
		clone.setName(getName());
		clone.setType(getType());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ListTypeImpl listType = (ListTypeImpl)obj;

		int value = 0;

		value = getName().toLowerCase().compareTo(listType.getName()
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

		ListTypeImpl listType = null;

		try {
			listType = (ListTypeImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		int pk = listType.getPrimaryKey();

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

	private int _listTypeId;
	private String _name;
	private String _type;
}
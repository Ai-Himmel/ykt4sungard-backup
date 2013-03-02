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

package com.liferay.portlet.shopping.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.shopping.model.ShoppingItemField;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="ShoppingItemFieldModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ShoppingItemField</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingItemField
 * @see com.liferay.portlet.shopping.service.model.ShoppingItemFieldModel
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingItemFieldImpl
 *
 */
public class ShoppingItemFieldModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ShoppingItemField";
	public static final Object[][] TABLE_COLUMNS = {
			{ "itemFieldId", new Integer(Types.BIGINT) },
			

			{ "itemId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "values_", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table ShoppingItemField (itemFieldId LONG not null primary key,itemId LONG,name VARCHAR(75) null,values_ STRING null,description STRING null)";
	public static final String TABLE_SQL_DROP = "drop table ShoppingItemField";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.shopping.model.ShoppingItemField"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingItemField"));

	public ShoppingItemFieldModelImpl() {
	}

	public long getPrimaryKey() {
		return _itemFieldId;
	}

	public void setPrimaryKey(long pk) {
		setItemFieldId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_itemFieldId);
	}

	public long getItemFieldId() {
		return _itemFieldId;
	}

	public void setItemFieldId(long itemFieldId) {
		if (itemFieldId != _itemFieldId) {
			_itemFieldId = itemFieldId;
		}
	}

	public long getItemId() {
		return _itemId;
	}

	public void setItemId(long itemId) {
		if (itemId != _itemId) {
			_itemId = itemId;
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

	public String getValues() {
		return GetterUtil.getString(_values);
	}

	public void setValues(String values) {
		if (((values == null) && (_values != null)) ||
				((values != null) && (_values == null)) ||
				((values != null) && (_values != null) &&
				!values.equals(_values))) {
			_values = values;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
		}
	}

	public ShoppingItemField toEscapedModel() {
		if (isEscapedModel()) {
			return (ShoppingItemField)this;
		}
		else {
			ShoppingItemField model = new ShoppingItemFieldImpl();

			model.setEscapedModel(true);

			model.setItemFieldId(getItemFieldId());
			model.setItemId(getItemId());
			model.setName(Html.escape(getName()));
			model.setValues(Html.escape(getValues()));
			model.setDescription(Html.escape(getDescription()));

			model = (ShoppingItemField)Proxy.newProxyInstance(ShoppingItemField.class.getClassLoader(),
					new Class[] { ShoppingItemField.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ShoppingItemFieldImpl clone = new ShoppingItemFieldImpl();

		clone.setItemFieldId(getItemFieldId());
		clone.setItemId(getItemId());
		clone.setName(getName());
		clone.setValues(getValues());
		clone.setDescription(getDescription());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingItemFieldImpl shoppingItemField = (ShoppingItemFieldImpl)obj;

		int value = 0;

		if (getItemId() < shoppingItemField.getItemId()) {
			value = -1;
		}
		else if (getItemId() > shoppingItemField.getItemId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		value = getName().toLowerCase().compareTo(shoppingItemField.getName()
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

		ShoppingItemFieldImpl shoppingItemField = null;

		try {
			shoppingItemField = (ShoppingItemFieldImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = shoppingItemField.getPrimaryKey();

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

	private long _itemFieldId;
	private long _itemId;
	private String _name;
	private String _values;
	private String _description;
}
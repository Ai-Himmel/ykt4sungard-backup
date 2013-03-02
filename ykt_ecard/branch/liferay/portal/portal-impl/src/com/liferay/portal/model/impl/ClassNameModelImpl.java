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
import com.liferay.portal.model.ClassName;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="ClassNameModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ClassName</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.ClassName
 * @see com.liferay.portal.service.model.ClassNameModel
 * @see com.liferay.portal.service.model.impl.ClassNameImpl
 *
 */
public class ClassNameModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ClassName_";
	public static final Object[][] TABLE_COLUMNS = {
			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "value", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table ClassName_ (classNameId LONG not null primary key,value VARCHAR(200) null)";
	public static final String TABLE_SQL_DROP = "drop table ClassName_";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.ClassName"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.ClassName"));

	public ClassNameModelImpl() {
	}

	public long getPrimaryKey() {
		return _classNameId;
	}

	public void setPrimaryKey(long pk) {
		setClassNameId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_classNameId);
	}

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		if (classNameId != _classNameId) {
			_classNameId = classNameId;
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

	public ClassName toEscapedModel() {
		if (isEscapedModel()) {
			return (ClassName)this;
		}
		else {
			ClassName model = new ClassNameImpl();

			model.setEscapedModel(true);

			model.setClassNameId(getClassNameId());
			model.setValue(Html.escape(getValue()));

			model = (ClassName)Proxy.newProxyInstance(ClassName.class.getClassLoader(),
					new Class[] { ClassName.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ClassNameImpl clone = new ClassNameImpl();

		clone.setClassNameId(getClassNameId());
		clone.setValue(getValue());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ClassNameImpl className = (ClassNameImpl)obj;

		long pk = className.getPrimaryKey();

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

		ClassNameImpl className = null;

		try {
			className = (ClassNameImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = className.getPrimaryKey();

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

	private long _classNameId;
	private String _value;
}
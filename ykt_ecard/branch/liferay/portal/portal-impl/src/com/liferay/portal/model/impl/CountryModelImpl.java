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
import com.liferay.portal.model.Country;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="CountryModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Country</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Country
 * @see com.liferay.portal.service.model.CountryModel
 * @see com.liferay.portal.service.model.impl.CountryImpl
 *
 */
public class CountryModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Country";
	public static final Object[][] TABLE_COLUMNS = {
			{ "countryId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "a2", new Integer(Types.VARCHAR) },
			

			{ "a3", new Integer(Types.VARCHAR) },
			

			{ "number_", new Integer(Types.VARCHAR) },
			

			{ "idd_", new Integer(Types.VARCHAR) },
			

			{ "active_", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table Country (countryId LONG not null primary key,name VARCHAR(75) null,a2 VARCHAR(75) null,a3 VARCHAR(75) null,number_ VARCHAR(75) null,idd_ VARCHAR(75) null,active_ BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table Country";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Country"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Country"));

	public CountryModelImpl() {
	}

	public long getPrimaryKey() {
		return _countryId;
	}

	public void setPrimaryKey(long pk) {
		setCountryId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_countryId);
	}

	public long getCountryId() {
		return _countryId;
	}

	public void setCountryId(long countryId) {
		if (countryId != _countryId) {
			_countryId = countryId;
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

	public String getA2() {
		return GetterUtil.getString(_a2);
	}

	public void setA2(String a2) {
		if (((a2 == null) && (_a2 != null)) || ((a2 != null) && (_a2 == null)) ||
				((a2 != null) && (_a2 != null) && !a2.equals(_a2))) {
			_a2 = a2;
		}
	}

	public String getA3() {
		return GetterUtil.getString(_a3);
	}

	public void setA3(String a3) {
		if (((a3 == null) && (_a3 != null)) || ((a3 != null) && (_a3 == null)) ||
				((a3 != null) && (_a3 != null) && !a3.equals(_a3))) {
			_a3 = a3;
		}
	}

	public String getNumber() {
		return GetterUtil.getString(_number);
	}

	public void setNumber(String number) {
		if (((number == null) && (_number != null)) ||
				((number != null) && (_number == null)) ||
				((number != null) && (_number != null) &&
				!number.equals(_number))) {
			_number = number;
		}
	}

	public String getIdd() {
		return GetterUtil.getString(_idd);
	}

	public void setIdd(String idd) {
		if (((idd == null) && (_idd != null)) ||
				((idd != null) && (_idd == null)) ||
				((idd != null) && (_idd != null) && !idd.equals(_idd))) {
			_idd = idd;
		}
	}

	public boolean getActive() {
		return _active;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		if (active != _active) {
			_active = active;
		}
	}

	public Country toEscapedModel() {
		if (isEscapedModel()) {
			return (Country)this;
		}
		else {
			Country model = new CountryImpl();

			model.setEscapedModel(true);

			model.setCountryId(getCountryId());
			model.setName(Html.escape(getName()));
			model.setA2(Html.escape(getA2()));
			model.setA3(Html.escape(getA3()));
			model.setNumber(Html.escape(getNumber()));
			model.setIdd(Html.escape(getIdd()));
			model.setActive(getActive());

			model = (Country)Proxy.newProxyInstance(Country.class.getClassLoader(),
					new Class[] { Country.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		CountryImpl clone = new CountryImpl();

		clone.setCountryId(getCountryId());
		clone.setName(getName());
		clone.setA2(getA2());
		clone.setA3(getA3());
		clone.setNumber(getNumber());
		clone.setIdd(getIdd());
		clone.setActive(getActive());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		CountryImpl country = (CountryImpl)obj;

		int value = 0;

		value = getName().compareTo(country.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		CountryImpl country = null;

		try {
			country = (CountryImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = country.getPrimaryKey();

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

	private long _countryId;
	private String _name;
	private String _a2;
	private String _a3;
	private String _number;
	private String _idd;
	private boolean _active;
}
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
import com.liferay.portal.model.Region;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="RegionModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Region</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Region
 * @see com.liferay.portal.service.model.RegionModel
 * @see com.liferay.portal.service.model.impl.RegionImpl
 *
 */
public class RegionModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Region";
	public static final Object[][] TABLE_COLUMNS = {
			{ "regionId", new Integer(Types.BIGINT) },
			

			{ "countryId", new Integer(Types.BIGINT) },
			

			{ "regionCode", new Integer(Types.VARCHAR) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "active_", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table Region (regionId LONG not null primary key,countryId LONG,regionCode VARCHAR(75) null,name VARCHAR(75) null,active_ BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table Region";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Region"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Region"));

	public RegionModelImpl() {
	}

	public long getPrimaryKey() {
		return _regionId;
	}

	public void setPrimaryKey(long pk) {
		setRegionId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_regionId);
	}

	public long getRegionId() {
		return _regionId;
	}

	public void setRegionId(long regionId) {
		if (regionId != _regionId) {
			_regionId = regionId;
		}
	}

	public long getCountryId() {
		return _countryId;
	}

	public void setCountryId(long countryId) {
		if (countryId != _countryId) {
			_countryId = countryId;
		}
	}

	public String getRegionCode() {
		return GetterUtil.getString(_regionCode);
	}

	public void setRegionCode(String regionCode) {
		if (((regionCode == null) && (_regionCode != null)) ||
				((regionCode != null) && (_regionCode == null)) ||
				((regionCode != null) && (_regionCode != null) &&
				!regionCode.equals(_regionCode))) {
			_regionCode = regionCode;
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

	public Region toEscapedModel() {
		if (isEscapedModel()) {
			return (Region)this;
		}
		else {
			Region model = new RegionImpl();

			model.setEscapedModel(true);

			model.setRegionId(getRegionId());
			model.setCountryId(getCountryId());
			model.setRegionCode(Html.escape(getRegionCode()));
			model.setName(Html.escape(getName()));
			model.setActive(getActive());

			model = (Region)Proxy.newProxyInstance(Region.class.getClassLoader(),
					new Class[] { Region.class }, new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		RegionImpl clone = new RegionImpl();

		clone.setRegionId(getRegionId());
		clone.setCountryId(getCountryId());
		clone.setRegionCode(getRegionCode());
		clone.setName(getName());
		clone.setActive(getActive());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		RegionImpl region = (RegionImpl)obj;

		int value = 0;

		value = getName().compareTo(region.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		RegionImpl region = null;

		try {
			region = (RegionImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = region.getPrimaryKey();

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

	private long _regionId;
	private long _countryId;
	private String _regionCode;
	private String _name;
	private boolean _active;
}
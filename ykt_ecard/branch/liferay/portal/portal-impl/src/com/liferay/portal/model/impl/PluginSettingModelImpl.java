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
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="PluginSettingModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>PluginSetting</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.PluginSetting
 * @see com.liferay.portal.service.model.PluginSettingModel
 * @see com.liferay.portal.service.model.impl.PluginSettingImpl
 *
 */
public class PluginSettingModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "PluginSetting";
	public static final Object[][] TABLE_COLUMNS = {
			{ "pluginSettingId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "pluginId", new Integer(Types.VARCHAR) },
			

			{ "pluginType", new Integer(Types.VARCHAR) },
			

			{ "roles", new Integer(Types.VARCHAR) },
			

			{ "active_", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table PluginSetting (pluginSettingId LONG not null primary key,companyId LONG,pluginId VARCHAR(75) null,pluginType VARCHAR(75) null,roles STRING null,active_ BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table PluginSetting";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.PluginSetting"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.PluginSetting"));

	public PluginSettingModelImpl() {
	}

	public long getPrimaryKey() {
		return _pluginSettingId;
	}

	public void setPrimaryKey(long pk) {
		setPluginSettingId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_pluginSettingId);
	}

	public long getPluginSettingId() {
		return _pluginSettingId;
	}

	public void setPluginSettingId(long pluginSettingId) {
		if (pluginSettingId != _pluginSettingId) {
			_pluginSettingId = pluginSettingId;
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

	public String getPluginId() {
		return GetterUtil.getString(_pluginId);
	}

	public void setPluginId(String pluginId) {
		if (((pluginId == null) && (_pluginId != null)) ||
				((pluginId != null) && (_pluginId == null)) ||
				((pluginId != null) && (_pluginId != null) &&
				!pluginId.equals(_pluginId))) {
			_pluginId = pluginId;
		}
	}

	public String getPluginType() {
		return GetterUtil.getString(_pluginType);
	}

	public void setPluginType(String pluginType) {
		if (((pluginType == null) && (_pluginType != null)) ||
				((pluginType != null) && (_pluginType == null)) ||
				((pluginType != null) && (_pluginType != null) &&
				!pluginType.equals(_pluginType))) {
			_pluginType = pluginType;
		}
	}

	public String getRoles() {
		return GetterUtil.getString(_roles);
	}

	public void setRoles(String roles) {
		if (((roles == null) && (_roles != null)) ||
				((roles != null) && (_roles == null)) ||
				((roles != null) && (_roles != null) && !roles.equals(_roles))) {
			_roles = roles;
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

	public PluginSetting toEscapedModel() {
		if (isEscapedModel()) {
			return (PluginSetting)this;
		}
		else {
			PluginSetting model = new PluginSettingImpl();

			model.setEscapedModel(true);

			model.setPluginSettingId(getPluginSettingId());
			model.setCompanyId(getCompanyId());
			model.setPluginId(Html.escape(getPluginId()));
			model.setPluginType(Html.escape(getPluginType()));
			model.setRoles(Html.escape(getRoles()));
			model.setActive(getActive());

			model = (PluginSetting)Proxy.newProxyInstance(PluginSetting.class.getClassLoader(),
					new Class[] { PluginSetting.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PluginSettingImpl clone = new PluginSettingImpl();

		clone.setPluginSettingId(getPluginSettingId());
		clone.setCompanyId(getCompanyId());
		clone.setPluginId(getPluginId());
		clone.setPluginType(getPluginType());
		clone.setRoles(getRoles());
		clone.setActive(getActive());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PluginSettingImpl pluginSetting = (PluginSettingImpl)obj;

		long pk = pluginSetting.getPrimaryKey();

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

		PluginSettingImpl pluginSetting = null;

		try {
			pluginSetting = (PluginSettingImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = pluginSetting.getPrimaryKey();

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

	private long _pluginSettingId;
	private long _companyId;
	private String _pluginId;
	private String _pluginType;
	private String _roles;
	private boolean _active;
}
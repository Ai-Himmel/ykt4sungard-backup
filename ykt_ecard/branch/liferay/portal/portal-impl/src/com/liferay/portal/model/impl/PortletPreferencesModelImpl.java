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
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="PortletPreferencesModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>PortletPreferences</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.PortletPreferences
 * @see com.liferay.portal.service.model.PortletPreferencesModel
 * @see com.liferay.portal.service.model.impl.PortletPreferencesImpl
 *
 */
public class PortletPreferencesModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "PortletPreferences";
	public static final Object[][] TABLE_COLUMNS = {
			{ "portletPreferencesId", new Integer(Types.BIGINT) },
			

			{ "ownerId", new Integer(Types.BIGINT) },
			

			{ "ownerType", new Integer(Types.INTEGER) },
			

			{ "plid", new Integer(Types.BIGINT) },
			

			{ "portletId", new Integer(Types.VARCHAR) },
			

			{ "preferences", new Integer(Types.CLOB) }
		};
	public static final String TABLE_SQL_CREATE = "create table PortletPreferences (portletPreferencesId LONG not null primary key,ownerId LONG,ownerType INTEGER,plid LONG,portletId VARCHAR(200) null,preferences TEXT null)";
	public static final String TABLE_SQL_DROP = "drop table PortletPreferences";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.PortletPreferences"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.PortletPreferences"));

	public PortletPreferencesModelImpl() {
	}

	public long getPrimaryKey() {
		return _portletPreferencesId;
	}

	public void setPrimaryKey(long pk) {
		setPortletPreferencesId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_portletPreferencesId);
	}

	public long getPortletPreferencesId() {
		return _portletPreferencesId;
	}

	public void setPortletPreferencesId(long portletPreferencesId) {
		if (portletPreferencesId != _portletPreferencesId) {
			_portletPreferencesId = portletPreferencesId;
		}
	}

	public long getOwnerId() {
		return _ownerId;
	}

	public void setOwnerId(long ownerId) {
		if (ownerId != _ownerId) {
			_ownerId = ownerId;
		}
	}

	public int getOwnerType() {
		return _ownerType;
	}

	public void setOwnerType(int ownerType) {
		if (ownerType != _ownerType) {
			_ownerType = ownerType;
		}
	}

	public long getPlid() {
		return _plid;
	}

	public void setPlid(long plid) {
		if (plid != _plid) {
			_plid = plid;
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

	public String getPreferences() {
		return GetterUtil.getString(_preferences);
	}

	public void setPreferences(String preferences) {
		if (((preferences == null) && (_preferences != null)) ||
				((preferences != null) && (_preferences == null)) ||
				((preferences != null) && (_preferences != null) &&
				!preferences.equals(_preferences))) {
			_preferences = preferences;
		}
	}

	public PortletPreferences toEscapedModel() {
		if (isEscapedModel()) {
			return (PortletPreferences)this;
		}
		else {
			PortletPreferences model = new PortletPreferencesImpl();

			model.setEscapedModel(true);

			model.setPortletPreferencesId(getPortletPreferencesId());
			model.setOwnerId(getOwnerId());
			model.setOwnerType(getOwnerType());
			model.setPlid(getPlid());
			model.setPortletId(Html.escape(getPortletId()));
			model.setPreferences(Html.escape(getPreferences()));

			model = (PortletPreferences)Proxy.newProxyInstance(PortletPreferences.class.getClassLoader(),
					new Class[] { PortletPreferences.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PortletPreferencesImpl clone = new PortletPreferencesImpl();

		clone.setPortletPreferencesId(getPortletPreferencesId());
		clone.setOwnerId(getOwnerId());
		clone.setOwnerType(getOwnerType());
		clone.setPlid(getPlid());
		clone.setPortletId(getPortletId());
		clone.setPreferences(getPreferences());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PortletPreferencesImpl portletPreferences = (PortletPreferencesImpl)obj;

		long pk = portletPreferences.getPrimaryKey();

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

		PortletPreferencesImpl portletPreferences = null;

		try {
			portletPreferences = (PortletPreferencesImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = portletPreferences.getPrimaryKey();

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

	private long _portletPreferencesId;
	private long _ownerId;
	private int _ownerType;
	private long _plid;
	private String _portletId;
	private String _preferences;
}
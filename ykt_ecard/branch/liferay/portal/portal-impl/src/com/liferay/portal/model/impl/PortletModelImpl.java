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
import com.liferay.portal.model.Portlet;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="PortletModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Portlet</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Portlet
 * @see com.liferay.portal.service.model.PortletModel
 * @see com.liferay.portal.service.model.impl.PortletImpl
 *
 */
public class PortletModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Portlet";
	public static final Object[][] TABLE_COLUMNS = {
			{ "id_", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "portletId", new Integer(Types.VARCHAR) },
			

			{ "roles", new Integer(Types.VARCHAR) },
			

			{ "active_", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table Portlet (id_ LONG not null primary key,companyId LONG,portletId VARCHAR(200) null,roles STRING null,active_ BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table Portlet";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Portlet"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Portlet"));

	public PortletModelImpl() {
	}

	public long getPrimaryKey() {
		return _id;
	}

	public void setPrimaryKey(long pk) {
		setId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_id);
	}

	public long getId() {
		return _id;
	}

	public void setId(long id) {
		if (id != _id) {
			_id = id;
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

	public Portlet toEscapedModel() {
		if (isEscapedModel()) {
			return (Portlet)this;
		}
		else {
			Portlet model = new PortletImpl();

			model.setEscapedModel(true);

			model.setId(getId());
			model.setCompanyId(getCompanyId());
			model.setPortletId(Html.escape(getPortletId()));
			model.setRoles(Html.escape(getRoles()));
			model.setActive(getActive());

			model = (Portlet)Proxy.newProxyInstance(Portlet.class.getClassLoader(),
					new Class[] { Portlet.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PortletImpl clone = new PortletImpl();

		clone.setId(getId());
		clone.setCompanyId(getCompanyId());
		clone.setPortletId(getPortletId());
		clone.setRoles(getRoles());
		clone.setActive(getActive());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PortletImpl portlet = (PortletImpl)obj;

		long pk = portlet.getPrimaryKey();

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

		PortletImpl portlet = null;

		try {
			portlet = (PortletImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = portlet.getPrimaryKey();

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

	private long _id;
	private long _companyId;
	private String _portletId;
	private String _roles;
	private boolean _active;
}
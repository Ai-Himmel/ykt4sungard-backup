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
import com.liferay.portal.model.Organization;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="OrganizationModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Organization</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Organization
 * @see com.liferay.portal.service.model.OrganizationModel
 * @see com.liferay.portal.service.model.impl.OrganizationImpl
 *
 */
public class OrganizationModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Organization_";
	public static final Object[][] TABLE_COLUMNS = {
			{ "organizationId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "parentOrganizationId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "location", new Integer(Types.BOOLEAN) },
			

			{ "recursable", new Integer(Types.BOOLEAN) },
			

			{ "regionId", new Integer(Types.BIGINT) },
			

			{ "countryId", new Integer(Types.BIGINT) },
			

			{ "statusId", new Integer(Types.INTEGER) },
			

			{ "comments", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table Organization_ (organizationId LONG not null primary key,companyId LONG,parentOrganizationId LONG,name VARCHAR(100) null,location BOOLEAN,recursable BOOLEAN,regionId LONG,countryId LONG,statusId INTEGER,comments STRING null)";
	public static final String TABLE_SQL_DROP = "drop table Organization_";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Organization"),
			true);
	public static final boolean CACHE_ENABLED_GROUPS_ORGS = com.liferay.portal.model.impl.GroupModelImpl.CACHE_ENABLED_GROUPS_ORGS;
	public static final boolean CACHE_ENABLED_USERS_ORGS = com.liferay.portal.model.impl.UserModelImpl.CACHE_ENABLED_USERS_ORGS;
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Organization"));

	public OrganizationModelImpl() {
	}

	public long getPrimaryKey() {
		return _organizationId;
	}

	public void setPrimaryKey(long pk) {
		setOrganizationId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_organizationId);
	}

	public long getOrganizationId() {
		return _organizationId;
	}

	public void setOrganizationId(long organizationId) {
		if (organizationId != _organizationId) {
			_organizationId = organizationId;
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

	public long getParentOrganizationId() {
		return _parentOrganizationId;
	}

	public void setParentOrganizationId(long parentOrganizationId) {
		if (parentOrganizationId != _parentOrganizationId) {
			_parentOrganizationId = parentOrganizationId;
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

	public boolean getLocation() {
		return _location;
	}

	public boolean isLocation() {
		return _location;
	}

	public void setLocation(boolean location) {
		if (location != _location) {
			_location = location;
		}
	}

	public boolean getRecursable() {
		return _recursable;
	}

	public boolean isRecursable() {
		return _recursable;
	}

	public void setRecursable(boolean recursable) {
		if (recursable != _recursable) {
			_recursable = recursable;
		}
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

	public int getStatusId() {
		return _statusId;
	}

	public void setStatusId(int statusId) {
		if (statusId != _statusId) {
			_statusId = statusId;
		}
	}

	public String getComments() {
		return GetterUtil.getString(_comments);
	}

	public void setComments(String comments) {
		if (((comments == null) && (_comments != null)) ||
				((comments != null) && (_comments == null)) ||
				((comments != null) && (_comments != null) &&
				!comments.equals(_comments))) {
			_comments = comments;
		}
	}

	public Organization toEscapedModel() {
		if (isEscapedModel()) {
			return (Organization)this;
		}
		else {
			Organization model = new OrganizationImpl();

			model.setEscapedModel(true);

			model.setOrganizationId(getOrganizationId());
			model.setCompanyId(getCompanyId());
			model.setParentOrganizationId(getParentOrganizationId());
			model.setName(Html.escape(getName()));
			model.setLocation(getLocation());
			model.setRecursable(getRecursable());
			model.setRegionId(getRegionId());
			model.setCountryId(getCountryId());
			model.setStatusId(getStatusId());
			model.setComments(Html.escape(getComments()));

			model = (Organization)Proxy.newProxyInstance(Organization.class.getClassLoader(),
					new Class[] { Organization.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		OrganizationImpl clone = new OrganizationImpl();

		clone.setOrganizationId(getOrganizationId());
		clone.setCompanyId(getCompanyId());
		clone.setParentOrganizationId(getParentOrganizationId());
		clone.setName(getName());
		clone.setLocation(getLocation());
		clone.setRecursable(getRecursable());
		clone.setRegionId(getRegionId());
		clone.setCountryId(getCountryId());
		clone.setStatusId(getStatusId());
		clone.setComments(getComments());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		OrganizationImpl organization = (OrganizationImpl)obj;

		int value = 0;

		value = getName().compareTo(organization.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		OrganizationImpl organization = null;

		try {
			organization = (OrganizationImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = organization.getPrimaryKey();

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

	private long _organizationId;
	private long _companyId;
	private long _parentOrganizationId;
	private String _name;
	private boolean _location;
	private boolean _recursable;
	private long _regionId;
	private long _countryId;
	private int _statusId;
	private String _comments;
}
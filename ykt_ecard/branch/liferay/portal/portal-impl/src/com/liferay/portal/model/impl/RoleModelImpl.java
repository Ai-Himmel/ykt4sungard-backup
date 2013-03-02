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
import com.liferay.portal.model.Role;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="RoleModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Role</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Role
 * @see com.liferay.portal.service.model.RoleModel
 * @see com.liferay.portal.service.model.impl.RoleImpl
 *
 */
public class RoleModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Role_";
	public static final Object[][] TABLE_COLUMNS = {
			{ "roleId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "type_", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table Role_ (roleId LONG not null primary key,companyId LONG,classNameId LONG,classPK LONG,name VARCHAR(75) null,description STRING null,type_ INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table Role_";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Role"),
			true);
	public static final boolean CACHE_ENABLED_GROUPS_ROLES = com.liferay.portal.model.impl.GroupModelImpl.CACHE_ENABLED_GROUPS_ROLES;
	public static final boolean CACHE_ENABLED_ROLES_PERMISSIONS = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.Roles_Permissions"), true);
	public static final boolean CACHE_ENABLED_USERS_ROLES = com.liferay.portal.model.impl.UserModelImpl.CACHE_ENABLED_USERS_ROLES;
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Role"));

	public RoleModelImpl() {
	}

	public long getPrimaryKey() {
		return _roleId;
	}

	public void setPrimaryKey(long pk) {
		setRoleId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_roleId);
	}

	public long getRoleId() {
		return _roleId;
	}

	public void setRoleId(long roleId) {
		if (roleId != _roleId) {
			_roleId = roleId;
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

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		if (classNameId != _classNameId) {
			_classNameId = classNameId;
		}
	}

	public long getClassPK() {
		return _classPK;
	}

	public void setClassPK(long classPK) {
		if (classPK != _classPK) {
			_classPK = classPK;
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

	public int getType() {
		return _type;
	}

	public void setType(int type) {
		if (type != _type) {
			_type = type;
		}
	}

	public Role toEscapedModel() {
		if (isEscapedModel()) {
			return (Role)this;
		}
		else {
			Role model = new RoleImpl();

			model.setEscapedModel(true);

			model.setRoleId(getRoleId());
			model.setCompanyId(getCompanyId());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));
			model.setType(getType());

			model = (Role)Proxy.newProxyInstance(Role.class.getClassLoader(),
					new Class[] { Role.class }, new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		RoleImpl clone = new RoleImpl();

		clone.setRoleId(getRoleId());
		clone.setCompanyId(getCompanyId());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setName(getName());
		clone.setDescription(getDescription());
		clone.setType(getType());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		RoleImpl role = (RoleImpl)obj;

		int value = 0;

		value = getName().compareTo(role.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		RoleImpl role = null;

		try {
			role = (RoleImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = role.getPrimaryKey();

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

	private long _roleId;
	private long _companyId;
	private long _classNameId;
	private long _classPK;
	private String _name;
	private String _description;
	private int _type;
}
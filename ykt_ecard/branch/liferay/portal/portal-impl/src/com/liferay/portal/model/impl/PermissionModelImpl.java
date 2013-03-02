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
import com.liferay.portal.model.Permission;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="PermissionModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Permission</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Permission
 * @see com.liferay.portal.service.model.PermissionModel
 * @see com.liferay.portal.service.model.impl.PermissionImpl
 *
 */
public class PermissionModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Permission_";
	public static final Object[][] TABLE_COLUMNS = {
			{ "permissionId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "actionId", new Integer(Types.VARCHAR) },
			

			{ "resourceId", new Integer(Types.BIGINT) }
		};
	public static final String TABLE_SQL_CREATE = "create table Permission_ (permissionId LONG not null primary key,companyId LONG,actionId VARCHAR(75) null,resourceId LONG)";
	public static final String TABLE_SQL_DROP = "drop table Permission_";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Permission"),
			true);
	public static final boolean CACHE_ENABLED_GROUPS_PERMISSIONS = com.liferay.portal.model.impl.GroupModelImpl.CACHE_ENABLED_GROUPS_PERMISSIONS;
	public static final boolean CACHE_ENABLED_ROLES_PERMISSIONS = com.liferay.portal.model.impl.RoleModelImpl.CACHE_ENABLED_ROLES_PERMISSIONS;
	public static final boolean CACHE_ENABLED_USERS_PERMISSIONS = com.liferay.portal.model.impl.UserModelImpl.CACHE_ENABLED_USERS_PERMISSIONS;
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Permission"));

	public PermissionModelImpl() {
	}

	public long getPrimaryKey() {
		return _permissionId;
	}

	public void setPrimaryKey(long pk) {
		setPermissionId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_permissionId);
	}

	public long getPermissionId() {
		return _permissionId;
	}

	public void setPermissionId(long permissionId) {
		if (permissionId != _permissionId) {
			_permissionId = permissionId;
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

	public String getActionId() {
		return GetterUtil.getString(_actionId);
	}

	public void setActionId(String actionId) {
		if (((actionId == null) && (_actionId != null)) ||
				((actionId != null) && (_actionId == null)) ||
				((actionId != null) && (_actionId != null) &&
				!actionId.equals(_actionId))) {
			_actionId = actionId;
		}
	}

	public long getResourceId() {
		return _resourceId;
	}

	public void setResourceId(long resourceId) {
		if (resourceId != _resourceId) {
			_resourceId = resourceId;
		}
	}

	public Permission toEscapedModel() {
		if (isEscapedModel()) {
			return (Permission)this;
		}
		else {
			Permission model = new PermissionImpl();

			model.setEscapedModel(true);

			model.setPermissionId(getPermissionId());
			model.setCompanyId(getCompanyId());
			model.setActionId(Html.escape(getActionId()));
			model.setResourceId(getResourceId());

			model = (Permission)Proxy.newProxyInstance(Permission.class.getClassLoader(),
					new Class[] { Permission.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PermissionImpl clone = new PermissionImpl();

		clone.setPermissionId(getPermissionId());
		clone.setCompanyId(getCompanyId());
		clone.setActionId(getActionId());
		clone.setResourceId(getResourceId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PermissionImpl permission = (PermissionImpl)obj;

		long pk = permission.getPrimaryKey();

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

		PermissionImpl permission = null;

		try {
			permission = (PermissionImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = permission.getPrimaryKey();

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

	private long _permissionId;
	private long _companyId;
	private String _actionId;
	private long _resourceId;
}
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
import com.liferay.portal.model.OrgGroupPermission;
import com.liferay.portal.service.persistence.OrgGroupPermissionPK;
import com.liferay.portal.util.PropsUtil;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="OrgGroupPermissionModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>OrgGroupPermission</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.OrgGroupPermission
 * @see com.liferay.portal.service.model.OrgGroupPermissionModel
 * @see com.liferay.portal.service.model.impl.OrgGroupPermissionImpl
 *
 */
public class OrgGroupPermissionModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "OrgGroupPermission";
	public static final Object[][] TABLE_COLUMNS = {
			{ "organizationId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "permissionId", new Integer(Types.BIGINT) }
		};
	public static final String TABLE_SQL_CREATE = "create table OrgGroupPermission (organizationId LONG not null,groupId LONG not null,permissionId LONG not null,primary key (organizationId, groupId, permissionId))";
	public static final String TABLE_SQL_DROP = "drop table OrgGroupPermission";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.OrgGroupPermission"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.OrgGroupPermission"));

	public OrgGroupPermissionModelImpl() {
	}

	public OrgGroupPermissionPK getPrimaryKey() {
		return new OrgGroupPermissionPK(_organizationId, _groupId, _permissionId);
	}

	public void setPrimaryKey(OrgGroupPermissionPK pk) {
		setOrganizationId(pk.organizationId);
		setGroupId(pk.groupId);
		setPermissionId(pk.permissionId);
	}

	public Serializable getPrimaryKeyObj() {
		return new OrgGroupPermissionPK(_organizationId, _groupId, _permissionId);
	}

	public long getOrganizationId() {
		return _organizationId;
	}

	public void setOrganizationId(long organizationId) {
		if (organizationId != _organizationId) {
			_organizationId = organizationId;
		}
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public long getPermissionId() {
		return _permissionId;
	}

	public void setPermissionId(long permissionId) {
		if (permissionId != _permissionId) {
			_permissionId = permissionId;
		}
	}

	public OrgGroupPermission toEscapedModel() {
		if (isEscapedModel()) {
			return (OrgGroupPermission)this;
		}
		else {
			OrgGroupPermission model = new OrgGroupPermissionImpl();

			model.setEscapedModel(true);

			model.setOrganizationId(getOrganizationId());
			model.setGroupId(getGroupId());
			model.setPermissionId(getPermissionId());

			model = (OrgGroupPermission)Proxy.newProxyInstance(OrgGroupPermission.class.getClassLoader(),
					new Class[] { OrgGroupPermission.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		OrgGroupPermissionImpl clone = new OrgGroupPermissionImpl();

		clone.setOrganizationId(getOrganizationId());
		clone.setGroupId(getGroupId());
		clone.setPermissionId(getPermissionId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		OrgGroupPermissionImpl orgGroupPermission = (OrgGroupPermissionImpl)obj;

		OrgGroupPermissionPK pk = orgGroupPermission.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		OrgGroupPermissionImpl orgGroupPermission = null;

		try {
			orgGroupPermission = (OrgGroupPermissionImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		OrgGroupPermissionPK pk = orgGroupPermission.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private long _organizationId;
	private long _groupId;
	private long _permissionId;
}
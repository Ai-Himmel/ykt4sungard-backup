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
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="UserGroupModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>UserGroup</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.UserGroup
 * @see com.liferay.portal.service.model.UserGroupModel
 * @see com.liferay.portal.service.model.impl.UserGroupImpl
 *
 */
public class UserGroupModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "UserGroup";
	public static final Object[][] TABLE_COLUMNS = {
			{ "userGroupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "parentUserGroupId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table UserGroup (userGroupId LONG not null primary key,companyId LONG,parentUserGroupId LONG,name VARCHAR(75) null,description STRING null)";
	public static final String TABLE_SQL_DROP = "drop table UserGroup";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.UserGroup"),
			true);
	public static final boolean CACHE_ENABLED_USERS_USERGROUPS = com.liferay.portal.model.impl.UserModelImpl.CACHE_ENABLED_USERS_USERGROUPS;
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.UserGroup"));

	public UserGroupModelImpl() {
	}

	public long getPrimaryKey() {
		return _userGroupId;
	}

	public void setPrimaryKey(long pk) {
		setUserGroupId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_userGroupId);
	}

	public long getUserGroupId() {
		return _userGroupId;
	}

	public void setUserGroupId(long userGroupId) {
		if (userGroupId != _userGroupId) {
			_userGroupId = userGroupId;
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

	public long getParentUserGroupId() {
		return _parentUserGroupId;
	}

	public void setParentUserGroupId(long parentUserGroupId) {
		if (parentUserGroupId != _parentUserGroupId) {
			_parentUserGroupId = parentUserGroupId;
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

	public UserGroup toEscapedModel() {
		if (isEscapedModel()) {
			return (UserGroup)this;
		}
		else {
			UserGroup model = new UserGroupImpl();

			model.setEscapedModel(true);

			model.setUserGroupId(getUserGroupId());
			model.setCompanyId(getCompanyId());
			model.setParentUserGroupId(getParentUserGroupId());
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));

			model = (UserGroup)Proxy.newProxyInstance(UserGroup.class.getClassLoader(),
					new Class[] { UserGroup.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		UserGroupImpl clone = new UserGroupImpl();

		clone.setUserGroupId(getUserGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setParentUserGroupId(getParentUserGroupId());
		clone.setName(getName());
		clone.setDescription(getDescription());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		UserGroupImpl userGroup = (UserGroupImpl)obj;

		int value = 0;

		value = getName().compareTo(userGroup.getName());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		UserGroupImpl userGroup = null;

		try {
			userGroup = (UserGroupImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = userGroup.getPrimaryKey();

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

	private long _userGroupId;
	private long _companyId;
	private long _parentUserGroupId;
	private String _name;
	private String _description;
}
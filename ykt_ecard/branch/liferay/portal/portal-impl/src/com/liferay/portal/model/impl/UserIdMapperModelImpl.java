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
import com.liferay.portal.model.UserIdMapper;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="UserIdMapperModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>UserIdMapper</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.UserIdMapper
 * @see com.liferay.portal.service.model.UserIdMapperModel
 * @see com.liferay.portal.service.model.impl.UserIdMapperImpl
 *
 */
public class UserIdMapperModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "UserIdMapper";
	public static final Object[][] TABLE_COLUMNS = {
			{ "userIdMapperId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "type_", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "externalUserId", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table UserIdMapper (userIdMapperId LONG not null primary key,userId LONG,type_ VARCHAR(75) null,description VARCHAR(75) null,externalUserId VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table UserIdMapper";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.UserIdMapper"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.UserIdMapper"));

	public UserIdMapperModelImpl() {
	}

	public long getPrimaryKey() {
		return _userIdMapperId;
	}

	public void setPrimaryKey(long pk) {
		setUserIdMapperId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_userIdMapperId);
	}

	public long getUserIdMapperId() {
		return _userIdMapperId;
	}

	public void setUserIdMapperId(long userIdMapperId) {
		if (userIdMapperId != _userIdMapperId) {
			_userIdMapperId = userIdMapperId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getType() {
		return GetterUtil.getString(_type);
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			_type = type;
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

	public String getExternalUserId() {
		return GetterUtil.getString(_externalUserId);
	}

	public void setExternalUserId(String externalUserId) {
		if (((externalUserId == null) && (_externalUserId != null)) ||
				((externalUserId != null) && (_externalUserId == null)) ||
				((externalUserId != null) && (_externalUserId != null) &&
				!externalUserId.equals(_externalUserId))) {
			_externalUserId = externalUserId;
		}
	}

	public UserIdMapper toEscapedModel() {
		if (isEscapedModel()) {
			return (UserIdMapper)this;
		}
		else {
			UserIdMapper model = new UserIdMapperImpl();

			model.setEscapedModel(true);

			model.setUserIdMapperId(getUserIdMapperId());
			model.setUserId(getUserId());
			model.setType(Html.escape(getType()));
			model.setDescription(Html.escape(getDescription()));
			model.setExternalUserId(Html.escape(getExternalUserId()));

			model = (UserIdMapper)Proxy.newProxyInstance(UserIdMapper.class.getClassLoader(),
					new Class[] { UserIdMapper.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		UserIdMapperImpl clone = new UserIdMapperImpl();

		clone.setUserIdMapperId(getUserIdMapperId());
		clone.setUserId(getUserId());
		clone.setType(getType());
		clone.setDescription(getDescription());
		clone.setExternalUserId(getExternalUserId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		UserIdMapperImpl userIdMapper = (UserIdMapperImpl)obj;

		long pk = userIdMapper.getPrimaryKey();

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

		UserIdMapperImpl userIdMapper = null;

		try {
			userIdMapper = (UserIdMapperImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = userIdMapper.getPrimaryKey();

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

	private long _userIdMapperId;
	private long _userId;
	private String _type;
	private String _description;
	private String _externalUserId;
}
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

package com.liferay.portlet.messageboards.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.messageboards.model.MBMessageFlag;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="MBMessageFlagModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>MBMessageFlag</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.model.MBMessageFlag
 * @see com.liferay.portlet.messageboards.service.model.MBMessageFlagModel
 * @see com.liferay.portlet.messageboards.service.model.impl.MBMessageFlagImpl
 *
 */
public class MBMessageFlagModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "MBMessageFlag";
	public static final Object[][] TABLE_COLUMNS = {
			{ "messageFlagId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "messageId", new Integer(Types.BIGINT) },
			

			{ "flag", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table MBMessageFlag (messageFlagId LONG not null primary key,userId LONG,messageId LONG,flag INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table MBMessageFlag";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.messageboards.model.MBMessageFlag"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBMessageFlag"));

	public MBMessageFlagModelImpl() {
	}

	public long getPrimaryKey() {
		return _messageFlagId;
	}

	public void setPrimaryKey(long pk) {
		setMessageFlagId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_messageFlagId);
	}

	public long getMessageFlagId() {
		return _messageFlagId;
	}

	public void setMessageFlagId(long messageFlagId) {
		if (messageFlagId != _messageFlagId) {
			_messageFlagId = messageFlagId;
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

	public long getMessageId() {
		return _messageId;
	}

	public void setMessageId(long messageId) {
		if (messageId != _messageId) {
			_messageId = messageId;
		}
	}

	public int getFlag() {
		return _flag;
	}

	public void setFlag(int flag) {
		if (flag != _flag) {
			_flag = flag;
		}
	}

	public MBMessageFlag toEscapedModel() {
		if (isEscapedModel()) {
			return (MBMessageFlag)this;
		}
		else {
			MBMessageFlag model = new MBMessageFlagImpl();

			model.setEscapedModel(true);

			model.setMessageFlagId(getMessageFlagId());
			model.setUserId(getUserId());
			model.setMessageId(getMessageId());
			model.setFlag(getFlag());

			model = (MBMessageFlag)Proxy.newProxyInstance(MBMessageFlag.class.getClassLoader(),
					new Class[] { MBMessageFlag.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		MBMessageFlagImpl clone = new MBMessageFlagImpl();

		clone.setMessageFlagId(getMessageFlagId());
		clone.setUserId(getUserId());
		clone.setMessageId(getMessageId());
		clone.setFlag(getFlag());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBMessageFlagImpl mbMessageFlag = (MBMessageFlagImpl)obj;

		long pk = mbMessageFlag.getPrimaryKey();

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

		MBMessageFlagImpl mbMessageFlag = null;

		try {
			mbMessageFlag = (MBMessageFlagImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = mbMessageFlag.getPrimaryKey();

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

	private long _messageFlagId;
	private long _userId;
	private long _messageId;
	private int _flag;
}
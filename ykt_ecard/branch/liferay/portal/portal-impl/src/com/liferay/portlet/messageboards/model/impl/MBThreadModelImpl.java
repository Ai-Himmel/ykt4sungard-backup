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
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.messageboards.model.MBThread;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="MBThreadModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>MBThread</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.model.MBThread
 * @see com.liferay.portlet.messageboards.service.model.MBThreadModel
 * @see com.liferay.portlet.messageboards.service.model.impl.MBThreadImpl
 *
 */
public class MBThreadModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "MBThread";
	public static final Object[][] TABLE_COLUMNS = {
			{ "threadId", new Integer(Types.BIGINT) },
			

			{ "categoryId", new Integer(Types.BIGINT) },
			

			{ "rootMessageId", new Integer(Types.BIGINT) },
			

			{ "messageCount", new Integer(Types.INTEGER) },
			

			{ "viewCount", new Integer(Types.INTEGER) },
			

			{ "lastPostByUserId", new Integer(Types.BIGINT) },
			

			{ "lastPostDate", new Integer(Types.TIMESTAMP) },
			

			{ "priority", new Integer(Types.DOUBLE) }
		};
	public static final String TABLE_SQL_CREATE = "create table MBThread (threadId LONG not null primary key,categoryId LONG,rootMessageId LONG,messageCount INTEGER,viewCount INTEGER,lastPostByUserId LONG,lastPostDate DATE null,priority DOUBLE)";
	public static final String TABLE_SQL_DROP = "drop table MBThread";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.messageboards.model.MBThread"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBThread"));

	public MBThreadModelImpl() {
	}

	public long getPrimaryKey() {
		return _threadId;
	}

	public void setPrimaryKey(long pk) {
		setThreadId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_threadId);
	}

	public long getThreadId() {
		return _threadId;
	}

	public void setThreadId(long threadId) {
		if (threadId != _threadId) {
			_threadId = threadId;
		}
	}

	public long getCategoryId() {
		return _categoryId;
	}

	public void setCategoryId(long categoryId) {
		if (categoryId != _categoryId) {
			_categoryId = categoryId;
		}
	}

	public long getRootMessageId() {
		return _rootMessageId;
	}

	public void setRootMessageId(long rootMessageId) {
		if (rootMessageId != _rootMessageId) {
			_rootMessageId = rootMessageId;
		}
	}

	public int getMessageCount() {
		return _messageCount;
	}

	public void setMessageCount(int messageCount) {
		if (messageCount != _messageCount) {
			_messageCount = messageCount;
		}
	}

	public int getViewCount() {
		return _viewCount;
	}

	public void setViewCount(int viewCount) {
		if (viewCount != _viewCount) {
			_viewCount = viewCount;
		}
	}

	public long getLastPostByUserId() {
		return _lastPostByUserId;
	}

	public void setLastPostByUserId(long lastPostByUserId) {
		if (lastPostByUserId != _lastPostByUserId) {
			_lastPostByUserId = lastPostByUserId;
		}
	}

	public Date getLastPostDate() {
		return _lastPostDate;
	}

	public void setLastPostDate(Date lastPostDate) {
		if (((lastPostDate == null) && (_lastPostDate != null)) ||
				((lastPostDate != null) && (_lastPostDate == null)) ||
				((lastPostDate != null) && (_lastPostDate != null) &&
				!lastPostDate.equals(_lastPostDate))) {
			_lastPostDate = lastPostDate;
		}
	}

	public double getPriority() {
		return _priority;
	}

	public void setPriority(double priority) {
		if (priority != _priority) {
			_priority = priority;
		}
	}

	public MBThread toEscapedModel() {
		if (isEscapedModel()) {
			return (MBThread)this;
		}
		else {
			MBThread model = new MBThreadImpl();

			model.setEscapedModel(true);

			model.setThreadId(getThreadId());
			model.setCategoryId(getCategoryId());
			model.setRootMessageId(getRootMessageId());
			model.setMessageCount(getMessageCount());
			model.setViewCount(getViewCount());
			model.setLastPostByUserId(getLastPostByUserId());
			model.setLastPostDate(getLastPostDate());
			model.setPriority(getPriority());

			model = (MBThread)Proxy.newProxyInstance(MBThread.class.getClassLoader(),
					new Class[] { MBThread.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		MBThreadImpl clone = new MBThreadImpl();

		clone.setThreadId(getThreadId());
		clone.setCategoryId(getCategoryId());
		clone.setRootMessageId(getRootMessageId());
		clone.setMessageCount(getMessageCount());
		clone.setViewCount(getViewCount());
		clone.setLastPostByUserId(getLastPostByUserId());
		clone.setLastPostDate(getLastPostDate());
		clone.setPriority(getPriority());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBThreadImpl mbThread = (MBThreadImpl)obj;

		int value = 0;

		if (getPriority() < mbThread.getPriority()) {
			value = -1;
		}
		else if (getPriority() > mbThread.getPriority()) {
			value = 1;
		}
		else {
			value = 0;
		}

		value = value * -1;

		if (value != 0) {
			return value;
		}

		value = DateUtil.compareTo(getLastPostDate(), mbThread.getLastPostDate());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		MBThreadImpl mbThread = null;

		try {
			mbThread = (MBThreadImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = mbThread.getPrimaryKey();

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

	private long _threadId;
	private long _categoryId;
	private long _rootMessageId;
	private int _messageCount;
	private int _viewCount;
	private long _lastPostByUserId;
	private Date _lastPostDate;
	private double _priority;
}
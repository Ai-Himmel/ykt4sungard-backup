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

import com.liferay.portlet.messageboards.model.MBDiscussion;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="MBDiscussionModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>MBDiscussion</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.model.MBDiscussion
 * @see com.liferay.portlet.messageboards.service.model.MBDiscussionModel
 * @see com.liferay.portlet.messageboards.service.model.impl.MBDiscussionImpl
 *
 */
public class MBDiscussionModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "MBDiscussion";
	public static final Object[][] TABLE_COLUMNS = {
			{ "discussionId", new Integer(Types.BIGINT) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "threadId", new Integer(Types.BIGINT) }
		};
	public static final String TABLE_SQL_CREATE = "create table MBDiscussion (discussionId LONG not null primary key,classNameId LONG,classPK LONG,threadId LONG)";
	public static final String TABLE_SQL_DROP = "drop table MBDiscussion";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.messageboards.model.MBDiscussion"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBDiscussion"));

	public MBDiscussionModelImpl() {
	}

	public long getPrimaryKey() {
		return _discussionId;
	}

	public void setPrimaryKey(long pk) {
		setDiscussionId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_discussionId);
	}

	public long getDiscussionId() {
		return _discussionId;
	}

	public void setDiscussionId(long discussionId) {
		if (discussionId != _discussionId) {
			_discussionId = discussionId;
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

	public long getThreadId() {
		return _threadId;
	}

	public void setThreadId(long threadId) {
		if (threadId != _threadId) {
			_threadId = threadId;
		}
	}

	public MBDiscussion toEscapedModel() {
		if (isEscapedModel()) {
			return (MBDiscussion)this;
		}
		else {
			MBDiscussion model = new MBDiscussionImpl();

			model.setEscapedModel(true);

			model.setDiscussionId(getDiscussionId());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setThreadId(getThreadId());

			model = (MBDiscussion)Proxy.newProxyInstance(MBDiscussion.class.getClassLoader(),
					new Class[] { MBDiscussion.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		MBDiscussionImpl clone = new MBDiscussionImpl();

		clone.setDiscussionId(getDiscussionId());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setThreadId(getThreadId());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBDiscussionImpl mbDiscussion = (MBDiscussionImpl)obj;

		long pk = mbDiscussion.getPrimaryKey();

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

		MBDiscussionImpl mbDiscussion = null;

		try {
			mbDiscussion = (MBDiscussionImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = mbDiscussion.getPrimaryKey();

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

	private long _discussionId;
	private long _classNameId;
	private long _classPK;
	private long _threadId;
}
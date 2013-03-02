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

import com.liferay.portlet.messageboards.model.MBMessage;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="MBMessageModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>MBMessage</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.model.MBMessage
 * @see com.liferay.portlet.messageboards.service.model.MBMessageModel
 * @see com.liferay.portlet.messageboards.service.model.impl.MBMessageImpl
 *
 */
public class MBMessageModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "MBMessage";
	public static final Object[][] TABLE_COLUMNS = {
			{ "uuid_", new Integer(Types.VARCHAR) },
			

			{ "messageId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "categoryId", new Integer(Types.BIGINT) },
			

			{ "threadId", new Integer(Types.BIGINT) },
			

			{ "parentMessageId", new Integer(Types.BIGINT) },
			

			{ "subject", new Integer(Types.VARCHAR) },
			

			{ "body", new Integer(Types.CLOB) },
			

			{ "attachments", new Integer(Types.BOOLEAN) },
			

			{ "anonymous", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table MBMessage (uuid_ VARCHAR(75) null,messageId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,categoryId LONG,threadId LONG,parentMessageId LONG,subject VARCHAR(75) null,body TEXT null,attachments BOOLEAN,anonymous BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table MBMessage";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.messageboards.model.MBMessage"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBMessage"));

	public MBMessageModelImpl() {
	}

	public long getPrimaryKey() {
		return _messageId;
	}

	public void setPrimaryKey(long pk) {
		setMessageId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_messageId);
	}

	public String getUuid() {
		return GetterUtil.getString(_uuid);
	}

	public void setUuid(String uuid) {
		if ((uuid != null) && (uuid != _uuid)) {
			_uuid = uuid;
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

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
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

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
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

	public long getThreadId() {
		return _threadId;
	}

	public void setThreadId(long threadId) {
		if (threadId != _threadId) {
			_threadId = threadId;
		}
	}

	public long getParentMessageId() {
		return _parentMessageId;
	}

	public void setParentMessageId(long parentMessageId) {
		if (parentMessageId != _parentMessageId) {
			_parentMessageId = parentMessageId;
		}
	}

	public String getSubject() {
		return GetterUtil.getString(_subject);
	}

	public void setSubject(String subject) {
		if (((subject == null) && (_subject != null)) ||
				((subject != null) && (_subject == null)) ||
				((subject != null) && (_subject != null) &&
				!subject.equals(_subject))) {
			_subject = subject;
		}
	}

	public String getBody() {
		return GetterUtil.getString(_body);
	}

	public void setBody(String body) {
		if (((body == null) && (_body != null)) ||
				((body != null) && (_body == null)) ||
				((body != null) && (_body != null) && !body.equals(_body))) {
			_body = body;
		}
	}

	public boolean getAttachments() {
		return _attachments;
	}

	public boolean isAttachments() {
		return _attachments;
	}

	public void setAttachments(boolean attachments) {
		if (attachments != _attachments) {
			_attachments = attachments;
		}
	}

	public boolean getAnonymous() {
		return _anonymous;
	}

	public boolean isAnonymous() {
		return _anonymous;
	}

	public void setAnonymous(boolean anonymous) {
		if (anonymous != _anonymous) {
			_anonymous = anonymous;
		}
	}

	public MBMessage toEscapedModel() {
		if (isEscapedModel()) {
			return (MBMessage)this;
		}
		else {
			MBMessage model = new MBMessageImpl();

			model.setEscapedModel(true);

			model.setUuid(Html.escape(getUuid()));
			model.setMessageId(getMessageId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setCategoryId(getCategoryId());
			model.setThreadId(getThreadId());
			model.setParentMessageId(getParentMessageId());
			model.setSubject(Html.escape(getSubject()));
			model.setBody(Html.escape(getBody()));
			model.setAttachments(getAttachments());
			model.setAnonymous(getAnonymous());

			model = (MBMessage)Proxy.newProxyInstance(MBMessage.class.getClassLoader(),
					new Class[] { MBMessage.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		MBMessageImpl clone = new MBMessageImpl();

		clone.setUuid(getUuid());
		clone.setMessageId(getMessageId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setCategoryId(getCategoryId());
		clone.setThreadId(getThreadId());
		clone.setParentMessageId(getParentMessageId());
		clone.setSubject(getSubject());
		clone.setBody(getBody());
		clone.setAttachments(getAttachments());
		clone.setAnonymous(getAnonymous());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBMessageImpl mbMessage = (MBMessageImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(), mbMessage.getCreateDate());

		if (value != 0) {
			return value;
		}

		if (getMessageId() < mbMessage.getMessageId()) {
			value = -1;
		}
		else if (getMessageId() > mbMessage.getMessageId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		MBMessageImpl mbMessage = null;

		try {
			mbMessage = (MBMessageImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = mbMessage.getPrimaryKey();

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

	private String _uuid;
	private long _messageId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _categoryId;
	private long _threadId;
	private long _parentMessageId;
	private String _subject;
	private String _body;
	private boolean _attachments;
	private boolean _anonymous;
}
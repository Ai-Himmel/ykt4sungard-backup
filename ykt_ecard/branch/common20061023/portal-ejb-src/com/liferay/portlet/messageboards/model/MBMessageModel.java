/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.messageboards.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.messageboards.service.persistence.MBMessagePK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="MBMessageModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.80 $
 *
 */
public class MBMessageModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.messageboards.model.MBMessage"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.messageboards.model.MBMessage"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_MESSAGEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.messageId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TOPICID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.topicId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_THREADID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.threadId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PARENTMESSAGEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.parentMessageId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SUBJECT = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.subject"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BODY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessage.body"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBMessageModel"));

	public MBMessageModel() {
	}

	public MBMessageModel(MBMessagePK pk) {
		_messageId = pk.messageId;
		_topicId = pk.topicId;
		setNew(true);
	}

	public MBMessageModel(String messageId, String topicId, String companyId,
		String userId, String userName, Date createDate, Date modifiedDate,
		String threadId, String parentMessageId, String subject, String body,
		boolean attachments, boolean anonymous) {
		_messageId = messageId;
		_topicId = topicId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_threadId = threadId;
		_parentMessageId = parentMessageId;
		_subject = subject;
		_body = body;
		_attachments = attachments;
		_anonymous = anonymous;
	}

	public MBMessagePK getPrimaryKey() {
		return new MBMessagePK(_messageId, _topicId);
	}

	public String getMessageId() {
		return _messageId;
	}

	public void setMessageId(String messageId) {
		if (((messageId == null) && (_messageId != null)) ||
				((messageId != null) && (_messageId == null)) ||
				((messageId != null) && (_messageId != null) &&
				!messageId.equals(_messageId))) {
			if (!XSS_ALLOW_MESSAGEID) {
				messageId = Xss.strip(messageId);
			}

			_messageId = messageId;
			setModified(true);
		}
	}

	public String getTopicId() {
		return _topicId;
	}

	public void setTopicId(String topicId) {
		if (((topicId == null) && (_topicId != null)) ||
				((topicId != null) && (_topicId == null)) ||
				((topicId != null) && (_topicId != null) &&
				!topicId.equals(_topicId))) {
			if (!XSS_ALLOW_TOPICID) {
				topicId = Xss.strip(topicId);
			}

			_topicId = topicId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
		}
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			if (!XSS_ALLOW_USERNAME) {
				userName = Xss.strip(userName);
			}

			_userName = userName;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public String getThreadId() {
		return _threadId;
	}

	public void setThreadId(String threadId) {
		if (((threadId == null) && (_threadId != null)) ||
				((threadId != null) && (_threadId == null)) ||
				((threadId != null) && (_threadId != null) &&
				!threadId.equals(_threadId))) {
			if (!XSS_ALLOW_THREADID) {
				threadId = Xss.strip(threadId);
			}

			_threadId = threadId;
			setModified(true);
		}
	}

	public String getParentMessageId() {
		return _parentMessageId;
	}

	public void setParentMessageId(String parentMessageId) {
		if (((parentMessageId == null) && (_parentMessageId != null)) ||
				((parentMessageId != null) && (_parentMessageId == null)) ||
				((parentMessageId != null) && (_parentMessageId != null) &&
				!parentMessageId.equals(_parentMessageId))) {
			if (!XSS_ALLOW_PARENTMESSAGEID) {
				parentMessageId = Xss.strip(parentMessageId);
			}

			_parentMessageId = parentMessageId;
			setModified(true);
		}
	}

	public String getSubject() {
		return _subject;
	}

	public void setSubject(String subject) {
		if (((subject == null) && (_subject != null)) ||
				((subject != null) && (_subject == null)) ||
				((subject != null) && (_subject != null) &&
				!subject.equals(_subject))) {
			if (!XSS_ALLOW_SUBJECT) {
				subject = Xss.strip(subject);
			}

			_subject = subject;
			setModified(true);
		}
	}

	public String getBody() {
		return _body;
	}

	public void setBody(String body) {
		if (((body == null) && (_body != null)) ||
				((body != null) && (_body == null)) ||
				((body != null) && (_body != null) && !body.equals(_body))) {
			if (!XSS_ALLOW_BODY) {
				body = Xss.strip(body);
			}

			_body = body;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new MBMessage(getMessageId(), getTopicId(), getCompanyId(),
			getUserId(), getUserName(), getCreateDate(), getModifiedDate(),
			getThreadId(), getParentMessageId(), getSubject(), getBody(),
			getAttachments(), getAnonymous());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBMessage mbMessage = (MBMessage)obj;
		int value = 0;
		value = getCreateDate().compareTo(mbMessage.getCreateDate());

		if (value != 0) {
			return value;
		}

		value = getMessageId().compareTo(mbMessage.getMessageId());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		MBMessage mbMessage = null;

		try {
			mbMessage = (MBMessage)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		MBMessagePK pk = mbMessage.getPrimaryKey();

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

	private String _messageId;
	private String _topicId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _threadId;
	private String _parentMessageId;
	private String _subject;
	private String _body;
	private boolean _attachments;
	private boolean _anonymous;
}
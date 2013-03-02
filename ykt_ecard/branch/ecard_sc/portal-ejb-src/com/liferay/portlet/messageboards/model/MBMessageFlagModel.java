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

import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

/**
 * <a href="MBMessageFlagModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class MBMessageFlagModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.messageboards.model.MBMessageFlag"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.messageboards.model.MBMessageFlag"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessageFlag"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_TOPICID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessageFlag.topicId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_MESSAGEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessageFlag.messageId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessageFlag.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FLAG = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBMessageFlag.flag"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBMessageFlagModel"));

	public MBMessageFlagModel() {
	}

	public MBMessageFlagModel(MBMessageFlagPK pk) {
		_topicId = pk.topicId;
		_messageId = pk.messageId;
		_userId = pk.userId;
		setNew(true);
	}

	public MBMessageFlagModel(String topicId, String messageId, String userId,
		String flag) {
		_topicId = topicId;
		_messageId = messageId;
		_userId = userId;
		_flag = flag;
	}

	public MBMessageFlagPK getPrimaryKey() {
		return new MBMessageFlagPK(_topicId, _messageId, _userId);
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

	public String getFlag() {
		return _flag;
	}

	public void setFlag(String flag) {
		if (((flag == null) && (_flag != null)) ||
				((flag != null) && (_flag == null)) ||
				((flag != null) && (_flag != null) && !flag.equals(_flag))) {
			if (!XSS_ALLOW_FLAG) {
				flag = Xss.strip(flag);
			}

			_flag = flag;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new MBMessageFlag(getTopicId(), getMessageId(), getUserId(),
			getFlag());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBMessageFlag mbMessageFlag = (MBMessageFlag)obj;
		MBMessageFlagPK pk = mbMessageFlag.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		MBMessageFlag mbMessageFlag = null;

		try {
			mbMessageFlag = (MBMessageFlag)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		MBMessageFlagPK pk = mbMessageFlag.getPrimaryKey();

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

	private String _topicId;
	private String _messageId;
	private String _userId;
	private String _flag;
}
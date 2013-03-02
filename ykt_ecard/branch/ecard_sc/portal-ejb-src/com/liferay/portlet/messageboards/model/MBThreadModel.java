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

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="MBThreadModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.79 $
 *
 */
public class MBThreadModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.messageboards.model.MBThread"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.messageboards.model.MBThread"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBThread"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_THREADID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBThread.threadId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ROOTMESSAGEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBThread.rootMessageId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TOPICID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.messageboards.model.MBThread.topicId"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.messageboards.model.MBThreadModel"));

	public MBThreadModel() {
	}

	public MBThreadModel(String threadId) {
		_threadId = threadId;
		setNew(true);
	}

	public MBThreadModel(String threadId, String rootMessageId, String topicId,
		int messageCount, Date lastPostDate) {
		_threadId = threadId;
		_rootMessageId = rootMessageId;
		_topicId = topicId;
		_messageCount = messageCount;
		_lastPostDate = lastPostDate;
	}

	public String getPrimaryKey() {
		return _threadId;
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

	public String getRootMessageId() {
		return _rootMessageId;
	}

	public void setRootMessageId(String rootMessageId) {
		if (((rootMessageId == null) && (_rootMessageId != null)) ||
				((rootMessageId != null) && (_rootMessageId == null)) ||
				((rootMessageId != null) && (_rootMessageId != null) &&
				!rootMessageId.equals(_rootMessageId))) {
			if (!XSS_ALLOW_ROOTMESSAGEID) {
				rootMessageId = Xss.strip(rootMessageId);
			}

			_rootMessageId = rootMessageId;
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

	public int getMessageCount() {
		return _messageCount;
	}

	public void setMessageCount(int messageCount) {
		if (messageCount != _messageCount) {
			_messageCount = messageCount;
			setModified(true);
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
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new MBThread(getThreadId(), getRootMessageId(), getTopicId(),
			getMessageCount(), getLastPostDate());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBThread mbThread = (MBThread)obj;
		int value = 0;
		value = getLastPostDate().compareTo(mbThread.getLastPostDate());
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

		MBThread mbThread = null;

		try {
			mbThread = (MBThread)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = mbThread.getPrimaryKey();

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

	private String _threadId;
	private String _rootMessageId;
	private String _topicId;
	private int _messageCount;
	private Date _lastPostDate;
}
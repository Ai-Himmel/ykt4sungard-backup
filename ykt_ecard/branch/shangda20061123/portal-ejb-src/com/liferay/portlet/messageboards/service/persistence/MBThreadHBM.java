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

package com.liferay.portlet.messageboards.service.persistence;

import java.util.Date;

/**
 * <a href="MBThreadHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBThreadHBM {
	protected MBThreadHBM() {
	}

	protected MBThreadHBM(String threadId) {
		_threadId = threadId;
	}

	protected MBThreadHBM(String threadId, String rootMessageId,
		String topicId, int messageCount, Date lastPostDate) {
		_threadId = threadId;
		_rootMessageId = rootMessageId;
		_topicId = topicId;
		_messageCount = messageCount;
		_lastPostDate = lastPostDate;
	}

	public String getPrimaryKey() {
		return _threadId;
	}

	protected void setPrimaryKey(String pk) {
		_threadId = pk;
	}

	protected String getThreadId() {
		return _threadId;
	}

	protected void setThreadId(String threadId) {
		_threadId = threadId;
	}

	protected String getRootMessageId() {
		return _rootMessageId;
	}

	protected void setRootMessageId(String rootMessageId) {
		_rootMessageId = rootMessageId;
	}

	protected String getTopicId() {
		return _topicId;
	}

	protected void setTopicId(String topicId) {
		_topicId = topicId;
	}

	protected int getMessageCount() {
		return _messageCount;
	}

	protected void setMessageCount(int messageCount) {
		_messageCount = messageCount;
	}

	protected Date getLastPostDate() {
		return _lastPostDate;
	}

	protected void setLastPostDate(Date lastPostDate) {
		_lastPostDate = lastPostDate;
	}

	private String _threadId;
	private String _rootMessageId;
	private String _topicId;
	private int _messageCount;
	private Date _lastPostDate;
}
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

/**
 * <a href="MBMessageFlagHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessageFlagHBM {
	protected MBMessageFlagHBM() {
	}

	protected MBMessageFlagHBM(MBMessageFlagPK pk) {
		_topicId = pk.topicId;
		_messageId = pk.messageId;
		_userId = pk.userId;
	}

	protected MBMessageFlagHBM(String topicId, String messageId, String userId,
		String flag) {
		_topicId = topicId;
		_messageId = messageId;
		_userId = userId;
		_flag = flag;
	}

	public MBMessageFlagPK getPrimaryKey() {
		return new MBMessageFlagPK(_topicId, _messageId, _userId);
	}

	protected void setPrimaryKey(MBMessageFlagPK pk) {
		_topicId = pk.topicId;
		_messageId = pk.messageId;
		_userId = pk.userId;
	}

	protected String getTopicId() {
		return _topicId;
	}

	protected void setTopicId(String topicId) {
		_topicId = topicId;
	}

	protected String getMessageId() {
		return _messageId;
	}

	protected void setMessageId(String messageId) {
		_messageId = messageId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getFlag() {
		return _flag;
	}

	protected void setFlag(String flag) {
		_flag = flag;
	}

	private String _topicId;
	private String _messageId;
	private String _userId;
	private String _flag;
}
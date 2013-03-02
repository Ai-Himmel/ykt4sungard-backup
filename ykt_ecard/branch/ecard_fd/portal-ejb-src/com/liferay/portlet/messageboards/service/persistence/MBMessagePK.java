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

import com.liferay.util.StringPool;
import com.liferay.util.lang.FastStringBuffer;

import java.io.Serializable;

/**
 * <a href="MBMessagePK.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessagePK implements Comparable, Serializable {
	public String messageId;
	public String topicId;

	public MBMessagePK() {
	}

	public MBMessagePK(String messageId, String topicId) {
		this.messageId = messageId;
		this.topicId = topicId;
	}

	public String getMessageId() {
		return messageId;
	}

	public void setMessageId(String messageId) {
		this.messageId = messageId;
	}

	public String getTopicId() {
		return topicId;
	}

	public void setTopicId(String topicId) {
		this.topicId = topicId;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		MBMessagePK pk = (MBMessagePK)obj;
		int value = 0;
		value = messageId.compareTo(pk.messageId);

		if (value != 0) {
			return value;
		}

		value = topicId.compareTo(pk.topicId);

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		MBMessagePK pk = null;

		try {
			pk = (MBMessagePK)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		if ((messageId.equals(pk.messageId)) && (topicId.equals(pk.topicId))) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (messageId + topicId).hashCode();
	}

	public String toString() {
		FastStringBuffer sb = new FastStringBuffer();
		sb.append(StringPool.OPEN_CURLY_BRACE);
		sb.append("messageId");
		sb.append(StringPool.EQUAL);
		sb.append(messageId);
		sb.append(StringPool.COMMA);
		sb.append(StringPool.SPACE);
		sb.append("topicId");
		sb.append(StringPool.EQUAL);
		sb.append(topicId);
		sb.append(StringPool.CLOSE_CURLY_BRACE);

		return sb.toString();
	}
}
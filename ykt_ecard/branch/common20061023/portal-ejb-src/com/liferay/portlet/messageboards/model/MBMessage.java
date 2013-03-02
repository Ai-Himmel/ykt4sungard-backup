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

import com.liferay.portlet.messageboards.service.persistence.MBMessagePK;

import java.util.Date;

/**
 * <a href="MBMessage.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class MBMessage extends MBMessageModel {

	public static final String DEFAULT_PARENT_MESSAGE_ID = "-1";

	public MBMessage() {
		super();
	}

	public MBMessage(MBMessagePK pk) {
		super(pk);
	}

	public MBMessage(String messageId, String topicId, String companyId,
					 String userId, String userName, Date createDate,
					 Date modifiedDate, String threadId, String parentMessageId,
					 String subject, String body, boolean attachments,
					 boolean anonymous) {

		super(messageId, topicId, companyId, userId, userName, createDate,
			  modifiedDate, threadId, parentMessageId, subject, body,
			  attachments, anonymous);
	}

	public boolean isReply() {
		return !isRoot();
	}

	public boolean isRoot() {
		String parentMessageId = getParentMessageId();

		if ((parentMessageId != null) &&
			(parentMessageId.equals(DEFAULT_PARENT_MESSAGE_ID))) {

			return true;
		}
		else {
			return false;
		}
	}

	public String getAttachmentsDir() {
		return "/messageboards/" + getTopicId() + "/" + getMessageId();
	}

}
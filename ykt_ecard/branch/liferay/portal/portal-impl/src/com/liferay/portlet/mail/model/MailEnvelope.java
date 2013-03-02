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

package com.liferay.portlet.mail.model;

import java.util.Date;

/**
 * <a href="MailEnvelope.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class MailEnvelope {

	public long getMessageId() {
		return _messageId;
	}

	public void setMessageId(long messageId) {
		_messageId = messageId;
	}

	public String getFolderName() {
		return _folderName;
	}

	public void setFolderName(String folderName) {
		_folderName = folderName;
	}

	public String getRecipient() {
		return _recipient;
	}

	public void setRecipient(String recipient) {
		_recipient = recipient;
	}

	public String getSubject() {
		return _subject;
	}

	public void setSubject(String subject) {
		_subject = subject;
	}

	public Date getDate() {
		return _date;
	}

	public void setDate(Date date) {
		_date = date;
	}

	public int getSize() {
		return _size;
	}

	public void setSize(int size) {
		_size = size;
	}

	public boolean isRead() {
		return _read;
	}

	public void setRead(boolean read) {
		_read = read;
	}

	public boolean isFlagged() {
		return _flagged;
	}

	public void setFlagged(boolean flagged) {
		_flagged = flagged;
	}

	public boolean isAnswered() {
		return _answered;
	}

	public void setAnswered(boolean answered) {
		_answered = answered;
	}

	private long _messageId;
	private String _folderName;
	private String _recipient;
	private String _subject;
	private Date _date;
	private int _size;
	private boolean _read;
	private boolean _flagged;
	private boolean _answered;

}
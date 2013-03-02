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

package com.liferay.portlet.mail.service.persistence;

import java.util.Date;

/**
 * <a href="MailReceiptHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MailReceiptHBM {
	protected MailReceiptHBM() {
	}

	protected MailReceiptHBM(String receiptId) {
		_receiptId = receiptId;
	}

	protected MailReceiptHBM(String receiptId, String companyId, String userId,
		Date createDate, Date modifiedDate, String recipientName,
		String recipientAddress, String subject, Date sentDate, int readCount,
		Date firstReadDate, Date lastReadDate) {
		_receiptId = receiptId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_recipientName = recipientName;
		_recipientAddress = recipientAddress;
		_subject = subject;
		_sentDate = sentDate;
		_readCount = readCount;
		_firstReadDate = firstReadDate;
		_lastReadDate = lastReadDate;
	}

	public String getPrimaryKey() {
		return _receiptId;
	}

	protected void setPrimaryKey(String pk) {
		_receiptId = pk;
	}

	protected String getReceiptId() {
		return _receiptId;
	}

	protected void setReceiptId(String receiptId) {
		_receiptId = receiptId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getRecipientName() {
		return _recipientName;
	}

	protected void setRecipientName(String recipientName) {
		_recipientName = recipientName;
	}

	protected String getRecipientAddress() {
		return _recipientAddress;
	}

	protected void setRecipientAddress(String recipientAddress) {
		_recipientAddress = recipientAddress;
	}

	protected String getSubject() {
		return _subject;
	}

	protected void setSubject(String subject) {
		_subject = subject;
	}

	protected Date getSentDate() {
		return _sentDate;
	}

	protected void setSentDate(Date sentDate) {
		_sentDate = sentDate;
	}

	protected int getReadCount() {
		return _readCount;
	}

	protected void setReadCount(int readCount) {
		_readCount = readCount;
	}

	protected Date getFirstReadDate() {
		return _firstReadDate;
	}

	protected void setFirstReadDate(Date firstReadDate) {
		_firstReadDate = firstReadDate;
	}

	protected Date getLastReadDate() {
		return _lastReadDate;
	}

	protected void setLastReadDate(Date lastReadDate) {
		_lastReadDate = lastReadDate;
	}

	private String _receiptId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _recipientName;
	private String _recipientAddress;
	private String _subject;
	private Date _sentDate;
	private int _readCount;
	private Date _firstReadDate;
	private Date _lastReadDate;
}
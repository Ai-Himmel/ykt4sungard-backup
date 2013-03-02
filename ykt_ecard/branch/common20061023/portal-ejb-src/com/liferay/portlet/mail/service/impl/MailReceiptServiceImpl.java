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

package com.liferay.portlet.mail.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.mail.NoSuchReceiptException;
import com.liferay.portlet.mail.ReceiptRecipientException;
import com.liferay.portlet.mail.ReceiptSentDateException;
import com.liferay.portlet.mail.ReceiptSubjectException;
import com.liferay.portlet.mail.model.MailReceipt;
import com.liferay.portlet.mail.service.persistence.MailReceiptUtil;
import com.liferay.portlet.mail.service.spring.MailReceiptService;
import com.liferay.util.PwdGenerator;
import com.liferay.util.Time;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;

import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;

/**
 * <a href="MailReceiptServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MailReceiptServiceImpl
	extends PrincipalBean implements MailReceiptService {

	// Business methods

	public MailReceipt addReceipt(
			String recipientName, String recipientAddress, String subject,
			Date sentDate)
		throws PortalException, SystemException {

		_validate(recipientName, recipientAddress, subject, sentDate);

		User user = getUser();

		String receiptId = _getReceiptId();

		MailReceipt receipt = MailReceiptUtil.create(receiptId);

		Date now = new Date();

		receipt.setCompanyId(user.getCompanyId());
		receipt.setUserId(user.getUserId());
		receipt.setCreateDate(now);
		receipt.setModifiedDate(now);
		receipt.setRecipientName(recipientName);
		receipt.setRecipientAddress(recipientAddress);
		receipt.setSubject(subject);
		receipt.setSentDate(sentDate);
		receipt.setReadCount(0);

		MailReceiptUtil.update(receipt);

		return receipt;
	}

	public void checkReceipts() throws PortalException, SystemException {
		List receipts = MailReceiptUtil.findAll();

		Date now = new Date();

		for (int i = 0; i < receipts.size(); i++) {
			MailReceipt receipt = (MailReceipt)receipts.get(i);

			long diff =
				(now.getTime() - receipt.getCreateDate().getTime()) /
					Time.DAY;

			// Delete receipts that are older than 60 days

			if (diff > 60) {
				MailReceiptUtil.remove(receipt.getPrimaryKey());
			}
		}
	}

	// Private methods

	private String _getReceiptId() throws SystemException {
		String receiptId =
			PwdGenerator.getPassword(PwdGenerator.KEY1 + PwdGenerator.KEY2, 6);

		try {
			MailReceiptUtil.findByPrimaryKey(receiptId);

			return _getReceiptId();
		}
		catch (NoSuchReceiptException nsre) {
			return receiptId;
		}
	}

	private void _validate(
			String recipientName, String recipientAddress, String subject,
			Date sendDate)
		throws PortalException {

		if (Validator.isNull(recipientName)) {
			try {
				InternetAddress.parse(recipientAddress);
			}
			catch (AddressException ae) {
				throw new ReceiptRecipientException();
			}
		}
		else {
			try {
				InternetAddress.parse(
					recipientName + "<" + recipientAddress + ">");
			}
			catch (AddressException ae) {
				throw new ReceiptRecipientException();
			}
		}

		if (Validator.isNull(subject)) {
			throw new ReceiptSubjectException();
		}

		if (sendDate == null) {
			throw new ReceiptSentDateException();
		}
	}

}
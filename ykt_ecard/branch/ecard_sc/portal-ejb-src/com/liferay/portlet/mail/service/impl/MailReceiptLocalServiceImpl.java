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

import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portlet.mail.model.MailReceipt;
import com.liferay.portlet.mail.service.persistence.MailReceiptUtil;
import com.liferay.portlet.mail.service.spring.MailReceiptLocalService;
import com.liferay.util.StringUtil;
import com.liferay.util.mail.MailMessage;

import java.io.IOException;

import java.text.DateFormat;

import java.util.Date;

import javax.mail.internet.InternetAddress;

/**
 * <a href="MailReceiptLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MailReceiptLocalServiceImpl implements MailReceiptLocalService {

	// Business methods

	public MailReceipt updateReceipt(String receiptId)
		throws PortalException, SystemException {

		MailReceipt receipt = MailReceiptUtil.findByPrimaryKey(receiptId);

		Date now = new Date();

		int readCount = receipt.getReadCount() + 1;

		Date firstReadDate = receipt.getFirstReadDate();
		if (firstReadDate == null) {
			firstReadDate = now;
		}

		receipt.setModifiedDate(now);
		receipt.setReadCount(readCount);
		receipt.setFirstReadDate(firstReadDate);
		receipt.setLastReadDate(now);

		MailReceiptUtil.update(receipt);

		// Send email

		if (readCount == 1) {
			String subject = "Read: " + receipt.getSubject();

			User user = UserLocalServiceUtil.getUserById(receipt.getUserId());

			DateFormat dateFormat = DateFormat.getDateTimeInstance(
				DateFormat.LONG, DateFormat.LONG, user.getLocale());
			dateFormat.setTimeZone(user.getTimeZone());

			String body = ContentUtil.get(
				"content/en_US/mail_receipt_read.tmpl");
			body = StringUtil.replace(
				body,
				new String[] {"[$RECEIPT_RECIPIENT$]",
							  "[$RECEIPT_SUBJECT$]",
							  "[$RECEIPT_SENT_DATE$]",
							  "[$RECEIPT_READ_DATE$]"},
				new String[] {receipt.getRecipient(),
							  receipt.getSubject(),
							  dateFormat.format(receipt.getSentDate()),
							  dateFormat.format(receipt.getLastReadDate())});

			try {
				InternetAddress from = new InternetAddress(
					user.getEmailAddress(), user.getFullName());

				InternetAddress to = from;

				MailServiceUtil.sendEmail(new MailMessage(
					from, to, subject, body));
			}
			catch (IOException ioe) {
				throw new SystemException(ioe);
			}
		}

		return receipt;
	}

}
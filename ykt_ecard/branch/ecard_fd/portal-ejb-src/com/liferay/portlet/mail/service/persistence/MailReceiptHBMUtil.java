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

/**
 * <a href="MailReceiptHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MailReceiptHBMUtil {
	public static com.liferay.portlet.mail.model.MailReceipt model(
		MailReceiptHBM mailReceiptHBM) {
		com.liferay.portlet.mail.model.MailReceipt mailReceipt = MailReceiptPool.get(mailReceiptHBM.getPrimaryKey());

		if (mailReceipt == null) {
			mailReceipt = new com.liferay.portlet.mail.model.MailReceipt(mailReceiptHBM.getReceiptId(),
					mailReceiptHBM.getCompanyId(), mailReceiptHBM.getUserId(),
					mailReceiptHBM.getCreateDate(),
					mailReceiptHBM.getModifiedDate(),
					mailReceiptHBM.getRecipientName(),
					mailReceiptHBM.getRecipientAddress(),
					mailReceiptHBM.getSubject(), mailReceiptHBM.getSentDate(),
					mailReceiptHBM.getReadCount(),
					mailReceiptHBM.getFirstReadDate(),
					mailReceiptHBM.getLastReadDate());
			MailReceiptPool.put(mailReceipt.getPrimaryKey(), mailReceipt);
		}

		return mailReceipt;
	}
}
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

package com.liferay.portlet.mail.util.comparator;

import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portlet.mail.model.MailEnvelope;

import java.util.Comparator;

/**
 * <a href="SubjectComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class SubjectComparator implements Comparator {

	public SubjectComparator(boolean asc) {
		_asc = asc;
	}

	public int compare(Object obj1, Object obj2) {
		MailEnvelope mailEvenlope1 = (MailEnvelope)obj1;
		MailEnvelope mailEvenlope2 = (MailEnvelope)obj2;

		String subject1 = _getSubject(mailEvenlope1.getSubject());
		String subject2 = _getSubject(mailEvenlope2.getSubject());

		int value = subject1.compareTo(subject2);

		if (value == 0) {
			value = DateUtil.compareTo(
				mailEvenlope1.getDate(), mailEvenlope2.getDate());
		}

		if (value == 0) {
			Long messageId1 = new Long(mailEvenlope1.getMessageId());
			Long messageId2 = new Long(mailEvenlope2.getMessageId());

			value = messageId1.compareTo(messageId2);
		}

		if (_asc) {
			return value;
		}
		else {
			return -value;
		}
	}

	private String _getSubject(String subject) {
		subject = GetterUtil.getString(subject).toLowerCase();

		while (subject.startsWith("re:") || subject.startsWith("re>") ||
			   subject.startsWith("fw:") || subject.startsWith("fw>")) {

			subject = subject.substring(3).trim();
		}

		return subject;
	}

	private boolean _asc;

}
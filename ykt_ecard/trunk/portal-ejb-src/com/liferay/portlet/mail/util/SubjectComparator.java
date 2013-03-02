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

package com.liferay.portlet.mail.util;

import com.liferay.util.Validator;

import java.io.Serializable;

import java.util.Comparator;

import javax.mail.Message;
import javax.mail.MessagingException;

/**
 * <a href="SubjectComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class SubjectComparator implements Comparator, Serializable {

	public SubjectComparator(boolean asc) {
		_asc = asc;
	}

	public int compare(Object obj1, Object obj2) {
		Message msg1 = (Message)obj1;
		Message msg2 = (Message)obj2;

		try {
			String subject1 = msg1.getSubject();
			if (Validator.isNotNull(subject1)) {
				subject1 = subject1.toLowerCase();
			}
			else {
				subject1 = "";
			}

			String subject2 = msg2.getSubject();
			if (Validator.isNotNull(subject2)) {
				subject2 = subject2.toLowerCase();
			}
			else {
				subject2 = "";
			}

			if (_asc) {
				return subject1.compareTo(subject2);
			}
			else {
				return -(subject1.compareTo(subject2));
			}
		}
		catch (MessagingException me) {
			me.printStackTrace();
		}

		return 0;
	}

	private boolean _asc;

}
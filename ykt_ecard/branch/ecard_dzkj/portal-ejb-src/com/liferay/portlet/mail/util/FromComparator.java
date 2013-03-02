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

import java.io.Serializable;

import java.util.Comparator;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.internet.InternetAddress;

/**
 * <a href="FromComparator.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Jorge Ferrer
 * @version $Revision: 1.7 $
 *
 */
public class FromComparator implements Comparator, Serializable {

	public FromComparator(boolean asc) {
		_asc = asc;
	}

	public int compare(Object obj1, Object obj2) {
		Message msg1 = (Message)obj1;
		Message msg2 = (Message)obj2;

		try {
			if (_hasInvalidFrom(msg1) || _hasInvalidFrom(msg2)) {
				return -1;
			}

			InternetAddress ia1 = ((InternetAddress[])msg1.getFrom())[0];

			String address1 = MailUtil.toString(ia1).toLowerCase();

			if ((address1.startsWith("\"")) &&
				(address1.endsWith("\"")) &&
				(address1.length() > 1)) {

				address1 = address1.substring(1, address1.length() - 1);
			}
			else if (address1.startsWith("\"")) {
				address1 = address1.substring(1, address1.length());
			}
			else if (address1.endsWith("\"")) {
				address1 = address1.substring(0, address1.length() - 1);
			}

			InternetAddress ia2 = ((InternetAddress[])msg2.getFrom())[0];

			String address2 = MailUtil.toString(ia2).toLowerCase();

			if ((address2.startsWith("\"")) &&
				(address2.endsWith("\"")) &&
				(address2.length() > 1)) {

				address2 = address2.substring(1, address2.length() - 1);
			}
			else if (address2.startsWith("\"")) {
				address2 = address2.substring(1, address2.length());
			}
			else if (address2.endsWith("\"")) {
				address2 = address2.substring(0, address2.length() - 1);
			}

			if (_asc) {
				return address1.compareTo(address2);
			}
			else {
				return -(address1.compareTo(address2));
			}
		}
		catch (MessagingException me) {
			me.printStackTrace();
		}

		return 0;
	}

	private boolean _hasInvalidFrom(Message msg1) throws MessagingException {
		if ((msg1.getFrom() == null) ||
			(msg1.getFrom().length > 0) ||
			(msg1.getFrom()[0] == null)) {

			return true;
		}
		else {
			return false;
		}
	}

	private boolean _asc;

}
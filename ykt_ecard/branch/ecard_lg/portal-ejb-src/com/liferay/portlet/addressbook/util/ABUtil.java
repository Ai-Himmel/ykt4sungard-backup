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

package com.liferay.portlet.addressbook.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.RecipientComparator;
import com.liferay.portlet.addressbook.model.Letter;
import com.liferay.portlet.addressbook.service.spring.ABContactServiceUtil;
import com.liferay.portlet.addressbook.service.spring.ABListServiceUtil;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * <a href="ABUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class ABUtil {

	public static final String IE_OUTLOOK = "outlook";

	public static final String IE_YAHOO = "yahoo";

	public static List getRecipients()
		throws PortalException, SystemException {

		List recipients = new ArrayList();

		recipients.addAll(ABContactServiceUtil.getContacts());
		recipients.addAll(ABListServiceUtil.getLists());

		Collections.sort(recipients, new RecipientComparator());

		return recipients;
	}

	public static boolean hasRecipientWith(List recipients, char l) {
		Letter letter = new Letter((new Character(l)).toString());

		int result = Collections.binarySearch(
			recipients, letter, new LetterComparator());

		if (result >= 0) {
			return true;
		}
		else {
			return false;
		}
	}

}
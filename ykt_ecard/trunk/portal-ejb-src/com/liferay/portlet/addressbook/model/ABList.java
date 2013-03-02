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

package com.liferay.portlet.addressbook.model;

import com.liferay.portal.util.Recipient;
import com.liferay.portlet.addressbook.service.spring.ABListServiceUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="ABList.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class ABList extends ABListModel implements Recipient {

	public ABList() {
		super();
	}

	public ABList(String listId) {
		super(listId);
	}

	public ABList(String listId, String userId, String name) {
		super(listId, userId, name);
	}

	public String getRecipientId() {
		return getListId();
	}

	public String getRecipientName() {
		return getName();
	}

	public String getRecipientAddress() {
		FastStringBuffer sb = new FastStringBuffer();

		List recipients = null;

		try {
			recipients = ABListServiceUtil.getContacts(getListId());
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		if (recipients != null) {
			Iterator itr = recipients.iterator();

			while (itr.hasNext()) {
				Recipient recipient = (Recipient)itr.next();
				sb.append(recipient.getRecipientAddress());

				if (itr.hasNext()) {
					sb.append(", ");
				}
			}
		}

		return sb.toString();
	}

	public String getRecipientInternetAddress() {
		FastStringBuffer sb = new FastStringBuffer();

		List recipients = null;

		try {
			recipients = ABListServiceUtil.getContacts(getListId());
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		if (recipients != null) {
			Iterator itr = recipients.iterator();

			while (itr.hasNext()) {
				Recipient recipient = (Recipient)itr.next();
				sb.append(recipient.getRecipientInternetAddress());

				if (itr.hasNext()) {
					sb.append(", ");
				}
			}
		}

		return sb.toString();
	}

	public boolean isMultipleRecipients() {
		return true;
	}

}
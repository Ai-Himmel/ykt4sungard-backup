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

import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.Recipient;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.Date;

/**
 * <a href="ABContact.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class ABContact extends ABContactModel implements Recipient {

	public static final String[] JOB_CLASSES =
		PropsUtil.getArray(PropsUtil.ADDRESS_BOOK_CONTACT_JOB_CLASSES);

	public ABContact() {
		super();
	}

	public ABContact(String contactId) {
		super(contactId);
	}

	public ABContact(String firstName, String lastName, String emailAddress) {
		super(null, null, firstName, null, lastName, null, emailAddress, null,
			  null, null, null, null, null, null, null, null, null, null, null,
			  null, null, null, null, null, null, null, null, null, null, null,
			  null, null, null, null, null, null, null, null, null);
	}

	public ABContact(String contactId, String userId, String firstName,
					 String middleName, String lastName, String nickName,
					 String emailAddress, String homeStreet, String homeCity,
					 String homeState, String homeZip, String homeCountry,
					 String homePhone, String homeFax, String homeCell,
					 String homePager, String homeTollFree,
					 String homeEmailAddress, String businessCompany,
					 String businessStreet, String businessCity,
					 String businessState, String businessZip,
					 String businessCountry, String businessPhone,
					 String businessFax, String businessCell,
					 String businessPager, String businessTollFree,
					 String businessEmailAddress, String employeeNumber,
					 String jobTitle, String jobClass, String hoursOfOperation,
					 Date birthday, String timeZoneId, String instantMessenger,
					 String website, String comments) {

		super(contactId, userId, firstName, middleName, lastName, nickName,
			  emailAddress, homeStreet, homeCity, homeState, homeZip,
			  homeCountry, homePhone, homeFax, homeCell, homePager,
			  homeTollFree, homeEmailAddress, businessCompany, businessStreet,
			  businessCity, businessState, businessZip, businessCountry,
			  businessPhone, businessFax, businessCell, businessPager,
			  businessTollFree, businessEmailAddress, employeeNumber, jobTitle,
			  jobClass, hoursOfOperation,  birthday, timeZoneId,
			  instantMessenger, website, comments);
	}

	public String getFullName() {
		String firstName = getFirstName();
		String middleName = getMiddleName();
		String lastName = getLastName();

		if (Validator.isNull(middleName)) {
			return firstName + StringPool.SPACE + lastName;
		}
		else {
			return firstName + StringPool.SPACE + middleName +
				StringPool.SPACE + lastName;
		}
	}

	public String getRecipientId() {
		return getContactId();
	}

	public String getRecipientName() {
		return getFullName();
	}

	public String getRecipientAddress() {
		return getEmailAddress();
	}

	public String getRecipientInternetAddress() {
		return getFullName() + " <" + getEmailAddress() + ">";
	}

	public boolean isMultipleRecipients() {
		return false;
	}

}
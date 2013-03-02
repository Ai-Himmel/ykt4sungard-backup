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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchContactException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.ContactUtil;
import com.liferay.portal.service.spring.ContactLocalService;
import com.liferay.portal.service.spring.UserLocalServiceUtil;

import java.util.Date;

/**
 * <a href="ContactLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class ContactLocalServiceImpl implements ContactLocalService {

	// Business methods

	public Contact addUser(
			String userId, String firstName, String middleName, String lastName,
			String nickName, boolean male, Date birthday, String emailAddress,
			String smsId, String aimId, String icqId, String msnId,
			String skypeId, String ymId, String timeZoneId)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		String contactId = user.getUserId();

		Contact contact = null;

		try {
			contact = ContactUtil.findByPrimaryKey(contactId);
		}
		catch (NoSuchContactException nsae) {
			contact = ContactUtil.create(contactId);

			Date now = new Date();

			contact.setCompanyId(user.getCompanyId());
			contact.setUserId(user.getUserId());
			contact.setUserName(user.getFullName());
			contact.setCreateDate(now);
			contact.setModifiedDate(now);
			contact.setEmailAddress1(emailAddress);

			//ContactUtil.update(contact);
		}

		return contact;
	}

}
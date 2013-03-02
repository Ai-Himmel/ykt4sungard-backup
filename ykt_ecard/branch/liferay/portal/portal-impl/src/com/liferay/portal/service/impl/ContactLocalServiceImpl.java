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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchContactException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Contact;
import com.liferay.portal.service.base.ContactLocalServiceBaseImpl;

/**
 * <a href="ContactLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ContactLocalServiceImpl extends ContactLocalServiceBaseImpl {

	public Contact getContact(long contactId)
		throws PortalException, SystemException {

		return contactPersistence.findByPrimaryKey(contactId);
	}

	public void deleteContact(long contactId)
		throws PortalException, SystemException {

		try {
			Contact contact = contactPersistence.findByPrimaryKey(contactId);

			deleteContact(contact);
		}
		catch (NoSuchContactException nsce) {
		}
	}

	public void deleteContact(Contact contact)
		throws PortalException, SystemException {

		// Addresses

		addressLocalService.deleteAddresses(
			contact.getCompanyId(), Contact.class.getName(),
			contact.getContactId());

		// Email addresses

		emailAddressLocalService.deleteEmailAddresses(
			contact.getCompanyId(), Contact.class.getName(),
			contact.getContactId());

		// Phone

		phoneLocalService.deletePhones(
			contact.getCompanyId(), Contact.class.getName(),
			contact.getContactId());

		// Website

		websiteLocalService.deleteWebsites(
			contact.getCompanyId(), Contact.class.getName(),
			contact.getContactId());

		// Contact

		contactPersistence.remove(contact.getContactId());
	}

}
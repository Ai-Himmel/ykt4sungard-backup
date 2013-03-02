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

package com.liferay.portlet.addressbook.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.util.RecipientComparator;
import com.liferay.portlet.addressbook.ContactEmailAddressException;
import com.liferay.portlet.addressbook.ContactFirstNameException;
import com.liferay.portlet.addressbook.ContactLastNameException;
import com.liferay.portlet.addressbook.DuplicateContactException;
import com.liferay.portlet.addressbook.model.ABContact;
import com.liferay.portlet.addressbook.service.persistence.ABContactUtil;
import com.liferay.portlet.addressbook.service.spring.ABContactLocalServiceUtil;
import com.liferay.portlet.addressbook.service.spring.ABContactService;
import com.liferay.portlet.addressbook.util.Importer;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.Collections;
import java.util.Date;
import java.util.List;

/**
 * <a href="ABContactServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class ABContactServiceImpl
	extends PrincipalBean implements ABContactService {

	// Business methods

	public ABContact addContact(
			String firstName, String lastName, String emailAddress)
		throws PortalException, SystemException {

		return addContact(
			firstName, StringPool.BLANK, lastName, StringPool.BLANK,
			emailAddress, StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK, null,
			StringPool.BLANK, StringPool.BLANK, StringPool.BLANK,
			StringPool.BLANK);
	}

	public ABContact addContact(
			String firstName, String middleName, String lastName,
			String nickName, String emailAddress, String homeStreet,
			String homeCity, String homeState, String homeZip,
			String homeCountry, String homePhone, String homeFax,
			String homeCell, String homePager, String homeTollFree,
			String homeEmailAddress, String businessCompany,
			String businessStreet, String businessCity, String businessState,
			String businessZip, String businessCountry, String businessPhone,
			String businessFax, String businessCell, String businessPager,
			String businessTollFree, String businessEmailAddress,
			String employeeNumber, String jobTitle, String jobClass,
			String hoursOfOperation, Date birthday, String timeZoneId,
			String instantMessenger, String website, String comments)
		throws PortalException, SystemException {

		emailAddress = emailAddress.trim();

		_validate(firstName, lastName, emailAddress, true);

		String contactId = Long.toString(CounterServiceUtil.increment(
			ABContact.class.getName()));

		ABContact contact = ABContactUtil.create(contactId);

		contact.setUserId(getUserId());
		contact.setFirstName(firstName);
		contact.setMiddleName(middleName);
		contact.setLastName(lastName);
		contact.setNickName(nickName);
		contact.setEmailAddress(emailAddress);
		contact.setHomeStreet(homeStreet);
		contact.setHomeCity(homeCity);
		contact.setHomeState(homeState);
		contact.setHomeZip(homeZip);
		contact.setHomeCountry(homeCountry);
		contact.setHomePhone(homePhone);
		contact.setHomeFax(homeFax);
		contact.setHomeCell(homeCell);
		contact.setHomePager(homePager);
		contact.setHomeTollFree(homeTollFree);
		contact.setHomeEmailAddress(homeEmailAddress);
		contact.setBusinessCompany(businessCompany);
		contact.setBusinessStreet(businessStreet);
		contact.setBusinessCity(businessCity);
		contact.setBusinessState(businessState);
		contact.setBusinessZip(businessZip);
		contact.setBusinessCountry(businessCountry);
		contact.setBusinessPhone(businessPhone);
		contact.setBusinessFax(businessFax);
		contact.setBusinessCell(businessCell);
		contact.setBusinessPager(businessPager);
		contact.setBusinessTollFree(businessTollFree);
		contact.setBusinessEmailAddress(businessEmailAddress);
		contact.setEmployeeNumber(employeeNumber);
		contact.setJobTitle(jobTitle);
		contact.setJobClass(jobClass);
		contact.setHoursOfOperation(hoursOfOperation);
		contact.setBirthday(birthday);
		contact.setTimeZoneId(timeZoneId);
		contact.setInstantMessenger(instantMessenger);
		contact.setWebsite(website);
		contact.setComments(comments);

		ABContactUtil.update(contact);

		return contact;
	}

	public void addContacts(Importer importer)
		throws PortalException, SystemException {

		ABContact[] contacts = importer.getContacts();

		if (contacts == null || contacts.length == 0) {
			return;
		}

		for (int i = 0; i < contacts.length; i++) {
			_validate(
				contacts[i].getFirstName(), contacts[i].getLastName(),
				contacts[i].getEmailAddress(), true);
		}

		for (int i = 0; i < contacts.length; i++) {
			addContact(
				contacts[i].getFirstName(), contacts[i].getMiddleName(),
				contacts[i].getLastName(), contacts[i].getNickName(),
				contacts[i].getEmailAddress(), contacts[i].getHomeStreet(),
				contacts[i].getHomeCity(), contacts[i].getHomeState(),
				contacts[i].getHomeZip(), contacts[i].getHomeCountry(),
				contacts[i].getHomePhone(), contacts[i].getHomeFax(),
				contacts[i].getHomeCell(), contacts[i].getHomePager(),
				contacts[i].getHomeTollFree(),
				contacts[i].getHomeEmailAddress(),
				contacts[i].getBusinessCompany(),
				contacts[i].getBusinessStreet(), contacts[i].getBusinessCity(),
				contacts[i].getBusinessState(), contacts[i].getBusinessZip(),
				contacts[i].getBusinessCountry(),
				contacts[i].getBusinessPhone(), contacts[i].getBusinessFax(),
				contacts[i].getBusinessCell(), contacts[i].getBusinessPager(),
				contacts[i].getBusinessTollFree(),
				contacts[i].getBusinessEmailAddress(),
				contacts[i].getEmployeeNumber(), contacts[i].getJobTitle(),
				contacts[i].getJobClass(), contacts[i].getHoursOfOperation(),
				contacts[i].getBirthday(), contacts[i].getTimeZoneId(),
				contacts[i].getInstantMessenger(), contacts[i].getWebsite(),
				contacts[i].getComments());
		}
	}

	public void deleteContact(String contactId)
		throws PortalException, SystemException {

		ABContact contact = ABContactUtil.findByPrimaryKey(contactId);

		if (!contact.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		ABContactLocalServiceUtil.deleteContact(contactId);
	}

	public ABContact getContact(String contactId)
		throws PortalException, SystemException {

		ABContact contact = ABContactUtil.findByPrimaryKey(contactId);

		if (!contact.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		return contact;
	}

	public List getContacts() throws PortalException, SystemException {
		return ABContactUtil.findByUserId(getUserId());
	}

	public int getContactsSize() throws PortalException, SystemException {
		return ABContactUtil.countByUserId(getUserId());
	}

	public List getLists(String contactId)
		throws PortalException, SystemException {

		ABContact contact = ABContactUtil.findByPrimaryKey(contactId);

		if (!contact.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		List lists = ABContactUtil.getABLists(contactId);

		Collections.sort(lists, new RecipientComparator());

		return lists;
	}

	public void setLists(String contactId, List lists)
		throws PortalException, SystemException {

		ABContact contact = ABContactUtil.findByPrimaryKey(contactId);

		if (!contact.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		ABContactUtil.setABLists(contactId, lists);
	}

	public ABContact updateContact(
			String contactId, String firstName, String middleName,
			String lastName, String nickName, String emailAddress,
			String homeStreet, String homeCity, String homeState,
			String homeZip, String homeCountry, String homePhone,
			String homeFax, String homeCell, String homePager,
			String homeTollFree, String homeEmailAddress,
			String businessCompany, String businessStreet, String businessCity,
			String businessState, String businessZip, String businessCountry,
			String businessPhone, String businessFax, String businessCell,
			String businessPager, String businessTollFree,
			String businessEmailAddress, String employeeNumber, String jobTitle,
			String jobClass, String hoursOfOperation, Date birthday,
			String timeZoneId, String instantMessenger, String website,
			String comments)
		throws PortalException, SystemException {

		emailAddress = emailAddress.trim();

		_validate(firstName, lastName, emailAddress, false);

		ABContact contact = ABContactUtil.findByPrimaryKey(contactId);

		if (!contact.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		contact.setFirstName(firstName);
		contact.setMiddleName(middleName);
		contact.setLastName(lastName);
		contact.setNickName(nickName);
		contact.setEmailAddress(emailAddress);
		contact.setHomeStreet(homeStreet);
		contact.setHomeCity(homeCity);
		contact.setHomeState(homeState);
		contact.setHomeZip(homeZip);
		contact.setHomeCountry(homeCountry);
		contact.setHomePhone(homePhone);
		contact.setHomeFax(homeFax);
		contact.setHomeCell(homeCell);
		contact.setHomePager(homePager);
		contact.setHomeTollFree(homeTollFree);
		contact.setHomeEmailAddress(homeEmailAddress);
		contact.setBusinessCompany(businessCompany);
		contact.setBusinessStreet(businessStreet);
		contact.setBusinessCity(businessCity);
		contact.setBusinessState(businessState);
		contact.setBusinessZip(businessZip);
		contact.setBusinessCountry(businessCountry);
		contact.setBusinessPhone(businessPhone);
		contact.setBusinessFax(businessFax);
		contact.setBusinessCell(businessCell);
		contact.setBusinessPager(businessPager);
		contact.setBusinessTollFree(businessTollFree);
		contact.setBusinessEmailAddress(businessEmailAddress);
		contact.setEmployeeNumber(employeeNumber);
		contact.setJobTitle(jobTitle);
		contact.setJobClass(jobClass);
		contact.setHoursOfOperation(hoursOfOperation);
		contact.setBirthday(birthday);
		contact.setTimeZoneId(timeZoneId);
		contact.setInstantMessenger(instantMessenger);
		contact.setWebsite(website);
		contact.setComments(comments);

		ABContactUtil.update(contact);

		return contact;
	}

	// Private methods

	private void _validate(
			String firstName, String lastName, String emailAddress,
			boolean addContact)
		throws PortalException, SystemException {

		if (Validator.isNull(firstName)) {
			throw new ContactFirstNameException();
		}
		else if (Validator.isNull(lastName)) {
			throw new ContactLastNameException();
		}
		else if (!Validator.isEmailAddress(emailAddress)) {
			throw new ContactEmailAddressException();
		}

		if (addContact) {
			List contacts = getContacts();
			ABContact contact =
				new ABContact(firstName, lastName, emailAddress);

			int pos = Collections.binarySearch(contacts, contact);
			if (pos >= 0) {
				throw new DuplicateContactException();
			}
		}
	}

}
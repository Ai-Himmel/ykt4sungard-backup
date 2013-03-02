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

package com.liferay.portlet.addressbook.service.spring;

/**
 * <a href="ABContactServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ABContactServiceUtil {
	public static final String PORTLET_ID = "10";

	public static com.liferay.portlet.addressbook.model.ABContact addContact(
		java.lang.String firstName, java.lang.String lastName,
		java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.addContact(firstName, lastName, emailAddress);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.addressbook.model.ABContact addContact(
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String nickName,
		java.lang.String emailAddress, java.lang.String homeStreet,
		java.lang.String homeCity, java.lang.String homeState,
		java.lang.String homeZip, java.lang.String homeCountry,
		java.lang.String homePhone, java.lang.String homeFax,
		java.lang.String homeCell, java.lang.String homePager,
		java.lang.String homeTollFree, java.lang.String homeEmailAddress,
		java.lang.String businessCompany, java.lang.String businessStreet,
		java.lang.String businessCity, java.lang.String businessState,
		java.lang.String businessZip, java.lang.String businessCountry,
		java.lang.String businessPhone, java.lang.String businessFax,
		java.lang.String businessCell, java.lang.String businessPager,
		java.lang.String businessTollFree,
		java.lang.String businessEmailAddress, java.lang.String employeeNumber,
		java.lang.String jobTitle, java.lang.String jobClass,
		java.lang.String hoursOfOperation, java.util.Date birthday,
		java.lang.String timeZoneId, java.lang.String instantMessenger,
		java.lang.String website, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.addContact(firstName, middleName, lastName,
				nickName, emailAddress, homeStreet, homeCity, homeState,
				homeZip, homeCountry, homePhone, homeFax, homeCell, homePager,
				homeTollFree, homeEmailAddress, businessCompany,
				businessStreet, businessCity, businessState, businessZip,
				businessCountry, businessPhone, businessFax, businessCell,
				businessPager, businessTollFree, businessEmailAddress,
				employeeNumber, jobTitle, jobClass, hoursOfOperation, birthday,
				timeZoneId, instantMessenger, website, comments);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void addContacts(
		com.liferay.portlet.addressbook.util.Importer importer)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();
			abContactService.addContacts(importer);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteContact(java.lang.String contactId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();
			abContactService.deleteContact(contactId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.addressbook.model.ABContact getContact(
		java.lang.String contactId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.getContact(contactId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getContacts()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.getContacts();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getContactsSize()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.getContactsSize();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getLists(java.lang.String contactId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.getLists(contactId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setLists(java.lang.String contactId, java.util.List lists)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();
			abContactService.setLists(contactId, lists);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.addressbook.model.ABContact updateContact(
		java.lang.String contactId, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String nickName, java.lang.String emailAddress,
		java.lang.String homeStreet, java.lang.String homeCity,
		java.lang.String homeState, java.lang.String homeZip,
		java.lang.String homeCountry, java.lang.String homePhone,
		java.lang.String homeFax, java.lang.String homeCell,
		java.lang.String homePager, java.lang.String homeTollFree,
		java.lang.String homeEmailAddress, java.lang.String businessCompany,
		java.lang.String businessStreet, java.lang.String businessCity,
		java.lang.String businessState, java.lang.String businessZip,
		java.lang.String businessCountry, java.lang.String businessPhone,
		java.lang.String businessFax, java.lang.String businessCell,
		java.lang.String businessPager, java.lang.String businessTollFree,
		java.lang.String businessEmailAddress, java.lang.String employeeNumber,
		java.lang.String jobTitle, java.lang.String jobClass,
		java.lang.String hoursOfOperation, java.util.Date birthday,
		java.lang.String timeZoneId, java.lang.String instantMessenger,
		java.lang.String website, java.lang.String comments)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ABContactService abContactService = ABContactServiceFactory.getService();

			return abContactService.updateContact(contactId, firstName,
				middleName, lastName, nickName, emailAddress, homeStreet,
				homeCity, homeState, homeZip, homeCountry, homePhone, homeFax,
				homeCell, homePager, homeTollFree, homeEmailAddress,
				businessCompany, businessStreet, businessCity, businessState,
				businessZip, businessCountry, businessPhone, businessFax,
				businessCell, businessPager, businessTollFree,
				businessEmailAddress, employeeNumber, jobTitle, jobClass,
				hoursOfOperation, birthday, timeZoneId, instantMessenger,
				website, comments);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}
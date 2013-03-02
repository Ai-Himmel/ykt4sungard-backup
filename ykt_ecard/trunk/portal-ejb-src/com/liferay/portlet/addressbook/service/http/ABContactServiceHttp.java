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

package com.liferay.portlet.addressbook.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.addressbook.service.spring.ABContactServiceUtil;

import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ABContactServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ABContactServiceHttp {
	public static com.liferay.portlet.addressbook.model.ABContact addContact(
		HttpPrincipal httpPrincipal, java.lang.String firstName,
		java.lang.String lastName, java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = firstName;

			if (firstName == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = lastName;

			if (lastName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = emailAddress;

			if (emailAddress == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"addContact",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.addressbook.model.ABContact)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.addressbook.model.ABContact addContact(
		HttpPrincipal httpPrincipal, java.lang.String firstName,
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
			Object paramObj0 = firstName;

			if (firstName == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = middleName;

			if (middleName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = lastName;

			if (lastName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = nickName;

			if (nickName == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = emailAddress;

			if (emailAddress == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = homeStreet;

			if (homeStreet == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = homeCity;

			if (homeCity == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = homeState;

			if (homeState == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = homeZip;

			if (homeZip == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = homeCountry;

			if (homeCountry == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = homePhone;

			if (homePhone == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = homeFax;

			if (homeFax == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = homeCell;

			if (homeCell == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = homePager;

			if (homePager == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = homeTollFree;

			if (homeTollFree == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = homeEmailAddress;

			if (homeEmailAddress == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = businessCompany;

			if (businessCompany == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = businessStreet;

			if (businessStreet == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = businessCity;

			if (businessCity == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = businessState;

			if (businessState == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = businessZip;

			if (businessZip == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = businessCountry;

			if (businessCountry == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = businessPhone;

			if (businessPhone == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = businessFax;

			if (businessFax == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = businessCell;

			if (businessCell == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = businessPager;

			if (businessPager == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			Object paramObj26 = businessTollFree;

			if (businessTollFree == null) {
				paramObj26 = new NullWrapper("java.lang.String");
			}

			Object paramObj27 = businessEmailAddress;

			if (businessEmailAddress == null) {
				paramObj27 = new NullWrapper("java.lang.String");
			}

			Object paramObj28 = employeeNumber;

			if (employeeNumber == null) {
				paramObj28 = new NullWrapper("java.lang.String");
			}

			Object paramObj29 = jobTitle;

			if (jobTitle == null) {
				paramObj29 = new NullWrapper("java.lang.String");
			}

			Object paramObj30 = jobClass;

			if (jobClass == null) {
				paramObj30 = new NullWrapper("java.lang.String");
			}

			Object paramObj31 = hoursOfOperation;

			if (hoursOfOperation == null) {
				paramObj31 = new NullWrapper("java.lang.String");
			}

			Object paramObj32 = birthday;

			if (birthday == null) {
				paramObj32 = new NullWrapper("java.util.Date");
			}

			Object paramObj33 = timeZoneId;

			if (timeZoneId == null) {
				paramObj33 = new NullWrapper("java.lang.String");
			}

			Object paramObj34 = instantMessenger;

			if (instantMessenger == null) {
				paramObj34 = new NullWrapper("java.lang.String");
			}

			Object paramObj35 = website;

			if (website == null) {
				paramObj35 = new NullWrapper("java.lang.String");
			}

			Object paramObj36 = comments;

			if (comments == null) {
				paramObj36 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"addContact",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26, paramObj27, paramObj28, paramObj29,
						paramObj30, paramObj31, paramObj32, paramObj33,
						paramObj34, paramObj35, paramObj36
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.addressbook.model.ABContact)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void addContacts(HttpPrincipal httpPrincipal,
		com.liferay.portlet.addressbook.util.Importer importer)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = importer;

			if (importer == null) {
				paramObj0 = new NullWrapper(
						"com.liferay.portlet.addressbook.util.Importer");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"addContacts", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void deleteContact(HttpPrincipal httpPrincipal,
		java.lang.String contactId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = contactId;

			if (contactId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"deleteContact", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.addressbook.model.ABContact getContact(
		HttpPrincipal httpPrincipal, java.lang.String contactId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = contactId;

			if (contactId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"getContact", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.addressbook.model.ABContact)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getContacts(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"getContacts", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static int getContactsSize(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"getContactsSize", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Integer)returnObj).intValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getLists(HttpPrincipal httpPrincipal,
		java.lang.String contactId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = contactId;

			if (contactId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"getLists", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void setLists(HttpPrincipal httpPrincipal,
		java.lang.String contactId, java.util.List lists)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = contactId;

			if (contactId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = lists;

			if (lists == null) {
				paramObj1 = new NullWrapper("java.util.List");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"setLists", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.addressbook.model.ABContact updateContact(
		HttpPrincipal httpPrincipal, java.lang.String contactId,
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
			Object paramObj0 = contactId;

			if (contactId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = firstName;

			if (firstName == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = middleName;

			if (middleName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = lastName;

			if (lastName == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = nickName;

			if (nickName == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = emailAddress;

			if (emailAddress == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = homeStreet;

			if (homeStreet == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = homeCity;

			if (homeCity == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = homeState;

			if (homeState == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = homeZip;

			if (homeZip == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = homeCountry;

			if (homeCountry == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = homePhone;

			if (homePhone == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = homeFax;

			if (homeFax == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			Object paramObj13 = homeCell;

			if (homeCell == null) {
				paramObj13 = new NullWrapper("java.lang.String");
			}

			Object paramObj14 = homePager;

			if (homePager == null) {
				paramObj14 = new NullWrapper("java.lang.String");
			}

			Object paramObj15 = homeTollFree;

			if (homeTollFree == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = homeEmailAddress;

			if (homeEmailAddress == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = businessCompany;

			if (businessCompany == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = businessStreet;

			if (businessStreet == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = businessCity;

			if (businessCity == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = businessState;

			if (businessState == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = businessZip;

			if (businessZip == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = businessCountry;

			if (businessCountry == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = businessPhone;

			if (businessPhone == null) {
				paramObj23 = new NullWrapper("java.lang.String");
			}

			Object paramObj24 = businessFax;

			if (businessFax == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = businessCell;

			if (businessCell == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			Object paramObj26 = businessPager;

			if (businessPager == null) {
				paramObj26 = new NullWrapper("java.lang.String");
			}

			Object paramObj27 = businessTollFree;

			if (businessTollFree == null) {
				paramObj27 = new NullWrapper("java.lang.String");
			}

			Object paramObj28 = businessEmailAddress;

			if (businessEmailAddress == null) {
				paramObj28 = new NullWrapper("java.lang.String");
			}

			Object paramObj29 = employeeNumber;

			if (employeeNumber == null) {
				paramObj29 = new NullWrapper("java.lang.String");
			}

			Object paramObj30 = jobTitle;

			if (jobTitle == null) {
				paramObj30 = new NullWrapper("java.lang.String");
			}

			Object paramObj31 = jobClass;

			if (jobClass == null) {
				paramObj31 = new NullWrapper("java.lang.String");
			}

			Object paramObj32 = hoursOfOperation;

			if (hoursOfOperation == null) {
				paramObj32 = new NullWrapper("java.lang.String");
			}

			Object paramObj33 = birthday;

			if (birthday == null) {
				paramObj33 = new NullWrapper("java.util.Date");
			}

			Object paramObj34 = timeZoneId;

			if (timeZoneId == null) {
				paramObj34 = new NullWrapper("java.lang.String");
			}

			Object paramObj35 = instantMessenger;

			if (instantMessenger == null) {
				paramObj35 = new NullWrapper("java.lang.String");
			}

			Object paramObj36 = website;

			if (website == null) {
				paramObj36 = new NullWrapper("java.lang.String");
			}

			Object paramObj37 = comments;

			if (comments == null) {
				paramObj37 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(ABContactServiceUtil.class.getName(),
					"updateContact",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26, paramObj27, paramObj28, paramObj29,
						paramObj30, paramObj31, paramObj32, paramObj33,
						paramObj34, paramObj35, paramObj36, paramObj37
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.addressbook.model.ABContact)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	private static final Log _log = LogFactory.getLog(ABContactServiceHttp.class);
}
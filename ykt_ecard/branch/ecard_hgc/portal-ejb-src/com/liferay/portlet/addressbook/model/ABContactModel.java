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

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="ABContactModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.82 $
 *
 */
public class ABContactModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.addressbook.model.ABContact"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.addressbook.model.ABContact"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_CONTACTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.contactId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FIRSTNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.firstName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_MIDDLENAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.middleName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_LASTNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.lastName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NICKNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.nickName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_EMAILADDRESS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.emailAddress"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMESTREET = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeStreet"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMECITY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeCity"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMESTATE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeState"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMEZIP = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeZip"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMECOUNTRY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeCountry"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMEPHONE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homePhone"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMEFAX = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeFax"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMECELL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeCell"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMEPAGER = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homePager"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMETOLLFREE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeTollFree"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOMEEMAILADDRESS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.homeEmailAddress"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSCOMPANY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessCompany"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSSTREET = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessStreet"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSCITY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessCity"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSSTATE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessState"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSZIP = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessZip"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSCOUNTRY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessCountry"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSPHONE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessPhone"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSFAX = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessFax"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSCELL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessCell"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSPAGER = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessPager"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSTOLLFREE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessTollFree"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BUSINESSEMAILADDRESS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.businessEmailAddress"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_EMPLOYEENUMBER = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.employeeNumber"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_JOBTITLE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.jobTitle"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_JOBCLASS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.jobClass"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_HOURSOFOPERATION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.hoursOfOperation"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TIMEZONEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.timeZoneId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_INSTANTMESSENGER = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.instantMessenger"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_WEBSITE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.website"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMMENTS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.addressbook.model.ABContact.comments"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.addressbook.model.ABContactModel"));

	public ABContactModel() {
	}

	public ABContactModel(String contactId) {
		_contactId = contactId;
		setNew(true);
	}

	public ABContactModel(String contactId, String userId, String firstName,
		String middleName, String lastName, String nickName,
		String emailAddress, String homeStreet, String homeCity,
		String homeState, String homeZip, String homeCountry, String homePhone,
		String homeFax, String homeCell, String homePager, String homeTollFree,
		String homeEmailAddress, String businessCompany, String businessStreet,
		String businessCity, String businessState, String businessZip,
		String businessCountry, String businessPhone, String businessFax,
		String businessCell, String businessPager, String businessTollFree,
		String businessEmailAddress, String employeeNumber, String jobTitle,
		String jobClass, String hoursOfOperation, Date birthday,
		String timeZoneId, String instantMessenger, String website,
		String comments) {
		_contactId = contactId;
		_userId = userId;
		_firstName = firstName;
		_middleName = middleName;
		_lastName = lastName;
		_nickName = nickName;
		_emailAddress = emailAddress;
		_homeStreet = homeStreet;
		_homeCity = homeCity;
		_homeState = homeState;
		_homeZip = homeZip;
		_homeCountry = homeCountry;
		_homePhone = homePhone;
		_homeFax = homeFax;
		_homeCell = homeCell;
		_homePager = homePager;
		_homeTollFree = homeTollFree;
		_homeEmailAddress = homeEmailAddress;
		_businessCompany = businessCompany;
		_businessStreet = businessStreet;
		_businessCity = businessCity;
		_businessState = businessState;
		_businessZip = businessZip;
		_businessCountry = businessCountry;
		_businessPhone = businessPhone;
		_businessFax = businessFax;
		_businessCell = businessCell;
		_businessPager = businessPager;
		_businessTollFree = businessTollFree;
		_businessEmailAddress = businessEmailAddress;
		_employeeNumber = employeeNumber;
		_jobTitle = jobTitle;
		_jobClass = jobClass;
		_hoursOfOperation = hoursOfOperation;
		_birthday = birthday;
		_timeZoneId = timeZoneId;
		_instantMessenger = instantMessenger;
		_website = website;
		_comments = comments;
	}

	public String getPrimaryKey() {
		return _contactId;
	}

	public String getContactId() {
		return _contactId;
	}

	public void setContactId(String contactId) {
		if (((contactId == null) && (_contactId != null)) ||
				((contactId != null) && (_contactId == null)) ||
				((contactId != null) && (_contactId != null) &&
				!contactId.equals(_contactId))) {
			if (!XSS_ALLOW_CONTACTID) {
				contactId = Xss.strip(contactId);
			}

			_contactId = contactId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
		}
	}

	public String getFirstName() {
		return _firstName;
	}

	public void setFirstName(String firstName) {
		if (((firstName == null) && (_firstName != null)) ||
				((firstName != null) && (_firstName == null)) ||
				((firstName != null) && (_firstName != null) &&
				!firstName.equals(_firstName))) {
			if (!XSS_ALLOW_FIRSTNAME) {
				firstName = Xss.strip(firstName);
			}

			_firstName = firstName;
			setModified(true);
		}
	}

	public String getMiddleName() {
		return _middleName;
	}

	public void setMiddleName(String middleName) {
		if (((middleName == null) && (_middleName != null)) ||
				((middleName != null) && (_middleName == null)) ||
				((middleName != null) && (_middleName != null) &&
				!middleName.equals(_middleName))) {
			if (!XSS_ALLOW_MIDDLENAME) {
				middleName = Xss.strip(middleName);
			}

			_middleName = middleName;
			setModified(true);
		}
	}

	public String getLastName() {
		return _lastName;
	}

	public void setLastName(String lastName) {
		if (((lastName == null) && (_lastName != null)) ||
				((lastName != null) && (_lastName == null)) ||
				((lastName != null) && (_lastName != null) &&
				!lastName.equals(_lastName))) {
			if (!XSS_ALLOW_LASTNAME) {
				lastName = Xss.strip(lastName);
			}

			_lastName = lastName;
			setModified(true);
		}
	}

	public String getNickName() {
		return _nickName;
	}

	public void setNickName(String nickName) {
		if (((nickName == null) && (_nickName != null)) ||
				((nickName != null) && (_nickName == null)) ||
				((nickName != null) && (_nickName != null) &&
				!nickName.equals(_nickName))) {
			if (!XSS_ALLOW_NICKNAME) {
				nickName = Xss.strip(nickName);
			}

			_nickName = nickName;
			setModified(true);
		}
	}

	public String getEmailAddress() {
		return _emailAddress;
	}

	public void setEmailAddress(String emailAddress) {
		if (((emailAddress == null) && (_emailAddress != null)) ||
				((emailAddress != null) && (_emailAddress == null)) ||
				((emailAddress != null) && (_emailAddress != null) &&
				!emailAddress.equals(_emailAddress))) {
			if (!XSS_ALLOW_EMAILADDRESS) {
				emailAddress = Xss.strip(emailAddress);
			}

			_emailAddress = emailAddress;
			setModified(true);
		}
	}

	public String getHomeStreet() {
		return _homeStreet;
	}

	public void setHomeStreet(String homeStreet) {
		if (((homeStreet == null) && (_homeStreet != null)) ||
				((homeStreet != null) && (_homeStreet == null)) ||
				((homeStreet != null) && (_homeStreet != null) &&
				!homeStreet.equals(_homeStreet))) {
			if (!XSS_ALLOW_HOMESTREET) {
				homeStreet = Xss.strip(homeStreet);
			}

			_homeStreet = homeStreet;
			setModified(true);
		}
	}

	public String getHomeCity() {
		return _homeCity;
	}

	public void setHomeCity(String homeCity) {
		if (((homeCity == null) && (_homeCity != null)) ||
				((homeCity != null) && (_homeCity == null)) ||
				((homeCity != null) && (_homeCity != null) &&
				!homeCity.equals(_homeCity))) {
			if (!XSS_ALLOW_HOMECITY) {
				homeCity = Xss.strip(homeCity);
			}

			_homeCity = homeCity;
			setModified(true);
		}
	}

	public String getHomeState() {
		return _homeState;
	}

	public void setHomeState(String homeState) {
		if (((homeState == null) && (_homeState != null)) ||
				((homeState != null) && (_homeState == null)) ||
				((homeState != null) && (_homeState != null) &&
				!homeState.equals(_homeState))) {
			if (!XSS_ALLOW_HOMESTATE) {
				homeState = Xss.strip(homeState);
			}

			_homeState = homeState;
			setModified(true);
		}
	}

	public String getHomeZip() {
		return _homeZip;
	}

	public void setHomeZip(String homeZip) {
		if (((homeZip == null) && (_homeZip != null)) ||
				((homeZip != null) && (_homeZip == null)) ||
				((homeZip != null) && (_homeZip != null) &&
				!homeZip.equals(_homeZip))) {
			if (!XSS_ALLOW_HOMEZIP) {
				homeZip = Xss.strip(homeZip);
			}

			_homeZip = homeZip;
			setModified(true);
		}
	}

	public String getHomeCountry() {
		return _homeCountry;
	}

	public void setHomeCountry(String homeCountry) {
		if (((homeCountry == null) && (_homeCountry != null)) ||
				((homeCountry != null) && (_homeCountry == null)) ||
				((homeCountry != null) && (_homeCountry != null) &&
				!homeCountry.equals(_homeCountry))) {
			if (!XSS_ALLOW_HOMECOUNTRY) {
				homeCountry = Xss.strip(homeCountry);
			}

			_homeCountry = homeCountry;
			setModified(true);
		}
	}

	public String getHomePhone() {
		return _homePhone;
	}

	public void setHomePhone(String homePhone) {
		if (((homePhone == null) && (_homePhone != null)) ||
				((homePhone != null) && (_homePhone == null)) ||
				((homePhone != null) && (_homePhone != null) &&
				!homePhone.equals(_homePhone))) {
			if (!XSS_ALLOW_HOMEPHONE) {
				homePhone = Xss.strip(homePhone);
			}

			_homePhone = homePhone;
			setModified(true);
		}
	}

	public String getHomeFax() {
		return _homeFax;
	}

	public void setHomeFax(String homeFax) {
		if (((homeFax == null) && (_homeFax != null)) ||
				((homeFax != null) && (_homeFax == null)) ||
				((homeFax != null) && (_homeFax != null) &&
				!homeFax.equals(_homeFax))) {
			if (!XSS_ALLOW_HOMEFAX) {
				homeFax = Xss.strip(homeFax);
			}

			_homeFax = homeFax;
			setModified(true);
		}
	}

	public String getHomeCell() {
		return _homeCell;
	}

	public void setHomeCell(String homeCell) {
		if (((homeCell == null) && (_homeCell != null)) ||
				((homeCell != null) && (_homeCell == null)) ||
				((homeCell != null) && (_homeCell != null) &&
				!homeCell.equals(_homeCell))) {
			if (!XSS_ALLOW_HOMECELL) {
				homeCell = Xss.strip(homeCell);
			}

			_homeCell = homeCell;
			setModified(true);
		}
	}

	public String getHomePager() {
		return _homePager;
	}

	public void setHomePager(String homePager) {
		if (((homePager == null) && (_homePager != null)) ||
				((homePager != null) && (_homePager == null)) ||
				((homePager != null) && (_homePager != null) &&
				!homePager.equals(_homePager))) {
			if (!XSS_ALLOW_HOMEPAGER) {
				homePager = Xss.strip(homePager);
			}

			_homePager = homePager;
			setModified(true);
		}
	}

	public String getHomeTollFree() {
		return _homeTollFree;
	}

	public void setHomeTollFree(String homeTollFree) {
		if (((homeTollFree == null) && (_homeTollFree != null)) ||
				((homeTollFree != null) && (_homeTollFree == null)) ||
				((homeTollFree != null) && (_homeTollFree != null) &&
				!homeTollFree.equals(_homeTollFree))) {
			if (!XSS_ALLOW_HOMETOLLFREE) {
				homeTollFree = Xss.strip(homeTollFree);
			}

			_homeTollFree = homeTollFree;
			setModified(true);
		}
	}

	public String getHomeEmailAddress() {
		return _homeEmailAddress;
	}

	public void setHomeEmailAddress(String homeEmailAddress) {
		if (((homeEmailAddress == null) && (_homeEmailAddress != null)) ||
				((homeEmailAddress != null) && (_homeEmailAddress == null)) ||
				((homeEmailAddress != null) && (_homeEmailAddress != null) &&
				!homeEmailAddress.equals(_homeEmailAddress))) {
			if (!XSS_ALLOW_HOMEEMAILADDRESS) {
				homeEmailAddress = Xss.strip(homeEmailAddress);
			}

			_homeEmailAddress = homeEmailAddress;
			setModified(true);
		}
	}

	public String getBusinessCompany() {
		return _businessCompany;
	}

	public void setBusinessCompany(String businessCompany) {
		if (((businessCompany == null) && (_businessCompany != null)) ||
				((businessCompany != null) && (_businessCompany == null)) ||
				((businessCompany != null) && (_businessCompany != null) &&
				!businessCompany.equals(_businessCompany))) {
			if (!XSS_ALLOW_BUSINESSCOMPANY) {
				businessCompany = Xss.strip(businessCompany);
			}

			_businessCompany = businessCompany;
			setModified(true);
		}
	}

	public String getBusinessStreet() {
		return _businessStreet;
	}

	public void setBusinessStreet(String businessStreet) {
		if (((businessStreet == null) && (_businessStreet != null)) ||
				((businessStreet != null) && (_businessStreet == null)) ||
				((businessStreet != null) && (_businessStreet != null) &&
				!businessStreet.equals(_businessStreet))) {
			if (!XSS_ALLOW_BUSINESSSTREET) {
				businessStreet = Xss.strip(businessStreet);
			}

			_businessStreet = businessStreet;
			setModified(true);
		}
	}

	public String getBusinessCity() {
		return _businessCity;
	}

	public void setBusinessCity(String businessCity) {
		if (((businessCity == null) && (_businessCity != null)) ||
				((businessCity != null) && (_businessCity == null)) ||
				((businessCity != null) && (_businessCity != null) &&
				!businessCity.equals(_businessCity))) {
			if (!XSS_ALLOW_BUSINESSCITY) {
				businessCity = Xss.strip(businessCity);
			}

			_businessCity = businessCity;
			setModified(true);
		}
	}

	public String getBusinessState() {
		return _businessState;
	}

	public void setBusinessState(String businessState) {
		if (((businessState == null) && (_businessState != null)) ||
				((businessState != null) && (_businessState == null)) ||
				((businessState != null) && (_businessState != null) &&
				!businessState.equals(_businessState))) {
			if (!XSS_ALLOW_BUSINESSSTATE) {
				businessState = Xss.strip(businessState);
			}

			_businessState = businessState;
			setModified(true);
		}
	}

	public String getBusinessZip() {
		return _businessZip;
	}

	public void setBusinessZip(String businessZip) {
		if (((businessZip == null) && (_businessZip != null)) ||
				((businessZip != null) && (_businessZip == null)) ||
				((businessZip != null) && (_businessZip != null) &&
				!businessZip.equals(_businessZip))) {
			if (!XSS_ALLOW_BUSINESSZIP) {
				businessZip = Xss.strip(businessZip);
			}

			_businessZip = businessZip;
			setModified(true);
		}
	}

	public String getBusinessCountry() {
		return _businessCountry;
	}

	public void setBusinessCountry(String businessCountry) {
		if (((businessCountry == null) && (_businessCountry != null)) ||
				((businessCountry != null) && (_businessCountry == null)) ||
				((businessCountry != null) && (_businessCountry != null) &&
				!businessCountry.equals(_businessCountry))) {
			if (!XSS_ALLOW_BUSINESSCOUNTRY) {
				businessCountry = Xss.strip(businessCountry);
			}

			_businessCountry = businessCountry;
			setModified(true);
		}
	}

	public String getBusinessPhone() {
		return _businessPhone;
	}

	public void setBusinessPhone(String businessPhone) {
		if (((businessPhone == null) && (_businessPhone != null)) ||
				((businessPhone != null) && (_businessPhone == null)) ||
				((businessPhone != null) && (_businessPhone != null) &&
				!businessPhone.equals(_businessPhone))) {
			if (!XSS_ALLOW_BUSINESSPHONE) {
				businessPhone = Xss.strip(businessPhone);
			}

			_businessPhone = businessPhone;
			setModified(true);
		}
	}

	public String getBusinessFax() {
		return _businessFax;
	}

	public void setBusinessFax(String businessFax) {
		if (((businessFax == null) && (_businessFax != null)) ||
				((businessFax != null) && (_businessFax == null)) ||
				((businessFax != null) && (_businessFax != null) &&
				!businessFax.equals(_businessFax))) {
			if (!XSS_ALLOW_BUSINESSFAX) {
				businessFax = Xss.strip(businessFax);
			}

			_businessFax = businessFax;
			setModified(true);
		}
	}

	public String getBusinessCell() {
		return _businessCell;
	}

	public void setBusinessCell(String businessCell) {
		if (((businessCell == null) && (_businessCell != null)) ||
				((businessCell != null) && (_businessCell == null)) ||
				((businessCell != null) && (_businessCell != null) &&
				!businessCell.equals(_businessCell))) {
			if (!XSS_ALLOW_BUSINESSCELL) {
				businessCell = Xss.strip(businessCell);
			}

			_businessCell = businessCell;
			setModified(true);
		}
	}

	public String getBusinessPager() {
		return _businessPager;
	}

	public void setBusinessPager(String businessPager) {
		if (((businessPager == null) && (_businessPager != null)) ||
				((businessPager != null) && (_businessPager == null)) ||
				((businessPager != null) && (_businessPager != null) &&
				!businessPager.equals(_businessPager))) {
			if (!XSS_ALLOW_BUSINESSPAGER) {
				businessPager = Xss.strip(businessPager);
			}

			_businessPager = businessPager;
			setModified(true);
		}
	}

	public String getBusinessTollFree() {
		return _businessTollFree;
	}

	public void setBusinessTollFree(String businessTollFree) {
		if (((businessTollFree == null) && (_businessTollFree != null)) ||
				((businessTollFree != null) && (_businessTollFree == null)) ||
				((businessTollFree != null) && (_businessTollFree != null) &&
				!businessTollFree.equals(_businessTollFree))) {
			if (!XSS_ALLOW_BUSINESSTOLLFREE) {
				businessTollFree = Xss.strip(businessTollFree);
			}

			_businessTollFree = businessTollFree;
			setModified(true);
		}
	}

	public String getBusinessEmailAddress() {
		return _businessEmailAddress;
	}

	public void setBusinessEmailAddress(String businessEmailAddress) {
		if (((businessEmailAddress == null) && (_businessEmailAddress != null)) ||
				((businessEmailAddress != null) &&
				(_businessEmailAddress == null)) ||
				((businessEmailAddress != null) &&
				(_businessEmailAddress != null) &&
				!businessEmailAddress.equals(_businessEmailAddress))) {
			if (!XSS_ALLOW_BUSINESSEMAILADDRESS) {
				businessEmailAddress = Xss.strip(businessEmailAddress);
			}

			_businessEmailAddress = businessEmailAddress;
			setModified(true);
		}
	}

	public String getEmployeeNumber() {
		return _employeeNumber;
	}

	public void setEmployeeNumber(String employeeNumber) {
		if (((employeeNumber == null) && (_employeeNumber != null)) ||
				((employeeNumber != null) && (_employeeNumber == null)) ||
				((employeeNumber != null) && (_employeeNumber != null) &&
				!employeeNumber.equals(_employeeNumber))) {
			if (!XSS_ALLOW_EMPLOYEENUMBER) {
				employeeNumber = Xss.strip(employeeNumber);
			}

			_employeeNumber = employeeNumber;
			setModified(true);
		}
	}

	public String getJobTitle() {
		return _jobTitle;
	}

	public void setJobTitle(String jobTitle) {
		if (((jobTitle == null) && (_jobTitle != null)) ||
				((jobTitle != null) && (_jobTitle == null)) ||
				((jobTitle != null) && (_jobTitle != null) &&
				!jobTitle.equals(_jobTitle))) {
			if (!XSS_ALLOW_JOBTITLE) {
				jobTitle = Xss.strip(jobTitle);
			}

			_jobTitle = jobTitle;
			setModified(true);
		}
	}

	public String getJobClass() {
		return _jobClass;
	}

	public void setJobClass(String jobClass) {
		if (((jobClass == null) && (_jobClass != null)) ||
				((jobClass != null) && (_jobClass == null)) ||
				((jobClass != null) && (_jobClass != null) &&
				!jobClass.equals(_jobClass))) {
			if (!XSS_ALLOW_JOBCLASS) {
				jobClass = Xss.strip(jobClass);
			}

			_jobClass = jobClass;
			setModified(true);
		}
	}

	public String getHoursOfOperation() {
		return _hoursOfOperation;
	}

	public void setHoursOfOperation(String hoursOfOperation) {
		if (((hoursOfOperation == null) && (_hoursOfOperation != null)) ||
				((hoursOfOperation != null) && (_hoursOfOperation == null)) ||
				((hoursOfOperation != null) && (_hoursOfOperation != null) &&
				!hoursOfOperation.equals(_hoursOfOperation))) {
			if (!XSS_ALLOW_HOURSOFOPERATION) {
				hoursOfOperation = Xss.strip(hoursOfOperation);
			}

			_hoursOfOperation = hoursOfOperation;
			setModified(true);
		}
	}

	public Date getBirthday() {
		return _birthday;
	}

	public void setBirthday(Date birthday) {
		if (((birthday == null) && (_birthday != null)) ||
				((birthday != null) && (_birthday == null)) ||
				((birthday != null) && (_birthday != null) &&
				!birthday.equals(_birthday))) {
			_birthday = birthday;
			setModified(true);
		}
	}

	public String getTimeZoneId() {
		return _timeZoneId;
	}

	public void setTimeZoneId(String timeZoneId) {
		if (((timeZoneId == null) && (_timeZoneId != null)) ||
				((timeZoneId != null) && (_timeZoneId == null)) ||
				((timeZoneId != null) && (_timeZoneId != null) &&
				!timeZoneId.equals(_timeZoneId))) {
			if (!XSS_ALLOW_TIMEZONEID) {
				timeZoneId = Xss.strip(timeZoneId);
			}

			_timeZoneId = timeZoneId;
			setModified(true);
		}
	}

	public String getInstantMessenger() {
		return _instantMessenger;
	}

	public void setInstantMessenger(String instantMessenger) {
		if (((instantMessenger == null) && (_instantMessenger != null)) ||
				((instantMessenger != null) && (_instantMessenger == null)) ||
				((instantMessenger != null) && (_instantMessenger != null) &&
				!instantMessenger.equals(_instantMessenger))) {
			if (!XSS_ALLOW_INSTANTMESSENGER) {
				instantMessenger = Xss.strip(instantMessenger);
			}

			_instantMessenger = instantMessenger;
			setModified(true);
		}
	}

	public String getWebsite() {
		return _website;
	}

	public void setWebsite(String website) {
		if (((website == null) && (_website != null)) ||
				((website != null) && (_website == null)) ||
				((website != null) && (_website != null) &&
				!website.equals(_website))) {
			if (!XSS_ALLOW_WEBSITE) {
				website = Xss.strip(website);
			}

			_website = website;
			setModified(true);
		}
	}

	public String getComments() {
		return _comments;
	}

	public void setComments(String comments) {
		if (((comments == null) && (_comments != null)) ||
				((comments != null) && (_comments == null)) ||
				((comments != null) && (_comments != null) &&
				!comments.equals(_comments))) {
			if (!XSS_ALLOW_COMMENTS) {
				comments = Xss.strip(comments);
			}

			_comments = comments;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ABContact(getContactId(), getUserId(), getFirstName(),
			getMiddleName(), getLastName(), getNickName(), getEmailAddress(),
			getHomeStreet(), getHomeCity(), getHomeState(), getHomeZip(),
			getHomeCountry(), getHomePhone(), getHomeFax(), getHomeCell(),
			getHomePager(), getHomeTollFree(), getHomeEmailAddress(),
			getBusinessCompany(), getBusinessStreet(), getBusinessCity(),
			getBusinessState(), getBusinessZip(), getBusinessCountry(),
			getBusinessPhone(), getBusinessFax(), getBusinessCell(),
			getBusinessPager(), getBusinessTollFree(),
			getBusinessEmailAddress(), getEmployeeNumber(), getJobTitle(),
			getJobClass(), getHoursOfOperation(), getBirthday(),
			getTimeZoneId(), getInstantMessenger(), getWebsite(), getComments());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ABContact abContact = (ABContact)obj;
		int value = 0;
		value = getFirstName().toLowerCase().compareTo(abContact.getFirstName()
																.toLowerCase());

		if (value != 0) {
			return value;
		}

		value = getLastName().toLowerCase().compareTo(abContact.getLastName()
															   .toLowerCase());

		if (value != 0) {
			return value;
		}

		value = getEmailAddress().toLowerCase().compareTo(abContact.getEmailAddress()
																   .toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ABContact abContact = null;

		try {
			abContact = (ABContact)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = abContact.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _contactId;
	private String _userId;
	private String _firstName;
	private String _middleName;
	private String _lastName;
	private String _nickName;
	private String _emailAddress;
	private String _homeStreet;
	private String _homeCity;
	private String _homeState;
	private String _homeZip;
	private String _homeCountry;
	private String _homePhone;
	private String _homeFax;
	private String _homeCell;
	private String _homePager;
	private String _homeTollFree;
	private String _homeEmailAddress;
	private String _businessCompany;
	private String _businessStreet;
	private String _businessCity;
	private String _businessState;
	private String _businessZip;
	private String _businessCountry;
	private String _businessPhone;
	private String _businessFax;
	private String _businessCell;
	private String _businessPager;
	private String _businessTollFree;
	private String _businessEmailAddress;
	private String _employeeNumber;
	private String _jobTitle;
	private String _jobClass;
	private String _hoursOfOperation;
	private Date _birthday;
	private String _timeZoneId;
	private String _instantMessenger;
	private String _website;
	private String _comments;
}
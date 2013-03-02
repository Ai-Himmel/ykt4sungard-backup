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

package com.liferay.portlet.addressbook.service.persistence;

import java.util.Date;
import java.util.Set;

/**
 * <a href="ABContactHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ABContactHBM {
	protected ABContactHBM() {
	}

	protected ABContactHBM(String contactId) {
		_contactId = contactId;
	}

	protected ABContactHBM(String contactId, String userId, String firstName,
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

	protected void setPrimaryKey(String pk) {
		_contactId = pk;
	}

	protected String getContactId() {
		return _contactId;
	}

	protected void setContactId(String contactId) {
		_contactId = contactId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getFirstName() {
		return _firstName;
	}

	protected void setFirstName(String firstName) {
		_firstName = firstName;
	}

	protected String getMiddleName() {
		return _middleName;
	}

	protected void setMiddleName(String middleName) {
		_middleName = middleName;
	}

	protected String getLastName() {
		return _lastName;
	}

	protected void setLastName(String lastName) {
		_lastName = lastName;
	}

	protected String getNickName() {
		return _nickName;
	}

	protected void setNickName(String nickName) {
		_nickName = nickName;
	}

	protected String getEmailAddress() {
		return _emailAddress;
	}

	protected void setEmailAddress(String emailAddress) {
		_emailAddress = emailAddress;
	}

	protected String getHomeStreet() {
		return _homeStreet;
	}

	protected void setHomeStreet(String homeStreet) {
		_homeStreet = homeStreet;
	}

	protected String getHomeCity() {
		return _homeCity;
	}

	protected void setHomeCity(String homeCity) {
		_homeCity = homeCity;
	}

	protected String getHomeState() {
		return _homeState;
	}

	protected void setHomeState(String homeState) {
		_homeState = homeState;
	}

	protected String getHomeZip() {
		return _homeZip;
	}

	protected void setHomeZip(String homeZip) {
		_homeZip = homeZip;
	}

	protected String getHomeCountry() {
		return _homeCountry;
	}

	protected void setHomeCountry(String homeCountry) {
		_homeCountry = homeCountry;
	}

	protected String getHomePhone() {
		return _homePhone;
	}

	protected void setHomePhone(String homePhone) {
		_homePhone = homePhone;
	}

	protected String getHomeFax() {
		return _homeFax;
	}

	protected void setHomeFax(String homeFax) {
		_homeFax = homeFax;
	}

	protected String getHomeCell() {
		return _homeCell;
	}

	protected void setHomeCell(String homeCell) {
		_homeCell = homeCell;
	}

	protected String getHomePager() {
		return _homePager;
	}

	protected void setHomePager(String homePager) {
		_homePager = homePager;
	}

	protected String getHomeTollFree() {
		return _homeTollFree;
	}

	protected void setHomeTollFree(String homeTollFree) {
		_homeTollFree = homeTollFree;
	}

	protected String getHomeEmailAddress() {
		return _homeEmailAddress;
	}

	protected void setHomeEmailAddress(String homeEmailAddress) {
		_homeEmailAddress = homeEmailAddress;
	}

	protected String getBusinessCompany() {
		return _businessCompany;
	}

	protected void setBusinessCompany(String businessCompany) {
		_businessCompany = businessCompany;
	}

	protected String getBusinessStreet() {
		return _businessStreet;
	}

	protected void setBusinessStreet(String businessStreet) {
		_businessStreet = businessStreet;
	}

	protected String getBusinessCity() {
		return _businessCity;
	}

	protected void setBusinessCity(String businessCity) {
		_businessCity = businessCity;
	}

	protected String getBusinessState() {
		return _businessState;
	}

	protected void setBusinessState(String businessState) {
		_businessState = businessState;
	}

	protected String getBusinessZip() {
		return _businessZip;
	}

	protected void setBusinessZip(String businessZip) {
		_businessZip = businessZip;
	}

	protected String getBusinessCountry() {
		return _businessCountry;
	}

	protected void setBusinessCountry(String businessCountry) {
		_businessCountry = businessCountry;
	}

	protected String getBusinessPhone() {
		return _businessPhone;
	}

	protected void setBusinessPhone(String businessPhone) {
		_businessPhone = businessPhone;
	}

	protected String getBusinessFax() {
		return _businessFax;
	}

	protected void setBusinessFax(String businessFax) {
		_businessFax = businessFax;
	}

	protected String getBusinessCell() {
		return _businessCell;
	}

	protected void setBusinessCell(String businessCell) {
		_businessCell = businessCell;
	}

	protected String getBusinessPager() {
		return _businessPager;
	}

	protected void setBusinessPager(String businessPager) {
		_businessPager = businessPager;
	}

	protected String getBusinessTollFree() {
		return _businessTollFree;
	}

	protected void setBusinessTollFree(String businessTollFree) {
		_businessTollFree = businessTollFree;
	}

	protected String getBusinessEmailAddress() {
		return _businessEmailAddress;
	}

	protected void setBusinessEmailAddress(String businessEmailAddress) {
		_businessEmailAddress = businessEmailAddress;
	}

	protected String getEmployeeNumber() {
		return _employeeNumber;
	}

	protected void setEmployeeNumber(String employeeNumber) {
		_employeeNumber = employeeNumber;
	}

	protected String getJobTitle() {
		return _jobTitle;
	}

	protected void setJobTitle(String jobTitle) {
		_jobTitle = jobTitle;
	}

	protected String getJobClass() {
		return _jobClass;
	}

	protected void setJobClass(String jobClass) {
		_jobClass = jobClass;
	}

	protected String getHoursOfOperation() {
		return _hoursOfOperation;
	}

	protected void setHoursOfOperation(String hoursOfOperation) {
		_hoursOfOperation = hoursOfOperation;
	}

	protected Date getBirthday() {
		return _birthday;
	}

	protected void setBirthday(Date birthday) {
		_birthday = birthday;
	}

	protected String getTimeZoneId() {
		return _timeZoneId;
	}

	protected void setTimeZoneId(String timeZoneId) {
		_timeZoneId = timeZoneId;
	}

	protected String getInstantMessenger() {
		return _instantMessenger;
	}

	protected void setInstantMessenger(String instantMessenger) {
		_instantMessenger = instantMessenger;
	}

	protected String getWebsite() {
		return _website;
	}

	protected void setWebsite(String website) {
		_website = website;
	}

	protected String getComments() {
		return _comments;
	}

	protected void setComments(String comments) {
		_comments = comments;
	}

	protected Set getLists() {
		return _lists;
	}

	protected void setLists(Set lists) {
		_lists = lists;
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
	private Set _lists;
}
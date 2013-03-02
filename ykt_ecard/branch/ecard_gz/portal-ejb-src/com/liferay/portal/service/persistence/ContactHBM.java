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

package com.liferay.portal.service.persistence;

import java.util.Date;

/**
 * <a href="ContactHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ContactHBM {
	protected ContactHBM() {
	}

	protected ContactHBM(String contactId) {
		_contactId = contactId;
	}

	protected ContactHBM(String contactId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate,
		String parentContactId, String firstName, String middleName,
		String lastName, String nickName, String emailAddress1,
		String emailAddress2, String smsId, String aimId, String icqId,
		String msnId, String skypeId, String ymId, String website,
		boolean male, Date birthday, String timeZoneId, String employeeNumber,
		String jobTitle, String jobClass, String hoursOfOperation) {
		_contactId = contactId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_parentContactId = parentContactId;
		_firstName = firstName;
		_middleName = middleName;
		_lastName = lastName;
		_nickName = nickName;
		_emailAddress1 = emailAddress1;
		_emailAddress2 = emailAddress2;
		_smsId = smsId;
		_aimId = aimId;
		_icqId = icqId;
		_msnId = msnId;
		_skypeId = skypeId;
		_ymId = ymId;
		_website = website;
		_male = male;
		_birthday = birthday;
		_timeZoneId = timeZoneId;
		_employeeNumber = employeeNumber;
		_jobTitle = jobTitle;
		_jobClass = jobClass;
		_hoursOfOperation = hoursOfOperation;
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

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getUserName() {
		return _userName;
	}

	protected void setUserName(String userName) {
		_userName = userName;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getParentContactId() {
		return _parentContactId;
	}

	protected void setParentContactId(String parentContactId) {
		_parentContactId = parentContactId;
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

	protected String getEmailAddress1() {
		return _emailAddress1;
	}

	protected void setEmailAddress1(String emailAddress1) {
		_emailAddress1 = emailAddress1;
	}

	protected String getEmailAddress2() {
		return _emailAddress2;
	}

	protected void setEmailAddress2(String emailAddress2) {
		_emailAddress2 = emailAddress2;
	}

	protected String getSmsId() {
		return _smsId;
	}

	protected void setSmsId(String smsId) {
		_smsId = smsId;
	}

	protected String getAimId() {
		return _aimId;
	}

	protected void setAimId(String aimId) {
		_aimId = aimId;
	}

	protected String getIcqId() {
		return _icqId;
	}

	protected void setIcqId(String icqId) {
		_icqId = icqId;
	}

	protected String getMsnId() {
		return _msnId;
	}

	protected void setMsnId(String msnId) {
		_msnId = msnId;
	}

	protected String getSkypeId() {
		return _skypeId;
	}

	protected void setSkypeId(String skypeId) {
		_skypeId = skypeId;
	}

	protected String getYmId() {
		return _ymId;
	}

	protected void setYmId(String ymId) {
		_ymId = ymId;
	}

	protected String getWebsite() {
		return _website;
	}

	protected void setWebsite(String website) {
		_website = website;
	}

	protected boolean getMale() {
		return _male;
	}

	protected void setMale(boolean male) {
		_male = male;
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

	private String _contactId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _parentContactId;
	private String _firstName;
	private String _middleName;
	private String _lastName;
	private String _nickName;
	private String _emailAddress1;
	private String _emailAddress2;
	private String _smsId;
	private String _aimId;
	private String _icqId;
	private String _msnId;
	private String _skypeId;
	private String _ymId;
	private String _website;
	private boolean _male;
	private Date _birthday;
	private String _timeZoneId;
	private String _employeeNumber;
	private String _jobTitle;
	private String _jobClass;
	private String _hoursOfOperation;
}
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

package com.liferay.portal.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="UserSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.UserServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.UserServiceSoap
 *
 */
public class UserSoap implements Serializable {
	public static UserSoap toSoapModel(User model) {
		UserSoap soapModel = new UserSoap();

		soapModel.setUuid(model.getUuid());
		soapModel.setUserId(model.getUserId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setDefaultUser(model.getDefaultUser());
		soapModel.setContactId(model.getContactId());
		soapModel.setPassword(model.getPassword());
		soapModel.setPasswordEncrypted(model.getPasswordEncrypted());
		soapModel.setPasswordReset(model.getPasswordReset());
		soapModel.setPasswordModifiedDate(model.getPasswordModifiedDate());
		soapModel.setGraceLoginCount(model.getGraceLoginCount());
		soapModel.setScreenName(model.getScreenName());
		soapModel.setEmailAddress(model.getEmailAddress());
		soapModel.setPortraitId(model.getPortraitId());
		soapModel.setLanguageId(model.getLanguageId());
		soapModel.setTimeZoneId(model.getTimeZoneId());
		soapModel.setGreeting(model.getGreeting());
		soapModel.setComments(model.getComments());
		soapModel.setLoginDate(model.getLoginDate());
		soapModel.setLoginIP(model.getLoginIP());
		soapModel.setLastLoginDate(model.getLastLoginDate());
		soapModel.setLastLoginIP(model.getLastLoginIP());
		soapModel.setLastFailedLoginDate(model.getLastFailedLoginDate());
		soapModel.setFailedLoginAttempts(model.getFailedLoginAttempts());
		soapModel.setLockout(model.getLockout());
		soapModel.setLockoutDate(model.getLockoutDate());
		soapModel.setAgreedToTermsOfUse(model.getAgreedToTermsOfUse());
		soapModel.setActive(model.getActive());

		return soapModel;
	}

	public static UserSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			User model = (User)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (UserSoap[])soapModels.toArray(new UserSoap[0]);
	}

	public UserSoap() {
	}

	public long getPrimaryKey() {
		return _userId;
	}

	public void setPrimaryKey(long pk) {
		setUserId(pk);
	}

	public String getUuid() {
		return _uuid;
	}

	public void setUuid(String uuid) {
		_uuid = uuid;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	public boolean getDefaultUser() {
		return _defaultUser;
	}

	public boolean isDefaultUser() {
		return _defaultUser;
	}

	public void setDefaultUser(boolean defaultUser) {
		_defaultUser = defaultUser;
	}

	public long getContactId() {
		return _contactId;
	}

	public void setContactId(long contactId) {
		_contactId = contactId;
	}

	public String getPassword() {
		return _password;
	}

	public void setPassword(String password) {
		_password = password;
	}

	public boolean getPasswordEncrypted() {
		return _passwordEncrypted;
	}

	public boolean isPasswordEncrypted() {
		return _passwordEncrypted;
	}

	public void setPasswordEncrypted(boolean passwordEncrypted) {
		_passwordEncrypted = passwordEncrypted;
	}

	public boolean getPasswordReset() {
		return _passwordReset;
	}

	public boolean isPasswordReset() {
		return _passwordReset;
	}

	public void setPasswordReset(boolean passwordReset) {
		_passwordReset = passwordReset;
	}

	public Date getPasswordModifiedDate() {
		return _passwordModifiedDate;
	}

	public void setPasswordModifiedDate(Date passwordModifiedDate) {
		_passwordModifiedDate = passwordModifiedDate;
	}

	public int getGraceLoginCount() {
		return _graceLoginCount;
	}

	public void setGraceLoginCount(int graceLoginCount) {
		_graceLoginCount = graceLoginCount;
	}

	public String getScreenName() {
		return _screenName;
	}

	public void setScreenName(String screenName) {
		_screenName = screenName;
	}

	public String getEmailAddress() {
		return _emailAddress;
	}

	public void setEmailAddress(String emailAddress) {
		_emailAddress = emailAddress;
	}

	public long getPortraitId() {
		return _portraitId;
	}

	public void setPortraitId(long portraitId) {
		_portraitId = portraitId;
	}

	public String getLanguageId() {
		return _languageId;
	}

	public void setLanguageId(String languageId) {
		_languageId = languageId;
	}

	public String getTimeZoneId() {
		return _timeZoneId;
	}

	public void setTimeZoneId(String timeZoneId) {
		_timeZoneId = timeZoneId;
	}

	public String getGreeting() {
		return _greeting;
	}

	public void setGreeting(String greeting) {
		_greeting = greeting;
	}

	public String getComments() {
		return _comments;
	}

	public void setComments(String comments) {
		_comments = comments;
	}

	public Date getLoginDate() {
		return _loginDate;
	}

	public void setLoginDate(Date loginDate) {
		_loginDate = loginDate;
	}

	public String getLoginIP() {
		return _loginIP;
	}

	public void setLoginIP(String loginIP) {
		_loginIP = loginIP;
	}

	public Date getLastLoginDate() {
		return _lastLoginDate;
	}

	public void setLastLoginDate(Date lastLoginDate) {
		_lastLoginDate = lastLoginDate;
	}

	public String getLastLoginIP() {
		return _lastLoginIP;
	}

	public void setLastLoginIP(String lastLoginIP) {
		_lastLoginIP = lastLoginIP;
	}

	public Date getLastFailedLoginDate() {
		return _lastFailedLoginDate;
	}

	public void setLastFailedLoginDate(Date lastFailedLoginDate) {
		_lastFailedLoginDate = lastFailedLoginDate;
	}

	public int getFailedLoginAttempts() {
		return _failedLoginAttempts;
	}

	public void setFailedLoginAttempts(int failedLoginAttempts) {
		_failedLoginAttempts = failedLoginAttempts;
	}

	public boolean getLockout() {
		return _lockout;
	}

	public boolean isLockout() {
		return _lockout;
	}

	public void setLockout(boolean lockout) {
		_lockout = lockout;
	}

	public Date getLockoutDate() {
		return _lockoutDate;
	}

	public void setLockoutDate(Date lockoutDate) {
		_lockoutDate = lockoutDate;
	}

	public boolean getAgreedToTermsOfUse() {
		return _agreedToTermsOfUse;
	}

	public boolean isAgreedToTermsOfUse() {
		return _agreedToTermsOfUse;
	}

	public void setAgreedToTermsOfUse(boolean agreedToTermsOfUse) {
		_agreedToTermsOfUse = agreedToTermsOfUse;
	}

	public boolean getActive() {
		return _active;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		_active = active;
	}

	private String _uuid;
	private long _userId;
	private long _companyId;
	private Date _createDate;
	private Date _modifiedDate;
	private boolean _defaultUser;
	private long _contactId;
	private String _password;
	private boolean _passwordEncrypted;
	private boolean _passwordReset;
	private Date _passwordModifiedDate;
	private int _graceLoginCount;
	private String _screenName;
	private String _emailAddress;
	private long _portraitId;
	private String _languageId;
	private String _timeZoneId;
	private String _greeting;
	private String _comments;
	private Date _loginDate;
	private String _loginIP;
	private Date _lastLoginDate;
	private String _lastLoginIP;
	private Date _lastFailedLoginDate;
	private int _failedLoginAttempts;
	private boolean _lockout;
	private Date _lockoutDate;
	private boolean _agreedToTermsOfUse;
	private boolean _active;
}
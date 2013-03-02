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

import java.util.Date;

/**
 * <a href="UserModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>User</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.User
 * @see com.liferay.portal.service.model.impl.UserImpl
 * @see com.liferay.portal.service.model.impl.UserModelImpl
 *
 */
public interface UserModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public String getUuid();

	public void setUuid(String uuid);

	public long getUserId();

	public void setUserId(long userId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public Date getCreateDate();

	public void setCreateDate(Date createDate);

	public Date getModifiedDate();

	public void setModifiedDate(Date modifiedDate);

	public boolean getDefaultUser();

	public boolean isDefaultUser();

	public void setDefaultUser(boolean defaultUser);

	public long getContactId();

	public void setContactId(long contactId);

	public String getPassword();

	public void setPassword(String password);

	public boolean getPasswordEncrypted();

	public boolean isPasswordEncrypted();

	public void setPasswordEncrypted(boolean passwordEncrypted);

	public boolean getPasswordReset();

	public boolean isPasswordReset();

	public void setPasswordReset(boolean passwordReset);

	public Date getPasswordModifiedDate();

	public void setPasswordModifiedDate(Date passwordModifiedDate);

	public int getGraceLoginCount();

	public void setGraceLoginCount(int graceLoginCount);

	public String getScreenName();

	public void setScreenName(String screenName);

	public String getEmailAddress();

	public void setEmailAddress(String emailAddress);

	public long getPortraitId();

	public void setPortraitId(long portraitId);

	public String getLanguageId();

	public void setLanguageId(String languageId);

	public String getTimeZoneId();

	public void setTimeZoneId(String timeZoneId);

	public String getGreeting();

	public void setGreeting(String greeting);

	public String getComments();

	public void setComments(String comments);

	public Date getLoginDate();

	public void setLoginDate(Date loginDate);

	public String getLoginIP();

	public void setLoginIP(String loginIP);

	public Date getLastLoginDate();

	public void setLastLoginDate(Date lastLoginDate);

	public String getLastLoginIP();

	public void setLastLoginIP(String lastLoginIP);

	public Date getLastFailedLoginDate();

	public void setLastFailedLoginDate(Date lastFailedLoginDate);

	public int getFailedLoginAttempts();

	public void setFailedLoginAttempts(int failedLoginAttempts);

	public boolean getLockout();

	public boolean isLockout();

	public void setLockout(boolean lockout);

	public Date getLockoutDate();

	public void setLockoutDate(Date lockoutDate);

	public boolean getAgreedToTermsOfUse();

	public boolean isAgreedToTermsOfUse();

	public void setAgreedToTermsOfUse(boolean agreedToTermsOfUse);

	public boolean getActive();

	public boolean isActive();

	public void setActive(boolean active);

	public User toEscapedModel();
}
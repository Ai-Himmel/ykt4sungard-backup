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
 * <a href="PasswordPolicyModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>PasswordPolicy</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.PasswordPolicy
 * @see com.liferay.portal.service.model.impl.PasswordPolicyImpl
 * @see com.liferay.portal.service.model.impl.PasswordPolicyModelImpl
 *
 */
public interface PasswordPolicyModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public long getPasswordPolicyId();

	public void setPasswordPolicyId(long passwordPolicyId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public long getUserId();

	public void setUserId(long userId);

	public String getUserName();

	public void setUserName(String userName);

	public Date getCreateDate();

	public void setCreateDate(Date createDate);

	public Date getModifiedDate();

	public void setModifiedDate(Date modifiedDate);

	public boolean getDefaultPolicy();

	public boolean isDefaultPolicy();

	public void setDefaultPolicy(boolean defaultPolicy);

	public String getName();

	public void setName(String name);

	public String getDescription();

	public void setDescription(String description);

	public boolean getChangeable();

	public boolean isChangeable();

	public void setChangeable(boolean changeable);

	public boolean getChangeRequired();

	public boolean isChangeRequired();

	public void setChangeRequired(boolean changeRequired);

	public long getMinAge();

	public void setMinAge(long minAge);

	public boolean getCheckSyntax();

	public boolean isCheckSyntax();

	public void setCheckSyntax(boolean checkSyntax);

	public boolean getAllowDictionaryWords();

	public boolean isAllowDictionaryWords();

	public void setAllowDictionaryWords(boolean allowDictionaryWords);

	public int getMinLength();

	public void setMinLength(int minLength);

	public boolean getHistory();

	public boolean isHistory();

	public void setHistory(boolean history);

	public int getHistoryCount();

	public void setHistoryCount(int historyCount);

	public boolean getExpireable();

	public boolean isExpireable();

	public void setExpireable(boolean expireable);

	public long getMaxAge();

	public void setMaxAge(long maxAge);

	public long getWarningTime();

	public void setWarningTime(long warningTime);

	public int getGraceLimit();

	public void setGraceLimit(int graceLimit);

	public boolean getLockout();

	public boolean isLockout();

	public void setLockout(boolean lockout);

	public int getMaxFailure();

	public void setMaxFailure(int maxFailure);

	public long getLockoutDuration();

	public void setLockoutDuration(long lockoutDuration);

	public boolean getRequireUnlock();

	public boolean isRequireUnlock();

	public void setRequireUnlock(boolean requireUnlock);

	public long getResetFailureCount();

	public void setResetFailureCount(long resetFailureCount);

	public PasswordPolicy toEscapedModel();
}
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
 * <a href="PasswordPolicySoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.PasswordPolicyServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.PasswordPolicyServiceSoap
 *
 */
public class PasswordPolicySoap implements Serializable {
	public static PasswordPolicySoap toSoapModel(PasswordPolicy model) {
		PasswordPolicySoap soapModel = new PasswordPolicySoap();

		soapModel.setPasswordPolicyId(model.getPasswordPolicyId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setDefaultPolicy(model.getDefaultPolicy());
		soapModel.setName(model.getName());
		soapModel.setDescription(model.getDescription());
		soapModel.setChangeable(model.getChangeable());
		soapModel.setChangeRequired(model.getChangeRequired());
		soapModel.setMinAge(model.getMinAge());
		soapModel.setCheckSyntax(model.getCheckSyntax());
		soapModel.setAllowDictionaryWords(model.getAllowDictionaryWords());
		soapModel.setMinLength(model.getMinLength());
		soapModel.setHistory(model.getHistory());
		soapModel.setHistoryCount(model.getHistoryCount());
		soapModel.setExpireable(model.getExpireable());
		soapModel.setMaxAge(model.getMaxAge());
		soapModel.setWarningTime(model.getWarningTime());
		soapModel.setGraceLimit(model.getGraceLimit());
		soapModel.setLockout(model.getLockout());
		soapModel.setMaxFailure(model.getMaxFailure());
		soapModel.setLockoutDuration(model.getLockoutDuration());
		soapModel.setRequireUnlock(model.getRequireUnlock());
		soapModel.setResetFailureCount(model.getResetFailureCount());

		return soapModel;
	}

	public static PasswordPolicySoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			PasswordPolicy model = (PasswordPolicy)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (PasswordPolicySoap[])soapModels.toArray(new PasswordPolicySoap[0]);
	}

	public PasswordPolicySoap() {
	}

	public long getPrimaryKey() {
		return _passwordPolicyId;
	}

	public void setPrimaryKey(long pk) {
		setPasswordPolicyId(pk);
	}

	public long getPasswordPolicyId() {
		return _passwordPolicyId;
	}

	public void setPasswordPolicyId(long passwordPolicyId) {
		_passwordPolicyId = passwordPolicyId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		_userName = userName;
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

	public boolean getDefaultPolicy() {
		return _defaultPolicy;
	}

	public boolean isDefaultPolicy() {
		return _defaultPolicy;
	}

	public void setDefaultPolicy(boolean defaultPolicy) {
		_defaultPolicy = defaultPolicy;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		_description = description;
	}

	public boolean getChangeable() {
		return _changeable;
	}

	public boolean isChangeable() {
		return _changeable;
	}

	public void setChangeable(boolean changeable) {
		_changeable = changeable;
	}

	public boolean getChangeRequired() {
		return _changeRequired;
	}

	public boolean isChangeRequired() {
		return _changeRequired;
	}

	public void setChangeRequired(boolean changeRequired) {
		_changeRequired = changeRequired;
	}

	public long getMinAge() {
		return _minAge;
	}

	public void setMinAge(long minAge) {
		_minAge = minAge;
	}

	public boolean getCheckSyntax() {
		return _checkSyntax;
	}

	public boolean isCheckSyntax() {
		return _checkSyntax;
	}

	public void setCheckSyntax(boolean checkSyntax) {
		_checkSyntax = checkSyntax;
	}

	public boolean getAllowDictionaryWords() {
		return _allowDictionaryWords;
	}

	public boolean isAllowDictionaryWords() {
		return _allowDictionaryWords;
	}

	public void setAllowDictionaryWords(boolean allowDictionaryWords) {
		_allowDictionaryWords = allowDictionaryWords;
	}

	public int getMinLength() {
		return _minLength;
	}

	public void setMinLength(int minLength) {
		_minLength = minLength;
	}

	public boolean getHistory() {
		return _history;
	}

	public boolean isHistory() {
		return _history;
	}

	public void setHistory(boolean history) {
		_history = history;
	}

	public int getHistoryCount() {
		return _historyCount;
	}

	public void setHistoryCount(int historyCount) {
		_historyCount = historyCount;
	}

	public boolean getExpireable() {
		return _expireable;
	}

	public boolean isExpireable() {
		return _expireable;
	}

	public void setExpireable(boolean expireable) {
		_expireable = expireable;
	}

	public long getMaxAge() {
		return _maxAge;
	}

	public void setMaxAge(long maxAge) {
		_maxAge = maxAge;
	}

	public long getWarningTime() {
		return _warningTime;
	}

	public void setWarningTime(long warningTime) {
		_warningTime = warningTime;
	}

	public int getGraceLimit() {
		return _graceLimit;
	}

	public void setGraceLimit(int graceLimit) {
		_graceLimit = graceLimit;
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

	public int getMaxFailure() {
		return _maxFailure;
	}

	public void setMaxFailure(int maxFailure) {
		_maxFailure = maxFailure;
	}

	public long getLockoutDuration() {
		return _lockoutDuration;
	}

	public void setLockoutDuration(long lockoutDuration) {
		_lockoutDuration = lockoutDuration;
	}

	public boolean getRequireUnlock() {
		return _requireUnlock;
	}

	public boolean isRequireUnlock() {
		return _requireUnlock;
	}

	public void setRequireUnlock(boolean requireUnlock) {
		_requireUnlock = requireUnlock;
	}

	public long getResetFailureCount() {
		return _resetFailureCount;
	}

	public void setResetFailureCount(long resetFailureCount) {
		_resetFailureCount = resetFailureCount;
	}

	private long _passwordPolicyId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private boolean _defaultPolicy;
	private String _name;
	private String _description;
	private boolean _changeable;
	private boolean _changeRequired;
	private long _minAge;
	private boolean _checkSyntax;
	private boolean _allowDictionaryWords;
	private int _minLength;
	private boolean _history;
	private int _historyCount;
	private boolean _expireable;
	private long _maxAge;
	private long _warningTime;
	private int _graceLimit;
	private boolean _lockout;
	private int _maxFailure;
	private long _lockoutDuration;
	private boolean _requireUnlock;
	private long _resetFailureCount;
}
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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="PasswordPolicyModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>PasswordPolicy</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.PasswordPolicy
 * @see com.liferay.portal.service.model.PasswordPolicyModel
 * @see com.liferay.portal.service.model.impl.PasswordPolicyImpl
 *
 */
public class PasswordPolicyModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "PasswordPolicy";
	public static final Object[][] TABLE_COLUMNS = {
			{ "passwordPolicyId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "defaultPolicy", new Integer(Types.BOOLEAN) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "changeable", new Integer(Types.BOOLEAN) },
			

			{ "changeRequired", new Integer(Types.BOOLEAN) },
			

			{ "minAge", new Integer(Types.BIGINT) },
			

			{ "checkSyntax", new Integer(Types.BOOLEAN) },
			

			{ "allowDictionaryWords", new Integer(Types.BOOLEAN) },
			

			{ "minLength", new Integer(Types.INTEGER) },
			

			{ "history", new Integer(Types.BOOLEAN) },
			

			{ "historyCount", new Integer(Types.INTEGER) },
			

			{ "expireable", new Integer(Types.BOOLEAN) },
			

			{ "maxAge", new Integer(Types.BIGINT) },
			

			{ "warningTime", new Integer(Types.BIGINT) },
			

			{ "graceLimit", new Integer(Types.INTEGER) },
			

			{ "lockout", new Integer(Types.BOOLEAN) },
			

			{ "maxFailure", new Integer(Types.INTEGER) },
			

			{ "lockoutDuration", new Integer(Types.BIGINT) },
			

			{ "requireUnlock", new Integer(Types.BOOLEAN) },
			

			{ "resetFailureCount", new Integer(Types.BIGINT) }
		};
	public static final String TABLE_SQL_CREATE = "create table PasswordPolicy (passwordPolicyId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,defaultPolicy BOOLEAN,name VARCHAR(75) null,description STRING null,changeable BOOLEAN,changeRequired BOOLEAN,minAge LONG,checkSyntax BOOLEAN,allowDictionaryWords BOOLEAN,minLength INTEGER,history BOOLEAN,historyCount INTEGER,expireable BOOLEAN,maxAge LONG,warningTime LONG,graceLimit INTEGER,lockout BOOLEAN,maxFailure INTEGER,lockoutDuration LONG,requireUnlock BOOLEAN,resetFailureCount LONG)";
	public static final String TABLE_SQL_DROP = "drop table PasswordPolicy";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.PasswordPolicy"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.PasswordPolicy"));

	public PasswordPolicyModelImpl() {
	}

	public long getPrimaryKey() {
		return _passwordPolicyId;
	}

	public void setPrimaryKey(long pk) {
		setPasswordPolicyId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_passwordPolicyId);
	}

	public long getPasswordPolicyId() {
		return _passwordPolicyId;
	}

	public void setPasswordPolicyId(long passwordPolicyId) {
		if (passwordPolicyId != _passwordPolicyId) {
			_passwordPolicyId = passwordPolicyId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public boolean getDefaultPolicy() {
		return _defaultPolicy;
	}

	public boolean isDefaultPolicy() {
		return _defaultPolicy;
	}

	public void setDefaultPolicy(boolean defaultPolicy) {
		if (defaultPolicy != _defaultPolicy) {
			_defaultPolicy = defaultPolicy;
		}
	}

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
		}
	}

	public boolean getChangeable() {
		return _changeable;
	}

	public boolean isChangeable() {
		return _changeable;
	}

	public void setChangeable(boolean changeable) {
		if (changeable != _changeable) {
			_changeable = changeable;
		}
	}

	public boolean getChangeRequired() {
		return _changeRequired;
	}

	public boolean isChangeRequired() {
		return _changeRequired;
	}

	public void setChangeRequired(boolean changeRequired) {
		if (changeRequired != _changeRequired) {
			_changeRequired = changeRequired;
		}
	}

	public long getMinAge() {
		return _minAge;
	}

	public void setMinAge(long minAge) {
		if (minAge != _minAge) {
			_minAge = minAge;
		}
	}

	public boolean getCheckSyntax() {
		return _checkSyntax;
	}

	public boolean isCheckSyntax() {
		return _checkSyntax;
	}

	public void setCheckSyntax(boolean checkSyntax) {
		if (checkSyntax != _checkSyntax) {
			_checkSyntax = checkSyntax;
		}
	}

	public boolean getAllowDictionaryWords() {
		return _allowDictionaryWords;
	}

	public boolean isAllowDictionaryWords() {
		return _allowDictionaryWords;
	}

	public void setAllowDictionaryWords(boolean allowDictionaryWords) {
		if (allowDictionaryWords != _allowDictionaryWords) {
			_allowDictionaryWords = allowDictionaryWords;
		}
	}

	public int getMinLength() {
		return _minLength;
	}

	public void setMinLength(int minLength) {
		if (minLength != _minLength) {
			_minLength = minLength;
		}
	}

	public boolean getHistory() {
		return _history;
	}

	public boolean isHistory() {
		return _history;
	}

	public void setHistory(boolean history) {
		if (history != _history) {
			_history = history;
		}
	}

	public int getHistoryCount() {
		return _historyCount;
	}

	public void setHistoryCount(int historyCount) {
		if (historyCount != _historyCount) {
			_historyCount = historyCount;
		}
	}

	public boolean getExpireable() {
		return _expireable;
	}

	public boolean isExpireable() {
		return _expireable;
	}

	public void setExpireable(boolean expireable) {
		if (expireable != _expireable) {
			_expireable = expireable;
		}
	}

	public long getMaxAge() {
		return _maxAge;
	}

	public void setMaxAge(long maxAge) {
		if (maxAge != _maxAge) {
			_maxAge = maxAge;
		}
	}

	public long getWarningTime() {
		return _warningTime;
	}

	public void setWarningTime(long warningTime) {
		if (warningTime != _warningTime) {
			_warningTime = warningTime;
		}
	}

	public int getGraceLimit() {
		return _graceLimit;
	}

	public void setGraceLimit(int graceLimit) {
		if (graceLimit != _graceLimit) {
			_graceLimit = graceLimit;
		}
	}

	public boolean getLockout() {
		return _lockout;
	}

	public boolean isLockout() {
		return _lockout;
	}

	public void setLockout(boolean lockout) {
		if (lockout != _lockout) {
			_lockout = lockout;
		}
	}

	public int getMaxFailure() {
		return _maxFailure;
	}

	public void setMaxFailure(int maxFailure) {
		if (maxFailure != _maxFailure) {
			_maxFailure = maxFailure;
		}
	}

	public long getLockoutDuration() {
		return _lockoutDuration;
	}

	public void setLockoutDuration(long lockoutDuration) {
		if (lockoutDuration != _lockoutDuration) {
			_lockoutDuration = lockoutDuration;
		}
	}

	public boolean getRequireUnlock() {
		return _requireUnlock;
	}

	public boolean isRequireUnlock() {
		return _requireUnlock;
	}

	public void setRequireUnlock(boolean requireUnlock) {
		if (requireUnlock != _requireUnlock) {
			_requireUnlock = requireUnlock;
		}
	}

	public long getResetFailureCount() {
		return _resetFailureCount;
	}

	public void setResetFailureCount(long resetFailureCount) {
		if (resetFailureCount != _resetFailureCount) {
			_resetFailureCount = resetFailureCount;
		}
	}

	public PasswordPolicy toEscapedModel() {
		if (isEscapedModel()) {
			return (PasswordPolicy)this;
		}
		else {
			PasswordPolicy model = new PasswordPolicyImpl();

			model.setEscapedModel(true);

			model.setPasswordPolicyId(getPasswordPolicyId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setDefaultPolicy(getDefaultPolicy());
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));
			model.setChangeable(getChangeable());
			model.setChangeRequired(getChangeRequired());
			model.setMinAge(getMinAge());
			model.setCheckSyntax(getCheckSyntax());
			model.setAllowDictionaryWords(getAllowDictionaryWords());
			model.setMinLength(getMinLength());
			model.setHistory(getHistory());
			model.setHistoryCount(getHistoryCount());
			model.setExpireable(getExpireable());
			model.setMaxAge(getMaxAge());
			model.setWarningTime(getWarningTime());
			model.setGraceLimit(getGraceLimit());
			model.setLockout(getLockout());
			model.setMaxFailure(getMaxFailure());
			model.setLockoutDuration(getLockoutDuration());
			model.setRequireUnlock(getRequireUnlock());
			model.setResetFailureCount(getResetFailureCount());

			model = (PasswordPolicy)Proxy.newProxyInstance(PasswordPolicy.class.getClassLoader(),
					new Class[] { PasswordPolicy.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		PasswordPolicyImpl clone = new PasswordPolicyImpl();

		clone.setPasswordPolicyId(getPasswordPolicyId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setDefaultPolicy(getDefaultPolicy());
		clone.setName(getName());
		clone.setDescription(getDescription());
		clone.setChangeable(getChangeable());
		clone.setChangeRequired(getChangeRequired());
		clone.setMinAge(getMinAge());
		clone.setCheckSyntax(getCheckSyntax());
		clone.setAllowDictionaryWords(getAllowDictionaryWords());
		clone.setMinLength(getMinLength());
		clone.setHistory(getHistory());
		clone.setHistoryCount(getHistoryCount());
		clone.setExpireable(getExpireable());
		clone.setMaxAge(getMaxAge());
		clone.setWarningTime(getWarningTime());
		clone.setGraceLimit(getGraceLimit());
		clone.setLockout(getLockout());
		clone.setMaxFailure(getMaxFailure());
		clone.setLockoutDuration(getLockoutDuration());
		clone.setRequireUnlock(getRequireUnlock());
		clone.setResetFailureCount(getResetFailureCount());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PasswordPolicyImpl passwordPolicy = (PasswordPolicyImpl)obj;

		long pk = passwordPolicy.getPrimaryKey();

		if (getPrimaryKey() < pk) {
			return -1;
		}
		else if (getPrimaryKey() > pk) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		PasswordPolicyImpl passwordPolicy = null;

		try {
			passwordPolicy = (PasswordPolicyImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = passwordPolicy.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
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
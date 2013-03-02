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
import com.liferay.portal.model.Account;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="AccountModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Account</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Account
 * @see com.liferay.portal.service.model.AccountModel
 * @see com.liferay.portal.service.model.impl.AccountImpl
 *
 */
public class AccountModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Account_";
	public static final Object[][] TABLE_COLUMNS = {
			{ "accountId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "parentAccountId", new Integer(Types.BIGINT) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "legalName", new Integer(Types.VARCHAR) },
			

			{ "legalId", new Integer(Types.VARCHAR) },
			

			{ "legalType", new Integer(Types.VARCHAR) },
			

			{ "sicCode", new Integer(Types.VARCHAR) },
			

			{ "tickerSymbol", new Integer(Types.VARCHAR) },
			

			{ "industry", new Integer(Types.VARCHAR) },
			

			{ "type_", new Integer(Types.VARCHAR) },
			

			{ "size_", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table Account_ (accountId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,parentAccountId LONG,name VARCHAR(75) null,legalName VARCHAR(75) null,legalId VARCHAR(75) null,legalType VARCHAR(75) null,sicCode VARCHAR(75) null,tickerSymbol VARCHAR(75) null,industry VARCHAR(75) null,type_ VARCHAR(75) null,size_ VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table Account_";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Account"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Account"));

	public AccountModelImpl() {
	}

	public long getPrimaryKey() {
		return _accountId;
	}

	public void setPrimaryKey(long pk) {
		setAccountId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_accountId);
	}

	public long getAccountId() {
		return _accountId;
	}

	public void setAccountId(long accountId) {
		if (accountId != _accountId) {
			_accountId = accountId;
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

	public long getParentAccountId() {
		return _parentAccountId;
	}

	public void setParentAccountId(long parentAccountId) {
		if (parentAccountId != _parentAccountId) {
			_parentAccountId = parentAccountId;
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

	public String getLegalName() {
		return GetterUtil.getString(_legalName);
	}

	public void setLegalName(String legalName) {
		if (((legalName == null) && (_legalName != null)) ||
				((legalName != null) && (_legalName == null)) ||
				((legalName != null) && (_legalName != null) &&
				!legalName.equals(_legalName))) {
			_legalName = legalName;
		}
	}

	public String getLegalId() {
		return GetterUtil.getString(_legalId);
	}

	public void setLegalId(String legalId) {
		if (((legalId == null) && (_legalId != null)) ||
				((legalId != null) && (_legalId == null)) ||
				((legalId != null) && (_legalId != null) &&
				!legalId.equals(_legalId))) {
			_legalId = legalId;
		}
	}

	public String getLegalType() {
		return GetterUtil.getString(_legalType);
	}

	public void setLegalType(String legalType) {
		if (((legalType == null) && (_legalType != null)) ||
				((legalType != null) && (_legalType == null)) ||
				((legalType != null) && (_legalType != null) &&
				!legalType.equals(_legalType))) {
			_legalType = legalType;
		}
	}

	public String getSicCode() {
		return GetterUtil.getString(_sicCode);
	}

	public void setSicCode(String sicCode) {
		if (((sicCode == null) && (_sicCode != null)) ||
				((sicCode != null) && (_sicCode == null)) ||
				((sicCode != null) && (_sicCode != null) &&
				!sicCode.equals(_sicCode))) {
			_sicCode = sicCode;
		}
	}

	public String getTickerSymbol() {
		return GetterUtil.getString(_tickerSymbol);
	}

	public void setTickerSymbol(String tickerSymbol) {
		if (((tickerSymbol == null) && (_tickerSymbol != null)) ||
				((tickerSymbol != null) && (_tickerSymbol == null)) ||
				((tickerSymbol != null) && (_tickerSymbol != null) &&
				!tickerSymbol.equals(_tickerSymbol))) {
			_tickerSymbol = tickerSymbol;
		}
	}

	public String getIndustry() {
		return GetterUtil.getString(_industry);
	}

	public void setIndustry(String industry) {
		if (((industry == null) && (_industry != null)) ||
				((industry != null) && (_industry == null)) ||
				((industry != null) && (_industry != null) &&
				!industry.equals(_industry))) {
			_industry = industry;
		}
	}

	public String getType() {
		return GetterUtil.getString(_type);
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			_type = type;
		}
	}

	public String getSize() {
		return GetterUtil.getString(_size);
	}

	public void setSize(String size) {
		if (((size == null) && (_size != null)) ||
				((size != null) && (_size == null)) ||
				((size != null) && (_size != null) && !size.equals(_size))) {
			_size = size;
		}
	}

	public Account toEscapedModel() {
		if (isEscapedModel()) {
			return (Account)this;
		}
		else {
			Account model = new AccountImpl();

			model.setEscapedModel(true);

			model.setAccountId(getAccountId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setParentAccountId(getParentAccountId());
			model.setName(Html.escape(getName()));
			model.setLegalName(Html.escape(getLegalName()));
			model.setLegalId(Html.escape(getLegalId()));
			model.setLegalType(Html.escape(getLegalType()));
			model.setSicCode(Html.escape(getSicCode()));
			model.setTickerSymbol(Html.escape(getTickerSymbol()));
			model.setIndustry(Html.escape(getIndustry()));
			model.setType(Html.escape(getType()));
			model.setSize(Html.escape(getSize()));

			model = (Account)Proxy.newProxyInstance(Account.class.getClassLoader(),
					new Class[] { Account.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		AccountImpl clone = new AccountImpl();

		clone.setAccountId(getAccountId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setParentAccountId(getParentAccountId());
		clone.setName(getName());
		clone.setLegalName(getLegalName());
		clone.setLegalId(getLegalId());
		clone.setLegalType(getLegalType());
		clone.setSicCode(getSicCode());
		clone.setTickerSymbol(getTickerSymbol());
		clone.setIndustry(getIndustry());
		clone.setType(getType());
		clone.setSize(getSize());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		AccountImpl account = (AccountImpl)obj;

		long pk = account.getPrimaryKey();

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

		AccountImpl account = null;

		try {
			account = (AccountImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = account.getPrimaryKey();

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

	private long _accountId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _parentAccountId;
	private String _name;
	private String _legalName;
	private String _legalId;
	private String _legalType;
	private String _sicCode;
	private String _tickerSymbol;
	private String _industry;
	private String _type;
	private String _size;
}
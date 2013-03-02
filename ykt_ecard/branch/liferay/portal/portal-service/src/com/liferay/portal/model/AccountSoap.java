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
 * <a href="AccountSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.AccountServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.AccountServiceSoap
 *
 */
public class AccountSoap implements Serializable {
	public static AccountSoap toSoapModel(Account model) {
		AccountSoap soapModel = new AccountSoap();

		soapModel.setAccountId(model.getAccountId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setParentAccountId(model.getParentAccountId());
		soapModel.setName(model.getName());
		soapModel.setLegalName(model.getLegalName());
		soapModel.setLegalId(model.getLegalId());
		soapModel.setLegalType(model.getLegalType());
		soapModel.setSicCode(model.getSicCode());
		soapModel.setTickerSymbol(model.getTickerSymbol());
		soapModel.setIndustry(model.getIndustry());
		soapModel.setType(model.getType());
		soapModel.setSize(model.getSize());

		return soapModel;
	}

	public static AccountSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			Account model = (Account)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (AccountSoap[])soapModels.toArray(new AccountSoap[0]);
	}

	public AccountSoap() {
	}

	public long getPrimaryKey() {
		return _accountId;
	}

	public void setPrimaryKey(long pk) {
		setAccountId(pk);
	}

	public long getAccountId() {
		return _accountId;
	}

	public void setAccountId(long accountId) {
		_accountId = accountId;
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

	public long getParentAccountId() {
		return _parentAccountId;
	}

	public void setParentAccountId(long parentAccountId) {
		_parentAccountId = parentAccountId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getLegalName() {
		return _legalName;
	}

	public void setLegalName(String legalName) {
		_legalName = legalName;
	}

	public String getLegalId() {
		return _legalId;
	}

	public void setLegalId(String legalId) {
		_legalId = legalId;
	}

	public String getLegalType() {
		return _legalType;
	}

	public void setLegalType(String legalType) {
		_legalType = legalType;
	}

	public String getSicCode() {
		return _sicCode;
	}

	public void setSicCode(String sicCode) {
		_sicCode = sicCode;
	}

	public String getTickerSymbol() {
		return _tickerSymbol;
	}

	public void setTickerSymbol(String tickerSymbol) {
		_tickerSymbol = tickerSymbol;
	}

	public String getIndustry() {
		return _industry;
	}

	public void setIndustry(String industry) {
		_industry = industry;
	}

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		_type = type;
	}

	public String getSize() {
		return _size;
	}

	public void setSize(String size) {
		_size = size;
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
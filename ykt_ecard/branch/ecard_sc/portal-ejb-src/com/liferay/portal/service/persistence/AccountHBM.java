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
 * <a href="AccountHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class AccountHBM {
	protected AccountHBM() {
	}

	protected AccountHBM(String accountId) {
		_accountId = accountId;
	}

	protected AccountHBM(String accountId, String companyId, String userId,
		String userName, Date createDate, Date modifiedDate,
		String parentAccountId, String name, String legalName, String legalId,
		String legalType, String sicCode, String tickerSymbol, String industry,
		String type, String size, String website, String emailAddress1,
		String emailAddress2) {
		_accountId = accountId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_parentAccountId = parentAccountId;
		_name = name;
		_legalName = legalName;
		_legalId = legalId;
		_legalType = legalType;
		_sicCode = sicCode;
		_tickerSymbol = tickerSymbol;
		_industry = industry;
		_type = type;
		_size = size;
		_website = website;
		_emailAddress1 = emailAddress1;
		_emailAddress2 = emailAddress2;
	}

	public String getPrimaryKey() {
		return _accountId;
	}

	protected void setPrimaryKey(String pk) {
		_accountId = pk;
	}

	protected String getAccountId() {
		return _accountId;
	}

	protected void setAccountId(String accountId) {
		_accountId = accountId;
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

	protected String getParentAccountId() {
		return _parentAccountId;
	}

	protected void setParentAccountId(String parentAccountId) {
		_parentAccountId = parentAccountId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getLegalName() {
		return _legalName;
	}

	protected void setLegalName(String legalName) {
		_legalName = legalName;
	}

	protected String getLegalId() {
		return _legalId;
	}

	protected void setLegalId(String legalId) {
		_legalId = legalId;
	}

	protected String getLegalType() {
		return _legalType;
	}

	protected void setLegalType(String legalType) {
		_legalType = legalType;
	}

	protected String getSicCode() {
		return _sicCode;
	}

	protected void setSicCode(String sicCode) {
		_sicCode = sicCode;
	}

	protected String getTickerSymbol() {
		return _tickerSymbol;
	}

	protected void setTickerSymbol(String tickerSymbol) {
		_tickerSymbol = tickerSymbol;
	}

	protected String getIndustry() {
		return _industry;
	}

	protected void setIndustry(String industry) {
		_industry = industry;
	}

	protected String getType() {
		return _type;
	}

	protected void setType(String type) {
		_type = type;
	}

	protected String getSize() {
		return _size;
	}

	protected void setSize(String size) {
		_size = size;
	}

	protected String getWebsite() {
		return _website;
	}

	protected void setWebsite(String website) {
		_website = website;
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

	private String _accountId;
	private String _companyId;
	private String _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _parentAccountId;
	private String _name;
	private String _legalName;
	private String _legalId;
	private String _legalType;
	private String _sicCode;
	private String _tickerSymbol;
	private String _industry;
	private String _type;
	private String _size;
	private String _website;
	private String _emailAddress1;
	private String _emailAddress2;
}
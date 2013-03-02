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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.service.AccountLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;

import java.security.Key;

import java.util.Locale;
import java.util.TimeZone;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CompanyImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CompanyImpl extends CompanyModelImpl implements Company {

	public static final String DEFAULT_WEB_ID =
		PropsUtil.get(PropsUtil.COMPANY_DEFAULT_WEB_ID);

	public static final String AUTH_TYPE_EA = "emailAddress";

	public static final String AUTH_TYPE_SN = "screenName";

	public static final String AUTH_TYPE_ID = "userId";

	public static final long SYSTEM = 0;

	public static final String SYSTEM_STRING = String.valueOf(SYSTEM);

	public CompanyImpl() {
	}

	public void setKey(String key) {
		_keyObj = null;

		super.setKey(key);
	}

	public Key getKeyObj() {
		if (_keyObj == null) {
			String key = getKey();

			if (Validator.isNotNull(key)) {
				_keyObj = (Key)Base64.stringToObject(key);
			}
		}

		return _keyObj;
	}

	public void setKeyObj(Key keyObj) {
		_keyObj = keyObj;

		super.setKey(Base64.objectToString(keyObj));
	}

	public Account getAccount() {
		Account account = null;

		try {
			account = AccountLocalServiceUtil.getAccount(getAccountId());
		}
		catch (Exception e) {
			account = new AccountImpl();

			_log.error(e);
		}

		return account;
	}

	public String getName() {
		return getAccount().getName();
	}

	public String getShortName() {
		return getName();
	}

	public String getEmailAddress() {

		// Primary email address

		return "admin@" + getMx();
	}

	public User getDefaultUser() {
		User defaultUser = null;

		try {
			defaultUser = UserLocalServiceUtil.getDefaultUser(getCompanyId());
		}
		catch (Exception e) {
			_log.error(e);
		}

		return defaultUser;
	}

	public Locale getLocale() {
		return getDefaultUser().getLocale();
	}

	public TimeZone getTimeZone() {
		return getDefaultUser().getTimeZone();
	}

	public String getAdminName() {
		return "Administrator";
	}

	public String getAuthType() throws PortalException, SystemException {
		return PrefsPropsUtil.getString(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_AUTH_TYPE,
			PropsValues.COMPANY_SECURITY_AUTH_TYPE);
	}

	public boolean isAutoLogin() throws PortalException, SystemException {
		return PrefsPropsUtil.getBoolean(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_AUTO_LOGIN,
			PropsValues.COMPANY_SECURITY_AUTO_LOGIN);
	}

	public boolean isSendPassword() throws PortalException, SystemException {
		return PrefsPropsUtil.getBoolean(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_SEND_PASSWORD,
			PropsValues.COMPANY_SECURITY_SEND_PASSWORD);
	}

	public boolean isStrangers() throws PortalException, SystemException {
		return PrefsPropsUtil.getBoolean(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_STRANGERS,
			PropsValues.COMPANY_SECURITY_STRANGERS);
	}

	public boolean isStrangersWithMx() throws PortalException, SystemException {
		return PrefsPropsUtil.getBoolean(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_STRANGERS_WITH_MX,
			PropsValues.COMPANY_SECURITY_STRANGERS_WITH_MX);
	}

	public boolean isStrangersVerify() throws PortalException, SystemException {
		return PrefsPropsUtil.getBoolean(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_STRANGERS_VERIFY,
			PropsValues.COMPANY_SECURITY_STRANGERS_VERIFY);
	}

	public boolean isCommunityLogo() throws PortalException, SystemException {
		return PrefsPropsUtil.getBoolean(
			getCompanyId(), PropsUtil.COMPANY_SECURITY_COMMUNITY_LOGO,
			PropsValues.COMPANY_SECURITY_COMMUNITY_LOGO);
	}

	public boolean hasCompanyMx(String emailAddress) {
		emailAddress = emailAddress.trim().toLowerCase();

		int pos = emailAddress.indexOf(StringPool.AT);

		if (pos == -1) {
			return false;
		}

		String mx = emailAddress.substring(pos + 1, emailAddress.length());

		if (mx.equals(getMx())) {
			return true;
		}

		try {
			String[] mailHostNames = PrefsPropsUtil.getStringArray(
				getCompanyId(), PropsUtil.ADMIN_MAIL_HOST_NAMES,
				StringPool.NEW_LINE, PropsValues.ADMIN_MAIL_HOST_NAMES);

			for (int i = 0; i < mailHostNames.length; i++) {
				if (mx.equalsIgnoreCase(mailHostNames[i])) {
					return true;
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return false;
	}

	public int compareTo(Object obj) {
		Company company = (Company)obj;

		String webId1 = getWebId();
		String webId2 = company.getWebId();

		if (webId1.equals(DEFAULT_WEB_ID)) {
			return -1;
		}
		else if (webId2.equals(DEFAULT_WEB_ID)) {
			return 1;
		}
		else {
			return webId1.compareTo(webId2);
		}
	}

	private static Log _log = LogFactory.getLog(CompanyImpl.class);

	private Key _keyObj = null;

}
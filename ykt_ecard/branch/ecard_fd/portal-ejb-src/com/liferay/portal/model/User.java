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

package com.liferay.portal.model;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.spring.AddressServiceUtil;
import com.liferay.portal.service.spring.ColorSchemeServiceUtil;
import com.liferay.portal.service.spring.CompanyServiceUtil;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.ThemeServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.Recipient;
import com.liferay.portlet.admin.model.UserConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.LocaleUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="User.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.41 $
 *
 */
public class User extends UserModel implements Recipient {

	public static final String DEFAULT = "default";

	public static String getDefaultUserId(String companyId) {
		return companyId + "." + DEFAULT;
	}

	public static String getFullName(
		String firstName, String middleName, String lastName) {

		if (Validator.isNull(middleName)) {
			return firstName + StringPool.SPACE + lastName;
		}
		else {
			return firstName + StringPool.SPACE + middleName +
				StringPool.SPACE + lastName;
		}
	}

	public static boolean isLayoutsRequired(String userId) {
		boolean universalPersonalization = GetterUtil.get(
			PropsUtil.get(PropsUtil.UNIVERSAL_PERSONALIZATION), false);

		boolean powerUser = true;

		try {
			if (!universalPersonalization) {
				powerUser = RoleLocalServiceUtil.isPowerUser(userId);
			}
		}
		catch (Exception e) {
			_log.warn(e.getMessage());

			powerUser = false;
		}

		return powerUser;
	}

	public User() {
		super();
	}

	public User(String userId) {
		super(userId);
	}

	public User(String userId, String companyId, String password,
				boolean passwordEncrypted, Date passwordExpirationDate,
				boolean passwordReset, String firstName, String middleName,
				String lastName, String nickName, boolean male, Date birthday,
				String emailAddress, String smsId, String aimId, String icqId,
				String msnId, String ymId, String favoriteActivity,
				String favoriteBibleVerse, String favoriteFood,
				String favoriteMovie, String favoriteMusic, String languageId,
				String timeZoneId, String themeId, String colorSchemeId,
				String greeting, String resolution, String comments,
				Date createDate, Date loginDate, String loginIP,
				Date lastLoginDate, String lastLoginIP, int failedLoginAttempts,
				boolean agreedToTermsOfUse, boolean active) {

		super(userId, companyId, password, passwordEncrypted,
			  passwordExpirationDate, passwordReset, firstName, middleName,
			  lastName, nickName, male, birthday, emailAddress, smsId, aimId,
			  icqId, msnId, ymId, favoriteActivity, favoriteBibleVerse,
			  favoriteFood, favoriteMovie, favoriteMusic, languageId,
			  timeZoneId, themeId, colorSchemeId, greeting, resolution,
			  comments, createDate, loginDate, loginIP, lastLoginDate,
			  lastLoginIP, failedLoginAttempts, agreedToTermsOfUse, active);

		setCompanyId(companyId);
		setLanguageId(languageId);
		setTimeZoneId(timeZoneId);
		setResolution(resolution);
	}

	public boolean isDefaultUser() {
		return _defaultUser;
	}

	public void setCompanyId(String companyId) {
		if (companyId.equalsIgnoreCase(DEFAULT)) {
			_defaultUser = true;
		}
		else {
			_defaultUser = false;
		}

		super.setCompanyId(companyId);
	}

	public String getActualCompanyId() {
		if (isDefaultUser()) {
			return getUserId().substring(
				0, getUserId().indexOf(User.DEFAULT) - 1);
		}
		else {
			return getCompanyId();
		}
	}

	public String getCompanyMx() {
		String companyMx = null;

		try {
			companyMx =
				CompanyServiceUtil.getCompany(getCompanyId()).getMx();
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return companyMx;
	}

	public boolean hasCompanyMx() {
		return hasCompanyMx(getEmailAddress());
	}

	public boolean hasCompanyMx(String emailAddress) {
		String mx = emailAddress.substring(
			emailAddress.indexOf('@') + 1, emailAddress.length());

		if (mx.equals(getCompanyMx())) {
			return true;
		}

		try {
			UserConfig userConfig =
				AdminConfigServiceUtil.getUserConfig(getCompanyId());

			if (userConfig.hasMailHostName(mx)) {
				return true;
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return false;
	}

	public boolean isPasswordExpired() {
		if (getPasswordExpirationDate() != null &&
			getPasswordExpirationDate().before(new Date())) {

			return true;
		}
		else {
			return false;
		}
	}
	

	public String getFullName() {
		return getFullName(getFirstName(), getMiddleName(), getLastName());
	}

	public boolean getFemale() {
		return !getMale();
	}

	public boolean isFemale() {
		return !isMale();
	}

	public void setFemale(boolean female) {
		super.setMale(!female);
	}

	public Locale getLocale() {
		return _locale;
	}

	public void setLanguageId(String languageId) {
		_locale = LocaleUtil.fromLanguageId(languageId);

		super.setLanguageId(LocaleUtil.toLanguageId(_locale));
	}

	public TimeZone getTimeZone() {
		return _timeZone;
	}

	public void setTimeZoneId(String timeZoneId) {
		if (Validator.isNull(timeZoneId)) {
			timeZoneId = TimeZone.getDefault().getID();
		}

		_timeZone = TimeZone.getTimeZone(timeZoneId);

		super.setTimeZoneId(timeZoneId);
	}

	public Theme getTheme() throws SystemException {
		return ThemeServiceUtil.getTheme(getThemeId());
	}

	public ColorScheme getColorScheme() throws SystemException {
		return ColorSchemeServiceUtil.getColorScheme(
			getThemeId(), getColorSchemeId());
	}

	public boolean hasCustomColorScheme() {
		if (getUserId().equals(getColorSchemeId())) {
			return true;
		}
		else {
			return false;
		}
	}

	public void setResolution(String resolution) {
		if (Validator.isNull(resolution)) {
			resolution = PropsUtil.get(
				PropsUtil.DEFAULT_USER_LAYOUT_RESOLUTION);
		}

		super.setResolution(resolution);
	}

	public boolean hasLayouts() {
		try {
			int layoutsSize = UserLocalServiceUtil.getLayoutsSize(getUserId());

			if (layoutsSize > 0) {
				return true;
			}
			else {
				return false;
			}
		}
		catch (SystemException se) {
			_log.warn(se.getMessage());

			return false;
		}
	}

	public boolean isLayoutsRequired() {
		return isLayoutsRequired(getUserId());
	}

	public boolean hasGroupLayouts() {
		boolean hasGroupLayouts = false;

		try {
			List groups = UserLocalServiceUtil.getGroups(getUserId());

			for (int i = 0; i < groups.size(); i++) {
				Group group = (Group)groups.get(i);

				int layoutsSize =
					GroupLocalServiceUtil.getLayoutsSize(group.getGroupId());

				if (layoutsSize > 0) {
					hasGroupLayouts = true;

					break;
				}
			}
		}
		catch (Exception e) {
			_log.warn(e.getMessage());
		}

		return hasGroupLayouts;
	}

	public Address getPrimaryAddress() throws PortalException, SystemException {
		return AddressServiceUtil.getPrimaryAddress(
			User.class.getName(), getUserId());
	}

	public List getAddresses() throws PortalException, SystemException {
		return AddressServiceUtil.getAddresses(
			User.class.getName(), getUserId());
	}

	public BaseModel getProtected() {
		if (_user == null) {
			protect();
		}

		return _user;
	}

	public void protect() {
		_user = (User)this.clone();

		_user.setPassword(null);
		_user.setCreateDate(null);
		_user.setLoginDate(null);
		_user.setLoginIP(null);
		_user.setLastLoginDate(null);
		_user.setLastLoginIP(null);
		_user.setFailedLoginAttempts(0);
		_user.setAgreedToTermsOfUse(false);
		_user.setActive(false);
	}

	public String getRecipientId() {
		return getUserId();
	}

	public String getRecipientName() {
		return StringUtil.replace(
			getFullName(),
			new String[] {
				StringPool.COLON, StringPool.COMMA
			},
			new String[] {
				StringPool.BLANK, StringPool.BLANK
			});
	}

	public String getRecipientAddress() {
		return getEmailAddress();
	}

	public String getRecipientInternetAddress() {
		return getRecipientName() + " <" + getEmailAddress() + ">";
	}

	public boolean isMultipleRecipients() {
		return false;
	}

	public int compareTo(Object obj) {
		User user = (User)obj;

		return getFullName().toLowerCase().compareTo(
			user.getFullName().toLowerCase());
	}

	private Group _getGeneralGuestGroup()
		throws PortalException, SystemException {

		return GroupLocalServiceUtil.getGroupByName(
			getActualCompanyId(), Group.GENERAL_GUEST);
	}

	private static final Log _log = LogFactory.getLog(User.class);

	private boolean _defaultUser;
	private Locale _locale;
	private TimeZone _timeZone;
	private User _user;

}
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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.CompanyUtil;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.RoleUtil;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.CompanyLocalService;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.Encryptor;
import com.liferay.util.EncryptorException;
import com.liferay.util.StringPool;

import java.security.Key;

import java.util.Date;
import java.util.List;

/**
 * <a href="CompanyLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class CompanyLocalServiceImpl implements CompanyLocalService {

	// Business methods

	public void checkCompany(String companyId)
		throws PortalException, SystemException {

		// Company

		Company company = null;

		try {
			company = CompanyUtil.findByPrimaryKey(companyId);
		}
		catch (NoSuchCompanyException nsce) {
			company = CompanyUtil.create(companyId);

			company.setPortalURL("localhost");
			company.setHomeURL("localhost");
			company.setMx(companyId);
			company.setName(companyId);
			company.setShortName(companyId);
			company.setType("biz");
			company.setEmailAddress("test@" + companyId);

			CompanyUtil.update(company);
		}

		// Key

		checkCompanyKey(companyId);

		// Groups

		GroupLocalServiceUtil.checkSystemGroups(companyId);

		// Roles

		RoleLocalServiceUtil.checkSystemRoles(companyId);

		// Default user

		User defaultUser = null;

		try {
			defaultUser = UserLocalServiceUtil.getDefaultUser(companyId);
		}
		catch (NoSuchUserException nsue) {
			defaultUser = UserUtil.create(User.getDefaultUserId(companyId));

			Date now = new Date();

			defaultUser.setCompanyId(User.DEFAULT);
			defaultUser.setCreateDate(now);
			defaultUser.setPassword("password");
			defaultUser.setFirstName(StringPool.BLANK);
			defaultUser.setMiddleName(StringPool.BLANK);
			defaultUser.setLastName(StringPool.BLANK);
			defaultUser.setMale(true);
			defaultUser.setBirthday(now);
			defaultUser.setEmailAddress(User.DEFAULT + "@" + company.getMx());

			defaultUser.setLanguageId(null);
			defaultUser.setTimeZoneId(null);
			defaultUser.setThemeId(Theme.DEFAULT_THEME_ID);
			defaultUser.setColorSchemeId(ColorScheme.DEFAULT_COLOR_SCHEME_ID);
			defaultUser.setGreeting("Welcome!");
			defaultUser.setResolution(
				PropsUtil.get(PropsUtil.DEFAULT_GUEST_LAYOUT_RESOLUTION));
			defaultUser.setLoginDate(now);
			defaultUser.setFailedLoginAttempts(0);
			defaultUser.setAgreedToTermsOfUse(false);
			defaultUser.setActive(true);

			UserUtil.update(defaultUser);
		}

		// Default admin

		if (countUsers(companyId) == 0) {
			Date now = new Date();

			User user = UserLocalServiceUtil.addUser(
				companyId, true, StringPool.BLANK, false, "test", "test", false,
				"Test", StringPool.BLANK, "Test", StringPool.BLANK, true, now,
				"test@" + company.getMx(), defaultUser.getLocale());

			Role adminRole = RoleLocalServiceUtil.getRoleByName(
				companyId, Role.ADMINISTRATOR);

			String[] roleIds = new String[] {adminRole.getRoleId()};

			UserLocalServiceUtil.setRoles(user.getUserId(), roleIds);
		}
	}

	public void checkCompanyKey(String companyId)
		throws PortalException, SystemException {

		try {
			Company company = CompanyUtil.findByPrimaryKey(companyId);

			if (company.getKeyObj() == null) {
				Key key = Encryptor.generateKey();

				company.setKeyObj(Encryptor.generateKey());
			}

			CompanyUtil.update(company);
		}
		catch (EncryptorException ee) {
			throw new SystemException(ee);
		}
	}

	public int countUsers(String companyId) throws SystemException {
		return UserUtil.countByCompanyId(companyId);
	}

	public List getCompanies() throws SystemException {
		return CompanyUtil.findAll();
	}

	public Company getCompany(String companyId)
		throws PortalException, SystemException {

		return CompanyUtil.findByPrimaryKey(companyId);
	}

	public List getGroups(String companyId) throws SystemException {
		return GroupUtil.findByCompanyId(companyId);
	}

	public List getRoles(String companyId) throws SystemException {
		return RoleUtil.findByCompanyId(companyId);
	}

	public List getUsers(String companyId) throws SystemException {
		return UserUtil.findByCompanyId(companyId);
	}

	public List getUsers(String companyId, int begin, int end)
		throws SystemException {

		return UserUtil.findByCompanyId(companyId, begin, end);
	}

}
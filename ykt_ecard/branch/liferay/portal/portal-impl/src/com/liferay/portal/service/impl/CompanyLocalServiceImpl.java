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

package com.liferay.portal.service.impl;

import com.liferay.portal.AccountNameException;
import com.liferay.portal.CompanyMxException;
import com.liferay.portal.CompanyVirtualHostException;
import com.liferay.portal.CompanyWebIdException;
import com.liferay.portal.NoSuchAccountException;
import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.NoSuchLayoutSetException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.model.impl.ContactImpl;
import com.liferay.portal.model.impl.CountryImpl;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.ListTypeImpl;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.model.impl.RegionImpl;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.service.base.CompanyLocalServiceBaseImpl;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.Encryptor;
import com.liferay.util.EncryptorException;
import com.liferay.util.Normalizer;
import com.liferay.util.lucene.HitsImpl;

import java.io.File;
import java.io.IOException;

import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Locale;

import javax.portlet.PortletException;
import javax.portlet.PortletPreferences;

import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;

/**
 * <a href="CompanyLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CompanyLocalServiceImpl extends CompanyLocalServiceBaseImpl {

	public Company addCompany(String webId, String virtualHost, String mx)
		throws PortalException, SystemException {

		// Company

		virtualHost = getVirtualHost(virtualHost);

		if ((Validator.isNull(webId)) ||
			(webId.equals(CompanyImpl.DEFAULT_WEB_ID)) ||
			(companyPersistence.fetchByWebId(webId) != null)) {

			throw new CompanyWebIdException();
		}

		validate(webId, virtualHost, mx);

		Company company = checkCompany(webId, mx);

		company.setVirtualHost(virtualHost);
		company.setMx(mx);

		companyPersistence.update(company);

		// Lucene

		LuceneUtil.checkLuceneDir(company.getCompanyId());

		return company;
	}

	public Company checkCompany(String webId)
		throws PortalException, SystemException {

		String mx = webId;

		return checkCompany(webId, mx);
	}

	public Company checkCompany(String webId, String mx)
		throws PortalException, SystemException {

		// Company

		Date now = new Date();

		Company company = companyPersistence.fetchByWebId(webId);

		if (company == null) {
			String virtualHost = webId;

			if (webId.equals(CompanyImpl.DEFAULT_WEB_ID)) {
				virtualHost = PortalInstances.DEFAULT_VIRTUAL_HOST;
			}

			String name = webId;
			String legalName = null;
			String legalId = null;
			String legalType = null;
			String sicCode = null;
			String tickerSymbol = null;
			String industry = null;
			String type = null;
			String size = null;

			long companyId = counterLocalService.increment();

			company = companyPersistence.create(companyId);

			try {
				company.setKeyObj(Encryptor.generateKey());
			}
			catch (EncryptorException ee) {
				throw new SystemException(ee);
			}

			company.setWebId(webId);
			company.setVirtualHost(virtualHost);
			company.setMx(mx);

			companyPersistence.update(company);

			updateCompany(
				companyId, virtualHost, mx, name, legalName, legalId, legalType,
				sicCode, tickerSymbol, industry, type, size);

			// Demo settings

			if (webId.equals("liferay.net")) {
				company = companyPersistence.findByWebId(webId);

				company.setVirtualHost("demo.liferay.net");

				companyPersistence.update(company);

				updateSecurity(
					companyId, CompanyImpl.AUTH_TYPE_EA, true, true, true, true,
					false, true);

				PortletPreferences prefs =
					PrefsPropsUtil.getPreferences(companyId);

				try {
					prefs.setValue(
						PropsUtil.ADMIN_EMAIL_FROM_NAME, "Liferay Demo");
					prefs.setValue(
						PropsUtil.ADMIN_EMAIL_FROM_ADDRESS, "test@liferay.net");

					prefs.store();
				}
				catch (IOException ioe) {
					throw new SystemException(ioe);
				}
				catch (PortletException pe) {
					throw new SystemException(pe);
				}
			}
		}

		long companyId = company.getCompanyId();

		// Key

		checkCompanyKey(companyId);

		// Default user

		User defaultUser = null;

		try {
			defaultUser = userLocalService.getDefaultUser(companyId);

			if (!defaultUser.isAgreedToTermsOfUse()) {
				defaultUser.setAgreedToTermsOfUse(true);

				userPersistence.update(defaultUser);
			}
		}
		catch (NoSuchUserException nsue) {
			long userId = counterLocalService.increment();

			defaultUser = userPersistence.create(userId);

			defaultUser.setCompanyId(companyId);
			defaultUser.setCreateDate(now);
			defaultUser.setModifiedDate(now);
			defaultUser.setDefaultUser(true);
			defaultUser.setContactId(counterLocalService.increment());
			defaultUser.setPassword("password");
			defaultUser.setScreenName(String.valueOf(defaultUser.getUserId()));
			defaultUser.setEmailAddress("default@" + company.getMx());
			defaultUser.setLanguageId(null);
			defaultUser.setTimeZoneId(null);
			defaultUser.setGreeting("Welcome!");
			defaultUser.setLoginDate(now);
			defaultUser.setFailedLoginAttempts(0);
			defaultUser.setAgreedToTermsOfUse(true);
			defaultUser.setActive(true);

			userPersistence.update(defaultUser);

			// Contact

			Contact defaultContact = contactPersistence.create(
				defaultUser.getContactId());

			defaultContact.setCompanyId(defaultUser.getCompanyId());
			defaultContact.setUserId(defaultUser.getUserId());
			defaultContact.setUserName(StringPool.BLANK);
			defaultContact.setCreateDate(now);
			defaultContact.setModifiedDate(now);
			defaultContact.setAccountId(company.getAccountId());
			defaultContact.setParentContactId(
				ContactImpl.DEFAULT_PARENT_CONTACT_ID);
			defaultContact.setFirstName(StringPool.BLANK);
			defaultContact.setMiddleName(StringPool.BLANK);
			defaultContact.setLastName(StringPool.BLANK);
			defaultContact.setMale(true);
			defaultContact.setBirthday(now);

			contactPersistence.update(defaultContact);
		}

		// System groups

		groupLocalService.checkSystemGroups(companyId);

		// Default password policy

		passwordPolicyLocalService.checkDefaultPasswordPolicy(companyId);

		// System roles

		roleLocalService.checkSystemRoles(companyId);

		// Default user must have the Guest role

		Role guestRole = roleLocalService.getRole(companyId, RoleImpl.GUEST);

		roleLocalService.setUserRoles(
			defaultUser.getUserId(), new long[] {guestRole.getRoleId()});

		// Default admin

		if (userPersistence.countByCompanyId(companyId) == 1) {
			long creatorUserId = 0;
			boolean autoPassword = false;
			String password1 = PropsValues.DEFAULT_ADMIN_PASSWORD;
			String password2 = password1;
			boolean autoScreenName = false;
			String screenName = PropsValues.DEFAULT_ADMIN_SCREEN_NAME;
			String emailAddress =
				PropsValues.DEFAULT_ADMIN_EMAIL_ADDRESS_PREFIX + "@" + mx;
			Locale locale = defaultUser.getLocale();
			String firstName = PropsValues.DEFAULT_ADMIN_FIRST_NAME;
			String middleName = PropsValues.DEFAULT_ADMIN_MIDDLE_NAME;
			String lastName = PropsValues.DEFAULT_ADMIN_LAST_NAME;
			int prefixId = 0;
			int suffixId = 0;
			boolean male = true;
			int birthdayMonth = Calendar.JANUARY;
			int birthdayDay = 1;
			int birthdayYear = 1970;
			String jobTitle = StringPool.BLANK;
			long[] organizationIds = new long[0];

			User user = userLocalService.addUser(
				creatorUserId, companyId, autoPassword, password1, password2,
				autoScreenName, screenName, emailAddress, locale, firstName,
				middleName, lastName, prefixId, suffixId, male, birthdayMonth,
				birthdayDay, birthdayYear, jobTitle, organizationIds, false);

			Group guestGroup = groupLocalService.getGroup(
				companyId, GroupImpl.GUEST);

			long[] groupIds = new long[] {guestGroup.getGroupId()};

			groupLocalService.addUserGroups(user.getUserId(), groupIds);

			Role adminRole = roleLocalService.getRole(
				companyId, RoleImpl.ADMINISTRATOR);

			Role powerUserRole = roleLocalService.getRole(
				companyId, RoleImpl.POWER_USER);

			long[] roleIds = new long[] {
				adminRole.getRoleId(), powerUserRole.getRoleId()
			};

			roleLocalService.setUserRoles(user.getUserId(), roleIds);

			Organization organization =
				organizationLocalService.addOrganization(
					user.getUserId(),
					OrganizationImpl.DEFAULT_PARENT_ORGANIZATION_ID,
					"Test Organization", OrganizationImpl.TYPE_REGULAR, true,
					RegionImpl.DEFAULT_REGION_ID,
					CountryImpl.DEFAULT_COUNTRY_ID,
					ListTypeImpl.ORGANIZATION_STATUS_DEFAULT, StringPool.BLANK);

			organizationLocalService.addOrganization(
				user.getUserId(), organization.getOrganizationId(),
				"Test Location", OrganizationImpl.TYPE_LOCATION, true,
				RegionImpl.DEFAULT_REGION_ID, CountryImpl.DEFAULT_COUNTRY_ID,
				ListTypeImpl.ORGANIZATION_STATUS_DEFAULT, StringPool.BLANK);
		}

		return company;
	}

	public void checkCompanyKey(long companyId)
		throws PortalException, SystemException {

		Company company = companyPersistence.findByPrimaryKey(companyId);

		if (company.getKeyObj() == null) {
			try {
				company.setKeyObj(Encryptor.generateKey());
			}
			catch (EncryptorException ee) {
				throw new SystemException(ee);
			}
		}

		companyPersistence.update(company);
	}

	public List getCompanies() throws SystemException {
		return companyPersistence.findAll();
	}

	public Company getCompanyById(long companyId)
		throws PortalException, SystemException {

		return companyPersistence.findByPrimaryKey(companyId);
	}

	public Company getCompanyByLogoId(long logoId)
		throws PortalException, SystemException {

		return companyPersistence.findByLogoId(logoId);
	}

	public Company getCompanyByMx(String mx)
		throws PortalException, SystemException {

		return companyPersistence.findByMx(mx);
	}

	public Company getCompanyByVirtualHost(String virtualHost)
		throws PortalException, SystemException {

		virtualHost = getVirtualHost(virtualHost);

		return companyPersistence.findByVirtualHost(virtualHost);
	}

	public Company getCompanyByWebId(String webId)
		throws PortalException, SystemException {

		return companyPersistence.findByWebId(webId);
	}

	public Hits search(long companyId, String keywords)
		throws SystemException {

		return search(companyId, null, 0, null, keywords);
	}

	public Hits search(
			long companyId, String portletId, long groupId, String type,
			String keywords)
		throws SystemException {

		Searcher searcher = null;

		try {
			HitsImpl hits = new HitsImpl();

			BooleanQuery contextQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				contextQuery, LuceneFields.COMPANY_ID, companyId);

			if (Validator.isNotNull(portletId)) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.PORTLET_ID, portletId);
			}

			if (groupId > 0) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.GROUP_ID, groupId);
			}

			if (Validator.isNotNull(type)) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.TYPE, type);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(searchQuery, LuceneFields.TITLE, keywords);
				LuceneUtil.addTerm(searchQuery, LuceneFields.CONTENT, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.DESCRIPTION, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.PROPERTIES, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.TAG_ENTRY, keywords);
			}

			BooleanQuery fullQuery = new BooleanQuery();

			fullQuery.add(contextQuery, BooleanClause.Occur.MUST);

			if (searchQuery.clauses().size() > 0) {
				fullQuery.add(searchQuery, BooleanClause.Occur.MUST);
			}

			searcher = LuceneUtil.getSearcher(companyId);

			hits.recordHits(searcher.search(fullQuery), searcher);

			return hits;
		}
		catch (Exception e) {
			return LuceneUtil.closeSearcher(searcher, keywords, e);
		}
	}

	public Company updateCompany(long companyId, String virtualHost, String mx)
		throws PortalException, SystemException {

		virtualHost = getVirtualHost(virtualHost);

		Company company = companyPersistence.findByPrimaryKey(companyId);

		validate(company.getWebId(), virtualHost, mx);

		company.setVirtualHost(virtualHost);

		if (PropsValues.MAIL_MX_UPDATE) {
			company.setMx(mx);
		}

		companyPersistence.update(company);

		return company;
	}

	public Company updateCompany(
			long companyId, String virtualHost, String mx, String name,
			String legalName, String legalId, String legalType, String sicCode,
			String tickerSymbol, String industry, String type, String size)
		throws PortalException, SystemException {

		// Company

		virtualHost = getVirtualHost(virtualHost);
		Date now = new Date();

		Company company = companyPersistence.findByPrimaryKey(companyId);

		validate(company.getWebId(), virtualHost, mx);
		validate(name);

		company.setVirtualHost(virtualHost);

		if (PropsValues.MAIL_MX_UPDATE) {
			company.setMx(mx);
		}

		companyPersistence.update(company);

		// Account

		Account account = null;

		try {
			account = accountPersistence.findByPrimaryKey(
				company.getAccountId());
		}
		catch (NoSuchAccountException nsae) {
			long accountId = counterLocalService.increment();

			account = accountPersistence.create(accountId);

			account.setCreateDate(now);
			account.setCompanyId(companyId);
			account.setUserId(0);
			account.setUserName(StringPool.BLANK);

			company.setAccountId(accountId);

			companyPersistence.update(company);
		}

		account.setModifiedDate(now);
		account.setName(name);
		account.setLegalName(legalName);
		account.setLegalId(legalId);
		account.setLegalType(legalType);
		account.setSicCode(sicCode);
		account.setTickerSymbol(tickerSymbol);
		account.setIndustry(industry);
		account.setType(type);
		account.setSize(size);

		accountPersistence.update(account);

		return company;
	}

	public void updateDisplay(
			long companyId, String languageId, String timeZoneId)
		throws PortalException, SystemException {

		User user = userLocalService.getDefaultUser(companyId);

		user.setLanguageId(languageId);
		user.setTimeZoneId(timeZoneId);

		userPersistence.update(user);
	}

	public void updateLogo(long companyId, File file)
		throws PortalException, SystemException {

		Company company = companyPersistence.findByPrimaryKey(companyId);

		long logoId = company.getLogoId();

		if (logoId <= 0) {
			logoId = counterLocalService.increment();

			company.setLogoId(logoId);
		}

		ImageLocalUtil.updateImage(logoId, file);
	}

	public void updateSecurity(
			long companyId, String authType, boolean autoLogin,
			boolean sendPassword, boolean strangers, boolean strangersWithMx,
			boolean strangersVerify, boolean communityLogo)
		throws PortalException, SystemException {

		PortletPreferences prefs = PrefsPropsUtil.getPreferences(companyId);

		try {
			prefs.setValue(PropsUtil.COMPANY_SECURITY_AUTH_TYPE, authType);
			prefs.setValue(
				PropsUtil.COMPANY_SECURITY_AUTO_LOGIN,
				String.valueOf(autoLogin));
			prefs.setValue(
				PropsUtil.COMPANY_SECURITY_SEND_PASSWORD,
				String.valueOf(sendPassword));
			prefs.setValue(
				PropsUtil.COMPANY_SECURITY_STRANGERS,
				String.valueOf(strangers));
			prefs.setValue(
				PropsUtil.COMPANY_SECURITY_STRANGERS_WITH_MX,
				String.valueOf(strangersWithMx));
			prefs.setValue(
				PropsUtil.COMPANY_SECURITY_STRANGERS_VERIFY,
				String.valueOf(strangersVerify));
			prefs.setValue(
				PropsUtil.COMPANY_SECURITY_COMMUNITY_LOGO,
				String.valueOf(communityLogo));

			prefs.store();
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (PortletException pe) {
			throw new SystemException(pe);
		}
	}

	protected String getVirtualHost(String virtualHost) {
		return Normalizer.normalizeToAscii(virtualHost.trim().toLowerCase());
	}

	protected void validate(String name) throws PortalException {
		if (Validator.isNull(name)) {
			throw new AccountNameException();
		}
	}

	protected void validate(String webId, String virtualHost, String mx)
		throws PortalException, SystemException {

		if (Validator.isNull(virtualHost)) {
			throw new CompanyVirtualHostException();
		}
		else if (virtualHost.equals(PortalInstances.DEFAULT_VIRTUAL_HOST) &&
				 !webId.equals(CompanyImpl.DEFAULT_WEB_ID)) {

			throw new CompanyVirtualHostException();
		}
		else {
			try {
				Company virtualHostCompany = getCompanyByVirtualHost(
					virtualHost);

				if (!virtualHostCompany.getWebId().equals(webId)) {
					throw new CompanyVirtualHostException();
				}
			}
			catch (NoSuchCompanyException nsce) {
			}

			try {
				layoutSetLocalService.getLayoutSet(virtualHost);

				throw new CompanyVirtualHostException();
			}
			catch (NoSuchLayoutSetException nslse) {
			}
		}

		if (Validator.isNull(mx)) {
			throw new CompanyMxException();
		}
	}

}
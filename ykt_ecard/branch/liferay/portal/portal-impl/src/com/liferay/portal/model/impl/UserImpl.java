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
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.TimeZoneUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.model.User;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.service.ContactLocalServiceUtil;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.OrganizationLocalServiceUtil;
import com.liferay.portal.service.PasswordPolicyLocalServiceUtil;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.comparator.OrganizationNameComparator;
import com.liferay.util.dao.hibernate.QueryUtil;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UserImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserImpl extends UserModelImpl implements User {

	public static String getFullName(
		String firstName, String middleName, String lastName) {

		return ContactImpl.getFullName(firstName, middleName, lastName);
	}

	public UserImpl() {
	}

	public String getCompanyMx() {
		String companyMx = null;

		try {
			Company company = CompanyLocalServiceUtil.getCompanyById(
				getCompanyId());

			companyMx = company.getMx();
		}
		catch (Exception e) {
			_log.error(e);
		}

		return companyMx;
	}

	public boolean hasCompanyMx() {
		return hasCompanyMx(getEmailAddress());
	}

	public boolean hasCompanyMx(String emailAddress) {
		try {
			Company company = CompanyLocalServiceUtil.getCompanyById(
				getCompanyId());

			return company.hasCompanyMx(emailAddress);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return false;
	}

	public String getLogin() throws PortalException, SystemException {
		String login = null;

		Company company = CompanyLocalServiceUtil.getCompanyById(
			getCompanyId());

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			login = getEmailAddress();
		}
		else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			login = getScreenName();
		}
		else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			login = String.valueOf(getUserId());
		}

		return login;
	}

	public PasswordPolicy getPasswordPolicy()
		throws PortalException, SystemException {

		PasswordPolicy passwordPolicy =
			PasswordPolicyLocalServiceUtil.getPasswordPolicyByUserId(
				getUserId());

		return passwordPolicy;
	}

	public String getPasswordUnencrypted() {
		return _passwordUnencrypted;
	}

	public void setPasswordUnencrypted(String passwordUnencrypted) {
		_passwordUnencrypted = passwordUnencrypted;
	}

	public boolean getPasswordModified() {
		return _passwordModified;
	}

	public boolean isPasswordModified() {
		return _passwordModified;
	}

	public void setPasswordModified(boolean passwordModified) {
		_passwordModified = passwordModified;
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
			timeZoneId = TimeZoneUtil.getDefault().getID();
		}

		_timeZone = TimeZone.getTimeZone(timeZoneId);

		super.setTimeZoneId(timeZoneId);
	}

	public Contact getContact() {
		Contact contact = null;

		try {
			contact = ContactLocalServiceUtil.getContact(getContactId());
		}
		catch (Exception e) {
			contact = new ContactImpl();

			_log.error(e);
		}

		return contact;
	}

	public String getFirstName() {
		return getContact().getFirstName();
	}

	public String getMiddleName() {
		return getContact().getMiddleName();
	}

	public String getLastName() {
		return getContact().getLastName();
	}

	public String getFullName() {
		return getContact().getFullName();
	}

	public boolean getMale() {
		return getContact().getMale();
	}

	public boolean isMale() {
		return getMale();
	}

	public boolean getFemale() {
		return !getMale();
	}

	public boolean isFemale() {
		return getFemale();
	}

	public Date getBirthday() {
		return getContact().getBirthday();
	}

	public Group getGroup() {
		Group group = null;

		try {
			group = GroupLocalServiceUtil.getUserGroup(
				getCompanyId(), getUserId());
		}
		catch (Exception e) {
		}

		return group;
	}

	/**
	 * @deprecated Will return the first regular organization of the list in
	 * alphabetical order.
	 */
	public Organization getOrganization() {
		try {
			List organizations =
				OrganizationLocalServiceUtil.getUserOrganizations(getUserId());

			Collections.sort(
				organizations, new OrganizationNameComparator(true));

			for (int i = 0; i < organizations.size(); i++) {
				Organization organization = (Organization)organizations.get(i);

				if (!organization.isLocation()) {
					return organization;
				}
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Unable to get an organization for user " + getUserId());
			}
		}

		return new OrganizationImpl();
	}

	public long[] getOrganizationIds() {
		List organizations = getOrganizations();

		long[] organizationIds = new long[organizations.size()];

		Iterator itr = organizations.iterator();

		for (int i = 0; itr.hasNext(); i++) {
			Organization organization = (Organization)itr.next();

			organizationIds[i] = organization.getOrganizationId();
		}

		return organizationIds;
	}

	public List getOrganizations() {
		try {
			return OrganizationLocalServiceUtil.getUserOrganizations(
				getUserId());
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Unable to get organizations for user " + getUserId());
			}
		}

		return new ArrayList();
	}

	public boolean hasOrganization() {
		if (getOrganizations().size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	/**
	 * @deprecated
	 */
	public Organization getLocation() {
		try {
			List organizations =
				OrganizationLocalServiceUtil.getUserOrganizations(getUserId());

			for (int i = 0; i < organizations.size(); i++) {
				Organization organization = (Organization)organizations.get(i);

				if (organization.isLocation()) {
					return organization;
				}
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn("Unable to get a location for user " + getUserId());
			}
		}

		return new OrganizationImpl();
	}

	/**
	 * @deprecated
	 */
	public long getLocationId() {
		Organization location = getLocation();

		if (location == null) {
			return OrganizationImpl.DEFAULT_PARENT_ORGANIZATION_ID;
		}

		return location.getOrganizationId();
	}

	/**
	 * @deprecated
	 */
	public boolean hasLocation() {
		if (getLocation().getOrganizationId() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public int getPrivateLayoutsPageCount() {
		try {
			Group group = getGroup();

			if (group == null) {
				return 0;
			}
			else {
				return group.getPrivateLayoutsPageCount();
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return 0;
	}

	public boolean hasPrivateLayouts() {
		if (getPrivateLayoutsPageCount() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public int getPublicLayoutsPageCount() {
		try {
			Group group = getGroup();

			if (group == null) {
				return 0;
			}
			else {
				return group.getPublicLayoutsPageCount();
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return 0;
	}

	public boolean hasPublicLayouts() {
		if (getPublicLayoutsPageCount() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isLayoutsRequired() {
		try {
			return RoleLocalServiceUtil.hasUserRole(
				getUserId(), getCompanyId(), RoleImpl.POWER_USER, true);
		}
		catch (Exception e) {
			return false;
		}
	}

	public List getMyPlaces() {
		List myPlaces = new ArrayList();

		try {
			if (isDefaultUser()) {
				return myPlaces;
			}

			LinkedHashMap groupParams = new LinkedHashMap();

			groupParams.put("usersGroups", new Long(getUserId()));
			//groupParams.put("pageCount", StringPool.BLANK);

			myPlaces = GroupLocalServiceUtil.search(
				getCompanyId(), null, null, groupParams, QueryUtil.ALL_POS,
				QueryUtil.ALL_POS);

			List userOrgs = getOrganizations();

			Iterator itr = userOrgs.iterator();

			while (itr.hasNext()) {
				Organization organization = (Organization)itr.next();

				myPlaces.add(0, organization.getGroup());
			}

			if (isLayoutsRequired()) {
				Group userGroup = getGroup();

				myPlaces.add(0, userGroup);
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e, e);
			}
		}

		return myPlaces;
	}

	public boolean hasMyPlaces() {
		try {
			if (isDefaultUser()) {
				return false;
			}

			LinkedHashMap groupParams = new LinkedHashMap();

			groupParams.put("usersGroups", new Long(getUserId()));
			//groupParams.put("pageCount", StringPool.BLANK);

			int count = GroupLocalServiceUtil.searchCount(
				getCompanyId(), null, null, groupParams);

			if (count > 0) {
				return true;
			}

			count = OrganizationLocalServiceUtil.getUserOrganizationsCount(
				getUserId());

			if (count > 0) {
				return true;
			}

			if (isLayoutsRequired()) {
				return true;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e, e);
			}
		}

		return false;
	}

	public String getDisplayURL(String portalURL) {
		try {
			Group group = getGroup();

			int publicLayoutsPageCount = group.getPublicLayoutsPageCount();

			if (publicLayoutsPageCount > 0) {
				return portalURL + PortalUtil.getPathMain() +
					"/my_places/view?groupId=" + group.getGroupId() +
						"&privateLayout=0";
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return StringPool.BLANK;
	}

	private static Log _log = LogFactory.getLog(UserImpl.class);

	private boolean _passwordModified;
	private String _passwordUnencrypted;
	private Locale _locale;
	private TimeZone _timeZone;

}
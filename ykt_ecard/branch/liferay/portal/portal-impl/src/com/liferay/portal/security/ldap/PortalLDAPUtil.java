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

package com.liferay.portal.security.ldap;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.NoSuchUserGroupException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.log.LogUtil;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.service.UserGroupLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.ldap.LDAPUtil;
import com.liferay.util.ldap.Modifications;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;

import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.Properties;

import javax.naming.Binding;
import javax.naming.Context;
import javax.naming.NameNotFoundException;
import javax.naming.NamingEnumeration;
import javax.naming.directory.Attribute;
import javax.naming.directory.Attributes;
import javax.naming.directory.ModificationItem;
import javax.naming.directory.SearchControls;
import javax.naming.directory.SearchResult;
import javax.naming.ldap.InitialLdapContext;
import javax.naming.ldap.LdapContext;

/**
 * <a href="PortalLDAPUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @author Brian Wing Shun Chan
 * @author Jerry Niu
 * @author Scott Lee
 * @author Hervé Ménage
 *
 */
public class PortalLDAPUtil {

	public static final String IMPORT_BY_USER = "user";

	public static final String IMPORT_BY_GROUP = "group";

	public static void exportToLDAP(Contact contact) throws Exception {
		long companyId = contact.getCompanyId();

		if (!isAuthEnabled(companyId) || !isExportEnabled(companyId)) {
			return;
		}

		LdapContext ctx = getContext(companyId);

		if (ctx == null) {
			return;
		}

		User user = UserLocalServiceUtil.getUserByContactId(
			contact.getContactId());

		Properties userMappings = getUserMappings(companyId);
		Binding binding = getUser(contact.getCompanyId(), user.getScreenName());
		String name = StringPool.BLANK;

		if (binding == null) {

			// Generate full DN based on user DN

			StringMaker sm = new StringMaker();

			sm.append(userMappings.getProperty("screenName"));
			sm.append(StringPool.EQUAL);
			sm.append(user.getScreenName());
			sm.append(StringPool.COMMA);
			sm.append(getUsersDN(companyId));

			name = sm.toString();

			// Create new user in LDAP

			LDAPUser ldapUser = (LDAPUser)Class.forName(
				PropsValues.LDAP_USER_IMPL).newInstance();

			ldapUser.setUser(user);

			ctx.bind(name, ldapUser);
		}
		else {

			// Modify existing LDAP user record

			name = getNameInNamespace(companyId, binding);

			Modifications mods = Modifications.getInstance();

			mods.addItem(
				userMappings.getProperty("firstName"), contact.getFirstName());
			mods.addItem(
				userMappings.getProperty("lastName"), contact.getLastName());

			ModificationItem[] modItems = mods.getItems();

			ctx.modifyAttributes(name, modItems);
		}

		ctx.close();
	}

	public static void exportToLDAP(User user) throws Exception {
		long companyId = user.getCompanyId();

		if (!isAuthEnabled(companyId) || !isExportEnabled(companyId)) {
			return;
		}

		LdapContext ctx = getContext(companyId);

		if (ctx == null) {
			return;
		}

		Properties userMappings = getUserMappings(companyId);
		Binding binding = getUser(user.getCompanyId(), user.getScreenName());
		String name = StringPool.BLANK;

		if (binding == null) {

			// Generate full DN based on user DN

			StringMaker sm = new StringMaker();

			sm.append(userMappings.getProperty("screenName"));
			sm.append(StringPool.EQUAL);
			sm.append(user.getScreenName());
			sm.append(StringPool.COMMA);
			sm.append(getUsersDN(companyId));

			name = sm.toString();

			// Create new user in LDAP

			LDAPUser ldapUser = (LDAPUser)Class.forName(
				PropsValues.LDAP_USER_IMPL).newInstance();

			ldapUser.setUser(user);

			ctx.bind(name, ldapUser);
		}
		else {

			// Modify existing LDAP user record

			name = getNameInNamespace(companyId, binding);

			Modifications mods = Modifications.getInstance();

			if (user.isPasswordModified() &&
				Validator.isNotNull(user.getPasswordUnencrypted())) {

				mods.addItem(
					userMappings.getProperty("password"),
					user.getPasswordUnencrypted());
			}

			mods.addItem(
				userMappings.getProperty("emailAddress"),
				user.getEmailAddress());

			ModificationItem[] modItems = mods.getItems();

			ctx.modifyAttributes(name, modItems);
		}

		ctx.close();
	}

	public static Attributes getAttributes(
			LdapContext ctx, String fullDistinguishedName)
		throws Exception {

		String[] attrIds = {
			"creatorsName", "createTimestamp", "modifiersName",
			"modifyTimestamp"
		};

		Attributes attrs = ctx.getAttributes(fullDistinguishedName);

		NamingEnumeration enu = ctx.getAttributes(
			fullDistinguishedName, attrIds).getAll();

		while (enu.hasMore()) {
			attrs.put((Attribute)enu.next());
		}

		return attrs;
	}

	public static String getAuthSearchFilter(
			long companyId, String emailAddress, String screenName,
			String userId)
		throws PortalException, SystemException {

		String filter = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_AUTH_SEARCH_FILTER);

		if (_log.isDebugEnabled()) {
			_log.debug("Search filter before transformation " + filter);
		}

		filter = StringUtil.replace(
			filter,
			new String[] {
				"@company_id@", "@email_address@", "@screen_name@", "@user_id@"
			},
			new String[] {
				String.valueOf(companyId), emailAddress, screenName,
				userId
			});

		if (_log.isDebugEnabled()) {
			_log.debug("Search filter after transformation " + filter);
		}

		return filter;
	}

	public static LdapContext getContext(long companyId) throws Exception {
		String baseProviderURL = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_BASE_PROVIDER_URL);
		String pricipal = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_SECURITY_PRINCIPAL);
		String credentials = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_SECURITY_CREDENTIALS);

		return getContext(companyId, baseProviderURL, pricipal, credentials);
	}

	public static LdapContext getContext(
			long companyId, String providerURL, String pricipal,
			String credentials)
		throws Exception {

		Properties env = new Properties();

		env.put(
			Context.INITIAL_CONTEXT_FACTORY,
			PrefsPropsUtil.getString(
				companyId, PropsUtil.LDAP_FACTORY_INITIAL));
		env.put(Context.PROVIDER_URL, providerURL);
		env.put(Context.SECURITY_PRINCIPAL, pricipal);
		env.put(Context.SECURITY_CREDENTIALS, credentials);

		LogUtil.debug(_log, env);

		LdapContext ctx = null;

		try {
			ctx = new InitialLdapContext(env, null);
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn("Failed to bind to the LDAP server");
			}

			if (_log.isDebugEnabled()) {
				_log.debug(e);
			}
		}

		return ctx;
	}

	public static Properties getGroupMappings(long companyId)
		throws Exception {

		Properties groupMappings = PropertiesUtil.load(
			PrefsPropsUtil.getString(companyId, PropsUtil.LDAP_GROUP_MAPPINGS));

		LogUtil.debug(_log, groupMappings);

		return groupMappings;
	}

	public static NamingEnumeration getGroups(
			long companyId, LdapContext ctx, int maxResults)
		throws Exception {

		String baseDN = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_BASE_DN);
		String groupFilter = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_IMPORT_GROUP_SEARCH_FILTER);

		return getGroups(companyId, ctx, maxResults, baseDN, groupFilter);
	}

	public static NamingEnumeration getGroups(
			long companyId, LdapContext ctx, int maxResults, String baseDN,
			String groupFilter)
		throws Exception {

		SearchControls cons = new SearchControls(
			SearchControls.SUBTREE_SCOPE, maxResults, 0, null, false, false);

		return ctx.search(baseDN, groupFilter, cons);
	}

	public static String getNameInNamespace(long companyId, Binding binding)
		throws Exception {

		String baseDN = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_BASE_DN);

		if (Validator.isNull(baseDN)) {
			return binding.getName();
		}
		else {
			StringMaker sm = new StringMaker();

			sm.append(binding.getName());
			sm.append(StringPool.COMMA);
			sm.append(baseDN);

			return sm.toString();
		}
	}

	public static Binding getUser(long companyId, String screenName)
		throws Exception {

		LdapContext ctx = getContext(companyId);

		if (ctx == null) {
			return null;
		}

		String baseDN = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_BASE_DN);

		Properties userMappings = getUserMappings(companyId);

		StringMaker filter = new StringMaker();

		filter.append(StringPool.OPEN_PARENTHESIS);
		filter.append(userMappings.getProperty("screenName"));
		filter.append(StringPool.EQUAL);
		filter.append(screenName);
		filter.append(StringPool.CLOSE_PARENTHESIS);

		SearchControls cons = new SearchControls(
			SearchControls.SUBTREE_SCOPE, 1, 0, null, false, false);

		NamingEnumeration enu = ctx.search(baseDN, filter.toString(), cons);

		ctx.close();

		if (enu.hasMore()) {
			Binding binding = (Binding)enu.next();

			return binding;
		}
		else {
			return null;
		}
	}

	public static Properties getUserMappings(long companyId) throws Exception {
		Properties userMappings = PropertiesUtil.load(
			PrefsPropsUtil.getString(companyId, PropsUtil.LDAP_USER_MAPPINGS));

		LogUtil.debug(_log, userMappings);

		return userMappings;
	}

	public static NamingEnumeration getUsers(
			long companyId, LdapContext ctx, int maxResults)
		throws Exception {

		String baseDN = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_BASE_DN);
		String userFilter = PrefsPropsUtil.getString(
			companyId, PropsUtil.LDAP_IMPORT_USER_SEARCH_FILTER);

		return getUsers(companyId, ctx, maxResults, baseDN, userFilter);
	}

	public static NamingEnumeration getUsers(
			long companyId, LdapContext ctx, int maxResults, String baseDN,
			String userFilter)
		throws Exception {

		SearchControls cons = new SearchControls(
			SearchControls.SUBTREE_SCOPE, maxResults, 0, null, false, false);

		return ctx.search(baseDN, userFilter, cons);
	}

	public static String getUsersDN(long companyId) throws Exception {
		return PrefsPropsUtil.getString(companyId, PropsUtil.LDAP_USERS_DN);
	}

	public static boolean hasUser(long companyId, String screenName)
		throws Exception {

		if (getUser(companyId, screenName) != null) {
			return true;
		}
		else {
			return false;
		}
	}

	public static void importFromLDAP() throws Exception {
		List companies = CompanyLocalServiceUtil.getCompanies();

		for (int i = 0; i < companies.size(); i++) {
			Company company = (Company)companies.get(i);

			importFromLDAP(company.getCompanyId());
		}
	}

	public static void importFromLDAP(long companyId) throws Exception {
		if (!isImportEnabled(companyId)) {
			return;
		}

		LdapContext ctx = getContext(companyId);

		if (ctx == null) {
			return;
		}

		try {
			String importMethod = PrefsPropsUtil.getString(
				companyId, PropsUtil.LDAP_IMPORT_METHOD);

			if (importMethod.equals(IMPORT_BY_USER)) {
				NamingEnumeration enu = getUsers(companyId, ctx, 0);

				// Loop through all LDAP users

				while (enu.hasMore()) {
					SearchResult result = (SearchResult)enu.next();

					Attributes attrs = getAttributes(
						ctx, getNameInNamespace(companyId, result));

					importLDAPUser(
						companyId, ctx, attrs, StringPool.BLANK, true);
				}
			}
			else if (importMethod.equals(IMPORT_BY_GROUP)) {
				NamingEnumeration enu = getGroups(companyId, ctx, 0);

				// Loop through all LDAP groups

				while (enu.hasMore()) {
					SearchResult result = (SearchResult)enu.next();

					Attributes attrs = getAttributes(
						ctx, getNameInNamespace(companyId, result));

					importLDAPGroup(companyId, ctx, attrs, true);
				}
			}
		}
		catch (Exception e) {
			_log.error("Error importing LDAP users and groups", e);
		}
		finally {
			if (ctx != null) {
				ctx.close();
			}
		}
	}

	public static UserGroup importLDAPGroup(
			long companyId, LdapContext ctx, Attributes attrs,
			boolean importGroupMembership)
		throws Exception {

		AttributesTransformer attrsTransformer =
			AttributesTransformerFactory.getInstance();

		attrs = attrsTransformer.transformGroup(attrs);

		Properties groupMappings = getGroupMappings(companyId);

		LogUtil.debug(_log, groupMappings);

		String groupName = LDAPUtil.getAttributeValue(
			attrs, groupMappings.getProperty("groupName")).toLowerCase();
		String description = LDAPUtil.getAttributeValue(
			attrs, groupMappings.getProperty("description"));

		// Get or create user group

		UserGroup userGroup = null;

		try {
			userGroup = UserGroupLocalServiceUtil.getUserGroup(
				companyId, groupName);

			UserGroupLocalServiceUtil.updateUserGroup(
				companyId, userGroup.getUserGroupId(), groupName, description);
		}
		catch (NoSuchUserGroupException nsuge) {
			if (_log.isDebugEnabled()) {
				_log.debug("Adding user group to portal " + groupName);
			}

			long defaultUserId = UserLocalServiceUtil.getDefaultUserId(
				companyId);

			try {
				userGroup = UserGroupLocalServiceUtil.addUserGroup(
					defaultUserId, companyId, groupName, description);
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn("Could not create user group " + groupName);
				}

				if (_log.isDebugEnabled()) {
					_log.debug(e, e);
				}
			}
		}

		// Import users and membership

		if (importGroupMembership && (userGroup != null)) {
			Attribute attr = attrs.get(groupMappings.getProperty("user"));

			if (attr != null){
				_importUsersAndMembershipFromLDAPGroup(
					companyId, ctx, userGroup.getUserGroupId(), attr);
			}
		}

		return userGroup;
	}

	public static User importLDAPUser(
			long companyId, LdapContext ctx, Attributes attrs, String password,
			boolean importGroupMembership)
		throws Exception {

		AttributesTransformer attrsTransformer =
			AttributesTransformerFactory.getInstance();

		attrs = attrsTransformer.transformUser(attrs);

		Properties userMappings = getUserMappings(companyId);

		LogUtil.debug(_log, userMappings);

		User defaultUser = UserLocalServiceUtil.getDefaultUser(companyId);

		boolean autoPassword = false;
		boolean updatePassword = true;

		if (password.equals(StringPool.BLANK)) {
			autoPassword = true;
			updatePassword = false;
		}

		long creatorUserId = 0;
		boolean passwordReset = false;
		boolean autoScreenName = false;
		String screenName = LDAPUtil.getAttributeValue(
			attrs, userMappings.getProperty("screenName")).toLowerCase();
		String emailAddress = LDAPUtil.getAttributeValue(
			attrs, userMappings.getProperty("emailAddress"));
		Locale locale = defaultUser.getLocale();
		String firstName = LDAPUtil.getAttributeValue(
			attrs, userMappings.getProperty("firstName"));
		String middleName = LDAPUtil.getAttributeValue(
			attrs, userMappings.getProperty("middleName"));
		String lastName = LDAPUtil.getAttributeValue(
			attrs, userMappings.getProperty("lastName"));

		if (Validator.isNull(firstName) || Validator.isNull(lastName)) {
			String fullName = LDAPUtil.getAttributeValue(
				attrs, userMappings.getProperty("fullName"));

			String[] names = LDAPUtil.splitFullName(fullName);

			firstName = names[0];
			middleName = names[1];
			lastName = names[2];
		}

		int prefixId = 0;
		int suffixId = 0;
		boolean male = true;
		int birthdayMonth = Calendar.JANUARY;
		int birthdayDay = 1;
		int birthdayYear = 1970;
		String jobTitle = LDAPUtil.getAttributeValue(
			attrs, userMappings.getProperty("jobTitle"));
		long[] organizationIds = new long[0];
		boolean sendEmail = false;

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Screen name " + screenName + " and email address " +
					emailAddress);
		}

		if (Validator.isNull(screenName) || Validator.isNull(emailAddress)) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Cannot add user because screen name and email address " +
						"are required");
			}

			return null;
		}

		User user = null;

		try {

			// Find corresponding portal user

			String authType = PrefsPropsUtil.getString(
				companyId, PropsUtil.COMPANY_SECURITY_AUTH_TYPE,
				PropsValues.COMPANY_SECURITY_AUTH_TYPE);

			if (authType.equals(CompanyImpl.AUTH_TYPE_SN)) {
				user = UserLocalServiceUtil.getUserByScreenName(
					companyId, screenName);
			}
			else {
				user = UserLocalServiceUtil.getUserByEmailAddress(
					companyId, emailAddress);
			}

			// Skip if is default user

			if (user.isDefaultUser()) {
				return user;
			}

			// Skip import if user fields has been already synced and if
			// import is part of a scheduled import

			Date ldapUserModifiedDate = null;

			String modifiedDate = LDAPUtil.getAttributeValue(
				attrs, "modifyTimestamp");

			try {
				DateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmss");

				ldapUserModifiedDate = dateFormat.parse(modifiedDate);

				if (ldapUserModifiedDate.equals(user.getModifiedDate()) &&
					autoPassword) {

					if (_log.isDebugEnabled()) {
						_log.debug(
							"User is already syncronized, skipping user " +
								user.getEmailAddress());
					}

					return user;
				}
			}
			catch (ParseException pe) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Unable to parse LDAP modify timestamp " +
							modifiedDate);
				}

				_log.debug(pe, pe);
			}

			Contact contact = user.getContact();

			Calendar birthdayCal = CalendarFactoryUtil.getCalendar();

			birthdayCal.setTime(contact.getBirthday());

			birthdayMonth = birthdayCal.get(Calendar.MONTH);
			birthdayDay = birthdayCal.get(Calendar.DATE);
			birthdayYear = birthdayCal.get(Calendar.YEAR);

			// User exists so update user information

			if (updatePassword) {
				user = UserLocalServiceUtil.updatePassword(
					user.getUserId(), password, password, passwordReset,
					true);
			}

			user = UserLocalServiceUtil.updateUser(
				user.getUserId(), password, user.isPasswordReset(), screenName,
				emailAddress, user.getLanguageId(), user.getTimeZoneId(),
				user.getGreeting(), user.getComments(), firstName, middleName,
				lastName, contact.getPrefixId(), contact.getSuffixId(),
				contact.getMale(), birthdayMonth, birthdayDay, birthdayYear,
				contact.getSmsSn(), contact.getAimSn(), contact.getIcqSn(),
				contact.getJabberSn(), contact.getMsnSn(), contact.getSkypeSn(),
				contact.getYmSn(), jobTitle, user.getOrganizationIds());

			if (ldapUserModifiedDate != null) {
				UserLocalServiceUtil.updateModifiedDate(
					user.getUserId(), ldapUserModifiedDate);
			}
		}
		catch (NoSuchUserException nsue) {

			// User does not exist so create

		}

		if (user == null) {
			try {
				if (_log.isDebugEnabled()) {
					_log.debug("Adding user to portal " + emailAddress);
				}

				user = UserLocalServiceUtil.addUser(
					creatorUserId, companyId, autoPassword, password, password,
					autoScreenName, screenName, emailAddress, locale, firstName,
					middleName, lastName, prefixId, suffixId, male,
					birthdayMonth, birthdayDay, birthdayYear, jobTitle,
					organizationIds, sendEmail);
			}
			catch (Exception e){
				_log.error(
					"Problem adding user with screen name " + screenName +
						" and email address " + emailAddress,
					e);
			}
		}

		// Import user groups and membership

		if (importGroupMembership && (user != null)) {
			String userMappingsGroup = userMappings.getProperty("group");

			if (userMappingsGroup != null) {
				Attribute attr = attrs.get(userMappingsGroup);

				if (attr != null){
					_importGroupsAndMembershipFromLDAPUser(
						companyId, ctx, user.getUserId(), attr);
				}
			}
		}

		return user;
	}

	public static boolean isAuthEnabled(long companyId)
		throws PortalException, SystemException {

		if (PrefsPropsUtil.getBoolean(
				companyId, PropsUtil.LDAP_AUTH_ENABLED,
				PropsValues.LDAP_AUTH_ENABLED)) {

			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isExportEnabled(long companyId)
		throws PortalException, SystemException {

		if (PrefsPropsUtil.getBoolean(
				companyId, PropsUtil.LDAP_EXPORT_ENABLED,
				PropsValues.LDAP_EXPORT_ENABLED)) {

			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isImportEnabled(long companyId)
		throws PortalException, SystemException {

		if (PrefsPropsUtil.getBoolean(
				companyId, PropsUtil.LDAP_IMPORT_ENABLED,
				PropsValues.LDAP_IMPORT_ENABLED)) {

			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isImportOnStartup(long companyId)
		throws PortalException, SystemException {

		if (PrefsPropsUtil.getBoolean(
				companyId, PropsUtil.LDAP_IMPORT_ON_STARTUP)) {

			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isNtlmEnabled(long companyId)
		throws PortalException, SystemException {

		if (!isAuthEnabled(companyId)) {
			return false;
		}

		if (PrefsPropsUtil.getBoolean(companyId, PropsUtil.NTLM_AUTH_ENABLED)) {
			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isPasswordPolicyEnabled(long companyId)
		throws PortalException, SystemException {

		if (PrefsPropsUtil.getBoolean(
				companyId, PropsUtil.LDAP_PASSWORD_POLICY_ENABLED,
				PropsValues.LDAP_PASSWORD_POLICY_ENABLED)) {

			return true;
		}
		else {
			return false;
		}
	}

	private static void _importGroupsAndMembershipFromLDAPUser(
			long companyId, LdapContext ctx, long userId, Attribute attr)
		throws Exception {

		// Remove all user group membership from user

		UserGroupLocalServiceUtil.clearUserUserGroups(userId);

		for (int i = 0; i < attr.size(); i++) {

			// Find group in LDAP

			String fullGroupDN = (String)attr.get(i);

			Attributes groupAttrs = null;

			try {
				groupAttrs = getAttributes(ctx, fullGroupDN);
			}
			catch (NameNotFoundException nnfe) {
				_log.error(
					"LDAP group not found with fullGroupDN " + fullGroupDN);

				_log.error(nnfe, nnfe);

				continue;
			}

			UserGroup userGroup = importLDAPGroup(
				companyId, ctx, groupAttrs, false);

			// Add user to user group

			if (userGroup != null) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Adding " + userId + " to group " +
							userGroup.getUserGroupId());
				}

				UserLocalServiceUtil.addUserGroupUsers(
					userGroup.getUserGroupId(), new long[] {userId});
			}
		}
	}

	private static void _importUsersAndMembershipFromLDAPGroup(
			long companyId, LdapContext ctx, long userGroupId, Attribute attr)
		throws Exception {

		// Remove all user membership from user group

		UserLocalServiceUtil.clearUserGroupUsers(userGroupId);

		for (int i = 0; i < attr.size(); i++) {

			// Find user in LDAP

			String fullUserDN = (String)attr.get(i);

			Attributes userAttrs = null;

			try {
				userAttrs = getAttributes(ctx, fullUserDN);
			}
			catch (NameNotFoundException nnfe) {
				_log.error(
					"LDAP user not found with fullUserDN " + fullUserDN);

				_log.error(nnfe, nnfe);

				continue;
			}

			User user = importLDAPUser(
				companyId, ctx, userAttrs, StringPool.BLANK, false);

			// Add user to user group

			if (user != null) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Adding " + user.getUserId() + " to group " +
							userGroupId);
				}

				UserLocalServiceUtil.addUserGroupUsers(
					userGroupId, new long[] {user.getUserId()});
			}
		}
	}

	private static Log _log = LogFactoryUtil.getLog(PortalLDAPUtil.class);

}
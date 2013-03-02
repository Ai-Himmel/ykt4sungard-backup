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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.DuplicateUserEmailAddressException;
import com.liferay.portal.DuplicateUserIdException;
import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.RequiredLayoutException;
import com.liferay.portal.RequiredUserException;
import com.liferay.portal.ReservedUserEmailAddressException;
import com.liferay.portal.ReservedUserIdException;
import com.liferay.portal.SystemException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserFirstNameException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserIdValidator;
import com.liferay.portal.UserLastNameException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserSmsException;
import com.liferay.portal.language.LanguageException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.pwd.PwdToolkitUtil;
import com.liferay.portal.service.persistence.CompanyUtil;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.persistence.LayoutUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.AddressLocalServiceUtil;
import com.liferay.portal.service.spring.ColorSchemeLocalServiceUtil;
import com.liferay.portal.service.spring.ColorSchemeServiceUtil;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.service.spring.PasswordTrackerLocalServiceUtil;
import com.liferay.portal.service.spring.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalService;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.addressbook.service.spring.ABContactLocalServiceUtil;
import com.liferay.portlet.addressbook.service.spring.ABListLocalServiceUtil;
import com.liferay.portlet.admin.model.EmailConfig;
import com.liferay.portlet.admin.model.UserConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.portlet.biblejournal.service.spring.BJEntryLocalServiceUtil;
import com.liferay.portlet.biblejournal.service.spring.BJTopicLocalServiceUtil;
import com.liferay.portlet.biblejournal.service.spring.BJVerseLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsCategoryLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsEntryLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsLinkLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsUserLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderLocalServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalEventLocalServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalTaskLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLFileRankLocalServiceUtil;
import com.liferay.portlet.messageboards.service.spring.MBMessageFlagLocalServiceUtil;
import com.liferay.portlet.network.service.spring.NetworkAddressLocalServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCartLocalServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemLocalServiceUtil;
import com.liferay.portlet.wiki.service.spring.WikiNodeLocalServiceUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.Encryptor;
import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.StringUtil;
import com.liferay.util.Time;
import com.liferay.util.Validator;
import com.liferay.util.mail.MailMessage;

import java.io.IOException;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;

import javax.mail.internet.InternetAddress;

/**
 * <a href="UserLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class UserLocalServiceImpl implements UserLocalService {

	// Business methods

	public boolean addGroup(String userId, String groupId)
		throws PortalException, SystemException {

		return UserUtil.addGroup(userId, groupId);
	}

	public boolean addGroup(String userId, Group group)
		throws PortalException, SystemException {

		return UserUtil.addGroup(userId, group);
	}

	public boolean addRole(String userId, String roleId)
		throws PortalException, SystemException {

		return UserUtil.addRole(userId, roleId);
	}

	public boolean addRole(String userId, Role role)
		throws PortalException, SystemException {

		return UserUtil.addRole(userId, role);
	}

	public User addUser(
			String companyId, boolean autoUserId, String userId,
			boolean autoPassword, String password1, String password2,
			boolean passwordReset, String firstName, String middleName,
			String lastName, String nickName, boolean male, Date birthday,
			String emailAddress, Locale locale)
		throws PortalException, SystemException {

		userId = userId.trim();
		emailAddress = emailAddress.trim();

		boolean alwaysAutoUserId = GetterUtil.getBoolean(
			PropsUtil.get(PropsUtil.USERS_ID_ALWAYS_AUTOGENERATE));

		if (alwaysAutoUserId) {
			autoUserId = true;
		}

		validate(
			companyId, autoUserId, userId, autoPassword, password1, password2,
			firstName, lastName, emailAddress);

		Company company = CompanyUtil.findByPrimaryKey(companyId);

		if (autoUserId) {
			userId =
				companyId + "." +
				Long.toString(CounterServiceUtil.increment(
					User.class.getName() + "." + companyId));
		}

		User user = UserUtil.create(userId);

		if (autoPassword) {
			password1 = PwdToolkitUtil.generate();
		}

		int passwordsLifespan = GetterUtil.getInteger(
			PropsUtil.get(PropsUtil.PASSWORDS_LIFESPAN));

		Date expirationDate = null;
		if (passwordsLifespan > 0) {
			expirationDate = new Date(
				System.currentTimeMillis() + Time.DAY * passwordsLifespan);
		}

		user.setCompanyId(companyId);
		user.setCreateDate(new Date());
		user.setPassword(Encryptor.digest(password1));
		user.setPasswordEncrypted(true);
		user.setPasswordExpirationDate(expirationDate);
		user.setPasswordReset(passwordReset);
		user.setFirstName(firstName);
		user.setMiddleName(middleName);
		user.setLastName(lastName);
		user.setNickName(nickName);
		user.setMale(male);
		user.setBirthday(birthday);
		user.setEmailAddress(emailAddress);

		if (user.hasCompanyMx()) {
			MailServiceUtil.addUser(
				userId, password1, firstName, middleName, lastName,
				emailAddress);
		}

		User defaultUser = getDefaultUser(companyId);

		String greeting = null;
		try {
			greeting =
				LanguageUtil.get(companyId, locale, "welcome") +
				", " + user.getFullName() + "!";
		}
		catch (LanguageException le) {
			greeting = "Welcome, " + user.getFullName() + "!";
		}

		user.setLanguageId(locale.toString());
		user.setTimeZoneId(defaultUser.getTimeZoneId());
		user.setThemeId(defaultUser.getThemeId());
		user.setColorSchemeId(defaultUser.getColorSchemeId());
		user.setGreeting(greeting);
		user.setResolution(defaultUser.getResolution());
		user.setActive(true);

		UserUtil.update(user);
		/* we don not need these update 
		UserConfig userConfig =
			AdminConfigServiceUtil.getUserConfig(companyId);

		// Add user groups

		List groups = new ArrayList();

		String groupNames[] = userConfig.getGroupNames();

		for (int i = 0; groupNames != null && i < groupNames.length; i++) {
			try {
				groups.add(GroupUtil.findByC_N(companyId, groupNames[i]));
			}
			catch (NoSuchGroupException nsge) {
			}
		}

		UserUtil.setGroups(userId, groups);

		// Add user roles

		List roles = new ArrayList();

		String roleNames[] = userConfig.getRoleNames();

		for (int i = 0; roleNames != null && i < roleNames.length; i++) {
			try {
				Role role =
					RoleLocalServiceUtil.getRoleByName(companyId, roleNames[i]);

				roles.add(role);
			}
			catch (NoSuchRoleException nsre) {
			}
		}

		UserUtil.setRoles(userId, roles);

		// Send email notification

		EmailConfig registrationEmail = userConfig.getRegistrationEmail();

		if (registrationEmail != null && registrationEmail.isSend()) {
			String adminName = company.getAdminName();

			String subject = registrationEmail.getSubject();
			subject = StringUtil.replace(
				subject,
				new String[] {"[$ADMIN_EMAIL_ADDRESS$]", "[$ADMIN_NAME$]",
							  "[$COMPANY_MX$]", "[$COMPANY_NAME$]",
							  "[$PORTAL_URL$]",
							  "[$USER_EMAIL_ADDRESS$]", "[$USER_ID$]",
							  "[$USER_NAME$]", "[$USER_PASSWORD$]"},
				new String[] {company.getEmailAddress(), adminName,
							  company.getMx(), company.getName(),
							  company.getPortalURL(),
							  user.getEmailAddress(), user.getUserId(),
							  user.getFullName(), password1});

			String body = registrationEmail.getBody();
			body = StringUtil.replace(
				body,
				new String[] {"[$ADMIN_EMAIL_ADDRESS$]", "[$ADMIN_NAME$]",
							  "[$COMPANY_MX$]", "[$COMPANY_NAME$]",
							  "[$PORTAL_URL$]",
							  "[$USER_EMAIL_ADDRESS$]", "[$USER_ID$]",
							  "[$USER_NAME$]", "[$USER_PASSWORD$]"},
				new String[] {company.getEmailAddress(), adminName,
							  company.getMx(), company.getName(),
							  company.getPortalURL(),
							  user.getEmailAddress(), user.getUserId(),
							  user.getFullName(), password1});

			try {
				InternetAddress from =
					new InternetAddress(company.getEmailAddress(), adminName);

				InternetAddress[] to = new InternetAddress[] {
					new InternetAddress(
						user.getEmailAddress(), user.getFullName())
				};

				InternetAddress[] cc = null;

				InternetAddress[] bcc = new InternetAddress[] {
					new InternetAddress(company.getEmailAddress(), adminName)
				};

				MailServiceUtil.sendEmail(new MailMessage(
					from, to, cc, bcc, subject, body));
			}
			catch (IOException ioe) {
				throw new SystemException(ioe);
			}
		}
		*/
		// Update calendar birthday

		try {
			CalEventLocalServiceUtil.updateBirthday(userId);
		}
		catch (NoSuchUserException nsue) {
			nsue.printStackTrace();
		}

		return user;
	}

	public boolean deleteGroup(String userId, String groupId)
		throws PortalException, SystemException {

		return UserUtil.removeGroup(userId, groupId);
	}

	public boolean deleteGroup(String userId, Group group)
		throws PortalException, SystemException {

		return UserUtil.removeGroup(userId, group);
	}

	public boolean deleteRole(String userId, String roleId)
		throws PortalException, SystemException {

		return UserUtil.removeRole(userId, roleId);
	}

	public boolean deleteRole(String userId, Role role)
		throws PortalException, SystemException {

		return UserUtil.removeRole(userId, role);
	}

	public void deleteUser(String userId)
		throws PortalException, SystemException {

		if (!GetterUtil.getBoolean(PropsUtil.get(PropsUtil.USERS_DELETE))) {
			throw new RequiredUserException();
		}

		User user = UserUtil.findByPrimaryKey(userId);

		// Delete user's portrait

		ImageLocalUtil.remove(userId);

		// Delete user's color scheme

		ColorSchemeLocalServiceUtil.deleteColorScheme(userId);

		// Delete user's portlet preferences

		PortletPreferencesLocalServiceUtil.deleteAllByUser(userId);

		// Delete user's layouts

		LayoutLocalServiceUtil.deleteAll(userId);

		// Delete user's old passwords

		PasswordTrackerLocalServiceUtil.deleteAll(userId);

		// Delete user's addresses

		AddressLocalServiceUtil.deleteAll(
			user.getCompanyId(), User.class.getName(), userId);

		// Delete user's address book contacts and lists

		ABContactLocalServiceUtil.deleteAll(userId);
		ABListLocalServiceUtil.deleteAll(userId);

		// Delete user's Bible journal entries, topics, and verses

		BJEntryLocalServiceUtil.deleteAll(userId);
		BJTopicLocalServiceUtil.deleteAll(userId);
		BJVerseLocalServiceUtil.deleteAll(userId);

		// Delete user's blog links, entries, and categories

		BlogsUserLocalServiceUtil.deleteUser(userId);
		BlogsLinkLocalServiceUtil.deleteAll(userId);
		BlogsEntryLocalServiceUtil.deleteAll(userId);
		BlogsCategoryLocalServiceUtil.deleteAll(userId);

		// Delete user's bookmarks entries and folders

		BookmarksEntryLocalServiceUtil.deleteAllByUser(userId);
		BookmarksFolderLocalServiceUtil.deleteAllByUser(userId);

		// Delete user's calendar events and tasks

		CalEventLocalServiceUtil.deleteAllByUser(userId);
		CalTaskLocalServiceUtil.deleteAll(userId);

		// Delete user's document library file ranks

		DLFileRankLocalServiceUtil.deleteAll(userId);

		// Delete user's message boards message flags

		MBMessageFlagLocalServiceUtil.deleteAll(userId);

		// Delete user's network addresses

		NetworkAddressLocalServiceUtil.deleteAll(userId);

		// Delete user's shopping cart and supplier items

		ShoppingCartLocalServiceUtil.deleteAll(userId);
		ShoppingItemLocalServiceUtil.deleteAll(userId);

		// Delete user's wiki nodes

		WikiNodeLocalServiceUtil.deleteAll(userId);

		// Delete user's mail

		MailServiceUtil.deleteUser(userId);

		// Delete user

		UserUtil.remove(userId);
	}

	public List findByC_SMS(String companyId) throws SystemException {
		return UserFinder.findByC_SMS(companyId);
	}

	public User getDefaultUser(String companyId)
		throws PortalException, SystemException {

		return UserUtil.findByPrimaryKey(User.getDefaultUserId(companyId));
	}

	public List getLayouts(String userId) throws SystemException {
		return LayoutUtil.findByUserId(userId);
	}

	public List getLayouts(String userId, String parentLayoutId)
		throws SystemException {

		return LayoutUtil.findByU_P(userId, parentLayoutId);
	}

	public int getLayoutsSize(String userId) throws SystemException {
		return LayoutUtil.countByUserId(userId);
	}

	public List getGroups(String userId)
		throws PortalException, SystemException {

		return UserUtil.getGroups(userId);
	}

	public List getGroups(String userId, int begin, int end)
		throws PortalException, SystemException {

		return UserUtil.getGroups(userId, begin, end);
	}

	public int getGroupsSize(String userId) throws SystemException {
		return UserUtil.getGroupsSize(userId);
	}

	public List getProjProjects(String userId)
		throws PortalException, SystemException {

		return UserUtil.getProjProjects(userId);
	}

	public List getProjTasks(String userId)
		throws PortalException, SystemException {

		return UserUtil.getProjTasks(userId);
	}

	public List getRoles(String userId)
		throws PortalException, SystemException {

		return UserUtil.getRoles(userId);
	}

	public List getRoles(String userId, int begin, int end)
		throws PortalException, SystemException {

		return UserUtil.getRoles(userId, begin, end);
	}

	public int getRolesSize(String userId) throws SystemException {
		return UserUtil.getRolesSize(userId);
	}

	public User getUserByEmailAddress(
			String companyId, String emailAddress)
		throws PortalException, SystemException {

		emailAddress = emailAddress.trim();

		return UserUtil.findByC_EA(companyId, emailAddress);
	}

	public User getUserById(String userId)
		throws PortalException, SystemException {

		userId = userId.trim();

		return UserUtil.findByPrimaryKey(userId);
	}

	public User getUserById(String companyId, String userId)
		throws PortalException, SystemException {

		userId = userId.trim();

		return UserUtil.findByC_U(companyId, userId);
	}

	public boolean hasGroupById(String userId, String groupId)
		throws PortalException, SystemException {

		return UserUtil.containsGroup(userId, groupId);
	}

	public boolean hasGroupByName(
			String companyId, String userId, String name)
		throws PortalException, SystemException {

		Group group = GroupLocalServiceUtil.getGroupByName(companyId, name);

		return UserUtil.containsGroup(userId, group.getGroupId());
	}

	public void setGroups(String userId, String[] groupIds)
		throws PortalException, SystemException {

		UserUtil.setGroups(userId, groupIds);
	}

	public void setGroups(String userId, List groups)
		throws PortalException, SystemException {

		UserUtil.setGroups(userId, groups);
	}

	public void setLayouts(
			String userId, String parentLayoutId, String[] layoutIds)
		throws PortalException, SystemException {

		if (layoutIds == null) {
			return;
		}

		if (parentLayoutId.equals(Layout.DEFAULT_PARENT_LAYOUT_ID)) {
			if (layoutIds.length < 1) {
				throw new RequiredLayoutException();
			}

			Layout layout = LayoutUtil.findByPrimaryKey(
				new LayoutPK(layoutIds[0], userId));

			if (!layout.getType().equals(Layout.TYPE_PORTLET)) {
				throw new RequiredLayoutException();
			}
		}

		Set layoutIdsSet = new LinkedHashSet();

		for (int i = 0; i < layoutIds.length; i++) {
			layoutIdsSet.add(layoutIds[i]);
		}

		Set newLayoutIdsSet = CollectionFactory.getHashSet();

		Iterator itr = LayoutUtil.findByU_P(userId, parentLayoutId).iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			if (!layoutIdsSet.contains(layout.getLayoutId())) {
				LayoutLocalServiceUtil.deleteLayout(layout.getPrimaryKey());
			}
			else {
				newLayoutIdsSet.add(layout.getLayoutId());
			}
		}

		int priority = 0;

		itr = layoutIdsSet.iterator();

		while (itr.hasNext()) {
			String layoutId = (String)itr.next();

			Layout layout = LayoutUtil.findByPrimaryKey(
				new LayoutPK(layoutId, userId));

			layout.setPriority(priority++);

			LayoutUtil.update(layout);
		}
	}

	public void setProjProjects(String userId, String[] projProjectIds)
		throws PortalException, SystemException {

		UserUtil.setProjProjects(userId, projProjectIds);
	}

	public void setProjProjects(String userId, List projProjects)
		throws PortalException, SystemException {

		UserUtil.setProjProjects(userId, projProjects);
	}

	public void setProjTasks(String userId, String[] projTaskIds)
		throws PortalException, SystemException {

		UserUtil.setProjTasks(userId, projTaskIds);
	}

	public void setProjTasks(String userId, List projTasks)
		throws PortalException, SystemException {

		UserUtil.setProjTasks(userId, projTasks);
	}

	public void setRoles(String userId, String[] roleIds)
		throws PortalException, SystemException {

		UserUtil.setRoles(userId, roleIds);
	}

	public void setRoles(String userId, List roles)
		throws PortalException, SystemException {

		UserUtil.setRoles(userId, roles);
	}

	public User updateActive(String userId, boolean active)
		throws PortalException, SystemException {

		userId = userId.trim();

		User user = UserUtil.findByPrimaryKey(userId);

		user.setActive(active);

		UserUtil.update(user);

		return user;
	}

	public User updateLookAndFeel(
			String userId, String themeId, String colorSchemeId)
		throws PortalException, SystemException {

		userId = userId.trim();

		colorSchemeId = ColorSchemeServiceUtil.getColorScheme(
			themeId, colorSchemeId).getColorSchemeId();

		User user = UserUtil.findByPrimaryKey(userId);

		user.setThemeId(themeId);
		user.setColorSchemeId(colorSchemeId);

		UserUtil.update(user);

		return user;
	}

	public User updateUser(
			String userId, String password1, String password2,
			boolean passwordReset)
		throws PortalException, SystemException {

		userId = userId.trim();

		validate(userId, password1, password2);

		User user = UserUtil.findByPrimaryKey(userId);

		String oldEncPwd = user.getPassword();
		if (!user.isPasswordEncrypted()) {
			oldEncPwd = Encryptor.digest(user.getPassword());
		}

		String newEncPwd = Encryptor.digest(password1);

		int passwordsLifespan = GetterUtil.getInteger(
			PropsUtil.get(PropsUtil.PASSWORDS_LIFESPAN));

		Date expirationDate = null;
		if (passwordsLifespan > 0) {
			expirationDate = new Date(
				System.currentTimeMillis() + Time.DAY * passwordsLifespan);
		}

		if (user.hasCompanyMx()) {
			MailServiceUtil.updatePassword(userId, password1);
		}

		user.setPassword(newEncPwd);
		user.setPasswordEncrypted(true);
		user.setPasswordExpirationDate(expirationDate);
		user.setPasswordReset(passwordReset);

		UserUtil.update(user);

		PasswordTrackerLocalServiceUtil.trackPassword(userId, oldEncPwd);

		return user;
	}

	public User updateUser(
			String userId, String password, String firstName, String middleName,
			String lastName, String nickName, boolean male, Date birthday,
			String emailAddress, String smsId, String aimId, String icqId,
			String msnId, String ymId, String favoriteActivity,
			String favoriteBibleVerse, String favoriteFood,
			String favoriteMovie, String favoriteMusic, String languageId,
			String timeZoneId, String themeId, String colorSchemeId,
			String greeting, String resolution, String comments)
		throws PortalException, SystemException {

		userId = userId.trim();
		emailAddress = emailAddress.trim();

		validate(userId, firstName, lastName, emailAddress, smsId);

		User user = UserUtil.findByPrimaryKey(userId);

		user.setFirstName(firstName);
		user.setMiddleName(middleName);
		user.setLastName(lastName);
		user.setNickName(nickName);
		user.setMale(male);
		user.setBirthday(birthday);

		if (!emailAddress.equals(user.getEmailAddress())) {

			// test@test.com -> test@liferay.com

			if (!user.hasCompanyMx() && user.hasCompanyMx(emailAddress)) {
				MailServiceUtil.addUser(
					userId, password, firstName, middleName, lastName,
					emailAddress);
			}

			// test@liferay.com -> bob@liferay.com

			else if (user.hasCompanyMx() && user.hasCompanyMx(emailAddress)) {
				MailServiceUtil.updateEmailAddress(userId, emailAddress);
			}

			// test@liferay.com -> test@test.com

			else if (user.hasCompanyMx() && !user.hasCompanyMx(emailAddress)) {
				MailServiceUtil.deleteEmailAddress(userId);
			}

			user.setEmailAddress(emailAddress);
		}

		user.setSmsId(smsId);
		user.setAimId(aimId);
		user.setIcqId(icqId);
		user.setMsnId(msnId);
		user.setYmId(ymId);
		user.setFavoriteActivity(favoriteActivity);
		user.setFavoriteBibleVerse(favoriteBibleVerse);
		user.setFavoriteFood(favoriteFood);
		user.setFavoriteMovie(favoriteMovie);
		user.setFavoriteMusic(favoriteMusic);
		user.setLanguageId(languageId);
		user.setTimeZoneId(timeZoneId);
		user.setThemeId(themeId);
		user.setColorSchemeId(colorSchemeId);
		user.setGreeting(greeting);
		user.setResolution(resolution);
		user.setComments(comments);

		UserUtil.update(user);

		// Update calendar birthday

		CalEventLocalServiceUtil.updateBirthday(userId);

		return user;
	}

	public void validate(
			String companyId, boolean autoUserId, String userId,
			boolean autoPassword, String password1, String password2,
			String firstName, String lastName, String emailAddress)
		throws PortalException, SystemException {

		if (Validator.isNull(firstName)) {
			throw new UserFirstNameException();
		}
		/* chinese do not have separte names
		else if (Validator.isNull(lastName)) {
			throw new UserLastNameException();
		}*/

		if (!autoUserId) {
			if (Validator.isNull(userId)) {
				throw new UserIdException();
			}
			/*we do not need these validation
			UserIdValidator userIdValidator = (UserIdValidator)InstancePool.get(
				PropsUtil.get(PropsUtil.USERS_ID_VALIDATOR));

			if (userIdValidator != null) {
				if (!userIdValidator.validate(userId, companyId)) {
					throw new UserIdException();
				}
			}

			String[] anonymousNames = PrincipalSessionBean.ANONYMOUS_NAMES;

			for (int i = 0; i < anonymousNames.length; i++) {
				if (userId.equalsIgnoreCase(anonymousNames[i])) {
					throw new UserIdException();
				}
			}

			String[] companyIds = PortalInstances.getCompanyIds();

			for (int i = 0; i < companyIds.length; i++) {
				if (userId.indexOf(companyIds[i]) != -1) {
					throw new UserIdException();
				}
			}
			*/
			try {
				User user = UserUtil.findByPrimaryKey(userId);

				if (user != null) {
					throw new DuplicateUserIdException();
				}
			}
			catch (NoSuchUserException nsue) {
			}

			UserConfig userConfig =
				AdminConfigServiceUtil.getUserConfig(companyId);

			if (userConfig.hasReservedUserId(userId)) {
				throw new ReservedUserIdException();
			}
		}
		/*We do not need email format check
		if (!Validator.isEmailAddress(emailAddress)) {
			throw new UserEmailAddressException();
		}
		else {
			try {
				User user = UserUtil.findByC_EA(companyId, emailAddress);

				if (user != null) {
					throw new DuplicateUserEmailAddressException();
				}
			}
			catch (NoSuchUserException nsue) {
			}

			UserConfig userConfig =
				AdminConfigServiceUtil.getUserConfig(companyId);

			if (userConfig.hasReservedUserEmailAddress(emailAddress)) {
				throw new ReservedUserEmailAddressException();
			}
		}
		*/
		if (!autoPassword) {
			if (!password1.equals(password2)) {
				throw new UserPasswordException(
					UserPasswordException.PASSWORDS_DO_NOT_MATCH);
			}
			else if (!PwdToolkitUtil.validate(password1) ||
					 !PwdToolkitUtil.validate(password2)) {

				throw new UserPasswordException(
					UserPasswordException.PASSWORD_INVALID);
			}
		}
	}

	public void validate(String userId, String password1, String password2)
		throws PortalException, SystemException {

		if (!password1.equals(password2)) {
			throw new UserPasswordException(
				UserPasswordException.PASSWORDS_DO_NOT_MATCH);
		}
		else if (!PwdToolkitUtil.validate(password1) ||
				 !PwdToolkitUtil.validate(password2)) {

			throw new UserPasswordException(
				UserPasswordException.PASSWORD_INVALID);
		}
		else if (!PasswordTrackerLocalServiceUtil.isValidPassword(
					userId, password1)) {

			throw new UserPasswordException(
				UserPasswordException.PASSWORD_ALREADY_USED);
		}
	}

	public void validate(
			String userId, String firstName, String lastName,
			String emailAddress, String smsId)
		throws PortalException, SystemException {

		if (Validator.isNull(firstName)) {
			throw new UserFirstNameException();
		}
		else if (Validator.isNull(lastName)) {
			throw new UserLastNameException();
		}

		User user = UserUtil.findByPrimaryKey(userId);

		if (!Validator.isEmailAddress(emailAddress)) {
			throw new UserEmailAddressException();
		}
		else {
			try {
				if (!user.getEmailAddress().equals(emailAddress)) {
					if (UserUtil.findByC_EA(
							user.getCompanyId(), emailAddress) != null) {

						throw new DuplicateUserEmailAddressException();
					}
				}
			}
			catch (NoSuchUserException nsue) {
			}

			UserConfig userConfig =
				AdminConfigServiceUtil.getUserConfig(user.getCompanyId());

			if (userConfig.hasReservedUserEmailAddress(emailAddress)) {
				throw new ReservedUserEmailAddressException();
			}
		}

		if (Validator.isNotNull(smsId) && !Validator.isEmailAddress(smsId)) {
			throw new UserSmsException();
		}
	}

}
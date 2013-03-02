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

package com.liferay.portlet.messageboards.util;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.OrganizationLocalServiceUtil;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.service.UserGroupLocalServiceUtil;
import com.liferay.portal.service.UserGroupRoleLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.messageboards.model.MBBan;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBStatsUser;
import com.liferay.portlet.messageboards.model.impl.MBCategoryImpl;
import com.liferay.portlet.messageboards.service.MBCategoryLocalServiceUtil;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceUtil;
import com.liferay.util.Http;
import com.liferay.util.LocalizationUtil;

import java.io.IOException;

import java.util.Calendar;
import java.util.Date;

import javax.portlet.PortletPreferences;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBUtil {

	public static final String POP_PORTLET_PREFIX = "mb.";

	public static String getBreadcrumbs(
			long categoryId, long messageId, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if (messageId > 0) {
			MBMessage message = MBMessageLocalServiceUtil.getMessage(messageId);

			return getBreadcrumbs(null, message, pageContext, req, res);
		}
		else {
			MBCategory category = null;

			try {
				if ((categoryId > 0) &&
					(categoryId != MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID)) {

					category = MBCategoryLocalServiceUtil.getCategory(
						categoryId);
				}
			}
			catch (Exception e) {
			}

			return getBreadcrumbs(category, null, pageContext, req, res);
		}
	}

	public static String getBreadcrumbs(
			MBCategory category, MBMessage message, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if ((message != null) && (category == null)) {
			category = message.getCategory();
		}

		PortletURL categoriesURL = res.createRenderURL();

		WindowState windowState = req.getWindowState();

		if (windowState.equals(LiferayWindowState.POP_UP)) {
			categoriesURL.setWindowState(LiferayWindowState.POP_UP);

			categoriesURL.setParameter(
				"struts_action", "/message_boards/select_category");
		}
		else {
			categoriesURL.setWindowState(WindowState.MAXIMIZED);

			categoriesURL.setParameter("struts_action", "/message_boards/view");
			categoriesURL.setParameter(
				"categoryId",
				String.valueOf(MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID));
		}

		String categoriesLink =
			"<a href=\"" + categoriesURL.toString() + "\">" +
				LanguageUtil.get(pageContext, "categories") + "</a>";

		if (category == null) {
			return categoriesLink;
		}

		String breadcrumbs = StringPool.BLANK;

		if (category != null) {
			for (int i = 0;; i++) {
				category = category.toEscapedModel();

				PortletURL portletURL = res.createRenderURL();

				if (windowState.equals(LiferayWindowState.POP_UP)) {
					portletURL.setWindowState(LiferayWindowState.POP_UP);

					portletURL.setParameter(
						"struts_action", "/message_boards/select_category");
					portletURL.setParameter(
						"categoryId", String.valueOf(category.getCategoryId()));
				}
				else {
					portletURL.setWindowState(WindowState.MAXIMIZED);

					portletURL.setParameter(
						"struts_action", "/message_boards/view");
					portletURL.setParameter(
						"categoryId", String.valueOf(category.getCategoryId()));
				}

				String categoryLink =
					"<a href=\"" + portletURL.toString() + "\">" +
						category.getName() + "</a>";

				if (i == 0) {
					breadcrumbs = categoryLink;
				}
				else {
					breadcrumbs = categoryLink + " &raquo; " + breadcrumbs;
				}

				if (category.isRoot()) {
					break;
				}

				category = MBCategoryLocalServiceUtil.getCategory(
					category.getParentCategoryId());
			}
		}

		breadcrumbs = categoriesLink + " &raquo; " + breadcrumbs;

		if (message != null) {
			message = message.toEscapedModel();

			PortletURL messageURL = res.createRenderURL();

			messageURL.setWindowState(WindowState.MAXIMIZED);

			messageURL.setParameter(
				"struts_action", "/message_boards/view_message");
			messageURL.setParameter(
				"messageId", String.valueOf(message.getMessageId()));

			String messageLink =
				"<a href=\"" + messageURL.toString() + "\">" +
					message.getSubject() + "</a>";

			breadcrumbs = breadcrumbs + " &raquo; " + messageLink;
		}

		return breadcrumbs;
	}

	public static String getEmailFromAddress(PortletPreferences prefs) {
		String emailFromAddress = PropsUtil.get(
			PropsUtil.MESSAGE_BOARDS_EMAIL_FROM_ADDRESS);

		return prefs.getValue("email-from-address", emailFromAddress);
	}

	public static String getEmailFromName(PortletPreferences prefs) {
		String emailFromName = PropsUtil.get(
			PropsUtil.MESSAGE_BOARDS_EMAIL_FROM_NAME);

		return prefs.getValue("email-from-name", emailFromName);
	}

	public static boolean getEmailMessageAddedEnabled(
		PortletPreferences prefs) {

		String emailMessageAddedEnabled = prefs.getValue(
			"email-message-added-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageAddedEnabled)) {
			return GetterUtil.getBoolean(emailMessageAddedEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_ENABLED));
		}
	}

	public static String getEmailMessageAddedBody(PortletPreferences prefs)
		throws IOException {

		String emailMessageAddedBody = prefs.getValue(
			"email-message-added-body", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageAddedBody)) {
			return emailMessageAddedBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_BODY));
		}
	}

	public static String getEmailMessageAddedSignature(PortletPreferences prefs)
		throws IOException {

		String emailMessageAddedSignature = prefs.getValue(
			"email-message-added-signature", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageAddedSignature)) {
			return emailMessageAddedSignature;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_SIGNATURE));
		}
	}

	public static String getEmailMessageAddedSubjectPrefix(
			PortletPreferences prefs)
		throws IOException {

		String emailMessageAddedSubjectPrefix = prefs.getValue(
			"email-message-added-subject-prefix", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageAddedSubjectPrefix)) {
			return emailMessageAddedSubjectPrefix;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_ADDED_SUBJECT_PREFIX));
		}
	}

	public static boolean getEmailMessageUpdatedEnabled(
		PortletPreferences prefs) {

		String emailMessageUpdatedEnabled = prefs.getValue(
			"email-message-updated-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageUpdatedEnabled)) {
			return GetterUtil.getBoolean(emailMessageUpdatedEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_ENABLED));
		}
	}

	public static String getEmailMessageUpdatedBody(PortletPreferences prefs)
		throws IOException {

		String emailMessageUpdatedBody = prefs.getValue(
			"email-message-updated-body", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageUpdatedBody)) {
			return emailMessageUpdatedBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_BODY));
		}
	}

	public static String getEmailMessageUpdatedSignature(
			PortletPreferences prefs)
		throws IOException {

		String emailMessageUpdatedSignature = prefs.getValue(
			"email-message-updated-signature", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageUpdatedSignature)) {
			return emailMessageUpdatedSignature;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_SIGNATURE));
		}
	}

	public static String getEmailMessageUpdatedSubjectPrefix(
			PortletPreferences prefs)
		throws IOException {

		String emailMessageUpdatedSubject = prefs.getValue(
			"email-message-updated-subject-prefix", StringPool.BLANK);

		if (Validator.isNotNull(emailMessageUpdatedSubject)) {
			return emailMessageUpdatedSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.MESSAGE_BOARDS_EMAIL_MESSAGE_UPDATED_SUBJECT_PREFIX));
		}
	}

	public static String getMailId(String mx, long categoryId, long messageId) {
		StringMaker sm = new StringMaker();

		sm.append(StringPool.LESS_THAN);
		sm.append(POP_PORTLET_PREFIX);
		sm.append(categoryId);
		sm.append(StringPool.PERIOD);
		sm.append(messageId);
		sm.append(StringPool.AT);
		sm.append(PropsValues.POP_SERVER_SUBDOMAIN);
		sm.append(StringPool.PERIOD);
		sm.append(mx);
		sm.append(StringPool.GREATER_THAN);

		return sm.toString();
	}

	public static String getMailingListAddress(
		long categoryId, long messageId, String mx) {

		StringMaker sm = new StringMaker();

		sm.append(POP_PORTLET_PREFIX);
		sm.append(categoryId);
		sm.append(StringPool.PERIOD);
		sm.append(messageId);
		sm.append(StringPool.AT);
		sm.append(PropsValues.POP_SERVER_SUBDOMAIN);
		sm.append(StringPool.PERIOD);
		sm.append(mx);

		return sm.toString();
	}

	public static long getMessageId(String mailId) {
		int x = mailId.indexOf(StringPool.LESS_THAN) + 1;
		int y = mailId.indexOf(StringPool.AT);

		long messageId = 0;

		if ((x > 0 ) && (y != -1)) {
			String temp = mailId.substring(x, y);

			int z = temp.indexOf(StringPool.PERIOD);

			if (z != -1) {
				messageId = GetterUtil.getLong(temp.substring(z));
			}
		}

		return messageId;
	}

	public static String[] getThreadPriority(
			PortletPreferences prefs, String languageId, double value,
			ThemeDisplay themeDisplay)
		throws Exception {

		String[] priorities = LocalizationUtil.getPrefsValues(
			prefs, "priorities", languageId);

		String[] priorityPair = _findThreadPriority(
			value, themeDisplay, priorities);

		if (priorityPair == null) {
			String defaultLanguageId = LocaleUtil.toLanguageId(
				LocaleUtil.getDefault());

			priorities = LocalizationUtil.getPrefsValues(
				prefs, "priorities", defaultLanguageId);

			priorityPair = _findThreadPriority(value, themeDisplay, priorities);
		}

		return priorityPair;
	}

	public static Date getUnbanDate(MBBan ban, int expireInterval) {
		Date banDate = ban.getCreateDate();

		Calendar cal = Calendar.getInstance();

		cal.setTime(banDate);

		cal.add(Calendar.DATE, expireInterval);

		return cal.getTime();
	}

	public static String getUserRank(
			PortletPreferences prefs, String languageId, int posts)
		throws Exception {

		String rank = StringPool.BLANK;

		String[] ranks = LocalizationUtil.getPrefsValues(
			prefs, "ranks", languageId);

		for (int i = 0; i < ranks.length; i++) {
			String[] kvp = StringUtil.split(ranks[i], StringPool.EQUAL);

			String kvpName = kvp[0];
			int kvpPosts = GetterUtil.getInteger(kvp[1]);

			if (posts >= kvpPosts) {
				rank = kvpName;
			}
			else {
				break;
			}
		}

		return rank;
	}

	public static String getUserRank(
			PortletPreferences prefs, String languageId, MBStatsUser statsUser)
		throws Exception {

		String rank = StringPool.BLANK;

		Group group = GroupLocalServiceUtil.getGroup(
			statsUser.getGroupId());

		long companyId = group.getCompanyId();

		String[] ranks = LocalizationUtil.getPrefsValues(
			prefs, "ranks", languageId);

		for (int i = 0; i < ranks.length; i++) {
			String[] kvp = StringUtil.split(ranks[i], StringPool.EQUAL);

			String curRank = kvp[0];
			String curRankValue = kvp[1];

			String[] curRankValueKvp = StringUtil.split(
				curRankValue, StringPool.COLON);

			if (curRankValueKvp.length <= 1) {
				int kvpPosts = GetterUtil.getInteger(curRankValue);

				if (statsUser.getMessageCount() >= kvpPosts) {
					rank = curRank;
				}

				continue;
			}

			String entityType = curRankValueKvp[0];
			String entityValue = curRankValueKvp[1];

			try {
				if (_isEntityRank(
						companyId, statsUser, entityType, entityValue)) {

					return curRank;
				}
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e);
				}
			}
		}

		return rank;
	}

	public static boolean isAllowAnonymousPosting(PortletPreferences prefs) {
		String allowAnonymousPosting = prefs.getValue(
			"allow-anonymous-posting", StringPool.BLANK);

		if (Validator.isNotNull(allowAnonymousPosting)) {
			return GetterUtil.getBoolean(allowAnonymousPosting);
		}
		else {
			return PropsValues.MESSAGE_BOARDS_ANONYMOUS_POSTING_ENABLED;
		}
	}

	private static String[] _findThreadPriority(
		double value, ThemeDisplay themeDisplay, String[] priorities) {

		for (int i = 0; i < priorities.length; i++) {
			String[] priority = StringUtil.split(priorities[i]);

			try {
				String priorityName = priority[0];
				String priorityImage = priority[1];
				double priorityValue = GetterUtil.getDouble(priority[2]);

				if (value == priorityValue) {
					if (!priorityImage.startsWith(Http.HTTP)) {
						priorityImage =
							themeDisplay.getPathThemeImages() + priorityImage;
					}

					return new String[] {priorityName, priorityImage};
				}
			}
			catch (Exception e) {
			}
		}

		return null;
	}

	private static boolean _isEntityRank(
			long companyId, MBStatsUser statsUser, String entityType,
			String entityValue)
		throws Exception {

		long groupId = statsUser.getGroupId();
		long userId = statsUser.getUserId();

		if (entityType.equals("community-role") ||
			entityType.equals("organization-role")) {

			Role role = RoleLocalServiceUtil.getRole(companyId, entityValue);

			if (UserGroupRoleLocalServiceUtil.hasUserGroupRole(
					userId, groupId, role.getRoleId())) {

				return true;
			}
		}
		else if (entityType.equals("organization")) {
			Organization organization =
				OrganizationLocalServiceUtil.getOrganization(
					companyId, entityValue);

			if (OrganizationLocalServiceUtil.hasUserOrganization(
					userId, organization.getOrganizationId())) {

				return true;
			}
		}
		else if (entityType.equals("regular-role")) {
			if (RoleLocalServiceUtil.hasUserRole(
					userId, companyId, entityValue, true)) {

				return true;
			}
		}
		else if (entityType.equals("user-group")) {
			UserGroup userGroup = UserGroupLocalServiceUtil.getUserGroup(
				companyId, entityValue);

			if (UserLocalServiceUtil.hasUserGroupUser(
					userGroup.getUserGroupId(), userId)) {

				return true;
			}
		}

		return false;
	}

	private static Log _log = LogFactory.getLog(MBUtil.class);

}
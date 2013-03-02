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

package com.liferay.portlet.messageboards.action;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.util.LocalizationUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="ConfigurationActionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ConfigurationActionImpl implements ConfigurationAction {

	public void processAction(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		String portletResource = ParamUtil.getString(
			req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, false, true);

		String tabs2 = ParamUtil.getString(req, "tabs2");

		if (tabs2.equals("anonymous-posting")) {
			updateAnonymousPosting(req, prefs);
		}
		else if (tabs2.equals("email-from")) {
			updateEmailFrom(req, prefs);
		}
		else if (tabs2.equals("message-added-email")) {
			updateEmailMessageAdded(req, prefs);
		}
		else if (tabs2.equals("message-updated-email")) {
			updateEmailMessageUpdated(req, prefs);
		}
		else if (tabs2.equals("rss")) {
			updateRSS(req, prefs);
		}
		else if (tabs2.equals("thread-priorities")) {
			updateThreadPriorities(req, prefs);
		}
		else if (tabs2.equals("user-ranks")) {
			updateUserRanks(req, prefs);
		}

		if (SessionErrors.isEmpty(req)) {
			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/message_boards/configuration.jsp";
	}

	protected void updateAnonymousPosting(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String allowAnonymousPosting = ParamUtil.getString(
			req, "allowAnonymousPosting");

		prefs.setValue("allow-anonymous-posting", allowAnonymousPosting);
	}

	protected void updateEmailFrom(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailFromName = ParamUtil.getString(req, "emailFromName");
		String emailFromAddress = ParamUtil.getString(req, "emailFromAddress");

		if (Validator.isNull(emailFromName)) {
			SessionErrors.add(req, "emailFromName");
		}
		else if (!Validator.isEmailAddress(emailFromAddress) &&
				 !Validator.isVariableTerm(emailFromAddress)) {

			SessionErrors.add(req, "emailFromAddress");
		}
		else {
			prefs.setValue("email-from-name", emailFromName);
			prefs.setValue("email-from-address", emailFromAddress);
		}
	}

	protected void updateEmailMessageAdded(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailMessageAddedEnabled = ParamUtil.getString(
			req, "emailMessageAddedEnabled");
		String emailMessageAddedSubjectPrefix = ParamUtil.getString(
			req, "emailMessageAddedSubjectPrefix");
		String emailMessageAddedBody = ParamUtil.getString(
			req, "emailMessageAddedBody");
		String emailMessageAddedSignature = ParamUtil.getString(
			req, "emailMessageAddedSignature");

		if (Validator.isNull(emailMessageAddedSubjectPrefix)) {
			SessionErrors.add(req, "emailMessageAddedSubjectPrefix");
		}
		else if (Validator.isNull(emailMessageAddedBody)) {
			SessionErrors.add(req, "emailMessageAddedBody");
		}
		else {
			prefs.setValue(
				"email-message-added-enabled", emailMessageAddedEnabled);
			prefs.setValue(
				"email-message-added-subject-prefix",
				emailMessageAddedSubjectPrefix);
			prefs.setValue("email-message-added-body", emailMessageAddedBody);
			prefs.setValue(
				"email-message-added-signature", emailMessageAddedSignature);
		}
	}

	protected void updateEmailMessageUpdated(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailMessageUpdatedEnabled = ParamUtil.getString(
			req, "emailMessageUpdatedEnabled");
		String emailMessageUpdatedSubjectPrefix = ParamUtil.getString(
			req, "emailMessageUpdatedSubjectPrefix");
		String emailMessageUpdatedBody = ParamUtil.getString(
			req, "emailMessageUpdatedBody");
		String emailMessageUpdatedSignature = ParamUtil.getString(
			req, "emailMessageUpdatedSignature");

		if (Validator.isNull(emailMessageUpdatedSubjectPrefix)) {
			SessionErrors.add(req, "emailMessageUpdatedSubjectPrefix");
		}
		else if (Validator.isNull(emailMessageUpdatedBody)) {
			SessionErrors.add(req, "emailMessageUpdatedBody");
		}
		else {
			prefs.setValue(
				"email-message-updated-enabled", emailMessageUpdatedEnabled);
			prefs.setValue(
				"email-message-updated-subject-prefix",
				emailMessageUpdatedSubjectPrefix);
			prefs.setValue(
				"email-message-updated-body", emailMessageUpdatedBody);
			prefs.setValue(
				"email-message-updated-signature",
				emailMessageUpdatedSignature);
		}
	}

	protected void updateRSS(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		int rssDelta = ParamUtil.getInteger(req, "rssDelta");
		String rssDisplayStyle = ParamUtil.getString(req, "rssDisplayStyle");
		String rssFormat = ParamUtil.getString(req, "rssFormat");

		prefs.setValue("rss-delta", String.valueOf(rssDelta));
		prefs.setValue("rss-display-style", rssDisplayStyle);
		prefs.setValue("rss-format", rssFormat);
	}

	protected void updateThreadPriorities(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		Locale[] locales = LanguageUtil.getAvailableLocales();

		for (int i = 0; i < locales.length; i++) {
			String languageId = LocaleUtil.toLanguageId(locales[i]);

			List priorities = new ArrayList();

			for (int j = 0; j < 10; j++) {
				String name = ParamUtil.getString(
					req, "priorityName" + j + "_" + languageId);
				String image = ParamUtil.getString(
					req, "priorityImage" + j + "_" + languageId);
				double value = ParamUtil.getDouble(
					req, "priorityValue" + j + "_" + languageId);

				if (Validator.isNotNull(name) || Validator.isNotNull(image) ||
					(value != 0.0)) {

					priorities.add(
						name + StringPool.COMMA + image + StringPool.COMMA +
							value);
				}
			}

			LocalizationUtil.setPrefsValues(
				prefs, "priorities", languageId,
				(String[])priorities.toArray(new String[0]));
		}
	}

	protected void updateUserRanks(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		Locale[] locales = LanguageUtil.getAvailableLocales();

		for (int i = 0; i < locales.length; i++) {
			String languageId = LocaleUtil.toLanguageId(locales[i]);

			String[] ranks = StringUtil.split(
				ParamUtil.getString(req, "ranks_" + languageId),
				StringPool.NEW_LINE);

			Map map = new TreeMap();

			for (int j = 0; j < ranks.length; j++) {
				String[] kvp = StringUtil.split(ranks[j], StringPool.EQUAL);

				String kvpName = kvp[0];
				String kvpValue = kvp[1];

				map.put(kvpValue, kvpName);
			}

			ranks = new String[map.size()];

			int count = 0;

			Iterator itr = map.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				String kvpValue = (String)entry.getKey();
				String kvpName = (String)entry.getValue();

				ranks[count++] = kvpName + StringPool.EQUAL + kvpValue;
			}

			LocalizationUtil.setPrefsValues(prefs, "ranks", languageId, ranks);
		}
	}

}
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

package com.liferay.portlet.webform.action;

import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="ConfigurationActionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
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

		String title = ParamUtil.getString(req, "title");
		String description = ParamUtil.getString(req, "description");
		boolean requireCaptcha = ParamUtil.getBoolean(req, "requireCaptcha");
		String successURL = ParamUtil.getString(req, "successURL");
		boolean sendAsEmail = ParamUtil.getBoolean(req, "sendAsEmail");
		String subject = ParamUtil.getString(req, "subject");
		String emailAddress = ParamUtil.getString(req, "emailAddress");
		boolean saveToFile = ParamUtil.getBoolean(req, "saveToFile");
		String fileName = ParamUtil.getString(req, "fileName");

		String portletResource = ParamUtil.getString(req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, true, true);

		if (Validator.isNull(title)) {
			SessionErrors.add(req, "titleRequired");
		}

		if (Validator.isNull(subject)) {
			SessionErrors.add(req, "subjectRequired");
		}

		if (!sendAsEmail && !saveToFile){
			SessionErrors.add(req, "handlingRequired");
		}

		if (sendAsEmail) {
			if (Validator.isNull(emailAddress)) {
				SessionErrors.add(req, "emailAddressRequired");
			}
			else if (!Validator.isEmailAddress(emailAddress)) {
				SessionErrors.add(req, "emailAddressInvalid");
			}
		}

		if (saveToFile) {

			// Check if server can create a file as specified

			try {
				FileOutputStream fos = new FileOutputStream(fileName, true);

				fos.close();
			}
			catch (SecurityException es) {
				SessionErrors.add(req, "fileNameInvalid");
			}
			catch (FileNotFoundException fnfe) {
				SessionErrors.add(req, "fileNameInvalid");
			}
		}

		if (!SessionErrors.isEmpty(req)) {
			return;
		}

		prefs.setValue("title", title);
		prefs.setValue("description", description);
		prefs.setValue("requireCaptcha", String.valueOf(requireCaptcha));
		prefs.setValue("successURL", successURL);
		prefs.setValue("sendAsEmail", String.valueOf(sendAsEmail));
		prefs.setValue("subject", subject);
		prefs.setValue("emailAddress", emailAddress);
		prefs.setValue("saveToFile", String.valueOf(saveToFile));
		prefs.setValue("fileName", fileName);

		int i = 1;

		String fieldLabel = ParamUtil.getString(req, "fieldLabel" + i);
		String fieldType = ParamUtil.getString(req, "fieldType" + i);
		boolean fieldOptional = ParamUtil.getBoolean(req, "fieldOptional" + i);
		String fieldOptions = ParamUtil.getString(req, "fieldOptions" + i);

		while ((i == 1) || (fieldLabel.trim().length() > 0)) {
			prefs.setValue("fieldLabel" + i, fieldLabel);
			prefs.setValue("fieldType" + i, fieldType);
			prefs.setValue("fieldOptional" + i, String.valueOf(fieldOptional));
			prefs.setValue("fieldOptions" + i, fieldOptions);

			i++;

			fieldLabel = ParamUtil.getString(req, "fieldLabel" + i);
			fieldType = ParamUtil.getString(req, "fieldType" + i);
			fieldOptional = ParamUtil.getBoolean(req, "fieldOptional" + i);
			fieldOptions = ParamUtil.getString(req, "fieldOptions" + i);
		}

		// Clear previous preferences that are now blank

		fieldLabel = prefs.getValue("fieldLabel" + i, StringPool.BLANK);

		while (fieldLabel.trim().length() > 0) {
			prefs.setValue("fieldLabel" + i, StringPool.BLANK);
			prefs.setValue("fieldType" + i, StringPool.BLANK);
			prefs.setValue("fieldOptional" + i, StringPool.BLANK);
			prefs.setValue("fieldOptions" + i, StringPool.BLANK);

			i++;

			fieldLabel = prefs.getValue("fieldLabel" + i, StringPool.BLANK);
		}

		if (SessionErrors.isEmpty(req)) {
			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/web_form/configuration.jsp";
	}

}
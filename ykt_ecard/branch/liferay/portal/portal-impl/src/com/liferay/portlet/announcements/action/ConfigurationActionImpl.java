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

package com.liferay.portlet.announcements.action;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.announcements.AnnouncementsContentException;
import com.liferay.util.LocalizationUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

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

		try {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			if (!cmd.equals(Constants.UPDATE)) {
				return;
			}

			String content = ParamUtil.getString(req, "content");

			if (Validator.isNull(content)) {
				throw new AnnouncementsContentException();
			}

			String portletResource = ParamUtil.getString(
				req, "portletResource");

			String languageId = LanguageUtil.getLanguageId(req);

			PortletPreferences prefs =
				PortletPreferencesFactoryUtil.getPortletSetup(
					req, portletResource, false, false);

			LocalizationUtil.setPrefsValue(
				prefs, "content", languageId, content);

			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
		catch (AnnouncementsContentException ace) {
			SessionErrors.add(req, ace.getClass().getName());
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/announcements/configuration.jsp";
	}

}
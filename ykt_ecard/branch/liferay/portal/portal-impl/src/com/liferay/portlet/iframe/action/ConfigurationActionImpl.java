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

package com.liferay.portlet.iframe.action;

import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.util.Http;
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

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		String src = ParamUtil.getString(req, "src");

		if (!src.startsWith("/") &&
			!StringUtil.startsWith(src, "http://") &&
			!StringUtil.startsWith(src, "https://") &&
			!StringUtil.startsWith(src, "mhtml://")) {

			src = Http.getProtocol(req) + "://" + src;
		}

		boolean relative = ParamUtil.getBoolean(req, "relative");

		boolean auth = ParamUtil.getBoolean(req, "auth");
		String authType = ParamUtil.getString(req, "authType");
		String formMethod = ParamUtil.getString(req, "formMethod");
		String userName = ParamUtil.getString(req, "userName");
		String password = ParamUtil.getString(req, "password");
		String hiddenVariables = ParamUtil.getString(req, "hiddenVariables");

		String[] htmlAttributes = StringUtil.split(ParamUtil.getString(
			req, "htmlAttributes"), "\n");

		String portletResource = ParamUtil.getString(
			req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, true, true);

		prefs.setValue("src", src);
		prefs.setValue("relative", String.valueOf(relative));

		prefs.setValue("auth", String.valueOf(auth));
		prefs.setValue("auth-type", authType);
		prefs.setValue("form-method", formMethod);
		prefs.setValue("user-name", userName);
		prefs.setValue("password", password);
		prefs.setValue("hidden-variables", hiddenVariables);

		for (int i = 0; i < htmlAttributes.length; i++) {
			int pos = htmlAttributes[i].indexOf("=");

			if (pos != -1) {
				String key = htmlAttributes[i].substring(0, pos);
				String value = htmlAttributes[i].substring(
					pos + 1, htmlAttributes[i].length());

				prefs.setValue(key, value);
			}
		}

		prefs.store();

		SessionMessages.add(req, config.getPortletName() + ".doConfigure");
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/iframe/configuration.jsp";
	}

}
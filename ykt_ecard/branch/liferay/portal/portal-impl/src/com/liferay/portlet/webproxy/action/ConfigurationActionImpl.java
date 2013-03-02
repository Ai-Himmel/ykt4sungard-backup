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

package com.liferay.portlet.webproxy.action;

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

		String initUrl = ParamUtil.getString(req, "initUrl");

		if (!initUrl.startsWith("/") &&
			!StringUtil.startsWith(initUrl, "http://") &&
			!StringUtil.startsWith(initUrl, "https://") &&
			!StringUtil.startsWith(initUrl, "mhtml://")) {

			initUrl = Http.getProtocol(req) + "://" + initUrl;
		}

		String scope = ParamUtil.getString(req, "scope");
		String proxyHost = ParamUtil.getString(req, "proxyHost");
		String proxyPort = ParamUtil.getString(req, "proxyPort");
		String proxyAuthentication = ParamUtil.getString(
			req, "proxyAuthentication");
		String proxyAuthenticationUsername = ParamUtil.getString(
			req, "proxyAuthenticationUsername");
		String proxyAuthenticationPassword = ParamUtil.getString(
			req, "proxyAuthenticationPassword");
		String proxyAuthenticationHost = ParamUtil.getString(
			req, "proxyAuthenticationHost");
		String proxyAuthenticationDomain = ParamUtil.getString(
			req, "proxyAuthenticationDomain");
		String stylesheet = ParamUtil.getString(req, "stylesheet");

		String portletResource = ParamUtil.getString(
			req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, true, true);

		prefs.setValue("initUrl", initUrl);
		prefs.setValue("scope", scope);
		prefs.setValue("proxyHost", proxyHost);
		prefs.setValue("proxyPort", proxyPort);
		prefs.setValue("proxyAuthentication", proxyAuthentication);
		prefs.setValue(
			"proxyAuthenticationUsername", proxyAuthenticationUsername);
		prefs.setValue(
			"proxyAuthenticationPassword", proxyAuthenticationPassword);
		prefs.setValue("proxyAuthenticationHost", proxyAuthenticationHost);
		prefs.setValue("proxyAuthenticationDomain", proxyAuthenticationDomain);
		prefs.setValue("stylesheet", stylesheet);

		prefs.store();

		SessionMessages.add(req, config.getPortletName() + ".doConfigure");
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/web_proxy/configuration.jsp";
	}

}
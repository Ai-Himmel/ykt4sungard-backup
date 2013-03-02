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

package com.liferay.portlet.httpbridge.servlet;

import com.httpbridge.webproxy.cookie.SessionCookieCan;
import com.httpbridge.webproxy.http.TaskController;
import com.httpbridge.webproxy.ui.SessionData;
import com.httpbridge.webproxy.user.IpRuntime;
import com.httpbridge.webproxy.user.UserManager;
import com.httpbridge.webproxy.user.UserRuntime;

import com.liferay.portal.util.PortalUtil;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.servlet.DynamicServletRequest;

import java.io.IOException;

import java.util.Enumeration;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

/**
 * <a href="HttpBridgeServletRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class HttpBridgeServletRequest extends DynamicServletRequest {

	public static final String LOCALHOST_ADDR = "127.0.0.1";

	public HttpBridgeServletRequest(HttpServletRequest req,
									String queryString) {

		super(req);

		_queryString = queryString;

		HttpSession ses = req.getSession();

		SessionData httpBridgeSession =
			(SessionData)ses.getAttribute(SessionData.SESSION_KEY);

		if (httpBridgeSession == null) {
			String userId = "guest";
			String userIp = getRemoteAddr();

			UserRuntime userRuntime = UserManager.getUserRuntime(userId);
			IpRuntime ipRuntime = userRuntime.getIpRuntime(userIp, true);

			SessionCookieCan sessionCookieCan =
				new SessionCookieCan(ses.getId(), userId, userIp);

			httpBridgeSession = new SessionData(ipRuntime, sessionCookieCan);

			ses.setAttribute(SessionData.SESSION_KEY, httpBridgeSession);
		}

	}

	public ServletInputStream getInputStream() throws IOException {
		FastStringBuffer sb = new FastStringBuffer();

		Enumeration enu = getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();
			String[] values = getParameterValues(name);

			for (int i = 0; i < values.length; i++) {
				if (!PortalUtil.isReservedParameter(name)) {
					if (!name.startsWith(TaskController.bridgeGotoTag)) {
						sb.append(name);
						sb.append(StringPool.EQUAL);
						sb.append(Http.encodeURL(values[i]));
						sb.append(StringPool.AMPERSAND);
					}
				}
			}
		}

		if (sb.lastIndexOf(StringPool.AMPERSAND) == (sb.length() - 1)) {
			sb.deleteCharAt(sb.length() - 1);
		}

		if (sb.indexOf("j_username") != -1) {
			return super.getInputStream();
		}

		return new HttpBridgeServletInputStream(sb.toString());
	}

	public String getQueryString() {
		return _queryString;
	}

	public String getRemoteAddr() {
		String remoteAddr = super.getRemoteAddr();

		if (Validator.isNull(remoteAddr)) {
			remoteAddr = LOCALHOST_ADDR;
		}

		return remoteAddr;
	}

	private String _queryString;

}
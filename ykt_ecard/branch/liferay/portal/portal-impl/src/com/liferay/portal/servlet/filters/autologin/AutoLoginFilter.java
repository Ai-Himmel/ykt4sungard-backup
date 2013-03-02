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

package com.liferay.portal.servlet.filters.autologin;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.AutoLogin;
import com.liferay.portal.security.pwd.PwdEncryptor;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.ProtectedServletRequest;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * <a href="AutoLoginFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class AutoLoginFilter extends BaseFilter {

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		HttpServletRequest httpReq = (HttpServletRequest)req;
		HttpServletResponse httpRes = (HttpServletResponse)res;

		HttpSession ses = httpReq.getSession();

		String remoteUser = httpReq.getRemoteUser();
		String jUserName = (String)ses.getAttribute("j_username");

		if ((remoteUser == null) && (jUserName == null)) {
			for (int i = 0; i < PropsValues.AUTO_LOGIN_HOOKS.length; i++) {
				AutoLogin autoLogin = (AutoLogin)InstancePool.get(
					PropsValues.AUTO_LOGIN_HOOKS[i]);

				try {
					String[] credentials = autoLogin.login(httpReq, httpRes);

					String redirect = (String)req.getAttribute(
						AutoLogin.AUTO_LOGIN_REDIRECT);

					if (redirect != null) {
						httpRes.sendRedirect(redirect);

						return;
					}

					String loginRemoteUser = getLoginRemoteUser(
						httpReq, httpRes, ses, credentials);

					if (loginRemoteUser != null) {
						req = new ProtectedServletRequest(
							httpReq, loginRemoteUser);

						if (PropsValues.PORTAL_JAAS_ENABLE) {
							return;
						}
					}
				}
				catch (Exception e) {
					_log.warn(e, e);
					_log.error(e.getMessage());
				}
			}
		}

		doFilter(AutoLoginFilter.class, req, res, chain);
	}

	protected String getLoginRemoteUser(
			HttpServletRequest req, HttpServletResponse res, HttpSession ses,
			String[] credentials)
		throws Exception {

		if ((credentials != null) && (credentials.length == 3)) {
			String jUsername = credentials[0];
			String jPassword = credentials[1];
			boolean encPwd = GetterUtil.getBoolean(credentials[2]);

			if (Validator.isNotNull(jUsername) &&
				Validator.isNotNull(jPassword)) {

				try {
					long userId = GetterUtil.getLong(jUsername);

					if (userId > 0) {
						User user = UserLocalServiceUtil.getUserById(userId);

						if (user.isLockout()) {
							return null;
						}
					}
					else {
						return null;
					}
				}
				catch (NoSuchUserException nsue) {
					return null;
				}

				ses.setAttribute("j_username", jUsername);

				// Not having access to the unencrypted password
				// will not allow you to connect to external
				// resources that require it (mail server)

				if (encPwd) {
					ses.setAttribute("j_password", jPassword);
				}
				else {
					ses.setAttribute(
						"j_password", PwdEncryptor.encrypt(jPassword));

					ses.setAttribute(WebKeys.USER_PASSWORD, jPassword);
				}

				if (PropsValues.PORTAL_JAAS_ENABLE) {
					res.sendRedirect(
						PortalUtil.getPathMain() + "/portal/touch_protected");
				}

				return jUsername;
			}
		}

		return null;
	}

	private static Log _log = LogFactoryUtil.getLog(AutoLoginFilter.class);

}
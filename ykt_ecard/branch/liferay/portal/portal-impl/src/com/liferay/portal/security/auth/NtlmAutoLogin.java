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

package com.liferay.portal.security.auth;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.User;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;

import javax.naming.directory.SearchResult;
import javax.naming.ldap.LdapContext;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="NtlmAutoLogin.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class NtlmAutoLogin implements AutoLogin {

	public String[] login(HttpServletRequest req, HttpServletResponse res)
		throws AutoLoginException {

		String[] credentials = null;

		try {
			long companyId = PortalUtil.getCompanyId(req);

			if (!PortalLDAPUtil.isNtlmEnabled(companyId)) {
				return credentials;
			}

			String screenName = (String)req.getAttribute(
				WebKeys.NTLM_REMOTE_USER);

			if (screenName == null) {
				return credentials;
			}

			req.removeAttribute(WebKeys.NTLM_REMOTE_USER);

			User user = getUser(companyId, screenName);

			if (user != null) {
				credentials = new String[3];

				credentials[0] = String.valueOf(user.getUserId());
				credentials[1] = user.getPassword();
				credentials[2] = Boolean.TRUE.toString();
			}
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}

		return credentials;
	}

	protected User getUser(long companyId, String screenName) throws Exception {
		SearchResult result = (SearchResult)PortalLDAPUtil.getUser(
			companyId, screenName);

		if (result == null) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"No user was found in LDAP with screenName " + screenName);
			}

			return null;
		}

		LdapContext ctx = PortalLDAPUtil.getContext(companyId);

		User user = PortalLDAPUtil.importLDAPUser(
			companyId, ctx, result.getAttributes(), StringPool.BLANK, false);

		ctx.close();

		return user;
	}

	private static Log _log = LogFactory.getLog(NtlmAutoLogin.class);

}
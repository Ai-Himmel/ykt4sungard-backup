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

import com.liferay.portal.kernel.util.KeyValuePair;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.CookieKeys;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.CookieUtil;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="RememberMeAutoLogin.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RememberMeAutoLogin implements AutoLogin {

	public String[] login(HttpServletRequest req, HttpServletResponse res)
		throws AutoLoginException {

		try {
			String[] credentials = null;

			String autoUserId = CookieUtil.get(req.getCookies(), CookieKeys.ID);
			String autoPassword =
				CookieUtil.get(req.getCookies(), CookieKeys.PASSWORD);

			if (Validator.isNotNull(autoUserId) &&
				Validator.isNotNull(autoPassword)) {

				Company company = PortalUtil.getCompany(req);

				KeyValuePair kvp = null;

				if (company.isAutoLogin()) {
					kvp = UserLocalServiceUtil.decryptUserId(
						company.getCompanyId(), autoUserId, autoPassword);

					credentials = new String[3];

					credentials[0] = kvp.getKey();
					credentials[1] = kvp.getValue();
					credentials[2] = Boolean.FALSE.toString();
				}
			}

			return credentials;
		}
		catch (Exception e) {
			_log.warn(e, e);

			Cookie cookie = new Cookie(CookieKeys.ID, StringPool.BLANK);

			cookie.setMaxAge(0);
			cookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, cookie);

			cookie = new Cookie(CookieKeys.PASSWORD, StringPool.BLANK);

			cookie.setMaxAge(0);
			cookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, cookie);

			throw new AutoLoginException(e);
		}
	}

	private static Log _log = LogFactory.getLog(RememberMeAutoLogin.class);

}
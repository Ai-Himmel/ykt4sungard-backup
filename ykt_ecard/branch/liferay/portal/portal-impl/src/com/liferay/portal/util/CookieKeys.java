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

package com.liferay.portal.util;

import com.liferay.portal.CookieNotSupportedException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.CookieUtil;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="CookieKeys.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Minhchau Dang
 *
 */
public class CookieKeys {

	public static final String COOKIE_SUPPORT = "COOKIE_SUPPORT";

	public static final String COMPANY_ID = "COMPANY_ID";

	public static final String GUEST_LANGUAGE_ID = "GUEST_LANGUAGE_ID";

	public static final String ID = "ID";

	public static final String LOGIN = "LOGIN";

	public static final String PASSWORD = "PASSWORD";

	public static final String SCREEN_NAME = "SCREEN_NAME";

	public static final int MAX_AGE = 31536000;

	public static void addCookie(HttpServletResponse res, Cookie cookie) {
		if (PropsValues.SESSION_ENABLE_PERSISTENT_COOKIES) {
			if (!PropsValues.TCK_URL) {

				// Setting a cookie will cause the TCK to lose its ability
				// to track sessions

				res.addCookie(cookie);
			}
		}
	}

	public static void addSupportCookie(HttpServletResponse res) {
		Cookie cookieSupportCookie =
			new Cookie(CookieKeys.COOKIE_SUPPORT, "true");

		cookieSupportCookie.setPath("/");
		cookieSupportCookie.setMaxAge(CookieKeys.MAX_AGE);

		addCookie(res, cookieSupportCookie);
	}

	public static String getDomain(HttpServletRequest req) {

		// See LEP-4602 and	LEP-4618.

		if (Validator.isNotNull(PropsValues.SESSION_COOKIE_DOMAIN)) {
			return PropsValues.SESSION_COOKIE_DOMAIN;
		}

		String host = req.getServerName();

		return getDomain(host);
	}

	public static String getDomain(String host) {

		// See LEP-4602 and LEP-4645.

		if (host == null) {
			return null;
		}

		int x = host.lastIndexOf(StringPool.PERIOD);

		if (x <= 0) {
			return null;
		}

		int y = host.lastIndexOf(StringPool.PERIOD, x - 1);

		if (y <= 0) {
			return StringPool.PERIOD + host;
		}

		int z = host.lastIndexOf(StringPool.PERIOD, y - 1);

		String domain = null;

		if (z <= 0) {
			domain = host.substring(y);
		}
		else {
			domain = host.substring(z);
		}

		return domain;
	}

	public static void validateSupportCookie(HttpServletRequest req)
		throws CookieNotSupportedException {

		if (PropsValues.SESSION_ENABLE_PERSISTENT_COOKIES &&
			PropsValues.SESSION_TEST_COOKIE_SUPPORT) {

			String cookieSupport = CookieUtil.get(
				req.getCookies(), CookieKeys.COOKIE_SUPPORT);

			if (Validator.isNull(cookieSupport)) {
				throw new CookieNotSupportedException();
			}
		}
	}

}
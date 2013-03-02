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

package com.liferay.util;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;

import javax.servlet.http.Cookie;

/**
 * <a href="CookieUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CookieUtil {

	public static String get(Cookie[] cookies, String name) {
		if ((cookies != null) && (cookies.length > 0)) {
			for (int i = 0; i < cookies.length; i++) {
				String cookieName = GetterUtil.getString(cookies[i].getName());

				if (cookieName.equalsIgnoreCase(name)) {
					return cookies[i].getValue();
				}
			}
		}

		return null;
	}

	public static String get(String cookie, String tag) {
		if (cookie == null) {
			return "";
		}

		tag = tag + "=";

		if (cookie.startsWith(tag)) {
			int y = cookie.indexOf(';');

			return cookie.substring(tag.length(), y);
		}

		tag = ";" + tag;

		int x = cookie.indexOf(tag);

		if (x != -1) {
			int y = cookie.indexOf(';', x + 1);

			return cookie.substring(x + tag.length(), y);
		}

		return "";
	}

	public static String set(String cookie, String tag, String sub) {
		if (cookie == null) {
			return "";
		}

		tag = tag + "=";

		if (cookie.startsWith(tag)) {
			int y = cookie.indexOf(';');

			StringMaker sm = new StringMaker();

			sm.append(tag).append(sub).append(";");
			sm.append(cookie.substring(y + 1, cookie.length()));

			return sm.toString();
		}

		tag = ";" + tag;

		int x = cookie.indexOf(tag);

		if (x != -1) {
			int y = cookie.indexOf(';', x + 1);

			StringMaker sm = new StringMaker();

			sm.append(cookie.substring(0, x + tag.length()));
			sm.append(sub);
			sm.append(cookie.substring(y, cookie.length()));

			return sm.toString();
		}

		return cookie + tag.substring(1, tag.length()) + sub + ";";
	}

}
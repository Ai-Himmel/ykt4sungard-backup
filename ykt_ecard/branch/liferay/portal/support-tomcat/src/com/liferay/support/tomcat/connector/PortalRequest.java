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

package com.liferay.support.tomcat.connector;

import com.liferay.portal.kernel.util.StringPool;

import javax.servlet.http.Cookie;

import org.apache.catalina.connector.Request;

/**
 * <a href="PortalRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Minhchau Dang
 *
 */
public class PortalRequest extends Request {

	protected void configureSessionCookie(Cookie cookie) {
		super.configureSessionCookie(cookie);

		String host = getServerName();

		String domain = _getDomain(host);

		if (domain != null) {
			cookie.setDomain(domain);
		}
	}

	private String _getDomain(String host) {

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

}
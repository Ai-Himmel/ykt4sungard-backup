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

package com.liferay.portlet.network.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.network.model.Whois;
import com.liferay.util.Time;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;

import java.net.Socket;

/**
 * <a href="WhoisWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WhoisWebCacheItem implements WebCacheItem {

	public static String WHOIS_SERVER = "whois.geektools.com";

	public static int WHOIS_SERVER_PORT = 43;

	public WhoisWebCacheItem(String domain) {
		_domain = domain;
	}

	public Object convert(String key) throws WebCacheException {
		Whois whois = null;

		try {
			Socket socket = new Socket(WHOIS_SERVER, WHOIS_SERVER_PORT);

			BufferedReader br = new BufferedReader(
				new InputStreamReader(socket.getInputStream()));

			PrintStream out = new PrintStream(socket.getOutputStream());

			out.println(_domain);

			StringMaker sm = new StringMaker();
			String line = null;

			while ((line = br.readLine()) != null) {
				if (line.startsWith("Results ")) {
					break;
				}

				sm.append(line).append("\n");
			}

			br.close();
			socket.close();

			whois = new Whois(
				_domain,
				StringUtil.replace(sm.toString().trim(), "\n\n", "\n"));
		}
		catch (Exception e) {
			throw new WebCacheException(_domain + " " + e.toString());
		}

		return whois;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY;

	private String _domain;

}
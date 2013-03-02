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
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.network.model.DNSLookup;
import com.liferay.util.Time;

import java.net.InetAddress;

/**
 * <a href="DNSLookupWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DNSLookupWebCacheItem implements WebCacheItem {

	public DNSLookupWebCacheItem(String domain) {
		_domain = domain;
	}

	public Object convert(String key) throws WebCacheException {
		DNSLookup dnsLookup = null;

		try {
			String results = null;

			char[] array = _domain.trim().toCharArray();

			for (int i = 0; i < array.length; i++) {
				if ((array[i] != '.') && !Character.isDigit(array[i])) {
					InetAddress ia = InetAddress.getByName(_domain);

					results = ia.getHostAddress();

					break;
				}
			}

			if (results == null) {
				StringMaker sm = new StringMaker();

				InetAddress[] ia = InetAddress.getAllByName(_domain);

				for (int i = 0; i < ia.length; i++) {
					sm.append(ia[i].getHostName());

					if (i + 1 <= ia.length) {
						sm.append(",");
					}
				}

				results = sm.toString();
			}

			dnsLookup = new DNSLookup(_domain, results);
		}
		catch (Exception e) {
			throw new WebCacheException(_domain + " " + e.toString());
		}

		return dnsLookup;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY;

	private String _domain;

}
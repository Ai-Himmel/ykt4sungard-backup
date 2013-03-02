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

package com.liferay.portlet.network.util;

import com.liferay.portal.util.WebCachePool;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.network.model.DNSLookup;
import com.liferay.portlet.network.model.Whois;

/**
 * <a href="NetworkUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.13 $
 *
 */
public class NetworkUtil {

	public static final String[] ADDRESS_JOBS = new String[] {
		//"com.liferay.portlet.network.job.CheckAddressJob_1m",
		//"com.liferay.portlet.network.job.CheckAddressJob_3m",
		"com.liferay.portlet.network.job.CheckAddressJob_15m",
		"com.liferay.portlet.network.job.CheckAddressJob_30m",
		"com.liferay.portlet.network.job.CheckAddressJob_1h",
		"com.liferay.portlet.network.job.CheckAddressJob_4h",
		"com.liferay.portlet.network.job.CheckAddressJob_12h",
		"com.liferay.portlet.network.job.CheckAddressJob_1d",
		"com.liferay.portlet.network.job.CheckAddressJob_3d",
		"com.liferay.portlet.network.job.CheckAddressJob_1w",
		"com.liferay.portlet.network.job.CheckAddressJob_2w"
	};

	public static DNSLookup getDNSLookup(String domain) {
		WebCacheable wc = new DNSLookupConverter(domain);

		return (DNSLookup)WebCachePool.get(
			NetworkUtil.class.getName() + ".dnslookup." + domain, wc);
	}

	public static Whois getWhois(String domain) {
		WebCacheable wc = new WhoisConverter(domain);

		return (Whois)WebCachePool.get(
			NetworkUtil.class.getName() + ".whois." + domain, wc);
	}

}
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

package com.liferay.portal.util;

import com.liferay.util.ConverterException;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="WebCachePool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.18 $
 *
 */
public class WebCachePool {

	static Properties props = new Properties();
	static GeneralCacheAdministrator cache = null;

	static {

		// The OSCache settings for WebCachePool should not vary much for
		// different deployments. WebCachePool is only meant to cache feeds to
		// external web sites by portlets like Stocks, Weather, etc. Do not
		// confuse WebCachePool with the other pools that are automatically
		// generated to cache models (see com.liferay.portal.model.User).

		props.setProperty("cache.memory", "true");
		props.setProperty(
			"cache.algorithm",
			"com.opensymphony.oscache.base.algorithm.LRUCache");
		props.setProperty("cache.capacity", "100000");
		props.setProperty("cache.blocking", "false");

		cache = new GeneralCacheAdministrator(props);
	}

	public static Object get(String key, WebCacheable wc) {
		Object obj = null;

		try {
			obj = cache.getFromCache(key);
		}
		catch (NeedsRefreshException nfe) {
			try {
				obj = wc.convert(key);

				cache.putInCache(
					key, obj, new WebCachePolicy(wc.getRefreshTime()));
			}
			catch (ConverterException ce) {
				_log.error(ce.getMessage());
			}
			finally {
				if (obj == null) {
					cache.cancelUpdate(key);
				}
			}
		}

		return obj;
	}

	private static final Log _log = LogFactory.getLog(WebCachePool.class);

}
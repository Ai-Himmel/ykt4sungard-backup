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

package com.liferay.portal.webcache;

import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.cache.SingleVMPoolUtil;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portal.kernel.webcache.WebCachePool;
import com.liferay.util.Time;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="WebCachePoolImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WebCachePoolImpl implements WebCachePool {

	public static final String CACHE_NAME = WebCachePool.class.getName();

	public void clear() {
		_cache.removeAll();
	}

	public Object get(String key, WebCacheItem wci) {
		Object obj = SingleVMPoolUtil.get(_cache, key);

		if (obj == null) {
			try {
				obj = wci.convert(key);

				int timeToLive = (int)(wci.getRefreshTime() / Time.SECOND);

				_cache.put(key, obj, timeToLive);
			}
			catch (WebCacheException wce) {
				Throwable cause = wce.getCause();

				if (cause != null) {
					_log.error(cause, cause);
				}
				else {
					_log.error(wce, wce);
				}
			}
		}

		return obj;
	}

	public void remove(String key) {
		SingleVMPoolUtil.remove(_cache, key);
	}

	private WebCachePoolImpl() {
		_cache = SingleVMPoolUtil.getCache(CACHE_NAME);
	}

	private static Log _log = LogFactory.getLog(WebCachePoolImpl.class);

	private PortalCache _cache;

}
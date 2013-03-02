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

package com.liferay.util.dao.hibernate;

import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.cache.Cache;
import org.hibernate.cache.CacheException;
import org.hibernate.cache.CacheProvider;

/**
 * <a href="CacheProviderWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CacheProviderWrapper implements CacheProvider {

	public CacheProviderWrapper(String cacheProvider) {
		try {
			_cacheProvider = (CacheProvider)Class.forName(
				cacheProvider).newInstance();
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public CacheProviderWrapper(CacheProvider cacheProvider) {
		_cacheProvider = cacheProvider;
	}

	public Cache buildCache(String regionName, Properties properties)
		throws CacheException {

		return new CacheWrapper(
			_cacheProvider.buildCache(regionName, properties));
	}

	public boolean isMinimalPutsEnabledByDefault() {
		return _cacheProvider.isMinimalPutsEnabledByDefault();
	}

	public long nextTimestamp() {
		return _cacheProvider.nextTimestamp();
	}

	public void start(Properties properties) throws CacheException {
		_cacheProvider.start(properties);
	}

	public void stop() {
		_cacheProvider.stop();
	}

	private static Log _log = LogFactory.getLog(CacheProviderWrapper.class);

	private CacheProvider _cacheProvider;

}
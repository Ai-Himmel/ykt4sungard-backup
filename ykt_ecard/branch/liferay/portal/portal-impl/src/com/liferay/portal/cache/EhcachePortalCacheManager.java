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

package com.liferay.portal.cache;

import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.cache.PortalCacheManager;
import com.liferay.portal.util.PropsUtil;

import java.net.URL;

import net.sf.ehcache.Cache;
import net.sf.ehcache.CacheManager;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="EhcachePortalCacheManager.java.html"><b><i>View Source</i></b></a>
 *
 * @author Joseph Shum
 *
 */
public class EhcachePortalCacheManager
	implements InitializingBean, PortalCacheManager {

	public void afterPropertiesSet() {
		URL url = getClass().getResource(PropsUtil.get(_configPropertyKey));

		_cacheManager = new CacheManager(url);
	}

	public void clearAll() {
		_cacheManager.clearAll();
	}

	public PortalCache getCache(String name) {
		Cache cache = _cacheManager.getCache(name);

		if (cache == null) {
			_cacheManager.addCache(name);

			cache = _cacheManager.getCache(name);
		}

		return new EhcachePortalCache(cache);
	}

	public void setConfigPropertyKey(String configPropertyKey) {
		_configPropertyKey = configPropertyKey;
	}

	private String _configPropertyKey;
	private CacheManager _cacheManager;

}
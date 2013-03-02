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
import com.liferay.portal.kernel.cache.SingleVMPool;

import java.io.Serializable;

/**
 * <a href="SingleVMPoolImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Michael Young
 *
 */
public class SingleVMPoolImpl implements SingleVMPool {

	public void clear() {
		_portalCacheManager.clearAll();
	}

	public void clear(String name) {
		PortalCache portalCache = getCache(name);

		portalCache.removeAll();
	}

	public Object get(String name, String key) {
		PortalCache portalCache = getCache(name);

		return get(portalCache, key);
	}

	public Object get(PortalCache portalCache, String key) {
		return portalCache.get(key);
	}

	public PortalCache getCache(String name) {
		return _portalCacheManager.getCache(name);
	}

	public void put(String name, String key, Object obj) {
		PortalCache portalCache = getCache(name);

		put(portalCache, key, obj);
	}

	public void put(PortalCache portalCache, String key, Object obj) {
		portalCache.put(key, obj);
	}

	public void put(String name, String key, Serializable obj) {
		PortalCache portalCache = getCache(name);

		put(portalCache, key, obj);
	}

	public void put(PortalCache portalCache, String key, Serializable obj) {
		portalCache.put(key, obj);
	}

	public void remove(String name, String key) {
		PortalCache portalCache = getCache(name);

		remove(portalCache, key);
	}

	public void remove(PortalCache portalCache, String key) {
		portalCache.remove(key);
	}

	public void setPortalCacheManager(PortalCacheManager portalCacheManager) {
		_portalCacheManager = portalCacheManager;
	}

	private PortalCacheManager _portalCacheManager;

}
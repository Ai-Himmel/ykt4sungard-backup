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

import com.liferay.portal.kernel.cache.CacheRegistry;
import com.liferay.portal.kernel.cache.CacheRegistryItem;

import java.util.Map;

import org.hibernate.cache.Cache;
import org.hibernate.cache.CacheException;

/**
 * <a href="CacheWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CacheWrapper implements Cache, CacheRegistryItem {

	public CacheWrapper(Cache cache) {
		_cache = cache;

		CacheRegistry.register(this);
	}

	public void clear() throws CacheException {
		_cache.clear();
	}

	public void destroy() throws CacheException {
		_cache.destroy();
	}

	public Object get(Object key) throws CacheException {
		return _cache.get(key);
	}

	public long getElementCountInMemory() {
		return _cache.getElementCountInMemory();
	}

	public long getElementCountOnDisk() {
		return _cache.getElementCountOnDisk();
	}

	public String getRegionName() {
		return _cache.getRegionName();
	}

	public long getSizeInMemory() {
		return _cache.getSizeInMemory();
	}

	public int getTimeout() {
		return _cache.getTimeout();
	}

	public void lock(Object key) throws CacheException {
		_cache.lock(key);
	}

	public long nextTimestamp() {
		return _cache.nextTimestamp();
	}

	public void put(Object key, Object value) throws CacheException {
		if (CacheRegistry.isActive()) {
			_cache.put(key, value);
		}
	}

	public Object read(Object key) throws CacheException {
		return _cache.read(key);
	}

	public void remove(Object key) throws CacheException {
		_cache.remove(key);
	}

	public Map toMap() {
		return _cache.toMap();
	}

	public void unlock(Object key) throws CacheException {
		_cache.unlock(key);
	}

	public void update(Object key, Object value) throws CacheException {
		if (CacheRegistry.isActive()) {
			_cache.update(key, value);
		}
	}

	public void invalidate() {
		_cache.clear();
	}

	private Cache _cache;

}
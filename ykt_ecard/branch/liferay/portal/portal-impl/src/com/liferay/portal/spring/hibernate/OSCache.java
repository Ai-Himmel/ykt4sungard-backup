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

package com.liferay.portal.spring.hibernate;

import com.liferay.portal.util.PropsUtil;

import com.opensymphony.oscache.base.CacheEntry;
import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.cache.Cache;
import org.hibernate.cache.CacheException;
import org.hibernate.cache.Timestamper;

/**
 * <a href="OSCache.java.html"><b><i>View Source</i></b></a>
 *
 * @author Mathias Bogaert
 * @author Brian Wing Shun Chan
 *
 */
public class OSCache implements Cache {

	public OSCache(int refreshPeriod, String cron, String region) {
		_refreshPeriod = refreshPeriod;
		_cron = cron;
		_regionName = region;
		_regionGroups = new String[] {region};
	}

	public void clear() throws CacheException {
		_cache.flushGroup(_regionName);
	}

	public void destroy() throws CacheException {
		synchronized (_cache) {
			_cache.destroy();
		}
	}

	public Object get(Object key) throws CacheException {
		String keyString = _encodeKey(key);

		try {
			return _cache.getFromCache(keyString, _refreshPeriod, _cron);
		}
		catch (NeedsRefreshException nre) {
			_cache.cancelUpdate(keyString);

			return null;
		}
	}

	public long getElementCountOnDisk() {
		return -1;
	}

	public long getElementCountInMemory() {
		return -1;
	}

	public String getRegionName() {
		return _regionName;
	}

	public long getSizeInMemory() {
		return -1;
	}

	public int getTimeout() {
		return CacheEntry.INDEFINITE_EXPIRY;
	}

	public void lock(Object key) throws CacheException {
	}

	public long nextTimestamp() {
		return Timestamper.next();
	}

	public void put(Object key, Object value) throws CacheException {
		_cache.putInCache(_encodeKey(key), value, _regionGroups);
	}

	public Object read(Object key) throws CacheException {
		return get(key);
	}

	public void remove(Object key) throws CacheException {
		_cache.flushEntry(_encodeKey(key));
	}

	public Map toMap() {
		return null;
	}

	public void unlock(Object key) throws CacheException {
	}

	public void update(Object key, Object value) throws CacheException {
		_cache.flushEntry(_encodeKey(key));

		put(key, value);
	}

	private String _encodeKey(Object key) {
		String keyString = String.valueOf(key);

		if (_log.isDebugEnabled()) {
			_log.debug("Key " + keyString);
		}

		return keyString;
	}

	private static Log _log = LogFactory.getLog(OSCache.class);

	private static GeneralCacheAdministrator _cache =
		new GeneralCacheAdministrator(PropsUtil.getProperties());

	private int _refreshPeriod;
	private String _cron;
	private String _regionName;
	private String[] _regionGroups;

}
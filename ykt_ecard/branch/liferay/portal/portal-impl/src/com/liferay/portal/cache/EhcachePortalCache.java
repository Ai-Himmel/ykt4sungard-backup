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

import java.io.Serializable;

import net.sf.ehcache.Cache;
import net.sf.ehcache.Element;

/**
 * <a href="EhcachePortalCache.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EhcachePortalCache implements PortalCache {

	public EhcachePortalCache(Cache cache) {
		_cache = cache;
	}

	public Object get(String key) {
		Element element = _cache.get(key);

		if (element == null) {
			return null;
		}
		else {
			return element.getObjectValue();
		}
	}

	public void put(String key, Object obj) {
		Element element = new Element(key, obj);

		_cache.put(element);
	}

	public void put(String key, Object obj, int timeToLive) {
		Element element = new Element(key, obj);

		element.setTimeToLive(timeToLive);

		_cache.put(element);
	}

	public void put(String key, Serializable obj) {
		Element element = new Element(key, obj);

		_cache.put(element);
	}

	public void put(String key, Serializable obj, int timeToLive) {
		Element element = new Element(key, obj);

		element.setTimeToLive(timeToLive);

		_cache.put(element);
	}

	public void remove(String key) {
		_cache.remove(key);
	}

	public void removeAll() {
		_cache.removeAll();
	}

	private Cache _cache;

}
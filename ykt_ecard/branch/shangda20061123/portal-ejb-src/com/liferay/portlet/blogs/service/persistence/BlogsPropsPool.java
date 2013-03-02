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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.service.persistence.GlobalPool;

import com.liferay.portlet.blogs.model.BlogsProps;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="BlogsPropsPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsPropsPool {
	public static void clear() {
		_instance._clear();
	}

	public static BlogsProps get(String propsId) {
		return _instance._get(propsId);
	}

	public static BlogsProps put(String propsId, BlogsProps obj) {
		return _instance._put(propsId, obj);
	}

	public static BlogsProps remove(String propsId) {
		return _instance._remove(propsId);
	}

	private BlogsPropsPool() {
		_cacheable = BlogsProps.CACHEABLE;

		int maxSize = BlogsProps.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(BlogsPropsPool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private BlogsProps _get(String propsId) {
		if (!_cacheable) {
			return null;
		}
		else if (propsId == null) {
			return null;
		}
		else {
			BlogsProps obj = null;
			String key = propsId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (BlogsProps)_cache.getFromCache(key);
			}
			catch (NeedsRefreshException nfe) {
			}
			finally {
				if (obj == null) {
					_cache.cancelUpdate(key);
				}
			}

			return obj;
		}
	}

	private BlogsProps _put(String propsId, BlogsProps obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (propsId == null) {
			return obj;
		}
		else {
			String key = propsId.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private BlogsProps _remove(String propsId) {
		if (!_cacheable) {
			return null;
		}
		else if (propsId == null) {
			return null;
		}
		else {
			BlogsProps obj = null;
			String key = propsId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (BlogsProps)_cache.getFromCache(key);
				_cache.flushEntry(key);
			}
			catch (NeedsRefreshException nfe) {
			}
			finally {
				if (obj == null) {
					_cache.cancelUpdate(key);
				}
			}

			return obj;
		}
	}

	private static BlogsPropsPool _instance = new BlogsPropsPool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
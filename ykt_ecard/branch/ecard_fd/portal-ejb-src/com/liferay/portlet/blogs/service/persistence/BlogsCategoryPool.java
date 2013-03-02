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

import com.liferay.portlet.blogs.model.BlogsCategory;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="BlogsCategoryPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsCategoryPool {
	public static void clear() {
		_instance._clear();
	}

	public static BlogsCategory get(String categoryId) {
		return _instance._get(categoryId);
	}

	public static BlogsCategory put(String categoryId, BlogsCategory obj) {
		return _instance._put(categoryId, obj);
	}

	public static BlogsCategory remove(String categoryId) {
		return _instance._remove(categoryId);
	}

	private BlogsCategoryPool() {
		_cacheable = BlogsCategory.CACHEABLE;

		int maxSize = BlogsCategory.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(BlogsCategoryPool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private BlogsCategory _get(String categoryId) {
		if (!_cacheable) {
			return null;
		}
		else if (categoryId == null) {
			return null;
		}
		else {
			BlogsCategory obj = null;
			String key = categoryId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (BlogsCategory)_cache.getFromCache(key);
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

	private BlogsCategory _put(String categoryId, BlogsCategory obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (categoryId == null) {
			return obj;
		}
		else {
			String key = categoryId.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private BlogsCategory _remove(String categoryId) {
		if (!_cacheable) {
			return null;
		}
		else if (categoryId == null) {
			return null;
		}
		else {
			BlogsCategory obj = null;
			String key = categoryId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (BlogsCategory)_cache.getFromCache(key);
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

	private static BlogsCategoryPool _instance = new BlogsCategoryPool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
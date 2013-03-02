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

package com.liferay.portlet.shopping.service.persistence;

import com.liferay.portal.service.persistence.GlobalPool;

import com.liferay.portlet.shopping.model.ShoppingCategory;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="ShoppingCategoryPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCategoryPool {
	public static void clear() {
		_instance._clear();
	}

	public static ShoppingCategory get(String categoryId) {
		return _instance._get(categoryId);
	}

	public static ShoppingCategory put(String categoryId, ShoppingCategory obj) {
		return _instance._put(categoryId, obj);
	}

	public static ShoppingCategory remove(String categoryId) {
		return _instance._remove(categoryId);
	}

	private ShoppingCategoryPool() {
		_cacheable = ShoppingCategory.CACHEABLE;

		int maxSize = ShoppingCategory.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(ShoppingCategoryPool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private ShoppingCategory _get(String categoryId) {
		if (!_cacheable) {
			return null;
		}
		else if (categoryId == null) {
			return null;
		}
		else {
			ShoppingCategory obj = null;
			String key = categoryId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (ShoppingCategory)_cache.getFromCache(key);
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

	private ShoppingCategory _put(String categoryId, ShoppingCategory obj) {
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

	private ShoppingCategory _remove(String categoryId) {
		if (!_cacheable) {
			return null;
		}
		else if (categoryId == null) {
			return null;
		}
		else {
			ShoppingCategory obj = null;
			String key = categoryId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (ShoppingCategory)_cache.getFromCache(key);
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

	private static ShoppingCategoryPool _instance = new ShoppingCategoryPool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
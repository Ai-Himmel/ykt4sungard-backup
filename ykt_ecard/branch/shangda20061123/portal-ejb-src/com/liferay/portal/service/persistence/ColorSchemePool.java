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

package com.liferay.portal.service.persistence;

import com.liferay.portal.model.ColorScheme;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="ColorSchemePool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ColorSchemePool {
	public static void clear() {
		_instance._clear();
	}

	public static ColorScheme get(String colorSchemeId) {
		return _instance._get(colorSchemeId);
	}

	public static ColorScheme put(String colorSchemeId, ColorScheme obj) {
		return _instance._put(colorSchemeId, obj);
	}

	public static ColorScheme remove(String colorSchemeId) {
		return _instance._remove(colorSchemeId);
	}

	private ColorSchemePool() {
		_cacheable = ColorScheme.CACHEABLE;

		int maxSize = ColorScheme.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(ColorSchemePool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private ColorScheme _get(String colorSchemeId) {
		if (!_cacheable) {
			return null;
		}
		else if (colorSchemeId == null) {
			return null;
		}
		else {
			ColorScheme obj = null;
			String key = colorSchemeId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (ColorScheme)_cache.getFromCache(key);
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

	private ColorScheme _put(String colorSchemeId, ColorScheme obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (colorSchemeId == null) {
			return obj;
		}
		else {
			String key = colorSchemeId.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private ColorScheme _remove(String colorSchemeId) {
		if (!_cacheable) {
			return null;
		}
		else if (colorSchemeId == null) {
			return null;
		}
		else {
			ColorScheme obj = null;
			String key = colorSchemeId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (ColorScheme)_cache.getFromCache(key);
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

	private static ColorSchemePool _instance = new ColorSchemePool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
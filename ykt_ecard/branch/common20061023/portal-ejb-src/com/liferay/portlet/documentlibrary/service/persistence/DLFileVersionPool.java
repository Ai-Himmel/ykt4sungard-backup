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

package com.liferay.portlet.documentlibrary.service.persistence;

import com.liferay.portal.service.persistence.GlobalPool;

import com.liferay.portlet.documentlibrary.model.DLFileVersion;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="DLFileVersionPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileVersionPool {
	public static void clear() {
		_instance._clear();
	}

	public static DLFileVersion get(DLFileVersionPK dlFileVersionPK) {
		return _instance._get(dlFileVersionPK);
	}

	public static DLFileVersion put(DLFileVersionPK dlFileVersionPK,
		DLFileVersion obj) {
		return _instance._put(dlFileVersionPK, obj);
	}

	public static DLFileVersion remove(DLFileVersionPK dlFileVersionPK) {
		return _instance._remove(dlFileVersionPK);
	}

	private DLFileVersionPool() {
		_cacheable = DLFileVersion.CACHEABLE;

		int maxSize = DLFileVersion.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(DLFileVersionPool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private DLFileVersion _get(DLFileVersionPK dlFileVersionPK) {
		if (!_cacheable) {
			return null;
		}
		else if (dlFileVersionPK == null) {
			return null;
		}
		else {
			DLFileVersion obj = null;
			String key = dlFileVersionPK.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (DLFileVersion)_cache.getFromCache(key);
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

	private DLFileVersion _put(DLFileVersionPK dlFileVersionPK,
		DLFileVersion obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (dlFileVersionPK == null) {
			return obj;
		}
		else {
			String key = dlFileVersionPK.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private DLFileVersion _remove(DLFileVersionPK dlFileVersionPK) {
		if (!_cacheable) {
			return null;
		}
		else if (dlFileVersionPK == null) {
			return null;
		}
		else {
			DLFileVersion obj = null;
			String key = dlFileVersionPK.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (DLFileVersion)_cache.getFromCache(key);
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

	private static DLFileVersionPool _instance = new DLFileVersionPool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
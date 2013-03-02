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

import com.liferay.portal.model.Role;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="RolePool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class RolePool {
	public static void clear() {
		_instance._clear();
	}

	public static Role get(String roleId) {
		return _instance._get(roleId);
	}

	public static Role put(String roleId, Role obj) {
		return _instance._put(roleId, obj);
	}

	public static Role remove(String roleId) {
		return _instance._remove(roleId);
	}

	private RolePool() {
		_cacheable = Role.CACHEABLE;

		int maxSize = Role.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(RolePool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private Role _get(String roleId) {
		if (!_cacheable) {
			return null;
		}
		else if (roleId == null) {
			return null;
		}
		else {
			Role obj = null;
			String key = roleId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (Role)_cache.getFromCache(key);
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

	private Role _put(String roleId, Role obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (roleId == null) {
			return obj;
		}
		else {
			String key = roleId.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private Role _remove(String roleId) {
		if (!_cacheable) {
			return null;
		}
		else if (roleId == null) {
			return null;
		}
		else {
			Role obj = null;
			String key = roleId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (Role)_cache.getFromCache(key);
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

	private static RolePool _instance = new RolePool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}
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

package com.liferay.portal.service.impl;

import com.liferay.portal.kernel.cache.MultiVMPoolUtil;
import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.util.CollectionFactory;

import java.util.Map;

/**
 * <a href="PortletPreferencesLocalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Michael Young
 *
 */
public class PortletPreferencesLocalUtil {

	public static final String CACHE_NAME =
		PortletPreferencesLocalUtil.class.getName();

	protected static void clearPreferencesPool() {
		_cache.removeAll();
	}

	protected static void clearPreferencesPool(long ownerId, int ownerType) {
		String key = _encodeKey(ownerId, ownerType);

		_cache.remove(key);
	}

	protected static Map getPreferencesPool(long ownerId, int ownerType) {
		String key = _encodeKey(ownerId, ownerType);

		Map prefsPool = (Map)MultiVMPoolUtil.get(_cache, key);

		if (prefsPool == null) {
			prefsPool = CollectionFactory.getSyncHashMap();

			MultiVMPoolUtil.put(_cache, key, prefsPool);
		}

		return prefsPool;
	}

	private static String _encodeKey(long ownerId, int ownerType) {
		StringMaker sm = new StringMaker();

		sm.append(CACHE_NAME);
		sm.append(StringPool.POUND);
		sm.append(ownerId);
		sm.append(StringPool.POUND);
		sm.append(ownerType);

		return sm.toString();
	}

	private static PortalCache _cache = MultiVMPoolUtil.getCache(CACHE_NAME);

}
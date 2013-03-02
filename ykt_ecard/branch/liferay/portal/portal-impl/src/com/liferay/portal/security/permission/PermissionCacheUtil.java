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

package com.liferay.portal.security.permission;

import com.liferay.portal.kernel.cache.MultiVMPoolUtil;
import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;

/**
 * <a href="PermissionCacheUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Michael Young
 *
 */
public class PermissionCacheUtil {

	public static final String CACHE_NAME = PermissionCacheUtil.class.getName();

	public static void clearCache() {
		_cache.removeAll();
	}

	public static Boolean hasPermission(
		long userId, long groupId, String name, String primKey,
		String actionId) {

		String key = _encodeKey(userId, groupId, name, primKey, actionId);

		Boolean value = (Boolean)MultiVMPoolUtil.get(_cache, key);

		return value;
	}

	public static Boolean putPermission(
		long userId, long groupId, String name, String primKey, String actionId,
		Boolean value) {

		if (value != null) {
			String key = _encodeKey(userId, groupId, name, primKey, actionId);

			MultiVMPoolUtil.put(_cache, key, value);
		}

		return value;
	}

	private static String _encodeKey(
		long userId, long groupId, String name, String primKey,
		String actionId) {

		StringMaker sm = new StringMaker();

		sm.append(CACHE_NAME);
		sm.append(StringPool.POUND);
		sm.append(userId);
		sm.append(StringPool.POUND);
		sm.append(groupId);
		sm.append(StringPool.POUND);
		sm.append(name);
		sm.append(StringPool.POUND);
		sm.append(primKey);
		sm.append(StringPool.POUND);
		sm.append(actionId);

		return sm.toString();
	}

	private static PortalCache _cache = MultiVMPoolUtil.getCache(CACHE_NAME);

}
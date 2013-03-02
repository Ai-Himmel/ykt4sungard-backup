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

package com.liferay.portal.servlet.filters.layoutcache;

import com.liferay.portal.kernel.cache.MultiVMPoolUtil;
import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.CollectionFactory;
import com.liferay.util.servlet.filters.CacheResponseData;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LayoutCacheUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Michael Young
 *
 */
public class LayoutCacheUtil {

	public static String CACHE_NAME = LayoutCacheUtil.class.getName();

	public static void clearCache() {
		MultiVMPoolUtil.clear(CACHE_NAME);
	}

	public static void clearCache(long companyId) {
		String groupKey = _encodeGroupKey(companyId);

		MultiVMPoolUtil.clearGroup(_groups, groupKey, _cache);

		if (_log.isInfoEnabled()) {
			_log.info("Cleared layout cache for " + companyId);
		}
	}

	public static CacheResponseData getCacheResponseData(
		long companyId, String key) {

		if (Validator.isNull(key)) {
			return null;
		}

		key = _encodeKey(companyId, key);

		CacheResponseData data =
			(CacheResponseData)MultiVMPoolUtil.get(_cache, key);

		return data;
	}

	public static void putCacheResponseData(
		long companyId, String key, CacheResponseData data) {

		if (data != null) {
			key = _encodeKey(companyId, key);

			String groupKey = _encodeGroupKey(companyId);

			MultiVMPoolUtil.put(_cache, key, _groups, groupKey, data);
		}
	}

	private static String _encodeGroupKey(long companyId) {
		StringMaker sm = new StringMaker();

		sm.append(CACHE_NAME);
		sm.append(StringPool.POUND);
		sm.append(companyId);

		return sm.toString();
	}

	private static String _encodeKey(long companyId, String key) {
		StringMaker sm = new StringMaker();

		sm.append(CACHE_NAME);
		sm.append(StringPool.POUND);
		sm.append(companyId);
		sm.append(StringPool.POUND);
		sm.append(key);

		return sm.toString();
	}

	private static Log _log = LogFactory.getLog(LayoutCacheUtil.class);

	private static PortalCache _cache = MultiVMPoolUtil.getCache(CACHE_NAME);

	private static Map _groups = CollectionFactory.getSyncHashMap();

}
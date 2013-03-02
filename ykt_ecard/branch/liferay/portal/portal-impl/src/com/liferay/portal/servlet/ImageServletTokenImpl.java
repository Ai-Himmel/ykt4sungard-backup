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

package com.liferay.portal.servlet;

import com.liferay.portal.cms.servlet.CMSServletUtil;
import com.liferay.portal.kernel.cache.MultiVMPoolUtil;
import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.servlet.ImageServletToken;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.servlet.filters.layoutcache.LayoutCacheUtil;
import com.liferay.portlet.journalcontent.util.JournalContentUtil;

/**
 * <a href="ImageServletTokenImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImageServletTokenImpl implements ImageServletToken {

	public static final String CACHE_NAME = ImageServletToken.class.getName();

	public String getToken(long imageId) {
		String key = _encodeKey(imageId);

		String token = (String)MultiVMPoolUtil.get(_cache, key);

		if (token == null) {
			token = _createToken(imageId);

			MultiVMPoolUtil.put(_cache, key, token);
		}

		return token;
	}

	public void resetToken(long imageId) {
		String key = _encodeKey(imageId);

		_cache.remove(key);

		// CMS

		CMSServletUtil.clearCache();

		// Journal content

		JournalContentUtil.clearCache();

		// Layout cache

		LayoutCacheUtil.clearCache();
	}

	private String _createToken(long imageId) {
		return String.valueOf(System.currentTimeMillis());
	}

	private String _encodeKey(long imageId) {
		StringMaker sm = new StringMaker();

		sm.append(CACHE_NAME);
		sm.append(StringPool.POUND);
		sm.append(imageId);

		return sm.toString();
	}

	private static PortalCache _cache = MultiVMPoolUtil.getCache(CACHE_NAME);

}
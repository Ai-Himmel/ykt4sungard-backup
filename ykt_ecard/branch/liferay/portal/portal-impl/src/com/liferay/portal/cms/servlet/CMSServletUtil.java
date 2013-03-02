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

package com.liferay.portal.cms.servlet;

import com.liferay.portal.kernel.cache.MultiVMPoolUtil;
import com.liferay.portal.kernel.cache.PortalCache;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CMSServletUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class CMSServletUtil {

	public static final String CACHE_NAME = CMSServletUtil.class.getName();

	public static String LANGUAGE = "_LANGUAGE_";

	public static void clearCache() {
		_cache.removeAll();
	}

	public static String getContent(
		long groupId, String articleId, String languageId,
		ThemeDisplay themeDisplay) {

		if (Validator.isNull(articleId)) {
			return null;
		}

		articleId = articleId.trim().toUpperCase();

		String key = _encodeKey(articleId, languageId);

		String content = (String)MultiVMPoolUtil.get(_cache, key);

		if (content == null) {
			try {
				content = JournalArticleLocalServiceUtil.getArticleContent(
					groupId, articleId, languageId, themeDisplay);
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e.getMessage());
				}
			}

			if (content != null) {
				MultiVMPoolUtil.put(_cache, key, content);
			}
		}

		return content;
	}

	private static String _encodeKey(String articleId, String languageId) {
		StringMaker sm = new StringMaker();

		sm.append(CACHE_NAME);
		sm.append(StringPool.POUND);
		sm.append(articleId);
		sm.append(StringPool.POUND);
		sm.append(languageId);

		return sm.toString();
	}

	private static Log _log = LogFactory.getLog(CMSServletUtil.class);

	private static PortalCache _cache = MultiVMPoolUtil.getCache(CACHE_NAME);

}
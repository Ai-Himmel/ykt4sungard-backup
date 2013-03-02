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

package com.liferay.portlet.journalcontent.util;

import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.util.StringPool;
import com.liferay.util.SystemProperties;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JournalContentUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Raymond Auge
 * @version $Revision: 1.7 $
 *
 */
public class JournalContentUtil {

	public static String LANGUAGE = "_LANGUAGE_";

	public static void clearCache() {
		_cache.flushAll();
	}

	public static String getContent(
		String articleId, String languageId, String rootPath) {

		String content = null;

		if (articleId == null) {
			articleId = StringPool.BLANK;
		}

		articleId = articleId.trim().toUpperCase();

		String key = articleId + LANGUAGE + languageId;

		try {
			content = (String)_cache.getFromCache(key);
		}
		catch (NeedsRefreshException nre) {
			try {
				content = JournalArticleServiceUtil.getArticleContent(
					articleId, languageId, rootPath);
			}
			catch (Exception e1) {
				_log.warn(e1.getMessage());
			}

			if (content != null) {
				_cache.putInCache(key, content);
			}
		}
		finally {
			if (content == null) {
				_cache.cancelUpdate(key);
			}
		}

		return content;
	}

	private static final Log _log = LogFactory.getLog(JournalContentUtil.class);

	private static GeneralCacheAdministrator _cache =
		new GeneralCacheAdministrator(SystemProperties.getProperties());

}
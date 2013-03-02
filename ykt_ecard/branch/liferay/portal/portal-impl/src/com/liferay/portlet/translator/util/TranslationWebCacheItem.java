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

package com.liferay.portlet.translator.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.translator.model.Translation;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Time;

import java.net.URL;

/**
 * <a href="TranslationWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TranslationWebCacheItem implements WebCacheItem {

	public TranslationWebCacheItem(String translationId, String fromText) {
		_translationId = translationId;
		_fromText = fromText;
	}

	public Object convert(String key) throws WebCacheException {
		Translation translation = new Translation(_translationId, _fromText);

		try {
			StringMaker url = new StringMaker();

			url.append("http://babelfish.altavista.com/babelfish/tr?doit=done");
			url.append("&urltext=").append(HttpUtil.encodeURL(_fromText));
			url.append("&lp=").append(_translationId);

			String text = Http.URLtoString(new URL(url.toString()));

			int begin = text.indexOf("<div style=padding:10px;>") + 25;
			int end = text.indexOf("</div>", begin);

			String toText = text.substring(begin, end).trim();

			toText = StringUtil.replace(toText, "\n", " ");

			translation.setToText(toText);
		}
		catch (Exception e) {
			throw new WebCacheException(e);
		}

		return translation;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY * 90;

	private String _translationId;
	private String _fromText;

}
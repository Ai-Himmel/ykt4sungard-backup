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

package com.liferay.portlet.randombibleverse.util;

import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.randombibleverse.model.Verse;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Time;

/**
 * <a href="VerseWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class VerseWebCacheItem implements WebCacheItem {

	public VerseWebCacheItem(String location, String versionId) {
		_location = location;
		_versionId = versionId;
	}

	public Object convert(String key) throws WebCacheException {
		Verse verse = null;

		try {
			String url =
				"http://www.biblegateway.com/passage/?search=" +
					HttpUtil.encodeURL(_location) + "&version=" + _versionId;

			String text = Http.URLtoString(url);

			int x = text.indexOf("result-text-style-normal");
			x = text.indexOf(">", x);

			int y = text.indexOf("</div>", x);

			text = text.substring(x + 1, y);

			y = text.indexOf("Footnotes:");

			if (y != -1) {
				text = text.substring(0, y);
			}

			// Strip everything between <span> and </span>

			text = Html.stripBetween(text, "span");

			// Strip everything between <sup> and </sup>

			text = Html.stripBetween(text, "sup");

			// Strip everything between <h4> and </h4>

			text = Html.stripBetween(text, "h4");

			// Strip everything between <h5> and </h5>

			text = Html.stripBetween(text, "h5");

			// Strip HTML

			text = Html.stripHtml(text).trim();

			// Strip &nbsp;

			text = StringUtil.replace(text, "&nbsp;", "");

			// Strip carriage returns

			text = StringUtil.replace(text, "\n", "");

			// Strip double spaces

			while (text.indexOf("  ") != -1) {
				text = StringUtil.replace(text, "  ", " ");
			}

			// Replace " with &quot;

			text = StringUtil.replace(text, "\"", "&quot;");

			// Trim

			text = text.trim();

			verse = new Verse(_location, text);
		}
		catch (Exception e) {
			throw new WebCacheException(
				_location + " " + _versionId + " " + e.toString());
		}

		return verse;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.WEEK * 52;

	private String _location;
	private String _versionId;

}
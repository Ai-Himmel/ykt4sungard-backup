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

package com.liferay.portlet.randombibleverse.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.randombibleverse.model.Verse;
import com.liferay.util.ConverterException;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.StringUtil;
import com.liferay.util.Time;
import com.liferay.util.lang.FastStringBuffer;

/**
 * <a href="VerseConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class VerseConverter implements WebCacheable {

	public VerseConverter(String location, String versionId) {
		_location = location;
		_versionId = versionId;
	}

	public Object convert(String id) throws ConverterException {
		Verse verse = null;

		try {
			String url =
				"http://www.biblegateway.com/passage/?search=" +
					Http.encodeURL(_location) + "&version=" + _versionId +
						"&showfn=no&showxref=no";

			String text = Http.URLtoString(url);

			int x = text.indexOf("<sup");
			int y = text.indexOf("result-options", x);
			y = text.lastIndexOf("<div", y);

			text = text.substring(x, y);

			// Strip everything between <sup> and </sup>

			FastStringBuffer sb = new FastStringBuffer();
			x = 0;
			y = text.indexOf("<sup");

			while (y != -1) {
				sb.append(text.substring(x, y));
				x = text.indexOf("</sup>", y) + 6;
				y = text.indexOf("<sup", x);
			}

			if (y == -1) {
				sb.append(text.substring(x, text.length()));
			}

			text = sb.toString();

			// Strip HTML

			text = Html.stripHtml(text).trim();

			// Strip other formatting

			text = StringUtil.replace(text, "&nbsp;", "");

			// Strip carriage returns

			text = StringUtil.replace(text, "\n", "");

			// Strip double spaces

			while (text.indexOf("  ") != -1) {
				text = StringUtil.replace(text, "  ", " ");
			}

			verse = new Verse(_location, text);
		}
		catch (Exception e) {
			throw new ConverterException(
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
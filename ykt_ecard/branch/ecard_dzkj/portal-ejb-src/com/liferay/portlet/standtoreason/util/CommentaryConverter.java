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

package com.liferay.portlet.standtoreason.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.standtoreason.model.Commentary;
import com.liferay.util.ConverterException;
import com.liferay.util.Http;
import com.liferay.util.StringUtil;
import com.liferay.util.Time;

/**
 * <a href="CommentaryConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class CommentaryConverter implements WebCacheable {

	public CommentaryConverter() {
	}

	public Object convert(String id) throws ConverterException {
		Commentary commentary = null;

		try {
			String text = Http.URLtoString(
				"http://www.str.org/cgi-bin/daily_commentary.pl");

			int x = text.indexOf("<p align=center class=\"headline2\">");
			int y = text.indexOf("</p>", x);

			String title = text.substring(x + 34, y);

			x = text.indexOf("<blockquote class=\"body1\"><center><i>");
			y = text.indexOf("</i>", x);

			String blurb = text.substring(x + 37, y);

			x = text.indexOf("<table border=0><tr><td class=\"body1\">");
			y = text.indexOf("</td></tr></table><p>", x);

			String content = text.substring(x + 38, y);
			content = StringUtil.replace(
				content,
				"<img src=\"http://www.str.org/images/logos/maroon.gif\" " +
					"alt=\"divider\" width=\"300\" height=\"1\" border=\"0\">",
				"<hr>");

			commentary = new Commentary(title, blurb, content);
		}
		catch (Exception e) {
			throw new ConverterException(e);
		}

		return commentary;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.HOUR;

}
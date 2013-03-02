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

package com.liferay.util;

import com.liferay.util.lang.FastStringBuffer;

/**
 * <a href="Html.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Clarence Shen
 * @version $Revision: 1.14 $
 *
 */
public class Html {

	public static String formatFrom(String text) {
		if (text == null) {
			return null;
		}

		// Optimize this

		text = StringUtil.replace(text, "&#42;", "*");
		text = StringUtil.replace(text, "&#47;", "/");
		text = StringUtil.replace(text, "&#58;", ":");
		text = StringUtil.replace(text, "&#63;", "?");

		return text;
	}

	public static String formatTo(String text) {
		if (text == null) {
			return null;
		}

		int pos = text.indexOf("& ");

		if (pos != -1) {
			text = StringUtil.replace(text, "& ", "&amp; ");
		}

		FastStringBuffer sb = new FastStringBuffer();
		char c;

		for (int i = 0; i < text.length(); i++) {
			c = text.charAt(i);

			switch (c) {
				case '<':
					sb.append("&lt;");
					break;

				case '>':
					sb.append("&gt;");
					break;

				case '\'':
					sb.append("&#39;");
					break;

				case '\"':
					sb.append("&quot;");
					break;

				case '\r':
					break;

				case '\n':
					break;

				case '\t':
					break;

				default:
					if (((int)c) > 255) {
						sb.append("&#").append(((int)c)).append(";");
					}
					else {
						sb.append(c);
					}
			}
		}

		return sb.toString();
	}

	public static String stripComments(String text) {
		if (text == null) {
			return null;
		}

		FastStringBuffer sb = new FastStringBuffer();

		int x = 0;
		int y = text.indexOf("<!--");

		while (y != -1) {
			sb.append(text.substring(x, y));

			x = text.indexOf("-->", y) + 3;
			y = text.indexOf("<!--", x);
		}

		if (y == -1) {
			sb.append(text.substring(x, text.length()));
		}

		return sb.toString();

		/*
		int x = text.indexOf("<!--");
		int y = text.indexOf("-->");

		if (x != -1 && y != -1) {
			return stripComments(
				text.substring(0, x) + text.substring(y + 3, text.length()));
		}
		*/

		/*
		Perl5Util util = new Perl5Util();

		text = util.substitute("s/<!--.*-->//g", text);
		*/

		//return text;
	}

	public static String stripHtml(String text) {
		if (text == null) {
			return null;
		}

		text = stripComments(text);

		FastStringBuffer sb = new FastStringBuffer();
		int x = 0;
		int y = text.indexOf("<");

		while (y != -1) {
			sb.append(text.substring(x, y));

			x = text.indexOf(">", y) + 1;

			if (x < y) {

				// <b>Hello</b

				break;
			}

			y = text.indexOf("<", x);
		}

		if (y == -1) {
			sb.append(text.substring(x, text.length()));
		}

		return sb.toString();
	}

}
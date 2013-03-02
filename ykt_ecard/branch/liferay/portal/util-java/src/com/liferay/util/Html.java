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

package com.liferay.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;

/**
 * <a href="Html.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Clarence Shen
 * @author Harry Mark
 *
 */
public class Html {

	public static String escape(String text) {
		if (text == null) {
			return null;
		}

		// Escape using XSS recommendations from
		// http://www.owasp.org/index.php/Cross_Site_Scripting
		// #How_to_Protect_Yourself

		StringMaker sm = new StringMaker(text.length());

		for (int i = 0; i < text.length(); i++) {
			char c = text.charAt(i);

			switch (c) {
				case '<':
					sm.append("&lt;");

					break;

				case '>':
					sm.append("&gt;");

					break;

				case '&':
					sm.append("&amp;");

					break;

				case '"':
					sm.append("&#034;");

					break;

				case '\'':
					sm.append("&#039;");

					break;

				case '(':
					sm.append("&#040;");

					break;

				case ')':
					sm.append("&#041;");

					break;

				case '#':
					sm.append("&#035;");

					break;

				case '%':
					sm.append("&#037;");

					break;

				case ';':
					sm.append("&#059;");

					break;

				case '+':
					sm.append("&#043;");

					break;

				case '-':
					sm.append("&#045;");

					break;

				default:
					sm.append(c);

					break;
			}
		}

		return sm.toString();
	}

	public static String fromInputSafe(String text) {
		return StringUtil.replace(text, "&amp;", "&");
	}

	public static String replaceMsWordCharacters(String text) {
		return StringUtil.replace(text, _MS_WORD_UNICODE, _MS_WORD_HTML);
	}

	public static String stripBetween(String text, String tag) {
		return StringUtil.stripBetween(text, "<" + tag, "</" + tag + ">");
	}

	public static String stripComments(String text) {
		return StringUtil.stripBetween(text, "<!--", "-->");
	}

	public static String stripHtml(String text) {
		if (text == null) {
			return null;
		}

		text = stripComments(text);

		StringMaker sm = new StringMaker(text.length());

		int x = 0;
		int y = text.indexOf("<");

		while (y != -1) {
			sm.append(text.substring(x, y));
			sm.append(StringPool.SPACE);

			// Look for text enclosed by <script></script>

			boolean scriptFound = _isScriptTag(text, y + 1);

			if (scriptFound) {
				int pos = y + _TAG_SCRIPT.length;

				// Find end of the tag

				pos = text.indexOf(">", pos);

				if (pos >= 0) {

					// Check if preceding character is / (i.e. is this instance
					// of <script/>)

					if (text.charAt(pos-1) != '/') {

						// Search for the ending </script> tag

						for (;;) {
							pos = text.indexOf("</", pos);

							if (pos >= 0) {
								if (_isScriptTag(text, pos + 2)) {
									y = pos;

									break;
								}
								else {

									// Skip past "</"

									pos += 2;
								}
							}
							else {
								break;
							}
						}
					}
				}
			}

			x = text.indexOf(">", y);

			if (x == -1) {
				break;
			}

			x++;

			if (x < y) {

				// <b>Hello</b

				break;
			}

			y = text.indexOf("<", x);
		}

		if (y == -1) {
			sm.append(text.substring(x, text.length()));
		}

		return sm.toString();
	}

	public static String toInputSafe(String text) {
		return StringUtil.replace(
			text,
			new String[] {"&", "\""},
			new String[] {"&amp;", "&quot;"});
	}

	public static String unescape(String text) {
		if (text == null) {
			return null;
		}

		// Optimize this

		text = StringUtil.replace(text, "&lt;", "<");
		text = StringUtil.replace(text, "&gt;", ">");
		text = StringUtil.replace(text, "&amp;", "&");
		text = StringUtil.replace(text, "&#034;", "\"");
		text = StringUtil.replace(text, "&#039;", "'");
		text = StringUtil.replace(text, "&#040;", "(");
		text = StringUtil.replace(text, "&#041;", ")");
		text = StringUtil.replace(text, "&#035;", "#");
		text = StringUtil.replace(text, "&#037;", "%");
		text = StringUtil.replace(text, "&#059;", ";");
		text = StringUtil.replace(text, "&#043;", "+");
		text = StringUtil.replace(text, "&#045;", "-");

		return text;
	}

	private static boolean _isScriptTag(String text, int start) {
		char item;
		int pos = start;

		if (pos + _TAG_SCRIPT.length + 1 <= text.length()) {
			for (int i = 0; i < _TAG_SCRIPT.length; i++) {
				item = text.charAt(pos++);

				if (Character.toLowerCase(item) != _TAG_SCRIPT[i]) {
					return false;
				}
			}

			item = text.charAt(pos);

			// Check that char after "script" is not a letter (i.e. another tag)

			return !Character.isLetter(item);
		}
		else {
			return false;
		}
	}

	private static final String[] _MS_WORD_UNICODE = new String[] {
		"\u00ae", "\u2019", "\u201c", "\u201d"
	};

	private static final String[] _MS_WORD_HTML = new String[] {
		"&reg;", StringPool.APOSTROPHE, StringPool.QUOTE, StringPool.QUOTE
	};

	private static final char[] _TAG_SCRIPT = {'s', 'c', 'r', 'i', 'p', 't'};

}
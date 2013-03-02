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

package com.liferay.portal.kernel.util;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

/**
 * <a href="UnicodeFormatter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UnicodeFormatter {

	public static char HEX_DIGIT[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};

	public static String byteToHex(byte b) {
		char[] array = {HEX_DIGIT[(b >> 4) & 0x0f], HEX_DIGIT[b & 0x0f]};

		return new String(array);
	}

	public static String charToHex(char c) {
		byte hi = (byte)(c >>> 8);
		byte lo = (byte)(c & 0xff);

		return byteToHex(hi) + byteToHex(lo);
	}

	public static String parseString(String hexString) {
		StringMaker sm = new StringMaker();

		char[] array = hexString.toCharArray();

		if ((array.length % 6) != 0) {
			_log.error("String is not in hex format");

			return hexString;
		}

		for (int i = 2; i < hexString.length(); i = i + 6) {
			String s = hexString.substring(i, i + 4);

			try {
				char c = (char)Integer.parseInt(s, 16);

				sm.append(c);
			}
			catch (Exception e) {
				_log.error(e, e);

				return hexString;
			}
		}

		return sm.toString();
	}

	public static String toString(char[] array) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < array.length; i++) {
			sm.append("\\u");
			sm.append(charToHex(array[i]));
		}

		return sm.toString();
	}

	public static String toString(String s) {
		if (s == null) {
			return null;
		}

		return toString(s.toCharArray());
	}

	private static Log _log = LogFactoryUtil.getLog(UnicodeFormatter.class);

}
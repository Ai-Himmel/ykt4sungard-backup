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

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * <a href="Xss.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Clarence Shen
 * @version $Revision: 1.3 $
 *
 */
public class Xss {

	public static final String XSS_REGEXP_PATTERN = GetterUtil.getString(
		SystemProperties.get(Xss.class.getName() + ".regexp.pattern"));

	public static final Pattern XSS_PATTERN =
		Pattern.compile(XSS_REGEXP_PATTERN);

	public static String strip(String text) {
		if (text == null) {
			return null;
		}

		CharSequence sequence = text.subSequence(0, text.length());

		Matcher matcher = XSS_PATTERN.matcher(sequence);

		return matcher.replaceAll(StringPool.BLANK);
	}

}
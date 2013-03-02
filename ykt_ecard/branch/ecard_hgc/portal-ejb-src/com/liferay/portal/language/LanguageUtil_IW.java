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

package com.liferay.portal.language;

import javax.servlet.jsp.PageContext;

/**
 * <a href="LanguageUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.17 $
 *
 */
public class LanguageUtil_IW {

	public static LanguageUtil_IW getInstance() {
		return _instance;
	}

	public String format(
			PageContext pageContext, String pattern, Object argument)
		throws LanguageException {

		return LanguageUtil.format(pageContext, pattern, argument);
	}

	public String format(
			PageContext pageContext, String pattern, Object argument,
			boolean translateArguments)
		throws LanguageException {

		return LanguageUtil.format(
			pageContext, pattern, argument, translateArguments);
	}

	public String format(
			PageContext pageContext, String pattern, Object[] arguments)
		throws LanguageException {

		return LanguageUtil.format(pageContext, pattern, arguments);
	}

	public String format(
			PageContext pageContext, String pattern, Object[] arguments,
			boolean translateArguments)
		throws LanguageException {

		return LanguageUtil.format(
			pageContext, pattern, arguments, translateArguments);
	}

	public String get(PageContext pageContext, String key)
		throws LanguageException {

		return LanguageUtil.get(pageContext, key);
	}

	public static String get(
			PageContext pageContext, String key, String defaultValue)
		throws LanguageException {

		return LanguageUtil.get(pageContext, key, defaultValue);
	}

	private LanguageUtil_IW() {
	}

	private static LanguageUtil_IW _instance = new LanguageUtil_IW();

}
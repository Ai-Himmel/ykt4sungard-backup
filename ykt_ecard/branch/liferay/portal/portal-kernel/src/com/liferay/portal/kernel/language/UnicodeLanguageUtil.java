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

package com.liferay.portal.kernel.language;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

import java.util.Locale;

import javax.servlet.jsp.PageContext;

/**
 * <a href="UnicodeLanguageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UnicodeLanguageUtil {

	public static String format(
		Locale locale, String pattern, Object argument) {

		return getUnicodeLanguage().format(locale, pattern, argument);
	}

	public static String format(
		Locale locale, String pattern, Object[] arguments) {

		return getUnicodeLanguage().format(locale, pattern, arguments);
	}

	public static String format(
		long companyId, Locale locale, String pattern, Object argument) {

		return getUnicodeLanguage().format(
			companyId, locale, pattern, argument);
	}

	public static String format(
		long companyId, Locale locale, String pattern, Object[] arguments) {

		return getUnicodeLanguage().format(
			companyId, locale, pattern, arguments);
	}

	public static String format(
		PageContext pageContext, String pattern, Object argument) {

		return getUnicodeLanguage().format(pageContext, pattern, argument);
	}

	public static String format(
		PageContext pageContext, String pattern, Object argument,
		boolean translateArguments) {

		return getUnicodeLanguage().format(
			pageContext, pattern, argument, translateArguments);
	}

	public static String format(
		PageContext pageContext, String pattern, Object[] arguments) {

		return getUnicodeLanguage().format(pageContext, pattern, arguments);
	}

	public static String format(
		PageContext pageContext, String pattern, Object[] arguments,
		boolean translateArguments) {

		return getUnicodeLanguage().format(
			pageContext, pattern, arguments, translateArguments);
	}

	public static String format(
		PageContext pageContext, String pattern, LanguageWrapper argument) {

		return getUnicodeLanguage().format(pageContext, pattern, argument);
	}

	public static String format(
		PageContext pageContext, String pattern, LanguageWrapper argument,
		boolean translateArguments) {

		return getUnicodeLanguage().format(
			pageContext, pattern, argument, translateArguments);
	}

	public static String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments) {

		return getUnicodeLanguage().format(pageContext, pattern, arguments);
	}

	public static String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments,
		boolean translateArguments) {

		return getUnicodeLanguage().format(
			pageContext, pattern, arguments, translateArguments);
	}

	public static String get(Locale locale, String key) {
		return getUnicodeLanguage().get(locale, key);
	}

	public static String get(long companyId, Locale locale, String key) {
		return getUnicodeLanguage().get(companyId, locale, key);
	}

	public static String get(
		long companyId, Locale locale, String key, String defaultValue) {

		return getUnicodeLanguage().get(companyId, locale, key, defaultValue);
	}

	public static String get(PageContext pageContext, String key) {
		return getUnicodeLanguage().get(pageContext, key);
	}

	public static String get(
		PageContext pageContext, String key, String defaultValue) {

		return getUnicodeLanguage().get(pageContext, key, defaultValue);
	}

	public static String getTimeDescription(
		PageContext pageContext, Long milliseconds) {

		return getUnicodeLanguage().getTimeDescription(
			pageContext, milliseconds);
	}

	public static String getTimeDescription(
		PageContext pageContext, long milliseconds) {

		return getUnicodeLanguage().getTimeDescription(
			pageContext, milliseconds);
	}

	public static UnicodeLanguage getUnicodeLanguage() {
		return _getUtil()._unicodeLanguage;
	}

	public void setUnicodeLanguage(UnicodeLanguage unicodeLanguage) {
		_unicodeLanguage = unicodeLanguage;
	}

	private static UnicodeLanguageUtil _getUtil() {
		if (_util == null) {
			_util = (UnicodeLanguageUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = UnicodeLanguageUtil.class.getName();

	private static UnicodeLanguageUtil _util;

	private UnicodeLanguage _unicodeLanguage;

}
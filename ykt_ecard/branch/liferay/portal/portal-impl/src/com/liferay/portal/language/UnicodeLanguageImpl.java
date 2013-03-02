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

package com.liferay.portal.language;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.language.LanguageWrapper;
import com.liferay.portal.kernel.language.UnicodeLanguage;
import com.liferay.portal.kernel.util.UnicodeFormatter;

import java.util.Locale;

import javax.servlet.jsp.PageContext;

/**
 * <a href="UnicodeLanguageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UnicodeLanguageImpl implements UnicodeLanguage {

	public String format(Locale locale, String pattern, Object argument) {
		return UnicodeFormatter.toString(LanguageUtil.format(
			locale, pattern, argument));
	}

	public String format(Locale locale, String pattern, Object[] arguments) {
		return UnicodeFormatter.toString(LanguageUtil.format(
			locale, pattern, arguments));
	}

	public String format(
		long companyId, Locale locale, String pattern, Object argument) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			companyId, locale, pattern, argument));
	}

	public String format(
		long companyId, Locale locale, String pattern, Object[] arguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			companyId, locale, pattern, arguments));
	}

	public String format(
		PageContext pageContext, String pattern, Object argument) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, argument));
	}

	public String format(
		PageContext pageContext, String pattern, Object argument,
		boolean translateArguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, argument, translateArguments));
	}

	public String format(
		PageContext pageContext, String pattern, Object[] arguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, arguments));
	}

	public String format(
		PageContext pageContext, String pattern, Object[] arguments,
		boolean translateArguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, arguments, translateArguments));
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper argument) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, argument));
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper argument,
		boolean translateArguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, argument, translateArguments));
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, arguments));
	}

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments,
		boolean translateArguments) {

		return UnicodeFormatter.toString(LanguageUtil.format(
			pageContext, pattern, arguments, translateArguments));
	}

	public String get(Locale locale, String key) {
		return UnicodeFormatter.toString(LanguageUtil.get(locale, key));
	}

	public String get(long companyId, Locale locale, String key) {
		return UnicodeFormatter.toString(
			LanguageUtil.get(companyId, locale, key));
	}

	public String get(
		long companyId, Locale locale, String key, String defaultValue) {

		return UnicodeFormatter.toString(
			LanguageUtil.get(companyId, locale, key, defaultValue));
	}

	public String get(PageContext pageContext, String key) {
		return UnicodeFormatter.toString(LanguageUtil.get(pageContext, key));
	}

	public String get(
		PageContext pageContext, String key, String defaultValue) {

		return UnicodeFormatter.toString(LanguageUtil.get(
			pageContext, key, defaultValue));
	}

	public String getTimeDescription(
		PageContext pageContext, Long milliseconds) {

		return UnicodeFormatter.toString(LanguageUtil.getTimeDescription(
			pageContext, milliseconds));
	}

	public String getTimeDescription(
		PageContext pageContext, long milliseconds) {

		return UnicodeFormatter.toString(LanguageUtil.getTimeDescription(
			pageContext, milliseconds));
	}

}
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

import java.util.Locale;

import javax.servlet.jsp.PageContext;

/**
 * <a href="UnicodeLanguage.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface UnicodeLanguage {

	public String format(Locale locale, String pattern, Object argument);

	public String format(Locale locale, String pattern, Object[] arguments);

	public String format(
		long companyId, Locale locale, String pattern, Object argument);

	public String format(
		long companyId, Locale locale, String pattern, Object[] arguments);

	public String format(
		PageContext pageContext, String pattern, Object argument);

	public String format(
		PageContext pageContext, String pattern, Object argument,
		boolean translateArguments);

	public String format(
		PageContext pageContext, String pattern, Object[] arguments);

	public String format(
		PageContext pageContext, String pattern, Object[] arguments,
		boolean translateArguments);

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper argument);

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper argument,
		boolean translateArguments);

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments);

	public String format(
		PageContext pageContext, String pattern, LanguageWrapper[] arguments,
		boolean translateArguments);

	public String get(Locale locale, String key);

	public String get(long companyId, Locale locale, String key);

	public String get(
		long companyId, Locale locale, String key, String defaultValue);

	public String get(PageContext pageContext, String key);

	public String get(PageContext pageContext, String key, String defaultValue);

	public String getTimeDescription(
		PageContext pageContext, Long milliseconds);

	public String getTimeDescription(
		PageContext pageContext, long milliseconds);

}
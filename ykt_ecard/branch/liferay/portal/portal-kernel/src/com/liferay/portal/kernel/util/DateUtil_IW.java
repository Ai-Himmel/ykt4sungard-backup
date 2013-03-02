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

/**
 * <a href="DateUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DateUtil_IW {
	public static DateUtil_IW getInstance() {
		return _instance;
	}

	public int compareTo(java.util.Date date1, java.util.Date date2) {
		return DateUtil.compareTo(date1, date2);
	}

	public java.lang.String getCurrentDate(java.lang.String pattern,
		java.util.Locale locale) {
		return DateUtil.getCurrentDate(pattern, locale);
	}

	public java.lang.String getDate(java.util.Date date,
		java.lang.String pattern, java.util.Locale locale) {
		return DateUtil.getDate(date, pattern, locale);
	}

	public java.text.DateFormat getISOFormat() {
		return DateUtil.getISOFormat();
	}

	public java.text.DateFormat getISOFormat(java.lang.String text) {
		return DateUtil.getISOFormat(text);
	}

	public java.text.DateFormat getISO8601Format() {
		return DateUtil.getISO8601Format();
	}

	public java.text.DateFormat getUTCFormat() {
		return DateUtil.getUTCFormat();
	}

	public java.text.DateFormat getUTCFormat(java.lang.String text) {
		return DateUtil.getUTCFormat(text);
	}

	private DateUtil_IW() {
	}

	private static DateUtil_IW _instance = new DateUtil_IW();
}
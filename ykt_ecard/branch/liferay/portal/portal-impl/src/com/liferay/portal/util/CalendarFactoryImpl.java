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

package com.liferay.portal.util;

import com.liferay.portal.kernel.util.CalendarFactory;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;

/**
 * <a href="CalendarFactoryImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalendarFactoryImpl implements CalendarFactory {

	public Calendar getCalendar() {
		return new GregorianCalendar();
	}

	public Calendar getCalendar(int year, int month, int date) {
		return new GregorianCalendar(year, month, date);
	}

	public Calendar getCalendar(
		int year, int month, int date, int hour, int minute) {

		return new GregorianCalendar(year, month, date, hour, minute);
	}

	public Calendar getCalendar(
		int year, int month, int date, int hour, int minute, int second) {

		return new GregorianCalendar(year, month, date, hour, minute, second);
	}

	public Calendar getCalendar(Locale locale) {
		return new GregorianCalendar(locale);
	}

	public Calendar getCalendar(TimeZone timeZone) {
		return new GregorianCalendar(timeZone);
	}

	public Calendar getCalendar(TimeZone timeZone, Locale locale) {
		return new GregorianCalendar(timeZone, locale);
	}

}
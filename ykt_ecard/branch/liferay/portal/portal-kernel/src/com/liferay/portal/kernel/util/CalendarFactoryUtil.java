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

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

import java.util.Calendar;
import java.util.Locale;
import java.util.TimeZone;

/**
 * <a href="CalendarFactoryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalendarFactoryUtil {

	public static Calendar getCalendar() {
		return getCalendarFactory().getCalendar();
	}

	public static Calendar getCalendar(int year, int month, int date) {
		return getCalendarFactory().getCalendar(year, month, date);
	}

	public static Calendar getCalendar(
		int year, int month, int date, int hour, int minute) {

		return getCalendarFactory().getCalendar(
			year, month, date, hour, minute);
	}

	public static Calendar getCalendar(
		int year, int month, int date, int hour, int minute, int second) {

		return getCalendarFactory().getCalendar(
			year, month, date, hour, minute, second);
	}

	public static Calendar getCalendar(Locale locale) {
		return getCalendarFactory().getCalendar(locale);
	}

	public static Calendar getCalendar(TimeZone timeZone) {
		return getCalendarFactory().getCalendar(timeZone);
	}

	public static Calendar getCalendar(TimeZone timeZone, Locale locale) {
		return getCalendarFactory().getCalendar(timeZone, locale);
	}

	public static CalendarFactory getCalendarFactory() {
		return _getUtil()._calendarFactory;
	}

	public void setCalendarFactory(CalendarFactory calendarFactory) {
		_calendarFactory = calendarFactory;
	}

	private static CalendarFactoryUtil _getUtil() {
		if (_util == null) {
			_util = (CalendarFactoryUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CalendarFactoryUtil.class.getName();

	private static CalendarFactoryUtil _util;

	private CalendarFactory _calendarFactory;

}
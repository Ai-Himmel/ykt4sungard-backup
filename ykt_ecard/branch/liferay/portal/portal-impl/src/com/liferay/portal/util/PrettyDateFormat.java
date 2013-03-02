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

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.StringPool;

import java.text.DateFormat;
import java.text.FieldPosition;
import java.text.ParsePosition;

import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

/**
 * <a href="PrettyDateFormat.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class PrettyDateFormat extends DateFormat {

	public PrettyDateFormat(long companyId, Locale locale, TimeZone timeZone) {
		_companyId = companyId;
		_locale = locale;
		_timeZone = timeZone;
		_todayString = LanguageUtil.get(_companyId, _locale, "today");
		_yesterdayString = LanguageUtil.get(_companyId, _locale, "yesterday");
	}

	public StringBuffer format(Date date, StringBuffer sb, FieldPosition pos) {
		String dateString = StringPool.NBSP;

		if (date != null) {
			Date today = new Date();

			Calendar cal = Calendar.getInstance(_timeZone, _locale);

			cal.setTime(today);
			cal.add(Calendar.DATE, -1);

			Date yesterday = cal.getTime();

			DateFormat dateFormatDate = DateFormats.getDate(_locale, _timeZone);
			DateFormat dateFormatDateTime =
				DateFormats.getDateTime(_locale, _timeZone);
			DateFormat dateFormatTime = DateFormats.getTime(_locale, _timeZone);

			dateString = dateFormatDate.format(date);

			if (dateString.equals(dateFormatDate.format(today))) {
				dateString =
					_todayString + StringPool.SPACE +
						dateFormatTime.format(date);
			}
			else if (dateString.equals(dateFormatDate.format(yesterday))) {
				dateString =
					_yesterdayString + StringPool.SPACE +
						dateFormatTime.format(date);
			}
			else {
				dateString = dateFormatDateTime.format(date);
			}
		}

		return sb.append(dateString);
	}

	public Date parse(String source, ParsePosition pos) {
		DateFormat dateFormatDate = DateFormats.getDate(_locale, _timeZone);

		DateFormat dateFormatDateTime =
			DateFormats.getDateTime(_locale, _timeZone);

		Date today = new Date();

		String dateString = source.substring(pos.getIndex());

		if (dateString.startsWith(_todayString)) {
			dateString.replaceFirst(_todayString, dateFormatDate.format(today));
		}
		else if (dateString.startsWith(_yesterdayString)) {
			Calendar cal = Calendar.getInstance(_timeZone, _locale);

			cal.setTime(today);
			cal.add(Calendar.DATE, -1);

			Date yesterday = cal.getTime();

			dateString.replaceFirst(
				_todayString, dateFormatDate.format(yesterday));
		}

		return dateFormatDateTime.parse(dateString, new ParsePosition(0));
	}

	private long _companyId;
	private Locale _locale;
	private TimeZone _timeZone;
	private String _todayString;
	private String _yesterdayString;

}
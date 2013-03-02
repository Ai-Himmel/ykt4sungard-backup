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

package com.liferay.portlet.reverendfun.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.util.ConverterException;
import com.liferay.util.Http;
import com.liferay.util.StringComparator;
import com.liferay.util.Time;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="ReverendFunConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class ReverendFunConverter implements WebCacheable {

	public ReverendFunConverter(String date) {
		_date = date;
	}

	public Object convert(String id) throws ConverterException {
		Set dates = new TreeSet(new StringComparator(false, true));

		try {
			DateFormat yearMonthDayDF = new SimpleDateFormat("yyyyMMdd");
			DateFormat yearMonthDF = new SimpleDateFormat("yyyyMM");

			Calendar cal = new GregorianCalendar();
			cal.setTime(yearMonthDayDF.parse(_date));
			cal.set(Calendar.DATE, 1);

			Calendar now = new GregorianCalendar();

			String url =
				"http://rev-fun.gospelcom.net/artchives/monthly.php?month=";

			while (cal.before(now)) {
				String text = Http.URLtoString(
					url + yearMonthDF.format(cal.getTime()));

				int x = text.indexOf("date=");
				int y = text.indexOf("\">", x);

				while (x != -1 && y != -1) {
					String fromDateString = text.substring(x + 5, y);

					dates.add(fromDateString);

					x = text.indexOf("date=", y);
					y = text.indexOf("\">", x);
				}

				cal.add(Calendar.MONTH, 1);
			}
		}
		catch (Exception e) {
			throw new ConverterException(_date + " " + e.toString());
		}

		return dates;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY;

	private String _date;

}
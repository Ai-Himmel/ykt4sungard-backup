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

package com.liferay.portlet.reverendfun.util;

import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.StringComparator;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.util.Http;
import com.liferay.util.Time;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.Calendar;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="ReverendFunWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ReverendFunWebCacheItem implements WebCacheItem {

	public ReverendFunWebCacheItem(String date) {
		_date = date;
	}

	public Object convert(String key) throws WebCacheException {
		Set dates = new TreeSet(new StringComparator(false, true));

		try {
			DateFormat dateFormatYMD = new SimpleDateFormat("yyyyMMdd");
			DateFormat dateFormatYM = new SimpleDateFormat("yyyyMM");

			Calendar cal = CalendarFactoryUtil.getCalendar();

			cal.setTime(dateFormatYMD.parse(_date));
			cal.set(Calendar.DATE, 1);

			Calendar now = CalendarFactoryUtil.getCalendar();

			String url = "http://www.reverendfun.com/artchives/?search=";

			while (cal.before(now)) {
				String text = Http.URLtoString(
					url + dateFormatYM.format(cal.getTime()));

				int x = text.indexOf("date=");
				int y = text.indexOf("\"", x);

				while (x != -1 && y != -1) {
					String fromDateString = text.substring(x + 5, y);

					dates.add(fromDateString);

					x = text.indexOf("date=", y);
					y = text.indexOf("\"", x);
				}

				cal.add(Calendar.MONTH, 1);
			}
		}
		catch (Exception e) {
			throw new WebCacheException(_date + " " + e.toString());
		}

		return dates;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY;

	private String _date;

}
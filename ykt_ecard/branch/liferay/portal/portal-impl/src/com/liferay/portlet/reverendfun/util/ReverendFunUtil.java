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

import com.liferay.portal.kernel.util.StringComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portal.kernel.webcache.WebCachePoolUtil;
import com.liferay.portal.util.ContentUtil;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <a href="ReverendFunUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ReverendFunUtil {

	public static String getCurrentDate() {
		return _instance._getCurrentDate();
	}

	public static String getNextDate(String date) {
		return _instance._getNextDate(date);
	}

	public static String getPreviousDate(String date) {
		return _instance._getPreviousDate(date);
	}

	public static boolean hasDate(String date) {
		return _instance._hasDate(date);
	}

	private ReverendFunUtil() {
		_dates = new ArrayList();

		String[] dates = StringUtil.split(ContentUtil.get(
			"com/liferay/portlet/reverendfun/dependencies/dates.txt"), "\n");

		for (int i = 0; i < dates.length; i++) {
			_dates.add(dates[i]);
		}
	}

	private String _getCurrentDate() {
		String dates0 = (String)_dates.get(0);

		try {
			Set moreDates = _getMoreDates(dates0);

			if (moreDates.size() > 0) {
				String moreDates0 = (String)moreDates.iterator().next();

				if (!moreDates0.equals(dates0)) {
					_dates.addAll(0, moreDates);

					// Trim duplicate dates

					Set datesSet = new HashSet();

					Iterator itr = _dates.iterator();

					while (itr.hasNext()) {
						String date = (String)itr.next();

						if (datesSet.contains(date)) {
							itr.remove();
						}
						else {
							datesSet.add(date);
						}
					}
				}
			}
		}
		catch (Exception e) {
		}

		String currentDate = (String)_dates.get(1);

		return currentDate;
	}

	private Set _getMoreDates(String date) {
		WebCacheItem wci = new ReverendFunWebCacheItem(date);

		return (Set)WebCachePoolUtil.get(
			ReverendFunUtil.class.getName() + StringPool.PERIOD + date, wci);
	}

	private String _getNextDate(String date) {
		int pos = Collections.binarySearch(
			_dates, date, new StringComparator(false, true));

		if (pos > 1) {
			return (String)_dates.get(pos - 1);
		}

		return null;
	}

	private String _getPreviousDate(String date) {
		int pos = Collections.binarySearch(
			_dates, date, new StringComparator(false, true));

		if (pos > -1 && pos < _dates.size() - 1) {
			return (String)_dates.get(pos + 1);
		}

		return null;
	}

	private boolean _hasDate(String date) {
		int pos = Collections.binarySearch(
			_dates, date, new StringComparator(false, true));

		if (pos >= 1) {
			return true;
		}
		else {
			return false;
		}
	}

	private static ReverendFunUtil _instance = new ReverendFunUtil();

	private List _dates;

}
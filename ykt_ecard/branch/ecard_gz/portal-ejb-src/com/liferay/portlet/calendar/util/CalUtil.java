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

package com.liferay.portlet.calendar.util;

import com.liferay.portal.language.LanguageException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.model.CalTask;
import com.liferay.util.Time;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.text.DateFormat;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;

import javax.servlet.jsp.PageContext;

/**
 * <a href="CalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.23 $
 *
 */
public class CalUtil {

	public static Date getEndTime(CalEvent event) {
		long startTime = event.getStartDate().getTime();

		long endTime = startTime +
					   Time.HOUR * event.getDurationHour() +
					   Time.MINUTE * event.getDurationMinute();

		return new Date(endTime);
	}

	public static String getDueDate(
			CalTask task, DateFormat dateFormat, PageContext pageContext,
			TimeZone timeZone)
		throws LanguageException {

		if (task.isNoDueDate()) {
			return LanguageUtil.get(pageContext, "none");
		}
		else {
			Calendar dueCal = new GregorianCalendar();
			dueCal.setTime(task.getDueDate());

			Calendar nowCal = new GregorianCalendar(timeZone);

			int dueGregorianDay = CalendarUtil.getGregorianDay(dueCal);
			int nowGregorianDay = CalendarUtil.getGregorianDay(nowCal);

			if (dueGregorianDay == nowGregorianDay) {
				return LanguageUtil.get(pageContext, "today");
			}
			else if (dueGregorianDay - nowGregorianDay == 1) {
				return LanguageUtil.get(pageContext, "tomorrow");
			}
			else if (dueGregorianDay - nowGregorianDay == -1) {
				return LanguageUtil.get(pageContext, "yesterday");
			}
			else {
				return dateFormat.format(task.getDueDate());
			}
		}
	}

	public static boolean isAllDay(CalEvent event, TimeZone timeZone,
								   Locale locale) {

		Calendar cal = null;

		if (event.getTimeZoneSensitive()) {
			cal = new GregorianCalendar(timeZone, locale);
		}
		else {
			cal = new GregorianCalendar();
		}

		cal.setTime(event.getStartDate());

		int hour = cal.get(Calendar.HOUR_OF_DAY);
		int minute = cal.get(Calendar.MINUTE);
		int second = cal.get(Calendar.SECOND);
		int millisecond = cal.get(Calendar.MILLISECOND);

		int dHour = event.getDurationHour();
		int dMinute = event.getDurationMinute();

		if ((hour == 0) && (minute == 0) && (second == 0) &&
			(millisecond == 0) && (dHour == 24) && (dMinute == 0)) {

			return true;
		}

		return false;
	}

	public static String toString(Calendar cal) {
		FastStringBuffer sb = new FastStringBuffer();
		sb.append(cal.get(Calendar.YEAR)).append(".");
		sb.append(cal.get(Calendar.MONTH)).append(".");
		sb.append(cal.get(Calendar.DATE)).append(".");
		sb.append(cal.getTimeZone().getRawOffset());

		return sb.toString();
	}

}
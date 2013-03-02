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

package com.liferay.portlet.calendar.util;

import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.util.Time;

import java.io.IOException;

import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

import javax.portlet.PortletPreferences;

/**
 * <a href="CalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalUtil {

	public static String getEmailFromAddress(PortletPreferences prefs) {
		String emailFromAddress = PropsUtil.get(
			PropsUtil.CALENDAR_EMAIL_FROM_ADDRESS);

		return prefs.getValue("email-from-address", emailFromAddress);
	}

	public static String getEmailFromName(PortletPreferences prefs) {
		String emailFromName = PropsUtil.get(
			PropsUtil.CALENDAR_EMAIL_FROM_NAME);

		return prefs.getValue("email-from-name", emailFromName);
	}

	public static boolean getEmailEventReminderEnabled(
		PortletPreferences prefs) {

		String emailEventReminderEnabled = prefs.getValue(
			"email-event-reminder-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailEventReminderEnabled)) {
			return GetterUtil.getBoolean(emailEventReminderEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.CALENDAR_EMAIL_EVENT_REMINDER_ENABLED));
		}
	}

	public static String getEmailEventReminderBody(PortletPreferences prefs)
		throws IOException {

		String emailEventReminderBody = prefs.getValue(
			"email-event-reminder-body", StringPool.BLANK);

		if (Validator.isNotNull(emailEventReminderBody)) {
			return emailEventReminderBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.CALENDAR_EMAIL_EVENT_REMINDER_BODY));
		}
	}

	public static String getEmailEventReminderSubject(PortletPreferences prefs)
		throws IOException {

		String emailEventReminderSubject = prefs.getValue(
			"email-event-reminder-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailEventReminderSubject)) {
			return emailEventReminderSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.CALENDAR_EMAIL_EVENT_REMINDER_SUBJECT));
		}
	}

	public static Date getEndTime(CalEvent event) {
		long startTime = event.getStartDate().getTime();

		long endTime =
			startTime + (Time.HOUR * event.getDurationHour()) +
				(Time.MINUTE * event.getDurationMinute());

		return new Date(endTime);
	}

	public static boolean isAllDay(
		CalEvent event, TimeZone timeZone, Locale locale) {

		Calendar cal = null;

		if (event.getTimeZoneSensitive()) {
			cal = CalendarFactoryUtil.getCalendar(timeZone, locale);
		}
		else {
			cal = CalendarFactoryUtil.getCalendar();
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
		StringMaker sm = new StringMaker();

		sm.append(cal.get(Calendar.YEAR));
		sm.append(StringPool.PERIOD);
		sm.append(cal.get(Calendar.MONTH));
		sm.append(StringPool.PERIOD);
		sm.append(cal.get(Calendar.DATE));
		sm.append(StringPool.PERIOD);
		sm.append(cal.getTimeZone().getRawOffset());

		return sm.toString();
	}

}
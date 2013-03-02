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

package com.liferay.portlet.calendar.action;

import com.liferay.portal.kernel.cal.DayAndPosition;
import com.liferay.portal.kernel.cal.Duration;
import com.liferay.portal.kernel.cal.Recurrence;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.TimeZoneUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.calendar.EventDurationException;
import com.liferay.portlet.calendar.EventEndDateException;
import com.liferay.portlet.calendar.EventStartDateException;
import com.liferay.portlet.calendar.EventTitleException;
import com.liferay.portlet.calendar.NoSuchEventException;
import com.liferay.portlet.calendar.service.CalEventServiceUtil;
import com.liferay.util.servlet.SessionErrors;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditEventAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditEventAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateEvent(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteEvent(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchEventException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.calendar.error");
			}
			else if (e instanceof EventDurationException ||
					 e instanceof EventEndDateException ||
					 e instanceof EventStartDateException ||
					 e instanceof EventTitleException) {

				SessionErrors.add(req, e.getClass().getName());
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			ActionUtil.getEvent(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchEventException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.calendar.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.calendar.edit_event"));
	}

	protected void deleteEvent(ActionRequest req) throws Exception {
		long eventId = ParamUtil.getLong(req, "eventId");

		CalEventServiceUtil.deleteEvent(eventId);
	}

	protected void updateEvent(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long eventId = ParamUtil.getLong(req, "eventId");

		String title = ParamUtil.getString(req, "title");
		String description = ParamUtil.getString(req, "description");

		int startDateMonth = ParamUtil.getInteger(req, "startDateMonth");
		int startDateDay = ParamUtil.getInteger(req, "startDateDay");
		int startDateYear = ParamUtil.getInteger(req, "startDateYear");
		int startDateHour = ParamUtil.getInteger(req, "startDateHour");
		int startDateMinute = ParamUtil.getInteger(req, "startDateMinute");
		int startDateAmPm = ParamUtil.getInteger(req, "startDateAmPm");

		if (startDateAmPm == Calendar.PM) {
			startDateHour += 12;
		}

		int durationHour = ParamUtil.getInteger(req, "durationHour");
		int durationMinute = ParamUtil.getInteger(req, "durationMinute");
		boolean allDay = ParamUtil.getBoolean(req, "allDay");
		boolean timeZoneSensitive = ParamUtil.getBoolean(
			req, "timeZoneSensitive");
		String type = ParamUtil.getString(req, "type");

		int endDateMonth = ParamUtil.getInteger(req, "endDateMonth");
		int endDateDay = ParamUtil.getInteger(req, "endDateDay");
		int endDateYear = ParamUtil.getInteger(req, "endDateYear");

		boolean repeating = false;

		int recurrenceType = ParamUtil.getInteger(req, "recurrenceType");

		if (recurrenceType != Recurrence.NO_RECURRENCE) {
			repeating = true;
		}

		Locale locale = null;
		TimeZone timeZone = null;

		if (timeZoneSensitive) {
			User user = PortalUtil.getUser(req);

			locale = user.getLocale();
			timeZone = user.getTimeZone();
		}
		else {
			locale = LocaleUtil.getDefault();
			timeZone = TimeZoneUtil.getDefault();
		}

		Calendar startDate = CalendarFactoryUtil.getCalendar(timeZone, locale);

		startDate.set(Calendar.MONTH, startDateMonth);
		startDate.set(Calendar.DATE, startDateDay);
		startDate.set(Calendar.YEAR, startDateYear);
		startDate.set(Calendar.HOUR_OF_DAY, startDateHour);
		startDate.set(Calendar.MINUTE, startDateMinute);
		startDate.set(Calendar.SECOND, 0);
		startDate.set(Calendar.MILLISECOND, 0);

		if (allDay) {
			startDate.set(Calendar.HOUR_OF_DAY, 0);
			startDate.set(Calendar.MINUTE, 0);
			startDate.set(Calendar.SECOND, 0);
			startDate.set(Calendar.MILLISECOND, 0);

			durationHour = 24;
			durationMinute = 0;
		}

		Recurrence recurrence = null;

		if (repeating) {
			Calendar recStartCal = null;

			if (timeZoneSensitive) {
				recStartCal = CalendarFactoryUtil.getCalendar();

				recStartCal.setTime(startDate.getTime());
			}
			else {
				recStartCal = (Calendar)startDate.clone();
			}

			recurrence = new Recurrence(
				recStartCal, new Duration(1, 0, 0, 0), recurrenceType);

			recurrence.setWeekStart(Calendar.SUNDAY);

			if (recurrenceType == Recurrence.DAILY) {
				int dailyType = ParamUtil.getInteger(req, "dailyType");

				if (dailyType == 0) {
					int dailyInterval = ParamUtil.getInteger(
						req, "dailyInterval");

					// LEP-3468

					if (dailyInterval <= 0) {
						dailyInterval = 1;
					}

					recurrence.setInterval(dailyInterval);
				}
				else {
					DayAndPosition[] dayPos = {
						new DayAndPosition(Calendar.MONDAY, 0),
						new DayAndPosition(Calendar.TUESDAY, 0),
						new DayAndPosition(Calendar.WEDNESDAY, 0),
						new DayAndPosition(Calendar.THURSDAY, 0),
						new DayAndPosition(Calendar.FRIDAY, 0)};

					recurrence.setByDay(dayPos);
				}
			}
			else if (recurrenceType == Recurrence.WEEKLY) {
				int weeklyInterval = ParamUtil.getInteger(
					req, "weeklyInterval");

				recurrence.setInterval(weeklyInterval);

				List dayPos = new ArrayList();

				_addWeeklyDayPos(req, dayPos, Calendar.SUNDAY);
				_addWeeklyDayPos(req, dayPos, Calendar.MONDAY);
				_addWeeklyDayPos(req, dayPos, Calendar.TUESDAY);
				_addWeeklyDayPos(req, dayPos, Calendar.WEDNESDAY);
				_addWeeklyDayPos(req, dayPos, Calendar.THURSDAY);
				_addWeeklyDayPos(req, dayPos, Calendar.FRIDAY);
				_addWeeklyDayPos(req, dayPos, Calendar.SATURDAY);

				if (dayPos.size() == 0) {
					dayPos.add(new DayAndPosition(Calendar.MONDAY, 0));
				}

				recurrence.setByDay(
					(DayAndPosition[])dayPos.toArray(new DayAndPosition[0]));
			}
			else if (recurrenceType == Recurrence.MONTHLY) {
				int monthlyType = ParamUtil.getInteger(req, "monthlyType");

				if (monthlyType == 0) {
					int monthlyDay = ParamUtil.getInteger(req, "monthlyDay0");

					recurrence.setByMonthDay(new int[] {monthlyDay});

					int monthlyInterval = ParamUtil.getInteger(
						req, "monthlyInterval0");

					recurrence.setInterval(monthlyInterval);
				}
				else {
					int monthlyPos = ParamUtil.getInteger(req, "monthlyPos");
					int monthlyDay = ParamUtil.getInteger(req, "monthlyDay1");

					DayAndPosition[] dayPos = {
						new DayAndPosition(monthlyDay, monthlyPos)};

					recurrence.setByDay(dayPos);

					int monthlyInterval = ParamUtil.getInteger(
						req, "monthlyInterval1");

					recurrence.setInterval(monthlyInterval);
				}
			}
			else if (recurrenceType == Recurrence.YEARLY) {
				int yearlyType = ParamUtil.getInteger(req, "yearlyType");

				if (yearlyType == 0) {
					int yearlyMonth = ParamUtil.getInteger(req, "yearlyMonth0");
					int yearlyDay = ParamUtil.getInteger(req, "yearlyDay0");

					recurrence.setByMonth(new int[] {yearlyMonth});
					recurrence.setByMonthDay(new int[] {yearlyDay});

					int yearlyInterval = ParamUtil.getInteger(
						req, "yearlyInterval0");

					recurrence.setInterval(yearlyInterval);
				}
				else {
					int yearlyPos = ParamUtil.getInteger(req, "yearlyPos");
					int yearlyDay = ParamUtil.getInteger(req, "yearlyDay1");
					int yearlyMonth = ParamUtil.getInteger(req, "yearlyMonth1");

					DayAndPosition[] dayPos = {
						new DayAndPosition(yearlyDay, yearlyPos)};

					recurrence.setByDay(dayPos);

					recurrence.setByMonth(new int[] {yearlyMonth});

					int yearlyInterval = ParamUtil.getInteger(
						req, "yearlyInterval1");

					recurrence.setInterval(yearlyInterval);
				}
			}

			int endDateType = ParamUtil.getInteger(req, "endDateType");

			if (endDateType == 1) {
				int endDateOccurrence = ParamUtil.getInteger(
					req, "endDateOccurrence");

				recurrence.setOccurrence(endDateOccurrence);
			}
			else if (endDateType == 2) {
				Calendar recEndCal = null;

				if (timeZoneSensitive) {
					recEndCal = CalendarFactoryUtil.getCalendar();

					recEndCal.setTime(startDate.getTime());
				}
				else {
					recEndCal = (Calendar)startDate.clone();
				}

				recEndCal.set(Calendar.MONTH, endDateMonth);
				recEndCal.set(Calendar.DATE, endDateDay);
				recEndCal.set(Calendar.YEAR, endDateYear);

				recurrence.setUntil(recEndCal);
			}
		}

		String remindBy = ParamUtil.getString(req, "remindBy");
		int firstReminder = ParamUtil.getInteger(req, "firstReminder");
		int secondReminder = ParamUtil.getInteger(req, "secondReminder");

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (eventId <= 0) {

			// Add event

			CalEventServiceUtil.addEvent(
				layout.getPlid(), title, description, startDateMonth,
				startDateDay, startDateYear, startDateHour, startDateMinute,
				endDateMonth, endDateDay, endDateYear, durationHour,
				durationMinute, allDay, timeZoneSensitive, type, repeating,
				recurrence, remindBy, firstReminder, secondReminder,
				communityPermissions, guestPermissions);
		}
		else {

			// Update event

			CalEventServiceUtil.updateEvent(
				eventId, title, description, startDateMonth, startDateDay,
				startDateYear, startDateHour, startDateMinute, endDateMonth,
				endDateDay, endDateYear, durationHour, durationMinute,
				allDay, timeZoneSensitive, type, repeating, recurrence,
				remindBy, firstReminder, secondReminder);
		}
	}

	private void _addWeeklyDayPos(ActionRequest req, List list, int day) {
		if (ParamUtil.getBoolean(req, "weeklyDayPos" + day)) {
			list.add(new DayAndPosition(day, 0));
		}
	}

}
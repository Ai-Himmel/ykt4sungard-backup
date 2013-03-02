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

package com.liferay.portlet.calendar.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.calendar.EventDurationException;
import com.liferay.portlet.calendar.EventEndDateException;
import com.liferay.portlet.calendar.EventStartDateException;
import com.liferay.portlet.calendar.EventTitleException;
import com.liferay.portlet.calendar.NoSuchEventException;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.service.spring.CalEventServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.cal.DayAndPosition;
import com.liferay.util.cal.Duration;
import com.liferay.util.cal.Recurrence;
import com.liferay.util.servlet.SessionErrors;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditEventAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class EditEventAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			ActionUtil.getEvent(req);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			setForward(req, Constants.COMMON_ERROR);
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_updateEvent(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof EventDurationException ||
					e instanceof EventEndDateException ||
					e instanceof EventStartDateException ||
					e instanceof EventTitleException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.calendar.edit_event");
				}
				else if (e != null &&
						 e instanceof NoSuchEventException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.calendar.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals(Constants.DELETE))) {
			try {
				_deleteEvent(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchEventException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.calendar.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.calendar.edit_event");
		}
	}

	private void _addWeeklyDayPos(ActionRequest req, List list, int day) {
		if (ParamUtil.get(req, "event_rec_w_dp_" + day, false)) {
			list.add(new DayAndPosition(day, 0));
		}
	}

	private void _deleteEvent(ActionRequest req, ActionResponse res)
		throws Exception {

		CalEvent event = (CalEvent)req.getAttribute(WebKeys.CALENDAR_EVENT);

		if (event != null) {

			// Delete event

			CalEventServiceUtil.deleteEvent(event.getEventId());
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateEvent(ActionRequest req, ActionResponse res)
		throws Exception {

		String eventId = ParamUtil.getString(req, "event_id");

		String title = ParamUtil.getString(req, "event_title");
		String description = ParamUtil.getString(req, "event_desc");
		int sdMonth = ParamUtil.get(req, "event_sd_month", 0);
		int sdDay = ParamUtil.get(req, "event_sd_day", 0);
		int sdYear = ParamUtil.get(req, "event_sd_year", 0);
		int sdHour = ParamUtil.get(req, "event_sd_hour", 0);
		int sdMinute = ParamUtil.get(req, "event_sd_minute", 0);
		int sdAMPM = ParamUtil.get(req, "event_sd_am_pm", Calendar.AM);
		int dHour = ParamUtil.get(req, "event_d_hour", 1);
		int dMinute = ParamUtil.get(req, "event_d_minute", 0);
		boolean allDay = ParamUtil.get(req, "event_all_day", false);
		boolean tzSensitive = ParamUtil.get(req, "event_tz_sensitive", true);
		String type = ParamUtil.get(req, "event_type", "1");
		String location = ParamUtil.getString(req, "event_location");
		String street = ParamUtil.getString(req, "event_street");
		String city = ParamUtil.getString(req, "event_city");
		String state = ParamUtil.getString(req, "event_state");
		String zip = ParamUtil.getString(req, "event_zip");
		String phone = ParamUtil.getString(req, "event_phone");
		int edMonth = ParamUtil.get(req, "event_ed_month", 0);
		int edDay = ParamUtil.get(req, "event_ed_day", 0);
		int edYear = ParamUtil.get(req, "event_ed_year", 0);

		boolean repeating = false;

		int recurrenceType = ParamUtil.get(
			req, "event_rec_type", Recurrence.NO_RECURRENCE);

		if (recurrenceType != Recurrence.NO_RECURRENCE) {
			repeating = true;
		}

		int endDateType = ParamUtil.get(req, "event_ed_type", 0);

		String remindBy = ParamUtil.get(
			req, "event_remind_by", CalEvent.REMIND_BY_NONE);
		int firstReminder = ParamUtil.get(req, "event_first_reminder", 0);
		int secondReminder = ParamUtil.get(req, "event_second_reminder", 0);

		Locale locale = null;
		TimeZone timeZone = null;

		if (tzSensitive) {
			User user = PortalUtil.getUser(req);

			locale = user.getLocale();
			timeZone = user.getTimeZone();
		}
		else {
			locale = Locale.getDefault();
			timeZone = TimeZone.getDefault();
		}

		if (sdAMPM == Calendar.PM) {
			sdHour += 12;
		}

		Calendar startCal = new GregorianCalendar(timeZone, locale);
		startCal.set(Calendar.MONTH, sdMonth);
		startCal.set(Calendar.DATE, sdDay);
		startCal.set(Calendar.YEAR, sdYear);
		startCal.set(Calendar.HOUR_OF_DAY, sdHour);
		startCal.set(Calendar.MINUTE, sdMinute);
		startCal.set(Calendar.SECOND, 0);
		startCal.set(Calendar.MILLISECOND, 0);

		if (allDay) {
			startCal.set(Calendar.HOUR_OF_DAY, 0);
			startCal.set(Calendar.MINUTE, 0);
			startCal.set(Calendar.SECOND, 0);
			startCal.set(Calendar.MILLISECOND, 0);
			dHour = 24;
			dMinute = 0;
		}

		Recurrence recurrence = null;

		if (repeating) {
			Calendar recStartCal = null;

			if (tzSensitive) {
				recStartCal = new GregorianCalendar();
				recStartCal.setTime(startCal.getTime());
			}
			else {
				recStartCal = (Calendar)startCal.clone();
			}

			recurrence = new Recurrence(
				recStartCal, new Duration(1, 0, 0, 0), recurrenceType);

			recurrence.setWeekStart(Calendar.SUNDAY);

			if (recurrenceType == Recurrence.DAILY) {
				int dailyType = ParamUtil.get(req, "event_rec_d_type", 0);

				if (dailyType == 0) {
					int dailyInterval = ParamUtil.get(
						req, "event_rec_d_interval", 1);
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
				int weeklyInterval = ParamUtil.get(
					req, "event_rec_w_interval", 1);
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

				recurrence.setByDay((DayAndPosition[])dayPos.toArray(
					new DayAndPosition[0]));
			}
			else if (recurrenceType == Recurrence.MONTHLY) {
				int monthlyType = ParamUtil.get(req, "event_rec_m_type", 0);

				if (monthlyType == 0) {
					int monthlyDay = ParamUtil.get(
						req, "event_rec_m_day_0", 15);
					recurrence.setByMonthDay(new int[] {monthlyDay});

					int monthlyInterval = ParamUtil.get(
						req, "event_rec_m_interval_0", 1);
					recurrence.setInterval(monthlyInterval);
				}
				else {
					int monthlyPos = ParamUtil.get(req, "event_rec_m_pos", 1);
					int monthlyDay = ParamUtil.get(
						req, "event_rec_m_day_1", Calendar.SUNDAY);

					DayAndPosition[] dayPos = {
						new DayAndPosition(monthlyDay, monthlyPos)};
					recurrence.setByDay(dayPos);

					int monthlyInterval = ParamUtil.get(
						req, "event_rec_m_interval_1", 1);
					recurrence.setInterval(monthlyInterval);
				}
			}
			else if (recurrenceType == Recurrence.YEARLY) {
				int yearlyType = ParamUtil.get(req, "event_rec_y_type", 0);

				if (yearlyType == 0) {
					int yearlyMonth = ParamUtil.get(
						req, "event_rec_y_month_0", Calendar.JANUARY);
					int yearlyDay = ParamUtil.get(req, "event_rec_y_day_0", 15);

					Calendar yearlyCal = (Calendar)recStartCal.clone();
					yearlyCal.set(Calendar.MONTH, yearlyMonth);
					yearlyCal.set(Calendar.DATE, yearlyDay);

					if (yearlyCal.before(recStartCal)) {
						yearlyCal.add(Calendar.YEAR, 1);
					}

					recurrence.setDtStart(yearlyCal);

					int yearlyInterval = ParamUtil.get(
						req, "event_rec_y_interval_0", 1);
					recurrence.setInterval(yearlyInterval);
				}
				else {
					int yearlyPos = ParamUtil.get(req, "event_rec_y_pos", 1);
					int yearlyDay = ParamUtil.get(
						req, "event_rec_y_day_1", Calendar.SUNDAY);
					int yearlyMonth = ParamUtil.get(
						req, "event_rec_y_month_1", Calendar.JANUARY);

					DayAndPosition[] dayPos = {
						new DayAndPosition(yearlyDay, yearlyPos)};
					recurrence.setByDay(dayPos);

					recurrence.setByMonth(new int[] {yearlyMonth});

					int yearlyInterval = ParamUtil.get(
						req, "event_rec_y_interval_1", 1);
					recurrence.setInterval(yearlyInterval);
				}
			}

			if (endDateType == 1) {
				int endDateOccurrence = ParamUtil.get(
					req, "event_ed_occurrence", 10);

				recurrence.setOccurrence(endDateOccurrence);
			}
			else if (endDateType == 2) {
				Calendar recEndCal = null;

				if (tzSensitive) {
					recEndCal = new GregorianCalendar();
					recEndCal.setTime(startCal.getTime());
				}
				else {
					recEndCal = (Calendar)startCal.clone();
				}

				recEndCal.set(Calendar.MONTH, edMonth);
				recEndCal.set(Calendar.DATE, edDay);
				recEndCal.set(Calendar.YEAR, edYear);

				recurrence.setUntil(recEndCal);
			}
		}

		if (Validator.isNull(eventId)) {

			// Add event

			CalEventServiceUtil.addEvent(
				PortalUtil.getPortletGroupId(req), title, description, sdMonth,
				sdDay, sdYear, sdHour, sdMinute, edMonth, edDay, edYear, dHour,
				dMinute, allDay, tzSensitive, type, location, street, city,
				state, zip, phone, repeating, recurrence, remindBy,
				firstReminder, secondReminder);
		}
		else {

			// Update event

			CalEventServiceUtil.updateEvent(
				eventId, PortalUtil.getPortletGroupId(req), title, description,
				sdMonth, sdDay, sdYear, sdHour, sdMinute, edMonth, edDay,
				edYear, dHour, dMinute, allDay, tzSensitive, type, location,
				street, city, state, zip, phone, repeating, recurrence,
				remindBy, firstReminder, secondReminder);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}
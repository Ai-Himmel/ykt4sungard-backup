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

package com.liferay.portlet.calendar.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.calendar.EventDurationException;
import com.liferay.portlet.calendar.EventEndDateException;
import com.liferay.portlet.calendar.EventStartDateException;
import com.liferay.portlet.calendar.EventTitleException;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.service.persistence.CalEventFinder;
import com.liferay.portlet.calendar.service.persistence.CalEventUtil;
import com.liferay.portlet.calendar.service.spring.CalEventLocalServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalEventService;
import com.liferay.portlet.calendar.util.CalUtil;
import com.liferay.util.Base64;
import com.liferay.util.ListUtil;
import com.liferay.util.Validator;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.cal.Recurrence;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TimeZone;

/**
 * <a href="CalEventServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class CalEventServiceImpl
	extends PrincipalBean implements CalEventService {

	// Business methods

	public CalEvent addEvent(
			String groupId, String title, String description, int startMonth,
			int startDay, int startYear, int startHour, int startMinute,
			int endMonth, int endDay, int endYear, int durationHour,
			int durationMinute, boolean allDay, boolean timeZoneSensitive,
			String type, String location, String street, String city,
			String state, String zip, String phone, boolean repeating,
			Recurrence recurrence, String remindBy, int firstReminder,
			int secondReminder)
		throws PortalException, SystemException {

		_validate(
			groupId, title, startMonth, startDay, startYear, endMonth, endDay,
			endYear, durationHour, durationMinute, allDay);

		User user = getUser();

		String eventId = Long.toString(CounterServiceUtil.increment(
			CalEvent.class.getName()));

		CalEvent event = CalEventUtil.create(eventId);

		Date now = new Date();

		Locale locale = null;
		TimeZone timeZone = null;

		if (timeZoneSensitive) {
			locale = user.getLocale();
			timeZone = user.getTimeZone();
		}
		else {
			locale = Locale.getDefault();
			timeZone = TimeZone.getDefault();
		}

		Calendar startCal = new GregorianCalendar(timeZone, locale);
		startCal.set(Calendar.MONTH, startMonth);
		startCal.set(Calendar.DATE, startDay);
		startCal.set(Calendar.YEAR, startYear);
		startCal.set(Calendar.HOUR_OF_DAY, startHour);
		startCal.set(Calendar.MINUTE, startMinute);
		startCal.set(Calendar.SECOND, 0);
		startCal.set(Calendar.MILLISECOND, 0);

		Calendar endCal = new GregorianCalendar(timeZone, locale);
		endCal.set(Calendar.MONTH, endMonth);
		endCal.set(Calendar.DATE, endDay);
		endCal.set(Calendar.YEAR, endYear);
		endCal.set(Calendar.HOUR_OF_DAY, 23);
		endCal.set(Calendar.MINUTE, 59);
		endCal.set(Calendar.SECOND, 59);
		endCal.set(Calendar.MILLISECOND, 999);

		if (allDay) {
			startCal.set(Calendar.HOUR_OF_DAY, 0);
			startCal.set(Calendar.MINUTE, 0);

			durationHour = 24;
			durationMinute = 0;
		}

		event.setGroupId(groupId);
		event.setCompanyId(user.getCompanyId());
		event.setUserId(user.getUserId());
		event.setUserName(user.getFullName());
		event.setCreateDate(now);
		event.setModifiedDate(now);
		event.setTitle(title);
		event.setDescription(description);
		event.setStartDate(startCal.getTime());
		event.setEndDate(endCal.getTime());
		event.setDurationHour(durationHour);
		event.setDurationMinute(durationMinute);
		event.setAllDay(allDay);
		event.setTimeZoneSensitive(timeZoneSensitive);
		event.setType(type);
		event.setLocation(location);
		event.setStreet(street);
		event.setCity(city);
		event.setState(state);
		event.setZip(zip);
		event.setPhone(phone);
		event.setRepeating(repeating);
		event.setRecurrence(Base64.objectToString(recurrence));
		event.setRemindBy(remindBy);
		event.setFirstReminder(firstReminder);
		event.setSecondReminder(secondReminder);

		CalEventUtil.update(event);

		if (event.isGroupEvent()) {
			CalEventLocalUtil.clearEventsPool(event.getGroupId());
		}
		else {
			CalEventLocalUtil.clearEventsPool(event.getUserId());
		}

		return event;
	}

	public void checkReminders() throws PortalException, SystemException {
		CalEventLocalServiceUtil.checkReminders();
	}

	public void deleteEvent(String eventId)
		throws PortalException, SystemException {

		if (!hasAdmin(eventId)) {
			throw new PrincipalException();
		}

		CalEventLocalServiceUtil.deleteEvent(eventId);
	}

	public CalEvent getEvent(String eventId)
		throws PortalException, SystemException {

		return CalEventUtil.findByPrimaryKey(eventId);
	}

	public List getEvents(String groupId)
		throws PortalException, SystemException {

		return getEvents(groupId, null);
	}

	public List getEvents(String groupId, String type)
		throws PortalException, SystemException {

		List list = null;

		if (Validator.isNull(type)) {
			list = CalEventUtil.findByG_U(groupId, getUserId());
		}
		else {
			list = CalEventUtil.findByG_U_T(groupId, getUserId(), type);
		}

		return list;
	}

	public List getEventsAfter(String groupId, Date date)
		throws PortalException, SystemException {

		return getEventsAfter(groupId, null, date);
	}

	public List getEventsAfter(String groupId, String type, Date date)
		throws PortalException, SystemException {

		List list = getEvents(groupId, type);

		CalEvent[] events = (CalEvent[])list.toArray(new CalEvent[0]);

		int limit = 0;
		boolean found = false;

		for (int i = 0; i < events.length; i++) {
			if (events[i].getStartDate().after(date)) {
				limit = i;
				found = true;

				break;
			}
		}

		if (limit > 0) {
			CalEvent[] eventsAfter = new CalEvent[events.length - limit];

			System.arraycopy(
				events, limit, eventsAfter, 0, events.length - limit);

			return ListUtil.fromArray(eventsAfter);
		}
		else if (!found) {
			return new ArrayList();
		}
		else {
			return list;
		}
	}

	public List getEventsBefore(String groupId, Date date)
		throws PortalException, SystemException {

		return getEventsBefore(groupId, null, date);
	}

	public List getEventsBefore(String groupId, String type, Date date)
		throws PortalException, SystemException {

		List list = getEvents(groupId, type);

		CalEvent[] events = (CalEvent[])list.toArray(new CalEvent[0]);

		int limit = 0;
		boolean found = false;

		for (int i = 0; i < events.length; i++) {
			if (events[i].getStartDate().after(date)) {
				limit = i;
				found = true;

				break;
			}
		}

		if (limit > 0) {
			CalEvent[] eventsBefore = new CalEvent[limit];

			System.arraycopy(events, 0, eventsBefore, 0, limit);

			return ListUtil.fromArray(eventsBefore);
		}
		else if (found) {
			return new ArrayList();
		}
		else {
			return list;
		}
	}

	public List getEventsByDay(String groupId, String companyId, Calendar cal)
		throws PortalException, SystemException {

		List events = null;

		if (groupId.equals(Group.DEFAULT_PARENT_GROUP_ID)) {
			events = getPrivateEvents(cal);
		}
		else {
			events = getPublicEvents(groupId, companyId, cal);
		}

		Collections.sort(events);

		// Guests should never see birthdays

		try {
			getUserId();
		}
		catch (PortalException pe) {
			List tempEvents = new ArrayList(events);

			Iterator itr = tempEvents.iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent)itr.next();

				if (event.getType().equals(CalEvent.BIRTHDAY)) {
					itr.remove();
				}
			}

			events = tempEvents;
		}

		return events;
	}

	public List getEventsByDay(
			String groupId, String companyId, Calendar cal, String type)
		throws PortalException, SystemException {

		List events = getEventsByDay(groupId, companyId, cal);

		if (Validator.isNull(type)) {
			return events;
		}
		else {
			events = new ArrayList(events);

			Iterator itr = events.iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent)itr.next();

				if (!event.getType().equals(type)) {
					itr.remove();
				}
			}

			return events;
		}
	}

	public List getPrivateEvents(Calendar cal)
		throws PortalException, SystemException {

		String userId = getUserId();

		Map eventsPool = CalEventLocalUtil.getEventsPool(userId);

		String key = CalUtil.toString(cal);

		List events = (List)eventsPool.get(key);

		if (events == null) {

			// Time zone sensitive

			Collection eventsCol1 = CalEventFinder.findByG_U_SD(
				Group.DEFAULT_PARENT_GROUP_ID, userId,
				CalendarUtil.getGTDate(cal), CalendarUtil.getLTDate(cal), true);

			// Time zone insensitive

			Calendar tziCal = new GregorianCalendar(
				cal.get(Calendar.YEAR),
				cal.get(Calendar.MONTH),
				cal.get(Calendar.DATE));

			Collection eventsCol2 = CalEventFinder.findByG_U_SD(
				Group.DEFAULT_PARENT_GROUP_ID, userId,
				CalendarUtil.getGTDate(tziCal), CalendarUtil.getLTDate(tziCal),
				false);

			// Create new list

			events = new ArrayList();
			events.addAll(eventsCol1);
			events.addAll(eventsCol2);

			// Add repeating events

			Iterator itr = getPrivateRepeatingEvents().iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent)itr.next();

				Recurrence recurrence = event.getRecurrenceObj();

				if (recurrence.isInRecurrence(
						_getRecurrenceCal(cal, tziCal, event))) {

					events.add(event);
				}
			}

			eventsPool.put(key, events);
		}

		return events;
	}

	public List getPrivateRepeatingEvents()
		throws PortalException, SystemException {

		String userId = getUserId();

		Map eventsPool = CalEventLocalUtil.getEventsPool(userId);

		String key = "recurrence";

		List events = (List)eventsPool.get(key);

		if (events == null) {
			events = CalEventUtil.findByG_U_R(
				Group.DEFAULT_PARENT_GROUP_ID, userId, true);

			eventsPool.put(key, events);
		}

		return events;
	}

	public List getPublicEvents(String groupId, String companyId, Calendar cal)
		throws SystemException {

		Map eventsPool = CalEventLocalUtil.getEventsPool(groupId);

		String key = CalUtil.toString(cal);

		List events = (List)eventsPool.get(key);

		if (events == null) {

			// Time zone sensitive

			Collection eventsCol1 = CalEventFinder.findByG_C_SD(
				groupId, companyId, CalendarUtil.getGTDate(cal),
				CalendarUtil.getLTDate(cal), true);

			// Time zone insensitive

			Calendar tziCal = new GregorianCalendar(
				cal.get(Calendar.YEAR),
				cal.get(Calendar.MONTH),
				cal.get(Calendar.DATE));

			Collection eventsCol2 = CalEventFinder.findByG_C_SD(
				groupId, companyId, CalendarUtil.getGTDate(tziCal),
				CalendarUtil.getLTDate(tziCal), false);

			// Create new list

			events = new ArrayList();
			events.addAll(eventsCol1);
			events.addAll(eventsCol2);

			// Add repeating events

			Iterator itr = getPublicRepeatingEvents(
				groupId, companyId).iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent)itr.next();

				Recurrence recurrence = event.getRecurrenceObj();

				if (recurrence.isInRecurrence(
						_getRecurrenceCal(cal, tziCal, event))) {

					events.add(event);
				}
			}

			eventsPool.put(key, events);
		}

		return events;
	}

	public List getPublicRepeatingEvents(String groupId, String companyId)
		throws SystemException {

		Map eventsPool = CalEventLocalUtil.getEventsPool(groupId);

		String key = "recurrence";

		List events = (List)eventsPool.get(key);

		if (events == null) {
			events = CalEventUtil.findByG_C_R(groupId, companyId, true);

			eventsPool.put(key, events);
		}

		return events;
	}

	public boolean hasEvents(
			String groupId, String companyId, Calendar cal)
		throws PortalException, SystemException {

		return hasEvents(groupId, companyId, cal, null);
	}

	public boolean hasEvents(
			String groupId, String companyId, Calendar cal, String type)
		throws PortalException, SystemException {

		if (getEventsByDay(groupId, companyId, cal, type).size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public CalEvent updateEvent(
			String eventId, String groupId, String title, String description,
			int startMonth, int startDay, int startYear, int startHour,
			int startMinute, int endMonth, int endDay, int endYear,
			int durationHour, int durationMinute, boolean allDay,
			boolean timeZoneSensitive, String type, String location,
			String street, String city, String state, String zip, String phone,
			boolean repeating, Recurrence recurrence, String remindBy,
			int firstReminder, int secondReminder)
		throws PortalException, SystemException {

		_validate(
			groupId, title, startMonth, startDay, startYear, endMonth, endDay,
			endYear, durationHour, durationMinute, allDay);

		if (!hasAdmin(eventId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		CalEvent event = CalEventUtil.findByPrimaryKey(eventId);

		Locale locale = null;
		TimeZone timeZone = null;

		if (timeZoneSensitive) {
			locale = user.getLocale();
			timeZone = user.getTimeZone();
		}
		else {
			locale = Locale.getDefault();
			timeZone = TimeZone.getDefault();
		}

		Calendar startCal = new GregorianCalendar(timeZone, locale);
		startCal.set(Calendar.MONTH, startMonth);
		startCal.set(Calendar.DATE, startDay);
		startCal.set(Calendar.YEAR, startYear);
		startCal.set(Calendar.HOUR_OF_DAY, startHour);
		startCal.set(Calendar.MINUTE, startMinute);
		startCal.set(Calendar.SECOND, 0);
		startCal.set(Calendar.MILLISECOND, 0);

		Calendar endCal = new GregorianCalendar(timeZone, locale);
		endCal.set(Calendar.MONTH, endMonth);
		endCal.set(Calendar.DATE, endDay);
		endCal.set(Calendar.YEAR, endYear);
		endCal.set(Calendar.HOUR_OF_DAY, 23);
		endCal.set(Calendar.MINUTE, 59);
		endCal.set(Calendar.SECOND, 59);
		endCal.set(Calendar.MILLISECOND, 999);

		if (allDay) {
			startCal.set(Calendar.HOUR_OF_DAY, 0);
			startCal.set(Calendar.MINUTE, 0);

			durationHour = 24;
			durationMinute = 0;
		}

		event.setModifiedDate(new Date());
		event.setTitle(title);
		event.setDescription(description);
		event.setStartDate(startCal.getTime());
		event.setEndDate(endCal.getTime());
		event.setDurationHour(durationHour);
		event.setDurationMinute(durationMinute);
		event.setAllDay(allDay);
		event.setTimeZoneSensitive(timeZoneSensitive);
		event.setType(type);
		event.setLocation(location);
		event.setStreet(street);
		event.setCity(city);
		event.setState(state);
		event.setZip(zip);
		event.setPhone(phone);
		event.setRepeating(repeating);
		event.setRecurrence(Base64.objectToString(recurrence));
		event.setRemindBy(remindBy);
		event.setFirstReminder(firstReminder);
		event.setSecondReminder(secondReminder);

		CalEventUtil.update(event);

		if (event.isGroupEvent()) {
			CalEventLocalUtil.clearEventsPool(event.getGroupId());
		}
		else {
			CalEventLocalUtil.clearEventsPool(event.getUserId());
		}

		return event;
	}

	// Permission methods

	public boolean hasAdmin() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.CALENDAR_ADMIN)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasAdmin(String eventId)
		throws PortalException, SystemException {

		CalEvent event = CalEventUtil.findByPrimaryKey(eventId);

		if (!event.isGroupEvent()) {
			if (event.getUserId().equals(getUserId())) {
				return true;
			}
		}
		else {
			if (getUser().getCompanyId().equals(event.getCompanyId()) &&
				RoleServiceUtil.hasRole(getUserId(), Role.CALENDAR_ADMIN)) {

				return true;
			}
		}

		return false;
	}

	// Private methods

	private Calendar _getRecurrenceCal(
		Calendar cal, Calendar tziCal, CalEvent event) {

		Calendar eventCal = new GregorianCalendar();
		eventCal.setTime(event.getStartDate());

		Calendar recurrenceCal = (Calendar)tziCal.clone();
		recurrenceCal.set(
			Calendar.HOUR_OF_DAY, eventCal.get(Calendar.HOUR_OF_DAY));
		recurrenceCal.set(
			Calendar.MINUTE, eventCal.get(Calendar.MINUTE));
		recurrenceCal.set(Calendar.SECOND, 0);
		recurrenceCal.set(Calendar.MILLISECOND, 0);

		/*if (event.isTimeZoneSensitive()) {
			int gmtDate = eventCal.get(Calendar.DATE);
			long gmtMills = eventCal.getTimeInMillis();

			eventCal.setTimeZone(cal.getTimeZone());

			int tziDate = eventCal.get(Calendar.DATE);
			long tziMills = Time.getDate(eventCal).getTime();

			if (gmtDate != tziDate) {
				int diffDate = 0;

				if (gmtMills > tziMills) {
					diffDate = (int)Math.ceil(
						(double)(gmtMills - tziMills) / Time.DAY);
				}
				else {
					diffDate = (int)Math.floor(
						(double)(gmtMills - tziMills) / Time.DAY);
				}

				recurrenceCal.add(Calendar.DATE, diffDate);
			}
		}*/

		return recurrenceCal;
	}

	private void _validate(
			String groupId, String title, int startMonth, int startDay,
			int startYear, int endMonth, int endDay, int endYear,
			int durationHour, int durationMinute, boolean allDay)
		throws PortalException, SystemException {

		if (Validator.isNull(title)) {
			throw new EventTitleException();
		}
		else if (!Validator.isDate(startMonth, startDay, startYear)) {
			throw new EventStartDateException();
		}
		else if (!Validator.isDate(endMonth, endDay, endYear)) {
			throw new EventEndDateException();
		}

		if (!allDay && durationHour <= 0 && durationMinute <= 0) {
			throw new EventDurationException();
		}

		Calendar startCal = new GregorianCalendar(
			startYear, startMonth, startDay);
		Calendar endCal = new GregorianCalendar(endYear, endMonth, endDay);

		if (startCal.after(endCal)) {
			throw new EventEndDateException();
		}

		if ((!groupId.equals(Group.DEFAULT_PARENT_GROUP_ID)) &&
			(!RoleServiceUtil.hasRole(getUserId(), Role.CALENDAR_ADMIN))) {

			throw new PrincipalException();
		}
	}

}
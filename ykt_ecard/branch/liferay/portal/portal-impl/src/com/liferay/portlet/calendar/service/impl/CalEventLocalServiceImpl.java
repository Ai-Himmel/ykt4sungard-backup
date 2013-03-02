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

package com.liferay.portlet.calendar.service.impl;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.im.AIMConnector;
import com.liferay.portal.im.ICQConnector;
import com.liferay.portal.im.MSNConnector;
import com.liferay.portal.im.YMConnector;
import com.liferay.portal.kernel.cal.DayAndPosition;
import com.liferay.portal.kernel.cal.Recurrence;
import com.liferay.portal.kernel.mail.MailMessage;
import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.ReleaseInfo;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.TimeZoneUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.uuid.PortalUUIDUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.util.DateFormats;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.calendar.EventDurationException;
import com.liferay.portlet.calendar.EventEndDateException;
import com.liferay.portlet.calendar.EventStartDateException;
import com.liferay.portlet.calendar.EventTitleException;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.model.impl.CalEventImpl;
import com.liferay.portlet.calendar.service.base.CalEventLocalServiceBaseImpl;
import com.liferay.portlet.calendar.util.CalUtil;
import com.liferay.util.Time;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStream;

import java.text.DateFormat;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collection;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TimeZone;

import javax.mail.internet.InternetAddress;

import javax.portlet.PortletPreferences;

import net.fortuna.ical4j.data.CalendarBuilder;
import net.fortuna.ical4j.data.CalendarOutputter;
import net.fortuna.ical4j.data.ParserException;
import net.fortuna.ical4j.model.Component;
import net.fortuna.ical4j.model.DateTime;
import net.fortuna.ical4j.model.Parameter;
import net.fortuna.ical4j.model.Property;
import net.fortuna.ical4j.model.PropertyList;
import net.fortuna.ical4j.model.Recur;
import net.fortuna.ical4j.model.WeekDay;
import net.fortuna.ical4j.model.component.VEvent;
import net.fortuna.ical4j.model.component.VTimeZone;
import net.fortuna.ical4j.model.property.CalScale;
import net.fortuna.ical4j.model.property.Comment;
import net.fortuna.ical4j.model.property.Description;
import net.fortuna.ical4j.model.property.DtStart;
import net.fortuna.ical4j.model.property.Duration;
import net.fortuna.ical4j.model.property.ProdId;
import net.fortuna.ical4j.model.property.RRule;
import net.fortuna.ical4j.model.property.Summary;
import net.fortuna.ical4j.model.property.Uid;
import net.fortuna.ical4j.model.property.Version;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CalEventLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Bruno Farache
 *
 */
public class CalEventLocalServiceImpl extends CalEventLocalServiceBaseImpl {

	public CalEvent addEvent(
			long userId, long plid, String title, String description,
			int startDateMonth, int startDateDay, int startDateYear,
			int startDateHour, int startDateMinute, int endDateMonth,
			int endDateDay, int endDateYear, int durationHour,
			int durationMinute, boolean allDay, boolean timeZoneSensitive,
			String type, boolean repeating, Recurrence recurrence,
			String remindBy, int firstReminder, int secondReminder,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addEvent(
			null, userId, plid, title, description, startDateMonth,
			startDateDay, startDateYear, startDateHour, startDateMinute,
			endDateMonth, endDateDay, endDateYear, durationHour, durationMinute,
			allDay, timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public CalEvent addEvent(
			String uuid, long userId, long plid, String title,
			String description, int startDateMonth, int startDateDay,
			int startDateYear, int startDateHour, int startDateMinute,
			int endDateMonth, int endDateDay, int endDateYear, int durationHour,
			int durationMinute, boolean allDay, boolean timeZoneSensitive,
			String type, boolean repeating, Recurrence recurrence,
			String remindBy, int firstReminder, int secondReminder,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addEvent(
			uuid, userId, plid, title, description, startDateMonth,
			startDateDay, startDateYear, startDateHour, startDateMinute,
			endDateMonth, endDateDay, endDateYear, durationHour, durationMinute,
			allDay, timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder, new Boolean(addCommunityPermissions),
			new Boolean(addGuestPermissions), null, null);
	}

	public CalEvent addEvent(
			long userId, long plid, String title, String description,
			int startDateMonth, int startDateDay, int startDateYear,
			int startDateHour, int startDateMinute, int endDateMonth,
			int endDateDay, int endDateYear, int durationHour,
			int durationMinute, boolean allDay, boolean timeZoneSensitive,
			String type, boolean repeating, Recurrence recurrence,
			String remindBy, int firstReminder, int secondReminder,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		return addEvent(
			null, userId, plid, title, description, startDateMonth,
			startDateDay, startDateYear, startDateHour, startDateMinute,
			endDateMonth, endDateDay, endDateYear, durationHour, durationMinute,
			allDay, timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder, null, null, communityPermissions,
			guestPermissions);
	}

	public CalEvent addEvent(
			String uuid, long userId, long plid, String title,
			String description, int startDateMonth, int startDateDay,
			int startDateYear, int startDateHour, int startDateMinute,
			int endDateMonth, int endDateDay, int endDateYear, int durationHour,
			int durationMinute, boolean allDay, boolean timeZoneSensitive,
			String type, boolean repeating, Recurrence recurrence,
			String remindBy, int firstReminder, int secondReminder,
			Boolean addCommunityPermissions, Boolean addGuestPermissions,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		// Event

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);
		Date now = new Date();

		Locale locale = null;
		TimeZone timeZone = null;

		if (timeZoneSensitive) {
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

		Calendar endDate = CalendarFactoryUtil.getCalendar(timeZone, locale);

		endDate.set(Calendar.MONTH, endDateMonth);
		endDate.set(Calendar.DATE, endDateDay);
		endDate.set(Calendar.YEAR, endDateYear);
		endDate.set(Calendar.HOUR_OF_DAY, 23);
		endDate.set(Calendar.MINUTE, 59);
		endDate.set(Calendar.SECOND, 59);
		endDate.set(Calendar.MILLISECOND, 999);

		if (allDay) {
			startDate.set(Calendar.HOUR_OF_DAY, 0);
			startDate.set(Calendar.MINUTE, 0);

			durationHour = 24;
			durationMinute = 0;
		}

		validate(
			title, startDateMonth, startDateDay, startDateYear, endDateMonth,
			endDateDay, endDateYear, durationHour, durationMinute, allDay);

		long eventId = counterLocalService.increment();

		CalEvent event = calEventPersistence.create(eventId);

		event.setUuid(uuid);
		event.setGroupId(groupId);
		event.setCompanyId(user.getCompanyId());
		event.setUserId(user.getUserId());
		event.setUserName(user.getFullName());
		event.setCreateDate(now);
		event.setModifiedDate(now);
		event.setTitle(title);
		event.setDescription(description);
		event.setStartDate(startDate.getTime());
		event.setEndDate(endDate.getTime());
		event.setDurationHour(durationHour);
		event.setDurationMinute(durationMinute);
		event.setAllDay(allDay);
		event.setTimeZoneSensitive(timeZoneSensitive);
		event.setType(type);
		event.setRepeating(repeating);
		event.setRecurrence(Base64.objectToString(recurrence));
		event.setRemindBy(remindBy);
		event.setFirstReminder(firstReminder);
		event.setSecondReminder(secondReminder);

		calEventPersistence.update(event);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addEventResources(
				event, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addEventResources(event, communityPermissions, guestPermissions);
		}

		// Pool

		CalEventLocalUtil.clearEventsPool(event.getGroupId());

		return event;
	}

	public void addEventResources(
			long eventId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		CalEvent event = calEventPersistence.findByPrimaryKey(eventId);

		addEventResources(
			event, addCommunityPermissions, addGuestPermissions);
	}

	public void addEventResources(
			CalEvent event, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			event.getCompanyId(), event.getGroupId(), event.getUserId(),
			CalEvent.class.getName(), event.getEventId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addEventResources(
			long eventId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		CalEvent event = calEventPersistence.findByPrimaryKey(eventId);

		addEventResources(event, communityPermissions, guestPermissions);
	}

	public void addEventResources(
			CalEvent event, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			event.getCompanyId(), event.getGroupId(), event.getUserId(),
			CalEvent.class.getName(), event.getEventId(), communityPermissions,
			guestPermissions);
	}

	public void checkEvents() throws PortalException, SystemException {
		Iterator itr = calEventFinder.findByRemindBy().iterator();

		while (itr.hasNext()) {
			CalEvent event = (CalEvent)itr.next();

			User user = userPersistence.findByPrimaryKey(event.getUserId());

			Calendar now = CalendarFactoryUtil.getCalendar(
				user.getTimeZone(), user.getLocale());

			if (!event.isTimeZoneSensitive()) {
				Calendar temp = CalendarFactoryUtil.getCalendar();

				temp.setTime(Time.getDate(now));

				now = temp;
			}

			Calendar startDate = null;

			if (event.isTimeZoneSensitive()) {
				startDate = CalendarFactoryUtil.getCalendar(
					user.getTimeZone(), user.getLocale());
			}
			else {
				startDate = CalendarFactoryUtil.getCalendar();
			}

			startDate.setTime(event.getStartDate());

			long diff =
				(startDate.getTime().getTime() - now.getTime().getTime()) /
				Time.MINUTE;

			if ((diff == (event.getFirstReminder() / Time.MINUTE)) ||
				(diff == (event.getSecondReminder() / Time.MINUTE))) {

				remindUser(event, user);
			}
		}
	}

	public void deleteEvent(long eventId)
		throws PortalException, SystemException {

		CalEvent event = calEventPersistence.findByPrimaryKey(eventId);

		deleteEvent(event);
	}

	public void deleteEvent(CalEvent event)
		throws PortalException, SystemException {

		// Pool

		CalEventLocalUtil.clearEventsPool(event.getGroupId());

		// Resources

		resourceLocalService.deleteResource(
			event.getCompanyId(), CalEvent.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, event.getEventId());

		// Event

		calEventPersistence.remove(event.getEventId());
	}

	public void deleteEvents(long groupId)
		throws PortalException, SystemException {

		Iterator itr = calEventPersistence.findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			CalEvent event = (CalEvent)itr.next();

			deleteEvent(event);
		}
	}

	public File exportEvent(long userId, long eventId)
		throws PortalException, SystemException {

		List events = new ArrayList();

		CalEvent event = calEventPersistence.findByPrimaryKey(eventId);

		events.add(event);

		return exportICal4j(toICalCalendar(userId, events), null);
	}

	public File exportGroupEvents(long userId, long plid, String fileName)
		throws PortalException, SystemException {

		long groupId = PortalUtil.getPortletGroupId(plid);

		List events = calEventPersistence.findByGroupId(groupId);

		return exportICal4j(toICalCalendar(userId, events), fileName);
	}

	public CalEvent getEvent(long eventId)
		throws PortalException, SystemException {

		return calEventPersistence.findByPrimaryKey(eventId);
	}

	public List getEvents(long groupId, String type, int begin, int end)
		throws SystemException {

		if (Validator.isNull(type)) {
			return calEventPersistence.findByGroupId(groupId, begin, end);
		}
		else {
			return calEventPersistence.findByG_T(groupId, type, begin, end);
		}
	}

	public List getEvents(long groupId, Calendar cal) throws SystemException {
		Map eventsPool = CalEventLocalUtil.getEventsPool(groupId);

		String key = CalUtil.toString(cal);

		List events = (List)eventsPool.get(key);

		if (events == null) {

			// Time zone sensitive

			Collection eventsCol1 = calEventFinder.findByG_SD(
				groupId, CalendarUtil.getGTDate(cal),
				CalendarUtil.getLTDate(cal), true);

			// Time zone insensitive

			Calendar tzICal = CalendarFactoryUtil.getCalendar(
				cal.get(Calendar.YEAR),
				cal.get(Calendar.MONTH),
				cal.get(Calendar.DATE));

			Collection eventsCol2 = calEventFinder.findByG_SD(
				groupId, CalendarUtil.getGTDate(tzICal),
				CalendarUtil.getLTDate(tzICal), false);

			// Create new list

			events = new ArrayList();
			events.addAll(eventsCol1);
			events.addAll(eventsCol2);

			// Add repeating events

			Iterator itr = getRepeatingEvents(groupId).iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent)itr.next();

				Recurrence recurrence = event.getRecurrenceObj();

				try {

					// LEP-3468

					if ((recurrence.getFrequency() == Recurrence.DAILY) &&
						(recurrence.getInterval() <= 0)) {

						recurrence.setInterval(1);

						event.setRecurrence(Base64.objectToString(recurrence));

						event = calEventPersistence.update(event);

						recurrence = event.getRecurrenceObj();
					}

					if (recurrence.isInRecurrence(
							getRecurrenceCal(cal, tzICal, event))) {

						events.add(event);
					}
				}
				catch (Exception e) {
					_log.error(e.getMessage());
				}
			}

			eventsPool.put(key, events);
		}

		return events;
	}

	public List getEvents(long groupId, Calendar cal, String type)
		throws SystemException {

		List events = getEvents(groupId, cal);

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

	public int getEventsCount(long groupId, String type)
		throws SystemException {

		if (Validator.isNull(type)) {
			return calEventPersistence.countByGroupId(groupId);
		}
		else {
			return calEventPersistence.countByG_T(groupId, type);
		}
	}

	public List getRepeatingEvents(long groupId) throws SystemException {
		Map eventsPool = CalEventLocalUtil.getEventsPool(groupId);

		String key = "recurrence";

		List events = (List)eventsPool.get(key);

		if (events == null) {
			events = calEventPersistence.findByG_R(groupId, true);

			eventsPool.put(key, events);
		}

		return events;
	}

	public boolean hasEvents(long groupId, Calendar cal)
		throws SystemException {

		return hasEvents(groupId, cal, null);
	}

	public boolean hasEvents(long groupId, Calendar cal, String type)
		throws SystemException {

		if (getEvents(groupId, cal, type).size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void importICal4j(long userId, long plid, File file)
		throws PortalException, SystemException {

		try {
			CalendarBuilder builder = new CalendarBuilder();

			net.fortuna.ical4j.model.Calendar calendar = builder.build(
				new FileReader(file));

			TimeZone timeZone = toTimeZone(
				userId, (VTimeZone)calendar.getComponent(Component.VTIMEZONE));

			Iterator itr = calendar.getComponents(Component.VEVENT).iterator();

			while (itr.hasNext()) {
				VEvent vEvent = (VEvent)itr.next();

				importICal4j(userId, plid, vEvent, timeZone);
			}
		}
		catch (IOException ioe) {
			throw new SystemException(ioe.getMessage());
		}
		catch (ParserException pe) {
			throw new SystemException(pe.getMessage());
		}
	}

	public CalEvent updateEvent(
			long userId, long eventId, String title, String description,
			int startDateMonth, int startDateDay, int startDateYear,
			int startDateHour, int startDateMinute, int endDateMonth,
			int endDateDay, int endDateYear, int durationHour,
			int durationMinute, boolean allDay, boolean timeZoneSensitive,
			String type, boolean repeating, Recurrence recurrence,
			String remindBy, int firstReminder, int secondReminder)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		Locale locale = null;
		TimeZone timeZone = null;

		if (timeZoneSensitive) {
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

		Calendar endDate = CalendarFactoryUtil.getCalendar(timeZone, locale);

		endDate.set(Calendar.MONTH, endDateMonth);
		endDate.set(Calendar.DATE, endDateDay);
		endDate.set(Calendar.YEAR, endDateYear);
		endDate.set(Calendar.HOUR_OF_DAY, 23);
		endDate.set(Calendar.MINUTE, 59);
		endDate.set(Calendar.SECOND, 59);
		endDate.set(Calendar.MILLISECOND, 999);

		if (allDay) {
			startDate.set(Calendar.HOUR_OF_DAY, 0);
			startDate.set(Calendar.MINUTE, 0);

			durationHour = 24;
			durationMinute = 0;
		}

		validate(
			title, startDateMonth, startDateDay, startDateYear, endDateMonth,
			endDateDay, endDateYear, durationHour, durationMinute, allDay);

		CalEvent event = calEventPersistence.findByPrimaryKey(eventId);

		event.setModifiedDate(new Date());
		event.setTitle(title);
		event.setDescription(description);
		event.setStartDate(startDate.getTime());
		event.setEndDate(endDate.getTime());
		event.setDurationHour(durationHour);
		event.setDurationMinute(durationMinute);
		event.setAllDay(allDay);
		event.setTimeZoneSensitive(timeZoneSensitive);
		event.setType(type);
		event.setRepeating(repeating);
		event.setRecurrence(Base64.objectToString(recurrence));
		event.setRemindBy(remindBy);
		event.setFirstReminder(firstReminder);
		event.setSecondReminder(secondReminder);

		calEventPersistence.update(event);

		CalEventLocalUtil.clearEventsPool(event.getGroupId());

		return event;
	}

	protected File exportICal4j(
			net.fortuna.ical4j.model.Calendar cal, String fileName)
		throws SystemException {

		OutputStream os = null;

		try {
			String extension = ".ics";

			if (Validator.isNull(fileName)) {
				fileName = "liferay.";
			}
			else {
				int pos = fileName.lastIndexOf(StringPool.PERIOD);

				if (pos != -1) {
					extension = fileName.substring(pos);
					fileName = fileName.substring(0, pos);
				}
			}

			File file = File.createTempFile(fileName, extension);

			os = new BufferedOutputStream(new FileOutputStream(file.getPath()));

			CalendarOutputter calOutput = new CalendarOutputter();

			calOutput.output(cal, os);

			return file;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new SystemException(e);
		}
		finally {
			ServletResponseUtil.cleanUp(os);
		}
	}

	protected Calendar getRecurrenceCal(
		Calendar cal, Calendar tzICal, CalEvent event) {

		Calendar eventCal = CalendarFactoryUtil.getCalendar();
		eventCal.setTime(event.getStartDate());

		Calendar recurrenceCal = (Calendar)tzICal.clone();
		recurrenceCal.set(
			Calendar.HOUR_OF_DAY, eventCal.get(Calendar.HOUR_OF_DAY));
		recurrenceCal.set(
			Calendar.MINUTE, eventCal.get(Calendar.MINUTE));
		recurrenceCal.set(Calendar.SECOND, 0);
		recurrenceCal.set(Calendar.MILLISECOND, 0);

		if (event.isTimeZoneSensitive()) {
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
		}

		return recurrenceCal;
	}

	protected void importICal4j(
			long userId, long plid, VEvent event, TimeZone timeZone)
		throws PortalException, SystemException {

		String title = StringPool.BLANK;

		if (event.getSummary() != null) {
			title = event.getSummary().getValue();
		}

		String description = StringPool.BLANK;

		if (event.getDescription() != null) {
			description = event.getDescription().getValue();
		}

		Calendar startDate = Calendar.getInstance(timeZone);

		startDate.setTime(event.getStartDate().getDate());

		Calendar endDate = Calendar.getInstance(timeZone);

		endDate.setTime(event.getEndDate().getDate());

		long diffMillis =
			endDate.getTimeInMillis() - startDate.getTimeInMillis();
		long durationHours = diffMillis / (60 * 60 * 1000);
		long durationMins =
			(diffMillis / (60 * 1000)) - (durationHours * 60);
		boolean allDay = false;

		if (event.getProperty(Property.DTSTART).getParameter(
				Parameter.TZID) == null){

			Calendar startDateWithoutTimeZone = Calendar.getInstance();

			startDateWithoutTimeZone.setTime(
				event.getStartDate().getDate());

			startDate.set(
				Calendar.DAY_OF_MONTH,
				startDateWithoutTimeZone.get(Calendar.DAY_OF_MONTH));
			startDate.set(Calendar.HOUR_OF_DAY, 0);
			startDate.set(Calendar.MINUTE, 0);
			startDate.set(Calendar.SECOND, 0);
			startDate.set(Calendar.MILLISECOND, 0);

			durationHours = 24;
			durationMins = 0;
			allDay = true;
		}

		boolean timeZoneSensitive = false;
		String type = StringPool.BLANK;
		boolean repeating = false;
		Recurrence recurrence = null;

		RRule rrule = (RRule)event.getProperty(Property.RRULE);

		if (rrule != null) {
			repeating = true;
			recurrence = toRecurrence(
				rrule.getRecur(), timeZone, startDate);

			if (recurrence.getUntil() != null) {
				endDate = recurrence.getUntil();
			}
		}

		String remindBy = "none";
		int firstReminder = 300000;
		int secondReminder = 300000;

		boolean addCommunityPermissions = false;
		boolean addGuestPermissions = false;

		addEvent(
			userId, plid, title, description, startDate.get(Calendar.MONTH),
			startDate.get(Calendar.DAY_OF_MONTH),
			startDate.get(Calendar.YEAR),
			startDate.get(Calendar.HOUR_OF_DAY),
			startDate.get(Calendar.MINUTE), endDate.get(Calendar.MONTH),
			endDate.get(Calendar.DAY_OF_MONTH), endDate.get(Calendar.YEAR),
			(int)durationHours, (int)durationMins, allDay,
			timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder, addCommunityPermissions,
			addGuestPermissions);

	}

	protected void remindUser(CalEvent event, User user) {
		String remindBy = event.getRemindBy();

		if (remindBy.equals(CalEventImpl.REMIND_BY_NONE)) {
			return;
		}

		try {
			long ownerId = event.getGroupId();
			int ownerType = PortletKeys.PREFS_OWNER_TYPE_GROUP;
			long plid = PortletKeys.PREFS_PLID_SHARED;
			String portletId = PortletKeys.CALENDAR;

			PortletPreferences prefs =
				portletPreferencesLocalService.getPreferences(
					event.getCompanyId(), ownerId, ownerType, plid, portletId);

			Company company = companyPersistence.findByPrimaryKey(
				user.getCompanyId());

			Contact contact = user.getContact();

			String portletName = PortalUtil.getPortletTitle(
				PortletKeys.CALENDAR, user);

			String fromName = CalUtil.getEmailFromName(prefs);
			String fromAddress = CalUtil.getEmailFromAddress(prefs);

			String toName = user.getFullName();
			String toAddress = user.getEmailAddress();

			if (remindBy.equals(CalEventImpl.REMIND_BY_SMS)) {
				toAddress = contact.getSmsSn();
			}

			String subject = CalUtil.getEmailEventReminderSubject(prefs);
			String body = CalUtil.getEmailEventReminderBody(prefs);

			DateFormat dateFormatDateTime = DateFormats.getDateTime(
				user.getLocale(), user.getTimeZone());

			subject = StringUtil.replace(
				subject,
				new String[] {
					"[$EVENT_START_DATE$]",
					"[$EVENT_TITLE$]",
					"[$FROM_ADDRESS$]",
					"[$FROM_NAME$]",
					"[$PORTAL_URL$]",
					"[$PORTLET_NAME$]",
					"[$TO_ADDRESS$]",
					"[$TO_NAME$]"
				},
				new String[] {
					dateFormatDateTime.format(event.getStartDate()),
					event.getTitle(),
					fromAddress,
					fromName,
					company.getVirtualHost(),
					portletName,
					toAddress,
					toName,
				});

			body = StringUtil.replace(
				body,
				new String[] {
					"[$EVENT_START_DATE$]",
					"[$EVENT_TITLE$]",
					"[$FROM_ADDRESS$]",
					"[$FROM_NAME$]",
					"[$PORTAL_URL$]",
					"[$PORTLET_NAME$]",
					"[$TO_ADDRESS$]",
					"[$TO_NAME$]"
				},
				new String[] {
					dateFormatDateTime.format(event.getStartDate()),
					event.getTitle(),
					fromAddress,
					fromName,
					company.getVirtualHost(),
					portletName,
					toAddress,
					toName,
				});

			if (remindBy.equals(CalEventImpl.REMIND_BY_EMAIL) ||
				remindBy.equals(CalEventImpl.REMIND_BY_SMS)) {

				InternetAddress from = new InternetAddress(
					fromAddress, fromName);

				InternetAddress to = new InternetAddress(toAddress, toName);

				MailMessage message = new MailMessage(
					from, to, subject, body, true);

				mailService.sendEmail(message);
			}
			else if (remindBy.equals(CalEventImpl.REMIND_BY_AIM) &&
					 Validator.isNotNull(contact.getAimSn())) {

				AIMConnector.send(contact.getAimSn(), body);
			}
			else if (remindBy.equals(CalEventImpl.REMIND_BY_ICQ) &&
					 Validator.isNotNull(contact.getIcqSn())) {

				ICQConnector.send(contact.getIcqSn(), body);
			}
			else if (remindBy.equals(CalEventImpl.REMIND_BY_MSN) &&
					 Validator.isNotNull(contact.getMsnSn())) {

				MSNConnector.send(contact.getMsnSn(), body);
			}
			else if (remindBy.equals(CalEventImpl.REMIND_BY_YM) &&
					 Validator.isNotNull(contact.getYmSn())) {

				YMConnector.send(contact.getYmSn(), body);
			}
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	protected int toCalendarWeekDay(WeekDay weekDay) {
		int dayOfWeeek = 0;

		if (weekDay.getDay().equals(WeekDay.SU.getDay())) {
			dayOfWeeek = Calendar.SUNDAY;
		}
		else if (weekDay.getDay().equals(WeekDay.MO.getDay())) {
			dayOfWeeek = Calendar.MONDAY;
		}
		else if (weekDay.getDay().equals(WeekDay.TU.getDay())) {
			dayOfWeeek = Calendar.TUESDAY;
		}
		else if (weekDay.getDay().equals(WeekDay.WE.getDay())) {
			dayOfWeeek = Calendar.WEDNESDAY;
		}
		else if (weekDay.getDay().equals(WeekDay.TH.getDay())) {
			dayOfWeeek = Calendar.THURSDAY;
		}
		else if (weekDay.getDay().equals(WeekDay.FR.getDay())) {
			dayOfWeeek = Calendar.FRIDAY;
		}
		else if (weekDay.getDay().equals(WeekDay.SA.getDay())) {
			dayOfWeeek = Calendar.SATURDAY;
		}

		return dayOfWeeek;
	}

	protected net.fortuna.ical4j.model.Calendar toICalCalendar(
		long userId, List events)
		throws PortalException, SystemException {

		net.fortuna.ical4j.model.Calendar iCal =
			new net.fortuna.ical4j.model.Calendar();

		ProdId prodId = new ProdId(
			"-//Liferay Inc//Liferay Portal " + ReleaseInfo.getVersion() +
			"//EN");

		PropertyList props = iCal.getProperties();

		props.add(prodId);
		props.add(Version.VERSION_2_0);
		props.add(CalScale.GREGORIAN);

		User user = userPersistence.findByPrimaryKey(userId);
		TimeZone timeZone = user.getTimeZone();

		List components = iCal.getComponents();

		Iterator itr = events.iterator();

		while (itr.hasNext()) {
			CalEvent event = (CalEvent)itr.next();

			components.add(toICalVEvent(event, timeZone));
		}

		return iCal;
	}

	protected Recur toICalRecurrence(Recurrence recurrence) {
		Recur recur = null;

		int recurrenceType = recurrence.getFrequency();

		int interval = recurrence.getInterval();

		if (recurrenceType == Recurrence.DAILY) {
			recur = new Recur(Recur.DAILY, -1);

			if (interval >= 1) {
				recur.setInterval(interval);
			}

			DayAndPosition[] byDay = recurrence.getByDay();

			if (byDay != null) {
				for (int i = 0; i < byDay.length; i++) {
					WeekDay weekDay = toICalWeekDay(byDay[i].getDayOfWeek());

					recur.getDayList().add(weekDay);
				}
			}

		}
		else if (recurrenceType == Recurrence.WEEKLY) {
			recur = new Recur(Recur.WEEKLY, -1);

			recur.setInterval(interval);

			DayAndPosition[] byDay = recurrence.getByDay();

			if (byDay != null) {
				for (int i = 0; i < byDay.length; i++) {
					WeekDay weekDay = toICalWeekDay(byDay[i].getDayOfWeek());

					recur.getDayList().add(weekDay);
				}
			}
		}
		else if (recurrenceType == Recurrence.MONTHLY) {
			recur = new Recur(Recur.MONTHLY, -1);

			recur.setInterval(interval);

			int[] byMonthDay = recurrence.getByMonthDay();

			if (byMonthDay != null) {
				Integer monthDay = new Integer(byMonthDay[0]);

				recur.getMonthDayList().add(monthDay);
			}
			else if (recurrence.getByDay() != null){
				DayAndPosition[] byDay = recurrence.getByDay();

				WeekDay weekDay = toICalWeekDay(byDay[0].getDayOfWeek());

				recur.getDayList().add(weekDay);

				Integer position = new Integer(byDay[0].getDayPosition());

				recur.getSetPosList().add(position);
			}
		}
		else if (recurrenceType == Recurrence.YEARLY) {
			recur = new Recur(Recur.YEARLY, -1);

			recur.setInterval(interval);
		}

		Calendar until = recurrence.getUntil();

		if (until != null) {
			DateTime dateTime = new DateTime(until.getTime());

			recur.setUntil(dateTime);
		}

		return recur;
	}

	protected VEvent toICalVEvent(CalEvent event, TimeZone timeZone){
		VEvent vEvent = new VEvent();

		PropertyList eventProps = vEvent.getProperties();

		// UID

		Uid uid = new Uid(PortalUUIDUtil.generate());

		eventProps.add(uid);

		DtStart dtStart = new DtStart(new DateTime(event.getStartDate()));

		eventProps.add(dtStart);

		// Duration

		Calendar cal = Calendar.getInstance();

		Date start = cal.getTime();

		cal.add(Calendar.HOUR, event.getDurationHour());
		cal.add(Calendar.MINUTE, event.getDurationHour());

		Date end = cal.getTime();

		Duration duration = new Duration(start, end);

		eventProps.add(duration);

		// Summary

		Summary summary = new Summary(event.getTitle());

		eventProps.add(summary);

		// Description

		Description description = new Description(event.getDescription());

		eventProps.add(description);

		// Comment

		Comment comment = new Comment(event.getType());

		eventProps.add(comment);

		// Recurrence rule

		if (event.isRepeating()) {
			Recur recur = toICalRecurrence(event.getRecurrenceObj());

			RRule rRule = new RRule(recur);

			eventProps.add(rRule);
		}

		return vEvent;
	}

	protected WeekDay toICalWeekDay(int dayOfWeek) {
		WeekDay weekDay = null;

		if (dayOfWeek == Calendar.SUNDAY) {
			weekDay = WeekDay.SU;
		}
		else if (dayOfWeek == Calendar.MONDAY) {
			weekDay = WeekDay.MO;
		}
		else if (dayOfWeek == Calendar.TUESDAY) {
			weekDay = WeekDay.TU;
		}
		else if (dayOfWeek == Calendar.WEDNESDAY) {
			weekDay = WeekDay.WE;
		}
		else if (dayOfWeek == Calendar.THURSDAY) {
			weekDay = WeekDay.TH;
		}
		else if (dayOfWeek == Calendar.FRIDAY) {
			weekDay = WeekDay.FR;
		}
		else if (dayOfWeek == Calendar.SATURDAY) {
			weekDay = WeekDay.SA;
		}

		return weekDay;
	}

	protected TimeZone toTimeZone(long userId, VTimeZone vTimeZone)
		throws SystemException, NoSuchUserException {

		User user = userPersistence.findByPrimaryKey(userId);

		TimeZone timeZone = user.getTimeZone();

		timeZone = TimeZone.getTimeZone(
			vTimeZone.getTimeZoneId().getValue());

		return timeZone;
	}

	protected Recurrence toRecurrence(
		Recur recur, TimeZone timeZone, Calendar startDate) {

		Calendar recStartCal = CalendarFactoryUtil.getCalendar(timeZone);

		recStartCal.setTime(startDate.getTime());

		Recurrence recurrence = new Recurrence(
			recStartCal,
			new com.liferay.portal.kernel.cal.Duration(1, 0, 0, 0));

		recurrence.setWeekStart(Calendar.SUNDAY);

		if (recur.getInterval() > 1){
			recurrence.setInterval(recur.getInterval());
		}

		Calendar until = Calendar.getInstance(timeZone);

		if (recur.getUntil() != null) {
			until.setTime(recur.getUntil());

			recurrence.setUntil(until);
		}

		String frequency = recur.getFrequency();

		if (Recur.DAILY.equals(frequency)) {
			recurrence.setFrequency(Recurrence.DAILY);

			List dayPosList = new ArrayList();

			Iterator itr = recur.getDayList().iterator();

			while (itr.hasNext()) {
				WeekDay weekDay = (WeekDay)itr.next();

				dayPosList.add(
					new DayAndPosition(toCalendarWeekDay(weekDay), 0));
			}

			if (!dayPosList.isEmpty()) {
				recurrence.setByDay(
					(DayAndPosition[])dayPosList.toArray(
						new DayAndPosition[0]));
			}
		}
		else if (Recur.WEEKLY.equals(frequency)) {
			recurrence.setFrequency(Recurrence.WEEKLY);

			List dayPosList = new ArrayList();

			Iterator itr = recur.getDayList().iterator();

			while (itr.hasNext()) {
				WeekDay weekDay = (WeekDay)itr.next();

				dayPosList.add(
					new DayAndPosition(toCalendarWeekDay(weekDay), 0));
			}

			if (!dayPosList.isEmpty()) {
				recurrence.setByDay(
					(DayAndPosition[])dayPosList.toArray(
						new DayAndPosition[0]));
			}
		}
		else if (Recur.MONTHLY.equals(frequency)) {
			recurrence.setFrequency(Recurrence.MONTHLY);

			Iterator itr = recur.getMonthDayList().iterator();

			if (itr.hasNext()) {
				Integer monthDay = (Integer)itr.next();

				recurrence.setByMonthDay(new int[] {monthDay.intValue()});
			}

			itr = recur.getDayList().iterator();

			if (itr.hasNext()) {
				WeekDay weekDay = (WeekDay)itr.next();

				DayAndPosition[] dayPos = {
					new DayAndPosition(toCalendarWeekDay(weekDay),
					weekDay.getOffset())
				};

				recurrence.setByDay(dayPos);
			}
		}
		else if (Recur.YEARLY.equals(frequency)) {
			recurrence.setFrequency(Recurrence.YEARLY);
		}

		return recurrence;
	}

	protected void validate(
			String title, int startDateMonth, int startDateDay,
			int startDateYear, int endDateMonth, int endDateDay,
			int endDateYear, int durationHour, int durationMinute,
			boolean allDay)
		throws PortalException, SystemException {

		if (Validator.isNull(title)) {
			throw new EventTitleException();
		}
		else if (!Validator.isDate(
				startDateMonth, startDateDay, startDateYear)) {

			throw new EventStartDateException();
		}
		else if (!Validator.isDate(endDateMonth, endDateDay, endDateYear)) {
			throw new EventEndDateException();
		}

		if (!allDay && durationHour <= 0 && durationMinute <= 0) {
			throw new EventDurationException();
		}

		Calendar startDate = CalendarFactoryUtil.getCalendar(
			startDateYear, startDateMonth, startDateDay);

		Calendar endDate = CalendarFactoryUtil.getCalendar(
			endDateYear, endDateMonth, endDateDay);

		if (startDate.after(endDate)) {
			throw new EventEndDateException();
		}
	}

	private static Log _log = LogFactory.getLog(CalEventLocalServiceImpl.class);

}
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

package com.liferay.portlet.calendar.service.spring;

/**
 * <a href="CalEventServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventServiceUtil {
	public static final String PORTLET_ID = "8";

	public static com.liferay.portlet.calendar.model.CalEvent addEvent(
		java.lang.String groupId, java.lang.String title,
		java.lang.String description, int startMonth, int startDay,
		int startYear, int startHour, int startMinute, int endMonth,
		int endDay, int endYear, int durationHour, int durationMinute,
		boolean allDay, boolean timeZoneSensitive, java.lang.String type,
		java.lang.String location, java.lang.String street,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String phone, boolean repeating,
		com.liferay.util.cal.Recurrence recurrence, java.lang.String remindBy,
		int firstReminder, int secondReminder)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.addEvent(groupId, title, description,
				startMonth, startDay, startYear, startHour, startMinute,
				endMonth, endDay, endYear, durationHour, durationMinute,
				allDay, timeZoneSensitive, type, location, street, city, state,
				zip, phone, repeating, recurrence, remindBy, firstReminder,
				secondReminder);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void checkReminders()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();
			calEventService.checkReminders();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteEvent(java.lang.String eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();
			calEventService.deleteEvent(eventId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.calendar.model.CalEvent getEvent(
		java.lang.String eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEvent(eventId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEvents(java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEvents(groupId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEvents(java.lang.String groupId,
		java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEvents(groupId, type);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEventsAfter(java.lang.String groupId,
		java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEventsAfter(groupId, date);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEventsAfter(java.lang.String groupId,
		java.lang.String type, java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEventsAfter(groupId, type, date);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEventsBefore(java.lang.String groupId,
		java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEventsBefore(groupId, date);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEventsBefore(java.lang.String groupId,
		java.lang.String type, java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEventsBefore(groupId, type, date);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEventsByDay(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEventsByDay(groupId, companyId, cal);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEventsByDay(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal,
		java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getEventsByDay(groupId, companyId, cal, type);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getPrivateEvents(java.util.Calendar cal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getPrivateEvents(cal);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getPrivateRepeatingEvents()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getPrivateRepeatingEvents();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getPublicEvents(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getPublicEvents(groupId, companyId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getPublicRepeatingEvents(
		java.lang.String groupId, java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.getPublicRepeatingEvents(groupId, companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasEvents(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.hasEvents(groupId, companyId, cal);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasEvents(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal,
		java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.hasEvents(groupId, companyId, cal, type);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.calendar.model.CalEvent updateEvent(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String title, java.lang.String description, int startMonth,
		int startDay, int startYear, int startHour, int startMinute,
		int endMonth, int endDay, int endYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, java.lang.String location,
		java.lang.String street, java.lang.String city, java.lang.String state,
		java.lang.String zip, java.lang.String phone, boolean repeating,
		com.liferay.util.cal.Recurrence recurrence, java.lang.String remindBy,
		int firstReminder, int secondReminder)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.updateEvent(eventId, groupId, title,
				description, startMonth, startDay, startYear, startHour,
				startMinute, endMonth, endDay, endYear, durationHour,
				durationMinute, allDay, timeZoneSensitive, type, location,
				street, city, state, zip, phone, repeating, recurrence,
				remindBy, firstReminder, secondReminder);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.hasAdmin();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin(java.lang.String eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalEventService calEventService = CalEventServiceFactory.getService();

			return calEventService.hasAdmin(eventId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}
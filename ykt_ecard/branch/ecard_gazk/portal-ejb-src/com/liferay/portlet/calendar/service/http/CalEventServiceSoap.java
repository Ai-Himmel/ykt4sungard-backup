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

package com.liferay.portlet.calendar.service.http;

import com.liferay.portlet.calendar.service.spring.CalEventServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="CalEventServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventServiceSoap {
	public static com.liferay.portlet.calendar.model.CalEventModel addEvent(
		java.lang.String groupId, java.lang.String title,
		java.lang.String description, int startMonth, int startDay,
		int startYear, int startHour, int startMinute, int endMonth,
		int endDay, int endYear, int durationHour, int durationMinute,
		boolean allDay, boolean timeZoneSensitive, java.lang.String type,
		java.lang.String location, java.lang.String street,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String phone, boolean repeating,
		com.liferay.util.cal.Recurrence recurrence, java.lang.String remindBy,
		int firstReminder, int secondReminder) throws RemoteException {
		try {
			com.liferay.portlet.calendar.model.CalEvent returnValue = CalEventServiceUtil.addEvent(groupId,
					title, description, startMonth, startDay, startYear,
					startHour, startMinute, endMonth, endDay, endYear,
					durationHour, durationMinute, allDay, timeZoneSensitive,
					type, location, street, city, state, zip, phone, repeating,
					recurrence, remindBy, firstReminder, secondReminder);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void checkReminders() throws RemoteException {
		try {
			CalEventServiceUtil.checkReminders();
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEvent(java.lang.String eventId)
		throws RemoteException {
		try {
			CalEventServiceUtil.deleteEvent(eventId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel getEvent(
		java.lang.String eventId) throws RemoteException {
		try {
			com.liferay.portlet.calendar.model.CalEvent returnValue = CalEventServiceUtil.getEvent(eventId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEvents(
		java.lang.String groupId) throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEvents(groupId);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEvents(
		java.lang.String groupId, java.lang.String type)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEvents(groupId,
					type);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEventsAfter(
		java.lang.String groupId, java.util.Date date)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEventsAfter(groupId,
					date);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEventsAfter(
		java.lang.String groupId, java.lang.String type, java.util.Date date)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEventsAfter(groupId,
					type, date);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEventsBefore(
		java.lang.String groupId, java.util.Date date)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEventsBefore(groupId,
					date);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEventsBefore(
		java.lang.String groupId, java.lang.String type, java.util.Date date)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEventsBefore(groupId,
					type, date);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEventsByDay(
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal) throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEventsByDay(groupId,
					companyId, cal);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getEventsByDay(
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal, java.lang.String type)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getEventsByDay(groupId,
					companyId, cal, type);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getPrivateEvents(
		java.util.Calendar cal) throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getPrivateEvents(cal);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getPrivateRepeatingEvents()
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getPrivateRepeatingEvents();

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getPublicEvents(
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal) throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getPublicEvents(groupId,
					companyId, cal);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel[] getPublicRepeatingEvents(
		java.lang.String groupId, java.lang.String companyId)
		throws RemoteException {
		try {
			java.util.List returnValue = CalEventServiceUtil.getPublicRepeatingEvents(groupId,
					companyId);

			return (com.liferay.portlet.calendar.model.CalEvent[])returnValue.toArray(new com.liferay.portlet.calendar.model.CalEvent[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasEvents(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal)
		throws RemoteException {
		try {
			boolean returnValue = CalEventServiceUtil.hasEvents(groupId,
					companyId, cal);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasEvents(java.lang.String groupId,
		java.lang.String companyId, java.util.Calendar cal,
		java.lang.String type) throws RemoteException {
		try {
			boolean returnValue = CalEventServiceUtil.hasEvents(groupId,
					companyId, cal, type);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.calendar.model.CalEventModel updateEvent(
		java.lang.String eventId, java.lang.String groupId,
		java.lang.String title, java.lang.String description, int startMonth,
		int startDay, int startYear, int startHour, int startMinute,
		int endMonth, int endDay, int endYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, java.lang.String location,
		java.lang.String street, java.lang.String city, java.lang.String state,
		java.lang.String zip, java.lang.String phone, boolean repeating,
		com.liferay.util.cal.Recurrence recurrence, java.lang.String remindBy,
		int firstReminder, int secondReminder) throws RemoteException {
		try {
			com.liferay.portlet.calendar.model.CalEvent returnValue = CalEventServiceUtil.updateEvent(eventId,
					groupId, title, description, startMonth, startDay,
					startYear, startHour, startMinute, endMonth, endDay,
					endYear, durationHour, durationMinute, allDay,
					timeZoneSensitive, type, location, street, city, state,
					zip, phone, repeating, recurrence, remindBy, firstReminder,
					secondReminder);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin() throws RemoteException {
		try {
			boolean returnValue = CalEventServiceUtil.hasAdmin();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String eventId)
		throws RemoteException {
		try {
			boolean returnValue = CalEventServiceUtil.hasAdmin(eventId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}
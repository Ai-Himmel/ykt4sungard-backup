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

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.portlet.calendar.service.spring.CalEventServiceUtil;

import com.liferay.util.lang.BooleanWrapper;
import com.liferay.util.lang.IntegerWrapper;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CalEventServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventServiceHttp {
	public static com.liferay.portlet.calendar.model.CalEvent addEvent(
		HttpPrincipal httpPrincipal, java.lang.String groupId,
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
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = title;

			if (title == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = description;

			if (description == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new IntegerWrapper(startMonth);
			Object paramObj4 = new IntegerWrapper(startDay);
			Object paramObj5 = new IntegerWrapper(startYear);
			Object paramObj6 = new IntegerWrapper(startHour);
			Object paramObj7 = new IntegerWrapper(startMinute);
			Object paramObj8 = new IntegerWrapper(endMonth);
			Object paramObj9 = new IntegerWrapper(endDay);
			Object paramObj10 = new IntegerWrapper(endYear);
			Object paramObj11 = new IntegerWrapper(durationHour);
			Object paramObj12 = new IntegerWrapper(durationMinute);
			Object paramObj13 = new BooleanWrapper(allDay);
			Object paramObj14 = new BooleanWrapper(timeZoneSensitive);
			Object paramObj15 = type;

			if (type == null) {
				paramObj15 = new NullWrapper("java.lang.String");
			}

			Object paramObj16 = location;

			if (location == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = street;

			if (street == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = city;

			if (city == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = state;

			if (state == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = zip;

			if (zip == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = phone;

			if (phone == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = new BooleanWrapper(repeating);
			Object paramObj23 = recurrence;

			if (recurrence == null) {
				paramObj23 = new NullWrapper("com.liferay.util.cal.Recurrence");
			}

			Object paramObj24 = remindBy;

			if (remindBy == null) {
				paramObj24 = new NullWrapper("java.lang.String");
			}

			Object paramObj25 = new IntegerWrapper(firstReminder);
			Object paramObj26 = new IntegerWrapper(secondReminder);
			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"addEvent",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.calendar.model.CalEvent)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void checkReminders(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"checkReminders", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static void deleteEvent(HttpPrincipal httpPrincipal,
		java.lang.String eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = eventId;

			if (eventId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"deleteEvent", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.calendar.model.CalEvent getEvent(
		HttpPrincipal httpPrincipal, java.lang.String eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = eventId;

			if (eventId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEvent", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.calendar.model.CalEvent)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEvents(HttpPrincipal httpPrincipal,
		java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEvents", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEvents(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = type;

			if (type == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEvents", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEventsAfter(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = date;

			if (date == null) {
				paramObj1 = new NullWrapper("java.util.Date");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEventsAfter", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEventsAfter(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String type, java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = type;

			if (type == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = date;

			if (date == null) {
				paramObj2 = new NullWrapper("java.util.Date");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEventsAfter",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEventsBefore(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = date;

			if (date == null) {
				paramObj1 = new NullWrapper("java.util.Date");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEventsBefore", new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEventsBefore(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String type, java.util.Date date)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = type;

			if (type == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = date;

			if (date == null) {
				paramObj2 = new NullWrapper("java.util.Date");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEventsBefore",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEventsByDay(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = companyId;

			if (companyId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEventsByDay",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getEventsByDay(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal, java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = companyId;

			if (companyId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			Object paramObj3 = type;

			if (type == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getEventsByDay",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getPrivateEvents(HttpPrincipal httpPrincipal,
		java.util.Calendar cal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = cal;

			if (cal == null) {
				paramObj0 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getPrivateEvents", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getPrivateRepeatingEvents(
		HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getPrivateRepeatingEvents", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getPublicEvents(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = companyId;

			if (companyId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getPublicEvents",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static java.util.List getPublicRepeatingEvents(
		HttpPrincipal httpPrincipal, java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = companyId;

			if (companyId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"getPublicRepeatingEvents",
					new Object[] { paramObj0, paramObj1 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (java.util.List)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static boolean hasEvents(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = companyId;

			if (companyId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"hasEvents",
					new Object[] { paramObj0, paramObj1, paramObj2 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static boolean hasEvents(HttpPrincipal httpPrincipal,
		java.lang.String groupId, java.lang.String companyId,
		java.util.Calendar cal, java.lang.String type)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = groupId;

			if (groupId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = companyId;

			if (companyId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = cal;

			if (cal == null) {
				paramObj2 = new NullWrapper("java.util.Calendar");
			}

			Object paramObj3 = type;

			if (type == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"hasEvents",
					new Object[] { paramObj0, paramObj1, paramObj2, paramObj3 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static com.liferay.portlet.calendar.model.CalEvent updateEvent(
		HttpPrincipal httpPrincipal, java.lang.String eventId,
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
			Object paramObj0 = eventId;

			if (eventId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = groupId;

			if (groupId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = title;

			if (title == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = description;

			if (description == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = new IntegerWrapper(startMonth);
			Object paramObj5 = new IntegerWrapper(startDay);
			Object paramObj6 = new IntegerWrapper(startYear);
			Object paramObj7 = new IntegerWrapper(startHour);
			Object paramObj8 = new IntegerWrapper(startMinute);
			Object paramObj9 = new IntegerWrapper(endMonth);
			Object paramObj10 = new IntegerWrapper(endDay);
			Object paramObj11 = new IntegerWrapper(endYear);
			Object paramObj12 = new IntegerWrapper(durationHour);
			Object paramObj13 = new IntegerWrapper(durationMinute);
			Object paramObj14 = new BooleanWrapper(allDay);
			Object paramObj15 = new BooleanWrapper(timeZoneSensitive);
			Object paramObj16 = type;

			if (type == null) {
				paramObj16 = new NullWrapper("java.lang.String");
			}

			Object paramObj17 = location;

			if (location == null) {
				paramObj17 = new NullWrapper("java.lang.String");
			}

			Object paramObj18 = street;

			if (street == null) {
				paramObj18 = new NullWrapper("java.lang.String");
			}

			Object paramObj19 = city;

			if (city == null) {
				paramObj19 = new NullWrapper("java.lang.String");
			}

			Object paramObj20 = state;

			if (state == null) {
				paramObj20 = new NullWrapper("java.lang.String");
			}

			Object paramObj21 = zip;

			if (zip == null) {
				paramObj21 = new NullWrapper("java.lang.String");
			}

			Object paramObj22 = phone;

			if (phone == null) {
				paramObj22 = new NullWrapper("java.lang.String");
			}

			Object paramObj23 = new BooleanWrapper(repeating);
			Object paramObj24 = recurrence;

			if (recurrence == null) {
				paramObj24 = new NullWrapper("com.liferay.util.cal.Recurrence");
			}

			Object paramObj25 = remindBy;

			if (remindBy == null) {
				paramObj25 = new NullWrapper("java.lang.String");
			}

			Object paramObj26 = new IntegerWrapper(firstReminder);
			Object paramObj27 = new IntegerWrapper(secondReminder);
			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"updateEvent",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18, paramObj19, paramObj20, paramObj21,
						paramObj22, paramObj23, paramObj24, paramObj25,
						paramObj26, paramObj27
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portlet.calendar.model.CalEvent)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static boolean hasAdmin(HttpPrincipal httpPrincipal)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"hasAdmin", new Object[0]);
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	public static boolean hasAdmin(HttpPrincipal httpPrincipal,
		java.lang.String eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = eventId;

			if (eventId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CalEventServiceUtil.class.getName(),
					"hasAdmin", new Object[] { paramObj0 });
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return ((Boolean)returnObj).booleanValue();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	private static final Log _log = LogFactory.getLog(CalEventServiceHttp.class);
}
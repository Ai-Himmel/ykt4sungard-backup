<%
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
%>

<%@ include file="/html/portlet/init.jsp" %>

<%@ page import="com.liferay.portal.kernel.cal.DayAndPosition" %>
<%@ page import="com.liferay.portlet.calendar.EventDurationException" %>
<%@ page import="com.liferay.portlet.calendar.EventEndDateException" %>
<%@ page import="com.liferay.portlet.calendar.EventStartDateException" %>
<%@ page import="com.liferay.portlet.calendar.EventTitleException" %>
<%@ page import="com.liferay.portlet.calendar.NoSuchEventException" %>
<%@ page import="com.liferay.portlet.calendar.model.CalEvent" %>
<%@ page import="com.liferay.portlet.calendar.model.impl.CalEventImpl" %>
<%@ page import="com.liferay.portlet.calendar.service.CalEventLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.calendar.service.permission.CalEventPermission" %>
<%@ page import="com.liferay.portlet.calendar.util.CalUtil" %>

<%
String monthParam = request.getParameter("month");
String dayParam = request.getParameter("day");
String yearParam = request.getParameter("year");

Calendar selCal = CalendarFactoryUtil.getCalendar(timeZone, locale);

try {
	selCal.set(Calendar.YEAR, Integer.parseInt(yearParam));
}
catch (NumberFormatException nfe) {
}

try {
	if (dayParam != null) {
		selCal.set(Calendar.DATE, 1);
	}

	selCal.set(Calendar.MONTH, Integer.parseInt(monthParam));
}
catch (NumberFormatException nfe) {
}

try {
	int maxDayOfMonth = selCal.getActualMaximum(Calendar.DATE);

	int dayParamInt = Integer.parseInt(dayParam);

	if (dayParamInt > maxDayOfMonth) {
		dayParamInt = maxDayOfMonth;
	}

	selCal.set(Calendar.DATE, dayParamInt);
}
catch (NumberFormatException nfe) {
}

int selMonth = selCal.get(Calendar.MONTH);
int selDay = selCal.get(Calendar.DATE);
int selYear = selCal.get(Calendar.YEAR);

Calendar curCal = CalendarFactoryUtil.getCalendar(timeZone, locale);

int curMonth = curCal.get(Calendar.MONTH);
int curDay = curCal.get(Calendar.DATE);
int curYear = curCal.get(Calendar.YEAR);

int[] monthIds = CalendarUtil.getMonthIds();
String[] months = CalendarUtil.getMonths(locale);

String[] days = CalendarUtil.getDays(locale);

DateFormat dateFormatDate = DateFormats.getDate(locale);
DateFormat dateFormatDateTime = DateFormats.getDateTime(locale);
DateFormat dateFormatTime = DateFormats.getTime(locale);
DateFormat dateFormatISO8601 = DateUtil.getISO8601Format();
%>
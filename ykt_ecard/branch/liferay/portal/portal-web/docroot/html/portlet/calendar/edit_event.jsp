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

<%@ include file="/html/portlet/calendar/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

CalEvent event = (CalEvent)request.getAttribute(WebKeys.CALENDAR_EVENT);

long eventId = BeanParamUtil.getLong(event, request, "eventId");

Calendar startDate = CalendarUtil.roundByMinutes((Calendar)selCal.clone(), 15);

if (event != null) {
	if (!event.isTimeZoneSensitive()) {
		startDate = CalendarFactoryUtil.getCalendar();
	}

	startDate.setTime(event.getStartDate());
}

Calendar endDate = (Calendar)curCal.clone();

endDate.add(Calendar.YEAR, 1);

if (event != null) {
	if (!event.isTimeZoneSensitive()) {
		endDate = CalendarFactoryUtil.getCalendar();
	}

	if (event.getEndDate() != null) {
		endDate.setTime(event.getEndDate());
	}
}

String durationHour = String.valueOf(BeanParamUtil.getInteger(event, request, "durationHour", 1));
String durationMinute = String.valueOf(BeanParamUtil.getInteger(event, request, "durationMinute"));
String type = BeanParamUtil.getString(event, request, "type");
boolean repeating = BeanParamUtil.getBoolean(event, request, "repeating");

Recurrence recurrence = null;

int recurrenceType = ParamUtil.getInteger(request, "recurrenceType", Recurrence.NO_RECURRENCE);
String recurrenceTypeParam = ParamUtil.getString(request, "recurrenceType");
if (Validator.isNull(recurrenceTypeParam) && (event != null)) {
	if (event.getRepeating()) {
		recurrence = event.getRecurrenceObj();
		recurrenceType = recurrence.getFrequency();
	}
}

int dailyType = ParamUtil.getInteger(request, "dailyType");
String dailyTypeParam = ParamUtil.getString(request, "dailyType");
if (Validator.isNull(dailyTypeParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByDay() != null) {
			dailyType = 1;
		}
	}
}

int dailyInterval = ParamUtil.getInteger(request, "dailyInterval", 1);
String dailyIntervalParam = ParamUtil.getString(request, "dailyInterval");
if (Validator.isNull(dailyIntervalParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		dailyInterval = recurrence.getInterval();
	}
}

int weeklyInterval = ParamUtil.getInteger(request, "weeklyInterval", 1);
String weeklyIntervalParam = ParamUtil.getString(request, "weeklyInterval");
if (Validator.isNull(weeklyIntervalParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		weeklyInterval = recurrence.getInterval();
	}
}

boolean weeklyPosSu = _getWeeklyDayPos(request, Calendar.SUNDAY, event, recurrence);
boolean weeklyPosMo = _getWeeklyDayPos(request, Calendar.MONDAY, event, recurrence);
boolean weeklyPosTu = _getWeeklyDayPos(request, Calendar.TUESDAY, event, recurrence);
boolean weeklyPosWe = _getWeeklyDayPos(request, Calendar.WEDNESDAY, event, recurrence);
boolean weeklyPosTh = _getWeeklyDayPos(request, Calendar.THURSDAY, event, recurrence);
boolean weeklyPosFr = _getWeeklyDayPos(request, Calendar.FRIDAY, event, recurrence);
boolean weeklyPosSa = _getWeeklyDayPos(request, Calendar.SATURDAY, event, recurrence);

int monthlyType = ParamUtil.getInteger(request, "monthlyType");
String monthlyTypeParam = ParamUtil.getString(request, "monthlyType");
if (Validator.isNull(monthlyTypeParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonthDay() == null) {
			monthlyType = 1;
		}
	}
}

int monthlyDay0 = ParamUtil.getInteger(request, "monthlyDay0", 15);
String monthlyDay0Param = ParamUtil.getString(request, "monthlyDay0");
if (Validator.isNull(monthlyDay0Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonthDay() != null) {
			monthlyDay0 = recurrence.getByMonthDay()[0];
		}
	}
}

int monthlyInterval0 = ParamUtil.getInteger(request, "monthlyInterval0", 1);
String monthlyInterval0Param = ParamUtil.getString(request, "monthlyInterval0");
if (Validator.isNull(monthlyInterval0Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		monthlyInterval0 = recurrence.getInterval();
	}
}

int monthlyPos = ParamUtil.getInteger(request, "monthlyPos", 1);
String monthlyPosParam = ParamUtil.getString(request, "monthlyPos");
if (Validator.isNull(monthlyPosParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() != null) {
			monthlyPos = recurrence.getByMonth()[0];
		}
		else if (recurrence.getByDay() != null) {
			monthlyPos = recurrence.getByDay()[0].getDayPosition();
		}
	}
}

int monthlyDay1 = ParamUtil.getInteger(request, "monthlyDay1", Calendar.SUNDAY);
String monthlyDay1Param = ParamUtil.getString(request, "monthlyDay1");
if (Validator.isNull(monthlyDay1Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() != null) {
			monthlyDay1 = -1;
		}
		else if (recurrence.getByDay() != null) {
			monthlyDay1 = recurrence.getByDay()[0].getDayOfWeek();
		}
	}
}

int monthlyInterval1 = ParamUtil.getInteger(request, "monthlyInterval1", 1);
String monthlyInterval1Param = ParamUtil.getString(request, "monthlyInterval1");
if (Validator.isNull(monthlyInterval1Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		monthlyInterval1 = recurrence.getInterval();
	}
}

int yearlyType = ParamUtil.getInteger(request, "yearlyType");
String yearlyTypeParam = ParamUtil.getString(request, "yearlyType");
if (Validator.isNull(yearlyTypeParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() != null) {
			yearlyType = 1;
		}
	}
}

int yearlyMonth0 = ParamUtil.getInteger(request, "yearlyMonth0", Calendar.JANUARY);
String yearlyMonth0Param = ParamUtil.getString(request, "yearlyMonth0");
if (Validator.isNull(yearlyMonth0Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() == null) {
			yearlyMonth0 = recurrence.getDtStart().get(Calendar.MONTH);
		}
	}
}

int yearlyDay0 = ParamUtil.getInteger(request, "yearlyDay0", 15);
String yearlyDay0Param = ParamUtil.getString(request, "yearlyDay0");
if (Validator.isNull(yearlyDay0Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() == null) {
			yearlyDay0 = recurrence.getDtStart().get(Calendar.DATE);
		}
	}
}

int yearlyInterval0 = ParamUtil.getInteger(request, "yearlyInterval0", 1);
String yearlyInterval0Param = ParamUtil.getString(request, "yearlyInterval0");
if (Validator.isNull(yearlyInterval0Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		yearlyInterval0 = recurrence.getInterval();
	}
}

int yearlyPos = ParamUtil.getInteger(request, "yearlyPos", 1);
String yearlyPosParam = ParamUtil.getString(request, "yearlyPos");
if (Validator.isNull(yearlyPosParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() != null) {
			yearlyPos = recurrence.getByMonth()[0];
		}
		else if (recurrence.getByDay() != null) {
			yearlyPos = recurrence.getByDay()[0].getDayPosition();
		}
	}
}

int yearlyDay1 = ParamUtil.getInteger(request, "yearlyDay1", Calendar.SUNDAY);
String yearlyDay1Param = ParamUtil.getString(request, "yearlyDay1");
if (Validator.isNull(yearlyDay1Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() != null) {
			yearlyDay1 = -1;
		}
		else if (recurrence.getByDay() != null) {
			yearlyDay1 = recurrence.getByDay()[0].getDayOfWeek();
		}
	}
}

int yearlyMonth1 = ParamUtil.getInteger(request, "yearlyMonth1", Calendar.JANUARY);
String yearlyMonth1Param = ParamUtil.getString(request, "yearlyMonth1");
if (Validator.isNull(yearlyMonth1Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getByMonth() != null) {
			yearlyMonth1 = recurrence.getByMonth()[0];
		}
	}
}

int yearlyInterval1 = ParamUtil.getInteger(request, "yearlyInterval1", 1);
String yearlyInterval1Param = ParamUtil.getString(request, "yearlyInterval1");
if (Validator.isNull(yearlyInterval1Param) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		yearlyInterval1 = recurrence.getInterval();
	}
}

int endDateType = ParamUtil.getInteger(request, "endDateType");
String endDateTypeParam = ParamUtil.getString(request, "endDateType");
if (Validator.isNull(endDateTypeParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		if (recurrence.getUntil() != null) {
			endDateType = 2;
		}
		else if (recurrence.getOccurrence() > 0) {
			endDateType = 1;
		}
	}
}

int endDateOccurrence = ParamUtil.getInteger(request, "endDateOccurrence", 10);
String endDateOccurrenceParam = ParamUtil.getString(request, "endDateOccurrence");
if (Validator.isNull(endDateOccurrenceParam) && (event != null)) {
	if ((event.getRepeating()) && (recurrence != null)) {
		endDateOccurrence = recurrence.getOccurrence();
	}
}

String remindBy = BeanParamUtil.getString(event, request, "remindBy", CalEventImpl.REMIND_BY_EMAIL);
int firstReminder = BeanParamUtil.getInteger(event, request, "firstReminder", (int)Time.MINUTE * 15);
int secondReminder = BeanParamUtil.getInteger(event, request, "secondReminder", (int)Time.MINUTE * 5);
%>

<script type="text/javascript">
	function <portlet:namespace />init() {
		<c:choose>
			<c:when test="<%= recurrenceType == Recurrence.NO_RECURRENCE %>">
				<portlet:namespace />showTable("<portlet:namespace />neverTable");
			</c:when>
			<c:when test="<%= recurrenceType == Recurrence.DAILY %>">
				<portlet:namespace />showTable("<portlet:namespace />dailyTable");
			</c:when>
			<c:when test="<%= recurrenceType == Recurrence.WEEKLY %>">
				<portlet:namespace />showTable("<portlet:namespace />weeklyTable");
			</c:when>
			<c:when test="<%= recurrenceType == Recurrence.MONTHLY %>">
				<portlet:namespace />showTable("<portlet:namespace />monthlyTable");
			</c:when>
			<c:when test="<%= recurrenceType == Recurrence.YEARLY %>">
				<portlet:namespace />showTable("<portlet:namespace />yearlyTable");
			</c:when>
		</c:choose>
	}

	function <portlet:namespace />showTable(id) {
		document.getElementById("<portlet:namespace />neverTable").style.display = "none";
		document.getElementById("<portlet:namespace />dailyTable").style.display = "none";
		document.getElementById("<portlet:namespace />weeklyTable").style.display = "none";
		document.getElementById("<portlet:namespace />monthlyTable").style.display = "none";
		document.getElementById("<portlet:namespace />yearlyTable").style.display = "none";

		document.getElementById(id).style.display = "block";
	}

	function <portlet:namespace />saveEvent() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= event == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/calendar/edit_event" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveEvent(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />eventId" type="hidden" value="<%= eventId %>" />

<liferay-ui:tabs
	names="event"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= EventDurationException.class %>" message="please-enter-a-longer-duration" />
<liferay-ui:error exception="<%= EventStartDateException.class %>" message="please-enter-a-valid-start-date" />
<liferay-ui:error exception="<%= EventTitleException.class %>" message="please-enter-a-valid-title" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="start-date" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= CalEvent.class %>" bean="<%= event %>" field="startDate" defaultValue="<%= startDate %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="duration" />
	</td>
	<td>
		<select name="<portlet:namespace />durationHour">
			<option <%= (durationHour.equals("0")) ? "selected" : "" %> value="0">0</option>
			<option <%= (durationHour.equals("1")) ? "selected" : "" %> value="1">1</option>
			<option <%= (durationHour.equals("2")) ? "selected" : "" %> value="2">2</option>
			<option <%= (durationHour.equals("3")) ? "selected" : "" %> value="3">3</option>
			<option <%= (durationHour.equals("4")) ? "selected" : "" %> value="4">4</option>
			<option <%= (durationHour.equals("5")) ? "selected" : "" %> value="5">5</option>
			<option <%= (durationHour.equals("6")) ? "selected" : "" %> value="6">6</option>
			<option <%= (durationHour.equals("7")) ? "selected" : "" %> value="7">7</option>
			<option <%= (durationHour.equals("8")) ? "selected" : "" %> value="8">8</option>
			<option <%= (durationHour.equals("9")) ? "selected" : "" %> value="9">9</option>
			<option <%= (durationHour.equals("10")) ? "selected" : "" %> value="10">10</option>
			<option <%= (durationHour.equals("11")) ? "selected" : "" %> value="11">11</option>
			<option <%= (durationHour.equals("12")) ? "selected" : "" %> value="12">12</option>
			<option <%= (durationHour.equals("13")) ? "selected" : "" %> value="13">13</option>
			<option <%= (durationHour.equals("14")) ? "selected" : "" %> value="14">14</option>
			<option <%= (durationHour.equals("15")) ? "selected" : "" %> value="15">15</option>
			<option <%= (durationHour.equals("16")) ? "selected" : "" %> value="16">16</option>
			<option <%= (durationHour.equals("17")) ? "selected" : "" %> value="17">17</option>
			<option <%= (durationHour.equals("18")) ? "selected" : "" %> value="18">18</option>
			<option <%= (durationHour.equals("19")) ? "selected" : "" %> value="19">19</option>
			<option <%= (durationHour.equals("20")) ? "selected" : "" %> value="20">20</option>
			<option <%= (durationHour.equals("21")) ? "selected" : "" %> value="21">21</option>
			<option <%= (durationHour.equals("22")) ? "selected" : "" %> value="22">22</option>
			<option <%= (durationHour.equals("23")) ? "selected" : "" %> value="23">23</option>
			<option <%= (durationHour.equals("24")) ? "selected" : "" %> value="24">24</option>
		</select>

		<liferay-ui:message key="hours" />

		<select name="<portlet:namespace />durationMinute">
			<option <%= (durationMinute.equals("00")) ? "selected" : "" %> value="00">:00</option>
			<option <%= (durationMinute.equals("05")) ? "selected" : "" %> value="05">:05</option>
			<option <%= (durationMinute.equals("10")) ? "selected" : "" %> value="10">:10</option>
			<option <%= (durationMinute.equals("15")) ? "selected" : "" %> value="15">:15</option>
			<option <%= (durationMinute.equals("20")) ? "selected" : "" %> value="20">:20</option>
			<option <%= (durationMinute.equals("30")) ? "selected" : "" %> value="30">:30</option>
			<option <%= (durationMinute.equals("45")) ? "selected" : "" %> value="45">:45</option>
		</select>

		<liferay-ui:message key="minutes" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="all-day-event" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="allDay" defaultValue="<%= event == null ? false : event.isAllDay() %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="time-zone-sensitive" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="timeZoneSensitive" defaultValue="<%= event == null ? true : event.isTimeZoneSensitive() %>" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="title" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= CalEvent.class %>" field="title" defaultValue="<%= event == null ? LanguageUtil.get(pageContext, "new-event") : event.getTitle() %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= CalEvent.class %>" bean="<%= event %>" field="description" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="type" />
	</td>
	<td>
		<select name="<portlet:namespace />type">

			<%
			for (int i = 0; i < CalEventImpl.TYPES.length; i++) {
			%>

				<option <%= type.equals(CalEventImpl.TYPES[i]) ? "selected" : "" %> value="<%= CalEventImpl.TYPES[i] %>"><%= LanguageUtil.get(pageContext, CalEventImpl.TYPES[i]) %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>

<c:if test="<%= event == null %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="permissions" />
		</td>
		<td>
			<liferay-ui:input-permissions
				modelName="<%= CalEvent.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

<br /><br />

<liferay-ui:tabs names="repeat" />

<liferay-ui:error exception="<%= EventEndDateException.class %>" message="please-enter-a-valid-end-date" />

<table class="lfr-table">
<tr>
	<td>
		<input <%= (recurrenceType == Recurrence.NO_RECURRENCE) ? "checked" : "" %> name="<portlet:namespace />recurrenceType" type="radio" value="<%= Recurrence.NO_RECURRENCE %>" onClick="<portlet:namespace />showTable('<portlet:namespace />neverTable');"> <liferay-ui:message key="never" /><br />
		<input <%= (recurrenceType == Recurrence.DAILY) ? "checked" : "" %> name="<portlet:namespace />recurrenceType" type="radio" value="<%= Recurrence.DAILY %>" onClick="<portlet:namespace />showTable('<portlet:namespace />dailyTable');"> <liferay-ui:message key="daily" /><br />
		<input <%= (recurrenceType == Recurrence.WEEKLY) ? "checked" : "" %> name="<portlet:namespace />recurrenceType" type="radio" value="<%= Recurrence.WEEKLY %>" onClick="<portlet:namespace />showTable('<portlet:namespace />weeklyTable');"> <liferay-ui:message key="weekly" /><br />
		<input <%= (recurrenceType == Recurrence.MONTHLY) ? "checked" : "" %> name="<portlet:namespace />recurrenceType" type="radio" value="<%= Recurrence.MONTHLY %>" onClick="<portlet:namespace />showTable('<portlet:namespace />monthlyTable');"> <liferay-ui:message key="monthly" /><br />
		<input <%= (recurrenceType == Recurrence.YEARLY) ? "checked" : "" %> name="<portlet:namespace />recurrenceType" type="radio" value="<%= Recurrence.YEARLY %>" onClick="<portlet:namespace />showTable('<portlet:namespace />yearlyTable');"> <liferay-ui:message key="yearly" />
	</td>
	<td valign="top">
		<div id="<portlet:namespace />neverTable" style="display: none;">
			<table border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td>
					<liferay-ui:message key="do-not-repeat-this-event" />
				</td>
			</tr>
			</table>
		</div>

		<div id="<portlet:namespace />dailyTable" style="display: none;">
			<table border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td>
					<input <%= (dailyType == 0) ? "checked" : "" %> name="<portlet:namespace />dailyType" type="radio" value="0"> <input maxlength="3" name="<portlet:namespace />dailyInterval" size="3" type="text" value="<%= dailyInterval %>" /> <liferay-ui:message key="day-s" /><br />
					<input <%= (dailyType == 1) ? "checked" : "" %> name="<portlet:namespace />dailyType" type="radio" value="1"> <liferay-ui:message key="every-weekday" />
				</td>
			</tr>
			</table>
		</div>

		<div id="<portlet:namespace />weeklyTable" style="display: none;">
			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:message key="recur-every" /> <input maxlength="2" name="<portlet:namespace />weeklyInterval" size="2" type="text" value="<%= weeklyInterval %>" /> <liferay-ui:message key="weeks-on" />

					<table class="lfr-table">
					<tr>
						<td nowrap>
							<input <%= weeklyPosSu ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.SUNDAY %>" type="checkbox"> <%= days[0] %>
						</td>
						<td nowrap>
							<input <%= weeklyPosMo ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.MONDAY %>" type="checkbox"> <%= days[1] %>
						</td>
						<td nowrap>
							<input <%= weeklyPosTu ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.TUESDAY %>" type="checkbox"> <%= days[2] %>
						</td>
						<td nowrap>
							<input <%= weeklyPosWe ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.WEDNESDAY %>" type="checkbox"> <%= days[3] %>
						</td>
					</tr>
					<tr>
						<td nowrap>
							<input <%= weeklyPosTh ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.THURSDAY %>" type="checkbox"> <%= days[4] %>
						</td>
						<td nowrap>
							<input <%= weeklyPosFr ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.FRIDAY %>" type="checkbox"> <%= days[5] %>
						</td>
						<td colspan="2" nowrap>
							<input <%= weeklyPosSa ? "checked" : "" %> name="<portlet:namespace />weeklyDayPos<%= Calendar.SATURDAY %>" type="checkbox"> <%= days[6] %>
						</td>
					</tr>
					</table>
				</td>
			</tr>
			</table>
		</div>

		<div id="<portlet:namespace />monthlyTable" style="display: none;">
			<table class="lfr-table">
			<tr>
				<td nowrap>
					<input <%= (monthlyType == 0) ? "checked" : "" %> name="<portlet:namespace />monthlyType" type="radio" value="0"> <liferay-ui:message key="day" /> <input maxlength="2" name="<portlet:namespace />monthlyDay0" size="2" type="text" value="<%= monthlyDay0 %>" /> <liferay-ui:message key="of-every" /> <input maxlength="2" name="<portlet:namespace />monthlyInterval0" size="2" type="text" value="<%= monthlyInterval0 %>" /> <liferay-ui:message key="month-s" /><br />

					<input <%= (monthlyType == 1) ? "checked" : "" %> name="<portlet:namespace />monthlyType" type="radio" value="1">

					<liferay-ui:message key="the" />

					<select name="<portlet:namespace />monthlyPos">
						<option <%= (monthlyPos == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="first" /></option>
						<option <%= (monthlyPos == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="second" /></option>
						<option <%= (monthlyPos == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="third" /></option>
						<option <%= (monthlyPos == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="fourth" /></option>
						<option <%= (monthlyPos == -1) ? "selected" : "" %> value="-1"><liferay-ui:message key="last" /></option>
					</select>

					<select name="<portlet:namespace />monthlyDay1">
						<option <%= (monthlyDay1 == Calendar.SUNDAY) ? "selected" : "" %> value="<%= Calendar.SUNDAY %>"><%= days[0] %></option>
						<option <%= (monthlyDay1 == Calendar.MONDAY) ? "selected" : "" %> value="<%= Calendar.MONDAY %>"><%= days[1] %></option>
						<option <%= (monthlyDay1 == Calendar.TUESDAY) ? "selected" : "" %> value="<%= Calendar.TUESDAY %>"><%= days[2] %></option>
						<option <%= (monthlyDay1 == Calendar.WEDNESDAY) ? "selected" : "" %> value="<%= Calendar.WEDNESDAY %>"><%= days[3] %></option>
						<option <%= (monthlyDay1 == Calendar.THURSDAY) ? "selected" : "" %> value="<%= Calendar.THURSDAY %>"><%= days[4] %></option>
						<option <%= (monthlyDay1 == Calendar.FRIDAY) ? "selected" : "" %> value="<%= Calendar.FRIDAY %>"><%= days[5] %></option>
						<option <%= (monthlyDay1 == Calendar.SATURDAY) ? "selected" : "" %> value="<%= Calendar.SATURDAY %>"><%= days[6] %></option>
					</select>

					<liferay-ui:message key="of-every" /> <input maxlength="2" name="<portlet:namespace />monthlyInterval1" size="2" type="text" value="<%= monthlyInterval1 %>" /> <liferay-ui:message key="month-s" />
				</td>
			</tr>
			</table>
		</div>

		<div id="<portlet:namespace />yearlyTable" style="display: none;">
			<table class="lfr-table">
			<tr>
				<td nowrap>
					<input <%= (yearlyType == 0) ? "checked" : "" %> name="<portlet:namespace />yearlyType" type="radio" value="0"> <liferay-ui:message key="every" />

					<select name="<portlet:namespace />yearlyMonth0">

					<%
					for (int i = 0; i < 12; i++) {
					%>

							<option <%= (monthIds[i] == yearlyMonth0) ? "selected" : "" %> value="<%= monthIds[i] %>"><%= months[i] %></option>

					<%
					}
					%>

					</select>

					<input maxlength="2" name="<portlet:namespace />yearlyDay0" size="2" type="text" value="<%= yearlyDay0 %>" /> <liferay-ui:message key="of-every" /> <input maxlength="2" name="<portlet:namespace />yearlyInterval0" size="2" type="text" value="<%= yearlyInterval0 %>" /> <liferay-ui:message key="year-s" /><br />

					<input <%= (yearlyType == 1) ? "checked" : "" %> name="<portlet:namespace />yearlyType" type="radio" value="1"> <liferay-ui:message key="the" />

					<select name="<portlet:namespace />yearlyPos">
						<option <%= (yearlyPos == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="first" /></option>
						<option <%= (yearlyPos == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="second" /></option>
						<option <%= (yearlyPos == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="third" /></option>
						<option <%= (yearlyPos == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="fourth" /></option>
						<option <%= (yearlyPos == -1) ? "selected" : "" %> value="-1"><liferay-ui:message key="last" /></option>
					</select>

					<select name="<portlet:namespace />yearlyDay1">
						<option <%= (yearlyDay1 == Calendar.MONDAY) ? "selected" : "" %> value="<%= Calendar.MONDAY %>"><liferay-ui:message key="weekday" /></option>
						<option <%= (yearlyDay1 == Calendar.SATURDAY) ? "selected" : "" %> value="<%= Calendar.SATURDAY %>"><liferay-ui:message key="weekend-day" /></option>
						<option <%= (yearlyDay1 == Calendar.SUNDAY) ? "selected" : "" %> value="<%= Calendar.SUNDAY %>"><%= days[0] %></option>
						<option <%= (yearlyDay1 == Calendar.MONDAY) ? "selected" : "" %> value="<%= Calendar.MONDAY %>"><%= days[1] %></option>
						<option <%= (yearlyDay1 == Calendar.TUESDAY) ? "selected" : "" %> value="<%= Calendar.TUESDAY %>"><%= days[2] %></option>
						<option <%= (yearlyDay1 == Calendar.WEDNESDAY) ? "selected" : "" %> value="<%= Calendar.WEDNESDAY %>"><%= days[3] %></option>
						<option <%= (yearlyDay1 == Calendar.THURSDAY) ? "selected" : "" %> value="<%= Calendar.THURSDAY %>"><%= days[4] %></option>
						<option <%= (yearlyDay1 == Calendar.FRIDAY) ? "selected" : "" %> value="<%= Calendar.FRIDAY %>"><%= days[5] %></option>
						<option <%= (yearlyDay1 == Calendar.SATURDAY) ? "selected" : "" %> value="<%= Calendar.SATURDAY %>"><%= days[6] %></option>
					</select>

					<liferay-ui:message key="of" />

					<select name="<portlet:namespace />yearlyMonth1">

						<%
						for (int i = 0; i < 12; i++) {
						%>

								<option <%= (monthIds[i] == yearlyMonth1) ? "selected" : "" %> value="<%= monthIds[i] %>"><%= months[i] %></option>

						<%
						}
						%>

					</select>

					<liferay-ui:message key="of-every" /> <input maxlength="2" name="<portlet:namespace />yearlyInterval1" size="2" type="text" value="<%= yearlyInterval1 %>" /> <liferay-ui:message key="year-s" />
				</td>
			</tr>
			</table>
		</div>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="end-date" />
	</td>
	<td valign="top">
		<table class="lfr-table">
		<tr>
			<td>
				<input <%= (endDateType == 0) ? "checked" : "" %> name="<portlet:namespace />endDateType" type="radio" value="0"> <liferay-ui:message key="no-end-date" /><br />
				<%--<input <%= (endDateType == 1) ? "checked" : "" %> name="<portlet:namespace />endDateType" type="radio" value="1"> End after <input maxlength="3" name="<portlet:namespace />endDateOccurrence" size="3" type="text" value="<%= endDateOccurrence %>" /> occurrence(s)<br />--%>

				<input <%= (endDateType == 2) ? "checked" : "" %> name="<portlet:namespace />endDateType" type="radio" value="2"> <liferay-ui:message key="end-by" />

				<liferay-ui:input-field model="<%= CalEvent.class %>" bean="<%= event %>" field="endDate" defaultValue="<%= endDate %>" />
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

<br />

<liferay-ui:tabs names="reminders" />

<liferay-ui:message key="remind-me" />

<select name="<portlet:namespace />firstReminder">

	<%
	for (int i = 0; i < CalEventImpl.REMINDERS.length; i++) {
	%>

		<option <%= (firstReminder == CalEventImpl.REMINDERS[i]) ? "selected" : "" %> value="<%= CalEventImpl.REMINDERS[i] %>"><%= LanguageUtil.getTimeDescription(pageContext, CalEventImpl.REMINDERS[i]) %></option>

	<%
	}
	%>

</select>

<liferay-ui:message key="before-and-again" />

<select name="<portlet:namespace />secondReminder">

	<%
	for (int i = 0; i < CalEventImpl.REMINDERS.length; i++) {
	%>

		<option <%= (secondReminder == CalEventImpl.REMINDERS[i]) ? "selected" : "" %> value="<%= CalEventImpl.REMINDERS[i] %>"><%= LanguageUtil.getTimeDescription(pageContext, CalEventImpl.REMINDERS[i]) %></option>

	<%
	}
	%>

</select>

<liferay-ui:message key="before-the-event-by" />

<br /><br />

<input <%= remindBy.equals(CalEventImpl.REMIND_BY_NONE) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_NONE %>"> <liferay-ui:message key="do-not-send-a-reminder" /><br />
<input <%= remindBy.equals(CalEventImpl.REMIND_BY_EMAIL) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_EMAIL %>"> <liferay-ui:message key="email-address" /> (<%= user.getEmailAddress() %>)<br />
<input <%= remindBy.equals(CalEventImpl.REMIND_BY_SMS) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_SMS %>"> <liferay-ui:message key="sms" /> <%= Validator.isNotNull(contact.getSmsSn()) ? "(" + contact.getSmsSn() + ")" : "" %><br />
<input <%= remindBy.equals(CalEventImpl.REMIND_BY_AIM) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_AIM %>"> <liferay-ui:message key="aim" /> <%= Validator.isNotNull(contact.getAimSn()) ? "(" + contact.getAimSn() + ")" : "" %><br />
<input <%= remindBy.equals(CalEventImpl.REMIND_BY_ICQ) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_ICQ %>"> <liferay-ui:message key="icq" /> <%= Validator.isNotNull(contact.getIcqSn()) ? "(" + contact.getIcqSn() + ")" : "" %><br />
<input <%= remindBy.equals(CalEventImpl.REMIND_BY_MSN) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_MSN %>"> <liferay-ui:message key="msn" /> <%= Validator.isNotNull(contact.getMsnSn()) ? "(" + contact.getMsnSn() + ")" : "" %><br />
<input <%= remindBy.equals(CalEventImpl.REMIND_BY_YM) ? "checked" : "" %> name="<portlet:namespace />remindBy" type="radio" value="<%= CalEventImpl.REMIND_BY_YM %>"> <liferay-ui:message key="ym" /> <%= Validator.isNotNull(contact.getYmSn()) ? "(" + contact.getYmSn() + ")" : "" %>

</form>

<script type="text/javascript">
	<portlet:namespace />init();
</script>

<%!
private boolean _getWeeklyDayPos(HttpServletRequest req, int day, CalEvent event, Recurrence recurrence) {
	boolean weeklyPos = ParamUtil.getBoolean(req, "weeklyDayPos" + day);

	String weeklyPosParam = ParamUtil.getString(req, "weeklyDayPos" + day);

	if (Validator.isNull(weeklyPosParam) && (event != null)) {
		if ((event.getRepeating()) && (recurrence != null)) {
			DayAndPosition[] dayPositions = recurrence.getByDay();

			if (dayPositions != null) {
				for (int i = 0; i < dayPositions.length; i++) {
					if (dayPositions[i].getDayOfWeek() == day) {
						return true;
					}
				}
			}
		}
	}

	return weeklyPos;
}
%>
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

<%@ include file="/html/taglib/init.jsp" %>

<%
int month = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:calendar:month"));
int day = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:calendar:day"));
int year = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:calendar:year"));
String headerPattern = (String)request.getAttribute("liferay-ui:calendar:headerPattern");
DateFormat headerFormat = (DateFormat)request.getAttribute("liferay-ui:calendar:headerFormat");
Set data = (Set)request.getAttribute("liferay-ui:calendar:data");

Calendar selCal = CalendarFactoryUtil.getCalendar(timeZone, locale);

selCal.set(Calendar.MONTH, month);
selCal.set(Calendar.DATE, day);
selCal.set(Calendar.YEAR, year);

int selMonth = selCal.get(Calendar.MONTH);
int selDay = selCal.get(Calendar.DATE);
int selYear = selCal.get(Calendar.YEAR);

int maxDayOfMonth = selCal.getActualMaximum(Calendar.DATE);

selCal.set(Calendar.DATE, 1);
int dayOfWeek = selCal.get(Calendar.DAY_OF_WEEK);
selCal.set(Calendar.DATE, selDay);

Calendar curCal = CalendarFactoryUtil.getCalendar(timeZone, locale);

int curMonth = curCal.get(Calendar.MONTH);
int curDay = curCal.get(Calendar.DATE);
int curYear = curCal.get(Calendar.YEAR);
%>

<table border="0" cellpadding="0" cellspacing="0" width="190">
<tr>
	<td>
		<table border="0" cellpadding="0" cellspacing="0" width="100%">

		<c:if test="<%= Validator.isNotNull(headerPattern) || (headerFormat != null) %>">

			<%
			DateFormat dateFormat = headerFormat;

			if (Validator.isNotNull(headerPattern)) {
				dateFormat = new SimpleDateFormat(headerPattern, locale);
			}
			%>

			<tr class="portlet-section-header">
				<td class="portlet-section-header" colspan="15" style="height: 1px;"></td>
			</tr>
			<tr>
				<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
				<td align="center" colspan="13" height="20">
					<%= dateFormat.format(selCal.getTime()) %>
				</td>
				<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
			</tr>
		</c:if>

		<tr class="portlet-section-header">

			<%
			for (int i = 0; i < 7;  i++) {
				int daysIndex = (selCal.getFirstDayOfWeek() + i - 1) % 7;
			%>

				<td><img border="0" height="22" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
				<td align="center" width="26">
					<span class="font-small" style="font-weight: bold;">
					<%= LanguageUtil.get(pageContext, CalendarUtil.DAYS_ABBREVIATION[daysIndex]) %>
					</span>
				</td>

			<%
			}
			%>

			<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
		</tr>
		<tr>

			<%
			if (((selCal.getFirstDayOfWeek()) == Calendar.MONDAY)) {
				if (dayOfWeek == 1) {
					dayOfWeek += 6;
				}
				else {
					dayOfWeek --;
				}
			}

			for (int i = 1; i < dayOfWeek; i++) {
			%>

				<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
				<td height="25" width="26">&nbsp;</td>

			<%
			}

			for (int i = 1; i <= maxDayOfMonth; i++) {
				if (dayOfWeek > 7) {
			%>

						<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
					</tr>
					<tr>
						<td class="portlet-section-header" colspan="15" style="height: 1px;"></td>
					</tr>
					<tr>

			<%
					dayOfWeek = 1;
				}

				dayOfWeek++;

				Calendar tempCal = (Calendar)selCal.clone();

				tempCal.set(Calendar.MONTH, selMonth);
				tempCal.set(Calendar.DATE, i);
				tempCal.set(Calendar.YEAR, selYear);

				boolean hasData = (data != null) && data.contains(new Integer(i));

				String className = "";

				if ((selMonth == curMonth) &&
					(i == curDay) &&
					(selYear == curYear)) {

					className = "portlet-section-header";
				}
			%>

				<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
				<td align="center" class="<%= className %> font-small" height="25" valign="top" width="26">
					<table border="0" cellpadding="0" cellspacing="0" width="24">
					<tr>
						<td align="center" height="20" valign="top">
							<a href="javascript: <%= namespace %>updateCalendar(<%= selMonth %>, <%= i %>, <%= selYear %>);"><%= i %></a>
						</td>
					</tr>

					<c:if test="<%= hasData %>">
						<tr>
							<td class="portlet-section-alternate"><img border="0" height="3" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
						</tr>
					</c:if>

					</table>
				</td>

			<%
			}

			for (int i = 7; i >= dayOfWeek; i--) {
			%>

				<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
				<td height="25" width="26">&nbsp;</td>

			<%
			}
			%>

			<td class="portlet-section-header"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
		</tr>
		<tr>
			<td class="portlet-section-header" colspan="15" style="height: 1px;"></td>
		</tr>
		</table>
	</td>
</tr>
</table>
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

<%@ include file="/html/portlet/reverend_fun/init.jsp" %>

<c:choose>
	<c:when test="<%= windowState.equals(WindowState.NORMAL) %>">
		<table class="lfr-table">
		<tr>
			<td>

				<%
				String currentDate = ReverendFunUtil.getCurrentDate();

				Calendar currentCal = CalendarFactoryUtil.getCalendar();

				currentCal.setTime(dateFormat.parse(currentDate));
				%>

				<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" />"><img border="0" src="http://rev-fun.gospelcom.net/<%= currentCal.get(Calendar.YEAR) %>/<%= decimalFormat.format(currentCal.get(Calendar.MONTH) + 1) %>/<%= currentDate %>_sm.gif" width="72" /></a>
			</td>
			<td>
				Reverend Fun, daily humor for daily people!
			</td>
		</tr>
		</table>
	</c:when>
	<c:otherwise>

		<%
		String date = ParamUtil.getString(request, "date");

		if (!ReverendFunUtil.hasDate(date)) {
			date = ReverendFunUtil.getCurrentDate();
		}

		String previousDate = ReverendFunUtil.getPreviousDate(date);
		String nextDate = ReverendFunUtil.getNextDate(date);
		%>

		<table class="lfr-table">
		<tr>
			<td>
				<b><%= DateFormat.getDateInstance(DateFormat.LONG, locale).format(dateFormat.parse(date)) %></b>
			</td>
			<td align="right">
				<c:if test="<%= previousDate != null %>">
					<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="date" value="<%= previousDate %>" /></portlet:renderURL>"><liferay-ui:message key="previous" /></a>
				</c:if>

				<c:if test="<%= previousDate != null && nextDate != null %>">
					-
				</c:if>

				<c:if test="<%= nextDate != null %>">
					<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="date" value="<%= nextDate %>" /></portlet:renderURL>"><liferay-ui:message key="next" /></a>
				</c:if>
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />

				<img src="http://rev-fun.gospelcom.net/add_toon_info.php?date=<%= date %>" />
			</td>
		</tr>
		</table>
	</c:otherwise>
</c:choose>
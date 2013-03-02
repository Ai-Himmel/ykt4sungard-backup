<%
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
%>

<%@ include file="/html/common/init.jsp" %>

<c:if test="<%= ShutdownUtil.isInProcess() %>">
	<table border="0" cellpadding="1" cellspacing="0" width="<%= themeDisplay.getResTotal() %>">
	<tr>
		<td bgcolor="<%= colorScheme.getPortletMsgError() %>">
			<table border="0" cellpadding="8" cellspacing="0" width="100%">
			<tr>
				<td bgcolor="<%= colorScheme.getLayoutBg() %>">
					<font class="bg" size="2"><span class="bg-neg-alert">

					<%= LanguageUtil.get(pageContext, "maintenance-alert") %> &nbsp;&nbsp;&nbsp;<%= DateFormat.getTimeInstance(DateFormat.SHORT, locale).format(Time.getDate(new GregorianCalendar(timeZone))) %> <%= timeZone.getDisplayName(false, TimeZone.SHORT, locale) %><br><br>

					<%= LanguageUtil.format(pageContext, "the-portal-will-shutdown-for-maintenance-in-x-minutes", Long.toString(ShutdownUtil.getInProcess() / Time.MINUTE), false) %>

					</span></font>
				</td>
			</tr>

			<c:if test="<%= Validator.isNotNull(ShutdownUtil.getMessage()) %>">
				<tr>
					<td bgcolor="<%= colorScheme.getLayoutBg() %>">
						<font class="bg" size="2">
						<%= ShutdownUtil.getMessage() %>
						</font>
					</td>
				</tr>
			</c:if>

			</table>
		</td>
	</tr>
	</table>
</c:if>
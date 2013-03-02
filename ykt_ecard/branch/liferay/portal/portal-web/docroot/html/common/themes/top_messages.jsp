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

<%@ include file="/html/common/init.jsp" %>

<c:if test="<%= ShutdownUtil.isInProcess() %>">
	<div class="popup-alert-notice">
		<span class="notice-label"><liferay-ui:message key="maintenance-alert" /></span> <span class="notice-date"><%= DateFormat.getTimeInstance(DateFormat.SHORT, locale).format(Time.getDate(CalendarFactoryUtil.getCalendar(timeZone))) %> <%= timeZone.getDisplayName(false, TimeZone.SHORT, locale) %></span>
		<span class="notice-message"><%= LanguageUtil.format(pageContext, "the-portal-will-shutdown-for-maintenance-in-x-minutes", String.valueOf(ShutdownUtil.getInProcess() / Time.MINUTE), false) %></span>

		<c:if test="<%= Validator.isNotNull(ShutdownUtil.getMessage()) %>">
			<span class="custom-shutdown-message"><%= Html.escape(ShutdownUtil.getMessage()) %></span>
		</c:if>
	</div>
</c:if>

<c:if test="<%= themeDisplay.isImpersonated() %>">
	<div class="popup-alert-notice">
		<span class="notice-message">
			<c:choose>
				<c:when test="<%= themeDisplay.isSignedIn() %>">
					<%= LanguageUtil.format(pageContext, "hi-x-you-are-impersonating-x", new Object[] {realUser.getFullName(), user.getFullName()}) %>
				</c:when>
				<c:otherwise>
					<%= LanguageUtil.format(pageContext, "hi-x-you-are-impersonating-the-guest-user", new Object[] {realUser.getFullName()}) %>
				</c:otherwise>
			</c:choose>
		</span>

		<%= LanguageUtil.format(pageContext, "click-here-to-be-yourself-again", new Object[] {"<a href=\"" + PortalUtil.getLayoutURL(layout, themeDisplay, false) + "\">", "</a>"}) %>
	</div>
</c:if>
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

<c:if test="<%= themeDisplay.isSignedIn() && !PropsValues.SESSION_DISABLED %>">

	<%
	String autoUserId = CookieUtil.get(request.getCookies(), CookieKeys.ID);
	String autoPassword = CookieUtil.get(request.getCookies(), CookieKeys.PASSWORD);
	%>

	<c:if test="<%= Validator.isNull(autoUserId) || Validator.isNull(autoPassword) %>">
		<script type="text/javascript">

			<%
			int sessionTimeout = PropsValues.SESSION_TIMEOUT;
			int sessionTimeoutMinute = sessionTimeout * (int)Time.MINUTE;
			int sessionTimeoutWarning = PropsValues.SESSION_TIMEOUT_WARNING;
			int sessionTimeoutWarningMinute = sessionTimeoutWarning * (int)Time.MINUTE;
			int timeoutDiff = (sessionTimeout - sessionTimeoutWarning) * (int)Time.MINUTE;

			Calendar sessionTimeoutCal = CalendarFactoryUtil.getCalendar(timeZone);

			sessionTimeoutCal.add(Calendar.MILLISECOND, sessionTimeoutMinute);
			%>

			<c:if test="<%= sessionTimeoutWarning > 0 %>">
				Liferay.Session.init(
					{
						autoExtend: <%= PropsValues.SESSION_TIMEOUT_AUTO_EXTEND %>,
						timeout: <%= sessionTimeout %>,
						timeoutWarning: <%= sessionTimeoutWarning %>
					}
				);
			</c:if>
		</script>
	</c:if>
</c:if>
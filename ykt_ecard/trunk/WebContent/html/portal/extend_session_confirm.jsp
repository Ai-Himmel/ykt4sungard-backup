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

<%@ include file="/html/portal/init.jsp" %>

<%
int sessionTimeout = GetterUtil.getInteger(PropsUtil.get(PropsUtil.SESSION_TIMEOUT));
int sessionTimeoutWarning = GetterUtil.getInteger(PropsUtil.get(PropsUtil.SESSION_TIMEOUT_WARNING));
int sessionTimeoutWarningMinute = sessionTimeoutWarning * (int)Time.MINUTE;

Calendar sessionTimeoutCal = new GregorianCalendar(timeZone);
sessionTimeoutCal.add(Calendar.MILLISECOND, sessionTimeoutWarningMinute);
%>

<script language="JavaScript" event="onLoad()" for="window">
	setTimeout("sessionHasExpired()", <%= sessionTimeoutWarningMinute %>);
</script>

<script language="JavaScript">
	function sessionHasExpired() {
		document.getElementById("session_warning_text").innerHTML = "<%= UnicodeLanguageUtil.get(pageContext, "warning-due-to-inactivity-your-session-has-expired") %>";
		document.getElementById("session_btns").innerHTML = "";
	}
</script>

<form name="fm">

<table border="0" cellpadding="8" cellspacing="0" height="100%" width="100%">
<tr>
	<td align="center" valign="middle">
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td>
				<font class="bg" size="2"><span class="bg-neg-alert" id="session_warning_text">
				<%= LanguageUtil.format(pageContext, "warning-due-to-inactivity-your-session-will-expire", new Object[] {new Integer(sessionTimeoutWarning), DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.SHORT, locale).format(Time.getDate(sessionTimeoutCal)), timeZone.getDisplayName(false, TimeZone.SHORT, locale), new Integer(sessionTimeout)}, false) %>
				</span></font>
			</td>
		</tr>
		<tr>
			<td>
				<br>
			</td>
		</tr>
		<tr>
			<td align="center" id="session_btns">
				<input name="ok_btn" type="button" value="<%= LanguageUtil.get(pageContext, "OK") %>" onClick="opener.extendSession(); self.close();">

				<input name="cancel_btn" type="button" value="<%= LanguageUtil.get(pageContext, "Cancel") %>" onClick="self.close();">
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

</form>
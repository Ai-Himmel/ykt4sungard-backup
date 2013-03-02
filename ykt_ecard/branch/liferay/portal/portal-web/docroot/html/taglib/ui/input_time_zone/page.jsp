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
String name = namespace + request.getAttribute("liferay-ui:input-time-zone:name");
String value = (String)request.getAttribute("liferay-ui:input-time-zone:value");
boolean nullable = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time-zone:nullable"));
boolean daylight = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time-zone:daylight"));
int displayStyle = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:input-time-zone:displayStyle"));
boolean disabled = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time-zone:disabled"));

String[] timeZones = PropsUtil.getArray(PropsUtil.TIME_ZONES);

NumberFormat numberFormat = NumberFormat.getInstance(locale);
numberFormat.setMinimumIntegerDigits(2);
%>

<select <%= disabled ? "disabled" : "" %> name="<%= name %>">
	<c:if test="<%= nullable %>">
		<option value=""></option>
	</c:if>

	<%
	for (int i = 0; i < timeZones.length; i++) {
		TimeZone curTimeZone = TimeZone.getTimeZone(timeZones[i]);

		int rawOffset = curTimeZone.getRawOffset();
		String offset = StringPool.BLANK;

		if (rawOffset > 0) {
			offset = "+";
		}

		if (rawOffset != 0) {
			String offsetHour = numberFormat.format(rawOffset / Time.HOUR);
			String offsetMinute = numberFormat.format(Math.abs(rawOffset % Time.HOUR) / Time.MINUTE);

			offset += offsetHour + ":" + offsetMinute;
		}
	%>

		<option <%= value.equals(curTimeZone.getID()) ? "selected" : "" %> value="<%= curTimeZone.getID() %>">(GMT <%= offset %>) <%= curTimeZone.getDisplayName(daylight, displayStyle, locale) %></option>

	<%
	}
	%>

</select>
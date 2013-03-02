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
String hourParam = namespace + request.getAttribute("liferay-ui:input-time:hourParam");
int hourValue = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:input-time:hourValue"));
boolean hourNullable = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time:hourNullable"));
String minuteParam = namespace + request.getAttribute("liferay-ui:input-time:minuteParam");
int minuteValue = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:input-time:minuteValue"));
int minuteInterval = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:input-time:minuteInterval"));
boolean minuteNullable = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time:minuteNullable"));
String amPmParam = namespace + request.getAttribute("liferay-ui:input-time:amPmParam");
int amPmValue = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:input-time:amPmValue"));
boolean amPmNullable = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time:amPmNullable"));
boolean disabled = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-time:disabled"));

NumberFormat numberFormat = NumberFormat.getInstance(locale);
numberFormat.setMinimumIntegerDigits(2);
%>

<select <%= disabled ? "disabled" : "" %> name="<%= hourParam %>">
	<c:if test="<%= hourNullable %>">
		<option value=""></option>
	</c:if>

	<%
	for (int i = 0; i < 12; i++) {
	%>

		<option <%= (hourValue == i) ? "selected" : "" %> value="<%= i %>"><%= (i == 0) ? "12" : String.valueOf(i) %></option>

	<%
	}
	%>

</select>

<select <%= disabled ? "disabled" : "" %> name="<%= minuteParam %>">
	<c:if test="<%= minuteNullable %>">
		<option value=""></option>
	</c:if>

	<%
	for (int i = 0; i < 60; i++) {
		String minute = numberFormat.format(i);
	%>

		<c:if test="<%= (minuteInterval == 0) || ((i % minuteInterval) == 0) %>">
			<option <%= (minuteValue == i) ? "selected" : "" %> value="<%= i %>">:<%= minute %></option>
		</c:if>

	<%
	}
	%>

</select>

<select <%= disabled ? "disabled" : "" %> name="<%= amPmParam %>">
	<c:if test="<%= amPmNullable %>">
		<option value=""></option>
	</c:if>

	<option <%= (amPmValue == Calendar.AM) ? "selected" : "" %> value="<%= Calendar.AM %>">AM</option>
	<option <%= (amPmValue == Calendar.PM) ? "selected" : "" %> value="<%= Calendar.PM %>">PM</option>
</select>
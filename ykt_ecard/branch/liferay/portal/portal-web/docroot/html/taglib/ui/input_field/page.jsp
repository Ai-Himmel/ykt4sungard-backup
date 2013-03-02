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

<%@ page import="com.liferay.portal.model.impl.BaseModelImpl" %>

<%
String formName = (String)request.getAttribute("liferay-ui:input-field:formName");
String model = (String)request.getAttribute("liferay-ui:input-field:model");
Object bean = request.getAttribute("liferay-ui:input-field:bean");
String field = (String)request.getAttribute("liferay-ui:input-field:field");
String fieldParam = (String)request.getAttribute("liferay-ui:input-field:fieldParam");
Object defaultValue = request.getAttribute("liferay-ui:input-field:defaultValue");
boolean disabled = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-field:disabled"));

String type = ModelHintsUtil.getType(model, field);
Map hints = ModelHintsUtil.getHints(model, field);
%>

<c:if test="<%= type != null %>">
	<c:choose>
		<c:when test='<%= type.equals("boolean") %>'>

			<%
			boolean defaultBoolean = GetterUtil.DEFAULT_BOOLEAN;

			if (defaultValue != null) {
				defaultBoolean = ((Boolean)defaultValue).booleanValue();
			}
			else {
				if (hints != null) {
					defaultBoolean = GetterUtil.getBoolean((String)hints.get("default-value"));
				}
			}

			boolean value = BeanParamUtil.getBoolean(bean, request, field, defaultBoolean);
			%>

			<liferay-ui:input-checkbox formName="<%= formName %>" param="<%= field %>" defaultValue="<%= value %>" disabled="<%= disabled %>" />
		</c:when>
		<c:when test='<%= type.equals("Date") %>'>

			<%
			if (fieldParam == null) {
				fieldParam = field;
			}

			Calendar cal = (Calendar)defaultValue;

			int month = ParamUtil.getInteger(request, fieldParam + "Month", -1);

			if ((month == -1) && (cal != null)) {
				month = cal.get(Calendar.MONTH);
			}

			boolean monthNullable = false;

			if (hints != null) {
				monthNullable = GetterUtil.getBoolean((String)hints.get("month-nullable"), monthNullable);
			}

			int day = ParamUtil.getInteger(request, fieldParam + "Day", -1);

			if ((day == -1) && (cal != null)) {
				day = cal.get(Calendar.DATE);
			}

			boolean dayNullable = false;

			if (hints != null) {
				dayNullable = GetterUtil.getBoolean((String)hints.get("day-nullable"), dayNullable);
			}

			int year = ParamUtil.getInteger(request, fieldParam + "Year", -1);

			if ((year == -1) && (cal != null)) {
				year = cal.get(Calendar.YEAR);
			}

			boolean yearNullable = false;

			if (hints != null) {
				yearNullable = GetterUtil.getBoolean((String)hints.get("year-nullable"), yearNullable);
			}

			int yearRangeDelta = 5;

			if (hints != null) {
				yearRangeDelta = GetterUtil.getInteger((String)hints.get("year-range-delta"), yearRangeDelta);
			}

			int yearRangeStart = year - yearRangeDelta;
			int yearRangeEnd = year + yearRangeDelta;

			if (year == -1) {
				Calendar now = CalendarFactoryUtil.getCalendar(timeZone, locale);

				yearRangeStart = now.get(Calendar.YEAR) - yearRangeDelta;
				yearRangeEnd = now.get(Calendar.YEAR) + yearRangeDelta;
			}

			int firstDayOfWeek = Calendar.SUNDAY - 1;

			if (cal != null) {
				firstDayOfWeek = cal.getFirstDayOfWeek() - 1;
			}

			int hour = ParamUtil.getInteger(request, fieldParam + "Hour", -1);

			if ((hour == -1) && (cal != null)) {
				hour = cal.get(Calendar.HOUR);
			}

			int minute = ParamUtil.getInteger(request, fieldParam + "Minute", -1);

			if ((minute == -1) && (cal != null)) {
				minute = cal.get(Calendar.MINUTE);
			}

			int amPm = ParamUtil.getInteger(request, fieldParam + "AmPm", -1);

			if ((amPm == -1) && (cal != null)) {
				amPm = cal.get(Calendar.AM_PM);
			}

			boolean showTime = true;

			if (hints != null) {
				showTime = GetterUtil.getBoolean((String)hints.get("show-time"), showTime);
			}
			%>

			<liferay-ui:input-date
 				formName="<%= formName %>"
				monthParam='<%= fieldParam + "Month" %>'
				monthValue="<%= month %>"
				monthNullable="<%= monthNullable %>"
				dayParam='<%= fieldParam + "Day" %>'
				dayValue="<%= day %>"
				dayNullable="<%= dayNullable %>"
				yearParam='<%= fieldParam + "Year" %>'
				yearValue="<%= year %>"
				yearNullable="<%= yearNullable %>"
				yearRangeStart="<%= yearRangeStart %>"
				yearRangeEnd="<%= yearRangeEnd %>"
				firstDayOfWeek="<%= firstDayOfWeek %>"
				imageInputId='<%= fieldParam + "ImageInputId" %>'
 				disabled="<%= disabled %>"
			/>

			<c:if test="<%= showTime %>">
				&nbsp;

				<liferay-ui:input-time
					hourParam='<%= fieldParam + "Hour" %>'
					hourValue="<%= hour %>"
					minuteParam='<%= fieldParam + "Minute" %>'
					minuteValue="<%= minute %>"
					minuteInterval="1"
					amPmParam='<%= fieldParam + "AmPm" %>'
					amPmValue="<%= amPm %>"
					disabled="<%= disabled %>"
				/>
			</c:if>
		</c:when>
		<c:when test='<%= type.equals("double") || type.equals("int") || type.equals("String") %>'>

			<%
			String defaultString = GetterUtil.DEFAULT_STRING;

			if (defaultValue != null) {
				defaultString = (String)defaultValue;
			}

			String value = null;

			if (fieldParam == null) {
				fieldParam = namespace + field;

				if (type.equals("double")) {
					value = String.valueOf(BeanParamUtil.getDouble(bean, request, field, GetterUtil.DEFAULT_DOUBLE));
				}
				else if (type.equals("int")) {
					value = String.valueOf(BeanParamUtil.getInteger(bean, request, field, GetterUtil.DEFAULT_INTEGER));
				}
				else {
					value = BeanParamUtil.getString(bean, request, field, defaultString);

					String httpValue = request.getParameter(field);

					if (httpValue != null) {
						value = httpValue;
					}
				}
			}
			else {
				fieldParam = namespace + fieldParam;
				value = defaultString;
			}

			boolean autoEscape = true;

			if (hints != null) {
				autoEscape = GetterUtil.getBoolean((String)hints.get("auto-escape"), true);
			}

			if (autoEscape) {
				value = Html.escape(value);
			}

			String displayHeight = ModelHintsDefaults.TEXT_DISPLAY_HEIGHT;
			String displayWidth = ModelHintsDefaults.TEXT_DISPLAY_WIDTH;
			String maxLength = ModelHintsDefaults.TEXT_MAX_LENGTH;
			boolean upperCase = false;
			boolean checkTab = false;

			if (hints != null) {
				displayHeight = GetterUtil.getString((String)hints.get("display-height"), displayHeight);
				displayWidth = GetterUtil.getString((String)hints.get("display-width"), displayWidth);
				maxLength = GetterUtil.getString((String)hints.get("max-length"), maxLength);
				upperCase = GetterUtil.getBoolean((String)hints.get("upper-case"), upperCase);
				checkTab = GetterUtil.getBoolean((String)hints.get("check-tab"), checkTab);
			}
			%>

			<c:choose>
				<c:when test='<%= displayHeight.equals(ModelHintsDefaults.TEXT_DISPLAY_HEIGHT) %>'>

					<%
					if (Validator.isNotNull(value)) {
						int maxLengthInt = GetterUtil.getInteger(maxLength);

						if (value.length() > maxLengthInt) {
							value = value.substring(0, maxLengthInt);
						}
					}
					%>

					<input <%= disabled ? "disabled" : "" %> id="<%= fieldParam %>" name="<%= fieldParam %>" style="width: <%= displayWidth %>px; <%= upperCase ? "text-transform: uppercase;" : "" %>" type="text" value="<%= value %>" onKeyPress="Liferay.Util.checkMaxLength(this, <%= maxLength %>);">
				</c:when>
				<c:otherwise>
					<textarea <%= disabled ? "disabled" : "" %> id="<%= fieldParam %>" name="<%= fieldParam %>" style="height: <%= displayHeight %><%= Validator.isDigit(displayHeight) ? "px" : "" %>; width: <%= displayWidth %><%= Validator.isDigit(displayWidth) ? "px" : "" %>;" wrap="soft" onKeyDown="<%= checkTab ? "Liferay.Util.checkTab(this); " : "" %> Liferay.Util.disableEsc();" onKeyPress="Liferay.Util.checkMaxLength(this, <%= maxLength %>);"><%= value %></textarea>
				</c:otherwise>
			</c:choose>
		</c:when>
	</c:choose>
</c:if>
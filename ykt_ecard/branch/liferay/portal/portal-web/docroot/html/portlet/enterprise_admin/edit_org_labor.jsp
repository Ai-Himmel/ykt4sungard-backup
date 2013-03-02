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

<%@ include file="/html/portlet/enterprise_admin/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

OrgLabor orgLabor = (OrgLabor)request.getAttribute(WebKeys.ORG_LABOR);

long orgLaborId = BeanParamUtil.getLong(orgLabor, request, "orgLaborId");

long organizationId = BeanParamUtil.getLong(orgLabor, request, "organizationId");
int typeId = BeanParamUtil.getInteger(orgLabor, request, "typeId");
int sunOpen = BeanParamUtil.getInteger(orgLabor, request, "sunOpen", -1);
int sunClose = BeanParamUtil.getInteger(orgLabor, request, "sunClose", -1);
int monOpen = BeanParamUtil.getInteger(orgLabor, request, "monOpen", -1);
int monClose = BeanParamUtil.getInteger(orgLabor, request, "monClose", -1);
int tueOpen = BeanParamUtil.getInteger(orgLabor, request, "tueOpen", -1);
int tueClose = BeanParamUtil.getInteger(orgLabor, request, "tueClose", -1);
int wedOpen = BeanParamUtil.getInteger(orgLabor, request, "wedOpen", -1);
int wedClose = BeanParamUtil.getInteger(orgLabor, request, "wedClose", -1);
int thuOpen = BeanParamUtil.getInteger(orgLabor, request, "thuOpen", -1);
int thuClose = BeanParamUtil.getInteger(orgLabor, request, "thuClose", -1);
int friOpen = BeanParamUtil.getInteger(orgLabor, request, "friOpen", -1);
int friClose = BeanParamUtil.getInteger(orgLabor, request, "friClose", -1);
int satOpen = BeanParamUtil.getInteger(orgLabor, request, "satOpen", -1);
int satClose = BeanParamUtil.getInteger(orgLabor, request, "satClose", -1);

DateFormat timeFormat = new SimpleDateFormat("HH:mm", locale);
%>

<script type="text/javascript">
	function <portlet:namespace />saveOrgLabor() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= orgLabor == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_org_labor" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveOrgLabor(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />orgLaborId" type="hidden" value="<%= orgLaborId %>" />
<input name="<portlet:namespace />organizationId" type="hidden" value="<%= organizationId %>" />

<liferay-ui:tabs
	names="service"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= NoSuchListTypeException.class %>" message="please-select-a-type" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="type" />
	</td>
	<td>
		<select name="<portlet:namespace />typeId">
			<option value=""></option>

			<%
			List orgLaborTypes = ListTypeServiceUtil.getListTypes(ListTypeImpl.ORGANIZATION_SERVICE);

			for (int i = 0; i < orgLaborTypes.size(); i++) {
				ListType suffix = (ListType)orgLaborTypes.get(i);
			%>

				<option <%= suffix.getListTypeId() == typeId ? "selected" : "" %> value="<%= String.valueOf(suffix.getListTypeId()) %>"><%= LanguageUtil.get(pageContext, suffix.getName()) %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
</table>

<br />

<table class="lfr-table">

<%
String[] days = CalendarUtil.getDays(locale);

for (int i = 0; i < days.length; i++) {
	String curParam = null;
	int curOpen = 0;
	int curClose = 0;

	if (i == 0) {
		curParam = "sun";
		curOpen = sunOpen;
		curClose = sunClose;
	}
	else if (i == 1) {
		curParam = "mon";
		curOpen = monOpen;
		curClose = monClose;
	}
	else if (i == 2) {
		curParam = "tue";
		curOpen = tueOpen;
		curClose = tueClose;
	}
	else if (i == 3) {
		curParam = "wed";
		curOpen = wedOpen;
		curClose = wedClose;
	}
	else if (i == 4) {
		curParam = "thu";
		curOpen = thuOpen;
		curClose = thuClose;
	}
	else if (i == 5) {
		curParam = "fri";
		curOpen = friOpen;
		curClose = friClose;
	}
	else if (i == 6) {
		curParam = "sat";
		curOpen = satOpen;
		curClose = satClose;
	}
%>

	<tr>
		<td>
			<%= days[i] %>
		</td>
		<td>
			<liferay-ui:message key="open" />
		</td>
		<td>
			<select name="<portlet:namespace /><%= curParam %>Open">
				<option value="-1"></option>

				<%
				Calendar cal = CalendarFactoryUtil.getCalendar();

				cal.set(Calendar.HOUR_OF_DAY, 0);
				cal.set(Calendar.MINUTE, 0);
				cal.set(Calendar.SECOND, 0);
				cal.set(Calendar.MILLISECOND, 0);

				int today = cal.get(Calendar.DATE);

				while (cal.get(Calendar.DATE) == today) {
					String timeOfDayDisplay = timeFormat.format(cal.getTime());
					int timeOfDayValue = GetterUtil.getInteger(StringUtil.replace(timeOfDayDisplay, StringPool.COLON, StringPool.BLANK));

					cal.add(Calendar.MINUTE, 30);
				%>

					<option <%= curOpen == timeOfDayValue ? "selected" : "" %> value="<%= timeOfDayValue %>"><%= timeOfDayDisplay %></option>

				<%
				}
				%>

			</select>
		</td>
		<td>
			<liferay-ui:message key="close" />
		</td>
		<td>
			<select name="<portlet:namespace /><%= curParam %>Close">
				<option value="-1"></option>

				<%
				cal.set(Calendar.HOUR_OF_DAY, 0);
				cal.set(Calendar.MINUTE, 0);
				cal.set(Calendar.SECOND, 0);
				cal.set(Calendar.MILLISECOND, 0);

				today = cal.get(Calendar.DATE);

				while (cal.get(Calendar.DATE) == today) {
					String timeOfDayDisplay = timeFormat.format(cal.getTime());
					int timeOfDayValue = GetterUtil.getInteger(StringUtil.replace(timeOfDayDisplay, StringPool.COLON, StringPool.BLANK));

					cal.add(Calendar.MINUTE, 30);
				%>

					<option <%= curClose == timeOfDayValue ? "selected" : "" %> value="<%= timeOfDayValue %>"><%= timeOfDayDisplay %></option>

				<%
				}
				%>

			</select>
		</td>
	</tr>

<%
}
%>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />typeId);
	</script>
</c:if>
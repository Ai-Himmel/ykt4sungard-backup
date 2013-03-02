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

Website website = (Website)request.getAttribute(WebKeys.WEBSITE);

long websiteId = BeanParamUtil.getLong(website, request, "websiteId");

String className = ParamUtil.getString(request, "className");
long classPK = BeanParamUtil.getLong(website, request, "classPK");

int typeId = BeanParamUtil.getInteger(website, request, "typeId");
%>

<script type="text/javascript">
	function <portlet:namespace />saveWebsite() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= website == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_website" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveWebsite(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />websiteId" type="hidden" value="<%= String.valueOf(websiteId) %>" />
<input name="<portlet:namespace />className" type="hidden" value="<%= className %>" />
<input name="<portlet:namespace />classPK" type="hidden" value="<%= classPK %>" />

<liferay-ui:tabs
	names="website"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= NoSuchListTypeException.class %>" message="please-select-a-type" />
<liferay-ui:error exception="<%= WebsiteURLException.class %>" message="please-enter-a-valid-url" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= Website.class %>" bean="<%= website %>" field="url" />
	</td>
	<td>
		<liferay-ui:message key="type" />
	</td>
	<td>
		<select name="<portlet:namespace />typeId">
			<option value=""></option>

			<%
			List websiteTypes = ListTypeServiceUtil.getListTypes(className + ListTypeImpl.WEBSITE);

			for (int i = 0; i < websiteTypes.size(); i++) {
				ListType suffix = (ListType)websiteTypes.get(i);
			%>

				<option <%= suffix.getListTypeId() == typeId ? "selected" : "" %> value="<%= String.valueOf(suffix.getListTypeId()) %>"><%= LanguageUtil.get(pageContext, suffix.getName()) %></option>

			<%
			}
			%>

		</select>
	</td>
	<td>
		<liferay-ui:message key="primary" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= Website.class %>" bean="<%= website %>" field="primary" />
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />url);
	</script>
</c:if>
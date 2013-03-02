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
boolean editable = ParamUtil.getBoolean(request, "editable");

String redirect = ParamUtil.getString(request, "redirect");

Organization organization = (Organization)request.getAttribute(WebKeys.ORGANIZATION);

SearchContainer searchContainer = new SearchContainer();

List headerNames = new ArrayList();

headerNames.add("type");

if (editable) {
	headerNames.add(StringPool.BLANK);
}

searchContainer.setHeaderNames(headerNames);
searchContainer.setEmptyResultsMessage("the-organization-does-not-have-any-services");

List results = OrgLaborServiceUtil.getOrgLabors(organization.getOrganizationId());

searchContainer.setTotal(results.size());

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	OrgLabor orgLabor = (OrgLabor)results.get(i);

	ResultRow row = new ResultRow(orgLabor, orgLabor.getOrgLaborId(), i);

	row.addText(orgLabor.getType().getName());

	if (editable) {
		row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/org_labor_action.jsp");
	}

	resultRows.add(row);
}
%>

<c:if test="<%= editable %>">
	<input type="button" value="<liferay-ui:message key="add" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_org_labor" /><portlet:param name="redirect" value="<%= redirect %>" /><portlet:param name="organizationId" value="<%= String.valueOf(organization.getOrganizationId()) %>" /></portlet:renderURL>';" /><br />

	<br />
</c:if>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" paginate="<%= false %>" />

<c:if test="<%= editable || (results.size() > 0) %>">
	<br />
</c:if>
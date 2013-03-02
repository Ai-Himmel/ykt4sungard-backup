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
themeDisplay.setIncludeServiceJs(true);

OrganizationSearch searchContainer = (OrganizationSearch)request.getAttribute("liferay-ui:search:searchContainer");

OrganizationDisplayTerms displayTerms = (OrganizationDisplayTerms)searchContainer.getDisplayTerms();
%>

<liferay-ui:search-toggle
	id="toggle_id_enterprise_admin_organization_search"
	displayTerms="<%= displayTerms %>"
>
	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="name" />
		</td>
		<td>
			<liferay-ui:message key="street" />
		</td>
		<td>
			<liferay-ui:message key="city" />
		</td>
		<td>
			<liferay-ui:message key="zip" />
		</td>
	</tr>
	<tr>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.NAME %>" size="20" type="text" value="<%= Html.escape(displayTerms.getName()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.STREET %>" size="20" type="text" value="<%= Html.escape(displayTerms.getStreet()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.CITY %>" size="20" type="text" value="<%= Html.escape(displayTerms.getCity()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.ZIP %>" size="20" type="text" value="<%= Html.escape(displayTerms.getZip()) %>" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="type" />
		</td>
		<td>
			<liferay-ui:message key="country" />
		</td>
		<td>
			<liferay-ui:message key="region" />
		</td>
		<td colspan="2"></td>
	</tr>
	<tr>
		<td>
			<select name="<portlet:namespace /><%= displayTerms.TYPE %>">
				<option <%= (displayTerms.getType() == OrganizationImpl.ANY_TYPE) ? "selected" : "" %> value="<%= OrganizationImpl.ANY_TYPE %>"><liferay-ui:message key="any" /></option>
				<option <%= (displayTerms.getType() == OrganizationImpl.TYPE_REGULAR) ? "selected" : "" %> value="<%= OrganizationImpl.TYPE_REGULAR %>"><liferay-ui:message key="regular" /></option>
				<option <%= (displayTerms.getType() == OrganizationImpl.TYPE_LOCATION) ? "selected" : "" %> value="<%= OrganizationImpl.TYPE_LOCATION %>"><liferay-ui:message key="location" /></option>
			</select>
		</td>
		<td>
			<select id="<portlet:namespace /><%= displayTerms.COUNTRY_ID %>" name="<portlet:namespace /><%= displayTerms.COUNTRY_ID %>"></select>
		</td>
		<td>
			<select id="<portlet:namespace /><%= displayTerms.REGION_ID %>" name="<portlet:namespace /><%= displayTerms.REGION_ID %>"></select>
		</td>
		<td colspan="2"></td>
	</tr>
	</table>
</liferay-ui:search-toggle>

<br />

<div>
	<input type="submit" value="<liferay-ui:message key='<%= "search-" + tabs1 %>' />" />

	<%
	boolean showButtons = false;

	if (portletName.equals(PortletKeys.ENTERPRISE_ADMIN) && !windowState.equals(LiferayWindowState.POP_UP)) {
		showButtons = true;
	}
	%>

	<c:if test="<%= showButtons %>">
		<c:if test="<%= PortalPermissionUtil.contains(permissionChecker, ActionKeys.ADD_ORGANIZATION) %>">
			<input type="button" value="<liferay-ui:message key="add-organization" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value='/enterprise_admin/edit_organization' /></portlet:renderURL>&<portlet:namespace />redirect=' + encodeURIComponent(document.<portlet:namespace />fm.<portlet:namespace />organizationsRedirect.value);" />
		</c:if>
	</c:if>
</div>

<%
Organization organization = null;

if (displayTerms.getParentOrganizationId() > 0) {
	try {
		organization = OrganizationLocalServiceUtil.getOrganization(displayTerms.getParentOrganizationId());
	}
	catch (NoSuchOrganizationException nsoe) {
	}
}
%>

<c:if test="<%= organization != null %>">
	<input name="<portlet:namespace /><%= UserDisplayTerms.ORGANIZATION_ID %>" type="hidden" value="<%= organization.getOrganizationId() %>" />

	<br />

	<liferay-ui:message key="filter-by-organization" />: <%= organization.getName() %><br />
</c:if>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.NAME %>);
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.KEYWORDS %>);
	</script>
</c:if>

<script type="text/javascript">
	new Liferay.DynamicSelect(
		[
			{
				select: "<portlet:namespace /><%= displayTerms.COUNTRY_ID %>",
				selectId: "countryId",
				selectDesc: "name",
				selectVal: "<%= displayTerms.getCountryId() %>",
				selectData: function(callback) {
					Liferay.Service.Portal.Country.getCountries(
						{
							active: true
						},
						callback
					);
				}
			},
			{
				select: "<portlet:namespace /><%= displayTerms.REGION_ID %>",
				selectId: "regionId",
				selectDesc: "name",
				selectVal: "<%= displayTerms.getRegionId() %>",
				selectData: function(callback, selectKey) {
					Liferay.Service.Portal.Region.getRegions(
						{
							countryId: selectKey,
							active: true
						},
						callback
					);
				}
			}
		]
	);
</script>
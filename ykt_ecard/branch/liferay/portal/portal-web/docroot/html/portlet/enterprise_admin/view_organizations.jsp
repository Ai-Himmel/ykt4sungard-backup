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
PortletURL portletURL = (PortletURL)request.getAttribute("view.jsp-portletURL");
%>

<input name="<portlet:namespace />deleteOrganizationIds" type="hidden" value="" />

<liferay-ui:error exception="<%= RequiredOrganizationException.class %>" message="you-cannot-delete-organizations-that-have-suborganizations-or-users" />

<%
boolean showButtons = false;

if (portletName.equals(PortletKeys.ENTERPRISE_ADMIN)) {
	showButtons = true;
}

OrganizationSearch searchContainer = new OrganizationSearch(renderRequest, portletURL);

List headerNames = searchContainer.getHeaderNames();

headerNames.add(StringPool.BLANK);

if (showButtons) {
	RowChecker rowChecker = new RowChecker(renderResponse);

	searchContainer.setRowChecker(rowChecker);
}

portletURL.setParameter(searchContainer.getCurParam(), String.valueOf(searchContainer.getCurValue()));
%>

<input name="<portlet:namespace />organizationsRedirect" type="hidden" value="<%= portletURL.toString() %>" />

<liferay-ui:search-form
		page="/html/portlet/enterprise_admin/organization_search.jsp"
		searchContainer="<%= searchContainer %>"
/>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

	<%
	OrganizationSearchTerms searchTerms = (OrganizationSearchTerms)searchContainer.getSearchTerms();

	LinkedHashMap orgParams = new LinkedHashMap();

	if (portletName.equals(PortletKeys.ORGANIZATION_ADMIN)) {
		List manageableOrganizations = OrganizationLocalServiceUtil.getManageableOrganizations(user.getUserId());

		Long[] manageableOrganizationIds = EnterpriseAdminUtil.getOrganizationIds(manageableOrganizations);

		orgParams.put("organizations", manageableOrganizationIds);
	}

	long parentOrganizationId = ParamUtil.getLong(request, "parentOrganizationId", OrganizationImpl.DEFAULT_PARENT_ORGANIZATION_ID);

	if (parentOrganizationId <= 0) {
		parentOrganizationId = OrganizationImpl.ANY_PARENT_ORGANIZATION_ID;
	}

	int total = 0;

	if (searchTerms.isAdvancedSearch()) {
		total = OrganizationLocalServiceUtil.searchCount(company.getCompanyId(), parentOrganizationId, searchTerms.getName(), searchTerms.getType(), searchTerms.getStreet(), searchTerms.getCity(), searchTerms.getZip(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams, searchTerms.isAndOperator());
	}
	else {
		total = OrganizationLocalServiceUtil.searchCount(company.getCompanyId(), parentOrganizationId, searchTerms.getKeywords(), searchTerms.getType(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams);
	}

	searchContainer.setTotal(total);

	List results = null;

	if (searchTerms.isAdvancedSearch()) {
		results = OrganizationLocalServiceUtil.search(company.getCompanyId(), parentOrganizationId, searchTerms.getName(), searchTerms.getType(), searchTerms.getStreet(), searchTerms.getCity(), searchTerms.getZip(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams, searchTerms.isAndOperator(), searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());
	}
	else {
		results = OrganizationLocalServiceUtil.search(company.getCompanyId(), parentOrganizationId, searchTerms.getKeywords(), searchTerms.getType(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());
	}

	searchContainer.setResults(results);
	%>

	<div class="separator"><!-- --></div>

	<c:if test="<%= showButtons %>">
		<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />deleteOrganizations();" />

		<br /><br />
	</c:if>

	<%
	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.size(); i++) {
		Organization organization = (Organization)results.get(i);

		ResultRow row = new ResultRow(organization, organization.getOrganizationId(), i);

		PortletURL rowURL = renderResponse.createRenderURL();

		rowURL.setWindowState(WindowState.MAXIMIZED);

		rowURL.setParameter("struts_action", "/enterprise_admin/edit_organization");
		rowURL.setParameter("redirect", searchContainer.getIteratorURL().toString());
		rowURL.setParameter("organizationId", String.valueOf(organization.getOrganizationId()));

		// Name

		row.addText(organization.getName(), rowURL);

		// Parent organization

		String parentOrganizationName = StringPool.BLANK;

		if (organization.getParentOrganizationId() > 0) {
			try {
				Organization parentOrganization = OrganizationLocalServiceUtil.getOrganization(organization.getParentOrganizationId());

				parentOrganizationName = parentOrganization.getName();
			}
			catch (Exception e) {
			}
		}

		row.addText(parentOrganizationName);

		// Type

		row.addText(LanguageUtil.get(pageContext, organization.getTypeLabel()));

		// City

		Address address = organization.getAddress();

		row.addText(address.getCity(), rowURL);

		// Region

		String regionName = address.getRegion().getName();

		if (Validator.isNull(regionName)) {
			try {
				Region region = RegionServiceUtil.getRegion(organization.getRegionId());

				regionName = LanguageUtil.get(pageContext, region.getName());
			}
			catch (NoSuchRegionException nsce) {
			}
		}

		row.addText(regionName, rowURL);

		// Country

		String countryName = address.getCountry().getName();

		if (Validator.isNull(countryName)) {
			try {
				Country country = CountryServiceUtil.getCountry(organization.getCountryId());

				countryName = LanguageUtil.get(pageContext, country.getName());
			}
			catch (NoSuchCountryException nsce) {
			}
		}

		row.addText(countryName, rowURL);

		// Action

		row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/organization_action.jsp");

		// Add result row

		resultRows.add(row);
	}
	%>

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
</c:if>
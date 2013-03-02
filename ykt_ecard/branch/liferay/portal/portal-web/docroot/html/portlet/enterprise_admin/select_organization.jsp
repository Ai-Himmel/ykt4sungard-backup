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

<script type="text/javascript">
	function <portlet:namespace/>setOrgType(url, type) {
		if (type == 'locations') {
			url += '&<portlet:namespace/>parentOrganizationIds=' + opener.<portlet:namespace/>getSelectedOrganizationIds();
		}

		location.href = url;
	}
</script>

<form method="post" name="<portlet:namespace />fm">

<liferay-ui:tabs names="organizations" />

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(LiferayWindowState.POP_UP);

portletURL.setParameter("struts_action", "/enterprise_admin/select_organization");

OrganizationSearch searchContainer = new OrganizationSearch(renderRequest, portletURL);

List headerNames = new ArrayList();

headerNames.add("name");

headerNames.add("parent-organization");

headerNames.add("type");
headerNames.add("city");
headerNames.add("region");
headerNames.add("country");

searchContainer.setHeaderNames(headerNames);
%>

<liferay-ui:search-form
	page="/html/portlet/enterprise_admin/organization_search.jsp"
	searchContainer="<%= searchContainer %>"
/>

<%
OrganizationSearchTerms searchTerms = (OrganizationSearchTerms)searchContainer.getSearchTerms();

LinkedHashMap orgParams = new LinkedHashMap();

if (portletName.equals(PortletKeys.ORGANIZATION_ADMIN)) {
	List manageableOrganizations = OrganizationLocalServiceUtil.getManageableOrganizations(user.getUserId());

	Long[] manageableOrganizationIds = EnterpriseAdminUtil.getOrganizationIds(manageableOrganizations);

	orgParams.put("organizations", manageableOrganizationIds);
}

int total = 0;

if (searchTerms.isAdvancedSearch()) {
	total = OrganizationLocalServiceUtil.searchCount(company.getCompanyId(), OrganizationImpl.ANY_PARENT_ORGANIZATION_ID, searchTerms.getName(), searchTerms.getType(), searchTerms.getStreet(), searchTerms.getCity(), searchTerms.getZip(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams, searchTerms.isAndOperator());
}
else {
	total = OrganizationLocalServiceUtil.searchCount(company.getCompanyId(), OrganizationImpl.ANY_PARENT_ORGANIZATION_ID, searchTerms.getKeywords(), searchTerms.getType(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams);
}

searchContainer.setTotal(total);

List results = null;

if (searchTerms.isAdvancedSearch()) {
	results = OrganizationLocalServiceUtil.search(company.getCompanyId(), OrganizationImpl.ANY_PARENT_ORGANIZATION_ID, searchTerms.getName(), searchTerms.getType(), searchTerms.getStreet(), searchTerms.getCity(), searchTerms.getZip(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams, searchTerms.isAndOperator(), searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());
}
else {
	results = OrganizationLocalServiceUtil.search(company.getCompanyId(), OrganizationImpl.ANY_PARENT_ORGANIZATION_ID, searchTerms.getKeywords(), searchTerms.getType(), searchTerms.getRegionIdObj(), searchTerms.getCountryIdObj(), orgParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());
}

searchContainer.setResults(results);
%>

<div class="separator"><!-- --></div>

<%
List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	Organization organization = (Organization)results.get(i);

	ResultRow row = new ResultRow(organization, organization.getOrganizationId(), i);

	StringMaker sm = new StringMaker();

	sm.append("javascript: opener.");
	sm.append(renderResponse.getNamespace());
	sm.append("selectOrganization('");
	sm.append(organization.getOrganizationId());
	sm.append("', '");
	sm.append(UnicodeFormatter.toString(organization.getName()));
	sm.append("');");
	sm.append("window.close();");

	String rowHREF = sm.toString();

	// Name

	row.addText(organization.getName(), rowHREF);

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

	// Address

	Address address = organization.getAddress();

	row.addText(address.getCity(), rowHREF);
	row.addText(address.getRegion().getName(), rowHREF);
	row.addText(address.getCountry().getName(), rowHREF);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

</form>

<script type="text/javascript">
	Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name);
</script>
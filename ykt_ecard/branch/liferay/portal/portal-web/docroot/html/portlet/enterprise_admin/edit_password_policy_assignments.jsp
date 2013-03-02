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
String tabs2 = ParamUtil.getString(request, "tabs2", "users");
String tabs3 = ParamUtil.getString(request, "tabs3", "current");

String cur = ParamUtil.getString(request, "cur");

String redirect = ParamUtil.getString(request, "redirect");

PasswordPolicy passwordPolicy = (PasswordPolicy)request.getAttribute(WebKeys.PASSWORD_POLICY);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/enterprise_admin/edit_password_policy_assignments");
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("tabs3", tabs3);
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("passwordPolicyId", String.valueOf(passwordPolicy.getPasswordPolicyId()));
%>

<script type="text/javascript">
	function <portlet:namespace />updatePasswordPolicyOrganizations(assignmentsRedirect) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "password_policy_organizations";
		document.<portlet:namespace />fm.<portlet:namespace />assignmentsRedirect.value = assignmentsRedirect;
		document.<portlet:namespace />fm.<portlet:namespace />addOrganizationIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		document.<portlet:namespace />fm.<portlet:namespace />removeOrganizationIds.value = Liferay.Util.listUncheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />updatePasswordPolicyUsers(assignmentsRedirect) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "password_policy_users";
		document.<portlet:namespace />fm.<portlet:namespace />assignmentsRedirect.value = assignmentsRedirect;
		document.<portlet:namespace />fm.<portlet:namespace />addUserIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		document.<portlet:namespace />fm.<portlet:namespace />removeUserIds.value = Liferay.Util.listUncheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_password_policy_assignments" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />tabs3" type="hidden" value="<%= tabs3 %>" />
<input name="<portlet:namespace />assignmentsRedirect" type="hidden" value="" />
<input name="<portlet:namespace />passwordPolicyId" type="hidden" value="<%= String.valueOf(passwordPolicy.getPasswordPolicyId()) %>" />

<liferay-ui:message key="edit-assignments-for-password-policy" />: <%= passwordPolicy.getName() %>

<br /><br />

<liferay-ui:tabs
	names="users,organizations"
	param="tabs2"
	url="<%= portletURL.toString() %>"
	backURL="<%= redirect %>"
/>

<c:choose>
	<c:when test='<%= tabs2.equals("users") %>'>
		<input name="<portlet:namespace />addUserIds" type="hidden" value="" />
		<input name="<portlet:namespace />removeUserIds" type="hidden" value="" />

		<liferay-ui:tabs
			names="current,available"
			param="tabs3"
			url="<%= portletURL.toString() %>"
		/>

		<%
		UserSearch searchContainer = new UserSearch(renderRequest, portletURL);

		searchContainer.setRowChecker(new UserPasswordPolicyChecker(renderResponse, passwordPolicy));
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/user_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<%
		UserSearchTerms searchTerms = (UserSearchTerms)searchContainer.getSearchTerms();

		LinkedHashMap userParams = new LinkedHashMap();

		if (tabs3.equals("current")) {
			userParams.put("usersPasswordPolicies", new Long(passwordPolicy.getPasswordPolicyId()));
		}
		%>

		<%@ include file="/html/portlet/enterprise_admin/user_search_results.jspf" %>

		<div class="separator"><!-- --></div>

		<input type="button" value="<liferay-ui:message key="update-associations" />" onClick="<portlet:namespace />updatePasswordPolicyUsers('<%= portletURL.toString() %>&<portlet:namespace />cur=<%= cur %>');" />

		<br /><br />

		<%
		List headerNames = new ArrayList();

		headerNames.add("name");
		headerNames.add("screen-name");
		//headerNames.add("email-address");

		searchContainer.setHeaderNames(headerNames);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			User user2 = (User)results.get(i);

			ResultRow row = new ResultRow(user2, user2.getUserId(), i);

			// Name, screen name, and email address

			row.addText(user2.getFullName());
			row.addText(user2.getScreenName());
			//row.addText(user2.getEmailAddress());

			// Add result row

			resultRows.add(row);
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
	<c:when test='<%= tabs2.equals("organizations") %>'>
		<input name="<portlet:namespace />addOrganizationIds" type="hidden" value="" />
		<input name="<portlet:namespace />removeOrganizationIds" type="hidden" value="" />

		<liferay-ui:tabs
			names="current,available"
			param="tabs3"
			url="<%= portletURL.toString() %>"
		/>

		<%
		OrganizationSearch searchContainer = new OrganizationSearch(renderRequest, portletURL);

		searchContainer.setRowChecker(new OrganizationPasswordPolicyChecker(renderResponse, passwordPolicy));
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/organization_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<%
		OrganizationSearchTerms searchTerms = (OrganizationSearchTerms)searchContainer.getSearchTerms();

		long parentOrganizationId = OrganizationImpl.ANY_PARENT_ORGANIZATION_ID;

		LinkedHashMap organizationParams = new LinkedHashMap();

		if (tabs3.equals("current")) {
			organizationParams.put("organizationsPasswordPolicies", new Long(passwordPolicy.getPasswordPolicyId()));
		}
		%>

		<%@ include file="/html/portlet/enterprise_admin/organization_search_results.jspf" %>

		<div class="separator"><!-- --></div>

		<input type="button" value="<liferay-ui:message key="update-associations" />" onClick="<portlet:namespace />updatePasswordPolicyOrganizations('<%= portletURL.toString() %>&<portlet:namespace />cur=<%= cur %>');" />

		<br /><br />

		<%
		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			Organization organization = (Organization)results.get(i);

			ResultRow row = new ResultRow(organization, organization.getOrganizationId(), i);

			// Name

			row.addText(organization.getName());

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

			row.addText(address.getCity());

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

			row.addText(regionName);

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

			row.addText(countryName);

			// Add result row

			resultRows.add(row);
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
</c:choose>

</form>
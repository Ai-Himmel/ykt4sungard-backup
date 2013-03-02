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

String className = ParamUtil.getString(request, "className");
long classNameId = PortalUtil.getClassNameId(className);
long classPK = ParamUtil.getLong(request, "classPK");

long[] organizationIdsArray = StringUtil.split(ParamUtil.getString(request, "organizationIds"), 0L);

SearchContainer searchContainer = new SearchContainer();

List headerNames = new ArrayList();

headerNames.add("street");
headerNames.add("city");
headerNames.add("zip");
headerNames.add("type");
headerNames.add("mailing");
headerNames.add("primary");

if (editable) {
	headerNames.add(StringPool.BLANK);
}

searchContainer.setHeaderNames(headerNames);

if (className.equals(Contact.class.getName())) {
	if (classPK == user.getContactId()) {
		searchContainer.setEmptyResultsMessage("you-do-not-have-any-addresses");
	}
	else {
		searchContainer.setEmptyResultsMessage("the-user-does-not-have-any-addresses");
	}
}
else {
	searchContainer.setEmptyResultsMessage("the-organization-does-not-have-any-addresses");
}

List results = new ArrayList();

if (!className.equals(Organization.class.getName()) && (organizationIdsArray.length > 0)) {
	for (int i = 0; i < organizationIdsArray.length; i++) {
		try {
			results.addAll(AddressServiceUtil.getAddresses(Organization.class.getName(), organizationIdsArray[i]));
		}
		catch (PrincipalException pe) {
		}
	}
}

results.addAll(AddressServiceUtil.getAddresses(className, classPK));

searchContainer.setTotal(results.size());

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	Address address = (Address)results.get(i);

	ResultRow row = new ResultRow(address, address.getAddressId(), i);

	// Street

	StringMaker sm = new StringMaker();

	sm.append(address.getStreet1());

	if (Validator.isNotNull(address.getStreet2())) {
		sm.append("<br />");
		sm.append(address.getStreet2());
	}

	if (Validator.isNotNull(address.getStreet3())) {
		sm.append("<br />");
		sm.append(address.getStreet3());
	}

	row.addText(sm.toString());

	// Other fields

	row.addText(address.getCity());
	row.addText(address.getZip());
	row.addText(address.getType().getName());
	row.addText(LanguageUtil.get(pageContext, address.isMailing() ? "yes" : "no"));
	row.addText(LanguageUtil.get(pageContext, address.isPrimary() ? "yes" : "no"));

	// Action

	if (editable) {
		if (classNameId == address.getClassNameId()) {
			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/address_action.jsp");
		}
		else {
			row.addText(StringPool.BLANK);
		}
	}

	// Add result row

	resultRows.add(row);
}
%>

<c:if test="<%= editable %>">
	<input type="button" value="<liferay-ui:message key="add" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_address" /><portlet:param name="redirect" value="<%= redirect %>" /><portlet:param name="className" value="<%= className %>" /><portlet:param name="classPK" value="<%= String.valueOf(classPK) %>" /></portlet:renderURL>';" /><br />

	<br />
</c:if>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" paginate="<%= false %>" />

<c:if test="<%= editable || (results.size() > 0) %>">
	<br />
</c:if>
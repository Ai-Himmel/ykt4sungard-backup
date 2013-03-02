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

<%@ include file="/html/portlet/software_catalog/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "products");

String tabs1Values = "products";

if (themeDisplay.isSignedIn()) {
	tabs1Values += ",my_products";
}

if (PortalPermissionUtil.contains(permissionChecker, ActionKeys.ADD_LICENSE)) {
	tabs1Values += ",licenses";
}

if (PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.SOFTWARE_CATALOG, ActionKeys.ADD_FRAMEWORK_VERSION)) {
	tabs1Values += ",framework_versions";
}

String tabs1Names = StringUtil.replace(tabs1Values, StringPool.UNDERLINE, StringPool.DASH);

String keywords = ParamUtil.getString(request, "keywords");
String type = ParamUtil.getString(request, "type");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/software_catalog/view");
portletURL.setParameter("tabs1", tabs1);
%>

<form action="<%= portletURL %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="portletURL" />

<liferay-ui:tabs
	names="<%= tabs1Names %>"
	tabsValues="<%= tabs1Values %>"
	portletURL="<%= portletURL %>"
/>

<c:choose>
	<c:when test='<%= tabs1.equals("products") %>'>

		<%
		portletURL.setParameter("type", type);

		String orderByCol = ParamUtil.getString(request, "orderByCol");
		String orderByType = ParamUtil.getString(request, "orderByType");

		if (Validator.isNotNull(orderByCol) && Validator.isNotNull(orderByType)) {
			portalPrefs.setValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-col", orderByCol);
			portalPrefs.setValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-type", orderByType);
		}
		else {
			orderByCol = portalPrefs.getValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-col", "modified-date");
			orderByType = portalPrefs.getValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-type", "desc");
		}

		List headerNames = new ArrayList();

		headerNames.add("name");
		headerNames.add("version");
		headerNames.add("type");
		headerNames.add("tags");
		headerNames.add("licenses");
		headerNames.add("modified-date");
		headerNames.add(StringPool.BLANK);

		Map orderableHeaders = CollectionFactory.getHashMap();

		orderableHeaders.put("name", "name");
		orderableHeaders.put("version", "version");
		orderableHeaders.put("type", "type");
		orderableHeaders.put("modified-date", "modified-date");

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.get(pageContext, "no-products-were-found"));

		searchContainer.setOrderableHeaders(orderableHeaders);
		searchContainer.setOrderByCol(orderByCol);
		searchContainer.setOrderByType(orderByType);

		List hits = SCProductEntryLocalServiceUtil.search(company.getCompanyId(), portletGroupId.longValue(), keywords, type).toList();

		DocumentComparator docComparator = null;

		if (orderByType.equals("desc")) {
			docComparator = new DocumentComparator(false, false);
		}
		else {
			docComparator = new DocumentComparator();
		}

		if (orderByCol.equals("version")) {
			docComparator.addOrderBy("version");
			docComparator.addOrderBy("modified-date");
			docComparator.addOrderBy(LuceneFields.TITLE);
			docComparator.addOrderBy("type");
		}
		else if (orderByCol.equals("modified-date")) {
			docComparator.addOrderBy("modified-date");
			docComparator.addOrderBy(LuceneFields.TITLE);
			docComparator.addOrderBy("version");
			docComparator.addOrderBy("type");
		}
		else if (orderByCol.equals("type")) {
			docComparator.addOrderBy("type");
			docComparator.addOrderBy("modified-date");
			docComparator.addOrderBy(LuceneFields.TITLE);
			docComparator.addOrderBy("version");
		}
		else {
			docComparator.addOrderBy(LuceneFields.TITLE);
			docComparator.addOrderBy("version");
			docComparator.addOrderBy("modified-date");
			docComparator.addOrderBy("type");
		}

		Collections.sort(hits, docComparator);

		List results = ListUtil.subList(hits, searchContainer.getStart(), searchContainer.getEnd());
		int total = hits.size();

		searchContainer.setTotal(total);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			Document doc = (Document)results.get(i);

			long productEntryId = GetterUtil.getLong(doc.get("productEntryId"));

			SCProductEntry productEntry = SCProductEntryLocalServiceUtil.getProductEntry(productEntryId);

			productEntry = productEntry.toEscapedModel();

			SCProductVersion latestProductVersion = productEntry.getLatestVersion();

			if (latestProductVersion != null) {
				latestProductVersion = latestProductVersion.toEscapedModel();
			}

			ResultRow row = new ResultRow(productEntry, productEntryId, i);

			PortletURL rowURL = renderResponse.createRenderURL();

			rowURL.setWindowState(WindowState.MAXIMIZED);

			rowURL.setParameter("struts_action", "/software_catalog/view_product_entry");
			rowURL.setParameter("redirect", currentURL);
			rowURL.setParameter("productEntryId", String.valueOf(productEntryId));

			// Name and short description

			StringMaker sm = new StringMaker();

			sm.append("<b>");
			sm.append(productEntry.getName());
			sm.append("</b>");

			if (Validator.isNotNull(productEntry.getShortDescription())) {
				sm.append("<br />");
				sm.append(productEntry.getShortDescription());
			}

			row.addText(sm.toString(), rowURL);

			// Version

			if (latestProductVersion != null) {
				row.addText(latestProductVersion.getVersion(), rowURL);
			}
			else {
				row.addText(LanguageUtil.get(pageContext, "not-available"), rowURL);
			}

			// Type

			row.addText(LanguageUtil.get(pageContext, productEntry.getType()), rowURL);

			// Tags

			row.addText(LanguageUtil.get(pageContext, productEntry.getTags()), rowURL);

			// Licenses

			sm = new StringMaker();

			Iterator itr = productEntry.getLicenses().iterator();

			while (itr.hasNext()) {
				SCLicense license = (SCLicense)itr.next();

				license = license.toEscapedModel();

				sm.append(license.getName());

				if (itr.hasNext()) {
					sm.append(", ");
				}
			}

			row.addText(sm.toString(), rowURL);

			// Modified date

			row.addText(dateFormatDateTime.format(productEntry.getModifiedDate()), rowURL);

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/software_catalog/product_entry_action.jsp");

			// Add result row

			resultRows.add(row);
		}

		boolean showAddProductEntryButton = PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.SOFTWARE_CATALOG, ActionKeys.ADD_PRODUCT_ENTRY);
		%>

		<div>
			<label for="<portlet:namespace />keyword"><liferay-ui:message key="search" /></label>

			<input id="<portlet:namespace />keyword" name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" />

			<select name="<portlet:namespace/>type">
				<option value=""></option>
				<option <%= type.equals(PortletImpl.PLUGIN_TYPE) ? "selected" : "" %> value="<%= PortletImpl.PLUGIN_TYPE %>"><liferay-ui:message key="<%= PortletImpl.PLUGIN_TYPE %>" /></option>
				<option <%= type.equals(ThemeImpl.PLUGIN_TYPE) ? "selected" : "" %> value="<%= ThemeImpl.PLUGIN_TYPE %>"><liferay-ui:message key="<%= ThemeImpl.PLUGIN_TYPE %>" /></option>
				<option <%= type.equals(LayoutTemplateImpl.PLUGIN_TYPE) ? "selected" : "" %> value="<%= LayoutTemplateImpl.PLUGIN_TYPE %>"><liferay-ui:message key="<%= LayoutTemplateImpl.PLUGIN_TYPE %>" /></option>
				<%--<option <%= type.equals("extension") ? "selected" : "" %> value="extension"><liferay-ui:message key="extension" /></option>--%>
			</select>

			<input type="submit" value="<liferay-ui:message key="search-products" />" />

			<c:if test="<%= showAddProductEntryButton %>">
				<input type="button" value="<liferay-ui:message key="add-product" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/software_catalog/edit_product_entry" /><portlet:param name="redirect" value="<%= currentURL %>" /></portlet:renderURL>';" />
			</c:if>
		</div>

		<br />

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
	<c:when test='<%= tabs1.equals("my_products") %>'>

		<%
		String orderByCol = ParamUtil.getString(request, "orderByCol");
		String orderByType = ParamUtil.getString(request, "orderByType");

		if (Validator.isNotNull(orderByCol) && Validator.isNotNull(orderByType)) {
			portalPrefs.setValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-col", orderByCol);
			portalPrefs.setValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-type", orderByType);
		}
		else {
			orderByCol = portalPrefs.getValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-col", "modified-date");
			orderByType = portalPrefs.getValue(PortletKeys.SOFTWARE_CATALOG, "product-entries-order-by-type", "desc");
		}

		OrderByComparator orderByComparator = SCUtil.getProductEntryOrderByComparator(orderByCol, orderByType);

		List headerNames = new ArrayList();

		headerNames.add("name");
		headerNames.add("version");
		headerNames.add("type");
		headerNames.add("tags");
		headerNames.add("licenses");
		headerNames.add("modified-date");
		headerNames.add(StringPool.BLANK);

		Map orderableHeaders = CollectionFactory.getHashMap();

		orderableHeaders.put("name", "name");
		orderableHeaders.put("type", "type");
		orderableHeaders.put("modified-date", "modified-date");

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		searchContainer.setOrderableHeaders(orderableHeaders);
		searchContainer.setOrderByCol(orderByCol);
		searchContainer.setOrderByType(orderByType);

		int total = 0;

		if (tabs1.equals("products")) {
			total = SCProductEntryLocalServiceUtil.getProductEntriesCount(portletGroupId.longValue());
		}
		else {
			total = SCProductEntryLocalServiceUtil.getProductEntriesCount(portletGroupId.longValue(), user.getUserId());
		}

		searchContainer.setTotal(total);

		List results = null;

		if (tabs1.equals("products")) {
			results = SCProductEntryLocalServiceUtil.getProductEntries(portletGroupId.longValue(), searchContainer.getStart(), searchContainer.getEnd(), orderByComparator);
		}
		else {
			results = SCProductEntryLocalServiceUtil.getProductEntries(portletGroupId.longValue(), user.getUserId(), searchContainer.getStart(), searchContainer.getEnd(), orderByComparator);
		}

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			SCProductEntry productEntry = (SCProductEntry)results.get(i);

			productEntry = productEntry.toEscapedModel();

			long productEntryId = productEntry.getProductEntryId();

			SCProductVersion latestProductVersion = productEntry.getLatestVersion();

			if (latestProductVersion != null) {
				latestProductVersion = latestProductVersion.toEscapedModel();
			}

			ResultRow row = new ResultRow(productEntry, productEntryId, i);

			PortletURL rowURL = renderResponse.createRenderURL();

			rowURL.setWindowState(WindowState.MAXIMIZED);

			rowURL.setParameter("struts_action", "/software_catalog/view_product_entry");
			rowURL.setParameter("redirect", currentURL);
			rowURL.setParameter("productEntryId", String.valueOf(productEntryId));

			// Name and short description

			StringMaker sm = new StringMaker();

			sm.append("<b>");
			sm.append(productEntry.getName());
			sm.append("</b>");

			if (Validator.isNotNull(productEntry.getShortDescription())) {
				sm.append("<br />");
				sm.append(productEntry.getShortDescription());
			}

			row.addText(sm.toString(), rowURL);

			// Version

			if (latestProductVersion != null) {
				row.addText(latestProductVersion.getVersion(), rowURL);
			}
			else {
				row.addText(LanguageUtil.get(pageContext, "not-available"), rowURL);
			}

			// Type

			row.addText(LanguageUtil.get(pageContext, productEntry.getType()), rowURL);

			// Tags

			row.addText(LanguageUtil.get(pageContext, productEntry.getTags()), rowURL);

			// Licenses

			sm = new StringMaker();

			Iterator itr = productEntry.getLicenses().iterator();

			while (itr.hasNext()) {
				SCLicense license = (SCLicense)itr.next();

				license = license.toEscapedModel();

				sm.append(license.getName());

				if (itr.hasNext()) {
					sm.append(", ");
				}
			}

			row.addText(sm.toString(), rowURL);

			// Modified date

			row.addText(dateFormatDateTime.format(productEntry.getModifiedDate()), rowURL);

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/software_catalog/product_entry_action.jsp");

			// Add result row

			resultRows.add(row);
		}

		boolean showAddProductEntryButton = PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.SOFTWARE_CATALOG, ActionKeys.ADD_PRODUCT_ENTRY);
		%>

		<c:if test="<%= showAddProductEntryButton %>">
			<div>
				<input type="button" value="<liferay-ui:message key="add-product" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/software_catalog/edit_product_entry" /><portlet:param name="redirect" value="<%= currentURL %>" /></portlet:renderURL>';" />
			</div>

			<c:if test="<%= results.size() > 0 %>">
				<br />
			</c:if>
		</c:if>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
	<c:when test='<%= tabs1.equals("framework_versions") %>'>

		<%
		List headerNames = new ArrayList();

		headerNames.add("name");
		headerNames.add("url");
		headerNames.add("active");
		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		int total = SCFrameworkVersionLocalServiceUtil.getFrameworkVersionsCount(portletGroupId.longValue());

		searchContainer.setTotal(total);

		List results = SCFrameworkVersionLocalServiceUtil.getFrameworkVersions(portletGroupId.longValue(), searchContainer.getStart(),searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			SCFrameworkVersion frameworkVersion = (SCFrameworkVersion) results.get(i);

			frameworkVersion = frameworkVersion.toEscapedModel();

			ResultRow row = new ResultRow(frameworkVersion, frameworkVersion.getFrameworkVersionId(), i);

			String rowHREF = frameworkVersion.getUrl();

			TextSearchEntry rowTextEntry = new TextSearchEntry(SearchEntry.DEFAULT_ALIGN, SearchEntry.DEFAULT_VALIGN, frameworkVersion.getName(), rowHREF, "_blank", frameworkVersion.getName());

			// Name

			row.addText(rowTextEntry);

			// URL

			rowTextEntry = (TextSearchEntry) rowTextEntry.clone();

			rowTextEntry.setName(frameworkVersion.getUrl());

			row.addText(rowTextEntry);

			// Active

			rowTextEntry = (TextSearchEntry) rowTextEntry.clone();

			rowTextEntry.setName(LanguageUtil.get(pageContext,frameworkVersion.isActive() ? "yes" : "no"));

			row.addText(rowTextEntry);

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/software_catalog/framework_version_action.jsp");

			// Add result row

			resultRows.add(row);
		}
		%>

		<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.SOFTWARE_CATALOG, ActionKeys.ADD_FRAMEWORK_VERSION) %>">
			<input type="button" value="<liferay-ui:message key="add-framework-version" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/software_catalog/edit_framework_version" /><portlet:param name="redirect" value="<%= currentURL %>" /></portlet:renderURL>';" /><br />

			<c:if test="<%= results.size() > 0 %>">
				<br />
			</c:if>
		</c:if>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
	<c:when test='<%= tabs1.equals("licenses") %>'>

		<%
		List headerNames = new ArrayList();

		headerNames.add("name");
		headerNames.add("url");
		headerNames.add("open-source");
		headerNames.add("active");
		headerNames.add("recommended");
		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		int total = SCLicenseLocalServiceUtil.getLicensesCount();

		searchContainer.setTotal(total);

		List results = SCLicenseLocalServiceUtil.getLicenses(searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			SCLicense license = (SCLicense)results.get(i);

			license = license.toEscapedModel();

			ResultRow row = new ResultRow(license, license.getLicenseId(), i);

			String rowHREF = license.getUrl();

			TextSearchEntry rowTextEntry = new TextSearchEntry(SearchEntry.DEFAULT_ALIGN, SearchEntry.DEFAULT_VALIGN, license.getName(), rowHREF, "_blank", license.getName());

			// Name

			row.addText(rowTextEntry);

			// URL

			rowTextEntry = (TextSearchEntry) rowTextEntry.clone();

			rowTextEntry.setName(license.getUrl());

			row.addText(rowTextEntry);

			// Open source

			rowTextEntry = (TextSearchEntry) rowTextEntry.clone();

			rowTextEntry.setName(LanguageUtil.get(pageContext, license.isOpenSource() ? "yes" : "no"));

			row.addText(rowTextEntry);

			// Active

			rowTextEntry = (TextSearchEntry) rowTextEntry.clone();

			rowTextEntry.setName(LanguageUtil.get(pageContext, license.isActive() ? "yes" : "no"));

			row.addText(rowTextEntry);

			// Recommended

			rowTextEntry = (TextSearchEntry) rowTextEntry.clone();

			rowTextEntry.setName(LanguageUtil.get(pageContext, license.isRecommended() ? "yes" : "no"));

			row.addText(rowTextEntry);

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/software_catalog/license_action.jsp");

			// Add result row

			resultRows.add(row);
		}
		%>

		<c:if test="<%= PortalPermissionUtil.contains(permissionChecker, ActionKeys.ADD_LICENSE) %>">
			<input type="button" value="<liferay-ui:message key="add-license" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/software_catalog/edit_license" /><portlet:param name="redirect" value="<%= currentURL %>" /></portlet:renderURL>';" /><br />

			<c:if test="<%= results.size() > 0 %>">
				<br />
			</c:if>
		</c:if>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
</c:choose>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />keywords);
	</script>
</c:if>
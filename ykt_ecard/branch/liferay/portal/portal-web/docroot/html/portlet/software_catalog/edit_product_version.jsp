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
String redirect = ParamUtil.getString(request, "redirect");

SCProductEntry productEntry = (SCProductEntry)request.getAttribute(WebKeys.SOFTWARE_CATALOG_PRODUCT_ENTRY);

productEntry = productEntry.toEscapedModel();

SCProductVersion productVersion = (SCProductVersion)request.getAttribute(WebKeys.SOFTWARE_CATALOG_PRODUCT_VERSION);

long productEntryId = productEntry.getProductEntryId();
long productVersionId = BeanParamUtil.getLong(productVersion, request, "productVersionId");

Set frameworkVersionIds = CollectionFactory.getHashSet();

String[] frameworkVersions = request.getParameterValues("frameworkVersions");

if ((productVersion != null) && (frameworkVersions == null)) {
	Iterator itr = productVersion.getFrameworkVersions().iterator();

	while (itr.hasNext()) {
		SCFrameworkVersion frameworkVersion = (SCFrameworkVersion)itr.next();

		frameworkVersionIds.add(new Long(frameworkVersion.getFrameworkVersionId()));
	}
}
else {
	long[] frameworkVersionIdsArray = GetterUtil.getLongValues(frameworkVersions);

	for (int i = 0; i < frameworkVersionIdsArray.length; i++) {
		frameworkVersionIds.add(new Long(frameworkVersionIdsArray[i]));
	}
}

PortletURL editProductEntryURL = renderResponse.createRenderURL();

editProductEntryURL.setWindowState(WindowState.MAXIMIZED);

editProductEntryURL.setParameter("struts_action", "/software_catalog/edit_product_entry");
editProductEntryURL.setParameter("redirect", currentURL);
editProductEntryURL.setParameter("productEntryId", String.valueOf(productEntryId));
%>

<script type="text/javascript">
	function <portlet:namespace />saveEntry() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= productVersion == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/software_catalog/edit_product_version" /><portlet:param name="productEntryId" value="<%= String.valueOf(productEntryId) %>" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveEntry(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />productVersionId" type="hidden" value="<%= productVersionId %>" />

<liferay-ui:tabs
	names="product-version"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= DuplicateProductVersionDirectDownloadURLException.class %>" message="please-enter-a-unique-direct-download-url" />
<liferay-ui:error exception="<%= ProductVersionNameException.class %>" message="please-enter-a-valid-version-name" />
<liferay-ui:error exception="<%= ProductVersionChangeLogException.class %>" message="please-enter-a-valid-change-log" />
<liferay-ui:error exception="<%= ProductVersionDownloadURLException.class %>" message="please-enter-a-download-page-url-or-a-direct-download-url" />
<liferay-ui:error exception="<%= ProductVersionFrameworkVersionException.class %>" message="please-select-at-least-one-framework-version" />

<h3><%= productEntry.getName() %></h3>

<fieldset>
	<legend><liferay-ui:message key="main-fields" /></legend>

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="version-name" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= SCProductVersion.class %>" bean="<%= productVersion %>" field="version" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="change-log" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= SCProductVersion.class %>" bean="<%= productVersion %>" field="changeLog" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="supported-framework-versions" />
		</td>
		<td>
			<select multiple="true" name="<portlet:namespace/>frameworkVersions">

				<%
				Iterator itr = SCFrameworkVersionServiceUtil.getFrameworkVersions(portletGroupId.longValue(), true).iterator();

				while (itr.hasNext()) {
					SCFrameworkVersion frameworkVersion = (SCFrameworkVersion)itr.next();
				%>

					<option <%= (frameworkVersionIds.contains(new Long(frameworkVersion.getFrameworkVersionId()))) ? "selected" : "" %> value="<%= frameworkVersion.getFrameworkVersionId() %>"><%= frameworkVersion.getName() %></option>

				<%
				}
				%>

			</select>
		</td>
	</tr>
	</table>
</fieldset>

<fieldset class="repository-fields">
	<legend><%=LanguageUtil.get(pageContext, "repository-fields")%></legend>

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="download-page-url" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= SCProductVersion.class %>" bean="<%= productVersion %>" field="downloadPageURL" />
		</td>
	</tr>
		<tr>
			<td>
				<liferay-ui:message key="direct-download-url" /> (<liferay-ui:message key="recommended" />)
			</td>
			<td>
				<liferay-ui:input-field model="<%= SCProductVersion.class %>" bean="<%= productVersion %>" field="directDownloadURL" />
			</td>
		</tr>
	<tr>
		<td>
			<liferay-ui:message key="include-artifact-in-repository" />
		</td>

		<% if (Validator.isNotNull(productEntry.getRepoArtifactId()) && Validator.isNotNull(productEntry.getRepoArtifactId())) { %>
			<td>
				<select name="<portlet:namespace/>repoStoreArtifact" size="1">
					<option <%= ((productVersion != null) && (!productVersion.getRepoStoreArtifact())) ? "selected" : "" %> value="false"><liferay-ui:message key="no" /></option>
					<option <%= ((productVersion != null) && (productVersion.getRepoStoreArtifact())) ? "selected" : "" %> value="true"><liferay-ui:message key="yes" /></option>
				</select>
			</td>
		<% } else { %>
			<td>
				<a href="<%= editProductEntryURL %>"><liferay-ui:message key="you-must-specify-a-group-id-and-artifact-id-before-you-can-add-a-product-version" /></a>
			</td>
		<% } %>
	</tr>

	</table>
</fieldset>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<script type="text/javascript">
	function <portlet:namespace />showRepoStoreArtifact() {
		if (document.<portlet:namespace />fm.<portlet:namespace />repoStoreArtifact) {
			if (document.<portlet:namespace />fm.<portlet:namespace />directDownloadURL.value == '') {
				document.<portlet:namespace />fm.<portlet:namespace />repoStoreArtifact.disabled = true;
				document.<portlet:namespace />fm.<portlet:namespace />repoStoreArtifact.options[0].selected = true;
			}
			else {
				document.<portlet:namespace />fm.<portlet:namespace />repoStoreArtifact.disabled = false;
			}
		}
	}

	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />version);
	</c:if>

	document.<portlet:namespace />fm.<portlet:namespace />directDownloadURL.onkeyup = <portlet:namespace />showRepoStoreArtifact;

	<portlet:namespace />showRepoStoreArtifact();
</script>
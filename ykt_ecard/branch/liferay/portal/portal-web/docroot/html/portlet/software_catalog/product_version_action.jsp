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
ResultRow row =	(ResultRow) request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

SCProductVersion productVersion = (SCProductVersion)row.getObject();
%>

<liferay-ui:icon-menu>
	<c:if test="<%= Validator.isNotNull(productVersion.getDownloadPageURL()) %>">
		<liferay-ui:icon image="download" message="download-page" url="<%= productVersion.getDownloadPageURL() %>" />
	</c:if>

	<c:if test="<%= Validator.isNotNull(productVersion.getDirectDownloadURL()) %>">

		<%
		String jsDirectDownloadUrl = "javascript: self.location = '" + productVersion.getDirectDownloadURL() + "';";
		%>

		<liferay-ui:icon image="download" message="direct-download" url="<%= jsDirectDownloadUrl %>" />
	</c:if>

	<c:if test="<%= SCProductEntryPermission.contains(permissionChecker, productVersion.getProductEntryId(), ActionKeys.UPDATE) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editURL">
			<portlet:param name="struts_action" value="/software_catalog/edit_product_version" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="productEntryId" value="<%= String.valueOf(productVersion.getProductEntryId()) %>" />
			<portlet:param name="productVersionId" value="<%= String.valueOf(productVersion.getProductVersionId()) %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="edit" url="<%= editURL %>" />

		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="copyURL">
			<portlet:param name="struts_action" value="/software_catalog/edit_product_version" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="productEntryId" value="<%= String.valueOf(productVersion.getProductEntryId()) %>" />
			<portlet:param name="productVersionId" value="0" />
			<portlet:param name="copyProductVersionId" value="<%= String.valueOf(productVersion.getProductVersionId()) %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="copy" url="<%= copyURL %>" />

		<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deleteURL">
			<portlet:param name="struts_action" value="/software_catalog/edit_product_version" />
			<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.DELETE %>" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="productEntryId" value="<%= String.valueOf(productVersion.getProductEntryId()) %>" />
			<portlet:param name="productVersionId" value="<%= String.valueOf(productVersion.getProductVersionId()) %>" />
		</portlet:actionURL>

		<liferay-ui:icon-delete url="<%= deleteURL %>" />
	</c:if>
</liferay-ui:icon-menu>
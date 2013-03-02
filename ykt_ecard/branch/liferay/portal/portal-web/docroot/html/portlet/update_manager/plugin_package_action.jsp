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

<%@ include file="/html/portlet/update_manager/init.jsp" %>

<%
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

Object[] rowObj = (Object[])row.getObject();

PluginPackage pluginPackage = (PluginPackage)rowObj[0];
PluginPackage availablePluginPackage = (PluginPackage)rowObj[1];
String pluginPackageStatus = (String)rowObj[2];
String uploadProgressId = (String)rowObj[3];
String redirect = (String)rowObj[4];

String downloadURL = StringPool.BLANK;

if (availablePluginPackage != null) {
	downloadURL = availablePluginPackage.getDownloadURL();
}
%>

<c:if test='<%= pluginPackageStatus.equals("update-available") || pluginPackageStatus.equals("update-ignored") %>'>
	<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="updateURL">
		<portlet:param name="struts_action" value="/update_manager/install_plugin" />
		<portlet:param name="<%= Constants.CMD %>" value="remoteDeploy" />
		<portlet:param name="<%= Constants.PROGRESS_ID %>" value="<%= uploadProgressId %>" />
		<portlet:param name="redirect" value="<%= redirect %>" />
		<portlet:param name="url" value="<%= downloadURL %>" />
	</portlet:actionURL>

	<%
	String jsUpdateURL = "javascript: " + uploadProgressId + ".startProgress(); submitForm(document.hrefFm, '" + updateURL + "');";
	%>

	<liferay-ui:icon
		image="download"
		message="update"
		url="<%= jsUpdateURL %>"
	/>

	<c:choose>
		<c:when test="<%= !PluginPackageUtil.isIgnored(pluginPackage) %>">
			<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="ignoreURL">
				<portlet:param name="struts_action" value="/update_manager/install_plugin" />
				<portlet:param name="<%= Constants.CMD %>" value="ignorePackages" />
				<portlet:param name="redirect" value="<%= redirect %>" />
				<portlet:param name="pluginPackagesIgnored" value="<%= pluginPackage.getPackageId() %>" />
			</portlet:actionURL>

			<%
			String jsIgnoreURL = "javascript: submitForm(document.hrefFm, '" + ignoreURL + "');";
			%>

			<liferay-ui:icon
				image="unsubscribe"
				message="ignore"
				url="<%= jsIgnoreURL %>"
			/>
		</c:when>
		<c:otherwise>
			<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="unignoreURL">
				<portlet:param name="struts_action" value="/update_manager/install_plugin" />
				<portlet:param name="<%= Constants.CMD %>" value="unignorePackages" />
				<portlet:param name="redirect" value="<%= redirect %>" />
				<portlet:param name="pluginPackagesUnignored" value="<%= pluginPackage.getPackageId() %>" />
			</portlet:actionURL>

			<%
			String jsUnignoreURL = "javascript: submitForm(document.hrefFm, '" + unignoreURL + "');";
			%>

			<liferay-ui:icon
				image="subscribe"
				message="unignore"
				url="<%= jsUnignoreURL %>"
			/>
		</c:otherwise>
	</c:choose>

	<br />

	<c:choose>
		<c:when test="<%= PluginPackageUtil.isTrusted(availablePluginPackage.getRepositoryURL()) %>">
			<liferay-ui:message key="trusted" />
		</c:when>
		<c:otherwise>
			<liferay-ui:message key="untrusted" />
		</c:otherwise>
	</c:choose>
</c:if>
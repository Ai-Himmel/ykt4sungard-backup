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

<%@ include file="/html/common/init.jsp" %>

<%@ include file="/html/common/themes/top_meta.jspf" %>
<%@ include file="/html/common/themes/top_meta-ext.jsp" %>

<%@ page import="com.liferay.portlet.journal.NoSuchTemplateException" %>
<%@ page import="com.liferay.portlet.journal.model.JournalTemplate" %>
<%@ page import="com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil" %>


<link rel="Shortcut Icon" href="<%= themeDisplay.getPathThemeImages() %>/liferay.ico" />

<link href="<%= themeDisplay.getCDNHost() %><%= themeDisplay.getPathMain() %>/portal/css_cached?themeId=<%= themeDisplay.getTheme().getThemeId() %>&amp;colorSchemeId=<%= themeDisplay.getColorScheme().getColorSchemeId() %>&amp;t=<%= theme.getTimestamp() %>" type="text/css" rel="stylesheet" />

<%
List portlets = null;

if ((layout != null) && layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
	portlets = layoutTypePortlet.getPortlets();
}
%>

<c:if test="<%= portlets != null %>">

	<%
	Set headerPortalCssPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List headerPortalCssList = portlet.getHeaderPortalCss();

		for (int j = 0; j < headerPortalCssList.size(); j++) {
			String headerPortalCss = (String)headerPortalCssList.get(j);

			String headerPortalCssPath = request.getContextPath() + headerPortalCss;

			if (!headerPortalCssPaths.contains(headerPortalCssPath)) {
				headerPortalCssPaths.add(headerPortalCssPath);
	%>

				<link href="<%= headerPortalCssPath %>" rel="stylesheet" type="text/css" />

	<%
			}
		}
	}

	Set headerPortletCssPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List headerPortletCssList = portlet.getHeaderPortletCss();

		for (int j = 0; j < headerPortletCssList.size(); j++) {
			String headerPortletCss = (String)headerPortletCssList.get(j);

			String headerPortletCssPath = portlet.getContextPath() + headerPortletCss;

			if (!headerPortletCssPaths.contains(headerPortletCssPath)) {
				headerPortletCssPaths.add(headerPortletCssPath);

				if (headerPortletCssPath.endsWith(".jsp")) {
					headerPortletCssPath += "?themeId=" + themeDisplay.getTheme().getThemeId() + "&amp;colorSchemeId=" + themeDisplay.getColorScheme().getColorSchemeId() + "&amp;t=" + theme.getTimestamp();
				}
	%>

				<link href="<%= headerPortletCssPath %>" rel="stylesheet" type="text/css" />

	<%
			}
		}
	}
	%>

	<style type="text/css">

		<%
		for (int i = 0; i < portlets.size(); i++) {
			Portlet portlet = (Portlet)portlets.get(i);

			PortletPreferences portletSetup = PortletPreferencesFactoryUtil.getPortletSetup(request, portlet.getPortletId(), true, true);

			String portletSetupCss = portletSetup.getValue("portlet-setup-css", StringPool.BLANK);
		%>

			<c:if test="<%= Validator.isNotNull(portletSetupCss) %>">

				<%
				try {
				%>

					<%@ include file="/html/common/themes/portlet_css.jspf" %>

				<%
				}
				catch (Exception e) {
					if (_log.isWarnEnabled()) {
						_log.warn(e.getMessage());
					}
				}
				%>

			</c:if>

		<%
		}
		%>

	</style>
</c:if>

<c:if test="<%= (layout != null) && Validator.isNotNull(layout.getCssText()) %>">
	<style type="text/css">
		<%= layout.getCssText() %>
	</style>
</c:if>

<%@ include file="/html/common/themes/top_js.jspf" %>
<%@ include file="/html/common/themes/top_js-ext.jsp" %>
<%@ include file="/html/common/themes/calendar_js.jspf" %>
  

<c:if test="<%= portlets != null %>">

	<%
	Set headerPortalJavaScriptPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List headerPortalJavaScriptList = portlet.getHeaderPortalJavaScript();

		for (int j = 0; j < headerPortalJavaScriptList.size(); j++) {
			String headerPortalJavaScript = (String)headerPortalJavaScriptList.get(j);

			String headerPortalJavaScriptPath = request.getContextPath() + headerPortalJavaScript;

			if (!headerPortalJavaScriptPaths.contains(headerPortalJavaScriptPath) && !themeDisplay.isIncludedJs(headerPortalJavaScriptPath)) {
				headerPortalJavaScriptPaths.add(headerPortalJavaScriptPath);
	%>

				<script src="<%= headerPortalJavaScriptPath %>" type="text/javascript"></script>

	<%
			}
		}
	}

	Set headerPortletJavaScriptPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List headerPortletJavaScriptList = portlet.getHeaderPortletJavaScript();

		for (int j = 0; j < headerPortletJavaScriptList.size(); j++) {
			String headerPortletJavaScript = (String)headerPortletJavaScriptList.get(j);

			String headerPortletJavaScriptPath = portlet.getContextPath() + headerPortletJavaScript;

			if (!headerPortletJavaScriptPaths.contains(headerPortletJavaScriptPath)) {
				headerPortletJavaScriptPaths.add(headerPortletJavaScriptPath);
	%>

				<script src="<%= headerPortletJavaScriptPath %>" type="text/javascript"></script>

	<%
			}
		}
	}
	%>

</c:if>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.common.themes.top_head.jsp");
%>
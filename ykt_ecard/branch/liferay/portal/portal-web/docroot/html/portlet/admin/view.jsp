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

<%@ include file="/html/portlet/admin/init.jsp" %>

<c:choose>
	<c:when test="<%= permissionChecker.isOmniadmin() %>">

		<%
		String tabs1 = ParamUtil.getString(request, "tabs1", "server");
		String tabs2 = ParamUtil.getString(request, "tabs2", "memory");
		String tabs3 = ParamUtil.getString(request, "tabs3");

		if (tabs1.equals("plugins")) {
			if (!tabs2.equals("portlets") && !tabs2.equals("themes") && !tabs2.equals("layout-templates")) {
				tabs2 = "portlets";
			}
		}

		String cur = ParamUtil.getString(request, "cur");

		PortletURL portletURL = renderResponse.createRenderURL();

		portletURL.setWindowState(WindowState.MAXIMIZED);

		portletURL.setParameter("struts_action", "/admin/view");
		portletURL.setParameter("tabs1", tabs1);
		portletURL.setParameter("tabs2", tabs2);
		%>

		<script type="text/javascript">
			function <portlet:namespace />saveServer(cmd) {
				document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = cmd;
				document.<portlet:namespace />fm.<portlet:namespace />redirect.value = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/admin/view" /><portlet:param name="tabs1" value="<%= tabs1 %>" /><portlet:param name="tabs2" value="<%= tabs2 %>" /><portlet:param name="tabs3" value="<%= tabs3 %>" /><portlet:param name="cur" value="<%= cur %>" /></portlet:renderURL>";
				submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/admin/edit_server" /></portlet:actionURL>");
			}
		</script>

		<form method="post" name="<portlet:namespace />fm">
		<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
		<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />
		<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
		<input name="<portlet:namespace />tabs3" type="hidden" value="<%= tabs3 %>" />
		<input name="<portlet:namespace />redirect" type="hidden" value="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/admin/view" /><portlet:param name="tabs1" value="<%= tabs1 %>" /><portlet:param name="tabs2" value="<%= tabs2 %>" /><portlet:param name="tabs3" value="<%= tabs3 %>" />portlet:param name="cur" value="<%= cur %>" /></portlet:renderURL>" />

		<liferay-ui:tabs
			names="server,instances,plugins"
			url="<%= portletURL.toString() %>"
		/>

		<c:choose>
			<c:when test='<%= tabs1.equals("server") %>'>
				<%@ include file="/html/portlet/admin/server.jspf" %>
			</c:when>
			<c:when test='<%= tabs1.equals("instances") %>'>
				<%@ include file="/html/portlet/admin/instances.jspf" %>
			</c:when>
			<c:when test='<%= tabs1.equals("plugins") %>'>

				<%
				PortletURL installPluginsURL = null;

				if (PrefsPropsUtil.getBoolean(PropsUtil.AUTO_DEPLOY_ENABLED, PropsValues.AUTO_DEPLOY_ENABLED)) {
					installPluginsURL = ((RenderResponseImpl)renderResponse).createRenderURL(PortletKeys.PLUGIN_INSTALLER);

					installPluginsURL.setWindowState(WindowState.MAXIMIZED);

					installPluginsURL.setParameter("struts_action", "/plugin_installer/view");
					installPluginsURL.setParameter("backURL", currentURL);
					installPluginsURL.setParameter("tabs1", tabs1);
					installPluginsURL.setParameter("tabs2", tabs2);
				}
				%>

				<%@ include file="/html/portlet/enterprise_admin/plugins.jspf" %>
			</c:when>
		</c:choose>

		</form>
	</c:when>
	<c:otherwise>
		<liferay-util:include page="/html/portal/portlet_access_denied.jsp" />
	</c:otherwise>
</c:choose>
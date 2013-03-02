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

<%@ include file="/html/portlet/plugin_installer/init.jsp" %>

<c:choose>
	<c:when test="<%= permissionChecker.isOmniadmin() %>">

		<%
		String uploadProgressId = PwdGenerator.getPassword(PwdGenerator.KEY3, 4);

		String tabs1Names = "browse-repository,upload-file,download-file,configuration";
		String tabs1 = ParamUtil.getString(request, "tabs1");

		if (!PrefsPropsUtil.getBoolean(PropsUtil.AUTO_DEPLOY_ENABLED, PropsValues.AUTO_DEPLOY_ENABLED)) {
			tabs1Names = "configuration";
			tabs1 = "configuration";
		}

		String tabs2 = ParamUtil.getString(request, "tabs2");

		if (Validator.isNull(tabs2)) {
			tabs2 = "portlets";
		}

		String redirect = ParamUtil.getString(request, "redirect");
		String backURL = ParamUtil.getString(request, "backURL");

		String pluginType = null;

		if (tabs2.equals("themes")) {
			pluginType = ThemeImpl.PLUGIN_TYPE;
		}
		else if (tabs2.equals("layout-templates")) {
			pluginType = LayoutTemplateImpl.PLUGIN_TYPE;
		}
		else if (tabs2.equals("portlets")) {
			pluginType = PortletImpl.PLUGIN_TYPE;
		}

		String moduleId = ParamUtil.getString(request, "moduleId");
		String repositoryURL = ParamUtil.getString(request, "repositoryURL");

		PortletURL portletURL = renderResponse.createRenderURL();

		portletURL.setWindowState(WindowState.MAXIMIZED);

		portletURL.setParameter("struts_action", "/plugin_installer/view");
		portletURL.setParameter("tabs1", tabs1);
		portletURL.setParameter("tabs2", tabs2);
		portletURL.setParameter("backURL", backURL);
		portletURL.setParameter("moduleId", moduleId);
		portletURL.setParameter("repositoryURL", repositoryURL);

		pageContext.setAttribute("portletURL", portletURL);

		String portletURLString = portletURL.toString();
		%>

		<script type="text/javascript">
			function <portlet:namespace />installPluginPackage(cmd) {
				document.<portlet:namespace />fm.method = "post";

				if (cmd == "localDeploy") {
					document.<portlet:namespace />fm.encoding = "multipart/form-data";
				}

				document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = cmd;
				submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/plugin_installer/install_plugin" /></portlet:actionURL>");
			}

			function <portlet:namespace />reloadRepositories() {
				document.<portlet:namespace />fm.method = "post";
				document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "reloadRepositories";
				submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/plugin_installer/install_plugin" /></portlet:actionURL>");
			}

			function <portlet:namespace />saveDeployConfiguration() {
				document.<portlet:namespace />fm.method = "post";
				document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'deployConfiguration';
				submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/plugin_installer/install_plugin" /></portlet:actionURL>");
			}

			function <portlet:namespace />searchPlugins() {
				submitForm(document.<portlet:namespace />fm);
			}
		</script>

		<form action="<%= portletURL %>" method="get" name="<portlet:namespace />fm">
		<liferay-portlet:renderURLParams varImpl="portletURL" />
		<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
		<input name="<portlet:namespace /><%= Constants.PROGRESS_ID %>" type="hidden" value="<%= uploadProgressId %>" />
		<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />
		<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />

		<c:if test="<%= Validator.isNull(moduleId) || Validator.isNull(repositoryURL) %>">
			<input name="<portlet:namespace />redirect" type="hidden" value="<%= portletURLString %>" />
		</c:if>

		<input name="<portlet:namespace />pluginType" type="hidden" value="<%= pluginType %>" />
		<input name="<portlet:namespace />moduleId" type="hidden" value="<%= moduleId %>" />
		<input name="<portlet:namespace />repositoryURL" type="hidden" value="<%= repositoryURL %>" />

		<c:choose>
			<c:when test="<%= Validator.isNotNull(moduleId) && Validator.isNotNull(repositoryURL) %>">
				<%@ include file="/html/portlet/plugin_installer/view_plugin_package.jspf" %>
			</c:when>
			<c:otherwise>
				<liferay-ui:tabs
					names="<%= tabs1Names %>"
					param="tabs1"
					url="<%= portletURLString %>"
					backURL="<%= backURL %>"
				/>

				<c:choose>
					<c:when test='<%= tabs1.equals("upload-file") %>'>
						<%@ include file="/html/portlet/plugin_installer/upload_file.jspf" %>
					</c:when>
					<c:when test='<%= tabs1.equals("download-file") %>'>
						<%@ include file="/html/portlet/plugin_installer/download_file.jspf" %>
					</c:when>
					<c:when test='<%= tabs1.equals("configuration") %>'>
						<%@ include file="/html/portlet/plugin_installer/configuration.jspf" %>
					</c:when>
					<c:otherwise>
						<%@ include file="/html/portlet/plugin_installer/browse_repository.jspf" %>
					</c:otherwise>
				</c:choose>
			</c:otherwise>
		</c:choose>

		</form>
	</c:when>
	<c:otherwise>
		<liferay-util:include page="/html/portal/portlet_access_denied.jsp" />
	</c:otherwise>
</c:choose>
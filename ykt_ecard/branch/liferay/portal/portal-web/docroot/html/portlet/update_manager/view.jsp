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
List updatablePackageIds = new ArrayList();
%>

<c:choose>
	<c:when test="<%= permissionChecker.isOmniadmin() %>">
		<c:choose>
			<c:when test="<%= !PrefsPropsUtil.getBoolean(PropsUtil.AUTO_DEPLOY_ENABLED, PropsValues.AUTO_DEPLOY_ENABLED) %>">

				<%
				PortletURL configurationURL = ((RenderResponseImpl)renderResponse).createRenderURL(PortletKeys.PLUGIN_INSTALLER);

				configurationURL.setWindowState(WindowState.MAXIMIZED);

				configurationURL.setParameter("struts_action", "/plugin_installer/view");
				configurationURL.setParameter("backURL", currentURL);
				configurationURL.setParameter("tabs1", "configuration");
				%>

				<a href="<%= configurationURL %>"><liferay-ui:message key="auto-deploy-is-not-enabled" /></a>
			</c:when>
			<c:otherwise>

				<%
				String uploadProgressId = PwdGenerator.getPassword(PwdGenerator.KEY3, 4);

				PortletURL pluginInstallerURL = ((RenderResponseImpl)renderResponse).createRenderURL(PortletKeys.PLUGIN_INSTALLER);

				pluginInstallerURL.setWindowState(WindowState.MAXIMIZED);

				pluginInstallerURL.setParameter("struts_action", "/plugin_installer/view");
				pluginInstallerURL.setParameter("tabs1", "browse-repository");
				pluginInstallerURL.setParameter("backURL", currentURL);
				%>

				<script type="text/javascript">
					function <portlet:namespace />reloadRepositories() {
						document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "reloadRepositories";
						submitForm(document.<portlet:namespace />fm);
					}
				</script>

				<form action="<portlet:actionURL><portlet:param name="struts_action" value="/update_manager/install_plugin" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
				<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
				<input name="<portlet:namespace />redirect" type="hidden" value="<portlet:renderURL><portlet:param name="struts_action" value="/update_manager/view" /></portlet:renderURL>" />

				<%
					try {
						List headerNames = new ArrayList();

						headerNames.add("plugin");
						headerNames.add("status");
						headerNames.add("installed-version");
						headerNames.add("available-version");
						headerNames.add(StringPool.BLANK);

						SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, pluginInstallerURL, headerNames, null);

						List pluginPackages = PluginPackageUtil.getInstalledPluginPackages();

						int total = pluginPackages.size();

						searchContainer.setTotal(total);

						pluginPackages = pluginPackages.subList(searchContainer.getStart(), Math.min(total, searchContainer.getEnd()));

						List resultRows = searchContainer.getResultRows();

						for (int i = 0; i < pluginPackages.size(); i++) {
							PluginPackage pluginPackage = (PluginPackage)pluginPackages.get(i);

							PluginPackage availablePluginPackage = null;

							try {
								availablePluginPackage = PluginPackageUtil.getLatestAvailablePluginPackage(pluginPackage.getGroupId(), pluginPackage.getArtifactId());
							}
							catch (Exception e) {
							}

							String pluginPackageModuleId = pluginPackage.getModuleId();
							String pluginPackageName = pluginPackage.getName();
							String pluginPackageVersion = pluginPackage.getVersion();
							String pluginPackageContext = pluginPackage.getContext();

							String pluginPackageStatus = "up-to-date";

							if (PluginPackageUtil.isInstallationInProcess(pluginPackage.getContext())) {
								pluginPackageStatus = "installation-in-process";
							}
							else
							if ((availablePluginPackage != null) && Version.getInstance(availablePluginPackage.getVersion()).isLaterVersionThan(pluginPackageVersion)) {
								if (PluginPackageUtil.isIgnored(pluginPackage)) {
									pluginPackageStatus = "update-ignored";
								}
								else {
									pluginPackageStatus = "update-available";
								}

								updatablePackageIds.add(pluginPackage.getPackageId());
							}
							else
							if (pluginPackage.getVersion().equals(Version.UNKNOWN)) {
								pluginPackageStatus = "unknown";
							}

							ResultRow row = new ResultRow(new Object[] {pluginPackage, availablePluginPackage, pluginPackageStatus, uploadProgressId, currentURL}, pluginPackageModuleId, i);

							row.setClassName("status-" + pluginPackageStatus);

							// Name

							StringMaker sm = new StringMaker();

							sm.append("<b>");
							sm.append(pluginPackageName);
							sm.append("</b>");
							sm.append("<br />/");
							sm.append(pluginPackageContext);

							row.addText(sm.toString());

							// Status

							row.addText(LanguageUtil.get(pageContext, pluginPackageStatus));

							// Installed version

							row.addText(pluginPackageVersion);

							// Available version

							if (availablePluginPackage != null) {
								PortletURL rowURL = ((RenderResponseImpl) renderResponse).createRenderURL(PortletKeys.PLUGIN_INSTALLER);

								rowURL.setWindowState(WindowState.MAXIMIZED);

								rowURL.setParameter("struts_action", "/plugin_installer/view");
								rowURL.setParameter("referer", currentURL);
								rowURL.setParameter("tabs1", "browse-repository");
								rowURL.setParameter("moduleId", availablePluginPackage.getModuleId());
								rowURL.setParameter("repositoryURL", availablePluginPackage.getRepositoryURL());

								sm = new StringMaker();

								sm.append("<a href=\"");
								sm.append(rowURL.toString());
								sm.append("\">");
								sm.append(availablePluginPackage.getVersion());
								sm.append("</a>&nbsp;<img align=\"absmiddle\" border=\"0\" src='");
								sm.append(themeDisplay.getPathThemeImages());
								sm.append("/document_library/page.png");
								sm.append("' onmousemove=\"ToolTip.show(event, this, '");
								sm.append(availablePluginPackage.getChangeLog());
								sm.append("')\" />");

								row.addText(sm.toString());
							}
							else {
								row.addText(StringPool.DASH);
							}

							// Actions

							row.addJSP("/html/portlet/update_manager/plugin_package_action.jsp");

							// Add result row

							resultRows.add(row);
						}
				%>

					<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

					<liferay-ui:upload-progress
						id="<%= uploadProgressId %>"
						message="downloading"
						redirect="<%= currentURL %>"
					/>

					<c:if test="<%= pluginPackages.size() > 0 %>">
						<br />
					</c:if>

					<input type="button" value="<liferay-ui:message key="install-more-plugins" />" onClick="submitForm(document.hrefFm, '<%= pluginInstallerURL.toString() %>');" />

					<c:if test="<%= !updatablePackageIds.isEmpty() %>">
						<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="ignoreAllURL">
							<portlet:param name="struts_action" value="/update_manager/install_plugin" />
							<portlet:param name="<%= Constants.CMD %>" value="ignorePackages" />
							<portlet:param name="redirect" value="<%= currentURL %>" />
							<portlet:param name="pluginPackagesIgnored" value='<%= StringUtil.merge(updatablePackageIds, "\n") %>' />
						</portlet:actionURL>

						<input type="button" value="<liferay-ui:message key="ignore-all-updates" />" onClick="submitForm(document.hrefFm, '<%= ignoreAllURL.toString() %>');" />
					</c:if>

					<div class="separator"><!-- --></div>

					<div>
						<c:if test="<%= PluginPackageUtil.getLastUpdateDate() != null %>">
							<%= LanguageUtil.format(pageContext, "list-of-plugins-was-last-refreshed-on-x", dateFormatDateTime.format(PluginPackageUtil.getLastUpdateDate())) %>
						</c:if>

						<input type="button" value="<liferay-ui:message key="refresh" />" onClick="<portlet:namespace/>reloadRepositories();" />

						<br />

						<liferay-util:include page="/html/portlet/plugin_installer/repository_report.jsp" />
					</div>

				<%
				}
				catch (PluginPackageException ppe) {
					if (_log.isWarnEnabled()) {
						_log.warn("Error browsing the repository", ppe);
					}
				%>

					<span class="portlet-msg-error">
					<liferay-ui:message key="an-error-occurred-while-retrieving-available-plugins" />
					</span>

				<%
				}
				%>

				</form>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:otherwise>
		<liferay-util:include page="/html/portal/portlet_access_denied.jsp" />
	</c:otherwise>
</c:choose>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.update_manager.view.jsp");
%>
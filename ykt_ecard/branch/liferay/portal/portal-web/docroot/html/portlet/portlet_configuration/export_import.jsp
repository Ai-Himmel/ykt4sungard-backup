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

<%@ include file="/html/portlet/portlet_configuration/init.jsp" %>

<%
String tabs2 = ParamUtil.getString(request, "tabs2", "export");

String redirect = ParamUtil.getString(request, "redirect");
String returnToFullPageURL = ParamUtil.getString(request, "returnToFullPageURL");

String portletResource = ParamUtil.getString(request, "portletResource");

Portlet selPortlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);

String path = (String)request.getAttribute(WebKeys.CONFIGURATION_ACTION_PATH);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/portlet_configuration/export_import");
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("returnToFullPageURL", returnToFullPageURL);
portletURL.setParameter("portletResource", portletResource);

boolean supportsLAR = Validator.isNotNull(selPortlet.getPortletDataHandlerClass());
boolean supportsSetup = Validator.isNotNull(selPortlet.getConfigurationActionClass());
%>

<script type="text/javascript">
	function <portlet:namespace />copyFromLive() {
		if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-copy-from-live-and-update-the-existing-staging-portlet-information") %>')) {
			document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "copy_from_live";

			submitForm(document.<portlet:namespace />fm);
		}
	}

	function <portlet:namespace />exportData() {
		document.<portlet:namespace />fm.encoding = "multipart/form-data";

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "export";

		document.<portlet:namespace />fm.submit();
	}

	function <portlet:namespace />importData() {
		document.<portlet:namespace />fm.encoding = "multipart/form-data";

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "import";

		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />publishToLive() {
		if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-publish-to-live-and-update-the-existing-live-portlet-information") %>')) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "publish_to_live";

		submitForm(document.<portlet:namespace />fm);
		}
	}

	function <portlet:namespace />toggleChildren(checkbox, parentDivId) {
		if (checkbox.checked) {
			jQuery('#' + parentDivId).find("input").not(".disabled").removeAttr('disabled');
		}
		else {
			jQuery('#' + parentDivId).find("input").attr("disabled", "disabled");
		}
	}
</script>

<liferay-util:include page="/html/portlet/portlet_configuration/tabs1.jsp">
	<liferay-util:param name="tabs1" value="export-import" />
</liferay-util:include>

<c:choose>
	<c:when test="<%= supportsLAR || supportsSetup %>">

		<%
		String tabs2Names = "export,import";

		if (layout.getGroup().isStagingGroup()) {
			tabs2Names += ",staging";
		}
		%>

		<liferay-ui:tabs
			names="<%= tabs2Names %>"
			param="tabs2"
			url="<%= portletURL.toString() %>"
		/>

		<liferay-ui:error exception="<%= LayoutImportException.class %>" message="an-unexpected-error-occurred-while-importing-your-file" />
		<liferay-ui:error exception="<%= NoSuchLayoutException.class %>" message="an-error-occurred-because-the-live-group-does-not-have-the-current-page" />

		<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/portlet_configuration/export_import" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveData(); return false;">
		<input name="<portlet:namespace />tabs1" type="hidden" value="export_import">
		<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>">
		<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="">
		<input name="<portlet:namespace />plid" type="hidden" value="<%= layout.getPlid() %>">
		<input name="<portlet:namespace />groupId" type="hidden" value="<%= layout.getGroupId() %>">
		<input name="<portlet:namespace />portletResource" type="hidden" value="<%= portletResource %>">
		<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>">

		<c:choose>
			<c:when test='<%= tabs2.equals("export") %>'>
				<liferay-ui:message key="export-the-selected-data-to-the-given-lar-file-name" />

				<br /><br />

				<div>
					<input name="<portlet:namespace />exportFileName" size="50" type="text" value="<%= StringUtil.replace(selPortlet.getDisplayName(), " ", "_") %>-<%= Time.getShortTimestamp() %>.portlet.lar">
				</div>

				<br />

				<liferay-ui:message key="what-would-you-like-to-export" />

				<br /><br />

				<%@ include file="/html/portlet/portlet_configuration/export_import_options.jspf" %>

				<br />

				<input type="button" value='<liferay-ui:message key="export" />'  onClick="<portlet:namespace />exportData();" />
			</c:when>
			<c:when test='<%= tabs2.equals("import") %>'>
				<liferay-ui:message key="import-a-lar-file-to-overwrite-the-selected-data" />

				<br /><br />

				<div>
					<input name="<portlet:namespace />importFileName" size="50" type="file" />
				</div>

				<br />

				<liferay-ui:message key="what-would-you-like-to-import" />

				<br /><br />

				<%@ include file="/html/portlet/portlet_configuration/export_import_options.jspf" %>

				<br />

				<input type="button" value="<liferay-ui:message key="import" />" onClick="<portlet:namespace />importData();">
			</c:when>
			<c:when test='<%= tabs2.equals("staging") %>'>

				<%
				String errorMesageKey = StringPool.BLANK;

				Group stagingGroup = layout.getGroup();
				Group liveGroup = stagingGroup.getLiveGroup();

				Layout targetLayout = null;

				try {
					targetLayout = LayoutLocalServiceUtil.getLayout(liveGroup.getGroupId(), layout.isPrivateLayout(), layout.getLayoutId());
				}
				catch (NoSuchLayoutException nsle) {
					errorMesageKey = "this-portlet-is-placed-in-a-page-that-does-not-exist-in-the-live-site-publish-the-page-first";
				}

				if (targetLayout != null) {
					LayoutType layoutType = targetLayout.getLayoutType();

					if (!(layoutType instanceof LayoutTypePortlet) || !((LayoutTypePortlet)layoutType).hasPortletId(selPortlet.getPortletId())) {
						errorMesageKey = "this-portlet-has-not-been-added-to-the-live-page-publish-the-page-first";
					}
				}
				%>

				<c:choose>
					<c:when test="<%= Validator.isNull(errorMesageKey) %>">
						<liferay-ui:message key="what-would-you-like-to-copy-from-live-or-publish-to-live" />

						<br /><br />

						<%@ include file="/html/portlet/portlet_configuration/export_import_options.jspf" %>

						<br />

						<input type="button" value="<liferay-ui:message key="publish-to-live" />"  onClick="<portlet:namespace />publishToLive();" />

						<input type="button" value="<liferay-ui:message key="copy-from-live" />"  onClick="<portlet:namespace />copyFromLive();" />
					</c:when>
					<c:otherwise>
						<liferay-ui:message key="<%= errorMesageKey %>" />
					</c:otherwise>
				</c:choose>
			</c:when>
		</c:choose>

		</form>

		<script type="text/javascript">
			jQuery(function(){
				jQuery(".<portlet:namespace />handler-control input[@type=checkbox]:not([@checked])").parent().parent().parent(".<portlet:namespace />handler-control").children(".<portlet:namespace />handler-control").hide();

				jQuery(".<portlet:namespace />handler-control input[@type=checkbox]").unbind('click').click(function() {
					var input = jQuery(this).parents(".<portlet:namespace />handler-control:first");

					if (this.checked) {
						input.children(".<portlet:namespace />handler-control").show();
					}
					else {
						input.children(".<portlet:namespace />handler-control").hide();
					}
				});
			});
		</script>

	</c:when>
	<c:otherwise>
		<%= LanguageUtil.format(locale, "the-x-portlet-does-not-have-any-data-that-can-be-exported-or-does-not-include-support-for-it", PortalUtil.getPortletTitle(selPortlet, application, locale)) %>
	</c:otherwise>
</c:choose>

<%@ include file="/html/portlet/communities/render_controls.jspf" %>
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

<%@ include file="/html/portlet/nested_portlets/init.jsp" %>

<c:if test="<%= LayoutPermissionUtil.contains(permissionChecker, layout, ActionKeys.UPDATE) %>">
	<div class="portlet-msg-info" id="<portlet:namespace />nested-portlets-msg" style="display: none;">
		<liferay-ui:message key="drag-portlets-below-to-nest-them" />
	</div>

	<script type="text/javascript">
		jQuery(
			function() {
				var portletWrapper = jQuery('#portlet-wrapper-<%= portletDisplay.getId() %>');

				var message = portletWrapper.find('#<portlet:namespace />nested-portlets-msg');

				var nestedPortlets = portletWrapper.find('.portlet, .portlet-borderless-container');

				if (!nestedPortlets.length) {
					message.show();
				}
			}
		);
	</script>
</c:if>

<%
try {
	String content = (String)request.getAttribute(WebKeys.LAYOUT_TEMPLATE_CONTENT);
%>

	<%= RuntimePortletUtil.processTemplate(application, request, response, pageContext, content) %>

<%
}
catch (Exception e) {
	_log.error("Cannot render Nested Portlets portlet", e);
}
finally {
	RenderRequestImpl renderRequestImpl = (RenderRequestImpl)renderRequest;

	renderRequestImpl.defineObjects(portletConfig, renderResponse);
}
%>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.nested_portlets.view.jsp");
%>
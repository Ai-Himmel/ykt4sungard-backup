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

<%@ include file="/html/portlet/communities/init.jsp" %>

<%
String tabs4 = (String)request.getAttribute("edit_pages.jsp-tab4");

long groupId = ((Long)request.getAttribute("edit_pages.jsp-groupId")).longValue();
boolean privateLayout = ((Boolean)request.getAttribute("edit_pages.jsp-privateLayout")).booleanValue();

String rootNodeName = (String)request.getAttribute("edit_pages.jsp-rootNodeName");

PortletURL portletURL = (PortletURL)request.getAttribute("edit_pages.jsp-portletURL");
%>

<liferay-ui:error exception="<%= LayoutImportException.class %>" message="an-unexpected-error-occurred-while-importing-your-file" />

<%
List portletsList = new ArrayList();
Set portletIdsSet = new HashSet();

Iterator itr1 = LayoutLocalServiceUtil.getLayouts(groupId, privateLayout).iterator();

while (itr1.hasNext()) {
	Layout curLayout = (Layout)itr1.next();

	if (curLayout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
		LayoutTypePortlet curLayoutTypePortlet = (LayoutTypePortlet)curLayout.getLayoutType();

		Iterator itr2 = curLayoutTypePortlet.getPortletIds().iterator();

		while (itr2.hasNext()) {
			Portlet curPortlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), (String)itr2.next());

			if (curPortlet != null) {
				PortletDataHandler portletDataHandler = curPortlet.getPortletDataHandlerInstance();

				if ((portletDataHandler != null) && !portletIdsSet.contains(curPortlet.getRootPortletId())) {
					portletIdsSet.add(curPortlet.getRootPortletId());

					portletsList.add(curPortlet);
				}
			}
		}
	}
}

Collections.sort(portletsList, new PortletTitleComparator(application, locale));

String tabs4Names = "export,import";
%>

<liferay-ui:tabs
	names="<%= tabs4Names %>"
	param="tabs4"
	url="<%= portletURL.toString() %>"
/>

<c:choose>
	<c:when test='<%= tabs4.equals("export") %>'>
		<liferay-ui:message key="export-the-selected-data-to-the-given-lar-file-name" />

		<br /><br />

		<div>
			<input name="<portlet:namespace />exportFileName" size="50" type="text" value="<%= StringUtil.replace(rootNodeName, " ", "_") %>-<%= Time.getShortTimestamp() %>.lar">
		</div>

		<br />

		<liferay-ui:message key="what-would-you-like-to-export" />

		<br /><br />

		<%@ include file="/html/portlet/communities/edit_pages_export_import_options.jspf" %>

		<br />

		<input type="button" value='<liferay-ui:message key="export" />' onClick="<portlet:namespace />exportPages();" />
	</c:when>
	<c:when test='<%= tabs4.equals("import") %>'>
		<c:choose>
			<c:when test="<%= (layout.getGroupId() != groupId) || (layout.isPrivateLayout() != privateLayout) %>">
				<liferay-ui:message key="import-a-lar-file-to-overwrite-the-selected-data" />

				<br /><br />

				<div>
					<input name="<portlet:namespace />importFileName" size="50" type="file" />
				</div>

				<br />

				<liferay-ui:message key="what-would-you-like-to-import" />

				<br /><br />

				<%@ include file="/html/portlet/communities/edit_pages_export_import_options.jspf" %>

				<br />

				<input type="button" value="<liferay-ui:message key="import" />" onClick="<portlet:namespace />importPages();">
			</c:when>
			<c:otherwise>
				<liferay-ui:message key="import-from-within-the-target-community-can-cause-conflicts" />
			</c:otherwise>
		</c:choose>
	</c:when>
</c:choose>

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

<%@ include file="/html/portlet/communities/render_controls.jspf" %>
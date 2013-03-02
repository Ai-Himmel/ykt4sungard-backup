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

Group liveGroup = (Group)request.getAttribute("edit_pages.jsp-liveGroup");
long groupId = ((Long)request.getAttribute("edit_pages.jsp-groupId")).longValue();
long selPlid = ((Long)request.getAttribute("edit_pages.jsp-selPlid")).longValue();
boolean privateLayout = ((Boolean)request.getAttribute("edit_pages.jsp-privateLayout")).booleanValue();
Properties groupTypeSettings = (Properties)request.getAttribute("edit_pages.jsp-groupTypeSettings");
Layout selLayout = (Layout)request.getAttribute("edit_pages.jsp-selLayout");

PortletURL portletURL = (PortletURL)request.getAttribute("edit_pages.jsp-portletURL");

List selLayoutChildren = null;

if (selLayout != null) {
	selLayoutChildren = selLayout.getChildren();
}
else {
	selLayoutChildren = LayoutLocalServiceUtil.getLayouts(groupId, privateLayout, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID);
}

String tabs4Names = "new-page";

if ((selLayoutChildren != null) && (selLayoutChildren.size() > 0)) {
	tabs4Names += ",display-order";
}

Group guestGroup = GroupLocalServiceUtil.getGroup(company.getCompanyId(), GroupImpl.GUEST);

if ((selLayout == null) && !privateLayout && (liveGroup.getGroupId() != guestGroup.getGroupId())) {
	tabs4Names += ",merge-pages";
}
%>

<liferay-ui:tabs
	names="<%= tabs4Names %>"
	param="tabs4"
	url='<%= portletURL.toString() + "&" + renderResponse.getNamespace() + "selPlid=" + selPlid %>'
/>

<input name="<portlet:namespace />parentLayoutId" type="hidden" value="<%= (selLayout != null) ? selLayout.getLayoutId() : LayoutImpl.DEFAULT_PARENT_LAYOUT_ID %>" />
<input name="<portlet:namespace />layoutIds" type="hidden" value="" />

<c:choose>
	<c:when test='<%= tabs4.equals("new-page") %>'>

		<%
		String name = ParamUtil.getString(request, "name");
		String type = ParamUtil.getString(request, "type");
		boolean hidden = ParamUtil.getBoolean(request, "hidden");

		Locale defaultLocale = LocaleUtil.getDefault();
		String defaultLanguageId = LocaleUtil.toLanguageId(defaultLocale);
		%>

		<liferay-ui:message key="add-child-pages" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="name" />
			</td>
			<td>
				<input name="<portlet:namespace />name_<%= defaultLanguageId %>" size="30" type="text" value="<%= name %>" />
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="type" />
			</td>
			<td>
				<select name="<portlet:namespace />type">

					<%
					for (int i = 0; i < LayoutImpl.TYPES.length; i++) {
					%>

						<option <%= type.equals(LayoutImpl.TYPES[i]) ? "selected" : "" %> value="<%= LayoutImpl.TYPES[i] %>"><%= LanguageUtil.get(pageContext, "layout.types." + LayoutImpl.TYPES[i]) %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="hidden" />
			</td>
			<td>
				<liferay-ui:input-checkbox param="hidden" defaultValue="<%= hidden %>" />
			</td>
		</tr>

		<c:if test="<%= (selLayout != null) && selLayout.getType().equals(LayoutImpl.TYPE_PORTLET) %>">
			<tr>
				<td>
					<liferay-ui:message key="inherit" />
				</td>
				<td>
					<liferay-ui:input-checkbox param="inheritFromParentLayoutId" defaultValue="false" />
				</td>
			</tr>
		</c:if>

		</table>

		<br />

		<input type="submit" value="<liferay-ui:message key="add-page" />" /><br />

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
			<script type="text/javascript">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name_<%= defaultLanguageId %>);
			</script>
		</c:if>
	</c:when>
	<c:when test='<%= tabs4.equals("display-order") %>'>
		<liferay-ui:error exception="<%= RequiredLayoutException.class %>">

			<%
			RequiredLayoutException rle = (RequiredLayoutException)errorException;
			%>

			<c:if test="<%= rle.getType() == RequiredLayoutException.AT_LEAST_ONE %>">
				<liferay-ui:message key="you-must-have-at-least-one-page" />
			</c:if>

			<c:if test="<%= rle.getType() == RequiredLayoutException.FIRST_LAYOUT_TYPE %>">
				<liferay-ui:message key="your-first-page-must-be-a-portlet-page" />
			</c:if>

			<c:if test="<%= rle.getType() == RequiredLayoutException.FIRST_LAYOUT_HIDDEN %>">
				<liferay-ui:message key="your-first-page-must-not-be-hidden" />
			</c:if>
		</liferay-ui:error>

		<liferay-ui:message key="set-the-display-order-of-child-pages" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<select name="<portlet:namespace />layoutIdsBox" size="7">

				<%
				for (int i = 0; i < selLayoutChildren.size(); i++) {
					Layout selLayoutChild = (Layout)selLayoutChildren.get(i);
				%>

					<option value="<%= selLayoutChild.getLayoutId() %>"><%= selLayoutChild.getName(locale) %></option>

				<%
				}
				%>

				</select>
			</td>
			<td valign="top">
				<a href="javascript: Liferay.Util.reorder(document.<portlet:namespace />fm.<portlet:namespace />layoutIdsBox, 0);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_up.png" vspace="2" width="16" /></a><br />
				<a href="javascript: Liferay.Util.reorder(document.<portlet:namespace />fm.<portlet:namespace />layoutIdsBox, 1);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_down.png" vspace="2" width="16" /></a><br />
				<a href="javascript: Liferay.Util.removeItem(document.<portlet:namespace />fm.<portlet:namespace />layoutIdsBox);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_x.png" vspace="2" width="16" /></a><br />
			</td>
		</tr>
		</table>

		<br />

		<input type="button" value="<liferay-ui:message key="update-display-order" />" onClick="<portlet:namespace />updateDisplayOrder();" />
	</c:when>
	<c:when test='<%= tabs4.equals("merge-pages") %>'>

		<%
		boolean mergeGuestPublicPages = PropertiesParamUtil.getBoolean(groupTypeSettings, request, "mergeGuestPublicPages");
		%>

		<liferay-ui:message key="you-can-configure-the-top-level-pages-of-this-public-website-to-merge-with-the-top-level-pages-of-the-public-guest-community" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="merge-guest-public-pages" />
			</td>
			<td>
				<liferay-ui:input-checkbox param="mergeGuestPublicPages" defaultValue="<%= mergeGuestPublicPages %>" />
			</td>
		</tr>
		</table>

		<br />

		<input type="submit" value="<liferay-ui:message key="save" />" />
	</c:when>
</c:choose>
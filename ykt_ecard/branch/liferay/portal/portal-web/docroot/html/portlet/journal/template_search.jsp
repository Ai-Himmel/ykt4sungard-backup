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

<%@ include file="/html/portlet/journal/init.jsp" %>

<%
TemplateSearch searchContainer = (TemplateSearch)request.getAttribute("liferay-ui:search:searchContainer");

TemplateDisplayTerms displayTerms = (TemplateDisplayTerms)searchContainer.getDisplayTerms();
%>

<liferay-ui:search-toggle
	id="toggle_id_journal_template_search"
	displayTerms="<%= displayTerms %>"
>
	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="id" />
		</td>
		<td>
			<liferay-ui:message key="name" />
		</td>
		<td>
			<liferay-ui:message key="description" />
		</td>
	</tr>
	<tr>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.TEMPLATE_ID %>" size="20" type="text" value="<%= Html.escape(displayTerms.getTemplateId()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.NAME %>" size="20" type="text" value="<%= Html.escape(displayTerms.getName()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.DESCRIPTION %>" size="20" type="text" value="<%= Html.escape(displayTerms.getDescription()) %>" />
		</td>
	</tr>
	</table>
</liferay-ui:search-toggle>

<br />

<div>
	<input type="submit" value="<liferay-ui:message key="search-templates" />" />

	<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.ADD_TEMPLATE) %>">
		<input type="button" value="<liferay-ui:message key="add-template" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_template" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="structureId" value="<%= displayTerms.getStructureId() %>" /></portlet:renderURL>';" />
	</c:if>
</div>

<c:if test="<%= Validator.isNotNull(displayTerms.getStructureId()) %>">
	<br />

	<input name="<portlet:namespace /><%= displayTerms.STRUCTURE_ID %>" type="hidden" value="<%= displayTerms.getStructureId() %>" />

	<liferay-ui:message key="filter-by-structure" />: <%= displayTerms.getStructureId() %><br />
</c:if>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.TEMPLATE_ID %>);
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.KEYWORDS %>);
	</script>
</c:if>
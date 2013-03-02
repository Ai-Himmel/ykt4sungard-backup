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
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

Layout curLayout = (Layout)row.getObject();
%>

<div class="type" style="float: right; padding-right: 32px; text-align: center; width: 100px;">
	<%= LanguageUtil.get(pageContext, StringUtil.replace(curLayout.getType(), "_", "-")) %>
</div>

<div class="layout">
	<a href="javascript: Liferay.LayoutExporter.details({toggle: '#_detail_<%= curLayout.getPlid() %>_toggle', detail: '#_detail_<%= curLayout.getPlid() %>'});" style="text-decoration: none;" target="_self"><img align="absmiddle" border="0" id="_detail_<%= curLayout.getPlid() %>_toggle" src="<%= themeDisplay.getPathThemeImages() %>/arrows/01_plus.png" onMouseMove="ToolTip.show(event, this, '<%= UnicodeLanguageUtil.get(pageContext, "details") %>')" /> <%= curLayout.getName(locale) %></a>
</div>

<div class="export-layout-detail" id="_detail_<%= curLayout.getPlid() %>" style="border-top: 1px solid #CCC; display: none; margin-top: 4px; padding-top: 4px; width: 95%;">
	<input checked disabled name="<portlet:namespace />includeAncestors_<%= curLayout.getPlid() %>" type="checkbox" value="1" />

	<label for="<portlet:namespace />includeAncestors_<%= curLayout.getPlid() %>"><liferay-ui:message key="include-ancestor-pages-if-necessary" /></label>

	<c:if test="<%= curLayout.getChildren().size() > 0 %>">
		<br />

		<input name="<portlet:namespace />includeChildren_<%= curLayout.getPlid() %>" type="checkbox" value="1" />

		<label for="<portlet:namespace />includeChildren_<%= curLayout.getPlid() %>"><liferay-ui:message key="include-all-descendent-pages" /></label>
	</c:if>
</div>
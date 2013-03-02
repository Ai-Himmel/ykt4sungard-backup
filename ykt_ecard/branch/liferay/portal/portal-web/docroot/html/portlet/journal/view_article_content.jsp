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

<html>

<head>
	<link href="<%= themeDisplay.getPathMain() %>/portal/css_cached?themeId=<%= themeDisplay.getTheme().getThemeId() %>&colorSchemeId=<%= themeDisplay.getColorScheme().getColorSchemeId() %>" type="text/css" rel="stylesheet" />
	<link href="<%= themeDisplay.getPathThemeCss() %>/main.css?companyId=<%= themeDisplay.getCompanyId() %>&themeId=<%= themeDisplay.getTheme().getThemeId() %>&colorSchemeId=<%= themeDisplay.getColorScheme().getColorSchemeId() %>" rel="stylesheet" type="text/css" />

	<c:if test="<%= (layout != null) && Validator.isNotNull(layout.getCssText()) %>">
		<style type="text/css">
			<%= layout.getCssText() %>
		</style>
	</c:if>
</head>

<body>

<%= request.getAttribute(WebKeys.JOURNAL_ARTICLE_CONTENT) %>

</body>

</html>
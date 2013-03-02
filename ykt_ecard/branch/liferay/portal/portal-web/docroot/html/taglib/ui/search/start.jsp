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

<%@ include file="/html/taglib/ui/search/init.jsp" %>

<%
String defaultKeywords = LanguageUtil.get(pageContext, "search") + "...";
String unicodeDefaultKeywords = UnicodeFormatter.toString(defaultKeywords);

String keywords = ParamUtil.getString(request, namespace + "keywords", defaultKeywords);

PortletURL portletURL = new PortletURLImpl(request, PortletKeys.SEARCH, plid.longValue(), false);

portletURL.setWindowState(WindowState.MAXIMIZED);
portletURL.setPortletMode(PortletMode.VIEW);

portletURL.setParameter("struts_action", "/search/search");
%>

<form action="<%= portletURL.toString() %>" method="post" name="<%= namespace %>fm" onSubmit="submitForm(this); return false;">

<input name="<%= namespace %>keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" onBlur="if (this.value == '') { this.value = '<%= unicodeDefaultKeywords %>'; }" onFocus="if (this.value == '<%= unicodeDefaultKeywords %>') { this.value = ''; }" />

<input align="absmiddle" border="0" src="<%= themeDisplay.getPathThemeImages() %>/common/search.png" title="<liferay-ui:message key="search" />" type="image" />
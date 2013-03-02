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

<%@ include file="/html/taglib/ui/icon/init.jsp" %>

<%
if (url.startsWith(Http.HTTP_WITH_SLASH) || url.startsWith(Http.HTTPS_WITH_SLASH)) {
	url = "javascript: submitForm(document.hrefFm, '" + HttpUtil.encodeURL(url) + "');";
}

String targetHtml = StringPool.BLANK;

if (!target.equals("_self")) {
	targetHtml = "target=\"" + target + "\"";
}
%>

<c:choose>
	<c:when test="<%= (iconMenuIconCount != null) && (iconMenuSingleIcon == null) %>">
		<li><nobr><a href="<%= url %>" <%= targetHtml %>><img align="absmiddle" border="0" src="<%= src %>" <%= details %> /> <liferay-ui:message key="<%= message %>" /></a></nobr></li>
	</c:when>
	<c:otherwise>
		<nobr><a href="<%= url %>" <%= targetHtml %>><img align="absmiddle" border="0" src="<%= src %>" <%= details %> /></a><c:if test="<%= label %>"> <a href="<%= url %>" <%= targetHtml %>><liferay-ui:message key="<%= message %>" /></a></c:if></nobr>
	</c:otherwise>
</c:choose>
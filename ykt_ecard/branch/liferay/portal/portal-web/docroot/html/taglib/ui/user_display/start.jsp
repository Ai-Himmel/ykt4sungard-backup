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

<%@ include file="/html/taglib/ui/user_display/init.jsp" %>

<%
long portraitId = 0;
String tokenId = StringPool.BLANK;

if (userDisplay != null) {
	portraitId = userDisplay.getPortraitId();
	tokenId = ImageServletTokenUtil.getToken(userDisplay.getPortraitId());
}

if (Validator.isNull(url) && (userDisplay != null)) {
	url = userDisplay.getDisplayURL(themeDisplay.getURLPortal());
}
%>

<c:if test="<%= displayStyle == 1 %>">
	<table class="lfr-table">
	<tr>
		<td valign="top">
</c:if>

<c:if test="<%= displayStyle == 2 %>">
	<%--<div style="white-space: nowrap;">--%>
	<div>
</c:if>

<c:if test="<%= Validator.isNotNull(url) %>"><a href="<%= url %>"></c:if>

<div>
	<img border="0" src="<%= themeDisplay.getPathImage() %>/user_portrait?img_id=<%= portraitId %>&t=<%= tokenId %>" width="65" />
</div>

<c:if test="<%= Validator.isNotNull(url) %>"></a></c:if>

<c:if test="<%= displayStyle == 1 %>">
	</td>
	<td valign="top">
</c:if>

<c:if test="<%= displayStyle == 2 %>">
</c:if>

<c:choose>
	<c:when test="<%= userDisplay != null %>">
		<c:if test="<%= Validator.isNotNull(url) %>"><a href="<%= url %>"></c:if>

		<%= userDisplay.getFullName() %>

		<c:if test="<%= Validator.isNotNull(url) %>"></a></c:if>

		<c:if test="<%= MessagingUtil.isJabberEnabled() && themeDisplay.isSignedIn() %>">
			<a href="javascript: Messaging.chat({toId:'<%= userId %>', toName:'<%= userDisplay.getFullName() %>'});"><img src="<%= themeDisplay.getPathThemeImages() %>/chat/user_offline.png" /></a>
		</c:if>

		<br />
	</c:when>
	<c:otherwise>
		<%= userName %>
	</c:otherwise>
</c:choose>
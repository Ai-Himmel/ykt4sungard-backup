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

<%@ include file="/html/portlet/chat/init.jsp" %>

<c:choose>
	<c:when test="<%= MessagingUtil.isJabberEnabled() %>">
		<div id="portlet-chat-roster-list" style="margin-bottom: 5px;"></div>

		<img style="cursor: pointer" align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/chat/delete_user.png" onclick="MessagingRoster.deleteEntries()" />
		<img style="cursor: pointer" align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/chat/add_user.png" onclick="MessagingRoster.toggleEmail()" />

		<div id="portlet-chat-roster-email-div" class="font-small" style="display: none; margin-top: 3px">
			<liferay-ui:message key="email" /> <input id="portlet-chat-roster-email" name="email" onkeypress="MessagingRoster.onEmailKeypress(this, event)" type="text"  />
		</div>

		<script type="text/javascript">
			Messaging.checkRoster = true;
			MessagingRoster.getEntries();
			MessagingRoster.highlightColor = "";
		</script>
	</c:when>
	<c:otherwise>
		<liferay-util:include page="/html/portal/portlet_inactive.jsp" />
	</c:otherwise>
</c:choose>
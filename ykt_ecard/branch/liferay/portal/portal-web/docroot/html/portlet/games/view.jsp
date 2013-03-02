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

<%@ include file="/html/portlet/games/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "hangman");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setParameter("struts_action", "/games/view");
portletURL.setParameter("tabs1", tabs1);
%>

<form action="<portlet:renderURL><portlet:param name="struts_action" value="/games/view" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />

<liferay-ui:tabs
	names="hangman,minesweeper"
	url="<%= portletURL.toString() %>"
/>

<c:choose>
	<c:when test='<%= tabs1.equals("hangman") %>'>
		<applet archive="hangman.jar" code="com.liferay.applets.hangman.Hangman" codebase="<%= themeDisplay.getPathApplet() %>" height="150" width="300">
			<param name="word_list" value="<%= hangmanWordList %>" />
		</applet>
	</c:when>
	<c:when test='<%= tabs1.equals("minesweeper") %>'>

		<%
		String level = ParamUtil.get(request, "level", "beginner");

		int appletHeight = 195;
		int appletWidth = 152;

		if (level.equals("intermediate")) {
			appletHeight = 323;
			appletWidth = 280;
		}
		else if (level.equals("expert")) {
			appletHeight = 323;
			appletWidth = 504;
		}
		%>

		<input name="<portlet:namespace />level" type="hidden" value="<%= level %>" />

		<select onChange="document.<portlet:namespace />fm.<portlet:namespace />level.value = this[this.selectedIndex].value; submitForm(document.<portlet:namespace />fm);">
			<option value="beginner"><liferay-ui:message key="beginner" /></option>
			<option <%= level.equals("intermediate") ? "selected" : "" %> value="intermediate"><liferay-ui:message key="intermediate" /></option>
			<option <%= level.equals("expert") ? "selected" : "" %> value="expert"><liferay-ui:message key="expert" /></option>
		</select>

		<input type="submit" value="<liferay-ui:message key="new-game" />" />

		<br /><br />

		<applet archive="minesweeper.jar" code="jmapplet" codebase="<%= themeDisplay.getPathApplet() %>" height="<%= appletHeight %>" width="<%= appletWidth %>">
			<param name="level" value="<%= level %>" />
		</applet>
	</c:when>
</c:choose>

</form>
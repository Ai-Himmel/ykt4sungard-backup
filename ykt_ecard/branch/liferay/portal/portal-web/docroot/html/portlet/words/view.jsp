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

<%@ include file="/html/portlet/words/init.jsp" %>

<%
String word = ParamUtil.getString(request, "word");
boolean scramble = ParamUtil.getBoolean(request, "scramble", true);

String[] words = (String[])request.getAttribute(WebKeys.WORDS_LIST);
%>

<form action="<portlet:renderURL><portlet:param name="struts_action" value="/words/view" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.SEARCH %>" />

<liferay-ui:error exception="<%= ScramblerException.class %>" message="please-enter-a-word-that-is-at-least-3-characters-long" />

<input name="<portlet:namespace />word" type="text" value="<%= Html.escape(word) %>" />

<select name="<portlet:namespace />scramble">
	<option <%= scramble ? "selected" : "" %> value="1"><liferay-ui:message key="scramble" /></option>
	<option <%= !scramble ? "selected" : "" %> value="0"><liferay-ui:message key="unscramble" /></option>
</select>

<input type="submit" value="<liferay-ui:message key="search" />" />

<c:if test="<%= (words != null) && (words.length > 0) %>">
	<br /><br />

	<%
	for (int i = 0; i < words.length; i++) {
	%>

		<%= Html.escape(words[i]) %><br />

	<%
	}
	%>

</c:if>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />word);
	</script>
</c:if>
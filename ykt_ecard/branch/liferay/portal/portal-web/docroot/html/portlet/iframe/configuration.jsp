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

<%@ include file="/html/portlet/iframe/init.jsp" %>

<%
String htmlAttributes =
	"border=" + border + "\n" +
	"bordercolor=" + bordercolor + "\n" +
	"frameborder=" + frameborder + "\n" +
	"height-maximized=" + heightMaximized + "\n" +
	"height-normal=" + heightNormal + "\n" +
	"hspace=" + hspace + "\n" +
	"scrolling=" + scrolling + "\n" +
	"vspace=" + vspace + "\n" +
	"width=" + width + "\n";
%>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />

<div class="portlet-msg-info">
<liferay-ui:message key="leave-the-user-name-and-password-fields-blank-to-use-your-current-login-information" />
</div>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="source-url" />
	</td>
	<td>
		<span id="<portlet:namespace />context-path-text" style='<%= relative ? "" : "display: none;" %>'>...<%= themeDisplay.getPathContext() %></span> <input class="lfr-input-text" name="<portlet:namespace />src" type="text" value="<%= src %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="relative-to-context-path" />
	</td>
	<td>

		<%
		String relativeOnClick = "jQuery(\"#" + renderResponse.getNamespace() + "context-path-text\").toggle();";
		%>

		<liferay-ui:input-checkbox param="relative" defaultValue="<%= relative %>" onClick="<%= relativeOnClick %>" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="authenticate" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="auth" defaultValue="<%= auth %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="authentication-type" />
	</td>
	<td>
		<select name="<portlet:namespace />authType">
			<option <%= (authType.equals("basic")) ? "selected" : "" %> value="basic">Basic</option>
			<option <%= (authType.equals("form")) ? "selected" : "" %> value="form">Form</option>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="form-method" />
	</td>
	<td>
		<select name="<portlet:namespace />formMethod">
			<option <%= (formMethod.equals("get")) ? "selected" : "" %> value="get">Get</option>
			<option <%= (formMethod.equals("post")) ? "selected" : "" %> value="post">Post</option>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="user-name" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />userName" type="text" value="<%= userName %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="password" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />password" type="text" value="<%= password %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="hidden-variables" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />hiddenVariables" type="text" value="<%= hiddenVariables %>" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="html-attributes" />
	</td>
	<td>
		<textarea class="lfr-textarea" name="<portlet:namespace />htmlAttributes" wrap="soft" onKeyDown="Liferay.Util.checkTab(this); Liferay.Util.disableEsc();"><%= htmlAttributes %></textarea>
	</td>
</tr>
</table>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />src);
	</script>
</c:if>
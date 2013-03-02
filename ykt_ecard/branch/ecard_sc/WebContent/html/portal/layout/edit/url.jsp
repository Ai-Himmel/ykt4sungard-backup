<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

<%@ include file="/html/portal/init.jsp" %>

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td>
		<font class="gamma" size="2"><b><%= LanguageUtil.get(pageContext, "url") %></b></font>
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td>
		<input class="form-text" name="TypeSettingsProperties(url)" size="70" type="text" value="<bean:write name="SEL_LAYOUT" property="typeSettingsProperties(url)" />">
	</td>
</tr>
<tr>
	<td colspan="3"><img border="0" height="2" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
</tr>
<tr>
	<td>
		<font class="gamma" size="2"><b><%= LanguageUtil.get(pageContext, "description") %></b></font>
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td>
		<textarea class="form-text" cols="70" name="TypeSettingsProperties(description)" rows="10" wrap="soft"><bean:write name="SEL_LAYOUT" property="typeSettingsProperties(description)" /></textarea>
	</td>
</tr>
</table>
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

<form action="<%= themeDisplay.getPathMain() %>/portal/language" method="post" name="fm">
<input name="<%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>">

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td>
		<table border="0" cellpadding="0" cellspacing="2">
		<tr>
			<td>
				<font class="gamma" size="2"><b><%= LanguageUtil.get(pageContext, "language") %></b></font>
			</td>
			<td width="10">
				&nbsp;
			</td>
			<td>
				<select name="language_id" onChange="submitForm(document.fm);">

				<%
				Locale[] locales = LanguageUtil.getAvailableLocales();

				for (int i = 0; i < locales.length; i++) {
				%>

					<option <%= (locale.getLanguage().equals(locales[i].getLanguage()) && locale.getCountry().equals(locales[i].getCountry())) ? "selected" : "" %> value="<%= locales[i].getLanguage() + "_" + locales[i].getCountry() %>"><%= locales[i].getDisplayName(locale) %></option>

				<%
				}
				%>

				</select>
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

</form>
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

<%
String layoutFriendlyUrl = request.getParameter("p_l_friendly_url");
if ((layoutFriendlyUrl == null) || (layoutFriendlyUrl.equals(StringPool.NULL))) {
	if (selLayout != null) {
		layoutFriendlyUrl = GetterUtil.getString(selLayout.getFriendlyURL());
	}
	else {
		layoutFriendlyUrl = StringPool.BLANK;
	}
}
%>

<script language="JavaScript">
	function deletePage() {
		if (confirm("<%= UnicodeLanguageUtil.format(pageContext, "are-you-sure-you-want-to-delete-this-layout-and-all-of-its-children", "20", false) %>")) {
			document.fm.<%= Constants.CMD %>.value = "<%= Constants.DELETE %>";
			document.fm.referer.value = "<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayout.getParentLayoutId() %>";
			submitForm(document.fm);
		}
	}

	function updatePage() {
		document.fm.<%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";
		submitForm(document.fm);
	}
</script>

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tr>
	<td>
		<font class="gamma" size="2"><b>
		<%= LanguageUtil.get(pageContext, "id") %>
		</b></font>
	</td>
	<td width="20">
		&nbsp;
	</td>
	<td>
		<font class="gamma" size="2">
		<%= selLayout.getLayoutId() %>
		</font>
	</td>
	<td align="right" valign="top">
		<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "update-page") %>" onClick="updatePage();">

		<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "delete-page") %>" onClick="deletePage();">
	</td>

</tr>

<c:if test="<%= SessionErrors.contains(request, LayoutNameException.class.getName()) %>">
	<tr>
		<td colspan="4">
			<font class="gamma" size="1"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "please-enter-a-valid-name") %></span></font>
		</td>
	</tr>
</c:if>

<tr>
	<td>
		<font class="gamma" size="2"><b>
		<%= LanguageUtil.get(pageContext, "name") %>
		</b></font>
	</td>
	<td width="20">
		&nbsp;
	</td>
	<td colspan="2">
		<input class="form-text" name="p_l_name" size="20" type="text" value="<%= layoutName %>" onKeyPress="if (event.keyCode == 13) { updatePage(); }">
	</td>
</tr>

<c:if test="<%= group != null && layout.getType().equals(Layout.TYPE_PORTLET) %>">
	<c:if test="<%= SessionErrors.contains(request, LayoutFriendlyURLException.class.getName()) %>">

		<%
		LayoutFriendlyURLException lfurle = (LayoutFriendlyURLException)SessionErrors.get(request, LayoutFriendlyURLException.class.getName());
		%>

		<tr>
			<td colspan="4">
				<font class="gamma" size="1"><span class="gamma-neg-alert">

				<c:if test="<%= lfurle.getType() == LayoutFriendlyURLException.DOES_NOT_START_WITH_SLASH %>">
					<%= LanguageUtil.get(pageContext, "please-enter-a-friendly-url-that-begins-with-a-slash") %>
				</c:if>

				<c:if test="<%= lfurle.getType() == LayoutFriendlyURLException.ENDS_WITH_SLASH %>">
					<%= LanguageUtil.get(pageContext, "please-enter-a-friendly-url-that-does-not-end-with-a-slash") %>
				</c:if>

				<c:if test="<%= lfurle.getType() == LayoutFriendlyURLException.TOO_SHORT %>">
					<%= LanguageUtil.get(pageContext, "please-enter-a-friendly-url-that-is-at-least-two-characters-long") %>
				</c:if>

				<c:if test="<%= lfurle.getType() == LayoutFriendlyURLException.ADJACENT_SLASHES %>">
					<%= LanguageUtil.get(pageContext, "please-enter-a-friendly-url-that-does-not-have-adjacent-slashes") %>
				</c:if>

				<c:if test="<%= lfurle.getType() == LayoutFriendlyURLException.INVALID_CHARACTERS %>">
					<%= LanguageUtil.get(pageContext, "please-enter-a-friendly-url-with-valid-characters") %>
				</c:if>

				<c:if test="<%= lfurle.getType() == LayoutFriendlyURLException.DUPLICATE %>">
					<%= LanguageUtil.get(pageContext, "please-enter-a-unique-friendly-url") %>
				</c:if>

				</span></font>
			</td>
		</tr>
	</c:if>

	<tr>
		<td>
			<font class="gamma" size="2"><b>
			<%= LanguageUtil.get(pageContext, "friendly-url") %>
			</b></font>
		</td>
		<td width="20">
			&nbsp;
		</td>
		<td colspan="2">
			<input class="form-text" name="p_l_friendly_url" size="50" type="text" value="<%= layoutFriendlyUrl %>" onKeyPress="if (event.keyCode == 13) { updatePage(); }">
		</td>
	</tr>
</c:if>

</table>

<script language="JavaScript">
	document.fm.p_l_name.focus();
</script>

<br><div class="beta-separator"></div><br>

<liferay:include page="<%= Constants.TEXT_HTML_DIR + PortalUtil.getLayoutEditPage(selLayout) %>" />
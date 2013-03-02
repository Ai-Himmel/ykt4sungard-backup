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
String layoutType = ParamUtil.getString(request, "p_l_type");
%>

<script language="JavaScript">
	function addNewPage() {
		document.fm.<%= Constants.CMD %>.value = "<%= Constants.ADD %>";
		submitForm(document.fm);
	}

	function updateDisplayOrder() {
		document.fm.<%= Constants.CMD %>.value = "update_display_order";
		document.fm.p_l_display_order.value = listSelect(document.fm.p_l_display_order_box);
		submitForm(document.fm);
	}
</script>

<input name="p_l_display_order" type="hidden" value="">

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td colspan="3">
		<font class="gamma" size="1">
		<%= LanguageUtil.get(pageContext, "add-child-pages") %>
		</font>
	</td>
</tr>
<tr>
	<td colspan="3">
		<br>
	</td>
</tr>

<c:if test="<%= SessionErrors.contains(request, LayoutNameException.class.getName()) %>">
	<tr>
		<td colspan="3">
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
	<td width="10">
		&nbsp;
	</td>
	<td>
		<input class="form-text" name="p_l_name" size="20" type="text" value="<%= layoutName %>" onKeyPress="if (event.keyCode == 13) { addNewPage(); }">
	</td>
</tr>
<tr>
	<td colspan="3"><img border="0" height="2" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
</tr>

<c:if test="<%= SessionErrors.contains(request, LayoutTypeException.class.getName()) %>">
	<tr>
		<td colspan="3">
			<font class="gamma" size="1"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "your-first-page-must-be-a-portlet-page") %></span></font>
		</td>
	</tr>
</c:if>

<tr>
	<td>
		<font class="gamma" size="2"><b>
		<%= LanguageUtil.get(pageContext, "type") %>
		</b></font>
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td>
		<select name="p_l_type">

			<%
			for (int i = 0; i < Layout.TYPES.length; i++) {
			%>

				<option <%= layoutType.equals(Layout.TYPES[i]) ? "selected" : "" %> value="<%= Layout.TYPES[i] %>"><%= LanguageUtil.get(pageContext, "layout-types-" + Layout.TYPES[i]) %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
<tr>
	<td colspan="3">
		<br>
	</td>
</tr>
<tr>
	<td colspan="3">
		<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "add-new-page") %>" onClick="addNewPage();">
	</td>
</tr>
</table>

<script language="JavaScript">
	document.fm.p_l_name.focus();
</script>

<%
List selLayoutChildren = null;
if (selLayout != null) {
	selLayoutChildren = selLayout.getChildren();
}
%>

<c:if test="<%= (selLayoutChildren != null) && (selLayoutChildren.size() > 0) %>">
	<br><div class="beta-separator"></div><br>

	<table border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td>
			<font class="gamma" size="1">
			<%= LanguageUtil.get(pageContext, "set-the-display-order-of-child-pages") %>
			</font>
		</td>
	</tr>
	<tr>
		<td>
			<br>
		</td>
	</tr>
	<tr>
		<td>
			<c:if test="<%= SessionErrors.contains(request, RequiredLayoutException.class.getName()) %>">
				<table border="0" cellpadding="0" cellspacing="0">
				<tr>
					<td>
						<font class="gamma" size="1"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "your-first-page-must-be-a-portlet-page") %></span></font>
					</td>
				</tr>
				<tr>
					<td><img border="0" height="2" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
				</tr>
				</table>
			</c:if>

			<table border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td>
					<select name="p_l_display_order_box" size="7">

					<%
					for (int i = 0; i < selLayoutChildren.size(); i++) {
						Layout selLayoutChild = (Layout)selLayoutChildren.get(i);
					%>

						<option value="<%= selLayoutChild.getLayoutId() %>"><%= selLayoutChild.getName() %></option>

					<%
					}
					%>

					</select>
				</td>
				<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="2"></td>
				<td valign="top">
					<a class="gamma" href="javascript: reorder(document.fm.p_l_display_order_box, 0);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_up.gif" vspace="2" width="16"></a><br>
					<a class="gamma" href="javascript: reorder(document.fm.p_l_display_order_box, 1);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_down.gif" vspace="2" width="16"></a><br>
					<a class="gamma" href="javascript: removeItem(document.fm.p_l_display_order_box);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_x.gif" vspace="2" width="16"></a><br>
				</td>
			</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td>
			<br>
		</td>
	</tr>
	<tr>
		<td>
			<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "update-display-order") %>" onClick="updateDisplayOrder();">
		</td>
	</tr>
	</table>
</c:if>
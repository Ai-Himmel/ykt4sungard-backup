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

<%@ include file="/html/portal/personalize_init.jsp" %>

<%
String selCategoryName = ParamUtil.getString(request, "p_c_name");
if (selCategoryName.equals(StringPool.BLANK)) {
	selCategoryName = SessionClicks.get(request, "p_c_name");
}

String columnOrder = (String)request.getAttribute(WebKeys.LAYOUT_COLUMN_ORDER);
String[] columnOrderArray = StringUtil.split(columnOrder);

Portlet[] narrow1Portlets = (Portlet[])request.getAttribute(WebKeys.LAYOUT_NARROW_1_PORTLETS);
Portlet[] narrow2Portlets = (Portlet[])request.getAttribute(WebKeys.LAYOUT_NARROW_2_PORTLETS);
Portlet[] wide1Portlets = (Portlet[])request.getAttribute(WebKeys.LAYOUT_WIDE_1_PORTLETS);
%>

<script language="JavaScript">
	function updateNumberOfColumns(numOfColumns) {
		numOfColumns++;

		if (numOfColumns == 1) {
			self.location = "<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=w1,&p_l_wide_1_list=" + listSelect(document.fm.p_l_narrow_1) + listSelect(document.fm.p_l_narrow_2) + listSelect(document.fm.p_l_wide_1) + "&#p_content";
		}
		else if (numOfColumns == 2) {
			self.location = "<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=n1,w1,&p_l_narrow_1_list=" + listSelect(document.fm.p_l_narrow_1) + listSelect(document.fm.p_l_narrow_2) + "&p_l_wide_1_list=" + listSelect(document.fm.p_l_wide_1) + "&#p_content";
		}
		else if (numOfColumns == 3) {
			self.location = "<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=n1,w1,n2,&p_l_narrow_1_list=" + listSelect(document.fm.p_l_narrow_1) + "&p_l_narrow_2_list=&p_l_wide_1_list=" + listSelect(document.fm.p_l_wide_1) + "&#p_content";
		}
	}

	function updatePage() {
		var portletList = listSelect(document.fm.p_l_narrow_1) + listSelect(document.fm.p_l_narrow_2) + listSelect(document.fm.p_l_wide_1);

		if (count(portletList, ',') > 20) {
			alert("<%= UnicodeLanguageUtil.format(pageContext, "a-page-may-not-contain-more-than-x-portlets", "20", false) %>");
		}
		else {
			document.fm.<%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";
			document.fm.p_l_list.value = portletList;
			document.fm.p_l_narrow_1_list.value = listSelect(document.fm.p_l_narrow_1);
			document.fm.p_l_narrow_2_list.value = listSelect(document.fm.p_l_narrow_2);
			document.fm.p_l_wide_1_list.value = listSelect(document.fm.p_l_wide_1);
			submitForm(document.fm);
		}
	}
</script>

<input name="p_l_column_order" type="hidden" value="<%= columnOrder %>">
<input name="p_l_list" type="hidden" value="">
<input name="p_l_narrow_1_list" type="hidden" value="">
<input name="p_l_narrow_2_list" type="hidden" value="">
<input name="p_l_wide_1_list" type="hidden" value="">

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tr>
	<td>

		<%

		// Clone the layout and the layout type, because the layout type
		// holds a reference to the layout

		Layout curLayout = layout;
		layout = (Layout)curLayout.clone();

		LayoutTypePortlet curLayoutTypePortlet = layoutTypePortlet;
		layoutTypePortlet = (LayoutTypePortlet)layout.getLayoutType();

		layoutTypePortlet.setNarrow1Portlets(narrow1Portlets);
		layoutTypePortlet.setNarrow2Portlets(narrow2Portlets);
		layoutTypePortlet.setWide1Portlets(wide1Portlets);
		%>

		<%@ include file="/html/portal/layout/edit/portlet_by_category.jsp" %>

		<%
		layout = curLayout;
		layoutTypePortlet = curLayoutTypePortlet;
		%>

	</td>
</tr>
</table>

<br>

<a name="p_content"></a>

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tr>
	<td class="alpha">
		<table border="0" cellpadding="2" cellspacing="1" width="100%">
		<tr>

		<%
		for (int i = 0; i < columnOrderArray.length; i++) {
		%>

			<c:if test='<%= columnOrderArray[i].equals("n1") %>'>
				<%@ include file="/html/portal/layout/edit/portlet_narrow_1.jsp" %>
			</c:if>
			<c:if test='<%= columnOrderArray[i].equals("n2") %>'>
				<%@ include file="/html/portal/layout/edit/portlet_narrow_2.jsp" %>
			</c:if>
			<c:if test='<%= columnOrderArray[i].equals("w1") %>'>
				<%@ include file="/html/portal/layout/edit/portlet_wide_1.jsp" %>
			</c:if>

		<%
		}
		%>

		</tr>

		<c:if test="<%= columnOrderArray.length > 1 %>">
			<tr>
				<c:if test="<%= columnOrderArray.length == 2 %>">
					<td align="center" class="gamma">
						<table border="0" cellpadding="4" cellspacing="0">
						<tr>
							<td nowrap><font class="gamma" size="1"><b><%= LanguageUtil.get(pageContext, "move-column") %></b></font></td>
							<td><a class="gamma" href="javascript: self.location = '<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=<%= (columnOrder.startsWith("n")) ? "w1,n1," : "n1,w1," %>&p_l_narrow_1_list=' + listSelect(document.fm.p_l_narrow_1) + '&p_l_wide_1_list=' + listSelect(document.fm.p_l_wide_1) + '&#p_content';"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_right.gif" vspace="2" width="16"></a></td>
						</tr>
						</table>
					</td>
					<td align="center" class="gamma">
						<table border="0" cellpadding="4" cellspacing="0">
						<tr>
							<td><a class="gamma" href="javascript: self.location = '<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=<%= (columnOrder.startsWith("n")) ? "w1,n1," : "n1,w1," %>&p_l_narrow_1_list=' + listSelect(document.fm.p_l_narrow_1) + '&p_l_wide_1_list=' + listSelect(document.fm.p_l_wide_1) + '&#p_content';"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_left.gif" vspace="2" width="16"></a></td>
							<td nowrap><font class="gamma" size="1"><b><%= LanguageUtil.get(pageContext, "move-column") %></b></font></td>
						</tr>
						</table>
					</td>
				</c:if>

				<c:if test="<%= columnOrderArray.length == 3 %>">

					<%
					String rightColOrder = columnOrderArray[1] + StringPool.COMMA + columnOrderArray[0] + StringPool.COMMA + columnOrderArray[2] + StringPool.COMMA;
					String leftColOrder = columnOrderArray[0] + StringPool.COMMA + columnOrderArray[2] + StringPool.COMMA + columnOrderArray[1] + StringPool.COMMA;
					%>

					<td align="center" class="gamma">
						<table border="0" cellpadding="4" cellspacing="0">
						<tr>
							<td nowrap><font class="gamma" size="1"><b><%= LanguageUtil.get(pageContext, "move-column") %></b></font></td>
							<td><a class="gamma" href="javascript: javascript: self.location = '<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=<%= rightColOrder %>&p_l_narrow_1_list=' + listSelect(document.fm.p_l_narrow_1) + '&p_l_narrow_2_list=' + listSelect(document.fm.p_l_narrow_2) + '&p_l_wide_1_list=' + listSelect(document.fm.p_l_wide_1) + '&#p_content';"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_right.gif" vspace="2" width="16"></a></td>
						</tr>
						</table>
					</td>
					<td align="center" class="gamma">
						<table border="0" cellpadding="4" cellspacing="0">
						<tr>
							<td><a class="gamma" href="javascript: self.location = '<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=<%= rightColOrder %>&p_l_narrow_1_list=' + listSelect(document.fm.p_l_narrow_1) + '&p_l_narrow_2_list=' + listSelect(document.fm.p_l_narrow_2) + '&p_l_wide_1_list=' + listSelect(document.fm.p_l_wide_1) + '&#p_content';"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_left.gif" vspace="2" width="16"></a></td>
							<td nowrap><font class="gamma" size="1"><b><%= LanguageUtil.get(pageContext, "move-column") %></b></font></td>
							<td><a class="gamma" href="javascript: self.location = '<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=<%= leftColOrder %>&p_l_narrow_1_list=' + listSelect(document.fm.p_l_narrow_1) + '&p_l_narrow_2_list=' + listSelect(document.fm.p_l_narrow_2) + '&p_l_wide_1_list=' + listSelect(document.fm.p_l_wide_1) + '&#p_content';"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_right.gif" vspace="2" width="16"></a></td>
						</tr>
						</table>
					</td>
					<td align="center" class="gamma">
						<table border="0" cellpadding="4" cellspacing="0">
						<tr>
							<td><a class="gamma" href="javascript: self.location = '<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>&p_l_column_order=<%= leftColOrder %>&p_l_narrow_1_list=' + listSelect(document.fm.p_l_narrow_1) + '&p_l_narrow_2_list=' + listSelect(document.fm.p_l_narrow_2) + '&p_l_wide_1_list=' + listSelect(document.fm.p_l_wide_1) + '&#p_content';"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_left.gif" vspace="2" width="16"></a></td>
							<td nowrap><font class="gamma" size="1"><b><%= LanguageUtil.get(pageContext, "move-column") %></b></font></td>
						</tr>
						</table>
					</td>
				</c:if>
			</tr>
		</c:if>

		</table>
	</td>
</tr>
</table>

<br>

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td>
		<font class="gamma" size="2"><b>
		<%= LanguageUtil.get(pageContext, "number-of-columns") %>
		</b></font>
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td>
		<select onChange="updateNumberOfColumns(this.selectedIndex);">
			<option <%= (columnOrderArray.length == 1) ? "selected" : "" %> value="1"><%= LanguageUtil.get(pageContext, "one-column") %></option>
			<option <%= (columnOrderArray.length == 2) ? "selected" : "" %> value="2"><%= LanguageUtil.get(pageContext, "two-columns") %></option>
			<option <%= (columnOrderArray.length == 3) ? "selected" : "" %> value="3"><%= LanguageUtil.get(pageContext, "three-columns") %></option>
		</select>
	</td>
</tr>
</table>

<br><div class="beta-separator"></div><br>

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td valign="top">
		<font class="gamma" size="2">
		<%= LanguageUtil.get(pageContext, "you-can-quickly-copy-the-content-and-layout-for-this-page-if-you-specify-the-page-id-to-copy-from") %>
		</font>
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td valign="top">
		<input class="form-text" name="p_l_copy_id" size="5" type="text" value="">
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td valign="top">
		<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "copy-page") %>" onClick="updatePage();">
	</td>
</tr>
</table>
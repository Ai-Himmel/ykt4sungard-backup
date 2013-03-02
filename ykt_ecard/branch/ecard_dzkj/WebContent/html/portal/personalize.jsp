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

<form method="post" name="fm" onSubmit="return false;">
<input name="<%= Constants.CMD %>" type="hidden" value="">
<input name="referer" type="hidden" value="<%= path %>tab=<%= tab %>&p_sel_l_id=<%= selLayoutId %>">
<input name="group_id" type="hidden" value="<%= group != null ? group.getGroupId() : StringPool.BLANK %>">
<input name="p_sel_l_id" type="hidden" value="<%= selLayoutId %>">

<c:if test="<%= layouts == null %>">
	<table border="0" cellpadding="0" cellspacing="0" width="95%">
	<tr>
		<td>
			<font class="gamma" size="1"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "you-have-no-personalized-pages") %></span></font>
		</td>
	</tr>
	</table>

	<br>
</c:if>

<%
LayoutLister layoutLister = new LayoutLister();

LayoutView layoutView = null;
if (group == null) {
	layoutView = layoutLister.getLayoutView(user.getUserId());
}
else {
	layoutView = layoutLister.getLayoutView(Layout.GROUP + group.getGroupId());
}

List layoutList = layoutView.getLayoutList();
%>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td valign="top">

		<%@ include file="/html/portal/personalize_tree_js.jsp" %>

		<div>
			<script language="JavaScript">
				var layoutsTree = new Tree("layoutsTree", layoutsArray, layoutsIcons, "gamma");
				layoutsTree.create("<%= SessionTreeJSClicks.getOpenNodes(request, "layoutsTree") %>");
			</script>
		</div>
	</td>
	<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="20"></td>
	<td valign="top" width="75%">
		<ul id="gamma-tab">
			<c:if test="<%= selLayout != null %>">
				<li <%= tab.equals("layout") ? "id=\"current\"" : "" %>>
					<a class="gamma" href="<%= path %>tab=layout&p_sel_l_id=<%= selLayoutId %>"><%= LanguageUtil.get(pageContext, "modify-layout") %></a>
				</li>
			</c:if>

			<c:if test="<%= ((selLayout == null) || PortalUtil.isLayoutParentable(selLayout)) %>">
				<li <%= tab.equals("children") ? "id=\"current\"" : "" %>>
					<a class="gamma" href="<%= path %>tab=children&p_sel_l_id=<%= selLayoutId %>"><%= LanguageUtil.get(pageContext, "manage-children") %></a>
				</li>
			</c:if>
		</ul>

		<%
		String layoutName = request.getParameter("p_l_name");
		if ((layoutName == null) || (layoutName.equals(StringPool.NULL))) {
			if ((selLayout != null) && (tab.equals("layout"))) {
				layoutName = selLayout.getName();
			}
			else {
				layoutName = StringPool.BLANK;
			}
		}
		%>

		<c:choose>
			<c:when test='<%= tab.equals("children") %>'>
				<%@ include file="/html/portal/personalize_children.jsp" %>
			</c:when>
			<c:otherwise>
				<%@ include file="/html/portal/personalize_layout.jsp" %>
			</c:otherwise>
		</c:choose>
	</td>
</tr>
</table>

</form>
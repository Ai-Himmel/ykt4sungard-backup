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
Map categories = (Map)WebAppPool.get(company.getCompanyId(), WebKeys.PORTLET_CATEGORIES);

List userRoles = UserLocalServiceUtil.getRoles(user.getUserId());

boolean newPage = false;
if (request.getAttribute("p_add_page") != null) {
	newPage = true;
}

String className = "bg";
if (newPage) {
	className = "gamma";
}
%>

<script language="JavaScript">
	function showCategory(categoryName) {
		document.getElementById('please.select.a.category').style.display = "none";

		<%
		Iterator itr = categories.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String categoryName = (String)entry.getKey();
		%>

			document.getElementById('<%= categoryName %>').style.display = "none";

		<%
		}
		%>

		document.getElementById(categoryName).style.display = "";

		document.fm.p_c_n.value = categoryName;
	}
</script>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td>
		<font class="<%= className %>" size="1">
		<%= LanguageUtil.get(pageContext, "n-signifies-narrow-portlets-and-w-signifies-wide-portlets") %>
		</font>
	</td>
</tr>
</table>

<br>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td valign="top" width="40%">
		<c:if test="<%= !BrowserSniffer.is_ns_4(request) %>">
			<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td class="alpha" width="1"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
				<td class="alpha" width="*">
					<table border="0" cellpadding="3" cellspacing="0">
					<tr>
						<td><font class="alpha" size="1"><b>&nbsp;<%= LanguageUtil.get(pageContext, "categories") %></b></font></td>
					</tr>
					</table>
				</td>
				<td  width="10"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="10"></td>
			</tr>
			<tr>
				<td class="alpha"></td>
				<td>
					<table border="0" cellpadding="4" cellspacing="2">
					<tr>
						<td>
							<font class="bg" size="2">

							<%
							int maxCategorySize = 0;

							itr = categories.entrySet().iterator();

							while (itr.hasNext()) {
								Map.Entry entry = (Map.Entry)itr.next();

								String categoryName = (String)entry.getKey();
								List kvps = (List)entry.getValue();

								if (kvps.size() > maxCategorySize) {
									maxCategorySize = kvps.size();
								}

								if (_hasCategory(kvps, user, userRoles)) {
							%>

									<a class="bg" href="javascript: showCategory('<%= categoryName %>');"><%= LanguageUtil.get(pageContext, categoryName) %></a><%= itr.hasNext() ? ",&nbsp;&nbsp;" : "" %>

							<%
								}
							}
							%>

							</font>

						</td>
					</tr>
					</table>
				</td>
				<td></td>
			</tr>
			</table>

			<%
			for (int i = 0; i <= maxCategorySize / 2 - 1; i++) {
			%>

				<br>

			<%
			}
			%>

		</c:if>
	</td>
	<td valign="top"  width="60%">
		<c:if test="<%= !BrowserSniffer.is_ns_4(request) %>">
			<table border="0" cellpadding="0" cellspacing="0" id="please.select.a.category" <%= (!selCategoryName.equals(StringPool.BLANK)) ? "style=\"display: none;\"" : "" %> width="100%">
			<tr>
				<td class="beta" width="1"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
				<td class="beta" width="*">
					<table border="0" cellpadding="3" cellspacing="0">
					<tr>
						<td><font class="beta" size="1"><b>&nbsp;<%= LanguageUtil.get(pageContext, "not-available") %></b></font></td>
					</tr>
					</table>
				</td>
				<td  width="10"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="10"></td>
			</tr>
			<tr>
				<td class="beta"></td>
				<td>
					<table border="0" cellpadding="4" cellspacing="2" width="100%">
					<tr>
						<td>
							<font class="beta" size="2"><span class="beta-neg-alert"><%= LanguageUtil.get(pageContext, "please-select-a-category") %></span></font>
						</td>
					</tr>
					</table>
				</td>
				<td></td>
			</tr>
			</table>
		</c:if>

		<%
		itr = categories.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String categoryName = (String)entry.getKey();
			List kvps = (List)entry.getValue();
		%>

			<table border="0" cellpadding="0" cellspacing="0" id="<%= categoryName %>" <%= (!selCategoryName.equals(categoryName)) ? "style=\"display: none;\"" : "" %> width="100%">
			<tr>
				<td class="beta" width="1"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
				<td class="beta" width="*">
					<table border="0" cellpadding="3" cellspacing="0">
					<tr>
						<td><font class="beta" size="1"><b>&nbsp;<%= LanguageUtil.get(pageContext, categoryName) %></b></font></td>
					</tr>
					</table>
				</td>
				<td  width="10"><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="10"></td>
			</tr>
			<tr>
				<td class="beta"></td>
				<td>
					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tr>
						<td valign="top">

							<%
							for (int j = 0; j < kvps.size(); j++) {
								KeyValuePair kvp = (KeyValuePair)kvps.get(j);
							%>

								<%= _formatPortlet(kvp.getKey(), kvp.getValue(), newPage, className, user, locale, userRoles, layout, application, pageContext) %>

								<c:if test="<%= (j + 1 == Math.ceil((double)kvps.size() / 2)) %>">
									</td><td valign="top">
								</c:if>

							<%
							}
							%>

						</td>
					</tr>
					</table>
				</td>
				<td></td>
			</tr>
			</table>

		<%
		}
		%>

	</td>
</tr>
</table>

<br>

<%!
private String _formatPortlet(String portletId, String status, boolean newPage, String className, User user, Locale locale, List userRoles, Layout layout, ServletContext application, PageContext pageContext) throws Exception {
	FastStringBuffer sb = new FastStringBuffer();

	Portlet portlet = PortletServiceUtil.getPortletById(user.getCompanyId(), portletId);

	if (portlet != null && portlet.isActive() && RoleLocalServiceUtil.hasRoles(user.getUserId(), userRoles, portlet.getRolesArray())) {
		String portletName = PortletConfigFactory.create(portlet, application).getResourceBundle(locale).getString(WebKeys.JAVAX_PORTLET_TITLE);
		String portletNameUnicode = UnicodeFormatter.toString(portletName);

		sb.append("<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\">");
		sb.append("<tr>");
		sb.append("<td><input ").append((!newPage && layout.hasPortletId(portletId)) ? "checked " : "").append("name=\"p_l_").append(portletId).append("\" type=\"checkbox\" value=\"").append(portletId).append("\" ");

		if (!newPage) {
			sb.append("onClick=\"");

			sb.append("if (this.checked) {");

			if (portlet.isNarrow()) {
				sb.append("if (document.fm.p_l_n1) { addItem(document.fm.p_l_n1, '").append(portletNameUnicode).append("', '").append(portletId).append("'); } else { addItem(document.fm.p_l_w, '").append(portletNameUnicode).append("', '").append(portletId).append("'); }");
			}
			else {
				sb.append("addItem(document.fm.p_l_w, '").append(portletNameUnicode).append("', '").append(portletId).append("');");
			}

			sb.append("}");
			sb.append("else {");

			sb.append("if (document.fm.p_l_n1) { removeItem(document.fm.p_l_n1").append(", '").append(portletId).append("'); }");
			sb.append("if (document.fm.p_l_narrow_2) { removeItem(document.fm.p_l_narrow_2").append(", '").append(portletId).append("'); }");
			sb.append("if (document.fm.p_l_w) { removeItem(document.fm.p_l_w").append(", '").append(portletId).append("'); }");

			sb.append("}");

			sb.append("\"");
		}

		sb.append("></td><td nowrap><font class=\"").append(className).append("\" size=\"1\">");

		sb.append(portletName).append(" (").append(portlet.isNarrow() ? "n" : "w").append(") ");

		if (status != null && status.equals("new")) {
			sb.append("<span class=\"").append(className).append("-pos-alert\"><i>").append(LanguageUtil.get(pageContext, "new")).append("</i></span>");
		}
		else if (status != null && status.equals("alpha")) {
			sb.append("<span class=\"").append(className).append("-neg-alert\"><i>").append(LanguageUtil.get(pageContext, "alpha")).append("</i></span>");
		}
		else if (status != null && status.equals("beta")) {
			sb.append("<span class=\"").append(className).append("-neg-alert\"><i>").append(LanguageUtil.get(pageContext, "beta")).append("</i></span>");
		}

		sb.append("</font></td>");
		sb.append("</tr></table>");

		return sb.toString();
	}

	return StringPool.BLANK;
}

private boolean _hasCategory(List kvps, User user, List userRoles) throws Exception {
	for (int i = 0; i < kvps.size(); i++) {
		KeyValuePair kvp = (KeyValuePair)kvps.get(i);

		Portlet portlet = PortletServiceUtil.getPortletById(user.getCompanyId(), kvp.getKey());

		if (portlet != null && portlet.isActive() && RoleLocalServiceUtil.hasRoles(user.getUserId(), userRoles, portlet.getRolesArray())) {
			return true;
		}
	}

	return false;
}
%>
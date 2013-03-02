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

<%
Group group = (Group)request.getAttribute(WebKeys.GROUP);

String path = themeDisplay.getPathMain() + "/portal/look_and_feel?";
if (group != null) {
	PortletURL editGroupLookAndFeelURL = new PortletURLImpl(request, PortletKeys.ADMIN, layoutId, true);

	editGroupLookAndFeelURL.setWindowState(WindowState.MAXIMIZED);
	editGroupLookAndFeelURL.setPortletMode(PortletMode.VIEW);

	editGroupLookAndFeelURL.setParameter("struts_action", "/admin/edit_group_look_and_feel");

	path = editGroupLookAndFeelURL.toString() + "&group_id=" + group.getGroupId() + "&";
}
%>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td valign="top" width="49%">
		<liferay:box top="/html/common/themes/inner_top.jsp" bottom="/html/common/themes/inner_bottom.jsp">
			<liferay:param name="box_title" value='<%= LanguageUtil.get(pageContext, "themes") %>' />
			<liferay:param name="box_width" value="100%" />

			<table border="0" cellpadding="0" cellspacing="0" width="100%">

			<%
			Theme[] themes = (Theme[])ThemeServiceUtil.getThemes().toArray(new Theme[0]);

			int numOfRows = 2;
			boolean start = true;

			for (int i = 0; i < themes.length; i++) {
				if (start == true) {
					start = false;
			%>

				<tr>

			<%
				}
			%>

				<td align="center" width="50%">
					<table border="0" cellpadding="2" cellspacing="0">
					<tr>
						<td align="center" valign="middle">
							<font class="bg" size="2">
							<%= themes[i].getName() %>
							</font>

							<input <%= theme.getThemeId().equals(themes[i].getThemeId()) ? "checked" : "" %> name="theme_id" type="radio" value="<%= themes[i].getThemeId() %>" onClick="self.location = '<%= path %><%= Constants.CMD %>=<%= Constants.UPDATE %>&theme_id=' + this.value + '&referer=<%= Http.encodeURL(path) %>';">
						</td>
					</tr>
					</table>

					<table border="0" cellpadding="1" cellspacing="1">
					<tr>
						<td>
							<img border="0" hspace="0" src="<%= themes[i].getContextPath() %><%= themes[i].getImagesPath() %>/thumbnail.gif" vspace="0">
						</td>
					</tr>
					</table>
				</td>

			<%
				if (start == false) {
					if (((i + 1) % numOfRows) == 0) {
						start = true;
			%>

						</tr>
						<tr>
							<td colspan="<%= numOfRows %>">
								<br>
							</td>
						</tr>

			<%
					}
				}
			}

			int mod = themes.length % numOfRows;

			if (mod > 0) {
				for (int i = mod; i < numOfRows; i++) {
			%>

					<td width="50%">
						&nbsp;
					</td>

			<%
				}
			%>

				</tr>

			<%
			}
			%>

			</table>
		</liferay:box>
	</td>
	<td width="2%">
		&nbsp;
	</td>
	<td valign="top" width="49%">
		<liferay:box top="/html/common/themes/inner_top.jsp" bottom="/html/common/themes/inner_bottom.jsp">
			<liferay:param name="box_title" value='<%= LanguageUtil.get(pageContext, "color-schemes") %>' />
			<liferay:param name="box_width" value="100%" />

			<table border="0" cellpadding="0" cellspacing="0" width="100%">

			<%
			ColorScheme[] colorSchemes = (ColorScheme[])theme.getColorSchemes().toArray(new ColorScheme[0]);

			int numOfRows = 2;
			boolean start = true;

			for (int i = 0; i < colorSchemes.length; i++) {
				if (start == true) {
					start = false;
			%>

				<tr>

			<%
				}
			%>

				<td align="center" width="50%">
					<table border="0" cellpadding="2" cellspacing="0">
					<tr>
						<td align="center" valign="middle">
							<font class="bg" size="2">
							<%= colorSchemes[i].getName() %>
							</font>

							<input <%= colorScheme.getColorSchemeId().equals(colorSchemes[i].getColorSchemeId()) ? "checked" : "" %> name="color_scheme_id" type="radio" value="<%= colorSchemes[i].getColorSchemeId() %>" onClick="self.location = '<%= path %><%= Constants.CMD %>=<%= Constants.UPDATE %>&theme_id=<%= theme.getThemeId() %>&color_scheme_id=' + this.value + '&referer=<%= Http.encodeURL(path) %>';">
						</td>
					</tr>
					</table>

					<table border="1" cellpadding="1" cellspacing="1">
					<tr>
						<td>
							<table border="0" cellpadding="2" cellspacing="0">
							<tr>
								<td bgcolor="<%= colorSchemes[i].getLayoutTabSelectedBg() %>">
									<font color="<%= colorSchemes[i].getLayoutTabSelectedText() %>" face="Tahoma, Verdana, Arial" size="2">&nbsp;<b>Tab Selected</b>&nbsp;</font>
								</td>
							</tr>
							<tr>
								<td bgcolor="<%= colorSchemes[i].getLayoutTabBg() %>">
									<font color="<%= colorSchemes[i].getLayoutTabText() %>" face="Tahoma, Verdana, Arial" size="2">&nbsp;<b>Tab Unselected</b>&nbsp;</font>
								</td>
							</tr>
							<tr>
								<td bgcolor="<%= colorSchemes[i].getPortletTitleBg() %>">
									<font color="<%= colorSchemes[i].getPortletTitleText() %>" face="Tahoma, Verdana, Arial" size="2">&nbsp;<b>Portlet Title</b>&nbsp;</font>
								</td>
							</tr>
							<tr>
								<td bgcolor="<%= colorSchemes[i].getPortletMenuBg() %>">
									<font color="<%= colorSchemes[i].getPortletMenuText() %>" face="Tahoma, Verdana, Arial" size="2">&nbsp;Portlet Menu&nbsp;</font>
								</td>
							</tr>
							<tr>
								<td bgcolor="<%= colorSchemes[i].getPortletBg() %>">
									<font color="<%= colorSchemes[i].getPortletFont() %>" face="Tahoma, Verdana, Arial" size="2">&nbsp;Portlet Body&nbsp;</font>
								</td>
							</tr>
							<tr>
								<td bgcolor="<%= colorSchemes[i].getLayoutBg() %>">
									<font color="<%= colorSchemes[i].getLayoutText() %>" face="Tahoma, Verdana, Arial" size="2">&nbsp;Page Background&nbsp;<br></font>
								</td>
							</tr>
							</table>
						</td>
					</tr>
					</table>
				</td>

			<%
				if (start == false) {
					if (((i + 1) % numOfRows) == 0) {
						start = true;
			%>

						</tr>
						<tr>
							<td colspan="<%= numOfRows %>">
								<br>
							</td>
						</tr>

			<%
					}
				}
			}

			int mod = colorSchemes.length % numOfRows;

			if (mod > 0) {
				for (int i = mod; i < numOfRows; i++) {
			%>

					<td width="50%">
						&nbsp;
					</td>

			<%
				}
			%>

				</tr>

			<%
			}
			%>

			</table>
		</liferay:box>
	</td>
</tr>
</table>
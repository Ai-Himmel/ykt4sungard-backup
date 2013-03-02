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

<td align="center" class="gamma" valign="top" width="<%= (columnOrderArray.length == 3) ? "50" : "75" %>%">
	<table border="0" cellpadding="2" cellspacing="0" width="100%">
	<tr>
		<td align="center" class="alpha" nowrap><font class="alpha" size="1"><b><%= LanguageUtil.get(pageContext, "wide-column") %></b></font></td>
	</tr>
	<tr>
		<td align="center">
			<table border="0" cellpadding="0" cellspacing="2">
			<tr>
				<td>
					<select name="p_l_wide_1" size="10">

					<%
					for (int j = 0; j < wide1Portlets.length; j++) {
						Portlet portlet = wide1Portlets[j];
					%>

						<option value="<%= portlet.getPortletId() %>">
						<%= PortletConfigFactory.create(portlet, application).getResourceBundle(locale).getString(WebKeys.JAVAX_PORTLET_TITLE) %>&nbsp;&nbsp;&nbsp;
						</option>

					<%
					}
					%>

					</select>
				</td>
				<td valign="top">
					<a class="gamma" href="javascript: reorder(document.fm.p_l_wide_1, 0);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_up.gif" vspace="2" width="16"></a><br>
					<a class="gamma" href="javascript: reorder(document.fm.p_l_wide_1, 1);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_down.gif" vspace="2" width="16"></a><br>
					<a class="gamma" href="javascript: eval('if (document.fm.p_l_' + document.fm.p_l_wide_1[document.fm.p_l_wide_1.selectedIndex].value + ') { document.fm.p_l_' + document.fm.p_l_wide_1[document.fm.p_l_wide_1.selectedIndex].value + '.checked = false; }'); removeItem(document.fm.p_l_wide_1);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/arrows/02_x.gif" vspace="2" width="16"></a><br>
				</td>
			</tr>
			</table>
		</td>
	</tr>
	</table>
</td>
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

<%@ include file="/html/portlet/communities/init.jsp" %>

<%
String tabs4 = (String)request.getAttribute("edit_pages.jsp-tab4");

long groupId = ((Long)request.getAttribute("edit_pages.jsp-groupId")).longValue();
long liveGroupId = ((Long)request.getAttribute("edit_pages.jsp-liveGroupId")).longValue();
long selPlid = ((Long)request.getAttribute("edit_pages.jsp-selPlid")).longValue();
boolean privateLayout = ((Boolean)request.getAttribute("edit_pages.jsp-privateLayout")).booleanValue();
Layout selLayout = (Layout)request.getAttribute("edit_pages.jsp-selLayout");

PortletURL portletURL = (PortletURL)request.getAttribute("edit_pages.jsp-portletURL");
%>

<liferay-ui:tabs
	names="regular-browsers,mobile-devices"
	param="tabs4"
	url='<%= portletURL.toString() + "&" + renderResponse.getNamespace() + "selPlid=" + selPlid %>'
/>

<c:choose>
	<c:when test='<%= tabs4.equals("regular-browsers") %>'>

		<%
		Theme selTheme = null;
		ColorScheme selColorScheme = null;

		if (selLayout != null) {
			selTheme = selLayout.getTheme();
			selColorScheme = selLayout.getColorScheme();
		}
		else {
			LayoutSet layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(groupId, privateLayout);

			selTheme = layoutSet.getTheme();
			selColorScheme = layoutSet.getColorScheme();
		}
		%>

		<c:if test="<%= selLayout != null %>">
			<table class="lfr-table">
			<tr>
				<td>
					<%= LanguageUtil.get(pageContext, "inherit-look-and-feel-from-the-" + (privateLayout ? "public" : "private") + "-root-node") %>
				</td>
				<td>
					<select name="<portlet:namespace />hidden" onChange="if (this.value == 1) { <portlet:namespace />updateLookAndFeel('', ''); } else { <portlet:namespace />updateLookAndFeel('<%= selTheme.getThemeId() %>', '<%= selColorScheme.getColorSchemeId() %>'); }">
						<option <%= (selLayout.isInheritLookAndFeel()) ? "selected" : "" %> value="1"><liferay-ui:message key="yes" /></option>
						<option <%= (!selLayout.isInheritLookAndFeel()) ? "selected" : "" %> value="0"><liferay-ui:message key="no" /></option>
					</select>
				</td>
			</table>

			<br />
		</c:if>

		<liferay-ui:tabs names="themes,color-schemes,css" refresh="<%= false %>">
			<liferay-ui:section>

				<%
				List themes = ThemeLocalUtil.getThemes(company.getCompanyId(), liveGroupId, user.getUserId(), false);
				%>

				<liferay-ui:table-iterator
					list="<%= themes %>"
					listType="com.liferay.portal.model.Theme"
					rowLength="2"
					rowPadding="30"
					rowValign="top"
				>
					<table border="0" cellpadding="0" cellspacing="0">
					<tr>
						<td align="center">
							<%= tableIteratorObj.getName() %> <input <%= selTheme.getThemeId().equals(tableIteratorObj.getThemeId()) ? "checked" : "" %> name="<portlet:namespace />themeId" type="radio" value="<%= tableIteratorObj.getThemeId() %>" onClick="<portlet:namespace />updateLookAndFeel('<%= tableIteratorObj.getThemeId() %>', '', '<%= sectionParam %>', '<%= sectionName %>');"><br />

							<img border="0" hspace="0" src="<%= tableIteratorObj.getContextPath() %><%= tableIteratorObj.getImagesPath() %>/thumbnail.png" vspace="0" />
						</td>
					</tr>
					</table>
				</liferay-ui:table-iterator>
			</liferay-ui:section>
			<liferay-ui:section>

				<%
				List colorSchemes = selTheme.getColorSchemes();
				%>

				<c:choose>
					<c:when test="<%= colorSchemes.size() > 0 %>">
						<liferay-ui:table-iterator
							list="<%= colorSchemes %>"
							listType="com.liferay.portal.model.ColorScheme"
							rowLength="2"
							rowPadding="30"
							rowValign="top"
						>
							<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<%= tableIteratorObj.getName() %> <input <%= selColorScheme.getColorSchemeId().equals(tableIteratorObj.getColorSchemeId()) ? "checked" : "" %> name="<portlet:namespace />colorSchemeId" type="radio" value="<%= tableIteratorObj.getColorSchemeId() %>" onClick="<portlet:namespace />updateLookAndFeel('<%= selTheme.getThemeId() %>', '<%= tableIteratorObj.getColorSchemeId() %>', '<%= sectionParam %>', '<%= sectionName %>')"><br />

									<img border="0" hspace="0" src="<%= selTheme.getContextPath() %><%= tableIteratorObj.getColorSchemeImagesPath() %>/thumbnail.png" vspace="0" />
								</td>
							</tr>
							</table>
						</liferay-ui:table-iterator>
					</c:when>
					<c:otherwise>
						<liferay-ui:message key="this-theme-does-not-have-any-color-schemes" />
					</c:otherwise>
				</c:choose>
			</liferay-ui:section>
			<liferay-ui:section>

				<%
				String selColorSchemeId = StringPool.BLANK;

				if (selTheme.hasColorSchemes()) {
					selColorSchemeId = selColorScheme.getColorSchemeId();
				}

				String cssText = null;

				if ((selLayout != null) && !selLayout.isInheritLookAndFeel()) {
					cssText = selLayout.getCssText();
				}
				else {
					LayoutSet layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(groupId, privateLayout);

					cssText = layoutSet.getCss();
				}
				%>

				<liferay-ui:message key="insert-custom-css-that-will-loaded-after-the-theme" />

				<br /><br />

				<textarea class="lfr-textarea" name="<portlet:namespace />css"><%= cssText %></textarea>

				<br /><br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />updateLookAndFeel('<%= selTheme.getThemeId() %>', '<%= selColorSchemeId %>', '<%= sectionParam %>', '<%= sectionName %>');" />
			</liferay-ui:section>
		</liferay-ui:tabs>
	</c:when>
	<c:when test='<%= tabs4.equals("mobile-devices") %>'>

		<%
		Theme selTheme = null;
		ColorScheme selColorScheme = null;

		if (selLayout != null) {
			selTheme = selLayout.getWapTheme();
			selColorScheme = selLayout.getWapColorScheme();
		}
		else {
			LayoutSet layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(groupId, privateLayout);

			selTheme = layoutSet.getWapTheme();
			selColorScheme = layoutSet.getWapColorScheme();
		}
		%>

		<c:if test="<%= selLayout != null %>">
			<table class="lfr-table">
			<tr>
				<td>
					<%= LanguageUtil.get(pageContext, "inherit-look-and-feel-from-the-" + (privateLayout ? "public" : "private") + "-root-node") %>
				</td>
				<td>
					<select name="<portlet:namespace />hidden" onChange="if (this.value == 1) { <portlet:namespace />updateLookAndFeel('', ''); } else { <portlet:namespace />updateLookAndFeel('<%= selTheme.getThemeId() %>', '<%= selColorScheme.getColorSchemeId() %>'); }">
						<option <%= (selLayout.isInheritWapLookAndFeel()) ? "selected" : "" %> value="1"><liferay-ui:message key="yes" /></option>
						<option <%= (!selLayout.isInheritWapLookAndFeel()) ? "selected" : "" %> value="0"><liferay-ui:message key="no" /></option>
					</select>
				</td>
			</table>

			<br />
		</c:if>

		<liferay-ui:tabs names="themes" />

		<%
		List themes = ThemeLocalUtil.getThemes(company.getCompanyId(), liveGroupId, user.getUserId(), true);
		%>

		<liferay-ui:table-iterator
			list="<%= themes %>"
			listType="com.liferay.portal.model.Theme"
			rowLength="2"
			rowPadding="30"
			rowValign="top"
		>
			<table border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td align="center">
					<%= tableIteratorObj.getName() %> <input <%= selTheme.getThemeId().equals(tableIteratorObj.getThemeId()) ? "checked" : "" %> name="<portlet:namespace />themeId" type="radio" value="<%= tableIteratorObj.getThemeId() %>" onClick="<portlet:namespace />updateLookAndFeel('<%= tableIteratorObj.getThemeId() %>', '');"><br />

					<img border="0" hspace="0" src="<%= tableIteratorObj.getContextPath() %><%= tableIteratorObj.getImagesPath() %>/thumbnail.png" vspace="0" />
				</td>
			</tr>
			</table>
		</liferay-ui:table-iterator>
	</c:when>
</c:choose>